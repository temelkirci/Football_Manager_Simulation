#include "CreateGame.h"
#include <memory>

CreateGame::CreateGame()
{
     mDay = 1;
     mMonth = 6;
     mYear = 2020;

     mFullDate = QString::number(mDay) + "." + QString::number(mMonth) + "." + QString::number(mYear);

     qDebug() << "mFullDate :" << mFullDate << endl;
}

CreateGame::~CreateGame()
{

}

QString CreateGame::getFullDate()
{
    return mFullDate;
}

void CreateGame::addFreePlayer( std::shared_ptr< Player > player )
{
    mFreePlayers.push_back( player );
}

std::vector<std::shared_ptr< Player >> CreateGame::getFreePlayers()
{
    return mFreePlayers;
}

void CreateGame::createDatabase()
{
    for(auto i : mLeagueList)
    {
        QSqlQuery leagueSQL( "SELECT * FROM LEAGUES" );
        int leagues = leagueSQL.record().indexOf( "LEAGUES" );
        int leagueReputation = leagueSQL.record().indexOf( "REPUTATION" );
        int leagueCountry = leagueSQL.record().indexOf( "COUNTRY" );
        int leagueDivision = leagueSQL.record().indexOf( "DIVISION" );

        while ( leagueSQL.next() )
        {
           QString pLeagueName = leagueSQL.value( leagues ).toString();
           QString pLeagueReputation = leagueSQL.value( leagueReputation ).toString();
           QString pLeagueCountry = leagueSQL.value( leagueCountry ).toString();
           QString pLeagueDivision = leagueSQL.value( leagueDivision ).toString();

            if( i == pLeagueName )
            {
                std::shared_ptr< League > pLeague = std::shared_ptr< League >(new League( pLeagueName, pLeagueCountry, pLeagueReputation.toInt(), pLeagueDivision.toInt() ));


                QSqlQuery ClubSQL( "SELECT * FROM " + pLeagueCountry+ "_TEAMS" );

                int Club_name = ClubSQL.record().indexOf( "TEAM_NAME" );
                int reputation = ClubSQL.record().indexOf( "REPUTATION" );
                int transfer_budget = ClubSQL.record().indexOf( "TRANSFER_BUDGET" );
                int wage_budget = ClubSQL.record().indexOf( "WAGE_BUDGET" );
                int league_name = ClubSQL.record().indexOf( "LEAGUE_NAME" );

                while ( ClubSQL.next() )
                {
                   QString pClubName = ClubSQL.value( Club_name ).toString();
                   QString pClubReputation = ClubSQL.value( reputation ).toString();
                   QString pTransferBudget = ClubSQL.value( transfer_budget ).toString();
                   QString pWageBudget = ClubSQL.value( wage_budget ).toString();
                   QString pLeagueName = ClubSQL.value( league_name ).toString();

                   pLeague->addClubToLeague( mClubDatabase->addClubToGame( pClubName, pClubReputation.toInt(), pTransferBudget.toInt(), pWageBudget.toInt(), pLeagueName, pLeagueReputation.toInt(), pLeagueCountry ) );

                   addFreePlayer( mClubDatabase->GenerateFreePlayers( "GK" ) );
                   addFreePlayer( mClubDatabase->GenerateFreePlayers( "DC" ) );
                   addFreePlayer( mClubDatabase->GenerateFreePlayers( "DR" ) );
                   addFreePlayer( mClubDatabase->GenerateFreePlayers( "DL" ) );
                   addFreePlayer( mClubDatabase->GenerateFreePlayers( "AMR" ) );
                   addFreePlayer( mClubDatabase->GenerateFreePlayers( "AML" ) );
                   addFreePlayer( mClubDatabase->GenerateFreePlayers( "MC" ) );
                   addFreePlayer( mClubDatabase->GenerateFreePlayers( "AMC" ) );
                   addFreePlayer( mClubDatabase->GenerateFreePlayers( "FC" ) );
                }
                mAllLeaguesInGame.push_back( pLeague );
                pLeague->createLeagueFixtures();
            }
        }
    }

    setScoutPlayers();
}

void CreateGame::setScoutPlayers()
{
    for( size_t i=0; i < mClubDatabase->allClubsInGame.size(); i++ )
    {
        std::shared_ptr< Club > tempClub = ( mClubDatabase->allClubsInGame[ i ] );

        if( tempClub->getPlayersInTransferList().size() != 0 )
        {
            unsigned maxTransfer = ( ( tempClub->getTransferBudget() / tempClub->getPlayersInTransferList().size() ) / 10000 ) * 10000;

            for( size_t x=0; x < tempClub->getPlayersInTransferList().size(); x++ )
            {
                std::shared_ptr< Player > tempPlayer = ( tempClub->getPlayersInTransferList()[ x ] );

                QString position = tempPlayer->getPlayerPosition();

                for( size_t t=0; t < mClubDatabase->allClubsInGame.size(); t++ )
                {
                    std::shared_ptr< Club > tempAllClub = ( mClubDatabase->allClubsInGame[ i ] );

                    if( tempClub->getClubName() != tempAllClub->getClubName() )
                    {
                        for( size_t m=0; m < tempAllClub->getPlayersInClub().size(); m++ )
                        {
                            std::shared_ptr< Player > tempPlayerInClub = ( tempAllClub->getPlayersInClub()[ m ] );

                            unsigned offer = tempPlayerInClub->getAskingPrice();
                            if( !tempPlayerInClub->isTransferList() )
                                offer = ( ( ( ( tempPlayerInClub->getPlayerValue() * tempPlayerInClub->getPlayerForm() ) /  ( 2020 - tempPlayerInClub->getPlayerBirthDay().year() ) ) + ( ( tempPlayerInClub->getPlayerValue() * tempPlayerInClub->getPlayerPA() ) / ( 2020 - tempPlayerInClub->getPlayerBirthDay().year() ) ) ) / 10000 ) * 2500;

                            if( ( tempClub->getClubReputation() > tempPlayerInClub->getMinimumInterestReputation() ) && ( tempPlayerInClub->getPlayerPosition() == position ) && ( offer < maxTransfer ) )
                            {
                                bool ScoutPlayer = false;

                                if( tempPlayerInClub->getPlayerPosition() == "GK" )
                                {
                                    if ( tempPlayerInClub->getPlayerReflexes() > ( tempClub->getClubReputation() / 12 ) )
                                    {
                                        ScoutPlayer = true;
                                    }
                                }
                                else if( tempPlayerInClub->getPlayerPosition() == "DC" )
                                {
                                    if ( tempPlayerInClub->getPlayerTackling() > (tempClub->getClubReputation() / 10 ) )
                                    {
                                        ScoutPlayer = true;
                                    }
                                }
                                else if( ( tempPlayerInClub->getPlayerPosition() == "DR" ) || ( tempPlayerInClub->getPlayerPosition() == "DL" ) )
                                {
                                    if ( ( tempPlayerInClub->getPlayerTackling() > ( tempClub->getClubReputation() / 10) ) )
                                    {
                                        ScoutPlayer = true;
                                    }
                                }
                                else if( tempPlayerInClub->getPlayerPosition() == "MC" )
                                {
                                    if ( tempPlayerInClub->getPlayerPassing() > ( tempClub->getClubReputation() / 10 ) )
                                    {
                                        ScoutPlayer = true;
                                    }
                                }
                                else if( tempPlayerInClub->getPlayerPosition() == "AMC" )
                                {
                                    if ( tempPlayerInClub->getPlayerPassing() > (tempClub->getClubReputation() / 10 ) )
                                    {
                                        ScoutPlayer = true;
                                    }
                                }
                                else if( ( tempPlayerInClub->getPlayerPosition() == "AMR" ) || ( tempPlayerInClub->getPlayerPosition() == "AML" ) )
                                {
                                    if ( ( tempPlayerInClub->getPlayerTechnique() > ( tempClub->getClubReputation() / 10 ) ) )
                                    {
                                        ScoutPlayer = true;
                                    }
                                }
                                else if( tempPlayerInClub->getPlayerPosition() == "FC" )
                                {
                                    if ( ( tempPlayerInClub->getPlayerFinishing() > ( tempClub->getClubReputation() / 10 ) ) )
                                    {
                                        ScoutPlayer = true;
                                    }
                                }

                                if( ScoutPlayer == true )
                                {
                                    if( tempPlayerInClub->isTransferList() )
                                    {
                                        tempClub->addScoutPlayer( tempPlayerInClub, offer );
                                        tempClub->generateTransferOffer( tempPlayerInClub, offer );
                                    }
                                    else
                                    {
                                        tempClub->addScoutPlayer( tempPlayerInClub, maxTransfer );
                                        tempClub->generateTransferOffer( tempPlayerInClub, maxTransfer );
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

std::vector< std::shared_ptr< Manager > > CreateGame::getAllManagers()
{
    return mAllManagers;
}

std::vector< std::shared_ptr< League > > CreateGame::getAllLeaguesInGame()
{
    return mAllLeaguesInGame;
}

std::shared_ptr< ClubDatabase > CreateGame::getClubDatabase()
{
    return (mClubDatabase);
}

void CreateGame::prepareDatabase(QString pManagerName, QString pMyClub, std::vector<QString> pLeagueList)
{
    mManagerName = pManagerName;
    mMyClub = pMyClub;
    mLeagueList = pLeagueList;

    mClubDatabase = std::shared_ptr< ClubDatabase > (new ClubDatabase());

    readCSV();
    setDatabase();
}

void CreateGame::setDatabase()
{
    mydb = QSqlDatabase::addDatabase( "QSQLITE" );
    mydb.setDatabaseName( "C:/Users/temel/Documents/FM20/FootballManagerSimulation/FM.db" );

    if( !mydb.open() )
        qDebug() << "failed to open the database" << endl;
    else
        createDatabase();

    mydb.close();
}

void CreateGame::readCSV()
{
    QFile f( "C:/Users/temel/Documents/FM20/FootballManagerSimulation/fm20.csv" );
    if ( f.open(QIODevice::ReadOnly ) )
    {
        //file opened successfully
        int i=0;
        while ( !f.atEnd() )
        {
            i++;

            if( i > 1 )
            {
                QByteArray line = f.readLine();

                QString playerSurname = line.split( ';' )[1];
                QString playerName = line.split( ';' )[0];
                QString playerCountry = line.split( ';' )[2].replace( "\r\n", "" );

                mClubDatabase->getPlayerDatabase()->addPlayerName( playerName, playerSurname, playerCountry );
            }
        }

        f.close();
    }
    else
    {
        qDebug()<< "file could not open" << endl;
    }

}
