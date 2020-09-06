#ifndef LEAGUE_H
#define LEAGUE_H

#include "Club.h"
#include "Fixture.h"
#include "Match.h"
#include <vector>

class League : public Fixture
{
private:
    std::vector< std::shared_ptr< Club > > mClubsInLeague;
    QString mLeagueName;
    QString mLeagueCountry;
    int mLeagueDivision;
    int mClubNumber;
    int mLeagueReputation;

    std::vector< std::shared_ptr< Match > > mFixtures;


public:
    League( QString, QString, int, int );
    void addClubToLeague( std::shared_ptr< Club > );
    QString getLeagueName();
    std::vector<std::shared_ptr< Club >> getAllClubs();
    void createLeagueFixtures();
    int generateRandomNumber( int, int );

    void setFixtures( std::shared_ptr< Match > );
    std::vector< std::shared_ptr< Match > > getAllMatchByDate( QDate );
};

#endif // LEAGUE_H
