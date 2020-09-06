#include "MainWindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QColor>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAreaSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QPolarChart>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QGridLayout>
#include <QCategoryAxis>
#include <thread>
#include <QThread>
#include "MatchEngine.h"

QT_CHARTS_USE_NAMESPACE

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowIcon(QIcon ("C:/Users/temel/Documents/FM20/FootballManagerSimulation/icons/031-ball.png"));

    mToday = QDate(2020, 6, 1);

    init = false;
    connect( ui->LeagueComboBox, SIGNAL( currentTextChanged( const QString& ) ),this, SLOT( drawLeague( QString ) ) );

    //QPixmap pix("C:/Users/temel/Documents/FM20/FootballManagerSimulation/saha.webp");
    //ui->saha->setPixmap(pix.scaled(900, 600, Qt::KeepAspectRatio));

    QPolarChart *chart = new QPolarChart();

    QCategoryAxis *angularAxis = new QCategoryAxis;
    angularAxis->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
    angularAxis->setRange(0, 360);
    angularAxis->append("Cat 1", 90);

    QLineSeries *series1 = new QLineSeries();
    *series1 << QPointF(0, 60) << QPointF(90, -60) << QPointF(180, 50) << QPointF(270, 62) << QPointF(360, 60);

    QLineSeries *series2 = new QLineSeries();
    *series2 << QPointF(0, 0)<< QPointF(90, 0) << QPointF(180, 0) << QPointF(270, 0) << QPointF(360, 0);

    chart->addSeries(series1);
    chart->addSeries(series2);
    chart->addAxis(angularAxis, QPolarChart::PolarOrientationAngular);

    QValueAxis *radialAxis = new QValueAxis();
    radialAxis->setTickCount(9);
    radialAxis->setLabelFormat("%d");
    chart->addAxis(radialAxis, QPolarChart::PolarOrientationRadial);

    series1->attachAxis(radialAxis);
    series1->attachAxis(angularAxis);
    series2->attachAxis(radialAxis);
    series2->attachAxis(angularAxis);

    radialAxis->setRange(-100, 100);

    QChartView *chartView = new QChartView();
    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView, 0, 0);

    setIcons();
}

void piechart()
{
    QPieSeries *series = new QPieSeries();
    series->append("Jane", 1);
    series->append("Joe", 2);
    series->append("Andy", 3);
    series->append("Barbara", 4);
    series->append("Axel", 5);

    QPieSlice *slice = series->slices().at(1);
    slice->setExploded();
    slice->setLabelVisible();
    slice->setPen(QPen(Qt::darkGreen, 2));
    slice->setBrush(Qt::green);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple piechart example");
    chart->legend()->hide();

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    //ui->gridLayout->addWidget(chartView, 0, 0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setIcons()
{
    ui->MainScreen->setTabIcon(0, QIcon("C:/Users/temel/Documents/FM20/FootballManagerSimulation/icons/037-soccer_player.png"));
    ui->MainScreen->setTabIcon(1, QIcon("C:/Users/temel/Documents/FM20/FootballManagerSimulation/icons/046-strategy.png"));
    ui->MainScreen->setTabIcon(2, QIcon("C:/Users/temel/Documents/FM20/FootballManagerSimulation/icons/015-training.png"));
    ui->MainScreen->setTabIcon(3, QIcon("C:/Users/temel/Documents/FM20/FootballManagerSimulation/icons/050-star.png"));
    ui->MainScreen->setTabIcon(4, QIcon("C:/Users/temel/Documents/FM20/FootballManagerSimulation/icons/016-manager.png"));
    ui->MainScreen->setTabIcon(5, QIcon("C:/Users/temel/Documents/FM20/FootballManagerSimulation/icons/016-manager.png"));
    ui->MainScreen->setTabIcon(6, QIcon("C:/Users/temel/Documents/FM20/FootballManagerSimulation/icons/007-football-field.png"));
    ui->MainScreen->setTabIcon(7, QIcon("C:/Users/temel/Documents/FM20/FootballManagerSimulation/icons/003-trophy-1.png"));
    ui->MainScreen->setTabIcon(8, QIcon("C:/Users/temel/Documents/FM20/FootballManagerSimulation/icons/003-search.png"));
}

std::shared_ptr< Club > MainWindow::getMyClub()
{
    for(size_t i=0; i<mClubDatabase->allClubsInGame.size(); i++)
    {
        if( mClubDatabase->allClubsInGame[i]->getClubName() == mMyClubName)
        {
            mMyClub = (mClubDatabase->allClubsInGame[i]);
            return (mMyClub);
        }
    }
    return nullptr;
}

void MainWindow::showMyClub()
{
    ui->myTeam->setRowCount( getMyClub()->getPlayersInClub().size() );
    ui->myTeam->resizeColumnsToContents();
    ui->myTeam->horizontalHeader()->setVisible( true );

    ui->TeamValueLabel->setText( QString("%L2").arg( mMyClub->getClubValue() ) + " $" );
    ui->TeamSalaryLabel->setText( QString("%L2").arg( mMyClub->getClubSalary() ) + " $");
    ui->TeamTransferLabel->setText( QString("%L2").arg( mMyClub->getTransferBudget() ) + " $");


    int index = 0;

    QTableWidgetItem *temp = new QTableWidgetItem();
    temp->setTextAlignment( Qt::AlignCenter );

    for( auto i : getMyClub()->getPlayersInClub() )
    {
        QTableWidgetItem* pPlayerName = temp->clone();
        pPlayerName->setText(i->getPlayerName().split(" ")[0]);

        QTableWidgetItem* pPlayerSurname = temp->clone();
        pPlayerSurname->setText(i->getPlayerName().split(" ")[1]);

        QTableWidgetItem* pPlayerAge = temp->clone();
        pPlayerAge->setText(QString::number(2020 - i->getPlayerBirthDay().year()));

        QTableWidgetItem* pWage = temp->clone();
        pWage->setText(QString("%L2").arg(i->getPlayerWage()));

        QTableWidgetItem* pValue = temp->clone();
        pValue->setText(QString("%L2").arg(i->getPlayerValue()));

        QTableWidgetItem* pPosition = temp->clone();
        pPosition->setText(i->getPlayerPosition());

        QTableWidgetItem* pForm = temp->clone();
        pForm->setText(QString::number(i->getPlayerForm()));

        QTableWidgetItem* pMoral = temp->clone();
        pMoral->setText(QString::number(i->getMoral()));

        QTableWidgetItem* pCondition = temp->clone();
        pCondition->setText(QString::number(i->getCondition()));

        QTableWidgetItem* pNationality = temp->clone();
        pNationality->setText(i->getPlayerNationality());

        QTableWidgetItem* pExpires = temp->clone();
        pExpires->setText(i->getPlayerContractExpires());

        ui->myTeam->setItem(index, 0, pPlayerName);
        ui->myTeam->setItem(index, 1, pPlayerSurname);
        ui->myTeam->setItem(index, 2, pPlayerAge);
        ui->myTeam->setItem(index, 3, pWage);
        ui->myTeam->setItem(index, 4, pValue);
        ui->myTeam->setItem(index, 5, pPosition);
        ui->myTeam->setItem(index, 6, pForm);
        ui->myTeam->setItem(index, 7, pMoral);
        ui->myTeam->setItem(index, 8, pCondition);
        ui->myTeam->setItem(index, 9, pNationality);
        ui->myTeam->setItem(index, 10, pExpires);

        index++;
    }
}

void MainWindow::InitGame( QString pManagerName, QString pMyClub, std::vector<QString> pLeagueList )
{
    ui->MainScreen->widget(2)->setDisabled( true );

    mMyClubName = pMyClub;
    ui->TeamNameLabel->setText( mMyClubName );

    ui->playerArea->hide();

    ui->LeagueComboBox->addItem( "" );
    for(auto i : pLeagueList)
        ui->LeagueComboBox->addItem( i );

    mCreateWindow = std::shared_ptr< CreateGame > ( new CreateGame() );
    mCreateWindow->prepareDatabase( pManagerName, pMyClub, pLeagueList );

    mClubDatabase = mCreateWindow->getClubDatabase();
    ui->Datelabel->setText( mCreateWindow->getFullDate() );

    QString header = "Welcome to " + pMyClub;
    QString message = pMyClub + " kulübüne hoşgeldiniz.";

    createInbox( header, message );

    showMyClub();
    showTransferList();
    showScoutList();
}

void MainWindow::showMyInbox()
{
    int messageNumber = mInbox.size();
    int index = 0;

    ui->tableWidget->setRowCount( messageNumber );

    for (auto itr = mInbox.begin(); itr != mInbox.end(); ++itr)
    {
        ui->tableWidget->setCellWidget( index, 0, itr->first );
        index++;
    }
}

void MainWindow::createInbox( QString header, QString message )
{
    QPushButton* button = new QPushButton( header );

    //connect( button, SIGNAL ( released() ), &mapper, SLOT ( map() ) );
    //mapper.setMapping( button, message );

    //connect( &mapper, SIGNAL( mapped( QString ) ), this, SLOT( showMyMessage( QString ) ) );

    mInbox.insert( std::pair<QPushButton*, QString>( button, message ) );

    showMyInbox();
}

void MainWindow::showMyMessage(QString pMessage)
{
    ui->MessageInboxTextArea->setText(pMessage);
}

void MainWindow::showTransferList()
{
    ui->transferListTable->setRowCount(mMyClub->getPlayersInTransferList().size());
    ui->transferListTable->resizeColumnsToContents();

    int index = 0;

    QTableWidgetItem *temp = new QTableWidgetItem();
    temp->setTextAlignment(Qt::AlignCenter);

    for(auto i : mMyClub->getPlayersInTransferList())
    {
        QTableWidgetItem* playerName = temp->clone();
        playerName->setText(i->getPlayerName());

        QTableWidgetItem* playerValue = temp->clone();
        playerValue->setText(QString("%L2").arg(i->getPlayerValue()));

        QTableWidgetItem* askingValue = temp->clone();
        askingValue->setText(QString("%L2").arg(i->getAskingPrice()));

        QTableWidgetItem* position = temp->clone();
        position->setText(i->getPlayerPosition());

        ui->transferListTable->setItem(index, 0, playerName);
        ui->transferListTable->setItem(index, 1, playerValue);
        ui->transferListTable->setItem(index, 2, askingValue);
        ui->transferListTable->setItem(index, 3, position);

        index++;
    }
}

void MainWindow::showScoutList()
{
    ui->scoutListTable->setRowCount(mMyClub->getScoutingPlayers().size());
    ui->scoutListTable->resizeColumnsToContents();

    int index = 0;

    QTableWidgetItem *temp = new QTableWidgetItem();
    temp->setTextAlignment(Qt::AlignCenter);

    for(auto i : mMyClub->getScoutingPlayers())
    {
        QTableWidgetItem* playerName = temp->clone();
        playerName->setText(i.first->getPlayerName());

        QTableWidgetItem* playerValue = temp->clone();
        playerValue->setText(QString("%L2").arg(i.first->getPlayerValue()));

        QTableWidgetItem* myOffer = temp->clone();
        myOffer->setText(QString("%L2").arg(i.second));

        QTableWidgetItem* position = temp->clone();
        position->setText(i.first->getPlayerPosition());

        QTableWidgetItem* playerClub = temp->clone();
        playerClub->setText(i.first->getPlayerClub()->getClubName());

        ui->scoutListTable->setItem(index, 0, playerName);
        ui->scoutListTable->setItem(index, 1, playerValue);
        ui->scoutListTable->setItem(index, 2, myOffer);
        ui->scoutListTable->setItem(index, 3, position);
        ui->scoutListTable->setItem(index, 4, playerClub);

        index++;
    }
}

void MainWindow::on_myClub_cellClicked(int row, int column)
{
    if( column == 0 )
    {
        ui->MessageFrame->hide();
        ui->myTeam->hide();
        ui->playerArea->setGeometry(50,100, 1800, 750);

        QString playerName = ui->myTeam->item(row, column)->text();
        QString playerSurname = ui->myTeam->item(row, column+1)->text();
        QString playerValue = ui->myTeam->item(row, column+4)->text();

        ui->playerArea->show();

        for(auto i : mMyClub->getPlayersInClub())
        {
            if( QString("%L2").arg(i->getPlayerValue()) == playerValue )
            {
                mSelectedPlayer = i;
                break;
            }
        }

        QPixmap pix(mSelectedPlayer->getFacePath());
        ui->playerFace->setPixmap(pix.scaled(100, 100, Qt::KeepAspectRatio));

        if(mSelectedPlayer->isTransferList())
        {
            ui->addTransferListButton->setText("Remove from list");
        }
        else
        {
            ui->addTransferListButton->setText("Add Transfer List");
        }

        ui->playerNameLabel->setText(mSelectedPlayer->getPlayerName());

        if(mSelectedPlayer->getPlayerPosition() == "GK")
        {
            ui->reflexesLabel->show();
            ui->reflexes->show();

            ui->reflexesLabel->setText(QString::number(mSelectedPlayer->getPlayerReflexes()));
            if(mSelectedPlayer->getPlayerReflexes() <= 50)
                ui->reflexesLabel->setStyleSheet("QLabel { color : red; }");
            else
                ui->reflexesLabel->setStyleSheet("QLabel { color : blue; }");
        }
        else
        {
            ui->reflexesLabel->hide();
            ui->reflexes->hide();
        }

        ui->playerNameLabel->setText(mSelectedPlayer->getPlayerName());

        ui->tacklingLabel->setText(QString::number(mSelectedPlayer->getPlayerTackling()));
        if(mSelectedPlayer->getPlayerTackling() <= 50)
            ui->tacklingLabel->setStyleSheet("QLabel { color : red; }");
        else
            ui->tacklingLabel->setStyleSheet("QLabel { color : blue; }");

        ui->passingLabel->setText(QString::number(mSelectedPlayer->getPlayerPassing()));
        if(mSelectedPlayer->getPlayerPassing() <= 50)
            ui->passingLabel->setStyleSheet("QLabel { color : red; }");
        else
            ui->passingLabel->setStyleSheet("QLabel { color : blue; }");

        ui->techniqueLabel->setText(QString::number(mSelectedPlayer->getPlayerTechnique()));
        if(mSelectedPlayer->getPlayerTechnique() <= 50)
            ui->techniqueLabel->setStyleSheet("QLabel { color : red; }");
        else
            ui->techniqueLabel->setStyleSheet("QLabel { color : blue; }");

        ui->paceLabel->setText(QString::number(mSelectedPlayer->getPlayerPace()));
        if(mSelectedPlayer->getPlayerPace() <= 50)
            ui->paceLabel->setStyleSheet("QLabel { color : red; }");
        else
            ui->paceLabel->setStyleSheet("QLabel { color : blue; }");

        ui->finishingLabel->setText(QString::number(mSelectedPlayer->getPlayerFinishing()));
        if(mSelectedPlayer->getPlayerFinishing() <= 50)
            ui->finishingLabel->setStyleSheet("QLabel { color : red; }");
        else
            ui->finishingLabel->setStyleSheet("QLabel { color : blue; }");

        /*
        ui->transferOffers->setRowCount( mSelectedPlayer->getTransferOffer().size() );
        ui->transferOffers->resizeColumnsToContents();

        int index = 0;

        QTableWidgetItem *temp = new QTableWidgetItem();
        temp->setTextAlignment(Qt::AlignCenter);

        for(auto i : mSelectedPlayer->getTransferOffer())
        {
            QTableWidgetItem* ClubName = temp->clone();
            ClubName->setText(i.first->getClubName());

            QTableWidgetItem* offer = temp->clone();
            offer->setText(QString("%L2").arg(i.second));

            ui->transferOffers->setItem(index, 0, ClubName);
            ui->transferOffers->setItem(index, 1, offer);

            index++;
        }
        */
    }
}


void MainWindow::on_pushButton_clicked()
{
    int reputation = mMyClub->getClubReputation();

    bool transferList = ui->TransferListCheckBox->isChecked();
    bool freePlayers = ui->freePlayersCheckbox->isChecked();
    bool interested = ui->InterestedCheckBox->isChecked();

    QString position = ui->PositionComboBox->currentText();

    std::vector<std::shared_ptr< Player >> TransferMarketList;

    if( freePlayers == false )
    {
        for( auto i : mClubDatabase->allClubsInGame )
        {
            for( auto x : i->getPlayersInClub() )
            {
                if( x->isTransferList() == transferList  &&  ( x->getPlayerPosition() == position || position == "ALL" ) )
                {
                    if( interested == true )
                    {
                        if( reputation >= x->getMinimumInterestReputation() )
                        {
                            TransferMarketList.push_back(x);
                        }
                    }
                    else
                    {
                        TransferMarketList.push_back(x);
                    }
                }
            }
        }
    }
    else
    {
        for( auto i : mCreateWindow->getFreePlayers() )
        {
            if( i->getPlayerPosition() == position || position == "ALL" )
            {
                if( interested == true )
                {
                    if( reputation >= i->getMinimumInterestReputation() )
                    {
                        TransferMarketList.push_back(i);
                    }
                }
                else
                {
                    TransferMarketList.push_back(i);
                }
            }
        }
    }

    ui->transferTable->setRowCount( TransferMarketList.size() );
    ui->transferTable->resizeColumnsToContents();

    int index = 0;

    QTableWidgetItem *temp = new QTableWidgetItem();
    temp->setTextAlignment( Qt::AlignCenter );

    for( auto i : TransferMarketList )
    {
        QTableWidgetItem* pPlayerName = temp->clone();
        pPlayerName->setText( i->getPlayerName() );

        QTableWidgetItem* pPlayerClub = temp->clone();
        pPlayerClub->setText( i->getPlayerClub()->getClubName() );

        QTableWidgetItem* pPlayerNationality = temp->clone();
        pPlayerNationality->setText( i->getPlayerNationality() );

        QTableWidgetItem* pPlayerAge = temp->clone();
        pPlayerAge->setText( QString::number( 2020 - i->getPlayerBirthDay().year() ) );

        QTableWidgetItem* pWage = temp->clone();
        pWage->setText( QString( "%L2" ).arg(i->getPlayerWage() ) );

        QTableWidgetItem* pValue = temp->clone();
        pValue->setText(QString( "%L2" ).arg( i->getPlayerValue() ) );

        QTableWidgetItem* pAskingPrice = temp->clone();
        if( i->getAskingPrice() == 0 )
            pAskingPrice->setText( "unkown" );
        else
            pAskingPrice->setText( QString( "%L2" ).arg( i->getAskingPrice() ) );

        QTableWidgetItem* pPosition = temp->clone();
        pPosition->setText( i->getPlayerPosition() );

        QTableWidgetItem* pForm = temp->clone();
        pForm->setText( QString::number(i->getPlayerForm() ) );

        QTableWidgetItem* pExpires = temp->clone();
        pExpires->setText( i->getPlayerContractExpires() );


        QTableWidgetItem* pReflexes = temp->clone();
        pReflexes->setText( QString::number(i->getPlayerReflexes() ) );
        if( i->getPlayerReflexes() <= 50 )
            pReflexes->setForeground( QColor( Qt::red ) );
        else
            pReflexes->setForeground( QColor( Qt::blue ) );


        QTableWidgetItem* pTackling = temp->clone();
        pTackling->setText( QString::number(i->getPlayerTackling() ) );
        if( i->getPlayerTackling() <= 50 )
            pTackling->setForeground( QColor( Qt::red ) );
        else
            pTackling->setForeground( QColor( Qt::blue ) );


        QTableWidgetItem* pPassing = temp->clone();
        pPassing->setText( QString::number(i->getPlayerPassing() ) );
        if( i->getPlayerPassing() <= 50 )
            pPassing->setForeground( QColor( Qt::red ) );
        else
            pPassing->setForeground( QColor( Qt::blue ) );


        QTableWidgetItem* pTechnique = temp->clone();
        pTechnique->setText( QString::number( i->getPlayerTechnique() ) );
        if( i->getPlayerTechnique() <= 50 )
            pTechnique->setForeground( QColor( Qt::red ) );
        else
            pTechnique->setForeground( QColor( Qt::blue ) );


        QTableWidgetItem* pPace = temp->clone();
        pPace->setText( QString::number(i->getPlayerPace() ) );
        if( i->getPlayerPace() <= 50 )
            pPace->setForeground( QColor( Qt::red ) );
        else
            pPace->setForeground( QColor( Qt::blue ) );


        QTableWidgetItem* pFinishing = temp->clone();
        pFinishing->setText( QString::number(i->getPlayerFinishing() ) );
        if( i->getPlayerFinishing() <= 50 )
            pFinishing->setForeground( QColor( Qt::red ) );
        else
            pFinishing->setForeground( QColor( Qt::blue ) );


        ui->transferTable->setItem( index, 0, pPlayerName );
        ui->transferTable->setItem( index, 1, pPlayerClub );
        ui->transferTable->setItem( index, 2, pPlayerNationality );
        ui->transferTable->setItem( index, 3, pPlayerAge );
        ui->transferTable->setItem( index, 4, pWage );
        ui->transferTable->setItem( index, 5, pValue );
        ui->transferTable->setItem( index, 6, pAskingPrice );
        ui->transferTable->setItem( index, 7, pPosition );
        ui->transferTable->setItem( index, 8, pForm );
        ui->transferTable->setItem( index, 9, pExpires );

        ui->transferTable->setItem( index, 10,  pReflexes );
        ui->transferTable->setItem( index, 11, pTackling );
        ui->transferTable->setItem( index, 12, pPassing );
        ui->transferTable->setItem( index, 13, pTechnique );
        ui->transferTable->setItem( index, 14, pPace );
        ui->transferTable->setItem( index, 15, pFinishing );

        index++;
    }
}


void MainWindow::drawLeague( QString pLeagueName )
{
    qDebug() << "pLeagueName : " << pLeagueName << endl;

    if( init && !pLeagueName.isEmpty() )
    {
        for(auto i : mCreateWindow->getAllLeaguesInGame())
        {
            if(i->getLeagueName() == pLeagueName)
            {
                int index = 0;
                ui->LeagueTable->setRowCount( i->getAllClubs().size() );
                ui->LeagueTable->resizeColumnsToContents();

                for( auto x : i->getAllClubs() )
                {
                    ui->LeagueTable->setItem(index, 0, new QTableWidgetItem(x->getClubName()));
                    ui->LeagueTable->setItem(index, 1, new QTableWidgetItem("0"));
                    ui->LeagueTable->setItem(index, 2, new QTableWidgetItem("0"));
                    ui->LeagueTable->setItem(index, 3, new QTableWidgetItem("0"));
                    ui->LeagueTable->setItem(index, 4, new QTableWidgetItem("0"));
                    ui->LeagueTable->setItem(index, 5, new QTableWidgetItem("0"));
                    ui->LeagueTable->setItem(index, 6, new QTableWidgetItem("0"));
                    ui->LeagueTable->setItem(index, 7, new QTableWidgetItem("0"));
                    ui->LeagueTable->setItem(index, 8, new QTableWidgetItem("0"));

                    index++;
                }
                break;
            }
        }
    }
    else
    {
        init = true;
    }

}

void MainWindow::on_ProgressButton_clicked()
{
    mToday = mToday.addDays(1);
    mInbox.clear();
    ui->MessageInboxTextArea->clear();

    bool isTomorrowMatch = false;

    for(auto i : mCreateWindow->getAllLeaguesInGame())
    {
        for(auto x : i->getAllMatchByDate(mToday.addDays(1)))
        {
            if((x->getAwayClub() == mMyClub)  || (x->getHomeClub() == mMyClub))
            {
                QString message = x->getHomeClub()->getClubName()+ " - " + x->getAwayClub()->getClubName();
                createInbox("Your next match", message);
                isTomorrowMatch = true;
                break;
            }
        }

    }

    ui->Datelabel->setText( QString::number( mToday.day() ) + "." + QString::number( mToday.month() ) + "." + QString::number( mToday.year() ) );
}

void MainWindow::setMatchUI( std::shared_ptr< Match > x )
{
    if( ( x->getAwayClub() == mMyClub )  || ( x->getHomeClub() == mMyClub ) )
    {
        ui->MainScreen->widget(2)->setDisabled( false );
        ui->MainScreen->setCurrentIndex(2);

        ui->MainScreen->widget(0)->setDisabled( true );
        ui->MainScreen->widget(1)->setDisabled( true );
        ui->MainScreen->widget(3)->setDisabled( true );
        ui->MainScreen->widget(4)->setDisabled( true );

        ui->ProgressButton->setDisabled( true );

        while( x->getHomeClub()->getMatchPlayers().size() != 11 )
        {
            qDebug() << "Home Club prepare Club" << endl;
            x->getHomeClub()->prepareMatchPlayers();
        }

        while( x->getAwayClub()->getMatchPlayers().size() != 11 )
        {
            qDebug() << "Away Club prepare Club" << endl;
            x->getAwayClub()->prepareMatchPlayers();
        }

        tMatch = x;

        ui->team_left->resizeColumnsToContents();
        ui->team_right->resizeColumnsToContents();

        ui->team_left->horizontalHeader()->setVisible( true );
        ui->team_right->horizontalHeader()->setVisible( true );

        ui->team_left_sub->resizeColumnsToContents();
        ui->team_right_sub->resizeColumnsToContents();

        ui->team_left_sub->horizontalHeader()->setVisible( true );
        ui->team_right_sub->horizontalHeader()->setVisible( true );

        ui->hometeam->setText( tMatch->getHomeClub()->getClubName() );
        ui->awayteam->setText( tMatch->getAwayClub()->getClubName() );

        ui->home_formation->setText( x->getHomeClub()->getClubManager()->getFormation() );
        ui->away_formation->setText( x->getAwayClub()->getClubManager()->getFormation() );

        ui->home_tackling->setText( x->getHomeClub()->getClubManager()->getTackling() );
        ui->away_tackling->setText( x->getAwayClub()->getClubManager()->getTackling() );

        ui->home_gamestyle->setText( x->getHomeClub()->getClubManager()->getManagerGameStyle() );
        ui->away_gamestyle->setText( x->getAwayClub()->getClubManager()->getManagerGameStyle() );

        ui->home_longshot->setText( x->getHomeClub()->getClubManager()->getLongShots() );
        ui->away_longshot->setText( x->getAwayClub()->getClubManager()->getLongShots() );

        ui->home_attackposition->setText( x->getHomeClub()->getClubManager()->getAttackPosition() );
        ui->away_attackposition->setText( x->getAwayClub()->getClubManager()->getAttackPosition() );


        QTableWidgetItem *temp = new QTableWidgetItem();
        temp->setTextAlignment(Qt::AlignCenter);

        int Club_left_index = 0;
        for(auto i : x->getHomeClub()->getMatchPlayers())
        {
            QTableWidgetItem* playerName = temp->clone();
            playerName->setText(i->getPlayerName());

            QTableWidgetItem* playerPosition = temp->clone();
            playerPosition->setText(i->getPlayerPosition());

            QTableWidgetItem* playerForm = temp->clone();
            playerForm->setText(QString::number(i->getPlayerForm()));

            ui->team_left->setItem(Club_left_index, 0, playerName);
            ui->team_left->setItem(Club_left_index, 1, playerPosition);
            ui->team_left->setItem(Club_left_index, 2, playerForm);
            Club_left_index++;
        }

        int Club_left_index_sub_index = 0;
        for(auto i : x->getHomeClub()->getSubMatchPlayers())
        {
            QTableWidgetItem* playerName = temp->clone();
            playerName->setText(i->getPlayerName());

            QTableWidgetItem* playerPosition = temp->clone();
            playerPosition->setText(i->getPlayerPosition());

            QTableWidgetItem* playerForm = temp->clone();
            playerForm->setText(QString::number(i->getPlayerForm()));

            ui->team_left_sub->setItem(Club_left_index_sub_index, 0, playerName);
            ui->team_left_sub->setItem(Club_left_index_sub_index, 1, playerPosition);
            ui->team_left_sub->setItem(Club_left_index_sub_index, 2, playerForm);
            Club_left_index_sub_index++;
        }



        int Club_right_index_index = 0;
        for(auto i : x->getAwayClub()->getMatchPlayers())
        {
            QTableWidgetItem* playerName = temp->clone();
            playerName->setText(i->getPlayerName());

            QTableWidgetItem* playerPosition = temp->clone();
            playerPosition->setText(i->getPlayerPosition());

            QTableWidgetItem* playerForm = temp->clone();
            playerForm->setText(QString::number(i->getPlayerForm()));

            ui->team_right->setItem(Club_right_index_index, 0, playerName);
            ui->team_right->setItem(Club_right_index_index, 1, playerPosition);
            ui->team_right->setItem(Club_right_index_index, 2, playerForm);
            Club_right_index_index++;
        }

        int Club_right_index_sub_index = 0;
        for(auto i : x->getAwayClub()->getSubMatchPlayers())
        {
            QTableWidgetItem* playerName = temp->clone();
            playerName->setText(i->getPlayerName());

            QTableWidgetItem* playerPosition = temp->clone();
            playerPosition->setText(i->getPlayerPosition());

            QTableWidgetItem* playerForm = temp->clone();
            playerForm->setText(QString::number(i->getPlayerForm()));

            ui->team_right_sub->setItem(Club_right_index_sub_index, 0, playerName);
            ui->team_right_sub->setItem(Club_right_index_sub_index, 1, playerPosition);
            ui->team_right_sub->setItem(Club_right_index_sub_index, 2, playerForm);
            Club_right_index_sub_index++;
        }
    }
}
void MainWindow::on_freePlayersCheckbox_stateChanged(int arg1)
{
    if(arg1 == 0)
    {
        ui->TransferListCheckBox->setCheckState(Qt::CheckState::Checked);
    }
    else if(arg1 == 2)
    {
        ui->TransferListCheckBox->setCheckState(Qt::CheckState::Unchecked);
    }

}

void MainWindow::on_LeagueTable_cellClicked(int row, int column)
{
    std::shared_ptr< Club > currentClub = nullptr;
    if(column == 0)
    {
        QString ClubName = ui->LeagueTable->item(row, column)->text();

        for(auto i : mClubDatabase->allClubsInGame)
            if(i->getClubName() == ClubName)
            {
                currentClub = i;
                break;
            }


        ui->selectedTeam->setRowCount(currentClub->getPlayersInClub().size());
        ui->selectedTeam->resizeColumnsToContents();

        int index = 0;

        QTableWidgetItem *temp = new QTableWidgetItem();
        temp->setTextAlignment(Qt::AlignCenter);

        for(auto i : currentClub->getPlayersInClub())
        {
            QTableWidgetItem* pPlayerName = temp->clone();
            pPlayerName->setText(i->getPlayerName().split(" ")[0]);

            QTableWidgetItem* pPlayerSurname = temp->clone();
            pPlayerSurname->setText(i->getPlayerName().split(" ")[1]);

            QTableWidgetItem* pPlayerAge = temp->clone();
            pPlayerAge->setText(QString::number(2020 - i->getPlayerBirthDay().year()));

            QTableWidgetItem* pWage = temp->clone();
            pWage->setText(QString("%L2").arg(i->getPlayerWage()));

            QTableWidgetItem* pValue = temp->clone();
            pValue->setText(QString("%L2").arg(i->getPlayerValue()));

            QTableWidgetItem* pAskingPrice = temp->clone();
            if(i->getAskingPrice() == 0)
                pAskingPrice->setText("unkown");
            else
                pAskingPrice->setText(QString("%L2").arg(i->getAskingPrice()));

            QTableWidgetItem* pPosition = temp->clone();
            pPosition->setText(i->getPlayerPosition());

            QTableWidgetItem* pForm = temp->clone();
            pForm->setText(QString::number(i->getPlayerForm()));

            QTableWidgetItem* pExpires = temp->clone();
            pExpires->setText(i->getPlayerContractExpires());

            QTableWidgetItem* pReflexes = temp->clone();
            pReflexes->setText(QString::number(i->getPlayerReflexes()));
            if(i->getPlayerReflexes() <= 50)
                pReflexes->setForeground(QColor(Qt::red));
            else
                pReflexes->setForeground(QColor(Qt::blue));


            QTableWidgetItem* pTackling = temp->clone();
            pTackling->setText(QString::number(i->getPlayerTackling()));
            if(i->getPlayerTackling() <= 50)
                pTackling->setForeground(QColor(Qt::red));
            else
                pTackling->setForeground(QColor(Qt::blue));


            QTableWidgetItem* pPassing = temp->clone();
            pPassing->setText(QString::number(i->getPlayerPassing()));
            if(i->getPlayerPassing() <= 50)
                pPassing->setForeground(QColor(Qt::red));
            else
                pPassing->setForeground(QColor(Qt::blue));


            QTableWidgetItem* pTechnique = temp->clone();
            pTechnique->setText(QString::number(i->getPlayerTechnique()));
            if(i->getPlayerTechnique() <= 50)
                pTechnique->setForeground(QColor(Qt::red));
            else
                pTechnique->setForeground(QColor(Qt::blue));


            QTableWidgetItem* pPace = temp->clone();
            pPace->setText(QString::number(i->getPlayerPace()));
            if(i->getPlayerPace() <= 50)
                pPace->setForeground(QColor(Qt::red));
            else
                pPace->setForeground(QColor(Qt::blue));


            QTableWidgetItem* pFinishing = temp->clone();
            pFinishing->setText(QString::number(i->getPlayerFinishing()));
            if(i->getPlayerFinishing() <= 50)
                pFinishing->setForeground(QColor(Qt::red));
            else
                pFinishing->setForeground(QColor(Qt::blue));

            ui->selectedTeam->setItem(index, 0, pPlayerName);
            ui->selectedTeam->setItem(index, 1, pPlayerSurname);
            ui->selectedTeam->setItem(index, 2, pPlayerAge);
            ui->selectedTeam->setItem(index, 3, pWage);
            ui->selectedTeam->setItem(index, 4, pValue);
            ui->selectedTeam->setItem(index, 5, pAskingPrice);
            ui->selectedTeam->setItem(index, 6, pPosition);
            ui->selectedTeam->setItem(index, 7, pForm);
            ui->selectedTeam->setItem(index, 8, pExpires);

            ui->selectedTeam->setItem(index, 9,  pReflexes);
            ui->selectedTeam->setItem(index, 10, pTackling);
            ui->selectedTeam->setItem(index, 11, pPassing);
            ui->selectedTeam->setItem(index, 12, pTechnique);
            ui->selectedTeam->setItem(index, 13, pPace);
            ui->selectedTeam->setItem(index, 14, pFinishing);

            index++;
        }
    }
}

void MainWindow::on_releasePlayerButton_clicked()
{
    unsigned fine = mSelectedPlayer->getPlayerWage() * (12*(mSelectedPlayer->getPlayerContractExpires().split(".")[2].toInt() - mCreateWindow->mYear) + (mSelectedPlayer->getPlayerContractExpires().split(".")[1].toInt()-mCreateWindow->mMonth));

    if(fine == 0)
        fine = mSelectedPlayer->getPlayerWage();

    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Release Player",
                                                              mSelectedPlayer->getPlayerName() + " adlı oyuncuyu " + QString("%L2").arg(fine) + " karşılığında serbest bırakmak istiyor musunuz ?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        if(mMyClub->getTransferBudget() >= fine)
        {
            mMyClub->decreaseTransferBudget(fine);
            mMyClub->removePlayer(mSelectedPlayer);

            mCreateWindow->addFreePlayer(mSelectedPlayer);

            createInbox(mSelectedPlayer->getPlayerName().split(" ")[0]+" released", mSelectedPlayer->getPlayerName()+" will be released tomorrow");
            //mSelectedPlayer->getTransferOffer().clear();
            ui->playerArea->hide();
            showMyClub();
        }
    }
}

void MainWindow::on_addTransferListButton_clicked()
{
    if(mSelectedPlayer->isTransferList())
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                                  "Transfer List",
                                                                  mSelectedPlayer->getPlayerName() + " adlı oyuncuyu transfer listesinden çıkarmak istiyor musunuz ?",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            createInbox(mSelectedPlayer->getPlayerName().split(" ")[0]+" is not in transfer list", mSelectedPlayer->getPlayerName()+" remove from the transfer list.Player is happy.");

            mSelectedPlayer->setTransferList(false);
            mSelectedPlayer->setAskingPrice(0);
            mMyClub->removeTransferList(mSelectedPlayer);
            ui->addTransferListButton->setText("Add Transfer List");
            showTransferList();
        }
    }
    else
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                                  "Transfer List",
                                                                  mSelectedPlayer->getPlayerName() + " adlı oyuncuyu transfer listesine eklemek istiyor musunuz ?",
                                                                  QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes)
        {
            createInbox(mSelectedPlayer->getPlayerName().split(" ")[0]+" in transfer list", mSelectedPlayer->getPlayerName()+" added to the transfer list.Player is unhappy.");

            mSelectedPlayer->setTransferList(true);
            mSelectedPlayer->setAskingPrice(mSelectedPlayer->getPlayerValue()/2);
            mMyClub->addTransferList(mSelectedPlayer);
            ui->addTransferListButton->setText("Remove from list");
            showTransferList();
        }
    }
}

void MainWindow::on_playMatchButton_clicked()
{
    MatchEngine* tMatchEngine = new MatchEngine(ui);

    //QThreadPool::globalInstance()->start(tMatchEngine);
    tMatchEngine->startMatch(tMatch);

    qDebug() << "Hello world from GUI thread" <<  QThread::currentThread() << endl;

}

void MainWindow::on_pushButton_2_clicked()
{
    ui->playerArea->hide();
    ui->MessageFrame->show();
    ui->myTeam->show();
}
