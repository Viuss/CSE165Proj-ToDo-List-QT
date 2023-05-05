
// Include guards to prevent multiple inclusion of the header file
#ifndef ITEM_H
#define ITEM_H

// Include necessary Qt headers
#include "qlabel.h"
#include <QWidget>
#include <QString>

// Define namespace for the UI
namespace Ui {
class Item;
}

// Define the Item class as a subclass of QWidget
class Item : public QWidget {
    Q_OBJECT // Macro required for using Qt's meta-object system

public:
    // Constructor to create an instance of an Item widget with a given name and parent
    // explicit in order to prevent implicit conversions and make sure QString and QWidget are specifically being used
    // const to indicate a constant reference (will not modify name)
    // dereference & in order to increase performance when passing large objects
    //parent widget is responsible for memory management of children in QT, using a pointer to set the parent to null and indicate item object as a top-level widget
    //this is necessary to have item exist as a standalone widget that can be dropped onto the user interface, and allows it to be used in other parts of the app like the list or another layout
    explicit Item(const QString& name, QWidget* parent = nullptr);

    // Destructor to clean up memory
    ~Item();

    // Function to set the name of the Item
    void setName(const QString& name);

    // Function to retrieve the name of the Item
    QString name() const;

    QString getName() const {
        return name();
    }

    QString Importance() const; // new member function to retrieve the importance value

    // Function to check if the Item is marked as completed
    bool isCompleted() const;

    // Function to remove an Item from the list of items
    void removeItem(Item* item);

    QLabel *importanceLabel;


signals:
    // Signal emitted when an Item is removed
    void removed(Item* item);
    // Signal emitted when the status of an Item is changed
    void statusChanged(Item* item);

//public slots:
//    void subStatusChanged(Item* item);

private slots:
    // Slot to handle when the checkbox for an Item is toggled
    void checked(bool checked);

    // Slot to handle adding a new sub-item
    void on_subButton_clicked();

private:
    Ui::Item* ui; // Pointer to the Item's UI elements
};

// End of the include guard
#endif // ITEM_H





