#include "Item.h"
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
    qDebug() << "~Item() called";
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
    // Set the font to strike out if the checkbox is checked.
    QFont font(ui->checkbox->font());
    font.setStrikeOut(checked);
    ui->checkbox->setFont(font);

    // Emit the statusChanged signal.
    emit statusChanged(this);
}


