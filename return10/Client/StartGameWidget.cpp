#include "StartGameWidget.h"
#include "ChooseGameDificulty.h"

StartGameWidget::StartGameWidget(QWidget *parent, ChooseGameDificulty* chooseGameDificulty)
	: QWidget(parent),chooseGameDificultyWidget(chooseGameDificulty)
{
	setupUI();
}

StartGameWidget::~StartGameWidget()
{}

void StartGameWidget::setupUI()
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* titleLabel = new QLabel("Welcome to the Game!", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(titleLabel);

    QPushButton* backButton = new QPushButton("Back to Difficulty Selection", this);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, [this]() {
        if (chooseGameDificultyWidget) {
            chooseGameDificultyWidget->stackedWidget->setCurrentWidget(chooseGameDificultyWidget);
        }
        });

    setLayout(layout);
}
