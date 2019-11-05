#include "teamdatabase.h"

TeamDatabase::TeamDatabase()
{

}

TeamDatabase::~TeamDatabase()
{
    for(unsigned int i=0; i<allTeamsInGame.size(); i++)
        delete allTeamsInGame[i];
}

int TeamDatabase::generateRandomNumber(int lower, int upper)
{
   return (qrand() % (upper - lower + 1)) + lower;
}

int TeamDatabase::generatePlayerValue(int lower, int upper)
{
    if(upper > 100)
        upper = 100;

    if(lower >= upper)
        return lower;

   return (qrand() % (upper - lower + 1)) + lower;
}

int TeamDatabase::getCalculatePlayerValue()
{
    return mPlayerValue;
}

unsigned int TeamDatabase::getLeagueReputation(int pLeagueReputation)
{
    unsigned int repu;

    if(pLeagueReputation >= 900)
        repu = 40;
    else if(pLeagueReputation>=800 && pLeagueReputation<900)
        repu = 35;
    else if(pLeagueReputation>=700 && pLeagueReputation<800)
        repu = 30;
    else if(pLeagueReputation>=600 && pLeagueReputation<700)
        repu = 25;
    else if(pLeagueReputation>=500 && pLeagueReputation<600)
        repu = 20;
    else if(pLeagueReputation>=400 && pLeagueReputation<500)
        repu = 15;
    else if(pLeagueReputation>=300 && pLeagueReputation<400)
        repu = 10;
    else if(pLeagueReputation>=200 && pLeagueReputation<300)
        repu = 5;
    else if(pLeagueReputation>=100 && pLeagueReputation<200)
        repu = 2;
    else
        repu = 1;


    return repu;
}

unsigned int TeamDatabase::getTeamReputation(int pTeamReputation)
{
    unsigned int teamRepu;

    if(pTeamReputation >= 900)
        teamRepu = 200;
    else if(pTeamReputation>=850 && pTeamReputation<900)
        teamRepu = 150;
    else if(pTeamReputation>=800 && pTeamReputation<850)
        teamRepu = 125;
    else if(pTeamReputation>=750 && pTeamReputation<800)
        teamRepu = 100;
    else if(pTeamReputation>=700 && pTeamReputation<750)
        teamRepu = 75;
    else if(pTeamReputation>=600 && pTeamReputation<700)
        teamRepu = 50;
    else if(pTeamReputation>=500 && pTeamReputation<600)
        teamRepu = 35;
    else if(pTeamReputation>=400 && pTeamReputation<500)
        teamRepu = 20;
    else if(pTeamReputation>=300 && pTeamReputation<400)
        teamRepu = 15;
    else if(pTeamReputation>=200 && pTeamReputation<300)
        teamRepu = 10;
    else if(pTeamReputation>=100 && pTeamReputation<200)
        teamRepu = 5;
    else
        teamRepu = 1;

    return teamRepu;
}

void TeamDatabase::generate_GK_Player(int number, Team* team, int leagueReputation)
{
    unsigned int lowAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)-20));
    unsigned int highAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)));

    unsigned int teamRepu = getTeamReputation(team->getTeamReputation());
    unsigned int repu = getLeagueReputation(leagueReputation);

    int baseSalary = (team->mMaxWageBudget / 100000);

    for(int i=0; i<number; i++)
    {
        unsigned int age = generateRandomNumber(1985, 2002);
        unsigned int expires = generateRandomNumber(2020, 2025);

        unsigned int CA = 0;
        unsigned int PA = 0;

        int base = 100;

        unsigned int reflexes = 0;

        QString pFullName = getRandomPlayerByCountry(team->getTeamCountry());
        QString contract_expires = "30.6." + QString::number(expires);

        reflexes = generatePlayerValue(lowAttribute+5, highAttribute+5);
        CA = reflexes;
        base = reflexes * (reflexes/10) * reflexes;

        PA = (generateRandomNumber(CA,100));
        int pPlayerForm = generateRandomNumber(1,10)*10;


        int ageDivide = (2020 - age)*12000;
        unsigned long long int temp = ( CA * repu * base );
        unsigned long long int pPlayerValue = ((temp + ((teamRepu*temp*base )/10000))/ageDivide ) * 50;

        pPlayerValue = (pPlayerValue/10000) * 10000;
        if(pPlayerValue <= 0)
            pPlayerValue = 10000;

        int playerSalary = baseSalary * CA * pPlayerForm;
        team->increaseWageBudget(playerSalary);
        team->mTeamValue = team->mTeamValue + pPlayerValue;

        Player* pPlayer = new Player(pFullName, "GK", team->getTeamName(), contract_expires, QString::number(age), pPlayerValue, playerSalary, pPlayerForm);
        pPlayer->setPlayerAttributes(reflexes, 0, 0, 0, 0, 0);
        pPlayer->setPlayerCA(CA);
        pPlayer->setPlayerPA(PA);
        pPlayer->setAskingPrice(0);
        pPlayer->setTransferList(false);

        team->addPlayerToTeam(pPlayer);
    }

}
void TeamDatabase::generate_DC_Player(int number, Team* team, int leagueReputation)
{
    unsigned int lowAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)-40));
    unsigned int highAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)));

    unsigned int teamRepu = getTeamReputation(team->getTeamReputation());
    unsigned int repu = getLeagueReputation(leagueReputation);

    int baseSalary = (team->mMaxWageBudget / 100000);

    for(int i=0; i<number; i++)
    {
        unsigned int age = generateRandomNumber(1985, 2002);
        unsigned int expires = generateRandomNumber(2020, 2025);

        QString pFullName = getRandomPlayerByCountry(team->getTeamCountry());
        QString contract_expires = "30.6." + QString::number(expires);

        unsigned int tackling = 0;
        unsigned int passing = 0;
        unsigned int pace = 0;
        unsigned int technique = 0;
        unsigned int finishing = 0;

        unsigned int CA = 0;
        unsigned int PA = 0;

        int base = 100;

        tackling = generatePlayerValue(lowAttribute+25, highAttribute+5);
        passing = generatePlayerValue(lowAttribute-10, highAttribute-15);
        pace = generatePlayerValue(lowAttribute, highAttribute);
        technique = generatePlayerValue(lowAttribute, highAttribute-10);
        finishing = generatePlayerValue(lowAttribute, highAttribute-20);

        if(age <= 1990)
        {
            pace -= 20;
        }

        base = ((tackling/10)*tackling + passing + pace + technique + finishing)*tackling;

        CA = (tackling + passing + pace + technique + finishing)/5;

        PA = (generateRandomNumber(CA,100));
        int pPlayerForm = generateRandomNumber(1,10)*10;

        int ageDivide = (2020 - age)*12000;
        unsigned long long int temp = ( CA * repu * base );
        unsigned long long int pPlayerValue = ((temp + ((teamRepu*temp*base )/10000))/ageDivide ) * 50;

        pPlayerValue = (pPlayerValue/10000) * 10000;
        if(pPlayerValue <= 0)
            pPlayerValue = 10000;

        int playerSalary = baseSalary * CA * pPlayerForm;
        team->increaseWageBudget(playerSalary);
        team->mTeamValue = team->mTeamValue + pPlayerValue;

        Player* pPlayer = new Player(pFullName, "DC", team->getTeamName(), contract_expires, QString::number(age), pPlayerValue, playerSalary, pPlayerForm);
        pPlayer->setPlayerAttributes(0, tackling, passing, technique, pace, finishing);
        pPlayer->setPlayerCA(CA);
        pPlayer->setPlayerPA(PA);
        pPlayer->setAskingPrice(0);
        pPlayer->setTransferList(false);

        team->addPlayerToTeam(pPlayer);
    }
}

void TeamDatabase::generate_DR_Player(int number, Team* team, int leagueReputation)
{
    unsigned int lowAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)-40));
    unsigned int highAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)));

    unsigned int teamRepu = getTeamReputation(team->getTeamReputation());
    unsigned int repu = getLeagueReputation(leagueReputation);

    int baseSalary = (team->mMaxWageBudget / 100000);

    for(int i=0; i<number; i++)
    {
        unsigned int age = generateRandomNumber(1985, 2002);
        unsigned int expires = generateRandomNumber(2020, 2025);

        QString pFullName = getRandomPlayerByCountry(team->getTeamCountry());
        QString contract_expires = "30.6." + QString::number(expires);

        unsigned int tackling = 0;
        unsigned int passing = 0;
        unsigned int pace = 0;
        unsigned int technique = 0;
        unsigned int finishing = 0;

        unsigned int CA = 0;
        unsigned int PA = 0;

        int base = 100;

        tackling = generatePlayerValue(lowAttribute+20, highAttribute+5);
        passing = generatePlayerValue(lowAttribute+10, highAttribute);
        pace = generatePlayerValue(lowAttribute+20, highAttribute);
        technique = generatePlayerValue(lowAttribute+15, highAttribute);
        finishing = generatePlayerValue(lowAttribute, highAttribute-10);

        if(age <= 1990)
        {
            pace -= 20;
        }

        base = ((tackling/10)*tackling + passing + pace + technique + finishing)*tackling;

        CA = (tackling + passing + pace + technique + finishing)/5;

        PA = (generateRandomNumber(CA,100));
        int pPlayerForm = generateRandomNumber(1,10)*10;

        int ageDivide = (2020 - age)*12000;
        unsigned long long int temp = ( CA * repu * base );
        unsigned long long int pPlayerValue = ((temp + ((teamRepu*temp*base )/10000))/ageDivide ) * 50;

        pPlayerValue = (pPlayerValue/10000) * 10000;
        if(pPlayerValue <= 0)
            pPlayerValue = 10000;

        int playerSalary = baseSalary * CA * pPlayerForm;
        team->increaseWageBudget(playerSalary);
        team->mTeamValue = team->mTeamValue + pPlayerValue;

        Player* pPlayer = new Player(pFullName, "DR", team->getTeamName(), contract_expires, QString::number(age), pPlayerValue, playerSalary, pPlayerForm);
        pPlayer->setPlayerAttributes(0, tackling, passing, technique, pace, finishing);
        pPlayer->setPlayerCA(CA);
        pPlayer->setPlayerPA(PA);
        pPlayer->setAskingPrice(0);
        pPlayer->setTransferList(false);

        team->addPlayerToTeam(pPlayer);
    }
}

void TeamDatabase::generate_AMR_Player(int number, Team* team, int leagueReputation)
{
    unsigned int lowAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)-40));
    unsigned int highAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)));

    unsigned int teamRepu = getTeamReputation(team->getTeamReputation());
    unsigned int repu = getLeagueReputation(leagueReputation);

    int baseSalary = (team->mMaxWageBudget / 100000);

    for(int i=0; i<number; i++)
    {
        unsigned int age = generateRandomNumber(1985, 2002);
        unsigned int expires = generateRandomNumber(2020, 2025);

        QString pFullName = getRandomPlayerByCountry(team->getTeamCountry());
        QString contract_expires = "30.6." + QString::number(expires);

        unsigned int tackling = 0;
        unsigned int passing = 0;
        unsigned int pace = 0;
        unsigned int technique = 0;
        unsigned int finishing = 0;

        unsigned int CA = 0;
        unsigned int PA = 0;

        int base = 100;

        tackling = generatePlayerValue(lowAttribute, highAttribute-20);
        passing = generatePlayerValue(lowAttribute+10, highAttribute);
        pace = generatePlayerValue(lowAttribute+25, highAttribute+5);
        technique = generatePlayerValue(lowAttribute+20, highAttribute+5);
        finishing = generatePlayerValue(lowAttribute, highAttribute-5);

        if(age <= 1990)
        {
            pace -= 20;
        }

        base = (tackling + passing + pace*(pace/10) + technique + finishing)*pace;

        CA = (tackling + passing + pace + technique + finishing)/5;

        PA = (generateRandomNumber(CA,100));
        int pPlayerForm = generateRandomNumber(1,10)*10;

        int ageDivide = (2020 - age)*12000;
        unsigned long long int temp = ( CA * repu * base );
        unsigned long long int pPlayerValue = ((temp + ((teamRepu*temp*base )/10000))/ageDivide ) * 50;

        pPlayerValue = (pPlayerValue/10000) * 10000;
        if(pPlayerValue <= 0)
            pPlayerValue = 10000;

        int playerSalary = baseSalary * CA * pPlayerForm;
        team->increaseWageBudget(playerSalary);
        team->mTeamValue = team->mTeamValue + pPlayerValue;

        Player* pPlayer = new Player(pFullName, "AMR", team->getTeamName(), contract_expires, QString::number(age), pPlayerValue, playerSalary, pPlayerForm);
        pPlayer->setPlayerAttributes(0, tackling, passing, technique, pace, finishing);
        pPlayer->setPlayerCA(CA);
        pPlayer->setPlayerPA(PA);
        pPlayer->setAskingPrice(0);
        pPlayer->setTransferList(false);

        team->addPlayerToTeam(pPlayer);
    }
}

void TeamDatabase::generate_DL_Player(int number, Team* team, int leagueReputation)
{
    unsigned int lowAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)-40));
    unsigned int highAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)));

    unsigned int teamRepu = getTeamReputation(team->getTeamReputation());
    unsigned int repu = getLeagueReputation(leagueReputation);

    int baseSalary = (team->mMaxWageBudget / 100000);

    for(int i=0; i<number; i++)
    {
        unsigned int age = generateRandomNumber(1985, 2002);
        unsigned int expires = generateRandomNumber(2020, 2025);

        QString pFullName = getRandomPlayerByCountry(team->getTeamCountry());
        QString contract_expires = "30.6." + QString::number(expires);

        unsigned int tackling = 0;
        unsigned int passing = 0;
        unsigned int pace = 0;
        unsigned int technique = 0;
        unsigned int finishing = 0;

        unsigned int CA = 0;
        unsigned int PA = 0;

        int base = 100;

        tackling = generatePlayerValue(lowAttribute+20, highAttribute+5);
        passing = generatePlayerValue(lowAttribute+10, highAttribute);
        pace = generatePlayerValue(lowAttribute+20, highAttribute);
        technique = generatePlayerValue(lowAttribute+15, highAttribute);
        finishing = generatePlayerValue(lowAttribute, highAttribute-10);

        if(age <= 1990)
        {
            pace -= 20;
        }

        base = ((tackling/10)*tackling + passing + pace + technique + finishing)*tackling;

        CA = (tackling + passing + pace + technique + finishing)/5;

        PA = (generateRandomNumber(CA,100));
        int pPlayerForm = generateRandomNumber(1,10)*10;

        int ageDivide = (2020 - age)*12000;
        unsigned long long int temp = ( CA * repu * base );
        unsigned long long int pPlayerValue = ((temp + ((teamRepu*temp*base )/10000))/ageDivide ) * 50;

        pPlayerValue = (pPlayerValue/10000) * 10000;
        if(pPlayerValue <= 0)
            pPlayerValue = 10000;

        int playerSalary = baseSalary * CA * pPlayerForm;
        team->increaseWageBudget(playerSalary);
        team->mTeamValue = team->mTeamValue + pPlayerValue;

        Player* pPlayer = new Player(pFullName, "DL", team->getTeamName(), contract_expires, QString::number(age), pPlayerValue, playerSalary, pPlayerForm);
        pPlayer->setPlayerAttributes(0, tackling, passing, technique, pace, finishing);
        pPlayer->setPlayerCA(CA);
        pPlayer->setPlayerPA(PA);
        pPlayer->setAskingPrice(0);
        pPlayer->setTransferList(false);

        team->addPlayerToTeam(pPlayer);
    }
}

void TeamDatabase::generate_AML_Player(int number, Team* team, int leagueReputation)
{
    unsigned int lowAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)-40));
    unsigned int highAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)));

    unsigned int teamRepu = getTeamReputation(team->getTeamReputation());
    unsigned int repu = getLeagueReputation(leagueReputation);

    int baseSalary = (team->mMaxWageBudget / 100000);

    for(int i=0; i<number; i++)
    {
        unsigned int age = generateRandomNumber(1985, 2002);
        unsigned int expires = generateRandomNumber(2020, 2025);

        QString pFullName = getRandomPlayerByCountry(team->getTeamCountry());
        QString contract_expires = "30.6." + QString::number(expires);

        unsigned int tackling = 0;
        unsigned int passing = 0;
        unsigned int pace = 0;
        unsigned int technique = 0;
        unsigned int finishing = 0;

        unsigned int CA = 0;
        unsigned int PA = 0;

        int base = 100;

        tackling = generatePlayerValue(lowAttribute, highAttribute-20);
        passing = generatePlayerValue(lowAttribute+10, highAttribute);
        pace = generatePlayerValue(lowAttribute+25, highAttribute+5);
        technique = generatePlayerValue(lowAttribute+20, highAttribute+5);
        finishing = generatePlayerValue(lowAttribute, highAttribute-5);

        if(age <= 1990)
        {
            pace -= 20;
        }

        base = (tackling + passing + pace*(pace/10) + technique + finishing)*pace;

        CA = (tackling + passing + pace + technique + finishing)/5;

        PA = (generateRandomNumber(CA,100));
        int pPlayerForm = generateRandomNumber(1,10)*10;

        int ageDivide = (2020 - age)*12000;
        unsigned long long int temp = ( CA * repu * base );
        unsigned long long int pPlayerValue = ((temp + ((teamRepu*temp*base )/10000))/ageDivide ) * 50;

        pPlayerValue = (pPlayerValue/10000) * 10000;
        if(pPlayerValue <= 0)
            pPlayerValue = 10000;

        int playerSalary = baseSalary * CA * pPlayerForm;
        team->increaseWageBudget(playerSalary);
        team->mTeamValue = team->mTeamValue + pPlayerValue;

        Player* pPlayer = new Player(pFullName, "AML", team->getTeamName(), contract_expires, QString::number(age), pPlayerValue, playerSalary, pPlayerForm);
        pPlayer->setPlayerAttributes(0, tackling, passing, technique, pace, finishing);
        pPlayer->setPlayerCA(CA);
        pPlayer->setPlayerPA(PA);
        pPlayer->setAskingPrice(0);
        pPlayer->setTransferList(false);

        team->addPlayerToTeam(pPlayer);
    }
}

void TeamDatabase::generate_MC_Player(int number, Team* team, int leagueReputation)
{
    unsigned int lowAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)-40));
    unsigned int highAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)));

    unsigned int teamRepu = getTeamReputation(team->getTeamReputation());
    unsigned int repu = getLeagueReputation(leagueReputation);

    int baseSalary = (team->mMaxWageBudget / 100000);

    for(int i=0; i<number; i++)
    {
        unsigned int age = generateRandomNumber(1985, 2002);
        unsigned int expires = generateRandomNumber(2020, 2025);

        QString pFullName = getRandomPlayerByCountry(team->getTeamCountry());
        QString contract_expires = "30.6." + QString::number(expires);

        unsigned int tackling = 0;
        unsigned int passing = 0;
        unsigned int pace = 0;
        unsigned int technique = 0;
        unsigned int finishing = 0;

        unsigned int CA = 0;
        unsigned int PA = 0;

        int base = 100;

        tackling = generatePlayerValue(lowAttribute+10, highAttribute-5);
        passing = generatePlayerValue(lowAttribute+20, highAttribute+10);
        pace = generatePlayerValue(lowAttribute+10, highAttribute);
        technique = generatePlayerValue(lowAttribute+5, highAttribute);
        finishing = generatePlayerValue(lowAttribute+5, highAttribute);

        if(age <= 1990)
        {
            pace -= 20;
        }

        base = (tackling + passing*(passing/10) + pace + technique + finishing)*passing;

        CA = (tackling + passing + pace + technique + finishing)/5;

        PA = (generateRandomNumber(CA,100));
        int pPlayerForm = generateRandomNumber(1,10)*10;

        int ageDivide = (2020 - age)*12000;
        unsigned long long int temp = ( CA * repu * base );
        unsigned long long int pPlayerValue = ((temp + ((teamRepu*temp*base )/10000))/ageDivide ) * 50;

        pPlayerValue = (pPlayerValue/10000) * 10000;
        if(pPlayerValue <= 0)
            pPlayerValue = 10000;

        int playerSalary = baseSalary * CA * pPlayerForm;
        team->increaseWageBudget(playerSalary);
        team->mTeamValue = team->mTeamValue + pPlayerValue;

        Player* pPlayer = new Player(pFullName, "MC", team->getTeamName(), contract_expires, QString::number(age), pPlayerValue, playerSalary, pPlayerForm);
        pPlayer->setPlayerAttributes(0, tackling, passing, technique, pace, finishing);
        pPlayer->setPlayerCA(CA);
        pPlayer->setPlayerPA(PA);
        pPlayer->setAskingPrice(0);
        pPlayer->setTransferList(false);
        team->addPlayerToTeam(pPlayer);
    }
}

void TeamDatabase::generate_AMC_Player(int number, Team* team, int leagueReputation)
{
    unsigned int lowAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)-40));
    unsigned int highAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)));

    unsigned int teamRepu = getTeamReputation(team->getTeamReputation());
    unsigned int repu = getLeagueReputation(leagueReputation);

    int baseSalary = (team->mMaxWageBudget / 100000);

    for(int i=0; i<number; i++)
    {
        unsigned int age = generateRandomNumber(1985, 2002);
        unsigned int expires = generateRandomNumber(2020, 2025);

        QString pFullName = getRandomPlayerByCountry(team->getTeamCountry());
        QString contract_expires = "30.6." + QString::number(expires);

        unsigned int tackling = 0;
        unsigned int passing = 0;
        unsigned int pace = 0;
        unsigned int technique = 0;
        unsigned int finishing = 0;

        unsigned int CA = 0;
        unsigned int PA = 0;

        int base = 100;

        tackling = generatePlayerValue(lowAttribute, highAttribute-10);
        passing = generatePlayerValue(lowAttribute+25, highAttribute+5);
        pace = generatePlayerValue(lowAttribute+10, highAttribute);
        technique = generatePlayerValue(lowAttribute+15, highAttribute);
        finishing = generatePlayerValue(lowAttribute, highAttribute-10);

        if(age <= 1990)
        {
            pace -= 20;
        }

        base = (tackling + passing*(passing/10) + pace + technique + finishing)*passing;

        CA = (tackling + passing + pace + technique + finishing)/5;

        PA = (generateRandomNumber(CA,100));
        int pPlayerForm = generateRandomNumber(1,10)*10;

        int ageDivide = (2020 - age)*12000;
        unsigned long long int temp = ( CA * repu * base );
        unsigned long long int pPlayerValue = ((temp + ((teamRepu*temp*base )/10000))/ageDivide ) * 50;

        pPlayerValue = (pPlayerValue/10000) * 10000;
        if(pPlayerValue <= 0)
            pPlayerValue = 10000;

        int playerSalary = baseSalary * CA * pPlayerForm;
        team->increaseWageBudget(playerSalary);
        team->mTeamValue = team->mTeamValue + pPlayerValue;

        Player* pPlayer = new Player(pFullName, "AMC", team->getTeamName(), contract_expires, QString::number(age), pPlayerValue, playerSalary, pPlayerForm);
        pPlayer->setPlayerAttributes(0, tackling, passing, technique, pace, finishing);
        pPlayer->setPlayerCA(CA);
        pPlayer->setPlayerPA(PA);
        pPlayer->setAskingPrice(0);

        team->addPlayerToTeam(pPlayer);
    }
}

void TeamDatabase::generate_FC_Player(int number, Team* team, int leagueReputation)
{
    unsigned int lowAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)-40));
    unsigned int highAttribute = std::lround(std::ceil(((team->getTeamReputation())/10)));

    unsigned int teamRepu = getTeamReputation(team->getTeamReputation());
    unsigned int repu = getLeagueReputation(leagueReputation);

    int baseSalary = (team->mMaxWageBudget / 100000);

    for(int i=0; i<number; i++)
    {
        unsigned int age = generateRandomNumber(1985, 2002);
        unsigned int expires = generateRandomNumber(2020, 2025);

        QString pFullName = getRandomPlayerByCountry(team->getTeamCountry());
        QString contract_expires = "30.6." + QString::number(expires);

        unsigned int tackling = 0;
        unsigned int passing = 0;
        unsigned int pace = 0;
        unsigned int technique = 0;
        unsigned int finishing = 0;

        unsigned int CA = 0;
        unsigned int PA = 0;

        int base = 100;

        tackling = generatePlayerValue(lowAttribute-10, highAttribute-10);
        passing = generatePlayerValue(lowAttribute, highAttribute-15);
        pace = generatePlayerValue(lowAttribute+20, highAttribute);
        technique = generatePlayerValue(lowAttribute+10, highAttribute);
        finishing = generatePlayerValue(lowAttribute+25, highAttribute+5);

        if(age <= 1990)
        {
            pace -= 20;
        }
        base = (tackling + passing + pace + technique + finishing*(finishing/10))*finishing;

        CA = (tackling + passing + pace + technique + finishing)/5;

        PA = (generateRandomNumber(CA,100));
        int pPlayerForm = generateRandomNumber(1,10)*10;

        int ageDivide = (2020 - age)*12000;
        unsigned long long int temp = ( CA * repu * base );
        unsigned long long int pPlayerValue = ((temp + ((teamRepu*temp*base )/10000))/ageDivide ) * 50;

        pPlayerValue = (pPlayerValue/10000) * 10000;
        if(pPlayerValue <= 0)
            pPlayerValue = 10000;

        int playerSalary = baseSalary * CA * pPlayerForm;
        team->increaseWageBudget(playerSalary);
        team->mTeamValue = team->mTeamValue + pPlayerValue;

        Player* pPlayer = new Player(pFullName, "ST", team->getTeamName(), contract_expires, QString::number(age), pPlayerValue, playerSalary, pPlayerForm);
        pPlayer->setPlayerAttributes(0, tackling, passing, technique, pace, finishing);
        pPlayer->setPlayerCA(CA);
        pPlayer->setPlayerPA(PA);
        pPlayer->setAskingPrice(0);

        team->addPlayerToTeam(pPlayer);
    }
}

Team* TeamDatabase::addTeamToGame(QString pTeamName, int pTeamReputation, int pTransferBudget, int pWageBudget, QString pLeagueName, int pLeagueReputation, QString pLeagueCountry)
{
    Team* pTeam = new Team(pTeamName, pTeamReputation, pLeagueName, pTransferBudget, pLeagueCountry);
    pTeam->mMaxWageBudget = pWageBudget;


    generate_GK_Player(3, pTeam, pLeagueReputation);

    generate_DC_Player(4, pTeam, pLeagueReputation);
    generate_DR_Player(2, pTeam, pLeagueReputation);
    generate_DL_Player(2, pTeam, pLeagueReputation);

    generate_AMR_Player(2, pTeam, pLeagueReputation);
    generate_AML_Player(2, pTeam, pLeagueReputation);

    generate_MC_Player(4, pTeam, pLeagueReputation);
    generate_AMC_Player(2, pTeam, pLeagueReputation);

    generate_FC_Player(3, pTeam, pLeagueReputation);

    //pTeam->setTeamAvaragePoint(teamPoint/24);
    //qDebug() << pTeam->getTeamName() << " : " << pTeam->getTeamAvaragePoint() << endl;

    allTeamsInGame.push_back(pTeam);

    int teamReputation = pTeam->getTeamReputation()/10-10;

    for(auto i : pTeam->getPlayersInTeam())
    {
        if(i->getPlayerPosition() == "GK")
        {
            if( ((i->getPlayerCA()+i->getPlayerForm()/10)) < (teamReputation))
            {
                i->setTransferList(true);
                unsigned long long int askingPrice = ( ( (i->getPlayerValue() * i->getPlayerForm()) / 100 + (i->getPlayerValue() * i->getPlayerPA()) / (2020 - i->getPlayerBirthDay().toInt())) /100000) * 15000;
                i->setAskingPrice(askingPrice);
                pTeam->addTransferList(i);
            }
        }
        if( (i->getPlayerPosition() == "DR") || (i->getPlayerPosition() == "DL"))
        {
            if( ((i->getPlayerCA()+i->getPlayerForm()/10) < teamReputation) && (i->getPlayerTackling()+i->getPlayerForm()/10 < teamReputation))
            {
                i->setTransferList(true);
                unsigned long long int askingPrice = ( ( (i->getPlayerValue() * i->getPlayerForm()) / 100 + (i->getPlayerValue() * i->getPlayerPA()) / (2020 - i->getPlayerBirthDay().toInt())) /100000) * 15000;
                i->setAskingPrice(askingPrice);
                pTeam->addTransferList(i);
            }
        }
        if( i->getPlayerPosition() == "DC")
        {
            if( ((i->getPlayerCA()+i->getPlayerForm()/10) < teamReputation) && (i->getPlayerTackling()+i->getPlayerForm()/10) < teamReputation)
            {
                i->setTransferList(true);
                unsigned long long int askingPrice = ( ( (i->getPlayerValue() * i->getPlayerForm()) / 100 + (i->getPlayerValue() * i->getPlayerPA()) / (2020 - i->getPlayerBirthDay().toInt())) /100000) * 15000;
                i->setAskingPrice(askingPrice);
                pTeam->addTransferList(i);
            }
        }

        if( i->getPlayerPosition() == "MC")
        {
            if( ((i->getPlayerCA()+i->getPlayerForm()/10) < teamReputation) && (i->getPlayerPassing()+i->getPlayerForm()/10) < teamReputation)
            {
                i->setTransferList(true);
                unsigned long long int askingPrice = ( ( (i->getPlayerValue() * i->getPlayerForm()) / 100 + (i->getPlayerValue() * i->getPlayerPA()) / (2020 - i->getPlayerBirthDay().toInt())) /100000) * 15000;
                i->setAskingPrice(askingPrice);
                pTeam->addTransferList(i);
            }
        }

        if( (i->getPlayerPosition() == "AMR") || (i->getPlayerPosition() == "AML"))
        {
            if( (i->getPlayerCA()+i->getPlayerForm()/10) < teamReputation && (i->getPlayerTechnique()+i->getPlayerForm()/10) < teamReputation)
            {
                i->setTransferList(true);
                unsigned long long int askingPrice = ( ( (i->getPlayerValue() * i->getPlayerForm()) / 100 + (i->getPlayerValue() * i->getPlayerPA()) / (2020 - i->getPlayerBirthDay().toInt())) /100000) * 15000;
                i->setAskingPrice(askingPrice);
                pTeam->addTransferList(i);
            }
        }

        if( i->getPlayerPosition() == "AMC")
        {
            if( (i->getPlayerCA()+i->getPlayerForm()/10) < teamReputation && (i->getPlayerPassing()+i->getPlayerForm()/10) < teamReputation)
            {
                i->setTransferList(true);
                unsigned long long int askingPrice = ( ( (i->getPlayerValue() * i->getPlayerForm()) / 100 + (i->getPlayerValue() * i->getPlayerPA()) / (2020 - i->getPlayerBirthDay().toInt())) /100000) * 15000;
                i->setAskingPrice(askingPrice);
                pTeam->addTransferList(i);
            }
        }

        if( i->getPlayerPosition() == "ST")
        {
            if( (i->getPlayerCA()+i->getPlayerForm()/10) < teamReputation  && ( (i->getPlayerFinishing()+i->getPlayerForm()/10) < teamReputation))
            {
                i->setTransferList(true);
                unsigned long long int askingPrice = ( ( (i->getPlayerValue() * i->getPlayerForm()) / 100 + (i->getPlayerValue() * i->getPlayerPA()) / (2020 - i->getPlayerBirthDay().toInt())) /100000) * 15000;
                i->setAskingPrice(askingPrice);
                pTeam->addTransferList(i);
            }
        }
    }

    return pTeam;
}
