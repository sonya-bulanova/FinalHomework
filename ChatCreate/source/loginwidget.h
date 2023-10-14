#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include <QString>
#include "database.h"
#include <memory>

namespace Ui {
class LoginWidget;
}

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();
    void SetDatabase(std::shared_ptr<Database> dbPtr);

signals:
    void registrationRequested();
    void accepted(int userID, QString Username);
    void rejected();

private slots:
    void on_buttonBox_rejected();
    void on_buttonBox_accepted();
    void on_RegisterButton_clicked();

private:
    Ui::LoginWidget *ui;
    std::shared_ptr<Database> m_dbPtr;
};

#endif // LOGINWIDGET_H
