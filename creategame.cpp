#include "creategame.h"

CreateGame::CreateGame() : mTeamDatabase(nullptr)
{
     qDebug() << "CreateGame()" << endl;

     mDay = 1;
     mMonth = 6;
     mYear = 2020;

     mFullDate = QString::number(mDay) + "." + QString::number(mMonth) + "." + QString::number(mYear);
}

CreateGame::~CreateGame()
{
    delete mTeamDatabase;
}

QString CreateGame::getFullDate()
{
    return mFullDate;
}

void CreateGame::addFreePlayer(Player* player)
{
    mFreePlayers.push_back(player);
}

std::vector<Player*> CreateGame::getFreePlayers()
{
    return mFreePlayers;
}

void CreateGame::createDatabase()
{
    for(auto i : mLeagueList)
    {
        QSqlQuery leagueSQL("SELECT * FROM LEAGUES");
        int leagues = leagueSQL.record().indexOf("LEAGUES");
        int leagueReputation = leagueSQL.record().indexOf("REPUTATION");
        int leagueCountry = leagueSQL.record().indexOf("COUNTRY");
        int leagueDivision = leagueSQL.record().indexOf("DIVISION");

        while (leagueSQL.next())
        {
           QString pLeagueName = leagueSQL.value(leagues).toString();
           QString pLeagueReputation = leagueSQL.value(leagueReputation).toString();
           QString pLeagueCountry = leagueSQL.value(leagueCountry).toString();
           QString pLeagueDivision = leagueSQL.value(leagueDivision).toString();

            if(i == pLeagueName)
            {
                League* pLeague = new League(pLeagueName, pLeagueCountry, pLeagueReputation.toInt(), pLeagueDivision.toInt());


                QSqlQuery teamSQL("SELECT * FROM "+pLeagueCountry+ "_TEAMS");

                int team_name = teamSQL.record().indexOf("TEAM_NAME");
                int reputation = teamSQL.record().indexOf("REPUTATION");
                int transfer_budget = teamSQL.record().indexOf("TRANSFER_BUDGET");
                int wage_budget = teamSQL.record().indexOf("WAGE_BUDGET");
                int league_name = teamSQL.record().indexOf("LEAGUE_NAME");

                while (teamSQL.next())
                {
                   QString pTeamName = teamSQL.value(team_name).toString();
                   QString pTeamReputation = teamSQL.value(reputation).toString();
                   QString pTransferBudget = teamSQL.value(transfer_budget).toString();
                   QString pWageBudget = teamSQL.value(wage_budget).toString();
                   QString pLeagueName = teamSQL.value(league_name).toString();

                   pLeague->addTeamToLeague(mTeamDatabase->addTeamToGame(pTeamName, pTeamReputation.toInt(), pTransferBudget.toInt(), pWageBudget.toInt(), pLeagueName, pLeagueReputation.toInt(), pLeagueCountry));
                }
                mAllLeaguesInGame.push_back(pLeague);
                pLeague->createLeagueFixtures();
            }

        }
    }

    setScoutPlayers();
    qDebug() << "Game was created" << endl;
}

void CreateGame::setScoutPlayers()
{
    for(auto i : mTeamDatabase->allTeamsInGame)
    {
        if(i->getPlayersInTransferList().size() != 0)
        {
            unsigned long long int maxTransfer = i->getTransferBudget() / i->getPlayersInTransferList().size();
            int clubPoint = i->getTeamAvaragePoint()+5;

            for(auto x : i->getPlayersInTransferList())
            {
                QString position = x->getPlayerPosition();

                for(auto t : mTeamDatabase->allTeamsInGame)
                {
                    if(i->getTeamName() != t->getTeamName())
                    {
                        for(auto m : t->getPlayersInTeam())
                        {
                            unsigned long long int offer = m->getAskingPrice();
                            if(!m->isTransferList())
                                offer = ( ( (( m->getPlayerValue()*m->getPlayerForm() ) /  (2020 - m->getPlayerBirthDay().toInt()) ) + (( m->getPlayerValue()*m->getPlayerPA() ) / (2020 - m->getPlayerBirthDay().toInt())) )/10000 ) * 2500;

                            if( ( (m->getPlayerCA()+m->getPlayerForm()/10) > clubPoint) && (m->getPlayerPosition() == position) && (offer < maxTransfer) )
                            {
                                if(m->getPlayerPosition() == "GK")
                                {
                                    if ( (m->getPlayerCA()+m->getPlayerForm()/10) >= (clubPoint+10))
                                    {
                                        if(m->isTransferList())
                                        {
                                            i->addScoutPlayer(m, offer);
                                            m->addTransferOffer(i, offer);
                                        }
                                        else
                                        {
                                            i->addScoutPlayer(m, maxTransfer);
                                            m->addTransferOffer(i, maxTransfer);
                                        }

                                    }
                                }
                                else
                                {
                                    if(m->isTransferList())
                                    {
                                        i->addScoutPlayer(m, offer);
                                        m->addTransferOffer(i, offer);
                                    }
                                    else
                                    {
                                        i->addScoutPlayer(m, maxTransfer);
                                        m->addTransferOffer(i, maxTransfer);
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

std::vector<Manager*> CreateGame::getAllManagers()
{
    return mAllManagers;
}

std::vector<League*> CreateGame::getAllLeaguesInGame()
{
    return mAllLeaguesInGame;
}

TeamDatabase* CreateGame::getTeamDatabase()
{
    return mTeamDatabase;
}

void CreateGame::prepareDatabase(QString pManagerName, QString pMyTeam, std::vector<QString> pLeagueList)
{
    mManagerName = pManagerName;
    mMyTeam = pMyTeam;
    mLeagueList = pLeagueList;

    mTeamDatabase = new TeamDatabase();

    readCSV();
    setDatabase();
}

void CreateGame::setDatabase()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/temel/Desktop/FM.db");

    if(!mydb.open())
        qDebug() << "failed to open the database" << endl;
    else
        createDatabase();

    mydb.close();
}

void CreateGame::readCSV()
{
    QFile f("C:/Users/temel/Desktop/fm20.csv");
    if (f.open(QIODevice::ReadOnly))
    {
        //file opened successfully
        int i=0;
        while (!f.atEnd())
        {
            i++;

            if(i > 1)
            {
                QByteArray line = f.readLine();

                QString playerSurname = line.split(';')[1];
                QString playerName = line.split(';')[0];
                QString playerCountry = line.split(';')[2].replace("\r\n", "");

                mTeamDatabase->getPlayerDatabase()->addPlayerName(playerName, playerSurname, playerCountry);
            }
        }

        f.close();
    }
    else
    {
        qDebug()<< "file could not open" << endl;
    }

}
