#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QMessageBox>
#include <QString>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget)
{
    ui->setupUi(this);
}

LoginWidget::~LoginWidget()
{
    delete ui;
}

void LoginWidget::on_buttonBox_rejected()
{
    emit rejected();
}

void LoginWidget::on_buttonBox_accepted()
{
    auto userID = m_dbPtr->checkPassword(ui->lineEdit->text().toStdString(), ui->lineEdit_2->text().toStdString());
    if(userID == -1){
        QMessageBox::critical(this, tr("Error"), tr("Uncorrect password!"));
        return;
    }
    emit accepted(userID, ui->lineEdit->text());
}

void LoginWidget::on_RegisterButton_clicked()
{
    emit registrationRequested();
}

void LoginWidget::SetDatabase(std::shared_ptr<Database> dbPtr){
    m_dbPtr = dbPtr;
}
