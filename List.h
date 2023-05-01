//Include guards
#ifndef LIST_H
#define LIST_H

//Necessary headers and Item header
#include <QList>
#include <QVector>
#include <QListWidget>
#include <QMainWindow>
#include "Item.h"

// Define namespace for the UI
namespace Ui {
class List;
}

//Define List as a subclass of QMainWindow
class List : public QMainWindow {
    Q_OBJECT

    //Declare constructor and destructor
public:
    explicit List(QMainWindow *parent = nullptr);
    ~List();

//Public slots connected to signals to respond to user actions
public slots:
    void on_addItem_clicked();
    void removeItem(Item* item);
    void itemStatusChanged(Item* item);
    void updateStatus();
    void removeItemName(QString name);

//Private slots for functions only within List class, can also be signaled
private slots:
    void on_actionClear_all_triggered();

    void on_actionExit_triggered();

    void on_actionSort_triggered();

    void on_actionExport_triggered();

    void on_actionRemind_me_triggered();

    void on_tableView_windowIconTextChanged(const QString &iconText);

    void setImportance(Item* item, const QString& importance);


//Define private member variables of List class
private:
    Ui::List* ui;
    QVector<Item*> items;
    QListWidget* listWidget;
    QList<QListWidgetItem*> secondItem;
    QVector<QString> itemNames; // Vector to store the names of the added items
    QVector<Item*> itemsM; // Vector to store pointers to the added items
};

//Mark end and include guards
#endif // LIST_H
