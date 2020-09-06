#ifndef CREATEGAME_H
#define CREATEGAME_H

#include "League.h"
#include "Manager.h"
#include "ClubDatabase.h"
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
    std::vector< std::shared_ptr< Manager > > mAllManagers;
    std::vector< std::shared_ptr< League > > mAllLeaguesInGame;
    std::vector<std::shared_ptr< Player >> mFreePlayers;

    QSqlDatabase mydb;

    std::shared_ptr< ClubDatabase > mClubDatabase;
    QString mManagerName;
    QString mMyClub;
    std::vector<QString> mLeagueList;
    std::vector< std::shared_ptr< Match > > mFriendlyMatch;
    std::vector< std::shared_ptr< Match > > mAllMatches;


    QString mFullDate;

public:
    int mDay;
    int mMonth;
    int mYear;

    CreateGame();
    virtual ~CreateGame();

    std::vector< std::shared_ptr< Manager > > getAllManagers();
    std::vector< std::shared_ptr< League > > getAllLeaguesInGame();
    std::shared_ptr< ClubDatabase > getClubDatabase();
    std::vector< std::shared_ptr< Match > > getFriendlyMatch(QDate);

    QString getFullDate();
    void setFreePlayers();
    void addFreePlayer( std::shared_ptr< Player > );
    std::vector<std::shared_ptr< Player >> getFreePlayers();
    void setScoutPlayers();
    void setDatabase();
    void createDatabase();
    void readCSV();
    void prepareDatabase( QString pManagerName, QString pMyClub, std::vector<QString> pLeagueList );
};

#endif // CREATEGAME_H
