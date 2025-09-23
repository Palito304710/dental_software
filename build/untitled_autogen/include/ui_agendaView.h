/********************************************************************************
** Form generated from reading UI file 'agendaView.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AGENDAVIEW_H
#define UI_AGENDAVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AgendaView
{
public:
    QLineEdit *patientName;
    QLineEdit *doctor;
    QLineEdit *timeSlot;
    QPushButton *addButton;
    QPushButton *removeButton;
    QTableWidget *appointmentTable;
    QGroupBox *appsRatio;
    QRadioButton *thirtyRatio;
    QRadioButton *hourRatio;
    QPushButton *addDoctorButton;
    QListView *doctorsList;

    void setupUi(QWidget *AgendaView)
    {
        if (AgendaView->objectName().isEmpty())
            AgendaView->setObjectName("AgendaView");
        AgendaView->resize(1413, 802);
        patientName = new QLineEdit(AgendaView);
        patientName->setObjectName("patientName");
        patientName->setGeometry(QRect(900, 40, 113, 22));
        doctor = new QLineEdit(AgendaView);
        doctor->setObjectName("doctor");
        doctor->setGeometry(QRect(40, 50, 113, 22));
        timeSlot = new QLineEdit(AgendaView);
        timeSlot->setObjectName("timeSlot");
        timeSlot->setGeometry(QRect(900, 140, 113, 22));
        addButton = new QPushButton(AgendaView);
        addButton->setObjectName("addButton");
        addButton->setGeometry(QRect(840, 220, 75, 24));
        removeButton = new QPushButton(AgendaView);
        removeButton->setObjectName("removeButton");
        removeButton->setGeometry(QRect(940, 220, 75, 24));
        appointmentTable = new QTableWidget(AgendaView);
        appointmentTable->setObjectName("appointmentTable");
        appointmentTable->setGeometry(QRect(240, 10, 911, 731));
        appsRatio = new QGroupBox(AgendaView);
        appsRatio->setObjectName("appsRatio");
        appsRatio->setGeometry(QRect(1190, 550, 120, 80));
        thirtyRatio = new QRadioButton(appsRatio);
        thirtyRatio->setObjectName("thirtyRatio");
        thirtyRatio->setGeometry(QRect(20, 20, 89, 20));
        hourRatio = new QRadioButton(appsRatio);
        hourRatio->setObjectName("hourRatio");
        hourRatio->setGeometry(QRect(20, 40, 89, 20));
        addDoctorButton = new QPushButton(AgendaView);
        addDoctorButton->setObjectName("addDoctorButton");
        addDoctorButton->setGeometry(QRect(50, 80, 80, 24));
        doctorsList = new QListView(AgendaView);
        doctorsList->setObjectName("doctorsList");
        doctorsList->setGeometry(QRect(50, 150, 171, 511));

        retranslateUi(AgendaView);

        QMetaObject::connectSlotsByName(AgendaView);
    } // setupUi

    void retranslateUi(QWidget *AgendaView)
    {
        AgendaView->setWindowTitle(QCoreApplication::translate("AgendaView", "Form", nullptr));
        addButton->setText(QCoreApplication::translate("AgendaView", "Add Appointment", nullptr));
        removeButton->setText(QCoreApplication::translate("AgendaView", "Remove Appointment", nullptr));
        appsRatio->setTitle(QCoreApplication::translate("AgendaView", "GroupBox", nullptr));
        thirtyRatio->setText(QCoreApplication::translate("AgendaView", "30 min Apps.", nullptr));
        hourRatio->setText(QCoreApplication::translate("AgendaView", "1 hour Apps.", nullptr));
        addDoctorButton->setText(QCoreApplication::translate("AgendaView", "Add Doctor", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AgendaView: public Ui_AgendaView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AGENDAVIEW_H
