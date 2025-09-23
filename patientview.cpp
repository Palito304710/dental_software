#include "patientview.h"
#include "agendaview.h"
#include "ui_patientView.h"
#include "agenda.h"


PatientView::PatientView(QWidget *parent, db* database) :QWidget(parent), ui(new Ui::PatientView), myDb(database)
{
    ui-> setupUi(this);

    ui->patientInfo->setColumnCount(2);
    ui->patientInfo->setHorizontalHeaderLabels({"Field", "Value"});
    ui->appointmentsInfo->setColumnCount(6);
    ui->appointmentsInfo->setHorizontalHeaderLabels({"Date", "Time", "Doctor", "Completed?", "Value", "Paid"});

    connect(ui->patientInfo, &QTableWidget::cellChanged, this, &PatientView::onCellChanges);
    connect(ui->appointmentsInfo, &QTableWidget::cellChanged, this, &PatientView::onAppointmentCellChanges);


    ui->appointmentsInfo->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);

}

PatientView::~PatientView()
{

}

void PatientView::displayPatient(const Patient &patient)
{
    currP = patient;
    currP.value = updatePrice();

    ui->patientInfo->setRowCount(0);
    addRow("Name", patient.patientName);
    addRow("Phone Number", patient.phoneNumber);
    addRow("Telephone", patient.telPhone);
    addRow("Occupation", patient.occupation);

    totalPriceRow = ui->patientInfo->rowCount();
    addRow("Total price", std::to_string(patient.value));

    updateAppointments();
}

void PatientView::addRow (const QString& field, const std::string &value)
{
    int rows = ui->patientInfo -> rowCount();
    ui-> patientInfo -> insertRow(rows);

    QTableWidgetItem *fieldVal = new QTableWidgetItem(field);
    QTableWidgetItem *valueVal = new QTableWidgetItem(QString::fromStdString(value));

    fieldVal->setFlags(fieldVal->flags() & ~Qt::ItemIsEditable);

    if (field == "Name")
        valueVal->setFlags(valueVal->flags() & ~Qt::ItemIsEditable);

    ui-> patientInfo -> setItem(rows, 0, fieldVal);
    ui-> patientInfo -> setItem(rows, 1, valueVal);

}

void PatientView::on_backToAgenda_clicked()
{
    emit backToAgenda();
}

void PatientView::addRowBool(const QString& field, const bool &value)
{
    int rows = ui->patientInfo -> rowCount();
    ui-> patientInfo -> insertRow(rows);

    QTableWidgetItem *fieldVal = new QTableWidgetItem(field);
    QTableWidgetItem *valueVal = new QTableWidgetItem(value ? "Yes" : "No");

    ui-> patientInfo -> setItem(rows, 0, fieldVal);
    ui-> patientInfo -> setItem(rows, 1, valueVal);
}

void PatientView::onCellChanges(int row, int col)
{

    QTableWidgetItem *item = ui->patientInfo->item(row, col);

    switch(row){

    case 1:
        currP.phoneNumber = item->text().toStdString();
        break;
    case 2:
        currP.telPhone = item->text().toStdString();
        break;
    case 3:
        currP.occupation = item->text().toStdString();
        break;

    default:
        break;

    }

    bool gotIt = myDb->updatePatient(currP);

    if (!gotIt)
        qDebug("couldnt udpate");


}

void PatientView::updateAppointments()
{
    ui->appointmentsInfo->setRowCount(0);
    int patientId = myDb->getPatientIdByName(QString::fromStdString(currP.patientName));
    std::vector<Appointment> apps = myDb->getPatientApps(patientId);

    for (const auto& app : apps)
    {
        int row = ui->appointmentsInfo->rowCount();
        ui->appointmentsInfo->insertRow(row);

        QTableWidgetItem *itemDate = new QTableWidgetItem(QString::fromStdString(app.appointmentDate));
        itemDate->setFlags(itemDate->flags() & ~Qt::ItemIsEditable);
        ui->appointmentsInfo->setItem(row, 0, itemDate);

        QTableWidgetItem *itemTime = new QTableWidgetItem(QString::fromStdString(app.timeSlot));
        itemTime->setFlags(itemTime->flags() & ~Qt::ItemIsEditable);
        ui->appointmentsInfo->setItem(row, 1, itemTime);

        QTableWidgetItem *itemDoctor = new QTableWidgetItem(QString::fromStdString(app.doctor));
        itemDoctor->setFlags(itemDoctor->flags() & ~Qt::ItemIsEditable);
        ui->appointmentsInfo->setItem(row, 2, itemDoctor);

        QTableWidgetItem *itemComp = new QTableWidgetItem(app.completed ? "Yes" : "No");
        itemComp->setFlags(itemComp->flags() & ~Qt::ItemIsEditable);
        ui->appointmentsInfo->setItem(row, 3, itemComp);

        QTableWidgetItem *itemVal = new QTableWidgetItem(QString::number(app.price));
        ui->appointmentsInfo->setItem(row, 4, itemVal);

        QTableWidgetItem *itemPaid = new QTableWidgetItem();
        itemPaid->setCheckState(app.paid ? Qt::Checked : Qt::Unchecked);
        itemPaid->setFlags(itemPaid->flags() & ~Qt::ItemIsEditable &~Qt::ItemIsSelectable);
        itemPaid->setData(Qt::UserRole, app.appointmentId);
        ui->appointmentsInfo->setItem(row, 5, itemPaid);

    }

    ui->appointmentsInfo->resizeColumnsToContents();
}

int PatientView::updatePrice()
{
    int patientId = myDb -> getPatientIdByName(QString::fromStdString(currP.patientName));
    std::vector<Appointment> apps = myDb -> getPatientApps(patientId);
    int total = 0;

    for (const auto& app : apps)
    {
        if (app.paid)
        total += app.price;
    }


    return total;
}


void PatientView::onAppointmentCellChanges(int row, int col)
{
    QTableWidgetItem *item = ui->appointmentsInfo->item(row, col);

    if (!item) return;

    int patientId = myDb->getPatientIdByName(QString::fromStdString(currP.patientName));
    std::vector<Appointment> apps = myDb->getPatientApps(patientId);

    if (row >= 0 && row < (int)apps.size()) {
        if (col == 4) {
            bool ok;
            int newPrice = item->text().toInt(&ok);
            if (!ok) {
                qDebug("Invalid number typed for price!");
                return;
            }
            apps[row].price = newPrice;
        }
        else if (col == 5) {
            apps[row].paid = (item->checkState() == Qt::Checked);
        }

        myDb->updateAppointment(apps[row]);


        currP.value = updatePrice();


                myDb -> updatePatient(currP);

            updateTotalPriceDisplay();


    }
}

void PatientView::updateTotalPriceDisplay()
{
    if (totalPriceRow >= 0 && totalPriceRow < ui->patientInfo->rowCount()) {
        QTableWidgetItem *valueItem = ui->patientInfo->item(totalPriceRow, 1);
        if (valueItem) {
            ui->patientInfo->blockSignals(true);
            valueItem->setText(QString::number(currP.value));
            ui->patientInfo->blockSignals(false);
        }
    }
}

