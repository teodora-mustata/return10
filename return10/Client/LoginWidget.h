#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

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
