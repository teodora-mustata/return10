#include "ChooseGameDificulty.h"
#include "MainMenuWidget.h"

ChooseGameDificulty::ChooseGameDificulty(QWidget* parent, MainMenuWidget* mainMenu)
    : QWidget(parent), mainMenuWidget(mainMenu), selectedDifficulty(0)
{
    setupUI();
    this->setWindowTitle("Choose Difficulty");
}

ChooseGameDificulty::~ChooseGameDificulty() {}

void ChooseGameDificulty::setupUI()
{
    layout = new QVBoxLayout(this);

    titleLabel = new QLabel("==== Choose Difficulty ====", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    easyModeButton = new QPushButton("Easy", this);
    layout->addWidget(easyModeButton);
    connect(easyModeButton, &QPushButton::clicked, this, &ChooseGameDificulty::on_easyModeButton_clicked);

    mediumModeButton = new QPushButton("Medium", this);
    layout->addWidget(mediumModeButton);
    connect(mediumModeButton, &QPushButton::clicked, this, &ChooseGameDificulty::on_mediumModeButton_clicked);

    hardModeButton = new QPushButton("Hard", this);
    layout->addWidget(hardModeButton);
    connect(hardModeButton, &QPushButton::clicked, this, &ChooseGameDificulty::on_hardModeButton_clicked);

    goBackButton = new QPushButton("Go Back", this);
    layout->addWidget(goBackButton);
    connect(goBackButton, &QPushButton::clicked, this, &ChooseGameDificulty::on_goBackButton_clicked);

    this->setLayout(layout);
}

void ChooseGameDificulty::on_easyModeButton_clicked()
{
    selectedDifficulty = 1;
    QMessageBox::information(this, "Difficulty", "Easy mode selected.");
}

void ChooseGameDificulty::on_mediumModeButton_clicked()
{
    selectedDifficulty = 2;
    QMessageBox::information(this, "Difficulty", "Medium mode selected.");
}

void ChooseGameDificulty::on_hardModeButton_clicked()
{
    selectedDifficulty = 3;
    QMessageBox::information(this, "Difficulty", "Hard mode selected.");
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
