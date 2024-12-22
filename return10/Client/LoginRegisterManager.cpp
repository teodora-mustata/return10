#include "LoginRegisterManager.h"
#include <QVBoxLayout>

LoginRegisterManager::LoginRegisterManager(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this);
    stackedWidget = new QStackedWidget(this);

    loginWidget = new LoginWidget(this);
    registerWidget = new RegisterWidget(this);

    stackedWidget->addWidget(loginWidget);
    stackedWidget->addWidget(registerWidget);

    layout->addWidget(stackedWidget);

    connect(loginWidget, &LoginWidget::switchToRegister, this, &LoginRegisterManager::showRegister);
    connect(registerWidget, &RegisterWidget::switchToLogin, this, &LoginRegisterManager::showLogin);
}

void LoginRegisterManager::showLogin() {
    stackedWidget->setCurrentWidget(loginWidget);
}

void LoginRegisterManager::showRegister() {
    stackedWidget->setCurrentWidget(registerWidget);
}
