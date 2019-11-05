#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QColor>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mToday = QDate(2020, 6, 1);

    init = false;
    connect(ui->LeagueComboBox, SIGNAL(currentTextChanged(const QString&)),this, SLOT(drawLeague(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mCreateWindow;
}

Team* MainWindow::getMyTeam()
{
    for(auto i : mTeamDatabase->allTeamsInGame)
    {
        if( i->getTeamName() == mMyTeamName)
        {
            mMyTeam = i;
            return mMyTeam;
        }
    }
    return nullptr;
}

void MainWindow::showMyTeam()
{
    ui->myTeam->setRowCount(getMyTeam()->getPlayersInTeam().size());
    ui->myTeam->resizeColumnsToContents();

    ui->TeamValueLabel->setText(QString("%L2").arg(mMyTeam->getTeamValue()) + " $");
    ui->TeamSalaryLabel->setText(QString("%L2").arg(mMyTeam->getTeamSalary()) + " $");
    ui->TeamTransferLabel->setText(QString("%L2").arg(mMyTeam->getTransferBudget()) + " $");


    int index = 0;

    QTableWidgetItem *temp = new QTableWidgetItem();
    temp->setTextAlignment(Qt::AlignCenter);

    for(auto i : getMyTeam()->getPlayersInTeam())
    {
        QTableWidgetItem* pPlayerName = temp->clone();
        pPlayerName->setText(i->getPlayerName().split(" ")[0]);

        QTableWidgetItem* pPlayerSurname = temp->clone();
        pPlayerSurname->setText(i->getPlayerName().split(" ")[1]);

        QTableWidgetItem* pPlayerAge = temp->clone();
        pPlayerAge->setText(QString::number(2020 - i->getPlayerBirthDay().toInt()));

        QTableWidgetItem* pWage = temp->clone();
        pWage->setText(QString("%L2").arg(i->getPlayerWage()));

        QTableWidgetItem* pValue = temp->clone();
        pValue->setText(QString("%L2").arg(i->getPlayerValue()));

        QTableWidgetItem* pPosition = temp->clone();
        pPosition->setText(i->getPlayerPosition());

        QTableWidgetItem* pForm = temp->clone();
        pForm->setText(QString::number(i->getPlayerForm()));

        QTableWidgetItem* pExpires = temp->clone();
        pExpires->setText(i->getPlayerContractExpires());


        ui->myTeam->setItem(index, 0, pPlayerName);
        ui->myTeam->setItem(index, 1, pPlayerSurname);
        ui->myTeam->setItem(index, 2, pPlayerAge);
        ui->myTeam->setItem(index, 3, pWage);
        ui->myTeam->setItem(index, 4, pValue);
        ui->myTeam->setItem(index, 5, pPosition);
        ui->myTeam->setItem(index, 6, pForm);
        ui->myTeam->setItem(index, 7, pExpires);

        index++;
    }
}

void MainWindow::InitGame(QString pManagerName, QString pMyTeam, std::vector<QString> pLeagueList)
{
    ui->MainScreen->widget(2)->setDisabled(true);

    mMyTeamName = pMyTeam;
    ui->TeamNameLabel->setText(mMyTeamName);

    ui->playerArea->hide();

    ui->LeagueComboBox->addItem("");
    for(auto i : pLeagueList)
        ui->LeagueComboBox->addItem(i);

    mCreateWindow = new CreateGame();
    mCreateWindow->prepareDatabase(pManagerName, pMyTeam, pLeagueList);

    mTeamDatabase = mCreateWindow->getTeamDatabase();
    ui->Datelabel->setText(mCreateWindow->getFullDate());

    QString header = "Welcome to " + pMyTeam;
    QString message = pMyTeam + " klübüne hoşgeldiniz.";

    createInbox(header, message);

    showMyTeam();
    showTransferList();
    showScoutList();
}

void MainWindow::showMyInbox()
{
    int messageNumber = mInbox.size();
    int index = 0;

    ui->tableWidget->setRowCount(messageNumber);

    for (auto itr = mInbox.begin(); itr != mInbox.end(); ++itr)
    {
        ui->tableWidget->setCellWidget( index, 0, itr->first );
        index++;
    }
}

void MainWindow::showPlayerDetails()
{

}

void MainWindow::createInbox(QString header, QString message)
{
    QPushButton* button = new QPushButton(header);

    connect(button, SIGNAL (released()), &mapper, SLOT (map()));
    mapper.setMapping(button, message);

    connect(&mapper, SIGNAL(mapped(QString)), this, SLOT(showMyMessage(QString)));

    mInbox.insert(std::pair<QPushButton*, QString>(button, message));

    showMyInbox();
}

void MainWindow::showMyMessage(QString pMessage)
{
    ui->MessageInboxTextArea->setText(pMessage);
}

void MainWindow::showTransferList()
{
    ui->transferListTable->setRowCount(mMyTeam->getPlayersInTransferList().size());
    ui->transferListTable->resizeColumnsToContents();

    int index = 0;

    QTableWidgetItem *temp = new QTableWidgetItem();
    temp->setTextAlignment(Qt::AlignCenter);

    for(auto i : mMyTeam->getPlayersInTransferList())
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
    ui->scoutListTable->setRowCount(mMyTeam->getScoutingPlayers().size());
    ui->scoutListTable->resizeColumnsToContents();

    int index = 0;

    QTableWidgetItem *temp = new QTableWidgetItem();
    temp->setTextAlignment(Qt::AlignCenter);

    for(auto i : mMyTeam->getScoutingPlayers())
    {
        QTableWidgetItem* playerName = temp->clone();
        playerName->setText(i.first->getPlayerName());

        QTableWidgetItem* playerValue = temp->clone();
        playerValue->setText(QString("%L2").arg(i.first->getPlayerValue()));

        QTableWidgetItem* myOffer = temp->clone();
        myOffer->setText(QString("%L2").arg(i.second));

        QTableWidgetItem* position = temp->clone();
        position->setText(i.first->getPlayerPosition());

        QTableWidgetItem* playerTeam = temp->clone();
        playerTeam->setText(i.first->getPlayerTeam());

        ui->scoutListTable->setItem(index, 0, playerName);
        ui->scoutListTable->setItem(index, 1, playerValue);
        ui->scoutListTable->setItem(index, 2, myOffer);
        ui->scoutListTable->setItem(index, 3, position);
        ui->scoutListTable->setItem(index, 4, playerTeam);

        index++;
    }
}

void MainWindow::on_myTeam_cellClicked(int row, int column)
{
    if(column == 0)
    {
        QString playerName = ui->myTeam->item(row, column)->text();
        QString playerSurname = ui->myTeam->item(row, column+1)->text();
        QString playerValue = ui->myTeam->item(row, column+4)->text();

        ui->playerArea->show();

        for(auto i : mMyTeam->getPlayersInTeam())
        {
            if( QString("%L2").arg(i->getPlayerValue()) == playerValue )
            {
                mSelectedPlayer = i;
                break;
            }
        }

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
                ui->reflexesLabel->setStyleSheet("QLabel { color : green; }");
            else
                ui->reflexesLabel->setStyleSheet("QLabel { color : red; }");
        }
        else
        {
            ui->reflexesLabel->hide();
            ui->reflexes->hide();
        }

        ui->playerNameLabel->setText(mSelectedPlayer->getPlayerName());

        ui->tacklingLabel->setText(QString::number(mSelectedPlayer->getPlayerTackling()));
        if(mSelectedPlayer->getPlayerTackling() <= 50)
            ui->tacklingLabel->setStyleSheet("QLabel { color : green; }");
        else
            ui->tacklingLabel->setStyleSheet("QLabel { color : red; }");

        ui->passingLabel->setText(QString::number(mSelectedPlayer->getPlayerPassing()));
        if(mSelectedPlayer->getPlayerPassing() <= 50)
            ui->passingLabel->setStyleSheet("QLabel { color : green; }");
        else
            ui->passingLabel->setStyleSheet("QLabel { color : red; }");

        ui->techniqueLabel->setText(QString::number(mSelectedPlayer->getPlayerTechnique()));
        if(mSelectedPlayer->getPlayerTechnique() <= 50)
            ui->techniqueLabel->setStyleSheet("QLabel { color : green; }");
        else
            ui->techniqueLabel->setStyleSheet("QLabel { color : red; }");

        ui->paceLabel->setText(QString::number(mSelectedPlayer->getPlayerPace()));
        if(mSelectedPlayer->getPlayerPace() <= 50)
            ui->paceLabel->setStyleSheet("QLabel { color : green; }");
        else
            ui->paceLabel->setStyleSheet("QLabel { color : red; }");

        ui->finishingLabel->setText(QString::number(mSelectedPlayer->getPlayerFinishing()));
        if(mSelectedPlayer->getPlayerFinishing() <= 50)
            ui->finishingLabel->setStyleSheet("QLabel { color : green; }");
        else
            ui->finishingLabel->setStyleSheet("QLabel { color : red; }");


        ui->transferOffers->setRowCount(mSelectedPlayer->getTransferOffer().size());
        ui->transferOffers->resizeColumnsToContents();

        int index = 0;

        QTableWidgetItem *temp = new QTableWidgetItem();
        temp->setTextAlignment(Qt::AlignCenter);

        for(auto i : mSelectedPlayer->getTransferOffer())
        {
            QTableWidgetItem* teamName = temp->clone();
            teamName->setText(i.first->getTeamName());

            QTableWidgetItem* offer = temp->clone();
            offer->setText(QString("%L2").arg(i.second));

            ui->transferOffers->setItem(index, 0, teamName);
            ui->transferOffers->setItem(index, 1, offer);

            index++;
        }

    }
}


void MainWindow::on_pushButton_clicked()
{
    int reputation = mMyTeam->getTeamAvaragePoint() + 10;

    bool transferList = ui->TransferListCheckBox->isChecked();
    bool freePlayers = ui->freePlayersCheckbox->isChecked();
    bool interested = ui->InterestedCheckBox->isChecked();

    QString position = ui->PositionComboBox->currentText();

    std::vector<Player*> tempTransferList;

    if(transferList == false)
    {
        if(freePlayers == false)
        {
            for(auto i : mTeamDatabase->allTeamsInGame)
                for(auto x : i->getPlayersInTeam())
                    if(interested)
                    {
                        if(( (x->getPlayerCA()+x->getPlayerForm()/10) < reputation))
                        {
                            if(x->getPlayerPosition() == position)
                                tempTransferList.push_back(x);
                            else if(position == "ALL")
                                tempTransferList.push_back(x);
                        }
                    }
                    else
                    {
                        if(x->getPlayerPosition() == position)
                            tempTransferList.push_back(x);
                        else if(position == "ALL")
                            tempTransferList.push_back(x);
                    }
        }
        else
        {
            for(auto x : mCreateWindow->getFreePlayers())
                if(interested)
                {
                    if(( (x->getPlayerCA()+x->getPlayerForm()/10) < reputation))
                    {
                        if(x->getPlayerPosition() == position)
                            tempTransferList.push_back(x);
                        else if(position == "ALL")
                            tempTransferList.push_back(x);
                    }
                }
                else
                {
                    if(x->getPlayerPosition() == position)
                        tempTransferList.push_back(x);
                    else if(position == "ALL")
                        tempTransferList.push_back(x);
                }
        }
    }
    else
    {
        for(auto i : mTeamDatabase->allTeamsInGame)
            for(auto x : i->getPlayersInTransferList())
                if(x->isTransferList())
                {
                    if(interested)
                    {
                        if( (x->getPlayerCA()+x->getPlayerForm()/10) < reputation)
                        {
                            if(x->getPlayerPosition() == position)
                                tempTransferList.push_back(x);
                        else if(position == "ALL")
                                tempTransferList.push_back(x);
                        }
                    }
                    else
                    {
                        if(x->getPlayerPosition() == position)
                            tempTransferList.push_back(x);
                        else if(position == "ALL")
                            tempTransferList.push_back(x);
                    }
                }
    }

    ui->transferTable->setRowCount(tempTransferList.size());
    ui->transferTable->resizeColumnsToContents();

    int index = 0;

    QTableWidgetItem *temp = new QTableWidgetItem();
    temp->setTextAlignment(Qt::AlignCenter);

    for(auto i : tempTransferList)
    {
        QTableWidgetItem* pPlayerName = temp->clone();
        pPlayerName->setText(i->getPlayerName());

        QTableWidgetItem* pPlayerTeam = temp->clone();
        pPlayerTeam->setText(i->getPlayerTeam());

        QTableWidgetItem* pPlayerAge = temp->clone();
        pPlayerAge->setText(QString::number(2020 - i->getPlayerBirthDay().toInt()));

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
            pReflexes->setForeground(QColor(Qt::green));
        else
            pReflexes->setForeground(QColor(Qt::red));


        QTableWidgetItem* pTackling = temp->clone();
        pTackling->setText(QString::number(i->getPlayerTackling()));
        if(i->getPlayerTackling() <= 50)
            pTackling->setForeground(QColor(Qt::green));
        else
            pTackling->setForeground(QColor(Qt::red));


        QTableWidgetItem* pPassing = temp->clone();
        pPassing->setText(QString::number(i->getPlayerPassing()));
        if(i->getPlayerPassing() <= 50)
            pPassing->setForeground(QColor(Qt::green));
        else
            pPassing->setForeground(QColor(Qt::red));


        QTableWidgetItem* pTechnique = temp->clone();
        pTechnique->setText(QString::number(i->getPlayerTechnique()));
        if(i->getPlayerTechnique() <= 50)
            pTechnique->setForeground(QColor(Qt::green));
        else
            pTechnique->setForeground(QColor(Qt::red));


        QTableWidgetItem* pPace = temp->clone();
        pPace->setText(QString::number(i->getPlayerPace()));
        if(i->getPlayerPace() <= 50)
            pPace->setForeground(QColor(Qt::green));
        else
            pPace->setForeground(QColor(Qt::red));


        QTableWidgetItem* pFinishing = temp->clone();
        pFinishing->setText(QString::number(i->getPlayerFinishing()));
        if(i->getPlayerFinishing() <= 50)
            pFinishing->setForeground(QColor(Qt::green));
        else
            pFinishing->setForeground(QColor(Qt::red));


        ui->transferTable->setItem(index, 0, pPlayerName);
        ui->transferTable->setItem(index, 1, pPlayerTeam);
        ui->transferTable->setItem(index, 2, pPlayerAge);
        ui->transferTable->setItem(index, 3, pWage);
        ui->transferTable->setItem(index, 4, pValue);
        ui->transferTable->setItem(index, 5, pAskingPrice);
        ui->transferTable->setItem(index, 6, pPosition);
        ui->transferTable->setItem(index, 7, pForm);
        ui->transferTable->setItem(index, 8, pExpires);

        ui->transferTable->setItem(index, 9,  pReflexes);
        ui->transferTable->setItem(index, 10, pTackling);
        ui->transferTable->setItem(index, 11, pPassing);
        ui->transferTable->setItem(index, 12, pTechnique);
        ui->transferTable->setItem(index, 13, pPace);
        ui->transferTable->setItem(index, 14, pFinishing);

        index++;
    }
}


void MainWindow::drawLeague(QString pLeagueName)
{
    qDebug() << "pLeagueName : " << pLeagueName << endl;

    if(init)
    {
        for(auto i : mCreateWindow->getAllLeaguesInGame())
        {
            if(i->getLeagueName() == pLeagueName)
            {
                int index = 0;
                ui->LeagueTable->setRowCount(i->getAllTeams().size());
                ui->LeagueTable->resizeColumnsToContents();

                for(auto x : i->getAllTeams())
                {
                    //qDebug() << index+1 << ": " << x->getTeamName() << endl;
                    ui->LeagueTable->setItem(index, 0, new QTableWidgetItem(x->getTeamName()));
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

    for(auto i : mCreateWindow->getAllLeaguesInGame())
    {
        for(auto x : i->getAllMatchByDate(mToday.addDays(1)))
        {
            if((x->getAwayTeam() == mMyTeam)  || (x->getHomeTeam() == mMyTeam))
            {
                QString message = x->getHomeTeam()->getTeamName()+ " - " + x->getAwayTeam()->getTeamName();
                createInbox("Your next match", message);
                break;
            }
        }

        for(auto x : i->getAllMatchByDate(mToday))
        {
            if((x->getAwayTeam() == mMyTeam)  || (x->getHomeTeam() == mMyTeam))
            {
                ui->MainScreen->widget(2)->setDisabled(false);
                ui->MainScreen->setCurrentIndex(2);

                ui->MainScreen->widget(0)->setDisabled(true);
                ui->MainScreen->widget(1)->setDisabled(true);
                ui->MainScreen->widget(3)->setDisabled(true);
                ui->MainScreen->widget(4)->setDisabled(true);

                x->getHomeTeam()->prepareMatchPlayers();
                x->getAwayTeam()->prepareMatchPlayers();

                break;
            }
        }
    }

    ui->Datelabel->setText(QString::number(mToday.day())+"."+ QString::number(mToday.month())+"."+ QString::number(mToday.year()));
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
    Team* currentTeam = nullptr;
    if(column == 0)
    {
        QString teamName = ui->LeagueTable->item(row, column)->text();

        for(auto i : mTeamDatabase->allTeamsInGame)
            if(i->getTeamName() == teamName)
            {
                currentTeam = i;
                break;
            }


        ui->selectedTeam->setRowCount(currentTeam->getPlayersInTeam().size());
        ui->selectedTeam->resizeColumnsToContents();

        int index = 0;

        QTableWidgetItem *temp = new QTableWidgetItem();
        temp->setTextAlignment(Qt::AlignCenter);

        for(auto i : currentTeam->getPlayersInTeam())
        {
            QTableWidgetItem* pPlayerName = temp->clone();
            pPlayerName->setText(i->getPlayerName().split(" ")[0]);

            QTableWidgetItem* pPlayerSurname = temp->clone();
            pPlayerSurname->setText(i->getPlayerName().split(" ")[1]);

            QTableWidgetItem* pPlayerAge = temp->clone();
            pPlayerAge->setText(QString::number(2020 - i->getPlayerBirthDay().toInt()));

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
                pReflexes->setForeground(QColor(Qt::green));
            else
                pReflexes->setForeground(QColor(Qt::red));


            QTableWidgetItem* pTackling = temp->clone();
            pTackling->setText(QString::number(i->getPlayerTackling()));
            if(i->getPlayerTackling() <= 50)
                pTackling->setForeground(QColor(Qt::green));
            else
                pTackling->setForeground(QColor(Qt::red));


            QTableWidgetItem* pPassing = temp->clone();
            pPassing->setText(QString::number(i->getPlayerPassing()));
            if(i->getPlayerPassing() <= 50)
                pPassing->setForeground(QColor(Qt::green));
            else
                pPassing->setForeground(QColor(Qt::red));


            QTableWidgetItem* pTechnique = temp->clone();
            pTechnique->setText(QString::number(i->getPlayerTechnique()));
            if(i->getPlayerTechnique() <= 50)
                pTechnique->setForeground(QColor(Qt::green));
            else
                pTechnique->setForeground(QColor(Qt::red));


            QTableWidgetItem* pPace = temp->clone();
            pPace->setText(QString::number(i->getPlayerPace()));
            if(i->getPlayerPace() <= 50)
                pPace->setForeground(QColor(Qt::green));
            else
                pPace->setForeground(QColor(Qt::red));


            QTableWidgetItem* pFinishing = temp->clone();
            pFinishing->setText(QString::number(i->getPlayerFinishing()));
            if(i->getPlayerFinishing() <= 50)
                pFinishing->setForeground(QColor(Qt::green));
            else
                pFinishing->setForeground(QColor(Qt::red));

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
    unsigned long long int fine = mSelectedPlayer->getPlayerWage() * (12*(mSelectedPlayer->getPlayerContractExpires().split(".")[2].toInt() - mCreateWindow->mYear) + (mSelectedPlayer->getPlayerContractExpires().split(".")[1].toInt()-mCreateWindow->mMonth));

    if(fine == 0)
        fine = mSelectedPlayer->getPlayerWage();

    QMessageBox::StandardButton reply = QMessageBox::question(this,
                                                              "Release Player",
                                                              mSelectedPlayer->getPlayerName() + " adlı oyuncuyu " + QString("%L2").arg(fine) + " karşılığında serbest bırakmak istiyor musunuz ?",
                                                              QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        if(mMyTeam->getTransferBudget() >= fine)
        {
            mMyTeam->decreaseTransferBudget(fine);
            mMyTeam->removePlayer(mSelectedPlayer);

            mCreateWindow->addFreePlayer(mSelectedPlayer);

            createInbox(mSelectedPlayer->getPlayerName().split(" ")[0]+" released", mSelectedPlayer->getPlayerName()+" will be released tomorrow");
            mSelectedPlayer->getTransferOffer().clear();
            ui->playerArea->hide();
            showMyTeam();
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
            mMyTeam->removeTransferList(mSelectedPlayer);
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
            mMyTeam->addTransferList(mSelectedPlayer);
            ui->addTransferListButton->setText("Remove from list");
            showTransferList();
        }
    }
}
