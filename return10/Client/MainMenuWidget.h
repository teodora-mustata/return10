
#include <QWidget>
//#include "Game.h"
//#include "ShopWidget.h"
#include "LeaderboardWidget.h"

namespace Ui {
    class MainMenuWidget;
}

class MainMenuWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenuWidget(QWidget* parent = nullptr);
    ~MainMenuWidget();

private slots:
    /*void on_startGameButton_clicked();
    void on_shopButton_clicked();
    void on_leaderboardButton_clicked();*/
    void on_leaderboardButton_clicked(); 
    void on_exitButton_clicked();

private:
    Ui::MainMenuWidget* ui;
    //Game* gamePage;
    //ShopWidget* shopPage;
    LeaderboardWidget* leaderboardPage;
};
