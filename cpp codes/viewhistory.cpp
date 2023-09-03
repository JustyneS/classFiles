#include "viewhistory.h"
#include "ui_viewhistory.h"
#include "userhome.h"

#include <QFile>
#include <QTextStream>
#include <QPlainTextEdit>

viewHistory::viewHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::viewHistory)
{
    ui->setupUi(this);
    ui->checkEmail->setPlaceholderText("Confirm email to view");
}

viewHistory::~viewHistory()
{
    delete ui;
}


void viewHistory::on_viewHistoryButton_clicked()
{
    // Get the entered email from the checkEmail field
    QString emailToCheck = ui->checkEmail->text();

    // Open the "userResults.txt" file for reading
    QFile userResultsFile("userResults.txt");
    if (userResultsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&userResultsFile);

        // Clear the existing text in historyDisplay
        ui->historyDisplay->clear();

        while (!stream.atEnd()) {
            QString line = stream.readLine();

            // Check if the line contains the user's email
            if (line.contains("User email: " + emailToCheck)) {
                QString testResult = "";
                QString testDate = "";
                QString testTime = "";

                // Read the relevant test result information
                while (!stream.atEnd()) {
                    line = stream.readLine();
                    if (line.startsWith("Date of test: ")) {
                        testDate = line.mid(15);
                    } else if (line.startsWith("Time of test: ")) {
                        testTime = line.mid(15);
                    } else if (line.startsWith("Result: ")) {
                        testResult = line.mid(8);
                        break;  // Break when we have read all relevant information
                    }
                }

                // Display the test result information in the desired format
                ui->historyDisplay->appendPlainText("Disease targeted: SARS-CoV/COVID-19");
                ui->historyDisplay->appendPlainText("Date of test: " + testDate);
                ui->historyDisplay->appendPlainText("Time of test: " + testTime);
                ui->historyDisplay->appendPlainText("Result: " + testResult);
                ui->historyDisplay->appendPlainText("-------------------------");
            }
        }

        userResultsFile.close();
    }
}



void viewHistory::on_returnHomeButton_clicked()
{
    userHome *homeWidget = new userHome;
    homeWidget->show();
    this->close();
}


void viewHistory::on_userButton_clicked()
{
    userHome *homeWidget = new userHome;
    homeWidget->show();
    this->close();
}

