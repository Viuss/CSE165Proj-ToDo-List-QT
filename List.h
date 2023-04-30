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

    void on_addItem_clicked();
    void removeItem(Item* item);
    void itemStatusChanged(Item* item);
    void updateStatus();
    void removeItemName(QString name);

private slots:
    void on_actionClear_all_triggered();

    void on_actionExit_triggered();

    void on_actionSort_triggered();

    void on_actionExport_triggered();

    void on_actionRemind_me_triggered();

    void on_tableView_windowIconTextChanged(const QString &iconText);

    void setImportance(Item* item, const QString& importance);



private:
    Ui::List* ui;
    QVector<Item*> items;
    QListWidget* listWidget;
    QList<QListWidgetItem*> secondItem;
    QVector<QString> itemNames; // Vector to store the names of the added items
    QVector<Item*> itemsM; // Vector to store pointers to the added items
};

#endif // LIST_H
