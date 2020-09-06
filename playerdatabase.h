#ifndef PLAYERDATABASE_H
#define PLAYERDATABASE_H

#include <map>
#include <vector>
#include <QString>
#include <QDebug>
#include <QChar>
#include <random>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

class PlayerDatabase
{
public:
    PlayerDatabase();
    ~PlayerDatabase();

    void addPlayerName(QString playerName, QString playerSurname, QString playerCountry);
    void showPlayerNames(QString playerCountry);
    QString getRandomPlayerByCountry(QString playerCountry);
    QString getRandomCountry();
    QString getRandomPlayerFullName();

    PlayerDatabase* getPlayerDatabase();

    std::map<QString, std::vector<QString>> playerNameSurnameCountry;
    std::map<QString, std::vector<QString>>::iterator itr;

    std::vector<QString> mAllCountriesInGame;

    QString europe = "C:/Users/temel/Documents/FM20/FootballManagerSimulation/hair/euro/long/";
    QString afro = "C:/Users/temel/Documents/FM20/FootballManagerSimulation/hair/afro/long/";
    QString hispanic = "C:/Users/temel/Documents/FM20/FootballManagerSimulation/hair/hispanic/long/";
    QString asia = "C:/Users/temel/Documents/FM20/FootballManagerSimulation/hair/asian/long/";
    QString mixed_race = "C:/Users/temel/Documents/FM20/FootballManagerSimulation/hair/mixed_race/long/";

    QString getEuropePlayer();
    QString getAsianPlayer();
    QString getAfroPlayer();
    QString getMixedRacePlayer();
    QString getHispanicPlayer();

private:
    int playerSize ;
    std::vector<QString> mEuropePlayers;
    std::vector<QString> mAsianPlayers;
    std::vector<QString> mAfroPlayers;
    std::vector<QString> mMixedRacePlayers;
    std::vector<QString> mHispanicPlayers;
};

#endif // PLAYERDATABASE_H
