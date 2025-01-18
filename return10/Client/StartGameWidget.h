#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class ChooseGameDificulty;
class MainMenuWidget;

class StartGameWidget : public QWidget
{
	Q_OBJECT//go back to main menu

public:
	StartGameWidget(QWidget *parent = nullptr,ChooseGameDificulty* chooseGameDificuly=nullptr,MainMenuWidget* mainMenuWidget=nullptr);
	~StartGameWidget();

private:
	MainMenuWidget* mainMenuWidget;
	ChooseGameDificulty* chooseGameDificultyWidget;
	void setupUI();
};
