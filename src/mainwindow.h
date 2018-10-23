#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "list.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    List *list;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void displayList(QList<ListItem> data);
    void displayList();
private slots:
    void on_action_4_triggered();
    void deleteAction();
    void editAction();

    void on_pushButton_2_clicked();

    void on_action_3_triggered();

    void on_open_action_triggered();

    void on_action_2_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
