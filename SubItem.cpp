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

subItem::~subItem()
{
    qDebug() << "~subItem() called";
    delete ui;
}

void subItem::setName(const QString& name)
{
    ui->checkSub->setText(name);
}

QString subItem::name() const
{
    return ui->checkSub->text();
}

bool subItem::isCompleted() const
{
    return ui->checkSub->isChecked();
}

//void subItem::removeSub()
//{
//    // Remove the subItem from its parent widget.
//    if (parentWidget()) {
//        parentWidget()->layout()->removeWidget(this);
//        parentWidget()->adjustSize();
//    }

//    // Emit the removed signal.
//    emit removed(this);
//}

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
