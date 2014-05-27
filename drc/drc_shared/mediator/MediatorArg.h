//
//  MediatorArg.h
//  mediator_test
//
//  Created by Lansdon Page on 5/25/14.
//  Copyright (c) 2014 lp. All rights reserved.
//

#ifndef mediator_test_MediatorArg_h
#define mediator_test_MediatorArg_h

#include <assert.h>
#include <typeinfo>
#include <type_traits>
#include <string>
#include <iostream>

//namespace drc {
//namespace drc_shared {

class MediatorArg
{
public:
	MediatorArg(void* arg = nullptr, bool success = true, std::string errorMessage = "")
	: _arg(arg)
	, _success(success)
	, _errorMessage(errorMessage)
	{};
	~MediatorArg() { }
	
	// Accessors
	bool IsSuccessful() { return _success; };
	void SetSuccessful(bool isSuccessful) { _success = isSuccessful; }
	std::string ErrorMessage() { return _errorMessage; }
	void SetErrorMsg(std::string errorMessage) { _errorMessage = errorMessage; }
	void SetArg(void* arg) { _arg = arg; }
	
	// Cast the argument to expected type (Must be a pointer!)
	template<typename T>
	T getArg() {
		
		// Verify T is a pointer. MUST BE A POINTER
		assert(std::is_pointer<T>::value);
		
		// Special case for no arguments
		if(_arg == nullptr) return nullptr;
		
		if (T result = static_cast<T>(_arg)) {
			return result;
		} else {
			std::cerr << "Mediator arg conversion error. Cannot cast to " << typeid(T).name() << "\n";
			assert(false);
			return nullptr;
		}
	};
	
private:
	void* _arg;					// optional pointer to some object
	
	// Meta data
	bool _success;				// Success or fail status of the caller
	std::string _errorMessage;	// Reason for the error
	
	// ... We can add other meta as desired
	
};

//}   // end namespace drc_shared
//}   // end namespace drc

#endif
