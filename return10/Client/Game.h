#pragma once

#include <QWidget>
#include<qpainter.h>
#include "ui_Game.h"

class Game : public QWidget
{
	Q_OBJECT

public:
	explicit Game(QWidget *parent = nullptr);
	~Game();

private:
	void paintEvent(QPaintEvent* event) override;//ovveriding for painting
};
