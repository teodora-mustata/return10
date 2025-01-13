#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include "ChooseGameDificulty.h"

class ChooseGameDificulty;

class StartGameWidget : public QWidget
{
    Q_OBJECT

public:
    StartGameWidget(QWidget* parent = nullptr, ChooseGameDificulty* chooseDifficulty = nullptr);
    ~StartGameWidget();

    void setDifficulty(int difficulty); // Metodã pentru a seta dificultatea

private slots:
    void on_readyToPlayButton_clicked();
    void on_goBackButton_clicked();

private:
    QLabel* titleLabel;
    QPushButton* readyToPlayButton;
    QPushButton* goBackButton;
    QVBoxLayout* layout;

    ChooseGameDificulty* chooseGameDificultyWidget;
    int currentDifficulty;

    void setupUI();
};
