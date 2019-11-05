#include "match.h"

Match::Match()
{
    mPlayed = false;
}

void Match::setMatch(int week, Team* home_team,Team* away_team, QDate match_date, bool friendly_match)
{
    if(friendly_match)
    {

    }
    else
    {
        mHomeTeam = home_team;
        mAwayTeam = away_team;
        mMatchDate = match_date;
    }

    qDebug() << home_team->getTeamName() << " : " << away_team->getTeamName() << " -> " << match_date << endl;
}

bool Match::isPlayed()
{
    return mPlayed;
}

Team* Match::getHomeTeam()
{
    return mHomeTeam;
}

Team* Match::getAwayTeam()
{
    return mAwayTeam;
}

QDate Match::getMatchDate()
{
    return mMatchDate;
}
