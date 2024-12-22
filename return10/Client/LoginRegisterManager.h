#pragma once
#include <QWidget>
#include <QStackedWidget>
#include "LoginWidget.h"
#include "RegisterWidget.h"

class LoginRegisterManager : public QWidget {
    Q_OBJECT
public:
    explicit LoginRegisterManager(QWidget* parent = nullptr);
private slots:
    void showLogin();
    void showRegister();
private:
    QStackedWidget* stackedWidget;
    LoginWidget* loginWidget;
    RegisterWidget* registerWidget;
};
