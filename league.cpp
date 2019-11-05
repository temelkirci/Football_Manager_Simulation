#include "league.h"
#include <QTime>
#include <algorithm>    // std::random_shuffle
#include <match.h>

League::League(QString pLeagueName, QString pLeagueCountry, int pLeagueReputation, int pLeagueDivision)
{
    mLeagueName = pLeagueName;
    mLeagueCountry = pLeagueCountry;
    mLeagueReputation = pLeagueReputation;
    mLeagueDivision = pLeagueDivision;
}

void League::addTeamToLeague(Team* team)
{
    mTeamsInLeague.push_back(team);
}

std::vector<Team*> League::getAllTeams()
{
    return mTeamsInLeague;
}

QString League::getLeagueName()
{
    return mLeagueName;
}

void League::setFixtures(Match* match)
{
    mFixtures.push_back(match);
}

std::vector<Match*> League::getAllMatchByDate(QDate match_date)
{
    std::vector<Match*> temp;

    for(auto i : mFixtures)
    {
        if(i->getMatchDate() == match_date)
        {
            temp.push_back(i);
        }
    }

    return temp;
}

void League::createLeagueFixtures()
{
    std::vector<Team*> temp = mTeamsInLeague;

    // using built-in random generator:
    std::random_shuffle ( temp.begin(), temp.end() );

    for(auto first_team : temp)
    {
        int week = 1;
        QDate startDate(2020, 6, 3);

        for(auto second_team : temp)
        {
            if(first_team != second_team)
            {
                Match *pMatch = new Match();
                pMatch->setMatch(week, first_team, second_team, startDate);

                setFixtures(pMatch);

                startDate = startDate.addDays(7);

                week++;
            }
        }
    }
}
