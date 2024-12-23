#pragma once

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include "UserSession.h"
class LeaderboardWidget : public QWidget {
    Q_OBJECT

public:
    explicit LeaderboardWidget(QWidget* parent = nullptr);

    
    void updateCrownsLeaderboard(const QVector<QVector<QString>>& players, const QVector<QString>& currentUser);
    void updateScoreLeaderboard(const QVector<QVector<QString>>& players, const QVector<QString>& currentUser);

private slots:
    void fetchCrownsLeaderboard();
    void fetchScoreLeaderboard();

private:
    QLabel* titleLabel;
    QTableWidget* crownsTable;
    QTableWidget* scoreTable;
    QPushButton* refreshCrownsButton;
    QPushButton* refreshScoreButton;

    void setupUI();
    void populateTable(QTableWidget* table, const QVector<QVector<QString>>& players, const QVector<QString>& currentUser);
};
