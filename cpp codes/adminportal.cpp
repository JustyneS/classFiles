    #include "adminportal.h"
    #include "ui_adminportal.h"
    #include "generator.h"
    #include "updatestatus.h"
    #include <QFile>
    #include <QStringList>
    #include <QTextStream>
    #include <QMessageBox>

    adminPortal::adminPortal(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::adminPortal)
    {
        ui->setupUi(this);
        ui->emailInput->setPlaceholderText("Enter email address");
    }

    adminPortal::~adminPortal()
    {
        delete ui;
    }


    bool adminPortal::searchUserDetails(const QString &searchEmail, QString &firstName, QString &lastName)
    {
        QFile userDetails("userDetails.txt");
        if (userDetails.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream stream(&userDetails);

            QString line;
            QStringList userLines;
            bool foundUser = false;

            while (!stream.atEnd()) {
                line = stream.readLine();
                userLines.prepend(line);
                if (line.startsWith("Email: " + searchEmail)) {
                    foundUser = true;
                    break;
                }
            }
            userDetails.close();
            if (foundUser) {
                foreach (const QString &userLine, userLines) {
                    if (userLine.startsWith("First Name: ")) {
                        firstName = userLine.mid(12);
                    } else if (userLine.startsWith("Last Name: ")) {
                        lastName = userLine.mid(11);
                    }
                    if (userLine.startsWith("===")) {
                        break;
                    }
                    ui->displayArea->appendPlainText(userLine);
                }
                return true;
            } else {
                return false;
            }
        } else {
            QMessageBox::critical(this, "Error", "Failed to open user details file.");
            return false;
        }
    }

    void adminPortal::on_searchButton_clicked()
    {
        QString email = ui->emailInput->text(); // Get the email from the line edit

        if (!email.isEmpty()) {
            QString firstName, lastName;
            QString userDetails; // Store the user details
            if (searchUserDetails(email, firstName, lastName)) {
                // Retrieve the user details
                userDetails = ui->displayArea->toPlainText();
            } else {
                QMessageBox::information(this, "Result", "User with the specified email not found.");
                return;
            }
            // Display the user details in the displayArea
            ui->displayArea->clear();
            ui->displayArea->setPlainText(userDetails);
        } else {
            QMessageBox::warning(this, "Error", "Please enter an email to search.");
        }
    }

    void adminPortal::on_qrGenButton_clicked()
    {
        QString email = ui->emailInput->text(); // Get the email from the line edit

        if (!email.isEmpty()) {
            QString firstName, lastName;
            if (searchUserDetails(email, firstName, lastName)) {
                generator *genWidget = new generator;
                genWidget->setUserNames(firstName, lastName); // Set the names for the label
                genWidget->show();
                this->hide();
            } else {
                QMessageBox::information(this, "Result", "User with the specified email not found.");
            }
        } else {
            QMessageBox::warning(this, "Error", "Please enter an email to search.");
        }
    }


    void adminPortal::on_updateVacButton_clicked()
    {
        QString email = ui->emailInput->text(); // Get the email from the line edit

        if (!email.isEmpty()) {
            QString firstName, lastName;
            if (searchUserDetails(email, firstName, lastName)) {
                updateStatus *updateWidget = new updateStatus;
                updateWidget->setUserNames(firstName, lastName); // Set the names for the label
                updateWidget->setEmail(email); // Pass the email
                updateWidget->show();
                this->hide();
            } else {
                QMessageBox::information(this, "Result", "User with the specified email not found.");
            }
        } else {
            QMessageBox::warning(this, "Error", "Please enter an email to search.");
        }
    }


