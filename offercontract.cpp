#include "offercontract.h"
#include "ui_offercontract.h"

OfferContract::OfferContract(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OfferContract)
{
    ui->setupUi(this);
}

OfferContract::~OfferContract()
{
    delete ui;
}
