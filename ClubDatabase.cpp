#include "ClubDatabase.h"
#include "Manager.h"
#include <memory>
#include <algorithm>

ClubDatabase::ClubDatabase()
{

}

ClubDatabase::~ClubDatabase()
{

}

int ClubDatabase::generateRandomNumber( unsigned lower, unsigned upper )
{
   return ( qrand() % ( upper - lower + 1 ) ) + lower;
}

int ClubDatabase::generatePlayerValue( unsigned lower, unsigned upper )
{
    if( upper > 100 )
        upper = 100;

    if( lower >= upper )
        return lower;

   return ( qrand() % ( upper - lower + 1 ) ) + lower;
}

int ClubDatabase::getCalculatePlayerValue()
{
    return mPlayerValue;
}

unsigned ClubDatabase::getLeagueReputation( unsigned pLeagueReputation )
{
    unsigned repu;

    if( pLeagueReputation >= 900 )
        repu = 40;
    else if( pLeagueReputation >= 800 && pLeagueReputation < 900 )
        repu = 35;
    else if( pLeagueReputation >= 700 && pLeagueReputation < 800)
        repu = 30;
    else if( pLeagueReputation >= 600 && pLeagueReputation < 700)
        repu = 25;
    else if( pLeagueReputation >= 500 && pLeagueReputation < 600)
        repu = 20;
    else if( pLeagueReputation >= 400 && pLeagueReputation < 500)
        repu = 15;
    else if( pLeagueReputation >= 300 && pLeagueReputation < 400)
        repu = 10;
    else if( pLeagueReputation >= 200 && pLeagueReputation < 300)
        repu = 5;
    else if( pLeagueReputation >= 100 && pLeagueReputation < 200)
        repu = 2;
    else
        repu = 1;


    return repu;
}

unsigned ClubDatabase::getClubReputation( unsigned pClubReputation )
{
    unsigned ClubRepu;

    if( pClubReputation >= 900 )
        ClubRepu = 200;
    else if( pClubReputation >= 850 && pClubReputation < 900 )
        ClubRepu = 150;
    else if( pClubReputation >= 800 && pClubReputation < 850 )
        ClubRepu = 125;
    else if( pClubReputation >= 750 && pClubReputation < 800)
        ClubRepu = 100;
    else if( pClubReputation >= 700 && pClubReputation < 750)
        ClubRepu = 75;
    else if( pClubReputation >= 600 && pClubReputation < 700)
        ClubRepu = 50;
    else if( pClubReputation >= 500 && pClubReputation < 600)
        ClubRepu = 35;
    else if( pClubReputation >= 400 && pClubReputation < 500)
        ClubRepu = 20;
    else if( pClubReputation >= 300 && pClubReputation < 400)
        ClubRepu = 15;
    else if( pClubReputation >= 200 && pClubReputation < 300)
        ClubRepu = 10;
    else if( pClubReputation >= 100 && pClubReputation < 200)
        ClubRepu = 5;
    else
        ClubRepu = 1;

    return ClubRepu;
}

void ClubDatabase::GeneratePlayersForClub( QString position, unsigned number, std::shared_ptr< Club > Club, unsigned leagueReputation )
{
    for( unsigned i=0; i < number; i++ )
    {
        unsigned lowAttribute = std::lround( std::ceil( ( ( Club->getClubReputation() ) / 20) ) );
        unsigned highAttribute = std::lround( std::ceil( ( ( Club->getClubReputation() ) / 10) ) );

        unsigned ClubRepu = getClubReputation( Club->getClubReputation() );
        unsigned repu = getLeagueReputation( leagueReputation );

        unsigned baseSalary = ( Club->getMaxWageBudget() / 100000 );

        unsigned day = generateRandomNumber( 1, 30 );
        unsigned month = generateRandomNumber( 1, 12 );
        unsigned year = generateRandomNumber( 1985, 2002 );

        unsigned expires = generateRandomNumber( 2020, 2025 );

        QString pFullName = getRandomPlayerByCountry( Club->getClubCountry() );
        QString contract_expires = "30.6." + QString::number( expires );

        unsigned reflexes = 0;
        unsigned tackling = 0;
        unsigned passing = 0;
        unsigned pace = 0;
        unsigned technique = 0;
        unsigned finishing = 0;

        unsigned CA = 0;
        unsigned PA = 0;

        unsigned InterestTransfer = 0;
        unsigned base = 100;

        unsigned pPlayerForm = generateRandomNumber( 1, 10 ) * 10;

        if( position == "GK" )
        {
            reflexes = generatePlayerValue( lowAttribute+5, highAttribute+5 );

            CA = reflexes;
            base = reflexes * ( reflexes / 8 ) * reflexes;

            InterestTransfer = ( CA * 100 ) / 10 + pPlayerForm;
        }
        else
        {
            if( year <= 1990 )
            {
                pace -= 20;
            }

            if( position == "DR" || position == "DL" )
            {
                tackling = generatePlayerValue( lowAttribute+20, highAttribute+5 );
                passing = generatePlayerValue( lowAttribute+10, highAttribute );
                pace = generatePlayerValue( lowAttribute+20, highAttribute );
                technique = generatePlayerValue( lowAttribute+15, highAttribute );
                finishing = generatePlayerValue( lowAttribute, highAttribute-10 );

                base = ( ( tackling / 10 ) * tackling + passing + pace + technique + finishing ) * tackling;
            }
            else if( position == "DC" )
            {
                tackling = generatePlayerValue( lowAttribute+25, highAttribute+5 );
                passing = generatePlayerValue( lowAttribute-10, highAttribute-15 );
                pace = generatePlayerValue( lowAttribute, highAttribute );
                technique = generatePlayerValue( lowAttribute, highAttribute-10 );
                finishing = generatePlayerValue( lowAttribute, highAttribute-20 );

                base = ( ( tackling / 10) * tackling + passing + pace + technique + finishing ) * tackling;
            }
            else if( position == "AMR" || position == "AML" )
            {
                tackling = generatePlayerValue( lowAttribute, highAttribute-20 );
                passing = generatePlayerValue( lowAttribute+10, highAttribute );
                pace = generatePlayerValue( lowAttribute+25, highAttribute+5 );
                technique = generatePlayerValue( lowAttribute+20, highAttribute+5 );
                finishing = generatePlayerValue( lowAttribute, highAttribute-5 );

                base = ( tackling + passing + pace * ( pace / 10 ) + technique + finishing ) * pace;
            }
            else if( position == "MC" )
            {
                tackling = generatePlayerValue( lowAttribute+10, highAttribute-5 );
                passing = generatePlayerValue( lowAttribute+20, highAttribute+10 );
                pace = generatePlayerValue( lowAttribute+10, highAttribute );
                technique = generatePlayerValue( lowAttribute+5, highAttribute );
                finishing = generatePlayerValue( lowAttribute+5, highAttribute );

                base = ( tackling + passing * ( passing / 10 ) + pace + technique + finishing ) * passing;
            }
            else if( position == "AMC" )
            {
                tackling = generatePlayerValue( lowAttribute, highAttribute-10 );
                passing = generatePlayerValue( lowAttribute+25, highAttribute+5 );
                pace = generatePlayerValue( lowAttribute+10, highAttribute );
                technique = generatePlayerValue( lowAttribute+15, highAttribute );
                finishing = generatePlayerValue( lowAttribute, highAttribute-10 );

                base = ( tackling + passing * ( passing  /10 ) + pace + technique + finishing ) * passing;
            }
            else if( position == "FC" )
            {
                tackling = generatePlayerValue( lowAttribute-10, highAttribute-10 );
                passing = generatePlayerValue( lowAttribute, highAttribute-15 );
                pace = generatePlayerValue( lowAttribute+20, highAttribute );
                technique = generatePlayerValue( lowAttribute+10, highAttribute );
                finishing = generatePlayerValue( lowAttribute+25, highAttribute+5 );

                base = ( tackling + passing + pace + technique + finishing * ( finishing / 10) ) * finishing;
            }

            CA = ( tackling + passing + pace + technique + finishing ) / 5;
            InterestTransfer = ( CA * 100 ) / 10 + pPlayerForm;
        }

        PA = ( generateRandomNumber( CA, 100 ) );
        unsigned ageDivide = ( 2020 - year ) * 12000;
        unsigned temp = ( CA * repu * base );
        unsigned pPlayerValue = ( ( temp + ( ( ClubRepu * temp * base ) / 10000 ) ) / ageDivide ) * 50;

        pPlayerValue = ( pPlayerValue / 10000 ) * 10000;
        if( pPlayerValue <= 0 )
            pPlayerValue = 10000;

        unsigned playerSalary = baseSalary * CA * pPlayerForm;
        Club->increaseWageBudget( playerSalary );
        Club->changeClubValue( pPlayerValue );

        std::shared_ptr<Player> pPlayer = std::shared_ptr<Player>( new Player( pFullName, position, (Club), contract_expires, QDate( year, month, day ), pPlayerValue, playerSalary, pPlayerForm ) );


        pPlayer->setPlayerAttributes( reflexes, tackling, passing, technique, pace, finishing );
        pPlayer->calculateCA();
        pPlayer->setPlayerPA( PA );
        pPlayer->setAskingPrice( 0 );
        pPlayer->setTransferList( false );
        pPlayer->setPlayerNationality( Club->getClubCountry() );


        pPlayer->setMinimumInterestReputation( InterestTransfer );

        if( Club->getClubCountry() == "Turkey" )
            pPlayer->setFacePath( getHispanicPlayer() );
        else
            pPlayer->setFacePath( getEuropePlayer() );

        Club->addPlayerToClub( (pPlayer) );
    }

    /*
    GenerateYouthPlayersForClub("GK", Club, leagueReputation);
    GenerateYouthPlayersForClub("DL", Club, leagueReputation);
    GenerateYouthPlayersForClub("DC", Club, leagueReputation);
    GenerateYouthPlayersForClub("DR", Club, leagueReputation);
    GenerateYouthPlayersForClub("MC", Club, leagueReputation);
    GenerateYouthPlayersForClub("AML", Club, leagueReputation);
    GenerateYouthPlayersForClub("AMC", Club, leagueReputation);
    GenerateYouthPlayersForClub("AMR", Club, leagueReputation);
    GenerateYouthPlayersForClub("FC", Club, leagueReputation);
    */
}

void ClubDatabase::GenerateYouthPlayersForClub( QString position, std::shared_ptr< Club > Club, unsigned leagueReputation )
{
    unsigned lowAttribute = std::lround( std::ceil( ( ( Club->getClubReputation() ) / 25 ) ) );
    unsigned highAttribute = std::lround( std::ceil( ( ( Club->getClubReputation() ) / 15 ) ) );

    unsigned ClubRepu = getClubReputation( Club->getClubReputation() );
    unsigned repu = getLeagueReputation( leagueReputation );

    int baseSalary = ( Club->getMaxWageBudget() / 1000000 );

    unsigned day = generateRandomNumber( 1, 30 );
    unsigned month = generateRandomNumber( 1, 12 );
    unsigned year = generateRandomNumber( 2002, 2005 );

    unsigned expires = generateRandomNumber( 2020, 2025 );

    QString pFullName = getRandomPlayerByCountry( Club->getClubCountry() );
    QString contract_expires = "30.6." + QString::number( expires );

    unsigned reflexes = 0;
    unsigned tackling = 0;
    unsigned passing = 0;
    unsigned pace = 0;
    unsigned technique = 0;
    unsigned finishing = 0;

    unsigned CA = 0;
    unsigned PA = 0;

    unsigned InterestTransfer = 0;
    unsigned base = 100;

    unsigned pPlayerForm = generateRandomNumber( 1, 10 ) * 10;

    if( position == "GK" )
    {
        reflexes = generatePlayerValue( lowAttribute+5, highAttribute+5 );

        CA = reflexes;
        base = reflexes * ( reflexes / 8 ) * reflexes;

        InterestTransfer = ( CA * 100 ) / 10 + pPlayerForm;
    }
    else
    {
        if( year <= 1990 )
        {
            pace -= 20;
        }

        if( position == "DR" || position == "DL" )
        {
            tackling = generatePlayerValue( lowAttribute+20, highAttribute+5 );
            passing = generatePlayerValue( lowAttribute+10, highAttribute );
            pace = generatePlayerValue( lowAttribute+20, highAttribute );
            technique = generatePlayerValue( lowAttribute+15, highAttribute );
            finishing = generatePlayerValue( lowAttribute, highAttribute-10 );

            base = ( ( tackling / 10 ) * tackling + passing + pace + technique + finishing ) * tackling;
        }
        else if( position == "DC" )
        {
            tackling = generatePlayerValue( lowAttribute+25, highAttribute+5 );
            passing = generatePlayerValue( lowAttribute-10, highAttribute-15 );
            pace = generatePlayerValue( lowAttribute, highAttribute );
            technique = generatePlayerValue( lowAttribute, highAttribute-10 );
            finishing = generatePlayerValue( lowAttribute, highAttribute-20 );

            base = ( ( tackling / 10 ) * tackling + passing + pace + technique + finishing ) * tackling;
        }
        else if( position == "AMR" || position == "AML" )
        {
            tackling = generatePlayerValue( lowAttribute, highAttribute-20 );
            passing = generatePlayerValue( lowAttribute+10, highAttribute );
            pace = generatePlayerValue( lowAttribute+25, highAttribute+5 );
            technique = generatePlayerValue( lowAttribute+20, highAttribute+5 );
            finishing = generatePlayerValue( lowAttribute, highAttribute-5 );

            base = ( tackling + passing + pace * ( pace / 10 ) + technique + finishing ) * pace;
        }
        else if( position == "MC" )
        {
            tackling = generatePlayerValue( lowAttribute+10, highAttribute-5 );
            passing = generatePlayerValue( lowAttribute+20, highAttribute+10 );
            pace = generatePlayerValue( lowAttribute+10, highAttribute );
            technique = generatePlayerValue( lowAttribute+5, highAttribute );
            finishing = generatePlayerValue( lowAttribute+5, highAttribute );

            base = ( tackling + passing * ( passing / 10 ) + pace + technique + finishing ) * passing;
        }
        else if( position == "AMC" )
        {
            tackling = generatePlayerValue( lowAttribute, highAttribute-10 );
            passing = generatePlayerValue( lowAttribute+25, highAttribute+5 );
            pace = generatePlayerValue( lowAttribute+10, highAttribute );
            technique = generatePlayerValue( lowAttribute+15, highAttribute );
            finishing = generatePlayerValue( lowAttribute, highAttribute-10 );

            base = ( tackling + passing * ( passing / 10 ) + pace + technique + finishing ) * passing;
        }
        else if( position == "FC" )
        {
            tackling = generatePlayerValue( lowAttribute-10, highAttribute-10 );
            passing = generatePlayerValue( lowAttribute, highAttribute-15 );
            pace = generatePlayerValue( lowAttribute+20, highAttribute );
            technique = generatePlayerValue( lowAttribute+10, highAttribute );
            finishing = generatePlayerValue( lowAttribute+25, highAttribute+5 );

            base = ( tackling + passing + pace + technique + finishing * ( finishing / 10 ) ) * finishing;
        }

        CA = ( tackling + passing + pace + technique + finishing ) / 5;
        InterestTransfer = ( CA * 100 ) / 10 + pPlayerForm;
    }

    PA = ( generateRandomNumber( CA, 100 ) );
    unsigned ageDivide = ( 2020 - year ) * 12000;
    unsigned temp = ( CA * repu * base );
    unsigned pPlayerValue = ( (temp + ( ( ClubRepu * temp * base ) / 10000 ) ) / ageDivide ) * 25;

    pPlayerValue = ( pPlayerValue / 10000 ) * 1000;
    if( pPlayerValue <= 0 )
        pPlayerValue = 1000;

    unsigned playerSalary = baseSalary * CA * pPlayerForm;
    Club->increaseWageBudget( playerSalary );
    Club->changeClubValue( pPlayerValue );

    std::shared_ptr< Player > pPlayer = std::shared_ptr< Player >(new Player( pFullName, position, (Club), contract_expires, QDate(year, month, day), pPlayerValue, playerSalary, pPlayerForm ));
    pPlayer->setPlayerAttributes( reflexes, tackling, passing, technique, pace, finishing );
    pPlayer->calculateCA();
    pPlayer->setPlayerPA( PA );
    pPlayer->setAskingPrice( 0 );
    pPlayer->setTransferList( false );
    pPlayer->setPlayerNationality( Club->getClubCountry() );


    pPlayer->setMinimumInterestReputation( InterestTransfer );
    /*
    if(Club->getClubCountry() == "Turkey")
        pPlayer->setFacePath(getHispanicPlayer());
    else
        pPlayer->setFacePath(getEuropePlayer());

    Club->addYouthPlayerToClub(pPlayer);
    */
}

std::shared_ptr< Player > ClubDatabase::GenerateFreePlayers( QString position )
{
    unsigned lowAttribute = generateRandomNumber( 10, 50 );
    unsigned highAttribute = generateRandomNumber( 50, 80 );

    unsigned day = generateRandomNumber( 1, 30 );
    unsigned month = generateRandomNumber( 1, 12 );
    unsigned year = generateRandomNumber( 1982, 2000 );

    QString tPlayerCountry = getRandomCountry();
    QString pFullName = getRandomPlayerByCountry( tPlayerCountry );
    QString contract_expires = "Free";

    unsigned reflexes = 0;
    unsigned tackling = 0;
    unsigned passing = 0;
    unsigned pace = 0;
    unsigned technique = 0;
    unsigned finishing = 0;

    unsigned CA = 0;
    unsigned PA = 0;

    unsigned InterestTransfer = 0;
    unsigned base;

    unsigned pPlayerForm = generateRandomNumber( 1, 10 ) * 10;

    if( position == "GK" )
    {
        reflexes = generatePlayerValue( lowAttribute+5, highAttribute+5 );

        CA = reflexes;
        base = reflexes * ( reflexes / 10 ) * reflexes;

        InterestTransfer = ( CA * 100 ) / 10 + pPlayerForm;
    }
    else
    {
        if( year <= 1990 )
        {
            pace -= 20;
        }

        if( position == "DR" || position == "DL" )
        {
            tackling = generatePlayerValue( lowAttribute+20, highAttribute+5 );
            passing = generatePlayerValue( lowAttribute+10, highAttribute );
            pace = generatePlayerValue( lowAttribute+20, highAttribute );
            technique = generatePlayerValue( lowAttribute+15, highAttribute );
            finishing = generatePlayerValue( lowAttribute, highAttribute-10 );

            base = ( ( tackling / 10 ) * tackling + passing + pace + technique + finishing ) * tackling;
        }
        else if( position == "DC" )
        {
            tackling = generatePlayerValue( lowAttribute+25, highAttribute+5 );
            passing = generatePlayerValue( lowAttribute-10, highAttribute-15 );
            pace = generatePlayerValue( lowAttribute, highAttribute );
            technique = generatePlayerValue( lowAttribute, highAttribute-10 );
            finishing = generatePlayerValue( lowAttribute, highAttribute-20 );

            base = ( ( tackling / 10 ) * tackling + passing + pace + technique + finishing ) * tackling;
        }
        else if( position == "AMR" || position == "AML" )
        {
            tackling = generatePlayerValue( lowAttribute, highAttribute-20 );
            passing = generatePlayerValue( lowAttribute+10, highAttribute );
            pace = generatePlayerValue( lowAttribute+25, highAttribute+5 );
            technique = generatePlayerValue( lowAttribute+20, highAttribute+5 );
            finishing = generatePlayerValue( lowAttribute, highAttribute-5 );

            base = ( tackling + passing + pace * ( pace / 10 ) + technique + finishing ) * pace;
        }
        else if( position == "MC" )
        {
            tackling = generatePlayerValue( lowAttribute+10, highAttribute-5 );
            passing = generatePlayerValue( lowAttribute+20, highAttribute+10 );
            pace = generatePlayerValue( lowAttribute+10, highAttribute );
            technique = generatePlayerValue( lowAttribute+5, highAttribute );
            finishing = generatePlayerValue( lowAttribute+5, highAttribute );

            base = ( tackling + passing * ( passing / 10 ) + pace + technique + finishing ) * passing;
        }
        else if( position == "AMC" )
        {
            tackling = generatePlayerValue( lowAttribute, highAttribute-10 );
            passing = generatePlayerValue( lowAttribute+25, highAttribute+5 );
            pace = generatePlayerValue( lowAttribute+10, highAttribute );
            technique = generatePlayerValue( lowAttribute+15, highAttribute );
            finishing = generatePlayerValue( lowAttribute, highAttribute-10 );

            base = ( tackling + passing * ( passing / 10 ) + pace + technique + finishing ) * passing;
        }
        else if( position == "FC" )
        {
            tackling = generatePlayerValue( lowAttribute-10, highAttribute-10 );
            passing = generatePlayerValue( lowAttribute, highAttribute-15 );
            pace = generatePlayerValue( lowAttribute+20, highAttribute );
            technique = generatePlayerValue( lowAttribute+10, highAttribute );
            finishing = generatePlayerValue( lowAttribute+25, highAttribute+5 );

            base = ( tackling + passing + pace + technique + finishing * ( finishing / 10 ) ) * finishing;
        }
        CA = ( tackling + passing + pace + technique + finishing ) / 5;
        InterestTransfer = ( CA * 100 ) / 10;
    }

    PA = ( generateRandomNumber( CA, 100 ) );

    std::shared_ptr< Player > pPlayer = std::shared_ptr< Player >(new Player( pFullName, position, nullptr, "Free", QDate( year, month, day ), 0, 0, pPlayerForm ));
    pPlayer->setPlayerAttributes( reflexes, tackling, passing, technique, pace, finishing );
    pPlayer->calculateCA();
    pPlayer->setPlayerPA( PA );
    pPlayer->setTransferList( false );
    pPlayer->setPlayerNationality( tPlayerCountry );
    pPlayer->setAskingPrice( 0 );

    pPlayer->setMinimumInterestReputation( InterestTransfer );

    pPlayer->setFacePath( getMixedRacePlayer() );

    return pPlayer;
}

std::shared_ptr< Club > ClubDatabase::addClubToGame( QString pClubName, unsigned pClubReputation, unsigned pTransferBudget, unsigned pWageBudget, QString pLeagueName, unsigned pLeagueReputation, QString pLeagueCountry )
{
    unsigned tTrainingFacilities = 0;
    unsigned tYouthTrainingFacilities = 0;
    unsigned tStadiumCapacity = 0;

    tTrainingFacilities = ( pClubReputation / 100 ) * 2;
    tYouthTrainingFacilities = ( pClubReputation / 100 ) * 2;
    tStadiumCapacity = ( pClubReputation*pClubReputation ) / 10;

    std::shared_ptr< Club > pClub = std::shared_ptr< Club >( new Club( pClubName, pClubReputation, pLeagueName, pTransferBudget, pLeagueCountry, tTrainingFacilities, tYouthTrainingFacilities, tStadiumCapacity ));
    pClub->setMaxWageBudget( pWageBudget );

    GeneratePlayersForClub( "GK", 3, pClub, pLeagueReputation );
    GeneratePlayersForClub( "DC", 4, pClub, pLeagueReputation );
    GeneratePlayersForClub( "DR", 2, pClub, pLeagueReputation );
    GeneratePlayersForClub( "DL", 2, pClub, pLeagueReputation );
    GeneratePlayersForClub( "AMR", 2, pClub, pLeagueReputation );
    GeneratePlayersForClub( "AML", 2, pClub, pLeagueReputation );
    GeneratePlayersForClub( "MC", 4, pClub, pLeagueReputation );
    GeneratePlayersForClub( "AMC", 2, pClub, pLeagueReputation );
    GeneratePlayersForClub( "FC", 3, pClub, pLeagueReputation );


    std::shared_ptr< Manager >tempManager = std::shared_ptr< Manager >( new Manager( getRandomPlayerByCountry(pLeagueCountry ), pLeagueCountry, pClubName ) );
    tempManager->setManagerAttributes(generateRandomNumber((pClubReputation/12), (pClubReputation/10)), generateRandomNumber((pClubReputation/12), (pClubReputation/10)), generateRandomNumber((pClubReputation/12), (pClubReputation/10)));

    pClub->setManager( tempManager );

    allClubsInGame.push_back( pClub );

    int ClubReputation = pClub->getClubReputation() / 10 - 10;

    for( size_t i=0; i < pClub->getPlayersInClub().size(); i++ )
    {
        std::shared_ptr< Player > tempPlayer = ( pClub->getPlayersInClub()[ i ] );

        if( tempPlayer->getPlayerPosition() == "GK" )
        {
            if( ( ( tempPlayer->getPlayerCA()+ tempPlayer->getPlayerForm() / 8 ) < ClubReputation ) && ( tempPlayer->getPlayerReflexes()+ tempPlayer->getPlayerForm() / 8 < ClubReputation ) )
            {
                tempPlayer->setTransferList( true );
                unsigned askingPrice = ( ( ( tempPlayer->getPlayerValue() * tempPlayer->getPlayerForm() ) / 100 + (tempPlayer->getPlayerValue() * tempPlayer->getPlayerPA() ) / ( 2020 - tempPlayer->getPlayerBirthDay().year() ) ) / 100000 ) * 15000;
                tempPlayer->setAskingPrice( askingPrice );
                pClub->addTransferList( tempPlayer );
            }
        }
        if( ( tempPlayer->getPlayerPosition() == "DR" ) || ( tempPlayer->getPlayerPosition() == "DL" ) )
        {
            if( ( ( tempPlayer->getPlayerCA()+ tempPlayer->getPlayerForm() / 10 ) < ClubReputation ) && ( tempPlayer->getPlayerTackling()+ tempPlayer->getPlayerForm() / 10 < ClubReputation ) )
            {
                tempPlayer->setTransferList( true );
                unsigned askingPrice = ( ( ( tempPlayer->getPlayerValue() * tempPlayer->getPlayerForm() ) / 100 + ( tempPlayer->getPlayerValue() * tempPlayer->getPlayerPA() ) / ( 2020 - tempPlayer->getPlayerBirthDay().year())) /100000) * 15000;
                tempPlayer->setAskingPrice( askingPrice );
                pClub->addTransferList( tempPlayer );
            }
        }
        if( tempPlayer->getPlayerPosition() == "DC" )
        {
            if( ( ( tempPlayer->getPlayerCA()+ tempPlayer->getPlayerForm() / 10 ) < ClubReputation ) && ( tempPlayer->getPlayerTackling()+ tempPlayer->getPlayerForm() / 10) < ClubReputation )
            {
                tempPlayer->setTransferList( true );
                unsigned askingPrice = ( ( ( tempPlayer->getPlayerValue() * tempPlayer->getPlayerForm() ) / 100 + ( tempPlayer->getPlayerValue() * tempPlayer->getPlayerPA() ) / ( 2020 - tempPlayer->getPlayerBirthDay().year() ) ) / 100000 ) * 15000;
                tempPlayer->setAskingPrice( askingPrice );
                pClub->addTransferList( tempPlayer );
            }
        }

        if( tempPlayer->getPlayerPosition() == "MC" )
        {
            if( ( ( tempPlayer->getPlayerCA()+ tempPlayer->getPlayerForm() / 10 ) < ClubReputation ) && ( tempPlayer->getPlayerPassing()+ tempPlayer->getPlayerForm() / 10 ) < ClubReputation )
            {
                tempPlayer->setTransferList( true );
                unsigned askingPrice = ( ( ( tempPlayer->getPlayerValue() * tempPlayer->getPlayerForm() ) / 100 + ( tempPlayer->getPlayerValue() * tempPlayer->getPlayerPA() ) / ( 2020 - tempPlayer->getPlayerBirthDay().year() ) ) / 100000 ) * 15000;
                tempPlayer->setAskingPrice( askingPrice );
                pClub->addTransferList( tempPlayer );
            }
        }

        if( (tempPlayer->getPlayerPosition() == "AMR" ) || (tempPlayer->getPlayerPosition() == "AML" ) )
        {
            if( (tempPlayer->getPlayerCA()+ tempPlayer->getPlayerForm()/10) < ClubReputation && (tempPlayer->getPlayerTechnique()+ tempPlayer->getPlayerForm()/10) < ClubReputation)
            {
                tempPlayer->setTransferList(true);
                unsigned askingPrice = ( ( ( tempPlayer->getPlayerValue() * tempPlayer->getPlayerForm() ) / 100 + ( tempPlayer->getPlayerValue() * tempPlayer->getPlayerPA() ) / ( 2020 - tempPlayer->getPlayerBirthDay().year() ) ) / 100000 ) * 15000;
                tempPlayer->setAskingPrice( askingPrice );
                pClub->addTransferList( tempPlayer );
            }
        }

        if( tempPlayer->getPlayerPosition() == "AMC" )
        {
            if( ( tempPlayer->getPlayerCA()+ tempPlayer->getPlayerForm() / 10) < ClubReputation && ( tempPlayer->getPlayerPassing()+ tempPlayer->getPlayerForm() / 10) < ClubReputation )
            {
                tempPlayer->setTransferList( true );
                unsigned askingPrice = ( ( ( tempPlayer->getPlayerValue() * tempPlayer->getPlayerForm() ) / 100 + ( tempPlayer->getPlayerValue() * tempPlayer->getPlayerPA() ) / ( 2020 - tempPlayer->getPlayerBirthDay().year() ) ) / 100000 ) * 15000;
                tempPlayer->setAskingPrice( askingPrice );
                pClub->addTransferList( tempPlayer );
            }
        }

        if( tempPlayer->getPlayerPosition() == "FC" )
        {
            if( (tempPlayer->getPlayerCA()+ tempPlayer->getPlayerForm()/10) < ClubReputation  && ( ( tempPlayer->getPlayerFinishing()+ tempPlayer->getPlayerForm() / 10) < ClubReputation) )
            {
                tempPlayer->setTransferList(true);
                unsigned askingPrice = ( ( ( tempPlayer->getPlayerValue() * tempPlayer->getPlayerForm() ) / 100 + ( tempPlayer->getPlayerValue() *  tempPlayer->getPlayerPA() ) / ( 2020 - tempPlayer->getPlayerBirthDay().year() ) ) / 100000 ) * 15000;
                tempPlayer->setAskingPrice( askingPrice );
                pClub->addTransferList( tempPlayer );
            }
        }
    }

    return pClub;
}
