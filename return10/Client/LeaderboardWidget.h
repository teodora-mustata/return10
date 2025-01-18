
#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>


//
// Forward declaration
class MainMenuWidget;

class LeaderboardWidget : public QWidget {
    Q_OBJECT

public:
    explicit LeaderboardWidget(QWidget* parent = nullptr, MainMenuWidget* mainMenu = nullptr);

    void updateCrownsLeaderboard(const QVector<QVector<QString>>& players, const QVector<QString>& currentUser);
    void updateScoreLeaderboard(const QVector<QVector<QString>>& players, const QVector<QString>& currentUser);

private slots:
    void fetchCrownsLeaderboard();
    void fetchScoreLeaderboard();
    void on_goBackButton_clicked();

private:
    QLabel* titleLabel;
    QTableWidget* crownsTable;
    QTableWidget* scoreTable;
    QPushButton* refreshCrownsButton;
    QPushButton* refreshScoreButton;
    QPushButton* goBackButton;

    MainMenuWidget* mainMenuWidget; // Pointer to main menu widget

    void setupUI();
    void populateTable(QTableWidget* table, const QVector<QVector<QString>>& players, const QVector<QString>& currentUser);
};