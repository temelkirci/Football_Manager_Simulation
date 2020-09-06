#include "Club.h"
#include <functional>   // std::greater
#include <vector>

Club::Club()
{
    qDebug() << "Club" << endl;
}

Club::Club( QString ClubName,
            unsigned ClubReputation,
            QString pLeagueName,
            unsigned pTransferBudget,
            QString pLeagueCountry,
            unsigned pTrainingFacilities,
            unsigned pYouthTrainingFacilities,
            unsigned pStadiumCapacity )
{
    mClubName = ClubName;
    mClubReputation = ClubReputation;
    mTransferBudget = pTransferBudget;
    mClubLeague = pLeagueName;
    mClubCountry = pLeagueCountry;

    mWageBudget = 0;
    mClubValue = 0;

    mTrainingFacilities = pTrainingFacilities;
    mYouthTrainingFacilitiesLevel = pYouthTrainingFacilities;
    mStadiumCapacity = pStadiumCapacity;

    mpManager = nullptr;
}

void Club::addTransferList( std::shared_ptr< Player > player )
{
    mTransferList.push_back( player );
}

void Club::removeTransferList( std::shared_ptr< Player > player )
{
    for( auto it = mTransferList.begin(); it != mTransferList.end(); ++it )
    {
        if( *it == player )
        {
            mTransferList.erase( it );
            break;
        }
    }
}

void Club::setManager( std::shared_ptr< Manager > tManager )
{
    mpManager = tManager;

    mRemaningManagerConfidence = 100;
}

std::map< std::shared_ptr< Player >, unsigned > Club::getScoutingPlayers()
{
    return mScoutingPlayers;
}

void Club::setClubPresidentName( QString president )
{
    mPresident = president;
}

QString Club::getClubPresidentName()
{
    return mPresident;
}

QString Club::getClubManagerName()
{
    return mpManager->getManagerName();
}

void Club::addScoutPlayer( std::shared_ptr< Player > player, unsigned value )
{
    mScoutingPlayers.insert( std::pair< std::shared_ptr< Player >, int > ( (player), value ) );
}

unsigned int Club::getClubAvaragePoint()
{
    mClubAvarageAbility = 0;

    for( size_t i=0; i < mAllPlayersInClub.size(); i++ )
        mClubAvarageAbility += mAllPlayersInClub[i]->getPlayerCA();
    return mClubAvarageAbility / (mAllPlayersInClub.size() );
}

std::vector< std::shared_ptr< Player > > Club::getPlayersInTransferList()
{
    return mTransferList;
}

int Club::getClubSalary()
{
    return mWageBudget;
}

void Club::increaseTransferBudget( unsigned increaseValue )
{
    mTransferBudget += increaseValue;
}

void Club::decreaseTransferBudget( unsigned decreaseValue )
{
    mTransferBudget -= decreaseValue;
}

void Club::increaseWageBudget( unsigned increaseWageValue )
{
    mWageBudget += increaseWageValue;
}

void Club::decreaseWageBudget( unsigned decreaseWageValue )
{
    mWageBudget -= decreaseWageValue;
}

void Club::addPlayerToClub( std::shared_ptr< Player > player )
{
    mAllPlayersInClub.push_back( player );
}

void Club::addYouthPlayerToClub( std::shared_ptr< Player > player )
{
    mAllPlayersInYouthClub.push_back( player );
}

void Club::setWageBudget( unsigned wageBudget )
{
    mWageBudget = wageBudget;
}

unsigned Club::getMaxWageBudget()
{
    return mMaxWageBudget;
}

void Club::setMaxWageBudget( unsigned maxWage )
{
    mMaxWageBudget = maxWage;
}

unsigned Club::getClubValue()
{
    return mClubValue;
}

void Club::changeClubValue( int clubValue )
{
    mClubValue = mClubValue + clubValue;
}

std::vector< std::shared_ptr< Player > > Club::getPlayersInClub()
{
    return mAllPlayersInClub;
}

std::vector< std::shared_ptr< Player > > Club::getYouthPlayersInClub()
{
    return mAllPlayersInYouthClub;
}

QString Club::getClubName()
{
    return mClubName;
}

QString Club::getClubCountry()
{
    return mClubCountry;
}

QString Club::getClubLeague()
{
    return mClubLeague;
}

std::vector< std::shared_ptr< Player > > Club::getPlayersByPosition( QString position )
{
    std::vector< std::shared_ptr< Player > > temp;
    for( size_t i=0; i < mAllPlayersInClub.size(); i++ )
        if( mAllPlayersInClub[i]->getPlayerPosition() == position )
            temp.push_back( mAllPlayersInClub[i] );

    return temp;
}

bool Club::isPlayerInMatch( std::shared_ptr< Player > tPlayer )
{
    if( std::count( mMatchPlayers.begin(), mMatchPlayers.end(), tPlayer ) )
        return true;
    else
        return false;
}

bool Club::isPlayerInSub( std::shared_ptr< Player > tPlayer )
{
    if( std::count( mSubMatchPlayers.begin(), mSubMatchPlayers.end(), tPlayer ) )
        return true;
    else
        return false;
}

std::shared_ptr< Manager > Club::getClubManager()
{
    return mpManager;
}

void Club::setMatch()
{

}

void Club::addTransferOffers( TransferOffer offer )
{
    transferOffers.push_back( offer );
}

void Club::generateTransferOffer( std::shared_ptr< Player > tPlayer, unsigned offer )
{
    TransferOffer transferOffer;
    transferOffer.player = tPlayer;
    transferOffer.bidForPlayer = offer;

    addTransferOffers( transferOffer );
}

void Club::prepareMatchPlayers()
{
    qDebug() << getClubName() << " preparing for match : " << mpManager->getFormation() << endl;

    mMatchPlayers.clear();
    mSubMatchPlayers.clear();

    std::vector< QString > formation;

    formation.push_back( "GK" );

    if( mpManager->getFormation() == "4-4-2" )
    {
        formation.push_back( "DR" );

        formation.push_back( "DC" );
        formation.push_back( "DC" );

        formation.push_back( "DL" );

        formation.push_back( "AML" );
        formation.push_back( "AMR" );

        formation.push_back( "MC" );
        formation.push_back( "MC" );

        formation.push_back( "FC" );
        formation.push_back( "FC" );
    }

    if( mpManager->getFormation() == "4-2-3-1" )
    {
        formation.push_back( "DR" );

        formation.push_back( "DC" );
        formation.push_back( "DC" );

        formation.push_back( "DL" );

        formation.push_back( "AML" );
        formation.push_back( "AMR" );

        formation.push_back( "MC" );
        formation.push_back( "MC" );

        formation.push_back( "AMC" );

        formation.push_back( "FC" );
    }

    if( mpManager->getFormation() == "4-3-2-1" )
    {
        formation.push_back( "DR" );

        formation.push_back( "DC" );
        formation.push_back( "DC" );

        formation.push_back( "DL" );

        formation.push_back( "AML" );
        formation.push_back( "AMR" );

        formation.push_back( "MC" );
        formation.push_back( "MC" );
        formation.push_back( "MC" );

        formation.push_back( "FC" );
    }

    if( mpManager->getFormation() == "4-2-1-2-1" )
    {
        formation.push_back( "DR" );

        formation.push_back( "DC" );
        formation.push_back( "DC" );

        formation.push_back( "DL" );

        formation.push_back( "AML" );
        formation.push_back( "AMR" );

        formation.push_back( "MC" );

        formation.push_back( "AMC" );

        formation.push_back( "FC" );
        formation.push_back( "FC" );
    }

    if( mpManager->getFormation() == "4-3-3" )
    {
        formation.push_back( "DR" );

        formation.push_back( "DC" );
        formation.push_back( "DC" );

        formation.push_back( "DL" );

        formation.push_back( "MC" );
        formation.push_back( "MC" );
        formation.push_back( "MC" );

        formation.push_back( "FC" );
        formation.push_back( "FC" );
        formation.push_back( "FC" );
    }

    for ( size_t t=0; t<formation.size(); t++ )
    {
        std::vector< std::shared_ptr< Player > > playersInTeam = getPlayersByPosition( formation[t] );
        std::vector< int > temp{};

        for( size_t i=0; i < playersInTeam.size(); i++ )
        {
            temp.push_back( playersInTeam[i]->getPlayerCA() );
        }

        sort( temp.begin(), temp.end() );


        for( size_t x=0; x < playersInTeam.size(); x++ )
        {
            std::shared_ptr< Player > tempPlayer = ( playersInTeam[ x ] );

            if( tempPlayer->getPlayerCA() == temp.back() && !isPlayerInMatch( (tempPlayer) ) && !tempPlayer->isInjured() )
            {
                mMatchPlayers.push_back( tempPlayer );
                temp.pop_back();

                break;
            }
        }


        for( size_t x=0; x < playersInTeam.size(); x++ )
        {
            std::shared_ptr< Player > tempPlayer = ( playersInTeam[ x ] );

            if( tempPlayer->getPlayerCA() == temp.back() && !isPlayerInSub( (tempPlayer) ) && !isPlayerInMatch( (tempPlayer) ) && !tempPlayer->isInjured() )
            {
                mSubMatchPlayers.push_back( tempPlayer );
                temp.pop_back();

                break;
            }
        }
    }


}

int Club::generateRandomNumber( int lower, int upper )
{
   return ( qrand () % ( upper - lower + 1 ) ) + lower;
}

std::vector< std::shared_ptr< Player > > Club::getMatchPlayers()
{
    return mMatchPlayers;
}

std::vector< std::shared_ptr< Player > > Club::getSubMatchPlayers()
{
    return mSubMatchPlayers;
}

void Club::removePlayer( std::shared_ptr< Player > player )
{
    int index = 0;
    for( size_t i=0; mAllPlayersInClub.size(); i++ )
    {
        if( player == mAllPlayersInClub[i] )
        {
            mAllPlayersInClub.erase( mAllPlayersInClub.begin() + index );
            increaseWageBudget( player->getPlayerWage() );
            mClubValue -= player->getPlayerValue();
            player->releasePlayer();
            break;
        }
        index++;
    }
}

unsigned Club::getTransferBudget()
{
    return mTransferBudget;
}

int Club::getClubReputation()
{
    return mClubReputation;
}

void Club::PlayersDevelopment()
{
    for( size_t i=0; i<mAllPlayersInClub.size(); i++ )
    {
        std::shared_ptr< Player > tempPlayer = ( mAllPlayersInClub[ i ] );

        unsigned int tAbilityDifference = tempPlayer->getPlayerPA()- tempPlayer->getPlayerCA();
        unsigned int tPlayerBase = (mTrainingFacilities * tAbilityDifference) / tempPlayer->getPlayerAge();

        if( tempPlayer->isInjured() )
        {
            tPlayerBase = ( -1000 ) / mTrainingFacilities;
        }

        if( tAbilityDifference > 0 ) // the player can improve him skills
        {
            if( tempPlayer->getPlayerPosition() == "GK" )
            {
                tempPlayer->PlayerDevelopAttributes( "Reflexes" , tPlayerBase );
            }
            else
            {
                tempPlayer->PlayerDevelopAttributes( "Tackling", tPlayerBase );
                tempPlayer->PlayerDevelopAttributes( "Passing", tPlayerBase );
                tempPlayer->PlayerDevelopAttributes( "Technique", tPlayerBase );
                tempPlayer->PlayerDevelopAttributes( "Pace", tPlayerBase );
                tempPlayer->PlayerDevelopAttributes( "Finishing", tPlayerBase );
            }
        }
        else
        {

        }
    }


    for( size_t i=0; i<mAllPlayersInYouthClub.size(); i++ )
    {
        std::shared_ptr< Player > tempPlayer = ( mAllPlayersInYouthClub[ i ] );

        unsigned int tAbilityDifference = tempPlayer->getPlayerPA()- tempPlayer->getPlayerCA();
        unsigned int tPlayerBase = ( mYouthTrainingFacilitiesLevel * tAbilityDifference ) / tempPlayer->getPlayerAge();

        if( tempPlayer->isInjured() )
        {
            tPlayerBase = ( -1000 ) / mYouthTrainingFacilitiesLevel;
        }

        if( tAbilityDifference > 0 ) // the player can improve him skills
        {
            if( tempPlayer->getPlayerPosition() == "GK" )
            {
                tempPlayer->PlayerDevelopAttributes( "Reflexes", tPlayerBase );
            }
            else
            {
                tempPlayer->PlayerDevelopAttributes( "Tackling", tPlayerBase );
                tempPlayer->PlayerDevelopAttributes( "Passing", tPlayerBase );
                tempPlayer->PlayerDevelopAttributes( "Technique", tPlayerBase );
                tempPlayer->PlayerDevelopAttributes( "Pace", tPlayerBase );
                tempPlayer->PlayerDevelopAttributes( "Finishing", tPlayerBase );
            }
        }
        else
        {

        }
    }
}
