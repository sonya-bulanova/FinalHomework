#include "registerform.h"
#include "ui_registerform.h"
#include <QMessageBox>

RegisterForm::RegisterForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterForm)
{
    ui->setupUi(this);
}

RegisterForm::~RegisterForm()
{
    delete ui;
}

void RegisterForm::on_pushButton_clicked()
{
    emit loginRequested();
}

void RegisterForm::on_buttonBox_accepted()
{
    if(ui->lineEdit_2->text() != ui->lineEdit_3->text()){
        QMessageBox::critical(this, tr("Error"), tr("Passwords don't match!"));
        return;
    }
    auto userID = m_dbPtr->addUser(ui->lineEdit->text().toStdString(), ui->lineEdit_2->text().toStdString(), ui->lineEdit_4->text().toStdString());

    switch(userID){
    case -1:
        QMessageBox::critical(this, tr("Error"), tr("Incorrect Login!"));
        return;
    case -2:
        QMessageBox::critical(this, tr("Error"), tr("Login already exists!"));
        return;
    default:
        emit accepted(userID, ui->lineEdit->text());
    }
}

void RegisterForm::on_buttonBox_rejected()
{
    emit rejected();
}

void RegisterForm::SetDatabase(std::shared_ptr<Database> dbPtr){
    m_dbPtr = dbPtr;
}
