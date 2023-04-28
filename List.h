#ifndef LIST_H
#define LIST_H

#include <QList>
#include <QVector>
#include <QListWidget>
#include <QMainWindow>
#include "Item.h"

namespace Ui {
class List;
}

class List : public QMainWindow {
    Q_OBJECT

public:
    explicit List(QMainWindow *parent = nullptr);
    ~List();

public slots:
    void addItem();
    void removeItem(Item* item);
    void itemStatusChanged(Item* item);
    void updateStatus();

private slots:
    void on_actionClear_all_triggered();

    void on_actionExit_triggered();

    void on_actionSort_triggered();

    void on_actionExport_triggered();

    //void on_actionRemind_me_triggered();

private:
    Ui::List* ui;
    QVector<Item*> items;
    QListWidget* listWidget;
};

#endif // LIST_H
