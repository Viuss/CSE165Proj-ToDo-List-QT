#include "subitem.h"
#include "ui_subitem.h"

#include <QInputDialog>
#include <QDebug>

subItem::subItem(const QString& name, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::subItem)
{
    ui->setupUi(this);
    setName(name);

    // Connect the remove button to the removed signal.
    connect(ui->removeSub, &QPushButton::clicked, this, [this] {
        emit removed(this);
    });

    // Connect the checkbox to the checked slot.
    connect(ui->checkSub, &QCheckBox::toggled, this, &subItem::checkSub);
}

//Destructor
subItem::~subItem()
{
    qDebug() << "~subItem() called";
    delete ui;
}

//Name setter on the checkbox
void subItem::setName(const QString& name)
{
    ui->checkSub->setText(name);
}

//Return name of sub item
QString subItem::name() const
{
    return ui->checkSub->text();
}

//Check box marked or not
bool subItem::isCompleted() const
{
    return ui->checkSub->isChecked();
}

QString subItem::Importance() const
{
    // Return the text of the importance label.
    return importanceLabel->text();
}

void subItem::checkSub(bool checked)
{
    // Set the font to strike out if the checkbox is checked.
    QFont font(ui->checkSub->font());
    font.setStrikeOut(checked);
    ui->checkSub->setFont(font);

    // Emit the statusChanged signal.
    emit statusChanged(this);
}
