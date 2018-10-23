#include "about.h"
#include "dialog.h"
#include "list.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setFixedWidth(680);
    this->setFixedHeight(569);

    ui->tableWidget->setColumnCount(6);
    ui->tableWidget->setColumnWidth(0, 75);
    ui->tableWidget->setColumnWidth(1, 160);
    ui->tableWidget->setColumnWidth(2, 120);
    ui->tableWidget->setColumnWidth(3, 130);
    ui->tableWidget->setColumnWidth(4, 80);
    ui->tableWidget->setColumnWidth(5, 80);

    ui->tableWidget->verticalHeader()->setVisible(false);
    ui->tableWidget->setFocusPolicy(Qt::NoFocus);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);


    this->list = new List();

    this->displayList();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::deleteAction()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());

    int id = pButton->objectName().split("delete_")[1].toInt();

    qDebug() << "delete " << id;

    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Question);
    msgBox.setText("Дійсно видалити препарат " + this->list->getData(id).name + "?");
    msgBox.setWindowTitle("Ви впевнені?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

    if (msgBox.exec() == QMessageBox::Ok) {
        this->list->deleteAt(id);
        this->displayList();
    }
}

void MainWindow::editAction()
{
    QPushButton* pButton = qobject_cast<QPushButton*>(sender());

    int id = pButton->objectName().split("edit_")[1].toInt();

    qDebug() << "edit " << id;

    Dialog d;
    d.setWindowTitle("Редагування препарату");
    d.setModal(true);
    d.setVal(this->list->getData(id));
    if (d.exec()) {
        ListItem l = d.getVal();

        this->list->setData(id, l);
        this->displayList();
    }
}

void MainWindow::on_action_4_triggered()
{
    QMessageBox msgBox;
    msgBox.setText("Програма створена студентом 2 курсу Рогожуком Назаром");
    msgBox.setIcon(QMessageBox::Information);
    msgBox.setWindowTitle("Про автора");
    msgBox.exec();
}

void MainWindow::displayList()
{
    QList<ListItem> data = this->list->getList();

    ui->tableWidget->setRowCount(data.size());
    int i = 0;
    for(auto &item : data) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(item.id));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(item.name));
        QString recept = item.withRecept ? "+" : "-";
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(recept));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(List::getCategories()[item.category]));


        QPushButton *btnDelete = new QPushButton();
        btnDelete->setParent(ui->tableWidget);
        btnDelete->setText("вид.");
        btnDelete->setObjectName("delete_"+QString::number(i));


        QPushButton *btnEdit = new QPushButton();
        btnEdit->setParent(ui->tableWidget);
        btnEdit->setText("ред.");
        btnEdit->setObjectName("edit_"+QString::number(i));


        connect(btnDelete, SIGNAL (released()), this, SLOT (deleteAction()));
        connect(btnEdit, SIGNAL (released()), this, SLOT (editAction()));

        ui->tableWidget->setCellWidget(i, 4, btnDelete);
        ui->tableWidget->setCellWidget(i, 5, btnEdit);
        i++;
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    Dialog d;
    d.setWindowTitle("Додавання препарату");
    d.setModal(true);
    if (d.exec()) {
        ListItem l = d.getVal();

        this->list->saveItem(l);
        this->displayList();
    }
}

void MainWindow::on_action_3_triggered()
{
    About a;
    a.setModal(true);
    a.exec();
}

void MainWindow::on_open_action_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Відкрити базу даних"), "",
            tr("База (*.kdb);;Текстова база (*.txt);;Всі файли (*)"));

    if (fileName.right(3) == "kdb") {
        this->list->loadFile(fileName);
    }
    else if (fileName.right(3) == "txt") {
        this->list->loadFileTxt(fileName);
    }
    this->displayList();
}

void MainWindow::on_action_2_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Зберегти базу даних"), "",
            tr("База (*.kdb);;Текстова база (*.txt);;Всі файли (*)"));

    qDebug() << fileName;
    if (fileName.right(3) == "kdb") {
        this->list->saveFile(fileName);
    }
    else if (fileName.right(3) == "txt") {
        this->list->saveFileTxt(fileName);
    }
}
