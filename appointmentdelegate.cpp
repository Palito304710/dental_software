#include "appointmentdelegate.h"
#include <QRect>
#include <QApplication>
#include <QMouseEvent>
#include <QAbstractItemView>
#include <QToolTip>
#include <QLineEdit>
#include <QCompleter>
#include <QStringListModel>

AppointmentDelegate::AppointmentDelegate(QObject *parent, db* database)
    : QStyledItemDelegate(parent), myDb(database) {}

void AppointmentDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QStyledItemDelegate::paint(painter, option, index);
    QString patientName = index.data(Qt::DisplayRole).toString();

    if(patientName.isEmpty())
        return;

    bool completed = index.data(Qt::UserRole).toBool();

    QRect check = QRect(option.rect.right() - 20, option.rect.top() + 5, 16, 16);

    QStyleOptionButton checkbox;
    checkbox.rect = check;
    checkbox.state = QStyle::State_Enabled;

    if (completed)
        checkbox.state |= QStyle::State_On;
    else
        checkbox.state |= QStyle::State_Off;

    QStyle* style = option.widget ? option.widget->style() : QApplication::style();
    style->drawControl(QStyle::CE_CheckBox, &checkbox, painter);
}

bool AppointmentDelegate::editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if(event->type() != QEvent::MouseButtonRelease)
        return false;

    QString patientName = index.data(Qt::DisplayRole).toString();
    QMouseEvent *mouse = static_cast<QMouseEvent*>(event);
    QRect check = QRect(option.rect.right() - 20, option.rect.top() + 5, 16, 16);

    if (check.contains(mouse->pos()) && !patientName.isEmpty())
    {
        bool completed = index.data(Qt::UserRole).toBool();
        model->setData(index, !completed, Qt::UserRole);
        return true;
    }

    return false;
}

bool AppointmentDelegate::helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    if (event->type() == QEvent::ToolTip) {
        QString patientName = index.data(Qt::DisplayRole).toString();
        if (patientName.isEmpty()) {
            return false;
        }

        if (!myDb) {
            return false;
        }

        Patient patient = myDb->getPatientByName(patientName);
        QString text = QString("Phone: %1\nPrefix: %2\nTel: %3")
                           .arg(QString::fromStdString(patient.phoneNumber))
                           .arg(QString::fromStdString(patient.occupation))
                           .arg(QString::fromStdString(patient.telPhone));

        QToolTip::showText(event->globalPos(), text, view);
        return true;
    }

    return QStyledItemDelegate::helpEvent(event, view, option, index);
}

QWidget* AppointmentDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *lineEdit = qobject_cast<QLineEdit*>(QStyledItemDelegate::createEditor(parent, option, index));
    if (!lineEdit)
        return nullptr;

    QCompleter *completer = new QCompleter(lineEdit);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);

    QStringListModel *model = new QStringListModel(completer);
    completer->setModel(model);

    lineEdit->setCompleter(completer);

    AppointmentDelegate* nonConstThis = const_cast<AppointmentDelegate*>(this);

    connect(lineEdit, &QLineEdit::textChanged, nonConstThis,
            [model, nonConstThis](const QString &text) {
                if (text.length() >= 2) {
                    std::vector<QString> names = nonConstThis->myDb->searchPatients(text);
                    QStringList namesList;
                    for (const QString& name : names) {
                        namesList << name;
                    }
                    model->setStringList(namesList);
                } else {
                    model->setStringList(QStringList());
                }
            });

    QAbstractItemView *popup = completer->popup();
    if (popup) {
        connect(popup, &QAbstractItemView::clicked, nonConstThis,
                [nonConstThis, index, lineEdit](const QModelIndex &clickedIndex) {
                    QString text = clickedIndex.data(Qt::DisplayRole).toString();
                    lineEdit->setText(text);
                    Patient patient = nonConstThis->myDb->getPatientByName(text);
                    emit nonConstThis->patientSelected(patient, index);
                    emit nonConstThis->commitData(lineEdit);
                    emit nonConstThis->closeEditor(lineEdit);
                });
    }

    return lineEdit;
}





