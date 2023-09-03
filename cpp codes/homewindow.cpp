#include "homewindow.h"
#include "./ui_homewindow.h"
#include "registrationform.h"
#include "loginform.h"
#include "adminlogin.h"


homeWindow::homeWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::homeWindow)
{
    ui->setupUi(this);
    QPixmap pix ("D:/YOOBEE/Software_Dev/Module 6_Integrated Studio II/Assessment 2/CovidRecord/My_Covid_Record_App/Images/beKind.png");
    int w = ui->beKindImage->width();
    int h = ui->beKindImage->height();
    ui->beKindImage->setPixmap(pix.scaled(w,h));
}


homeWindow::~homeWindow()
{
    delete ui;
}

void homeWindow::on_registerButton_2_clicked()
{
    // Creating an instance of the registrationForm widget then displaying the widget
    registrationForm *registrationWidget = new registrationForm;
    registrationWidget->show();
    this->hide(); // Hide the current widget (homeWindow)
}


void homeWindow::on_loginButton_2_clicked()
{
    // Creating an instance of the loginForm widget then displaying the widget
    loginForm *loginWidget = new loginForm;
    loginWidget->show();
    this->hide();
}


void homeWindow::on_adminButton_clicked()
{
    //Creating an instance of adminLogin widget then displaying the widget
    adminLogin *adminLogWidget = new adminLogin;
    adminLogWidget->show();
    this->hide();
}



