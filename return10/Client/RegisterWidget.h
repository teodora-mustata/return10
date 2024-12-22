#pragma once
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class RegisterWidget : public QWidget {
    Q_OBJECT
public:
    explicit RegisterWidget(QWidget* parent = nullptr);
signals:
    void registerSuccessful();
    void switchToLogin();
private slots:
    void handleRegister();
private:
    QLineEdit* usernameEdit;
    QLineEdit* passwordEdit;
    QLineEdit* confirmPasswordEdit;
    QPushButton* registerButton;
    QPushButton* loginButton;
};
