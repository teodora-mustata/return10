#include "login.h"
#include <QVBoxLayout>
#include <QLabel>
#include <cpr/cpr.h>
#include <crow.h>

Login::Login(QWidget* parent)
    : QWidget(parent),
    usernameInput(new QLineEdit(this)),
    passwordInput(new QLineEdit(this)),
    loginButton(new QPushButton("Login", this)) {

    // Configurare UI
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* usernameLabel = new QLabel("Username:", this);
    QLabel* passwordLabel = new QLabel("Password:", this);

    passwordInput->setEchoMode(QLineEdit::Password); // Ascunde textul pentru parola

    layout->addWidget(usernameLabel);
    layout->addWidget(usernameInput);
    layout->addWidget(passwordLabel);
    layout->addWidget(passwordInput);
    layout->addWidget(loginButton);

    setLayout(layout);

    // Conecteaz? butonul de login la metoda de tratare
    connect(loginButton, &QPushButton::clicked, this, &Login::onLoginClicked);
}

Login::~Login() {}

void Login::onLoginClicked() {
    QString username = usernameInput->text();
    QString password = passwordInput->text();

    if (username.isEmpty() || password.isEmpty()) {
        showErrorMessage("Username or password cannot be empty.");
        return;
    }

    if (!passwordValidation(password.toStdString())) {
        showErrorMessage("Password must contain at least one uppercase letter, one number, one special character, and be at least 8 characters long.");
        return;
    }

    if (handleLogin(username.toStdString(), password.toStdString())) {
        QMessageBox::information(this, "Success", "Login successful!");
    }
    else {
        showErrorMessage("Invalid username or password.");
    }
}

bool Login::passwordValidation(const std::string& password) {
    std::regex passwordRegex(R"(^(?=.*[A-Z])(?=.*[0-9])(?=.*[!@#$%^&*]).{8,}$)");
    return std::regex_match(password, passwordRegex);
}

bool Login::handleLogin(const std::string& username, const std::string& password) {
    crow::json::wvalue jsonData;
    jsonData["username"] = username;
    jsonData["password"] = password;

    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/login" },
        cpr::Header{ {"Content-Type", "application/json"} },
        cpr::Body{ jsonData.dump() }
    );

    if (response.status_code == 200) {
        auto responseJson = crow::json::load(response.text);

        if (responseJson.has("message")) {
            QString welcomeMessage = QString::fromStdString(responseJson["message"].s());
            QMessageBox::information(this, "Welcome", welcomeMessage);
        }

        return true;
    }
    else if (response.status_code == 401) {
        showErrorMessage("Invalid username or password.");
    }
    else {
        showErrorMessage("Server error. Please try again later.");
    }

    return false;
}

void Login::showErrorMessage(const QString& message) {
    QMessageBox::critical(this, "Error", message);
}

