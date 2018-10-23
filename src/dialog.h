#ifndef DIALOG_H
#define DIALOG_H

#include "list.h"

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    ListItem getVal();
    void setVal(ListItem val);
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H
