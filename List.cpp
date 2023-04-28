#include "List.h"
#include "ui_Item.h"
#include "ui_List.h"

#include <QDebug>
#include <QInputDialog>

List::List(QMainWindow *parent):
    QMainWindow(parent),
    ui(new Ui::List), // Instantiate the UI for this window
    items() // Initialize the vector of Items
{
    ui->setupUi(this); // Set up the UI for this window
    connect(ui->addItemButton, &QPushButton::clicked, this, &List::addItem); // Connect the addItemButton to the addItem slot
    updateStatus(); // Update the status label
}

List::~List()
{
    delete ui; // Deallocate the UI
}

void List::addItem()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Add Item"),
         tr("Item name"), QLineEdit::Normal,
         tr("Untitled Item"), &ok); // Prompt the user to enter the name of the new item
    if (ok && !name.isEmpty()) {
        qDebug() << "Adding new Item";
        Item* Item = new class Item(name); // Create a new item with the given name
        connect(Item, &Item::removed, this, &List::removeItem); // Connect the item's "removed" signal to the removeItem slot
        connect(Item, &Item::statusChanged, this, &::List::itemStatusChanged); // Connect the item's "statusChanged" signal to the ItemStatusChanged slot
        items.append(Item); // Add the item to the list of items
        QLayoutItem* layoutItem = new QWidgetItem(Item);
        ui->itemsLayout->addItem(layoutItem);
        updateStatus(); // Update the status label
    }
}

void List::removeItem(Item* Item)
{
    items.removeOne(Item);
    ui->itemsLayout->removeWidget(Item);
    delete Item;
    updateStatus();
}

void List::itemStatusChanged(Item* /*Item*/)
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

    ui->statusLabel->setText(QString("Status: %1 todo / %2 completed")
                                 .arg(todoCount)
                                 .arg(completedCount)); // Update the status label with the counts of completed and uncompleted items
}
