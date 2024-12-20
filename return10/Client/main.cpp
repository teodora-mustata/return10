//#include "Client.h"
//#include <QtWidgets/QApplication>
//
//int main(int argc, char *argv[])
//{
//    QApplication a(argc, argv);
//    Client w;
//    w.show();
//    return a.exec();
//}
#include <QApplication>
#include "login.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    Login loginWindow;
    loginWindow.setWindowTitle("Login");
    loginWindow.resize(400, 300);
    loginWindow.show();

    return app.exec();
}
