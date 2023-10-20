#include <QApplication>
#include "mainwindow.h"
#include "loginwidget.h"
#include "registerform.h"
#include "startwindow.h"
int main(int argc, char * argv[]){
    QApplication a(argc, argv);
    auto w = MainWindow::CreateClient();
    if(w){
        w->show();
    } else {
        return 0;
    }
    return a.exec();
}
