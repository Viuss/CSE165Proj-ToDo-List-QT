#include "List.h"
#include "ui_List.h"

#include <QDebug>
#include <QFile>
#include <QInputDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>

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
        QLayoutItem* itemsLayout = new QWidgetItem(Item);
        ui->itemsLayout->addItem(itemsLayout);
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

    ui->statusLabel->setText(QString("Status: %1 incomplete / %2 complete")
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


void List::on_actionExit_triggered()
{
    QApplication::quit(); //quit program
}


void List::on_actionSort_triggered()
{
    std::sort(items.begin(), items.end(), [](Item* a, Item* b) {
        return a->name() < b->name();
    });

    // Clear the current layout
    QLayoutItem *child;
    while ((child = ui->itemsLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    // Add the sorted items to the layout
    for (auto item : items) {
        ui->itemsLayout->addWidget(item);
    }
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



//void List::on_actionRemind_me_triggered()
//{
//    // Get the currently selected item
//    QListWidgetItem *currentItem = ui->listWidget->currentItem();
//    if (currentItem == nullptr) {
//        QMessageBox::warning(this, "No Item Selected", "Please select an item to set a reminder for.");
//        return;
//    }

//    // Get the due date for the selected item
//    QDate dueDate = currentItem->data(Qt::UserRole).toDate();

//    // Get the current time
//    QTime currentTime = QTime::currentTime();

//    int msecRemaining = 10;

//    // Schedule a timer to display a reminder
//    QTimer::singleShot(msecRemaining, this, [=]() {
//        QString message = QString("Reminder: %1").arg(currentItem->text());
//        QMessageBox::information(this, "Reminder", message);
//    });
//}
