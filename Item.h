#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QString>

namespace Ui {
class item;
}

class Item : public QWidget {
    Q_OBJECT

public:
    explicit Item(const QString& name, QWidget* parent = nullptr);
    ~Item();

    void setName(const QString& name);
    QString name() const;
    bool isCompleted() const;
    void removeItem(Item* item);

signals:
    void removed(Item* item);
    void statusChanged(Item* item);

private slots:
    void checked(bool checked);

private:
    Ui::item* ui;
};

#endif // ITEM_H
