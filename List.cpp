#include "List.h"
#include "ui_List.h"

#include <QDebug>
#include <QFile>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <iostream>
#include <vector>

QLayoutItem* itemsLayout;
std::vector<std::string> todoManual; // vector to store the names of the items

//Insertion sort for later reference
void insertionSort(QVector<QString> &vec) {
    int n = vec.size();
    for (int i = 1; i < n; i++) {
        QString key = vec[i];
        int j = i - 1;
        while (j >= 0 && vec[j] > key) {
            vec[j + 1] = vec[j];
            j = j - 1;
        }
        vec[j + 1] = key;
    }
}

List::List(QMainWindow *parent):
    QMainWindow(parent),
    ui(new Ui::List), // Instantiate the UI for this window
    items() // Initialize the vector of Items
{
    ui->setupUi(this); // Set up the UI for this window
    itemsLayout = ui->itemsLayout;
    updateStatus(); // Update the status label
}

List::~List()
{
    delete ui; // Deallocate the UI
}

void List::on_addItem_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Add Item", "Item name", QLineEdit::Normal,
                                         "Untitled Item", &ok); // Prompt the user to enter the name of the new item
    if (ok && !name.isEmpty()) {
        qDebug() << "Adding new Item";

        Item* Item = new class Item(name); // Create a new item with the given name
        connect(Item, &Item::removed, this, &List::removeItem); // Connect the item's "removed" signal to the removeItem slot
        connect(Item, &Item::statusChanged, this, &::List::itemStatusChanged); // Connect the item's "statusChanged" signal to the ItemStatusChanged slot
        items.append(Item); // Add the item to the list of items
        ui->itemsLayout->addWidget(Item);
        itemNames.push_back(name); // Add the name of the item to the vector
        updateStatus();
    }
}

void List::removeItem(Item* Item)
{
    items.removeOne(Item);
    ui->itemsLayout->removeWidget(Item);
    Item->setParent(nullptr); // Set the item's parent to nullptr to prevent memory leak
    delete Item;
    removeItemName(Item->getName()); // Remove the name of the deleted item from the vector
    updateStatus();
}

void List::itemStatusChanged(Item*)
{
    updateStatus(); // Update the status label
}

void List::updateStatus()
{
    int completedCount = 0;
    for(auto t : items)  {
        if (t->isCompleted()) {
            completedCount++; // Increment the count of completed items
        }
    }
    int todoCount = items.size() - completedCount; // Calculate the count of uncompleted items

    ui->statusLabel->setText(QString("Major Items: %1 incomplete / %2 complete")
         .arg(todoCount)
         .arg(completedCount)); // Update the status label with the counts of completed and uncompleted items
}

void List::on_actionClear_all_triggered()
{
    // Remove all items from the list
    while (!items.isEmpty()) {
        Item* item = items.takeFirst();
        removeItem(item);
    }
}

void List::setImportance(Item* item, const QString& importance)
{
    //item->importanceLabel(importance);
}

void List::on_actionExit_triggered()
{
    QApplication::quit(); //quit program
}


void List::on_actionSort_triggered()
{
    QVector<QString> names;
    for (auto item : items) {
        names.append(item->getName());
    }

    // Sort the vector
    insertionSort(names);

    // Create a QString to hold the sorted names
    QString sortedNames;

    // Combine the sorted names into a QString
    for (const QString& name : names) {
        sortedNames += name + "\n";
    }

    // Display the sorted names in a popup box
    QMessageBox::information(this, "Sorted Names", sortedNames);
}



void List::on_actionExport_triggered()
{
    // Get the file path and name from the user using a QFileDialog
    QString filePath = QFileDialog::getSaveFileName(this, tr("Export to CSV"), "", tr("CSV Files (*.csv)"));

    // Open the file in write mode
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for writing:" << filePath;
        return;
    }

    // Create a QTextStream object that is attached to the file
    QTextStream stream(&file);

    // Write the header row to the file
    stream << "Name,Completed\n";

    // Write the data rows to the file
    for (Item* item : items) {
        QString name = item->name();
        QString completed = item->isCompleted() ? "true" : "false";
        stream << name << "," << completed << "\n";
    }

    // Close the file
    file.close();
}

void List::on_actionRemind_me_triggered()
    {
        // Create a message box
        QMessageBox msgBox;
        msgBox.setWindowTitle("This is your reminder");
        msgBox.setText("Do your tasks!");
        msgBox.setIcon(QMessageBox::Information);
        msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

        msgBox.setButtonText(QMessageBox::Cancel, "NO");
        // Show the message box and wait for a response
        int ret = msgBox.exec();

        if (ret == QMessageBox::Ok) {
            // User clicked OK
            // Do something here if needed
        }
        else if (ret == QMessageBox::Cancel) {
            // User clicked cancel
            QApplication::quit(); //quit program
            return;
        }
}


void List::on_tableView_windowIconTextChanged(const QString &iconText)
{

}

void List::removeItemName(QString name)
{
    itemNames.removeAll(name); // Remove the name of the deleted item from the vector
}



