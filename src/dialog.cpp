#include "dialog.h"
#include "ui_dialog.h"
#include "list.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    for(auto &s : List::getCategories()) {
        ui->comboBox->addItem(s);
    }
}

ListItem Dialog::getVal()
{
    ListItem l;
    l.name = ui->lineEdit->text();
    l.withRecept = ui->comboBox_2->currentIndex();
    l.id = ui->lineEdit_2->text();
    l.category = ui->comboBox->currentIndex();

    return l;
}

void Dialog::setVal(ListItem val)
{
    ui->lineEdit->setText(val.name);
    ui->comboBox_2->setCurrentIndex(val.withRecept);
    ui->lineEdit_2->setText(val.id);
    ui->comboBox->setCurrentIndex(val.category);
}

Dialog::~Dialog()
{
    delete ui;
}
