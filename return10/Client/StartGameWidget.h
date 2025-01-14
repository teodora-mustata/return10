#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class ChooseGameDificulty;

class StartGameWidget : public QWidget
{
	Q_OBJECT

public:
	StartGameWidget(QWidget *parent = nullptr,ChooseGameDificulty* chooseGameDificuly=nullptr);
	~StartGameWidget();

private:
	
	ChooseGameDificulty* chooseGameDificultyWidget;
	void setupUI();
};
