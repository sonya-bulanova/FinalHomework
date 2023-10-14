#ifndef REGISTERFORM_H
#define REGISTERFORM_H

#include <QWidget>
#include <memory>
#include "database.h"

namespace Ui {
class RegisterForm;
}

class RegisterForm : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterForm(QWidget *parent = nullptr);
    ~RegisterForm();
    void SetDatabase(std::shared_ptr<Database> dbPtr);

signals:
    void loginRequested();
    void accepted(int userID, QString Username);
    void rejected();

private slots:
    void on_pushButton_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::RegisterForm *ui;
    std::shared_ptr<Database> m_dbPtr;
};

#endif // REGISTERFORM_H
