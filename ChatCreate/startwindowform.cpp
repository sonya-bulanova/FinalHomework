#include "startwindowform.h"
#include "ui_startwindowform.h"
#include "startwindow.h"
#include "ui_startwindow.h"

StartWindowForm::StartWindowForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StartWindowForm)
{
    ui->setupUi(this);
}

StartWindowForm::~StartWindowForm()
{
    delete ui;
}

void StartWindowForm::on_SignInButton_clicked()
{
    emit SignInRequest();
}

void StartWindowForm::on_SignUpButton_clicked()
{
    emit SignUpRequest();
}
