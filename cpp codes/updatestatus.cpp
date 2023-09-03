#include "updatestatus.h"
#include "ui_updatestatus.h"
#include "adminportal.h"
#include <QFile>
#include <QPlainTextEdit>
#include <QStringList>
#include <QMessageBox>

updateStatus::updateStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::updateStatus)
{
    ui->setupUi(this);
    ui->vacForm->setVisible(false);
}

updateStatus::~updateStatus()
{
    delete ui;
}

QString updateStatus::getEmail() const
{
    return userEmail;
}

void updateStatus::setEmail(const QString &email)
{
    userEmail = email;
}

void updateStatus::setUserNames(const QString &firstName, const QString &lastName)
{
    ui->userNameLabel->setText("Update vaccinations for: " + firstName + " " + lastName);
}

void updateStatus::on_enterVacButton_clicked()
{
    ui->vacForm->setVisible(true); // Show the vacForm frame
}

void updateStatus::on_confSaveButton_clicked()
{
    int doseCount = ui->doseCount_3->value();
    QString vacDate = ui->vacDate_3->date().toString("dd.MM.yyyy");
    QString vacAgainst = ui->vacAgainst_3->text();
    QString vacType = ui->vacType_3->text();
    QString vacLoc = ui->vacLoc_3->text(); 
    bool isFullVaxChecked = ui->fullVax->isChecked();
    bool isPartialVaxChecked = ui->partialVax->isChecked();

    if (userEmail.isEmpty()) {
        QMessageBox::warning(this, "Error", "No email found.");
        return;
    }
    // Open the userDetails.txt file
    QFile userDetails("userDetails.txt");
    if (userDetails.open(QIODevice::ReadWrite | QIODevice::Text)) {
        QTextStream stream(&userDetails);

        QString line;
        QStringList newLines;

        // Copy lines until the user section is found
        while (!stream.atEnd()) {
            line = stream.readLine();
            newLines.append(line);

            // If the line contains the user's email, add vaccination details after the password line
            if (line.contains("Email: " + userEmail)) {
                while (!line.contains("Password:")) {
                    line = stream.readLine(); // Skip lines until the password line
                    newLines.append(line);
                }
                // Add vaccination details after the password line
                newLines.append("\n");
                newLines.append("**Vaccination Details**");
                newLines.append("Dose Count: " + QString::number(doseCount));

                // Add Vaccination Level based on checkbox state
                if (isFullVaxChecked) {
                    newLines.append("Vaccination Level: Full");
                } else if (isPartialVaxChecked) {
                    newLines.append("Vaccination Level: Partial");
                }
                newLines.append("Vaccination Date: " + vacDate);
                newLines.append("Vaccination Against: " + vacAgainst);
                newLines.append("Vaccination Type: " + vacType);
                newLines.append("Administering Location: " + vacLoc);
            }
        }
        // Rewrite the file with updated information
        userDetails.resize(0);
        foreach (const QString &newLine, newLines) {
            stream << newLine << Qt::endl;
        }
        userDetails.close();
        // Hide the vacForm frame
        ui->vacForm->setVisible(false);

        // Show a message box to confirm saving
        QMessageBox::information(this, "Success", "Vaccination details saved.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to open user details file.");
    }
}

void updateStatus::displayDoseInformation(int doseCount, QPlainTextEdit* doseView)
{
    // Open the userDetails.txt file
    QFile userDetails("userDetails.txt");
    if (userDetails.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&userDetails);

        QString line;
        bool foundUser = false;
        bool foundDose = false;

        while (!stream.atEnd()) {
            line = stream.readLine();

            if (line.startsWith("Email: " + userEmail)) {
                foundUser = true;
                continue; // Skip user details until we find the right user
            }

            if (foundUser) {
                if (line.startsWith("**Vaccination Details**")) {
                    while (!stream.atEnd()) {
                        line = stream.readLine();

                        if (line.startsWith("Dose Count: " + QString::number(doseCount))) {
                            foundDose = true;
                            break; // Found the dose info, exit the loop
                        }
                    }
                }

                if (foundDose) {
                    // Display the dose details
                    doseView->appendPlainText(line);

                    if (line.startsWith("Administering Location:")) {
                        break; // Stop displaying after Administering Location
                    }
                }
            }
        }

        if (!foundDose) {
            doseView->setPlainText("Dose Count: " + QString::number(doseCount) + "\nVaccination Date: ...\nVaccination Against: ...\nVaccination Type: ...\nAdministering Location: ...");
        }

        userDetails.close();
    } else {
        QMessageBox::critical(this, "Error", "Failed to open user details file.");
    }
}

void updateStatus::on_firstDoseButton_clicked()
{
    displayDoseInformation(1, ui->firstDoseView);
}

void updateStatus::on_secondDoseButton_clicked()
{
    displayDoseInformation(2, ui->secondDoseView);
}

void updateStatus::on_thirdDoseButton_clicked()
{
    displayDoseInformation(3, ui->thirdDoseView);
}

void updateStatus::on_pushButton_clicked()
{
    adminPortal *portalWidget = new adminPortal;
    portalWidget->show();
    this->hide();
}
