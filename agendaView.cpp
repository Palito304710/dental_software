#include "agendaview.h"
#include "agenda.h"
#include "ui_agendaView.h"

#include"appointmentdelegate.h"

AgendaView::AgendaView(QWidget *main, db *database) : QWidget(main), ui(new Ui::AgendaView), myDb(database)
{
    ui->setupUi(this);

    ui->thirtyRatio->setChecked(true);

    ui->appointmentTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->appointmentTable, &QWidget::customContextMenuRequested, this, &AgendaView::showRCMenu);

    ui->doctorsList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->doctorsList, &QWidget::customContextMenuRequested, this, &AgendaView::showDoctorsMenu);
    ui->doctorsList->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui-> appointmentTable -> setEditTriggers(QAbstractItemView::AnyKeyPressed | QAbstractItemView::EditKeyPressed);
    appointmentDelegate = new AppointmentDelegate(this, myDb);
    ui->appointmentTable->setItemDelegate(appointmentDelegate);
    connect(appointmentDelegate, &AppointmentDelegate::patientSelected, this, &AgendaView::searchPSelected);

    connect(ui->appointmentTable, &QTableWidget::cellChanged,  this, &AgendaView::onCellChanges);
    connect(ui->appointmentTable->model(), &QAbstractItemModel::dataChanged, this, &AgendaView::onDataChange);

    updateTable();
    displayDoctors();



}

AgendaView::~AgendaView()
{
    delete ui;
}


void AgendaView::onCellChanges(int row, int column)
{
    QTableWidgetItem *item = ui->appointmentTable->item(row, column);

    if(!item)
        return;

    QString patientName = item->text();

    if(patientName.isEmpty())
        return;

    QTableWidgetItem *itemTime = ui->appointmentTable->verticalHeaderItem(row);
    if(!itemTime)
        return;
    QString timeSlot = itemTime->text();

    QTableWidgetItem *itemDoctor = ui->appointmentTable->horizontalHeaderItem(column);
    if (!itemDoctor)
        return;
    QString doctor = itemDoctor->text();


    int appointmentId = item->data(Qt::UserRole+1).toInt();
    bool completed = item->data(Qt::UserRole).toBool();

    if (appointmentId > 0)
    {
        myDb->updateCompleted(appointmentId, completed);
    }
    else
    {
        int patientId = myDb->getPatientIdByName(patientName);

        if (patientId == -1)
        {
            Patient p;
            p.patientName = patientName.toStdString();
            p.occupation = "";
            p.phoneNumber = "";
            p.telPhone = "";
            patientId = myDb->addPatient(p);
        }

        Appointment newApp;
        newApp.patientId = patientId;
        newApp.timeSlot = timeSlot.toStdString();
        newApp.appointmentDate = currentDate.toString("yyyy-MM-dd").toStdString();
        newApp.doctor = doctor.toStdString();
        newApp.completed = completed;
        newApp.notes = "";
        newApp.price = 0;
        newApp.paid = 0;

        int added = myDb->addAppointment(newApp);
        qDebug() << "added" << newApp.timeSlot << newApp.doctor;

        if (added == -1)
            qDebug("Didn't add");
    }

    disconnect(ui->appointmentTable, &QTableWidget::cellChanged, this, &AgendaView::onCellChanges);
    updateTable();
    connect(ui->appointmentTable, &QTableWidget::cellChanged, this, &AgendaView::onCellChanges);
}






void AgendaView::on_addButton_clicked()
{
    std::string patientName = ui->patientName->text().toStdString();
    std::string doctor = ui -> doctor -> text().toStdString();
    std::string timeSlot = ui-> timeSlot-> text().toStdString();

    Patient newApp;


    myAgenda.addAppointment(newApp);

    ui->patientName->clear();
    ui->doctor->clear();
    ui->timeSlot->clear();

    updateTable();
}





void AgendaView::on_removeButton_clicked()
{
    int row = ui-> appointmentTable->currentRow();

    myAgenda.removeAppointment(row);
    updateTable();
}




void AgendaView::displayDoctors()
{
    qDebug("displya");
    QStringListModel *model = new QStringListModel(this);

    std::vector<std::string> doctors = myDb->getAllDoctors();

    QStringList doctorsList;

    for (const auto &doctor :doctors)
    {
        doctorsList << QString::fromStdString(doctor);
    }

    model->setStringList(doctorsList);

    ui->doctorsList->setModel(model);

    ui->doctorsList->setSelectionMode(QAbstractItemView::MultiSelection);


    if (ui->doctorsList->selectionModel())
    {
        disconnect(ui->doctorsList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &AgendaView::doctorSelected);
        qDebug("displyaq");
    }

    connect(ui->doctorsList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &AgendaView::doctorSelected);


    for (int row = 0; row < model->rowCount(); row++)
    {
        QModelIndex index = model->index(row);
        qDebug("displyqa");
        ui->doctorsList->selectionModel()->select(index, QItemSelectionModel::Select);
    }
}





void AgendaView::updateTable()
{
    disconnect(ui->appointmentTable, &QTableWidget::cellChanged,  this, &AgendaView::onCellChanges);

    ui-> appointmentTable -> setColumnCount(selectedDoctors.size());
    QStringList headers;
    for(const auto& doctor : selectedDoctors)
    {
        headers << QString::fromStdString(doctor);
    }

    ui-> appointmentTable -> setHorizontalHeaderLabels(headers);
    int size;

    QStringList timeLabels;
    if (thirty)
    {
        size = (21-8) * 2;
        ui -> appointmentTable -> setRowCount(size);
        for (int i = 0; i < size; i++)
        {
            int hour = 8 + (i/2);
            int minutes = (i % 2) * 30;

            QString timeSlot = QString("%1:%2").arg(hour, 2, 10, QChar('0')).arg(minutes, 2, 10, QChar('0'));

            timeLabels << timeSlot;
        }
        ui-> appointmentTable -> setVerticalHeaderLabels(timeLabels);
    }

    else
    {
        size = 21-8;

        ui -> appointmentTable -> setRowCount(size);

        for(int i = 8; i <= 21; i++)
        {
            QString timeSlot = QString("%1:%2").arg(i,2,10,QChar('0')).arg(0, 2, 10, QChar('0'));
            timeLabels << timeSlot;
        }

        ui -> appointmentTable -> setVerticalHeaderLabels(timeLabels);
    }

    for (int row = 0; row < ui-> appointmentTable->rowCount(); row++)
    {
        for (int col = 0; col < ui -> appointmentTable->columnCount(); col++)
        {
            ui->appointmentTable->setItem(row,col, new QTableWidgetItem(""));
        }
    }


    QString dateString = currentDate.toString("yyyy-MM-dd");
    std::vector<Appointment> appointments = myDb->getAppointmentbyDate(dateString);

    for (const auto& app: appointments)
    {
        int row = -1;
        for (int i = 0; i < timeLabels.size(); i++)
        {
            if(timeLabels[i] == app.timeSlot)
            {
                row = i;
                break;
            }
        }

        int col = -1;
        for (int i = 0; i < selectedDoctors.size(); i++)
        {
            if (selectedDoctors[i]==app.doctor)
            {
                col = i;
                break;
            }
        }

        if (row != -1 && col != -1)
        {
            QString patientName = myDb->getPatientNameById(app.patientId);
            QTableWidgetItem *item = new QTableWidgetItem(patientName);
            item->setData(Qt::UserRole+1, app.appointmentId);
            item->setData(Qt::UserRole, app.completed);
            ui->appointmentTable->setItem(row, col, item);
        }
    }



    for (int row = 0; row < ui->appointmentTable->rowCount(); row++)
    {
        for(int col = 0; col < ui->appointmentTable->columnCount(); col++)
        {
            QTableWidgetItem *item = ui->appointmentTable->item(row, col);

        }
    }

    int appointmentCount = appointments.size();
    this->window()->setWindowTitle(QString("Appointments for %1: %2")
                                       .arg(currentDate.toString("yyyy-MM-dd"))
                                       .arg(appointmentCount));



    connect(ui->appointmentTable, &QTableWidget::cellChanged,  this, &AgendaView::onCellChanges);

}







void AgendaView::on_addDoctorButton_clicked()
{
    std::string doctor = ui->doctor->text().toStdString();
    bool added = myDb->addDoctor(doctor);
    displayDoctors();
    updateTable();
    ui->doctor->clear();

}


void AgendaView::on_thirtyRatio_clicked()
{
    thirty = true;
    updateTable();
}

void AgendaView::on_hourRatio_clicked()
{
    thirty=false;
    updateTable();
}



void AgendaView::on_appointmentTable_cellDoubleClicked(int row, int col)
{
    QTableWidgetItem *item = ui->appointmentTable->item(row, col);

    if(!item || item->text().isEmpty())
        return;

    QString patientName = item->text();

    Patient patientSel = myDb->getPatientByName(patientName);

    emit patientSelected(patientSel);

}



void AgendaView::onDataChange(const QModelIndex& left, const QModelIndex& right)
{
    QTableWidgetItem *item = ui->appointmentTable->item(left.row(), left.column());

    if (!item)
        return;

    int id = item->data(Qt::UserRole+1).toInt();
    bool completed = item->data(Qt::UserRole).toBool();

    myDb->appStatus(id, completed);
}


void AgendaView::searchPSelected(const Patient& patient, const QModelIndex& index)
{
    QTableWidgetItem *item = ui->appointmentTable->item(index.row(), index.column());
    if (item)
        item->setText(QString::fromStdString(patient.patientName));
}


void AgendaView::doctorSelected(const QItemSelection &sel, const QItemSelection &des)
{


    selectedDoctors.clear();

    QList<QModelIndex> selected = ui->doctorsList->selectionModel()->selectedIndexes();



    for (const auto &i : selected)
    {
        QString doctor = i.data().toString();
        selectedDoctors.push_back(doctor.toStdString());
    }

    updateTable();
}


void AgendaView::showRCMenu(const QPoint &pos)
{
    QModelIndex index = ui->appointmentTable->indexAt(pos);

    if(!index.isValid())
        return;

    QTableWidgetItem *item = ui->appointmentTable->item(index.row(), index.column());
    if(!item || item->text().isEmpty())
        return;

    QString name = item->text();
    QString timeSlot = ui->appointmentTable->verticalHeaderItem(index.row())->text();
    QString doctor = ui->appointmentTable->horizontalHeaderItem(index.column())->text();

    int appointmentId = myDb->getAppointmentId(name, timeSlot, doctor);

    if (appointmentId == -1)
    {
        qDebug("Problem getting the ID");
        return;
    }

    QMenu menu(this);

    menu.addAction("Delete Appointment", this, [this,appointmentId] ()
    {
        bool del = myDb->deleteAppointment(appointmentId);

        if(!del)
            qDebug("wasnt deleted");

        updateTable();
    });

    QPoint globalPos = ui->appointmentTable->mapToGlobal(pos);
    globalPos.setY(globalPos.y() + 40);
    globalPos.setX(globalPos.x() + 20);
    menu.exec(globalPos);
}

void AgendaView::showDoctorsMenu(const QPoint &pos)
{
    QModelIndex index = ui->doctorsList->indexAt(pos);

    if(!index.isValid())
        return;

    QString item = index.data().toString();

    if(item.isEmpty())
        return;

    QMenu menu(this);

    menu.addAction("Delete Doctor", this, [this, item] ()
    {
        bool del =  myDb->deleteDoctor(item);

        if (!del)
        {
            qDebug("could not delete doctor");
            return;
        }

        displayDoctors();
        updateTable();
    });

    menu.addAction("Modify Doctor", this, [this, item] ()
    {
        bool ok;
        QString newName = QInputDialog::getText(this, "Modify Doctor","Enter new name:", QLineEdit::Normal, item, &ok);

        if (ok && !newName.isEmpty()) {

            bool updated = myDb->updateDoctor(item, newName);
            if (!updated)
            {
                qDebug("could not change doctor name");
                return;
            }

            displayDoctors();
            updateTable();
        }
    });

    QPoint globalPos = ui->doctorsList->mapToGlobal(pos);
    globalPos.setY(globalPos.y() + 40);
    globalPos.setX(globalPos.x() + 20);
    menu.exec(globalPos);
}



void AgendaView::setDisplayDate(const QDate& date)
{
    // Store the selected date
    currentDate = date;
    // Update the table to show appointments for this date
    updateTable();
}
