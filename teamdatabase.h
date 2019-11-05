#ifndef TEAMDATABASE_H
#define TEAMDATABASE_H

#include "team.h"
#include <vector>
#include "playerdatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>

class TeamDatabase : public PlayerDatabase
{
public:
    std::vector<Team*> allTeamsInGame;

    TeamDatabase();
    virtual ~TeamDatabase();

    void setTeamDatabase(PlayerDatabase* pPlayerDatabase);
    Team* addTeamToGame(QString, int, int, int, QString, int, QString);
    int generateRandomNumber(int,int);
    int generatePlayerValue(int,int);
    int getCalculatePlayerValue();

    void generate_GK_Player(int number, Team* team, int leagueReputation);
    void generate_DC_Player(int number, Team* team, int leagueReputation);
    void generate_DR_Player(int number, Team* team, int leagueReputation);
    void generate_AMR_Player(int number, Team* team, int leagueReputation);
    void generate_DL_Player(int number, Team* team, int leagueReputation);
    void generate_AML_Player(int number, Team* team, int leagueReputation);
    void generate_MC_Player(int number, Team* team, int leagueReputation);
    void generate_AMC_Player(int number, Team* team, int leagueReputation);
    void generate_FC_Player(int number, Team* team, int leagueReputation);

    unsigned int getTeamReputation(int pTeamReputation);
    unsigned int getLeagueReputation(int pLeagueReputation);


private:
    std::map<int, QString> mPlayerPositions;

    int mPlayerValue;
};

#endif // TEAMDATABASE_H
