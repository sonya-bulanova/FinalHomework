#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(std::shared_ptr<Database> dbPtr, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartWindow)
{
    ui->setupUi(this);
    if (dbPtr){
        m_dbPtr = dbPtr;
    } else {
        m_dbPtr = std::make_shared<Database>();
    }
    ui->PageLogin->SetDatabase(m_dbPtr);
    ui->PageRegister->SetDatabase(m_dbPtr);

    connect(ui->StartPage, &StartWindowForm::SignInRequest, this, &StartWindow::SetLoginForm);
    connect(ui->StartPage, &StartWindowForm::SignUpRequest, this, &StartWindow::SetRegistrationForm);

    connect(ui->PageLogin, &LoginWidget::registrationRequested, this, &StartWindow::SetRegistrationForm);
    connect(ui->PageLogin, &LoginWidget::accepted, this, &StartWindow::OnLoggedIn);
    connect(ui->PageLogin, &LoginWidget::rejected, this, &StartWindow::OnRejectedRequest);

    connect(ui->PageRegister, &RegisterForm::loginRequested, this, &StartWindow::SetLoginForm);
    connect(ui->PageRegister, &RegisterForm::accepted, this, &StartWindow::OnLoggedIn);
    connect(ui->PageRegister, &RegisterForm::rejected, this, &StartWindow::OnRejectedRequest);
}

StartWindow::~StartWindow()
{
    delete ui;
}

void StartWindow::SetLoginForm()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void StartWindow::SetRegistrationForm()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void StartWindow::SetHelloForm()
{
    ui->stackedWidget->setCurrentIndex(2);
}


int StartWindow::Getm_UserId(){
    return m_UserId;
}

void StartWindow::OnLoggedIn(int userID, QString username){
    m_UserId = userID;
    m_userName = username;
    accept();
}

void StartWindow::OnRejectedRequest(){
    reject();
}

std::shared_ptr<Database> StartWindow::GetDatabase(){
    return m_dbPtr;
}

QString StartWindow::GetUsername(){
    return m_userName;
}
