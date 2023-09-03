#include "reportresult.h"
#include "ui_reportresult.h"
#include "userhome.h"

#include <QMessageBox>
#include <QFile>
#include <QTextStream>

reportResult::reportResult(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::reportResult)
{
    ui->setupUi(this);

    ui->confirmEmail->setPlaceholderText("Confirm email address");
    ui->stepOneFrame->setVisible(false);
    ui->stepTwoFrame->setVisible(false);

    QPixmap pix ("D:/YOOBEE/Software_Dev/Module 6_Integrated Studio II/Assessment 2/CovidRecord/My_Covid_Record_App/Images/positivetest.png");
    int w = ui->testImage->width();
    int h = ui->testImage->height();
    ui->testImage->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));
}

reportResult::~reportResult()
{
    delete ui;
}

void reportResult::on_continueButton_clicked()
{
    ui->stepOneFrame->show();
}

void reportResult::on_nextStep_clicked()
{
    ui->stepTwoFrame->show();
}
void reportResult::on_enterResultButton_clicked()
{
    // Retrieve checkbox values
    bool controlYesChecked = ui->controlYes->isChecked();
    bool controlNoChecked = ui->controlNo->isChecked();
    bool testYesChecked = ui->testYes->isChecked();
    bool testNoChecked = ui->testNo->isChecked();

    // Determine the test result based on checkbox values
    QString testResult;
    if (controlYesChecked && testYesChecked) {
        testResult = "Positive";
    } else if (controlYesChecked && testNoChecked) {
        testResult = "Negative";
    } else if (controlNoChecked && testYesChecked) {
        testResult = "Inconclusive";
    } else if (!controlYesChecked && !testYesChecked) {
        testResult = "Inconclusive";
    }

    // Retrieve other data
    QDate testDate = ui->testDate->date();
    QTime testTime = ui->testTime->time();
    QString confirmEmail = ui->confirmEmail->text();

    // Open "userResults.txt" in append mode
    QFile userResultsFile("userResults.txt");
    if (userResultsFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&userResultsFile);

        // Write the user's email
        stream << "User email: " << confirmEmail << "\n";

        // Write the test result information
        stream << "Disease targeted: SARS-CoV/COVID-19" << "\n";
        stream << "Date of test: " << testDate.toString("dd.MM.yyyy") << "\n";
        stream << "Time of test: " << testTime.toString("hh:mm") << "\n";
        stream << "Result: " << testResult << "\n";
        stream << "-------------------------" << "\n"; // Separation for the next entry

        // Close the file
        userResultsFile.close();

        // Show a message box to confirm saving
        QMessageBox::information(this, "Success", "The results of your RAT test have now been added to" "\n" "the userResults.txt file." "\n" "Results may take up to 30 minutes to appear in your history");

    } else {
        QMessageBox::critical(this, "Error", "Failed to open userResults.txt file.");
    }

    userHome *homeWidget = new userHome;
    homeWidget->show();
    this->close();
}


void reportResult::on_userButton_clicked()
{
    userHome *homeWidget = new userHome;
    homeWidget->show();
    this->close();
}

