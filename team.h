#ifndef TEAM_H
#define TEAM_H

#include <QString>
#include "player.h"
#include <vector>
#include <QDebug>
#include <QDate>

class Team
{
public:
    Team();
    Team(QString teamName, int teamReputation, QString teamCountry, int teamLeague, QString );
    void addPlayerToTeam(Player*);

    std::vector<Player*> getPlayersInTeam();

    QString getTeamName();
    QString getTeamCountry();
    QString getTeamLeague();
    unsigned long long int getTransferBudget();
    int getTeamSalary();

    void setTeamAvaragePoint(unsigned int);
    unsigned int getTeamAvaragePoint();

    void addTransferList(Player*);
    void removeTransferList(Player*);
    std::vector<Player*> getPlayersInTransferList();

    void increaseTransferBudget(unsigned long long int);
    void decreaseTransferBudget(unsigned long long int);

    void increaseWageBudget(int);
    void decreaseWageBudget(int);

    void setClubManagerName(QString);
    QString getClubManagerName();

    void setClubPresidentName(QString);
    QString getClubPresidentName();

    void removePlayer(Player*);

    void prepareMatchPlayers();
    std::vector<Player*> getMatchPlayers();
    std::vector<Player*> getPlayersByPosition(QString);

    int getTeamReputation();
    void setWageBudget(int);
    unsigned long long int getTeamValue();
    void addScoutPlayer(Player* player, unsigned long long int value);
    std::map<Player*, unsigned long long int> getScoutingPlayers();
    unsigned long long int mTeamValue;
    int mMaxWageBudget;
    std::map<Team*, QDate> getFixtures();
    void setFixtures(Team*, QDate);

private:
    std::map<Player*, unsigned long long int> mScoutingPlayers;
    std::vector<Player*> mTransferList;
    std::vector<Player*> mMatchPlayers;
    QString mFormation;

    QString mTeamName;
    QString mTeamCountry;
    int mWageBudget;
    int mRemainingWageBudget;
    unsigned long long int mRemainingTransferBudget;
    QString mTeamLeague;
    unsigned long long int mTransferBudget;
    std::vector<Player*> mAllPlayers;
    int mTeamReputation;
    unsigned int mTeamAvarageAbility;

    QString mClubManager;
    QString mPresident;
};

#endif // TEAM_H
