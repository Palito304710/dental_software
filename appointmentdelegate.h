#ifndef APPOINTMENTDELEGATE_H
#define APPOINTMENTDELEGATE_H

#include <QStyledItemDelegate>
#include "db.h"

class AppointmentDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    AppointmentDelegate(QObject *parent = nullptr, db* database = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;



private:
    db *myDb;

signals:
    void patientSelected(const Patient& patient, const QModelIndex& index);
};

#endif // APPOINTMENTDELEGATE_H
