#include "Match.h"

Match::Match()
{
    mTime = 0;
    mPlayed = false;

    mHomeScore = 0;
    mAwayScore = 0;
}

void Match::setMatch( int week, std::shared_ptr< Club > home_Club,std::shared_ptr< Club > away_Club, QDate match_date, bool friendly_match )
{
    mPlayed = false;

    if( friendly_match )
    {

    }
    else
    {
        mHomeClub = home_Club;
        mAwayClub = away_Club;
        mMatchDate = match_date;
    } 
}

void Match::addScoreForHomeClub(unsigned int tScore)
{
    mHomeScore = mHomeScore + tScore;
}

void Match::addScoreForAwayClub(unsigned int tScore)
{
    mAwayScore = mAwayScore + tScore;
}

unsigned int Match::getScoreForHomeClub()
{
    return mHomeScore;
}

unsigned int Match::getScoreForAwayClub()
{
    return mAwayScore;
}

void Match::eventsInGame(int tTime, QString tEvents)
{
    mEvents[tTime] = tEvents;
}

bool Match::isPlayed()
{
    return mPlayed;
}

std::shared_ptr< Club > Match::getHomeClub()
{
    return (mHomeClub);
}

std::shared_ptr< Club > Match::getAwayClub()
{
    return (mAwayClub);
}

QDate Match::getMatchDate()
{
    return mMatchDate;
}
