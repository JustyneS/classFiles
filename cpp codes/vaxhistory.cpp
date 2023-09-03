// vaxhistory.cpp
#include "vaxhistory.h"
#include "ui_vaxhistory.h"
#include "userhome.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>

vaxHistory::vaxHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vaxHistory)
{
    ui->setupUi(this);
    ui->checkUserField->setPlaceholderText("Confirm your email");
}

vaxHistory::~vaxHistory()
{
    delete ui;
}

void vaxHistory::on_checkUserButton_clicked()
{
    QString userEmail = ui->checkUserField->text();
    QFile userDetailsFile("userDetails.txt");

    if (userDetailsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&userDetailsFile);

        QString line;
        bool foundUser = false;
        QString userVaxDetails; // Store user's vaccination details

        while (!stream.atEnd()) {
            line = stream.readLine();

            if (line.startsWith("Email: " + userEmail)) {
                foundUser = true;
                continue;
            }

            if (foundUser) {
                if (line.startsWith("===")) {
                    break; // End of user data
                }

                if (!line.startsWith("Password:")) {
                    // Skip lines containing passwords
                    userVaxDetails += line + "\n";
                }
            }
        }

        if (!userVaxDetails.isEmpty()) {
            ui->vaxDisplayArea->setPlainText(userVaxDetails);
        } else {
            ui->vaxDisplayArea->setPlainText("User not found.");
        }

        userDetailsFile.close();
    } else {
        QMessageBox::critical(this, "Error", "Failed to open user details file.");
    }
}


void vaxHistory::on_userButton_clicked()
{
    userHome *userWidget = new userHome;
    userWidget->show();
    this->hide();
}

