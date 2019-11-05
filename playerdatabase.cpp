#include "playerdatabase.h"

PlayerDatabase::PlayerDatabase()
{
    playerSize = 0;
}

PlayerDatabase::~PlayerDatabase()
{

}

PlayerDatabase* PlayerDatabase::getPlayerDatabase()
{
    return this;
}

void PlayerDatabase::showPlayerNames(QString playerCountry)
{
    int i=0;
    for (itr = playerNameSurnameCountry.begin(); itr != playerNameSurnameCountry.end(); ++itr)
    {
        if(itr->first == playerCountry)
        {
            std::vector<QString>::iterator it;
            for(it = (itr->second).begin(); it != (itr->second).end(); ++it)
            {
                i++;
                qDebug() << i <<"."<< *it << endl;
            }
        }
    }
}
// 3 GK
// 4 DC
// 2 DR
// 2 DL
// 4 MC
// 2 AML
// 2 AMR
// 2 AMC
// 3 FC

QString PlayerDatabase::getRandomPlayerByCountry(QString playerCountry)
{
    unsigned int pPlayerSize = playerNameSurnameCountry[playerCountry].size();
    QString pNameSurname ;
    QString pName ;

    unsigned int name = qrand()%pPlayerSize;
    pName = playerNameSurnameCountry[playerCountry].at(name).split("~")[0];

    unsigned int surname = qrand()%pPlayerSize;
    pNameSurname = playerNameSurnameCountry[playerCountry].at(surname).split("~")[1];

    return pName + " " + pNameSurname;
}

QString PlayerDatabase::getRandomPlayer()
{
    unsigned int index = 0;
    unsigned int country = rand()%playerNameSurnameCountry.size();
    QString pPlayerName = "";

    for (itr = playerNameSurnameCountry.begin(); itr != playerNameSurnameCountry.end(); ++itr)
    {
        index++;
        if(index == country)
        {
            unsigned int name = qrand()%(itr->second).size();

            QString pNameSurname = (itr->second)[name];
            QString pCountry = (itr->first);

            pPlayerName = pCountry+"~"+pNameSurname;
            return pPlayerName;
        }
    }
    return pPlayerName;
}

void PlayerDatabase::addPlayerName(QString playerName, QString playerSurname, QString playerCountry)
{
    QString temp;
    temp = playerName+"~"+playerSurname;

    if(playerName.toLatin1().contains('?') || playerSurname.toLatin1().contains('?'))
    {

    }
    else
    {
        bool exist = false;

        for (itr = playerNameSurnameCountry.begin(); itr != playerNameSurnameCountry.end(); ++itr)
        {
            if(itr->first == playerCountry)
            {
                exist = true;
                break;
            }
        }

        if ( exist )
        {
            std::vector<QString>::iterator it;
            for(it = (itr->second).begin(); it != (itr->second).end(); ++it)
            {
               if((*it) == temp)
                   return;
            }
            playerNameSurnameCountry[playerCountry].push_back(temp);
        }
        else
        {
            std::vector<QString> tempVec;
            tempVec.push_back(temp);
            playerNameSurnameCountry[playerCountry] = tempVec;
        }

        playerSize++;
        //qDebug() << playerSize << ".playerCountry : " << playerCountry << "  PlayerNameSurname : " << temp << endl;
    }
}
