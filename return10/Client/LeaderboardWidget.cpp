#include "LeaderboardWidget.h"
#include <QHeaderView>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <cpr/cpr.h>

LeaderboardWidget::LeaderboardWidget(QWidget* parent)
    : QWidget(parent) {
    setupUI();

    connect(refreshCrownsButton, &QPushButton::clicked, this, &LeaderboardWidget::fetchCrownsLeaderboard);
    connect(refreshScoreButton, &QPushButton::clicked, this, &LeaderboardWidget::fetchScoreLeaderboard);

    fetchCrownsLeaderboard();
    fetchScoreLeaderboard();
}

void LeaderboardWidget::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    titleLabel = new QLabel("Leaderboard", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");

    crownsTable = new QTableWidget(this);
    scoreTable = new QTableWidget(this);

    refreshCrownsButton = new QPushButton("Refresh Crowns Leaderboard", this);
    refreshScoreButton = new QPushButton("Refresh Score Leaderboard", this);

    layout->addWidget(titleLabel);
    layout->addWidget(new QLabel("Players by Crowns:"));
    layout->addWidget(crownsTable);
    layout->addWidget(refreshCrownsButton);
    layout->addWidget(new QLabel("Players by Score:"));
    layout->addWidget(scoreTable);
    layout->addWidget(refreshScoreButton);

    setLayout(layout);
}

void LeaderboardWidget::populateTable(QTableWidget* table, const QVector<QVector<QString>>& players, const QVector<QString>& currentUser) {
    table->clear();
    table->setColumnCount(3);
    table->setHorizontalHeaderLabels({ "Rank", "Name", "Value" });
    table->setRowCount(players.size() + (currentUser.isEmpty() ? 0 : 1));

    for (int i = 0; i < players.size(); ++i) {
        for (int j = 0; j < players[i].size(); ++j) {
            table->setItem(i, j, new QTableWidgetItem(players[i][j]));
        }
    }

    if (!currentUser.isEmpty()) {
        int row = players.size();
        for (int j = 0; j < currentUser.size(); ++j) {
            auto item = new QTableWidgetItem(currentUser[j]);
            if (j == 1) {
                item->setText(currentUser[j] + " (You)");
            }
            table->setItem(row, j, item);
        }
    }

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void LeaderboardWidget::updateCrownsLeaderboard(const QVector<QVector<QString>>& players, const QVector<QString>& currentUser) {
    populateTable(crownsTable, players, currentUser);
}

void LeaderboardWidget::updateScoreLeaderboard(const QVector<QVector<QString>>& players, const QVector<QString>& currentUser) {
    populateTable(scoreTable, players, currentUser);
}

void LeaderboardWidget::fetchCrownsLeaderboard() {
    int userId = UserSession::getInstance().getUserId();
    auto response = cpr::Get(cpr::Url{ "http://localhost:18080/leaderboard/" + std::to_string(userId) });

    if (response.status_code == 200) {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response.text.c_str());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray topPlayers = jsonObject["topPlayers"].toArray();

        QVector<QVector<QString>> players;
        QVector<QString> currentUser;

        for (const auto& player : topPlayers) {
            QJsonObject obj = player.toObject();
            players.append({ QString::number(obj["rank"].toInt()), obj["name"].toString(), QString::number(obj["crowns"].toInt()) });
        }

        if (jsonObject.contains("currentUser")) {
            QJsonObject user = jsonObject["currentUser"].toObject();
            currentUser = { QString::number(user["rank"].toInt()), user["name"].toString(), QString::number(user["crowns"].toInt()) };
        }

        updateCrownsLeaderboard(players, currentUser);
    }
    else {
        QMessageBox::warning(this, "Error", "Failed to fetch crowns leaderboard.");
    }
}

void LeaderboardWidget::fetchScoreLeaderboard() {
    int userId = UserSession::getInstance().getUserId();
    auto response = cpr::Get(cpr::Url{ "http://localhost:18080/leaderboard/score/" + std::to_string(userId) });

    if (response.status_code == 200) {
        QJsonDocument jsonResponse = QJsonDocument::fromJson(response.text.c_str());
        QJsonObject jsonObject = jsonResponse.object();
        QJsonArray topPlayers = jsonObject["topPlayers"].toArray();

        QVector<QVector<QString>> players;
        QVector<QString> currentUser;

        for (const auto& player : topPlayers) {
            QJsonObject obj = player.toObject();
            players.append({ QString::number(obj["rank"].toInt()), obj["name"].toString(), QString::number(obj["score"].toInt()) });
        }

        if (jsonObject.contains("currentUser")) {
            QJsonObject user = jsonObject["currentUser"].toObject();
            currentUser = { QString::number(user["rank"].toInt()), user["name"].toString(), QString::number(user["score"].toInt()) };
        }

        updateScoreLeaderboard(players, currentUser);
    }
    else {
        QMessageBox::warning(this, "Error", "Failed to fetch score leaderboard.");
    }
}
