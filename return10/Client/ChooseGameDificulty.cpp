#include "ChooseGameDificulty.h"
#include "MainMenuWidget.h"
#include "StartGameWidget.h"
#include<QApplication>

ChooseGameDificulty::ChooseGameDificulty(QWidget* parent, MainMenuWidget* mainMenu)
    : QWidget(parent), mainMenuWidget(mainMenu), selectedDifficulty(0)
{
    setupUI();
    this->setWindowTitle("Choose Difficulty");
    // Crearea paginii StartGameWidget și transmiterea mainMenuWidget

}

ChooseGameDificulty::~ChooseGameDificulty() {}

void ChooseGameDificulty::setupUI()
{
    stackedWidget = new QStackedWidget(this);
  

    QWidget* chooseGameDificultyWidget = new QWidget(this);
    QVBoxLayout* chooseGameDificultyLayout = new QVBoxLayout(chooseGameDificultyWidget);



    titleLabel = new QLabel("==== Choose Difficulty ====", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    chooseGameDificultyLayout->addWidget(titleLabel);

    easyModeButton = new QPushButton("Easy", this);
    chooseGameDificultyLayout->addWidget(easyModeButton);
    connect(easyModeButton, &QPushButton::clicked, this, &ChooseGameDificulty::on_easyModeButton_clicked);

    mediumModeButton = new QPushButton("Medium", this);
    chooseGameDificultyLayout->addWidget(mediumModeButton);
    connect(mediumModeButton, &QPushButton::clicked, this, &ChooseGameDificulty::on_mediumModeButton_clicked);

    hardModeButton = new QPushButton("Hard", this);
    chooseGameDificultyLayout->addWidget(hardModeButton);
    connect(hardModeButton, &QPushButton::clicked, this, &ChooseGameDificulty::on_hardModeButton_clicked);

    goBackButton = new QPushButton("Go Back", this);
    chooseGameDificultyLayout->addWidget(goBackButton);
    connect(goBackButton, &QPushButton::clicked, this, &ChooseGameDificulty::on_goBackButton_clicked);

    chooseGameDificultyWidget->setLayout(chooseGameDificultyLayout);
    stackedWidget->addWidget(chooseGameDificultyWidget);

    startGameWidgetPage = new StartGameWidget(nullptr, this, mainMenuWidget);  // Modificare aici

    stackedWidget->addWidget(startGameWidgetPage);

    QVBoxLayout* chooseDificultyLayout = new QVBoxLayout(this);
    chooseDificultyLayout->addWidget(stackedWidget);
    setLayout(chooseDificultyLayout);
}

void ChooseGameDificulty::on_easyModeButton_clicked()
{
    selectedDifficulty = 1;
    QMessageBox::information(this, "Difficulty", "Easy mode selected.");
    stackedWidget->setCurrentWidget(startGameWidgetPage);
    // Verificăm widgetul curent
    qDebug() << "Current widget after switching:" << stackedWidget->currentWidget();
}

void ChooseGameDificulty::on_mediumModeButton_clicked()
{
    selectedDifficulty = 2;
    QMessageBox::information(this, "Difficulty", "Medium mode selected.");
    stackedWidget->setCurrentWidget(startGameWidgetPage);

}

void ChooseGameDificulty::on_hardModeButton_clicked()
{
    selectedDifficulty = 3;
    QMessageBox::information(this, "Difficulty", "Hard mode selected.");
    stackedWidget->setCurrentWidget(startGameWidgetPage);

}

void ChooseGameDificulty::on_goBackButton_clicked()
{
    if (mainMenuWidget) {
        mainMenuWidget->stackedWidget->setCurrentIndex(0);
    }
    else {
        QMessageBox::information(this, "Home", "Main menu is not available.");
    }
}

bool ChooseGameDificulty::sendDifficultyToServer(int difficulty)
{
    crow::json::wvalue jsonData;
    jsonData["difficulty"] = difficulty;

    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/send_difficulty" },
        cpr::Header{ { "Content-Type", "application/json" } },
        cpr::Body{ jsonData.dump() }
    );

    if (response.status_code == 200) {
        std::cout << "Difficulty sent successfully!\n";
        return true;
    }
    else {
        std::cout << "Failed to send difficulty to server. Try again.\n";
    }
    return false;
}
