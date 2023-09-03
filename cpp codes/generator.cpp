#include "generator.h"
#include "ui_generator.h"
#include "adminportal.h"
#include<QMessageBox>

generator::generator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::generator)
{
    ui->setupUi(this);
}

generator::~generator()
{
    delete ui;
}

void generator::setUserNames(const QString &firstName, const QString &lastName)
{
    ui->userNameLabel->setText("Generate and assign QR code for user: " + firstName + " " + lastName);
}

void generator::on_generateButton_clicked()
{
    // Load the QR image
    QPixmap image("D:/YOOBEE/Software_Dev/Module 6_Integrated Studio II/Assessment 2/CovidRecord./My_Covid_Record_App/Images/george.png");
    // Set the image as the pixmap for the genLabel
    ui->genLabel->setPixmap(image);
    int w = ui->genLabel->width();
    int h = ui->genLabel->height();
    ui->genLabel->setPixmap(image.scaled(w, h));
}




void generator::on_pushButton_clicked()
{
    QString message = "Thank you, QR has been assigned to user.";
    QMessageBox::information(this, "Success!", message);
    adminPortal *portalWidget = new adminPortal;
    portalWidget->show();
    this->hide();

}

