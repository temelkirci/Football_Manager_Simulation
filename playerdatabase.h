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
    QString getRandomPlayer();
    PlayerDatabase* getPlayerDatabase();

    std::map<QString, std::vector<QString>> playerNameSurnameCountry;
    std::map<QString, std::vector<QString>>::iterator itr;
private:
    int playerSize ;
};

#endif // PLAYERDATABASE_H
