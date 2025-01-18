#include "StartGameWidget.h"
#include "ChooseGameDificulty.h"
#include "MainMenuWidget.h"

StartGameWidget::StartGameWidget(QWidget *parent, ChooseGameDificulty* chooseGameDificulty,MainMenuWidget* mainMenu )
	: QWidget(parent),chooseGameDificultyWidget(chooseGameDificulty), mainMenuWidget(mainMenu)
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

    QPushButton* backButton = new QPushButton("Back to Main Menu", this);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, [this]() {
        if (mainMenuWidget) {
            mainMenuWidget->stackedWidget->setCurrentWidget(mainMenuWidget->stackedWidget->widget(0));
        }
        });

    setLayout(layout);
}
