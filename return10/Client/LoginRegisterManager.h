#pragma once
#include <QWidget>
//Este un widget care permite afisarea unui singur
//widget dintr - o lista de widgeturi.Este util cand vrei sa afisezi mai multe widgeturi si sa comuti �ntre ele.
#include <QStackedWidget>
#include "LoginWidget.h"
#include "RegisterWidget.h"

class LoginRegisterManager : public QWidget {
    Q_OBJECT
public:
    explicit LoginRegisterManager(QWidget* parent = nullptr);
    /*Sectiunea de "slots" definesc functiile care pot fi apelate atunci
        c�nd semnalele sunt emise(un concept �n Qt pentru a conecta evenimentele �ntre obiecte).*/
private slots:
    void showLogin();
    void showRegister();
private:
    QStackedWidget* stackedWidget;
    LoginWidget* loginWidget;
    RegisterWidget* registerWidget;
};
