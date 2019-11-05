#ifndef CREATEGAME_H
#define CREATEGAME_H

#include "league.h"
#include "manager.h"
#include "teamdatabase.h"
#include <vector>
#include <QtSql>
#include <QDebug>
#include <QFileInfo>
#include <QStringList>
#include <map>

using namespace std;

class CreateGame
{
private:
    std::vector<Manager*> mAllManagers;
    std::vector<League*> mAllLeaguesInGame;
    std::vector<Player*> mFreePlayers;

    QSqlDatabase mydb;

    TeamDatabase* mTeamDatabase;
    QString mManagerName;
    QString mMyTeam;
    std::vector<QString> mLeagueList;

    QString mFullDate;

public:
    int mDay;
    int mMonth;
    int mYear;

    CreateGame();
    virtual ~CreateGame();

    std::vector<Manager*> getAllManagers();
    std::vector<League*> getAllLeaguesInGame();
    TeamDatabase* getTeamDatabase();

    QString getFullDate();
    void setFreePlayers();
    void addFreePlayer(Player*);
    std::vector<Player*> getFreePlayers();
    void setScoutPlayers();
    void setDatabase();
    void createDatabase();
    void readCSV();
    void prepareDatabase(QString pManagerName, QString pMyTeam, std::vector<QString> pLeagueList);
};

#endif // CREATEGAME_H
