#include "gamemenu.h"
#include "ui_gamemenu.h"


GameMenu::GameMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameMenu),
    mLeagueNumber(0)
{
    ui->setupUi(this);
    setDatabase();
}

GameMenu::~GameMenu()
{
    delete ui;
}

void GameMenu::setDatabase()
{
    mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("C:/Users/temel/Desktop/FM.db");

    if(!mydb.open())
        qDebug() << "failed to open the database" << endl;
    else
        drawLeagues();

    mydb.close();
}

void GameMenu::drawLeagues()
{
    int x = 50;
    int y = 100;

    int index = 1;

    for(auto i : getLeaguesFromDatabase())
    {
        QCheckBox *checkbox = new QCheckBox(i, this);
        checkbox->setGeometry(x, y+(50*index), 150, 50);
        checkbox->setCheckState(Qt::CheckState::Checked);
        mCheckBox.push_back(checkbox);
        index++;
    }
}

std::vector<QString> GameMenu::getLeaguesFromDatabase()
{
    QSqlQuery leagueSQL("SELECT * FROM LEAGUES");
    int leagues = leagueSQL.record().indexOf("LEAGUES");
    //int leagueReputation = leagueSQL.record().indexOf("REPUTATION");
    int leagueCountry = leagueSQL.record().indexOf("COUNTRY");
    //int leagueDivision = leagueSQL.record().indexOf("DIVISION");

    std::vector<QString> temp;

    while (leagueSQL.next())
    {
       QString pLeagueName = leagueSQL.value(leagues).toString();
       //QString pLeagueReputation = leagueSQL.value(leagueReputation).toString();
       QString pLeagueCountry = leagueSQL.value(leagueCountry).toString();
       //QString pLeagueDivision = leagueSQL.value(leagueDivision).toString();
       temp.push_back(pLeagueName);
    }
    mLeagueNumber = temp.size();
    return temp;
}

void GameMenu::on_startGame_clicked()
{
    std::vector<QString> temp;

    for(auto i : mCheckBox)
        if(i->isChecked())
                temp.push_back(i->text());

    QString pManagerName = ui->lineEdit->text();

    if(temp.size() != 0 && pManagerName != "")
    {
        this->close();

        mMainWindow = new MainWindow(this);
        mMainWindow->InitGame(pManagerName, "Trabzonspor", temp);
        mMainWindow->show();
    }

}
