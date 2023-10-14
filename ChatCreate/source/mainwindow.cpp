#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "startwindow.h"
#include <QDialog>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QTimer>

int MainWindow::kInstanceCount = 0;

MainWindow::MainWindow(int userID, QString username, std::shared_ptr<Database> dbPtr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_userID(userID),
    m_username(username)
{
    ui->setupUi(this);
    kInstanceCount++;
    if (dbPtr){
        m_dbPtr = dbPtr;
    } else {
        m_dbPtr = std::make_shared<Database>();
    }
    auto timer = new QTimer();
    connect(timer, &QTimer::timeout, this, &MainWindow::UpdateChat);
    timer->start(500);
}

MainWindow::~MainWindow()
{
    delete ui;
    kInstanceCount--;
    if (kInstanceCount <= 0){
        qApp->exit();
    }
}

MainWindow *MainWindow::CreateClient(std::shared_ptr<Database> dbPtr)
{
    StartWindow wind(dbPtr);
    auto result = wind.exec();
    if (result == QDialog::Rejected){
        return nullptr;
    } else {
        auto w = new MainWindow(wind.Getm_UserId(), wind.GetUsername(), wind.GetDatabase());
        w->setAttribute(Qt::WA_DeleteOnClose);
        return w;
    }

}

void MainWindow::on_MessageLineEdit_returnPressed()
{
    on_SendAllMessage_clicked();
}

void MainWindow::on_SendAllMessage_clicked()
{
    m_dbPtr->addChatMessage(m_username.toStdString(), ui->MessageLineEdit->text().toStdString());
}

void MainWindow::on_SendPrivateMessage_clicked()
{
    QDialog dialog(this);
    dialog.setModal(true);
    auto lay = new QVBoxLayout();
    dialog.setLayout(lay);
    auto userListWigt = new QListWidget(&dialog);
    lay->addWidget(userListWigt);
    auto buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);
    lay->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

    auto userList = m_dbPtr->getUserList();
    for (auto user : userList){
        userListWigt->addItem(QString::fromStdString(user));
    }
    userListWigt -> setCurrentRow(0);
    auto result = dialog.exec();

    if(result == QDialog::Accepted && userListWigt->currentItem()){
        m_dbPtr->addPrivateMessage(m_username.toStdString(), userListWigt->currentItem()->text().toStdString(), ui->MessageLineEdit->text().toStdString());
    }

}

void MainWindow::on_actionOpen_another_client_triggered()
{
    auto w = CreateClient(m_dbPtr);
    if(w){
        w->show();
    }
}

void MainWindow::on_actionClose_this_client_triggered()
{
    this->close();
}

void MainWindow::UpdateChat(){
    auto chatMessages = m_dbPtr->getChatMessages();
    QString Chat;
    for(const auto &msg : chatMessages){
        Chat.append(QString::fromStdString(msg) + "\n");
    }
    if(ui->CommonChatBrows->toPlainText() != Chat){
        ui->CommonChatBrows->setText(Chat);
    }

    Chat.clear();

    auto privateMessages = m_dbPtr->getPrivateMessage();
    for(const auto &msg : privateMessages){
        if(QString::fromStdString(msg.getSender()) != m_username && msg.getDestination() != m_userID){
            continue;
        } else {
            QString prefix;
            if(m_username == QString::fromStdString(msg.getSender()) && m_userID == msg.getDestination()){
                prefix = tr("Self message") + ": ";
            } else if(m_username == QString::fromStdString(msg.getSender())){
                prefix = tr("Message to") + QString(": ").arg(QString::fromStdString(m_dbPtr->getUserName(msg.getDestination())));
            } else{
                prefix = QString::fromStdString(msg.getSender()) + ": ";
            }
            Chat.append(prefix + QString::fromStdString(msg.getText()) + "\n");
        }
        if(ui->PrivateChatBrows->toPlainText() != Chat){
            ui->PrivateChatBrows->setText(Chat);
        }
    }
}
