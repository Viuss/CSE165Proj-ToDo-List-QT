#include "Item.h"
#include "subitem.h"
#include "ui_Item.h"

#include <QWidget>
#include <QInputDialog>
#include <QDebug>

// Constructor: initialize the user interface, set the name, and connect the signals and slots.
Item::Item(const QString& name, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Item)
{
    ui->setupUi(this);
    setName(name);


    // Connect the remove button to the removed signal.
    connect(ui->removeButton, &QPushButton::clicked, this, [this] {
        emit removed(this);
    });

    connect(ui->Importance, &QCheckBox::toggled, this, &Item::checked);

    // Connect the checkbox to the checked slot.
    connect(ui->checkbox, &QCheckBox::toggled, this, &Item::checked);
}


// Destructor: print a message to the console and delete the user interface.
Item::~Item()
{
    delete ui;
}

// Set the name of the item.
void Item::setName(const QString& name)
{
    ui->checkbox->setText(name);
}

// Get the name of the item.
QString Item::name() const
{
    return ui->checkbox->text();
}

// Check if the item is completed.
bool Item::isCompleted() const
{
    return ui->checkbox->isChecked();
}

// Slot that is called when the checkbox is checked or unchecked.
void Item::checked(bool checked)
{
    // Emit the statusChanged signal.
    emit statusChanged(this);
}


//Function adding the sub item
void Item::on_subButton_clicked()
{
    bool ok;
    QString name = QInputDialog::getText(this, "Add Item", "Item name", QLineEdit::Normal,
                                         "Untitled Item", &ok); // Prompt the user to enter the name of the new item
    if (ok && !name.isEmpty()) {
        qDebug() << "Adding new Item";
        subItem* subItem = new class subItem(name); // Create a new item with the given name
        ui->subLayout->addWidget(subItem);
    }
}



