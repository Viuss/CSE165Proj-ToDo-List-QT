#ifndef SUBITEM_H
#define SUBITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class subItem;
}

class subItem : public QWidget {
    Q_OBJECT

public:
    explicit subItem(const QString& name, QWidget* parent = nullptr);
    ~subItem();

    void setName(const QString& name);

    QString name() const;

    bool isCompleted() const;

    void removeSub(subItem* subitem);

    QString Importance() const;

signals:
    void removed(subItem* subitem);
    void statusChanged(subItem* subitem);

private slots:
    void checkSub(bool checked);

private:
    Ui::subItem* ui;
    QLabel* importanceLabel;
};

#endif // SUBITEM_H
