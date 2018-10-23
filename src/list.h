#ifndef LIST_H
#define LIST_H

#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QString>
#include <qvector.h>


struct ListItem
{
    QString id;
    QString name;
    int category;
    bool withRecept;
};

inline QDataStream &operator<<(QDataStream &out, const ListItem &p)
{
    out << p.id << p.name << p.category << p.withRecept;
    return out;
}

inline QTextStream &operator<<(QTextStream &out, const ListItem &p)
{
    out << p.id << endl << p.name << endl << p.category << endl << p.withRecept << endl;
    return out;
}

inline QDataStream &operator >>(QDataStream &in, ListItem &p)
{
    in >> p.id >> p.name >> p.category;
    in >> p.withRecept;
    return in;
}

inline QTextStream &operator >>(QTextStream &in, ListItem &p)
{
    int sp;
    p.withRecept = false;

    in >> p.id >> p.name >> p.category >> sp;

    if (sp == 1) {
        p.withRecept = true;
    }
    return in;
}

class List
{
private:
    QList<ListItem> data;
public:
    List()
    {
        this->data = QList<ListItem>();
    }
    QList<ListItem> getList()
    {
        return this->data;
    }
    void setData(int id, ListItem item)
    {
        this->data[id] = item;
    }
    ListItem getData(int id)
    {
        return this->data[id];
    }
    int saveItem(ListItem item)
    {
        this->data.append(item);
        return this->data.size() - 1;
    }
    void deleteAt(int id)
    {
        this->data.removeAt(id);
    }
    void saveFile(QString name)
    {
        QFile file(name);
        file.open(QIODevice::WriteOnly);
        QDataStream out(&file);

        out << this->data.size();

        for(auto &item : this->data) {
            out << item;
        }
    }
    void saveFileTxt(QString name)
    {
        QFile file(name);
        file.open(QIODevice::WriteOnly);
        QTextStream out(&file);

        out << this->data.size() << endl;

        for(auto &item : this->data) {
            out << item;
        }
    }

    void loadFile(QString name)
    {
        QFile file(name);
        file.open(QIODevice::ReadOnly);
        QDataStream in(&file);

        int count;

        in >> count;

        this->data.clear();

        ListItem tmp;

        for(int i = 0; i < count; i++) {
            in >> tmp;
            this->data.push_back(tmp);
        }
    }
    void loadFileTxt(QString name)
    {
        QFile file(name);
        file.open(QIODevice::ReadOnly);
        QTextStream in(&file);

        int count;

        in >> count;

        this->data.clear();

        ListItem tmp;

        for(int i = 0; i < count; i++) {
            in >> tmp;
            this->data.push_back(tmp);
        }
    }


    static QVector<QString> getCategories()
    {
        QVector<QString> q = {"антибіотики",
                              "анестезія",
                              "жарознижуючі",
                              "перев'язочні матеріали",
                              "протизаплідні засоби",
                              "противірусні",
                              "носові каплі",
                              "ноотропи",
                              "інше..."};
        return q;
    }
};

#endif // LIST_H
