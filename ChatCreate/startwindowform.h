#ifndef STARTWINDOWFORM_H
#define STARTWINDOWFORM_H

#include <QWidget>

namespace Ui {
class StartWindowForm;
}

class StartWindowForm : public QWidget
{
    Q_OBJECT

public:
    explicit StartWindowForm(QWidget *parent = nullptr);
    ~StartWindowForm();

public slots:
    void on_SignInButton_clicked();
    void on_SignUpButton_clicked();

signals:
    void SignInRequest();
    void SignUpRequest();

private:
    Ui::StartWindowForm *ui;
};

#endif // STARTWINDOWFORM_H
