#include "RegisterWidget.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <regex>
#include <cpr/cpr.h>
#include <crow/json.h>

RegisterWidget::RegisterWidget(QWidget* parent) : QWidget(parent) {
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

    // Confirm Password
    QLabel* confirmPasswordLabel = new QLabel("Confirm Password:", this);
    confirmPasswordEdit = new QLineEdit(this);
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);
    layout->addWidget(confirmPasswordLabel);
    layout->addWidget(confirmPasswordEdit);

    // Register Button
    registerButton = new QPushButton("Register", this);
    layout->addWidget(registerButton);

    // Login Button
    loginButton = new QPushButton("Back to Login", this);
    layout->addWidget(loginButton);

    connect(registerButton, &QPushButton::clicked, this, &RegisterWidget::handleRegister);
    connect(loginButton, &QPushButton::clicked, this, &RegisterWidget::switchToLogin);
}
//
//bool RegisterWidget::validatePassword(const QString& password) {
//    std::regex passwordRegex(R"(^(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&*]).{8,}$)");
//    return std::regex_match(password.toStdString(), passwordRegex);
//}

void RegisterWidget::handleRegister() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();
    QString confirmPassword = confirmPasswordEdit->text();

    if (username.isEmpty() || password.isEmpty() || confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Registration Failed", "Please fill in all fields.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::critical(this, "Registration Failed", "Passwords do not match.");
        return;
    }

    //if (!validatePassword(password)) {
    //    QMessageBox::critical(this, "Registration Failed",
    //        "Password is not strong enough! It must contain an uppercase letter, a number, a special character, and be at least 8 characters long.");
    //    return;
    //}

    // Creeaz? un obiect JSON pentru request
    crow::json::wvalue jsonData;
    jsonData["username"] = username.toStdString();
    jsonData["password"] = password.toStdString();

    // Trimite un POST request c?tre server
    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/signup" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ jsonData.dump() }
    );

    // Verific? r?spunsul serverului
    if (response.status_code == 201) {
        QMessageBox::information(this, "Registration Successful", "Account created successfully!");
        emit registerSuccessful();
    }
    else if (response.status_code == 409) {
        QMessageBox::critical(this, "Registration Failed", "Username already exists. Please choose another.");
    }
    else {
        QMessageBox::critical(this, "Registration Failed", "Server error. Please try again later.");
    }
}
