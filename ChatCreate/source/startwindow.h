#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include <QString>
#include <QWidget>
#include <memory>
#include "database.h"

namespace Ui {
class StartWindow;
}

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    explicit StartWindow(std::shared_ptr<Database>dbPtr = nullptr, QWidget *parent = nullptr);
    ~StartWindow();

    void SetLoginForm();
    void SetRegistrationForm();
    int Getm_UserId();
    std::shared_ptr<Database> GetDatabase();
    QString GetUsername();

public slots:
    void OnLoggedIn(int userID, QString username);
    void OnRejectedRequest();

private:
    Ui::StartWindow *ui;
    int m_UserId;
    QString m_userName;
    std::shared_ptr<Database> m_dbPtr;
};

#endif // STARTWINDOW_H
