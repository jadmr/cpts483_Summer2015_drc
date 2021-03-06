#include "asyncmediatorworker.h"
#include "MediatorArg.h"
#include "Mediator.h"
#include <QDebug>

// --- CONSTRUCTOR ---
AsyncMediatorWorker::AsyncMediatorWorker(
        QString sendEventMediatorKey,
        QString recieveEventMediatorKey,
        MediatorCallbackFunc callback,
        void* argObject,
        bool waitForResponse,
        unsigned long timeoutSecs)
    : _sendEventMediatorKey(sendEventMediatorKey)
    , _recieveEventMediatorKey(recieveEventMediatorKey)
    , _callback(callback)
    , _sendMediatorArg(MediatorArg(argObject))
    , _willWaitForResponse(waitForResponse)
    , _timeoutSecs(timeoutSecs)
{
}
// --- CONSTRUCTOR ---
AsyncMediatorWorker::AsyncMediatorWorker(
        QString sendEventMediatorKey,
        QString recieveEventMediatorKey,
        MediatorCallbackFunc callback,
        MediatorArg sendMediatorArg,
        bool waitForResponse,
        unsigned long timeoutSecs)
    : _sendEventMediatorKey(sendEventMediatorKey)
    , _recieveEventMediatorKey(recieveEventMediatorKey)
    , _callback(callback)
    , _sendMediatorArg(sendMediatorArg)
    , _willWaitForResponse(waitForResponse)
    , _timeoutSecs(timeoutSecs)
{
}

// --- DECONSTRUCTOR ---
AsyncMediatorWorker::~AsyncMediatorWorker()
{
    // free resources
}

// --- Start ---
// This will send the outgoing event, and optionally wait for a response.
// When a response is reached the supplied callback will be called.
void AsyncMediatorWorker::Start()
{
    qDebug() << "AsyncMediatorWorker -> thread running...";

    _waiting = true;

    // Reset response data
    _recieveMediatorArg.SetSuccessful(true);
    _recieveMediatorArg.SetErrorMsg("");

    // Start listening for a response
    ResponseRecievedId = Mediator::Register(_recieveEventMediatorKey, [this](MediatorArg mediatorArg) { this->ResponseRecieved(mediatorArg); });

    // Send the Request
    Mediator::Call(_sendEventMediatorKey, _sendMediatorArg);

    // Wait or Timeout
    if(!WaitForResponse())
    {
        _recieveMediatorArg.SetSuccessful(false);
        _recieveMediatorArg.SetErrorMsg("Request timed out.");
    }

    // Stop listening for a response
     Mediator::Unregister(_recieveEventMediatorKey, ResponseRecievedId);

    // Update the response argument on MediatorCalback (main thread)
    emit sendResponseArg(_recieveMediatorArg);

    // This will cause the thread to shut down. (this triggers the callback on main thread)
    emit finished();
}
double AsyncMediatorWorker::Elapsed(clock_t startTime) {
    return double(clock() - startTime) / CLOCKS_PER_SEC;
}

// This will wait for the asynchronous response. This is intended to be run asynchronously
bool AsyncMediatorWorker::WaitForResponse()
{
    clock_t startTime = clock();
    // Wait for a response, or timeout
    while (_willWaitForResponse && _waiting)
    {
        double elapsed = Elapsed(startTime);
        if (elapsed > _timeoutSecs)
        {
            _waiting = false;
            qDebug() << "AsyncMediatorWorker -> Timeout";
            return false;		// timeout = error
        }
    }
    _waiting = false;
    return true;			// no error
}

// This internal function handles maintenance when a response is recieved. Then the _callback is called.
void AsyncMediatorWorker::ResponseRecieved(MediatorArg mediatorArg)
{
    _recieveMediatorArg = mediatorArg;
     qDebug() << "Async -> Response recieved - thread terminated.";

    // Ready to do it again
    _waiting = false;
}
