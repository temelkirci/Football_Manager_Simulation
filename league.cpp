#include "League.h"
#include <QTime>
#include <algorithm>    // std::random_shuffle
#include <memory>

League::League( QString pLeagueName,
                QString pLeagueCountry,
                int pLeagueReputation,
                int pLeagueDivision )
{
    mLeagueName = pLeagueName;
    mLeagueCountry = pLeagueCountry;
    mLeagueReputation = pLeagueReputation;
    mLeagueDivision = pLeagueDivision;

    qDebug() << pLeagueName << endl;
}

void League::addClubToLeague(std::shared_ptr< Club > Club)
{
    mClubsInLeague.push_back(Club);
}

std::vector<std::shared_ptr< Club >> League::getAllClubs()
{
    return mClubsInLeague;
}

QString League::getLeagueName()
{
    return mLeagueName;
}

void League::setFixtures(std::shared_ptr< Match > match)
{
    mFixtures.push_back(match);
}

std::vector< std::shared_ptr< Match > > League::getAllMatchByDate(QDate match_date)
{
    std::vector<std::shared_ptr< Match >> temp;

    for(size_t i=0; i < mFixtures.size(); i++)
    {
        if( mFixtures[i]->getMatchDate() == match_date)
        {
            temp.push_back( mFixtures[i]);
        }
    }
    return temp;
}

void League::createLeagueFixtures()
{

    std::vector< std::shared_ptr< Club > > temp = mClubsInLeague;

    // using built-in random generator:
    std::random_shuffle ( temp.begin(), temp.end() );
/*
    for( int i=0; i<first_; i++)
    {
        int week = 1;
        QDate startDate(2020, 6, 3);

        for(auto second_Club : temp)
        {
            if(first_Club != second_Club)
            {
                Match *pMatch = new Match();
                pMatch->setMatch(week, first_Club, second_Club, startDate);

                setFixtures(pMatch);

                startDate = startDate.addDays(7);

                week++;
            }
        }
    }
    */
}
