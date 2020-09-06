#ifndef MANAGER_H
#define MANAGER_H

#include <QString>
#include <QDate>
#include "Tactic.h"
#include <memory>

class Manager
{
public:
    Manager(QString, QString, QString);
    void FiredByClub();
    void SignClub(QString);

    QString getManagerName();
    void setTactics();
    std::shared_ptr< Tactic > getTactics();

    QString getManagerGameStyle();
    QString getFormation();
    QString getAttackPosition();
    QString getTackling();
    QString getLongShots();

    int getClubManagement();
    int getMotivation();
    int getTraining();

    void setManagerAttributes(int, int, int);

private:
    QString mManagerFullName;
    QString mManagerNationality;
    QDate mManagerBirthDate;
    QString mManagerCurrentClub;


    int mMotivation;
    int mClubManagement;
    int mTraining;

    std::shared_ptr< Tactic > mpTactic;

};

#endif // MANAGER_H
