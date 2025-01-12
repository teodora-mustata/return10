#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include<crow/json.h>
#include<cpr/cpr.h>
#include<qlabel.h>
#include<qmessagebox.h>
#include<QVBoxLayout>
#include"UserSession.h"

#include"MainMenuWidget.h"

class LoginWidget : public QWidget {
    Q_OBJECT
public:
    explicit LoginWidget(QWidget* parent = nullptr);
signals:
    //Cred ca se creaza automat
    void loginSuccessful();
    void switchToRegister();
private slots:
    void handleLogin();
private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QPushButton* loginButton;
    QPushButton* registerButton;
};
