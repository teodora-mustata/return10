#include "ChooseGameDificulty.h"
#include "MainMenuWidget.h"
#include "StartGameWidget.h"
#include "UserSession.h"

ChooseGameDificulty::ChooseGameDificulty(QWidget* parent, MainMenuWidget* mainMenu)
    : QWidget(parent), mainMenuWidget(mainMenu), selectedDifficulty(0) {
    setupUI();
    this->setWindowTitle("Choose Difficulty");
}

ChooseGameDificulty::~ChooseGameDificulty() {}

void ChooseGameDificulty::setupUI() {
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

    readyToPlayButton = new QPushButton("Ready To Play", this);
    chooseGameDificultyLayout->addWidget(readyToPlayButton);
    connect(readyToPlayButton, &QPushButton::clicked, this, &ChooseGameDificulty::on_readyToPlayButton_clicked);

    goBackButton = new QPushButton("Go Back", this);
    chooseGameDificultyLayout->addWidget(goBackButton);
    connect(goBackButton, &QPushButton::clicked, this, &ChooseGameDificulty::on_goBackButton_clicked);

    chooseGameDificultyWidget->setLayout(chooseGameDificultyLayout);
    stackedWidget->addWidget(chooseGameDificultyWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);
}

void ChooseGameDificulty::on_easyModeButton_clicked() {
    selectedDifficulty = 1;
    sendDifficultyToServer(selectedDifficulty);
    QMessageBox::information(this, "Difficulty", "Easy mode selected.");
}

void ChooseGameDificulty::on_mediumModeButton_clicked() {
    selectedDifficulty = 2;
    sendDifficultyToServer(selectedDifficulty);
    QMessageBox::information(this, "Difficulty", "Medium mode selected.");
}

void ChooseGameDificulty::on_hardModeButton_clicked() {
    selectedDifficulty = 3;
    sendDifficultyToServer(selectedDifficulty);
    QMessageBox::information(this, "Difficulty", "Hard mode selected.");
}

void ChooseGameDificulty::on_goBackButton_clicked() {
    if (mainMenuWidget) {
        mainMenuWidget->stackedWidget->setCurrentIndex(0);
    }
}

void ChooseGameDificulty::on_readyToPlayButton_clicked() {
    if (selectedDifficulty == 0) {
        QMessageBox::information(this, "Game", "First you have to choose difficulty.");
    }
    else {
        emit readyToPlay(); // Emit signal to start the game
    }
}

bool ChooseGameDificulty::createGame() {
    auto response = cpr::Post(cpr::Url{ "http://localhost:18080/start_game" });
    return response.status_code == 200;
}

bool ChooseGameDificulty::sendDifficultyToServer(int difficulty) {
    crow::json::wvalue jsonData;
    jsonData["difficulty"] = difficulty;
    jsonData["playerId"] = UserSession::getInstance().getUserId();

    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/send_difficulty" },
        cpr::Header{ { "Content-Type", "application/json" } },
        cpr::Body{ jsonData.dump() }
    );

    return response.status_code == 200;
}
