
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
    explicit Item(const QString& name, QWidget* parent = nullptr);

    // Destructor to clean up memory
    ~Item();// Function to set the name of the Item

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

    //void on_checkbox_stateChanged(int arg1);

    //void on_Importance_clicked();

    //void on_Importance_toggled(bool checked);

    //void on_checkbox_toggled(bool checked);

    void on_subButton_clicked();

private:
    Ui::Item* ui; // Pointer to the Item's UI elements
};

// End of the include guard
#endif // ITEM_H





