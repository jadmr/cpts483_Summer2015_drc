#include "mainmenutabwidget.h"
#include "ui_mainmenutabwidget.h"
#include "fruitnameform.h"
#include "intakeform.h"

MainMenuTabWidget::MainMenuTabWidget(QWidget *parent) :
    QTabWidget(parent),
    ui(new Ui::MainMenuTabWidget)
{
    ui->setupUi(this);
//    this->setWindowState(Qt::WindowMaximized);
//    QTabWidget::showFullScreen();
    // Setup the Tabs
    clear();
    addTab(new FruitNameForm(), "Fruit1");
    addTab(new IntakeForm(), "Intake Form");
}

MainMenuTabWidget::~MainMenuTabWidget()
{
    delete ui;
}
