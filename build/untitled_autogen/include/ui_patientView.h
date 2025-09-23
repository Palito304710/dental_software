/********************************************************************************
** Form generated from reading UI file 'patientView.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PATIENTVIEW_H
#define UI_PATIENTVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PatientView
{
public:
    QTableWidget *patientInfo;
    QPushButton *backToAgenda;
    QTableWidget *appointmentsInfo;

    void setupUi(QWidget *PatientView)
    {
        if (PatientView->objectName().isEmpty())
            PatientView->setObjectName("PatientView");
        PatientView->resize(1337, 834);
        patientInfo = new QTableWidget(PatientView);
        patientInfo->setObjectName("patientInfo");
        patientInfo->setGeometry(QRect(180, 120, 371, 261));
        backToAgenda = new QPushButton(PatientView);
        backToAgenda->setObjectName("backToAgenda");
        backToAgenda->setGeometry(QRect(40, 60, 80, 24));
        appointmentsInfo = new QTableWidget(PatientView);
        appointmentsInfo->setObjectName("appointmentsInfo");
        appointmentsInfo->setGeometry(QRect(190, 490, 761, 192));

        retranslateUi(PatientView);

        QMetaObject::connectSlotsByName(PatientView);
    } // setupUi

    void retranslateUi(QWidget *PatientView)
    {
        PatientView->setWindowTitle(QCoreApplication::translate("PatientView", "Form", nullptr));
        backToAgenda->setText(QCoreApplication::translate("PatientView", "Back to Agenda", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PatientView: public Ui_PatientView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PATIENTVIEW_H
