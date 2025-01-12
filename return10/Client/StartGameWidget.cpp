#include "StartGameWidget.h"
#include "MainMenuWidget.h"

StartGameWidget::StartGameWidget(QWidget* parent, MainMenuWidget* mainMenu)
    : QWidget(parent), mainMenuWidget(mainMenu), selectedDifficulty(0) {
    setupUI();
}

StartGameWidget::~StartGameWidget()
{}

void StartGameWidget::setupUI() {


    stackedWidget = new QStackedWidget(this);

    // Choose Difficulty Page
    chooseGameDificulty = new QWidget(this);
    QVBoxLayout* difficultyLayout = new QVBoxLayout(chooseGameDificulty);

    QLabel* titleLabel = new QLabel("Choose Difficulty", chooseGameDificulty);
    titleLabel->setAlignment(Qt::AlignCenter);
    difficultyLayout->addWidget(titleLabel);

    easyModeButton = new QPushButton("Easy", chooseGameDificulty);
    difficultyLayout->addWidget(easyModeButton);
    connect(easyModeButton, &QPushButton::clicked, this, &StartGameWidget::on_easyModeButton_clicked);

    mediumModeButton = new QPushButton("Medium", chooseGameDificulty);
    difficultyLayout->addWidget(mediumModeButton);
    connect(mediumModeButton, &QPushButton::clicked, this, &StartGameWidget::on_mediumModeButton_clicked);

    hardModeButton = new QPushButton("Hard", chooseGameDificulty);
    difficultyLayout->addWidget(hardModeButton);
    connect(hardModeButton, &QPushButton::clicked, this, &StartGameWidget::on_hardModeButton_clicked);

    goBackButton = new QPushButton("Go Back", chooseGameDificulty);
    difficultyLayout->addWidget(goBackButton);
    connect(goBackButton, &QPushButton::clicked, this, &StartGameWidget::on_goBackButton_clicked);

    chooseGameDificulty->setLayout(difficultyLayout);




    // Add pages to stackedWidget
    stackedWidget->addWidget(chooseGameDificulty);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(stackedWidget);
    setLayout(mainLayout);

    stackedWidget->setCurrentWidget(chooseGameDificulty);


}
void StartGameWidget::on_easyModeButton_clicked()
{
    selectedDifficulty = 1;
    if (sendDifficultyToServer(selectedDifficulty)) {
        stackedWidget->setCurrentWidget(readyToPlayPage);
    }
}

void StartGameWidget::on_mediumModeButton_clicked()
{
    selectedDifficulty = 2;
    if (sendDifficultyToServer(selectedDifficulty)) {
        stackedWidget->setCurrentWidget(readyToPlayPage);
    }
}

void StartGameWidget::on_hardModeButton_clicked()
{
    selectedDifficulty = 3;
    if (sendDifficultyToServer(selectedDifficulty)) {
        stackedWidget->setCurrentWidget(readyToPlayPage);
    }
}

void StartGameWidget::on_readyToPlayButton_clicked()
{
   
}

void StartGameWidget::on_goBackButton_clicked()
{
    if (mainMenuWidget) {
        mainMenuWidget->stackedWidget->setCurrentIndex(0);
    }
    else {
        QMessageBox::information(this, "Home", "Main menu is not available.");
    }
}

void StartGameWidget::on_quitGame_clicked()
{
}

bool StartGameWidget::sendDifficultyToServer(int difficulty) {
    crow::json::wvalue jsonData;
    jsonData["difficulty"] = difficulty;

    auto response = cpr::Post(
        cpr::Url{ "http://localhost:18080/send_difficulty" },
        cpr::Header{ { "Content-Type", "application/json" } },
        cpr::Body{ jsonData.dump() }
    );

    if (response.status_code == 200) {
        std::cout << "Difficulty set successfully!\n";
        return true;
    }
    else if (response.status_code == 403) {
        std::cout << "Difficulty already set by another client.\n";
    }
    else {
        std::cout << "Couldn't send difficulty to server. Try again.\n";
    }
    return false;
}

void StartGameWidget::checkCurrentDifficulty()
{
}

void StartGameWidget::startServerGame()
{
}
