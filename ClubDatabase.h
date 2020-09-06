#ifndef CLUBDATABASE_H
#define CLUBDATABASE_H

#include "Club.h"
#include <vector>
#include "PlayerDatabase.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <cmath>

class ClubDatabase : public PlayerDatabase
{
public:
    std::vector< std::shared_ptr< Club > > allClubsInGame;

    ClubDatabase();
    virtual ~ClubDatabase();

    void setClubDatabase( std::shared_ptr< PlayerDatabase > pPlayerDatabase );
    std::shared_ptr< Club > addClubToGame( QString, unsigned, unsigned, unsigned, QString, unsigned, QString );
    int generateRandomNumber( unsigned, unsigned );
    int generatePlayerValue( unsigned, unsigned );
    int getCalculatePlayerValue();

    void GeneratePlayersForClub( QString position, unsigned number, std::shared_ptr< Club > Club, unsigned leagueReputation );
    void GenerateYouthPlayersForClub( QString position, std::shared_ptr< Club > Club, unsigned leagueReputation );

    std::shared_ptr< Player > GenerateFreePlayers( QString position );

    unsigned getClubReputation( unsigned pClubReputation );
    unsigned getLeagueReputation( unsigned pLeagueReputation );


private:
    std::map< unsigned, QString > mPlayerPositions;

    int mPlayerValue;
};

#endif // ClubDATABASE_H
