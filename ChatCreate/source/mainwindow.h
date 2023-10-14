#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include <memory>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int userID, QString username, std::shared_ptr<Database> dbPtr = nullptr, QWidget *parent = nullptr);
    ~MainWindow();
    static MainWindow * CreateClient(std::shared_ptr<Database> dbPtr = nullptr);
    static int kInstanceCount;

private slots:
    void on_MessageLineEdit_returnPressed();
    void on_actionClose_this_client_triggered();
    void on_actionOpen_another_client_triggered();
    void on_SendAllMessage_clicked();
    void on_SendPrivateMessage_clicked();
    void UpdateChat();

private:
    Ui::MainWindow *ui;
    std::shared_ptr<Database> m_dbPtr;
    int m_userID;
    QString m_username;
};

#endif // MAINWINDOW_H
