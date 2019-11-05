#ifndef LEAGUE_H
#define LEAGUE_H

#include "team.h"
#include <vector>
#include "match.h"

class League
{
private:
    std::vector<Team*> mTeamsInLeague;
    QString mLeagueName;
    QString mLeagueCountry;
    int mLeagueDivision;
    int mTeamNumber;
    int mLeagueReputation;

    std::vector<Match*> mFixtures;


public:
    League(QString,QString,int,int);
    void addTeamToLeague(Team*);
    QString getLeagueName();
    std::vector<Team*> getAllTeams();
    void createLeagueFixtures();
    int generateRandomNumber(int, int);

    void setFixtures(Match*);
    std::vector<Match*> getAllMatchByDate(QDate);
};

#endif // LEAGUE_H
