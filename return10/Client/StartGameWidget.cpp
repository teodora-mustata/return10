#include "StartGameWidget.h"

StartGameWidget::StartGameWidget(QWidget* parent, ChooseGameDificulty* chooseDifficulty)
    : QWidget(parent), chooseGameDificultyWidget(chooseDifficulty), currentDifficulty(0)
{
    setupUI();
    this->setWindowTitle("Start Game");
}

StartGameWidget::~StartGameWidget() {}

void StartGameWidget::setupUI()
{
    layout = new QVBoxLayout(this);

    titleLabel = new QLabel("Ready to Play?", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    readyToPlayButton = new QPushButton("Ready to Play", this);
    layout->addWidget(readyToPlayButton);
    connect(readyToPlayButton, &QPushButton::clicked, this, &StartGameWidget::on_readyToPlayButton_clicked);

    goBackButton = new QPushButton("Go Back", this);
    layout->addWidget(goBackButton);
    connect(goBackButton, &QPushButton::clicked, this, &StartGameWidget::on_goBackButton_clicked);

    this->setLayout(layout);
}

void StartGameWidget::setDifficulty(int difficulty)
{
    currentDifficulty = difficulty;
    QString difficultyText = "Selected Difficulty: " + QString::number(currentDifficulty);
    titleLabel->setText(difficultyText);
}

void StartGameWidget::on_readyToPlayButton_clicked()
{
    if (currentDifficulty == 0) {
        QMessageBox::warning(this, "Error", "No difficulty selected! Please go back and choose a difficulty.");
        return;
    }

    QMessageBox::information(this, "Game Start", "Starting the game with difficulty: " + QString::number(currentDifficulty));
    // Logica pentru a începe jocul poate fi adãugatã aici.
}

void StartGameWidget::on_goBackButton_clicked()
{
    if (chooseGameDificultyWidget) {
        chooseGameDificultyWidget->show();
        this->hide();
    }
    else {
        QMessageBox::warning(this, "Error", "ChooseGameDificulty widget is not available.");
    }
}
