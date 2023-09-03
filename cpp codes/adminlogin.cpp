#include "adminlogin.h"
#include "ui_adminlogin.h"
#include "adminportal.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

adminLogin::adminLogin(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::adminLogin)
{
    ui->setupUi(this);
}

adminLogin::~adminLogin()
{
    delete ui;
}
bool adminLogin::checkCredentials(const QString &email, const QString &password)
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

void adminLogin::on_adminLogButton_clicked()
{
    QString email = ui->adminUserEnter->text();
    QString password = ui->adminPasswordEnter->text();

    // Check if credentials are correct
    if (checkCredentials(email, password)) {
        // Open the userHome widget and set the user's first name
        adminPortal *adminPage = new adminPortal;
        adminPage->show();

        // Close the loginForm widget
        close();

    } else {
        QMessageBox::warning(this, "Error", "Incorrect email or password.");
    }
}

