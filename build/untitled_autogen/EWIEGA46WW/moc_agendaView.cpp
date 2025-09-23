/****************************************************************************
** Meta object code from reading C++ file 'agendaView.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../agendaView.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'agendaView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN10AgendaViewE_t {};
} // unnamed namespace

template <> constexpr inline auto AgendaView::qt_create_metaobjectdata<qt_meta_tag_ZN10AgendaViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "AgendaView",
        "patientSelected",
        "",
        "Patient",
        "selectedPatient",
        "on_addButton_clicked",
        "on_removeButton_clicked",
        "on_thirtyRatio_clicked",
        "on_hourRatio_clicked",
        "onCellChanges",
        "row",
        "column",
        "on_addDoctorButton_clicked",
        "on_appointmentTable_cellDoubleClicked",
        "col",
        "onDataChange",
        "QModelIndex",
        "left",
        "right",
        "searchPSelected",
        "patient",
        "index",
        "doctorSelected",
        "QItemSelection",
        "sel",
        "des",
        "displayDoctors",
        "showRCMenu",
        "pos",
        "showDoctorsMenu"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'patientSelected'
        QtMocHelpers::SignalData<void(const Patient &)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { 0x80000000 | 3, 4 },
        }}),
        // Slot 'on_addButton_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_removeButton_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_thirtyRatio_clicked'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_hourRatio_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onCellChanges'
        QtMocHelpers::SlotData<void(int, int)>(9, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 10 }, { QMetaType::Int, 11 },
        }}),
        // Slot 'on_addDoctorButton_clicked'
        QtMocHelpers::SlotData<void()>(12, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_appointmentTable_cellDoubleClicked'
        QtMocHelpers::SlotData<void(int, int)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 10 }, { QMetaType::Int, 14 },
        }}),
        // Slot 'onDataChange'
        QtMocHelpers::SlotData<void(const QModelIndex &, const QModelIndex &)>(15, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 16, 17 }, { 0x80000000 | 16, 18 },
        }}),
        // Slot 'searchPSelected'
        QtMocHelpers::SlotData<void(const Patient &, const QModelIndex &)>(19, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 3, 20 }, { 0x80000000 | 16, 21 },
        }}),
        // Slot 'doctorSelected'
        QtMocHelpers::SlotData<void(const QItemSelection &, const QItemSelection &)>(22, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 23, 24 }, { 0x80000000 | 23, 25 },
        }}),
        // Slot 'displayDoctors'
        QtMocHelpers::SlotData<void()>(26, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'showRCMenu'
        QtMocHelpers::SlotData<void(const QPoint &)>(27, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QPoint, 28 },
        }}),
        // Slot 'showDoctorsMenu'
        QtMocHelpers::SlotData<void(const QPoint &)>(29, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QPoint, 28 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<AgendaView, qt_meta_tag_ZN10AgendaViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject AgendaView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10AgendaViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10AgendaViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN10AgendaViewE_t>.metaTypes,
    nullptr
} };

void AgendaView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<AgendaView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->patientSelected((*reinterpret_cast< std::add_pointer_t<Patient>>(_a[1]))); break;
        case 1: _t->on_addButton_clicked(); break;
        case 2: _t->on_removeButton_clicked(); break;
        case 3: _t->on_thirtyRatio_clicked(); break;
        case 4: _t->on_hourRatio_clicked(); break;
        case 5: _t->onCellChanges((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 6: _t->on_addDoctorButton_clicked(); break;
        case 7: _t->on_appointmentTable_cellDoubleClicked((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2]))); break;
        case 8: _t->onDataChange((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[2]))); break;
        case 9: _t->searchPSelected((*reinterpret_cast< std::add_pointer_t<Patient>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[2]))); break;
        case 10: _t->doctorSelected((*reinterpret_cast< std::add_pointer_t<QItemSelection>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<QItemSelection>>(_a[2]))); break;
        case 11: _t->displayDoctors(); break;
        case 12: _t->showRCMenu((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 13: _t->showDoctorsMenu((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 10:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 1:
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< QItemSelection >(); break;
            }
            break;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (AgendaView::*)(const Patient & )>(_a, &AgendaView::patientSelected, 0))
            return;
    }
}

const QMetaObject *AgendaView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AgendaView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN10AgendaViewE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int AgendaView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void AgendaView::patientSelected(const Patient & _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}
QT_WARNING_POP
