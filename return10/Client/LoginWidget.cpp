#include "LoginWidget.h"
#include "MainMenuWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <cpr/cpr.h>
#include <crow/json.h>
#include "UserSession.h"  // Pentru a seta userId, dac? e necesar

LoginWidget::LoginWidget(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);

    // Username
    QLabel* usernameLabel = new QLabel("Username:", this);
    usernameEdit = new QLineEdit(this);
    layout->addWidget(usernameLabel);
    layout->addWidget(usernameEdit);

    // Password
    QLabel* passwordLabel = new QLabel("Password:", this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordEdit);

    // Login Button
    loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton);

    // Register Button
    registerButton = new QPushButton("Register", this);
    layout->addWidget(registerButton);

    connect(loginButton, &QPushButton::clicked, this, &LoginWidget::handleLogin);
    connect(registerButton, &QPushButton::clicked, this, &LoginWidget::switchToRegister);
}

void LoginWidget::handleLogin() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Failed", "Please fill in all fields.");
        return;
    }

    // Creeaz? un obiect JSON pentru request
    crow::json::wvalue jsonData;
    jsonData["username"] = username.toStdString();
    jsonData["password"] = password.toStdString();

    // Trimite un POST request c?tre server
    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/login" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ jsonData.dump() }
    );

    // Verific? r?spunsul serverului
    if (response.status_code == 200) {
        auto responseJson = crow::json::load(response.text);

        if (responseJson.has("userId")) {
            int userId = responseJson["userId"].i();
            UserSession::getInstance().setUserId(userId);  // Seteaz? userId în sesiune
        }

    /*    QMessageBox::information(this, "Login Successful", "Welcome back!");
        emit loginSuccessful();*/


        // Afi?eaz? mesaj de succes
        QMessageBox::information(this, "Login Successful", "Welcome back!");

        // Creeaz? ?i afi?eaz? fereastra MainMenu
        MainMenuWidget* mainMenu = new MainMenuWidget();  // Creeaz? instan?a MainMenu
        mainMenu->show();  // Afi?eaz? fereastra

        // Închide fereastra de login
        this->close();  // Închide fereastra de login

    }
    else if (response.status_code == 401) {
        QMessageBox::critical(this, "Login Failed", "Invalid username or password.");
    }
    else {
        QMessageBox::critical(this, "Login Failed", "Server error. Please try again later.");
    }
}
