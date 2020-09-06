#include "PlayerDatabase.h"
#include <QDir>

PlayerDatabase::PlayerDatabase()
{
    playerSize = 0;

    QDir directory(europe);
    QStringList images = directory.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);
    foreach(QString filename, images)
    {
        mEuropePlayers.push_back(europe+filename);
    }

    QDir directory1(asia);
    QStringList images1 = directory1.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);
    foreach(QString filename, images1)
    {
        mAsianPlayers.push_back(asia+filename);
    }

    QDir directory2(afro);
    QStringList images2 = directory2.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);
    foreach(QString filename, images2)
    {
        mAfroPlayers.push_back(afro+filename);
    }

    QDir directory3(hispanic);
    QStringList images3 = directory3.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);
    foreach(QString filename, images3)
    {
        mHispanicPlayers.push_back(hispanic+filename);
    }

    QDir directory4(mixed_race);
    QStringList images4 = directory4.entryList(QStringList() << "*.png" << "*.PNG",QDir::Files);
    foreach(QString filename, images4)
    {
        mMixedRacePlayers.push_back(mixed_race+filename);
    }

    qDebug() << "Europe : " << mEuropePlayers.size() << endl;
    qDebug() << "Asia : " << mAsianPlayers.size() << endl;
    qDebug() << "Afro : " << mAfroPlayers.size() << endl;
    qDebug() << "Hispanic : " << mHispanicPlayers.size() << endl;
    qDebug() << "Mixed Race : " << mMixedRacePlayers.size() << endl;
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

QString PlayerDatabase::getRandomPlayerFullName()
{
    QString tPlayerCountry = getRandomCountry();
    unsigned int pPlayerSize = playerNameSurnameCountry[tPlayerCountry].size();
    QString pNameSurname ;
    QString pName ;

    unsigned int name = qrand()%pPlayerSize;
    pName = playerNameSurnameCountry[tPlayerCountry].at(name).split("~")[0];

    unsigned int surname = qrand()%pPlayerSize;
    pNameSurname = playerNameSurnameCountry[tPlayerCountry].at(surname).split("~")[1];

    return pName + " " + pNameSurname;
}

QString PlayerDatabase::getRandomCountry()
{
    unsigned int tCountrySize = mAllCountriesInGame.size();
    QString tCountryName ;

    unsigned int tCountryIndex = qrand()%tCountrySize;
    tCountryName = mAllCountriesInGame[tCountryIndex];

    return tCountryName;
}

void PlayerDatabase::addPlayerName(QString playerName, QString playerSurname, QString playerCountry)
{
    //if(std::count(mAllCountriesInGame.begin(), mAllCountriesInGame.end(), playerCountry))
    //{
        // founded
    //}
    //else
    //{
        // not founded
        mAllCountriesInGame.push_back(playerCountry);
    //}

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

QString PlayerDatabase::getEuropePlayer()
{
    int x = rand() % mEuropePlayers.size();
    QString path = mEuropePlayers[x];
    mEuropePlayers.erase(mEuropePlayers.begin() + x);
    return path;
}
QString PlayerDatabase::getAsianPlayer()
{
    int x = rand() % mAsianPlayers.size();
    QString path = mAsianPlayers[x];
    mAsianPlayers.erase(mAsianPlayers.begin() + x);
    return path;
}
QString PlayerDatabase::getAfroPlayer()
{
    int x = rand() % mAfroPlayers.size();
    QString path = mAfroPlayers[x];
    mAfroPlayers.erase(mAfroPlayers.begin() + x);
    return path;
}
QString PlayerDatabase::getMixedRacePlayer()
{
    int x = rand() % mMixedRacePlayers.size();
    QString path = mMixedRacePlayers[x];
    mMixedRacePlayers.erase(mMixedRacePlayers.begin() + x);
    return path;
}
QString PlayerDatabase::getHispanicPlayer()
{
    int x = rand() % mHispanicPlayers.size();
    QString path = mHispanicPlayers[x];
    mHispanicPlayers.erase(mHispanicPlayers.begin() + x);
    return path;
}
