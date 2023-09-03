#include "loginform.h"
#include "ui_loginform.h"
#include "userhome.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

loginForm::loginForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loginForm)
{
    ui->setupUi(this);
}

loginForm::~loginForm()
{
    delete ui;
}

bool loginForm::checkCredentials(const QString &email, const QString &password)
{
    QFile userDetails("userDetails.txt");
    if (userDetails.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&userDetails);
        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList fields = line.split(": ");
            if (fields.size() == 2 && fields[0] == "Email" && fields[1] == email) {
                line = stream.readLine(); // Move to password line
                fields = line.split(": ");
                if (fields.size() == 2 && fields[0] == "Password" && fields[1] == password) {
                    userDetails.close();
                    return true; // Email and password match
                }
            }
        }
        userDetails.close();
    }
    return false; // Email not found or password doesn't match
}

QString loginForm::getUserFirstName(const QString &email)
{
    QFile userDetails("userDetails.txt");
    if (userDetails.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&userDetails);
        QString firstName;
        QString currentEmail;

        while (!stream.atEnd()) {
            QString line = stream.readLine();
            QStringList fields = line.split(": ");
            if (fields.size() == 2 && fields[0] == "First Name") {
                firstName = fields[1]; // Get the user's first name
            }
            if (fields.size() == 2 && fields[0] == "Email") {
                currentEmail = fields[1];
                if (currentEmail == email) {
                    userDetails.close();
                    return firstName; // Return the user's first name
                }
            }
        }

        userDetails.close();
    }

    return QString(); // Return an empty string if not found
}

void loginForm::on_confirmLoginButton_clicked()
{
        QString email = ui->emailEnter->text();
        QString password = ui->passwordEnter->text();

        // Check if credentials are correct
        if (checkCredentials(email, password)) {
            // Open the userHome widget and set the user's first name
            userHome *home = new userHome;

            // Get the user's first name
            QString firstName = getUserFirstName(email);

            home->setUserFirstName(firstName); // Set the user's first name
            home->show();

            // Close the loginForm widget
            close();

        } else {
            QMessageBox::warning(this, "Error", "Incorrect email or password.");
     }
   }

void loginForm::on_pushButton_clicked()
{
     QString message = "Password reset instructions" "\n" "have been sent to your email";
     QMessageBox::information(this, "Password reset", message);

}

