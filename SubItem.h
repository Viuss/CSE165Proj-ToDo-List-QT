
// Header guard to prevent multiple inclusion of the header file
#ifndef SUBITEM_H
#define SUBITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class subItem;
}

// Define the subItem class as a subclass of QWidget
class subItem : public QWidget {
    Q_OBJECT // Macro required for using Qt's meta-object system

public:
    // Constructor to create an instance of a subItem widget with a given name and parent
    explicit subItem(const QString& name, QWidget* parent = nullptr);

    // Destructor to clean up memory
    ~subItem();

    // Function to set the name of the subItem
    void setName(const QString& name);

    // Function to retrieve the name of the subItem
    QString name() const;

    // Function to check if the subItem is marked as completed
    bool isCompleted() const;

    // Function to remove a subItem from the list of subItems
    void removeSub(subItem* subitem);

    // Function to retrieve the importance of the subItem
    QString Importance() const;

signals:
    // Signal emitted when a subItem is removed
    void removed(subItem* subitem);
    // Signal emitted when the status of a subItem is changed
    void statusChanged(subItem* subitem);

private slots:
    // Slot to handle when the checkbox for a subItem is toggled
    void checkSub(bool checked);

private:
    Ui::subItem* ui; // Pointer to the subItem's UI elements
    QLabel* importanceLabel;
};

// End of the header guard
#endif // SUBITEM_H
