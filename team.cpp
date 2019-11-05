#include "team.h"

Team::Team()
{

}

Team::Team(QString teamName, int teamReputation, QString pLeagueName, int pTransferBudget, QString pLeagueCountry)
{
    mTeamName = teamName;
    mTeamReputation = teamReputation;
    mTransferBudget = pTransferBudget;
    mTeamLeague = pLeagueName;
    mTeamCountry = pLeagueCountry;

    mWageBudget = 0;
    mTeamValue = 0;

    mMatchPlayers.clear();
    mFormation = QString("4-4-2");
}

void Team::addTransferList(Player* player)
{
    mTransferList.push_back(player);
}

void Team::removeTransferList(Player* player)
{
    for(auto it = mTransferList.begin(); it != mTransferList.end(); ++it)
        if(*it == player)
        {
            mTransferList.erase(it);
            break;
        }
}

std::map<Player*, unsigned long long int> Team::getScoutingPlayers()
{
    return mScoutingPlayers;
}

void Team::setClubPresidentName(QString president)
{
    mPresident = president;
}

QString Team::getClubPresidentName()
{
    return mPresident;
}

void Team::setClubManagerName(QString manager)
{
    mClubManager = manager;
}

QString Team::getClubManagerName()
{
    return mClubManager;
}

void Team::addScoutPlayer(Player* player, unsigned long long int value)
{
    mScoutingPlayers.insert(std::pair<Player*, int>(player, value));
}

unsigned int Team::getTeamAvaragePoint()
{
    mTeamAvarageAbility = 0;

    for(auto i : mAllPlayers)
        mTeamAvarageAbility += i->getPlayerCA();
    return mTeamAvarageAbility/(mAllPlayers.size());
}

std::vector<Player*> Team::getPlayersInTransferList()
{
    return mTransferList;
}

int Team::getTeamSalary()
{
    return mWageBudget;
}

void Team::increaseTransferBudget(unsigned long long int increaseValue)
{
    mTransferBudget += increaseValue;
}

void Team::decreaseTransferBudget(unsigned long long int decreaseValue)
{
    mTransferBudget -= decreaseValue;
}

void Team::increaseWageBudget(int increaseWageValue)
{
    mWageBudget += increaseWageValue;
}

void Team::decreaseWageBudget(int decreaseWageValue)
{
    mWageBudget -= decreaseWageValue;
}

void Team::addPlayerToTeam(Player* player)
{
    mAllPlayers.push_back(player);
}

void Team::setWageBudget(int wageBudget)
{
    mWageBudget = wageBudget;
}

unsigned long long int Team::getTeamValue()
{
    return mTeamValue;
}

std::vector<Player*> Team::getPlayersInTeam()
{
    return mAllPlayers;
}

QString Team::getTeamName()
{
    return mTeamName;
}

QString Team::getTeamCountry()
{
    return mTeamCountry;
}

QString Team::getTeamLeague()
{
    return mTeamLeague;
}

std::vector<Player*> Team::getPlayersByPosition(QString position)
{
    std::vector<Player*> temp;
    for(auto i : mAllPlayers)
        if(i->getPlayerPosition() == position)
            temp.push_back(i);

    return temp;
}

void Team::prepareMatchPlayers()
{
    mMatchPlayers.clear();

    int GK = 1;
    int DR = 0;
    int DC = 0;
    int DL = 0;

    int AML = 0;
    int AMR = 0;
    int MC = 0;
    int AMC = 0;

    int ST = 0;

    if(mFormation == "4-4-2")
    {
        DR = 1;
        DC = 2;
        DL = 1;

        AML = 1;
        AMR = 1;
        MC = 2;

        ST = 2;
    }

    for(int t = 0; t<GK; t++)
    {
        Player* temp = nullptr;

        for(auto i : getPlayersByPosition("GK"))
        {
            if(temp == nullptr)
                temp = i;
            else
            {
                if(i != temp)
                    if(i->getPlayerReflexes() > temp->getPlayerReflexes())
                        temp = i;
            }
        }
        mMatchPlayers.push_back(temp);
    }

    for(int t = 0; t<DR; t++)
    {
        Player* temp = nullptr;

        for(auto i : getPlayersByPosition("DR"))
        {
            if(temp == nullptr)
                temp = i;
            else
            {
                if(i != temp)
                    if(i->getPlayerCA() > temp->getPlayerCA())
                        temp = i;
            }
        }
        mMatchPlayers.push_back(temp);
    }

    for(int t = 0; t<DL; t++)
    {
        Player* temp = nullptr;

        for(auto i : getPlayersByPosition("DL"))
        {
            if(temp == nullptr)
                temp = i;
            else
            {
                if(i != temp)
                    if(i->getPlayerCA() > temp->getPlayerCA())
                        temp = i;
            }
        }
        mMatchPlayers.push_back(temp);
    }

    for(int t = 0; t<DC; t++)
    {
        Player* temp = nullptr;

        for(auto i : getPlayersByPosition("DC"))
        {
            if(temp == nullptr)
                temp = i;
            else
            {
                if(i != temp)
                    if(i->getPlayerCA() > temp->getPlayerCA())
                        temp = i;
            }
        }
        mMatchPlayers.push_back(temp);
    }

    for(int t = 0; t<MC; t++)
    {
        Player* temp = nullptr;

        for(auto i : getPlayersByPosition("MC"))
        {
            if(temp == nullptr)
                temp = i;
            else
            {
                if(i != temp)
                    if(i->getPlayerCA() > temp->getPlayerCA())
                        temp = i;
            }
        }
        mMatchPlayers.push_back(temp);
    }


    for(int t = 0; t<AML; t++)
    {
        Player* temp = nullptr;

        for(auto i : getPlayersByPosition("AML"))
        {
            if(temp == nullptr)
                temp = i;
            else
            {
                if(i != temp)
                    if(i->getPlayerCA() > temp->getPlayerCA())
                        temp = i;
            }
        }
        mMatchPlayers.push_back(temp);
    }

    for(int t = 0; t<AMR; t++)
    {
        Player* temp = nullptr;

        for(auto i : getPlayersByPosition("AMR"))
        {
            if(temp == nullptr)
                temp = i;
            else
            {
                if(i != temp)
                    if(i->getPlayerCA() > temp->getPlayerCA())
                        temp = i;
            }
        }
        mMatchPlayers.push_back(temp);
    }

    if(AMC > 0)
    {
        for(auto i : getPlayersByPosition("AMC"))
        {
            if(auto x : mMatchPlayers)
            {
                if(x == i)
                    break;
            }


        }
        mMatchPlayers.push_back(temp);
    }

    if(ST > 0)
    {
        std::vector<Player*> temp = getPlayersByPosition("ST");


        for(int i = 0; i<ST; ++i)
        {
            Player* player = temp.at(0);

            for(auto x : mMatchPlayers)
                if(player == x)
                    break;

            for(auto t : temp)
            {
                if(t->getPlayerCA() > player->getPlayerCA())
                    player = t;
            }

            mMatchPlayers.push_back(player);
        }

    }


    for(auto i : mMatchPlayers)
        qDebug() << i->getPlayerName() << " : " << i->getPlayerPosition() << " -> " << i->getPlayerCA() << endl;

    qDebug() << endl << endl;
}

std::vector<Player*> Team::getMatchPlayers()
{

}

void Team::removePlayer(Player* player)
{
    int index = 0;
    for(auto i : mAllPlayers)
    {
        if(player == i)
        {
            mAllPlayers.erase(mAllPlayers.begin()+index);
            increaseWageBudget(player->getPlayerWage());
            mTeamValue -= player->getPlayerValue();
            player->releasePlayer();
            break;
        }
        index++;
    }
}

unsigned long long int Team::getTransferBudget()
{
    return mTransferBudget;
}

int Team::getTeamReputation()
{
    return mTeamReputation;
}
