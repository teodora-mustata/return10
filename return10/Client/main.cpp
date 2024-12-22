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
#include "LoginRegisterManager.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    LoginRegisterManager loginRegisterWindow;
    loginRegisterWindow.setWindowTitle("Login");
    loginRegisterWindow.resize(400, 300);
    loginRegisterWindow.show();

    return app.exec();
}
