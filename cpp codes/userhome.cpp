#include "userhome.h"
#include "ui_userhome.h"
#include "reportresult.h"
#include "viewhistory.h"
#include "vaxhistory.h"


userHome::userHome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::userHome)
{
    ui->setupUi(this);
}
userHome::~userHome()
{
    delete ui;
}

void userHome::setUserFirstName(const QString &firstName)
{
    userFirstName = firstName;
    // Update the greeting label text with the user's first name
    ui->greetingLabel->setText("Kia ora, " + userFirstName);
}

void userHome::on_reportButton_clicked()
{
    reportResult *reportWidget = new reportResult;
    reportWidget->show();
    this->hide();
}


void userHome::on_historyButton_clicked()
{
    viewHistory *historyWidget = new viewHistory;
    historyWidget->show();
    this->close();
}


void userHome::on_vaccineButton_clicked()
{
    vaxHistory *vaxWidget = new vaxHistory;
    vaxWidget->show();
    this->hide();
}

