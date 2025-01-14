//#include "ShopWidget.h"
//#include <cpr/cpr.h>
//#include <crow/json.h>
//#include "UserSession.h"
//#include <QMessageBox>
//
//ShopWidget::ShopWidget(QWidget* parent)
//    : QWidget(parent) {
//    setupUI();
//}
//
//ShopWidget::~ShopWidget() {
//    // Destructor logic if needed
//}
//
//void ShopWidget::setupUI() {
//    layout = new QVBoxLayout(this);
//
//    titleLabel = new QLabel("==== Shop Menu ====", this);
//    titleLabel->setAlignment(Qt::AlignCenter);
//    layout->addWidget(titleLabel);
//
//    buyReloadSpeedButton = new QPushButton("Buy reload speed upgrade", this);
//    layout->addWidget(buyReloadSpeedButton);
//    connect(buyReloadSpeedButton, &QPushButton::clicked, this, &ShopWidget::on_buyReloadSpeedButton_clicked);
//
//    buyBulletSpeedButton = new QPushButton("Buy bullet speed upgrade", this);
//    layout->addWidget(buyBulletSpeedButton);
//    connect(buyBulletSpeedButton, &QPushButton::clicked, this, &ShopWidget::on_buyBulletSpeedButton_clicked);
//
//    goBackButton = new QPushButton("Go back to home page", this);
//    layout->addWidget(goBackButton);
//    connect(goBackButton, &QPushButton::clicked, this, &ShopWidget::on_goBackButton_clicked);
//}
//
//void ShopWidget::on_buyReloadSpeedButton_clicked() {
//    buyReloadSpeedUpgrade();
//}
//
//void ShopWidget::on_buyBulletSpeedButton_clicked() {
//    buyBulletSpeedUpgrade();
//}
//
//void ShopWidget::on_goBackButton_clicked() {
//    // Navigate back to the home page
//    // This can be implemented according to your application logic
//    QMessageBox::information(this, "Home", "Navigating back to home page...");
//}
//
//void ShopWidget::buyReloadSpeedUpgrade() {
//    int userId = UserSession::getInstance().getUserId();
//
//    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/upgrade/reload_speed/" + std::to_string(userId) });
//
//    if (response.status_code == 200) {
//        auto responseJson = crow::json::load(response.text);
//        QMessageBox::information(this, "Upgrade Successful", QString::fromStdString(responseJson["message"].s()) + "\nRemaining Score: " + QString::number(responseJson["remainingScore"].i()) + "\nNew Reload Speed: " + QString::number(responseJson["newReloadSpeed"].d()));
//    }
//    else if (response.status_code == 400) {
//        auto responseJson = crow::json::load(response.text);
//        if (responseJson.has("error")) {
//            QMessageBox::warning(this, "Error", QString::fromStdString(responseJson["error"].s()));
//        }
//        else {
//            QMessageBox::warning(this, "Error", "Something went wrong. Try again.");
//        }
//    }
//    else if (response.status_code == 404) {
//        QMessageBox::warning(this, "Error", "User or gun not found. Check your user ID.");
//    }
//    else {
//        QMessageBox::warning(this, "Error", "Error performing upgrade. Please try again later.\nServer responded with status code: " + QString::number(response.status_code));
//    }
//}
//
//void ShopWidget::buyBulletSpeedUpgrade() {
//    int userId = UserSession::getInstance().getUserId();
//
//    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/upgrade/bullet_speed/" + std::to_string(userId) });
//
//    if (response.status_code == 200) {
//        auto responseJson = crow::json::load(response.text);
//        QMessageBox::information(this, "Bullet Speed Upgrade Successful", QString::fromStdString(responseJson["message"].s()) + "\nNew Bullet Speed: " + QString::number(responseJson["newBulletSpeed"].d()) + "\nRemaining Crowns: " + QString::number(responseJson["remainingCrowns"].i()));
//    }
//    else if (response.status_code == 400) {
//        auto responseJson = crow::json::load(response.text);
//        if (responseJson.has("error")) {
//            QMessageBox::warning(this, "Error", QString::fromStdString(responseJson["error"].s()));
//        }
//        else {
//            QMessageBox::warning(this, "Error", "Something went wrong. Try again.");
//        }
//    }
//    else if (response.status_code == 404) {
//        QMessageBox::warning(this, "Error", "User or gun not found. Check your user ID.");
//    }
//    else {
//        QMessageBox::warning(this, "Error", "Error performing upgrade. Please try again later.\nServer responded with status code: " + QString::number(response.status_code));
//    }
//}
//
//#include "ShopWidget.h"
//#include <cpr/cpr.h>
//#include <crow/json.h>
//#include "UserSession.h"
//#include <QMessageBox>
//
//ShopWidget::ShopWidget(QWidget* parent, MainMenuWidget* mainMenu)
//    : QWidget(parent), mainMenuWidget(mainMenu) {
//    setupUI();
//}
//
//ShopWidget::~ShopWidget() {
//    // Destructor logic if needed
//}
//
//void ShopWidget::setupUI() {
//    layout = new QVBoxLayout(this);
//
//    titleLabel = new QLabel("==== Shop Menu ====", this);
//    titleLabel->setAlignment(Qt::AlignCenter);
//    layout->addWidget(titleLabel);
//
//    buyReloadSpeedButton = new QPushButton("Buy reload speed upgrade", this);
//    layout->addWidget(buyReloadSpeedButton);
//    connect(buyReloadSpeedButton, &QPushButton::clicked, this, &ShopWidget::on_buyReloadSpeedButton_clicked);
//
//    buyBulletSpeedButton = new QPushButton("Buy bullet speed upgrade", this);
//    layout->addWidget(buyBulletSpeedButton);
//    connect(buyBulletSpeedButton, &QPushButton::clicked, this, &ShopWidget::on_buyBulletSpeedButton_clicked);
//
//    goBackButton = new QPushButton("Go back to home page", this);
//    layout->addWidget(goBackButton);
//    connect(goBackButton, &QPushButton::clicked, this, &ShopWidget::on_goBackButton_clicked);
//}
//
//void ShopWidget::on_buyReloadSpeedButton_clicked() {
//    buyReloadSpeedUpgrade();
//}
//
//void ShopWidget::on_buyBulletSpeedButton_clicked() {
//    buyBulletSpeedUpgrade();
//}
//
//void ShopWidget::on_goBackButton_clicked() {
//    if(mainMenuWidget) {
//        mainMenuWidget->show();
//        this->close();
//    } else {
//        QMessageBox::information(this, "Home", "Main menu is not available.");
//    }
//}
//
//void ShopWidget::buyReloadSpeedUpgrade() {
//    int userId = UserSession::getInstance().getUserId();
//
//    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/upgrade/reload_speed/" + std::to_string(userId) });
//
//    if (response.status_code == 200) {
//        auto responseJson = crow::json::load(response.text);
//        QMessageBox::information(this, "Upgrade Successful", QString::fromStdString(responseJson["message"].s()) + "\nRemaining Score: " + QString::number(responseJson["remainingScore"].i()) + "\nNew Reload Speed: " + QString::number(responseJson["newReloadSpeed"].d()));
//    } else if (response.status_code == 400) {
//        auto responseJson = crow::json::load(response.text);
//        if (responseJson.has("error")) {
//            QMessageBox::warning(this, "Error", QString::fromStdString(responseJson["error"].s()));
//        } else {
//            QMessageBox::warning(this, "Error", "Something went wrong. Try again.");
//        }
//    } else if (response.status_code == 404) {
//        QMessageBox::warning(this, "Error", "User or gun not found. Check your user ID.");
//    } else {
//        QMessageBox::warning(this, "Error", "Error performing upgrade. Please try again later.\nServer responded with status code: " + QString::number(response.status_code));
//    }
//}
//
//void ShopWidget::buyBulletSpeedUpgrade() {
//    int userId = UserSession::getInstance().getUserId();
//
//    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/upgrade/bullet_speed/" + std::to_string(userId) });
//
//    if (response.status_code == 200) {
//        auto responseJson = crow::json::load(response.text);
//        QMessageBox::information(this, "Bullet Speed Upgrade Successful", QString::fromStdString(responseJson["message"].s()) + "\nNew Bullet Speed: " + QString::number(responseJson["newBulletSpeed"].d()) + "\nRemaining Crowns: " + QString::number(responseJson["remainingCrowns"].i()));
//    } else if (response.status_code == 400) {
//        auto responseJson = crow::json::load(response.text);
//        if (responseJson.has("error")) {
//            QMessageBox::warning(this, "Error", QString::fromStdString(responseJson["error"].s()));
//        } else {
//            QMessageBox::warning(this, "Error", "Something went wrong. Try again.");
//        }
//    } else if (response.status_code == 404) {
//        QMessageBox::warning(this, "Error", "User or gun not found. Check your user ID.");
//    } else {
//        QMessageBox::warning(this, "Error", "Error performing upgrade. Please try again later.\nServer responded with status code: " + QString::number(response.status_code));
//    }
//}

//
//#include "ShopWidget.h"
//#include <cpr/cpr.h>
//#include <crow/json.h>
//#include "UserSession.h"
//#include <QMessageBox>
//
//ShopWidget::ShopWidget(QWidget* parent, MainMenuWidget* mainMenu)
//    : QWidget(parent), mainMenuWidget(mainMenu) {
//    setupUI();
//}
//
//ShopWidget::~ShopWidget() {
//    // Destructor logic if needed
//}
//
//void ShopWidget::setupUI() {
//    layout = new QVBoxLayout(this);
//
//    titleLabel = new QLabel("==== Shop Menu ====", this);
//    titleLabel->setAlignment(Qt::AlignCenter);
//    layout->addWidget(titleLabel);
//
//    buyReloadSpeedButton = new QPushButton("Buy reload speed upgrade", this);
//    layout->addWidget(buyReloadSpeedButton);
//    connect(buyReloadSpeedButton, &QPushButton::clicked, this, &ShopWidget::on_buyReloadSpeedButton_clicked);
//
//    buyBulletSpeedButton = new QPushButton("Buy bullet speed upgrade", this);
//    layout->addWidget(buyBulletSpeedButton);
//    connect(buyBulletSpeedButton, &QPushButton::clicked, this, &ShopWidget::on_buyBulletSpeedButton_clicked);
//
//    goBackButton = new QPushButton("Go back to home page", this);
//    layout->addWidget(goBackButton);
//    connect(goBackButton, &QPushButton::clicked, this, &ShopWidget::on_goBackButton_clicked);
//}
//
//void ShopWidget::on_buyReloadSpeedButton_clicked() {
//    buyReloadSpeedUpgrade();
//}
//
//void ShopWidget::on_buyBulletSpeedButton_clicked() {
//    buyBulletSpeedUpgrade();
//}
//
//void ShopWidget::on_goBackButton_clicked() {
//    if (mainMenuWidget) {
//        mainMenuWidget->show();
//        this->close();
//    }
//    else {
//        QMessageBox::information(this, "Home", "Main menu is not available.");
//    }
//}
//
//void ShopWidget::buyReloadSpeedUpgrade() {
//    int userId = UserSession::getInstance().getUserId();
//
//    auto response = cpr::Post(cpr::Url{
//        "http://localhost:18080/upgrade/reload_speed/" + std::to_string(userId)
//        });
//
//    if (response.status_code == 200) {
//        auto responseJson = crow::json::load(response.text);
//        QMessageBox::information(this, "Upgrade Successful",
//            QString::fromStdString(responseJson["message"].s()) + "\nRemaining Score: " +
//            QString::number(responseJson["remainingScore"].i()) + "\nNew Reload Speed: " +
//            QString::number(responseJson["newReloadSpeed"].d()));
//    }
//    else if (response.status_code == 400) {
//        auto responseJson = crow::json::load(response.text);
//        if (responseJson.has("error")) {
//            QMessageBox::warning(this, "Error",
//                QString::fromStdString(responseJson["error"].s()));
//        }
//        else {
//            QMessageBox::warning(this, "Error",
//                "Something went wrong. Try again.");
//        }
//    }
//    else if (response.status_code == 404) {
//        QMessageBox::warning(this, "Error",
//            "User or gun not found. Check your user ID.");
//    }
//    else {
//        QMessageBox::warning(this, "Error",
//            "Error performing upgrade. Please try again later.\nServer responded with status code: " +
//            QString::number(response.status_code));
//    }
//}
//
//void ShopWidget::buyBulletSpeedUpgrade() {
//    int userId = UserSession::getInstance().getUserId();
//
//    auto response = cpr::Post(cpr::Url{
//        "http://localhost:18080/upgrade/bullet_speed/" + std::to_string(userId)
//        });
//
//    if (response.status_code == 200) {
//        auto responseJson = crow::json::load(response.text);
//        QMessageBox::information(this, "Bullet Speed Upgrade Successful",
//            QString::fromStdString(responseJson["message"].s()) + "\nNew Bullet Speed: " +
//            QString::number(responseJson["newBulletSpeed"].d()) + "\nRemaining Crowns: " +
//            QString::number(responseJson["remainingCrowns"].i()));
//    }
//    else if (response.status_code == 400) {
//        auto responseJson = crow::json::load(response.text);
//        if (responseJson.has("error")) {
//            QMessageBox::warning(this, "Error",
//                QString::fromStdString(responseJson["error"].s()));
//        }
//        else {
//            QMessageBox::warning(this, "Error",
//                "Something went wrong. Try again.");
//        }
//    }
//    else if (response.status_code == 404) {
//        QMessageBox::warning(this, "Error",
//            "User or gun not found. Check your user ID.");
//    }
//    else {
//        QMessageBox::warning(this, "Error",
//            "Error performing upgrade. Please try again later.\nServer responded with status code: " +
//            QString::number(response.status_code));
//    }
//}
//
//#include "ShopWidget.h"
//#include <cpr/cpr.h>
//#include <crow/json.h>
//#include "UserSession.h"
//#include <QMessageBox>
//
//ShopWidget::ShopWidget(QWidget* parent, MainMenuWidget* mainMenu)
//    : QWidget(parent), mainMenuWidget(mainMenu) {
//    setupUI();
//}
//
//ShopWidget::~ShopWidget() {
//    // Destructor logic if needed
//}
//
//void ShopWidget::setupUI() {
//    layout = new QVBoxLayout(this);
//
//    titleLabel = new QLabel("==== Shop Menu ====", this);
//    titleLabel->setAlignment(Qt::AlignCenter);
//    layout->addWidget(titleLabel);
//
//    buyReloadSpeedButton = new QPushButton("Buy reload speed upgrade", this);
//    layout->addWidget(buyReloadSpeedButton);
//    connect(buyReloadSpeedButton, &QPushButton::clicked, this, &ShopWidget::on_buyReloadSpeedButton_clicked);
//
//    buyBulletSpeedButton = new QPushButton("Buy bullet speed upgrade", this);
//    layout->addWidget(buyBulletSpeedButton);
//    connect(buyBulletSpeedButton, &QPushButton::clicked, this, &ShopWidget::on_buyBulletSpeedButton_clicked);
//
//    goBackButton = new QPushButton("Go back to home page", this);
//    layout->addWidget(goBackButton);
//    connect(goBackButton, &QPushButton::clicked, this, &ShopWidget::on_goBackButton_clicked);
//}
//
//void ShopWidget::on_buyReloadSpeedButton_clicked() {
//    buyReloadSpeedUpgrade();
//}
//
//void ShopWidget::on_buyBulletSpeedButton_clicked() {
//    buyBulletSpeedUpgrade();
//}
//
//void ShopWidget::on_goBackButton_clicked() {
//    if (mainMenuWidget) {
//        mainMenuWidget->stackedWidget->setCurrentWidget(mainMenuWidget);
//    }
//    else {
//        QMessageBox::information(this, "Home", "Main menu is not available.");
//    }
//}
//
//void ShopWidget::buyReloadSpeedUpgrade() {
//    int userId = UserSession::getInstance().getUserId();
//
//    auto response = cpr::Post(cpr::Url{
//        "http://localhost:18080/upgrade/reload_speed/" + std::to_string(userId)
//        });
//
//    if (response.status_code == 200) {
//        auto responseJson = crow::json::load(response.text);
//        QMessageBox::information(this, "Upgrade Successful",
//            QString::fromStdString(responseJson["message"].s()) + "\nRemaining Score: " +
//            QString::number(responseJson["remainingScore"].i()) + "\nNew Reload Speed: " +
//            QString::number(responseJson["newReloadSpeed"].d()));
//    }
//    else if (response.status_code == 400) {
//        auto responseJson = crow::json::load(response.text);
//        if (responseJson.has("error")) {
//            QMessageBox::warning(this, "Error",
//                QString::fromStdString(responseJson["error"].s()));
//        }
//        else {
//            QMessageBox::warning(this, "Error",
//                "Something went wrong. Try again.");
//        }
//    }
//    else if (response.status_code == 404) {
//        QMessageBox::warning(this, "Error",
//            "User or gun not found. Check your user ID.");
//    }
//    else {
//        QMessageBox::warning(this, "Error",
//            "Error performing upgrade. Please try again later.\nServer responded with status code: " +
//            QString::number(response.status_code));
//    }
//}
//
//void ShopWidget::buyBulletSpeedUpgrade() {
//    int userId = UserSession::getInstance().getUserId();
//
//    auto response = cpr::Post(cpr::Url{
//        "http://localhost:18080/upgrade/bullet_speed/" + std::to_string(userId)
//        });
//
//    if (response.status_code == 200) {
//        auto responseJson = crow::json::load(response.text);
//        QMessageBox::information(this, "Bullet Speed Upgrade Successful",
//            QString::fromStdString(responseJson["message"].s()) + "\nNew Bullet Speed: " +
//            QString::number(responseJson["newBulletSpeed"].d()) + "\nRemaining Crowns: " +
//            QString::number(responseJson["remainingCrowns"].i()));
//    }
//    else if (response.status_code == 400) {
//        auto responseJson = crow::json::load(response.text);
//        if (responseJson.has("error")) {
//            QMessageBox::warning(this, "Error",
//                QString::fromStdString(responseJson["error"].s()));
//        }
//        else {
//            QMessageBox::warning(this, "Error",
//                "Something went wrong. Try again.");
//        }
//    }
//    else if (response.status_code == 404) {
//        QMessageBox::warning(this, "Error",
//            "User or gun not found. Check your user ID.");
//    }
//    else {
//        QMessageBox::warning(this, "Error",
//            "Error performing upgrade. Please try again later.\nServer responded with status code: " +
//            QString::number(response.status_code));
//    }
//}

//
//#include "ShopWidget.h"
//#include <QMessageBox>
//
//ShopWidget::ShopWidget(QWidget* parent, MainMenuWidget* mainMenu)
//    : QWidget(parent), mainMenuWidget(mainMenu) {
//    setupUI();
//}
//
//ShopWidget::~ShopWidget() {
//    // Destructor logic if needed
//}
//
//void ShopWidget::setupUI() {
//    layout = new QVBoxLayout(this);
//
//    titleLabel = new QLabel("==== Shop Menu ====", this);
//    titleLabel->setAlignment(Qt::AlignCenter);
//    layout->addWidget(titleLabel);
//
//    buyReloadSpeedButton = new QPushButton("Buy reload speed upgrade", this);
//    layout->addWidget(buyReloadSpeedButton);
//    connect(buyReloadSpeedButton, &QPushButton::clicked, this, &ShopWidget::on_buyReloadSpeedButton_clicked);
//
//    buyBulletSpeedButton = new QPushButton("Buy bullet speed upgrade", this);
//    layout->addWidget(buyBulletSpeedButton);
//    connect(buyBulletSpeedButton, &QPushButton::clicked, this, &ShopWidget::on_buyBulletSpeedButton_clicked);
//
//    goBackButton = new QPushButton("Go back to home page", this);
//    layout->addWidget(goBackButton);
//    connect(goBackButton, &QPushButton::clicked, this, &ShopWidget::on_goBackButton_clicked);
//}
//
//void ShopWidget::on_buyReloadSpeedButton_clicked() {
//    buyReloadSpeedUpgrade();
//}
//
//void ShopWidget::on_buyBulletSpeedButton_clicked() {
//    buyBulletSpeedUpgrade();
//}
//
//void ShopWidget::on_goBackButton_clicked() {
//    if (mainMenuWidget) {
//        mainMenuWidget->stackedWidget->setCurrentWidget(mainMenuWidget);
//    }
//    else {
//        QMessageBox::information(this, "Home", "Main menu is not available.");
//    }
//}
//
//void ShopWidget::buyReloadSpeedUpgrade() {
//    int userId = UserSession::getInstance().getUserId();
//
//    auto response = cpr::Post(cpr::Url{
//        "http://localhost:18080/upgrade/reload_speed/" + std::to_string(userId)
//        });
//
//    if (response.status_code == 200) {
//        auto responseJson = crow::json::load(response.text);
//        QMessageBox::information(this, "Upgrade Successful",
//            QString::fromStdString(responseJson["message"].s()) + "\nRemaining Score: " +
//            QString::number(responseJson["remainingScore"].i()) + "\nNew Reload Speed: " +
//            QString::number(responseJson["newReloadSpeed"].d()));
//    }
//    else if (response.status_code == 400) {
//        auto responseJson = crow::json::load(response.text);
//        if (responseJson.has("error")) {
//            QMessageBox::warning(this, "Error",
//                QString::fromStdString(responseJson["error"].s()));
//        }
//        else {
//            QMessageBox::warning(this, "Error",
//                "Something went wrong. Try again.");
//        }
//    }
//    else if (response.status_code == 404) {
//        QMessageBox::warning(this, "Error",
//            "User or gun not found. Check your user ID.");
//    }
//    else {
//        QMessageBox::warning(this, "Error",
//            "Error performing upgrade. Please try again later.\nServer responded with status code: " +
//            QString::number(response.status_code));
//    }
//}
//
//void ShopWidget::buyBulletSpeedUpgrade() {
//    int userId = UserSession::getInstance().getUserId();
//
//    auto response = cpr::Post(cpr::Url{
//        "http://localhost:18080/upgrade/bullet_speed/" + std::to_string(userId)
//        });
//
//    if (response.status_code == 200) {
//        auto responseJson = crow::json::load(response.text);
//        QMessageBox::information(this, "Bullet Speed Upgrade Successful",
//            QString::fromStdString(responseJson["message"].s()) + "\nNew Bullet Speed: " +
//            QString::number(responseJson["newBulletSpeed"].d()) + "\nRemaining Crowns: " +
//            QString::number(responseJson["remainingCrowns"].i()));
//    }
//    else if (response.status_code == 400) {
//        auto responseJson = crow::json::load(response.text);
//        if (responseJson.has("error")) {
//            QMessageBox::warning(this, "Error",
//                QString::fromStdString(responseJson["error"].s()));
//        }
//        else {
//            QMessageBox::warning(this, "Error",
//                "Something went wrong. Try again.");
//        }
//    }
//    else if (response.status_code == 404) {
//        QMessageBox::warning(this, "Error",
//            "User or gun not found. Check your user ID.");
//    }
//    else {
//        QMessageBox::warning(this, "Error",
//            "Error performing upgrade. Please try again later.\nServer responded with status code: " +
//            QString::number(response.status_code));
//    }
//}

#include "ShopWidget.h"
#include "MainMenuWidget.h"
#include "UserSession.h"
#include <QMessageBox>
#include <cpr/cpr.h>
#include <crow/json.h>

ShopWidget::ShopWidget(QWidget* parent, MainMenuWidget* mainMenu)
    : QWidget(parent), mainMenuWidget(mainMenu) {
    setupUI();
}

ShopWidget::~ShopWidget() {
    // Destructor logic if needed
}

void ShopWidget::setupUI() {
    layout = new QVBoxLayout(this);

    titleLabel = new QLabel("==== Shop Menu ====", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    buyReloadSpeedButton = new QPushButton("Buy reload speed upgrade", this);
    layout->addWidget(buyReloadSpeedButton);
    connect(buyReloadSpeedButton, &QPushButton::clicked, this,
        &ShopWidget::on_buyReloadSpeedButton_clicked);

    buyBulletSpeedButton = new QPushButton("Buy bullet speed upgrade", this);
    layout->addWidget(buyBulletSpeedButton);
    connect(buyBulletSpeedButton, &QPushButton::clicked, this,
        &ShopWidget::on_buyBulletSpeedButton_clicked);

    goBackButton = new QPushButton("Go back to home page", this);
    layout->addWidget(goBackButton);
    connect(goBackButton, &QPushButton::clicked, this,
        &ShopWidget::on_goBackButton_clicked);
}

void ShopWidget::on_buyReloadSpeedButton_clicked() {
    buyReloadSpeedUpgrade();
}

void ShopWidget::on_buyBulletSpeedButton_clicked() {
    buyBulletSpeedUpgrade();
}

void ShopWidget::on_goBackButton_clicked() {
    if (mainMenuWidget) {
        mainMenuWidget->stackedWidget->setCurrentIndex(0);
    }
    else {
        QMessageBox::information(this, "Home", "Main menu is not available.");
    }
}

void ShopWidget::buyReloadSpeedUpgrade() {
    int userId = UserSession::getInstance().getUserId();

    auto response = cpr::Post(cpr::Url{
        "http://localhost:18080/upgrade/reload_speed/" + std::to_string(userId)
        });

    if (response.status_code == 200) {
        auto responseJson = crow::json::load(response.text);
        QMessageBox::information(this, "Upgrade Successful",
            QString::fromStdString(responseJson["message"].s()) + "\nRemaining Score: " +
            QString::number(responseJson["remainingScore"].i()) + "\nNew Reload Speed: " +
            QString::number(responseJson["newReloadSpeed"].d()));
    }
    else if (response.status_code == 400) {
        auto responseJson = crow::json::load(response.text);
        if (responseJson.has("error")) {
            QMessageBox::warning(this, "Error",
                QString::fromStdString(responseJson["error"].s()));
        }
        else {
            QMessageBox::warning(this, "Error",
                "Something went wrong. Try again.");
        }
    }
    else if (response.status_code == 404) {
        QMessageBox::warning(this, "Error",
            "User or gun not found. Check your user ID.");
    }
    else {
        QMessageBox::warning(this, "Error",
            "Error performing upgrade. Please try again later.\nServer responded with status code: " +
            QString::number(response.status_code));
    }
}

void ShopWidget::buyBulletSpeedUpgrade() {
    int userId = UserSession::getInstance().getUserId();

    auto response = cpr::Post(cpr::Url{
        "http://localhost:18080/upgrade/bullet_speed/" + std::to_string(userId)
        });

    if (response.status_code == 200) {
        auto responseJson = crow::json::load(response.text);
        QMessageBox::information(this, "Bullet Speed Upgrade Successful",
            QString::fromStdString(responseJson["message"].s()) + "\nNew Bullet Speed: " +
            QString::number(responseJson["newBulletSpeed"].d()) + "\nRemaining Crowns: " +
            QString::number(responseJson["remainingCrowns"].i()));
    }
    else if (response.status_code == 400) {
        auto responseJson = crow::json::load(response.text);
        if (responseJson.has("error")) {
            QMessageBox::warning(this, "Error",
                QString::fromStdString(responseJson["error"].s()));
        }
        else {
            QMessageBox::warning(this, "Error",
                "Something went wrong. Try again.");
        }
    }
    else if (response.status_code == 404) {
        QMessageBox::warning(this, "Error",
            "User or gun not found. Check your user ID.");
    }
    else {
        QMessageBox::warning(this, "Error",
            "Error performing upgrade. Please try again later.\nServer responded with status code: " +
            QString::number(response.status_code));
    }
}