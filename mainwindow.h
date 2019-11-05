#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QTableView>
#include <QTabWidget>
#include <QTableWidgetItem>
#include <string>
#include "creategame.h"
#include <map>
#include <QPushButton>
#include <vector>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Team* getMyTeam();
    void showMyTeam();
    void InitGame(QString pManagerName, QString pMyTeam, std::vector<QString> pLeagueList);
    void createInbox(QString, QString);
    void showMyInbox();
    void showTransferList();
    void showScoutList();
    QString getValueColor(int);
    QDate mToday;
    Ui::MainWindow *ui;

private slots:
    void showPlayerDetails();
    void drawLeague(QString);
    void on_pushButton_clicked();
    void on_myTeam_cellClicked(int row, int column);
    void showMyMessage(QString);

    void on_ProgressButton_clicked();
    void on_freePlayersCheckbox_stateChanged(int arg1);
    void on_LeagueTable_cellClicked(int row, int column);
    void on_releasePlayerButton_clicked();

    void on_addTransferListButton_clicked();

private:

    TeamDatabase* mTeamDatabase;
    Team* mMyTeam;
    QTableWidget* pTable;
    CreateGame* mCreateWindow;
    QString mMyTeamName;
    Player* mSelectedPlayer;
    bool init;
    QSignalMapper mapper;

    std::map<QPushButton*, QString> mInbox;
};

#endif // MAINWINDOW_H
