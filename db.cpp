#include "db.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QCoreApplication>

db::db() {}
bool db::connect(const QString& host, int port, const QString& dbName, const QString& user, const QString& pass)
{
    qDebug() << "Available SQL drivers:" << QSqlDatabase::drivers();
    qDebug() << "Current working directory:" << QDir::currentPath();

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    QString dbPath = QDir::homePath() + "/Desktop/clinic.db";
    db.setDatabaseName(dbPath);
    qDebug() << "Database path:" << dbPath;

    if (!db.open()) {
        qDebug() << "Database connection failed!";
        qDebug() << db.lastError().text();
        return false;
    }

    qDebug() << "Database opened successfully!";

    return true;
}




int db::addPatient(const Patient &patient)
{
    QSqlQuery q;

    q.prepare("INSERT INTO patient (name, phoneNumber, tel, occupation, value)" "VALUES (?, ?, ?, ?, ?)");

    q.addBindValue(QString::fromStdString(patient.patientName));
    q.addBindValue(QString::fromStdString(patient.phoneNumber));
    q.addBindValue(QString::fromStdString(patient.telPhone));
    q.addBindValue(QString::fromStdString(patient.occupation));
    q.addBindValue(patient.value);


    if (!q.exec())
    {
        qDebug() << q.lastError().text();
        return -1;
    }


    return q.lastInsertId().toInt();
}

int db::addAppointment(const Appointment& appointment)
{

    QSqlQuery q;

    q.prepare("INSERT INTO appointments (patientId, doctor, timeSlot, appointmentDate, completed, notes, price, paid) VALUES (?, ?, ?, ?, ?, ?, ?, ?)");

    q.addBindValue(appointment.patientId);
    q.addBindValue(QString::fromStdString(appointment.doctor));
    q.addBindValue(QString::fromStdString(appointment.timeSlot));
    q.addBindValue(QString::fromStdString(appointment.appointmentDate));
    q.addBindValue(appointment.completed);
    q.addBindValue(QString::fromStdString(appointment.notes));
    q.addBindValue(appointment.price);
    q.addBindValue(appointment.paid);

    if (!q.exec()) {
        qDebug() << q.lastError().text();
        return -1;
    }

    return q.lastInsertId().toInt();
}

std::vector<Appointment> db::getAllAppointments()
{
    std::vector<Appointment> appointments;
    QSqlQuery q("SELECT id, patientId, doctor, timeSlot, appointmentDate, completed, notes, price, paid FROM appointments");

    while (q.next())
    {
        Appointment app;
        app.appointmentId = q.value(0).toInt();
        app.patientId = q.value(1).toInt();
        app.doctor = q.value(2).toString().toStdString();
        app.timeSlot = q.value(3).toString().toStdString();
        app.appointmentDate = q.value(4).toString().toStdString();
        app.completed = q.value(5).toBool();
        app.notes = q.value(6).toString().toStdString();
        app.price = q.value(7).toInt();
        app.paid = q.value(8).toBool();

        appointments.push_back(app);
    }

    return appointments;
}

std::vector<Appointment> db::getAppointmentbyDate(const QString &date)
{
    std::vector<Appointment> appointments;
    QSqlQuery q("SELECT id, patientId, doctor, timeSlot, appointmentDate, completed, notes, price, paid FROM appointments WHERE appointmentDate = ?");
    q.addBindValue(date);

    if (!q.exec()) {  // Add this check!
        qDebug() << "Failed to get appointments by date:" << q.lastError().text();
        return appointments;
    }

    while (q.next())
    {
        Appointment app;
        app.appointmentId = q.value(0).toInt();
        app.patientId = q.value(1).toInt();
        app.doctor = q.value(2).toString().toStdString();
        app.timeSlot = q.value(3).toString().toStdString();
        app.appointmentDate = q.value(4).toString().toStdString();
        app.completed = q.value(5).toBool();
        app.notes = q.value(6).toString().toStdString();
        app.price = q.value(7).toInt();
        app.paid = q.value(8).toBool();

        appointments.push_back(app);
    }

    return appointments;
}

bool db::appStatus(const int& id, const bool& completed)
{
    QSqlQuery q ("UPDATE appointments SET completed = ? WHERE id  = ?");
    q.addBindValue(completed);
    q.addBindValue(id);

    if (q.exec())
        return true;

    qDebug() << q.lastError();
    return false;
}

Patient db::getPatientByName(const QString& patientName)
{
    QSqlQuery q;
    q.prepare("SELECT * FROM patient WHERE name = ?");
    q.addBindValue(patientName);

    Patient p;
    if (q.exec() && q.next()) {
        p.patientId = q.value(0).toInt();
        p.patientName = patientName.toStdString();
        p.phoneNumber = q.value(2).toString().toStdString();
        p.telPhone = q.value(3).toString().toStdString();
        p.occupation = q.value(4).toString().toStdString();
        p.value = q.value(5).toInt();
    } else {
        qDebug() << q.lastError().text();
    }

    return p;
}

QString db::getPatientNameById(const int& id)
{
    QSqlQuery q;
    q.prepare("SELECT name FROM patient WHERE id = ?");
    q.addBindValue(id);

    QString name;
    if (q.exec() && q.next()) {
        name = q.value(0).toString();
    } else {
        qDebug() << q.lastError().text();
    }

    return name;
}


int db::getPatientIdByName(const QString& name)
{
    QSqlQuery q;
    q.prepare("SELECT id FROM patient WHERE name = ?");
    q.addBindValue(name);

    int id = -1;
    if (q.exec() && q.next()) {
        id = q.value(0).toInt();
    }

    return id;
}


bool db::updatePatient(const Patient& p)
{
    int id = getPatientIdByName(QString::fromStdString(p.patientName));
    QSqlQuery q;

    q.prepare("UPDATE patient SET name = ?, phoneNumber = ?, tel = ?, occupation = ?, value = ? WHERE id = ?");
    q.addBindValue(QString::fromStdString(p.patientName));
    q.addBindValue(QString::fromStdString(p.phoneNumber));
    q.addBindValue(QString::fromStdString(p.telPhone));
    q.addBindValue(QString::fromStdString(p.occupation));
    q.addBindValue(p.value);
    q.addBindValue(id);

    if (!q.exec())
    {
        qDebug() << q.lastError();
        return false;
    }

    return true;
}

std::vector<QString> db::searchPatients(const QString& text)
{
    std::vector<QString> results;
    QSqlQuery q;

    if (!q.prepare("SELECT name FROM patient WHERE name LIKE ? LIMIT 6")) {
        qDebug() << "Query prepare failed:" << q.lastError().text();
        return results;
    }

    q.addBindValue("%" + text + "%");

    if (!q.exec()) {
        qDebug() << "Query exec failed:" << q.lastError().text();
        return results;
    }

    while (q.next()) {
        results.push_back(q.value(0).toString());
    }

    return results;
}

std::vector<std::string> db::getAllDoctors()
{
    std::vector<std::string> doctors;

    QSqlQuery q;
    q.prepare("SELECT name FROM doctor");

    if (!q.exec()) {
        qDebug() << "Error fetching doctors:" << q.lastError().text();
        return doctors;
    }

    while (q.next())
    {
        QString doctor = q.value(0).toString();
        doctors.push_back(doctor.toStdString());
    }

    return doctors;
}

bool db::addDoctor(const std::string &doctor)
{
    QSqlQuery q;


    q.prepare("INSERT INTO doctor (name) VALUES (?)");
    q.addBindValue(QString::fromStdString(doctor));

    if (!q.exec())
    {
        qDebug("could not add");
        return false;
    }

    return true;


}


int db::getAppointmentId(const QString &name, const QString &timeSlot, const QString &doctor)
{
    QSqlQuery q;

    int patientId = getPatientIdByName(name);

    if (patientId == -1)
    {
        qDebug("could not find the patient");
        return -1;
    }

    q.prepare("SELECT id FROM appointments WHERE patientId = ? AND timeSlot = ? AND doctor = ?");
    q.addBindValue(patientId);
    q.addBindValue(timeSlot);
    q.addBindValue(doctor);

    if (!q.exec())
    {
        qDebug("Could not get appointment Id");
        return -1;
    }

    if (q.next())
    {
        int appointmentId = q.value(0).toInt();
        return appointmentId;
    }
    else
    {
        qDebug() << "No appointment found:" << name << timeSlot << doctor;
        return -1;
    }

}

bool db::deleteAppointment(const int &id)
{
    QSqlQuery q;

    q.prepare("DELETE FROM appointments WHERE id = ?");
    q.addBindValue(id);
    if (!q.exec())
    {
        qDebug("Cant delete appointment");
        return false;
    }

    return true;
}

bool db:: deleteDoctor(const QString &name)
{
    QSqlQuery q;

    q.prepare("DELETE FROM doctor WHERE name = ?");
    q.addBindValue(name);

    if (!q.exec())
    {
        qDebug() << q.lastError();
        return false;
    }

    return true;
}


bool db :: updateDoctor(const QString &old, const QString &newName)
{
    QSqlQuery q;

    q.prepare("UPDATE doctor SET name = ? WHERE name = ?");
    q.addBindValue(newName);
    q.addBindValue(old);

    if (q.exec())
        return true;

    qDebug() << q.lastError();
    return false;
}

std::vector<Appointment> db::getPatientApps(const int &id)
{
    std::vector<Appointment> apps;
    QSqlQuery q;

    q.prepare("SELECT id, patientId, doctor, timeSlot, appointmentDate, completed, notes, price, paid FROM appointments WHERE patientId = ?");
    q.addBindValue(id);

    if (!q.exec()) {
        qDebug() << "Failed to get patient appointments:" << q.lastError().text();
        return apps;
    }

    while (q.next())
    {
        Appointment app;
        app.appointmentId = q.value(0).toInt();
        app.patientId = q.value(1).toInt();
        app.doctor = q.value(2).toString().toStdString();
        app.timeSlot = q.value(3).toString().toStdString();
        app.appointmentDate = q.value(4).toString().toStdString();
        app.completed = q.value(5).toBool();
        app.notes = q.value(6).toString().toStdString();
        app.price = q.value(7).toInt();
        app.paid = q.value(8).toBool();
        apps.push_back(app);
    }

    return apps;
}


bool db::updateCompleted(const int &appointmentId, const bool &completed)
{
    QSqlQuery q;

    q.prepare("UPDATE appointments SET completed = ? WHERE id = ?");
    q.addBindValue(completed);
    q.addBindValue(appointmentId);

    if (!q.exec())
    {
        qDebug() << "could not update completed";
        return false;
    }

    return true;
}

bool db::updateAppointment(const Appointment &app)
{
    QSqlQuery q;

    q.prepare("UPDATE appointments SET patientId = ?, doctor = ?, timeSlot = ?, completed = ?, notes = ?, price = ?, paid = ? WHERE id = ?");

    q.addBindValue(app.patientId);
    q.addBindValue(QString::fromStdString(app.doctor));
    q.addBindValue(QString::fromStdString(app.timeSlot));
    q.addBindValue(app.completed);
    q.addBindValue(QString::fromStdString(app.notes));
    q.addBindValue(app.price);
    q.addBindValue(app.paid);
    q.addBindValue(app.appointmentId);

    if (!q.exec()) {
        qDebug() << "Failed to update appointment:" << q.lastError().text();
        return false;
    }

    return true;
}


Appointment db::getAppointmentById(const int &id)
{
    QSqlQuery q;

    q.prepare("SELECT * FROM appointments WHERE id = ?");
    q.addBindValue(id);

    Appointment a;
    if (q.exec() && q.next())
    {
        a.appointmentId = q.value(0).toInt();
        a.completed = q.value(1).toBool();
        a.doctor = q.value(2).toString().toStdString();
        a.notes = q.value(3).toString().toStdString();
        a.paid = q.value(4).toBool();
        a.patientId = q.value(5).toInt();
        a.timeSlot= q.value(6).toString().toStdString();


    }


    return a;
}



