#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QMessageBox>
#include <regex>

class Login : public QWidget {
    Q_OBJECT

public:
    explicit Login(QWidget* parent = nullptr);
    ~Login();

private slots:
    void onLoginClicked(); // Slot pentru butonul de login

private:
    QLineEdit* usernameInput;
    QLineEdit* passwordInput;
    QPushButton* loginButton;

    bool handleLogin(const std::string& username, const std::string& password);
    bool passwordValidation(const std::string& password);
    void showErrorMessage(const QString& message);
};
