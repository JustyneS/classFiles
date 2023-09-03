#include "registrationform.h"
#include "ui_registrationform.h"
#include "loginform.h"
#include "homewindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

registrationForm::registrationForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registrationForm)
{
    ui->setupUi(this);
}

registrationForm::~registrationForm()
{
    delete ui;
}

void registrationForm::on_submitButton_clicked()
{
    QString firstName = ui->firstnameEdit->text();
    QString lastName = ui->lastnameEdit->text();
    QDate birthdate = ui->dobEdit->date();
    QString mobile = ui->mobileEdit->text();
    QString email = ui->emailEdit->text();
    QString password = ui->passwordEdit->text();

    // Check if any of the fields are empty
    if (firstName.isEmpty() || lastName.isEmpty() || mobile.isEmpty() || email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill out all fields.");
        return;
    }

    // Save user details to a file
    QFile userDetails("userDetails.txt");
    if (userDetails.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&userDetails);
        stream << "First Name: " << firstName << "\n";
        stream << "Last Name: " << lastName << "\n";
        stream << "Date of Birth: " << birthdate.toString("dd.MM.yyyy") << "\n";
        stream << "Mobile: " << mobile << "\n";
        stream << "Email: " << email << "\n";
        stream << "Password: " << password << "\n";
        stream << "===" << "\n"; // Separator between users
        userDetails.close();
        QMessageBox::information(this, "Success", "User details saved successfully.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to save user details.");
    }
    // Open the loginForm widget
    loginForm *login = new loginForm;
    login->show();
    close(); // Close the registrationForm widget
}



void registrationForm::on_userButton_clicked()
{
    homeWindow *homeWidget = new homeWindow;
    homeWidget->show();
    this->hide();
}

