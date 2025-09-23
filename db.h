#ifndef DB_H
#define DB_H

#include <QString>
#include "agenda.h"
#include <QtSql>
#include <QtCore>
class db
{
public:
    db();
    bool connect(const QString& host, int port, const QString& dbName, const QString& user, const QString& pass);
    int addPatient(const Patient &patient);
    int addAppointment(const Appointment &appointment);
    bool appStatus(const int& id, const bool& completed);
    std::vector<Appointment>getAllAppointments();
    std::vector<Appointment> getAppointmentbyDate(const QString &date);
    Patient getPatientByName(const QString& patientName);
    QString getPatientNameById(const int& id);
    int getPatientIdByName(const QString& name);
    bool updatePatient(const Patient& p);
    std::vector<QString> searchPatients(const QString& text);
    bool addDoctor(const std::string &doctor);
    std::vector<std::string> getAllDoctors();
    bool deleteAppointment(const int &id);
    int getAppointmentId(const QString &name, const QString &timeSlot, const QString &doctor);
    bool updateDoctor(const QString &old, const QString &newName);
    bool deleteDoctor(const QString &name);
    std::vector<Appointment> getPatientApps(const int &id);
    bool updateCompleted(const int &appointmentId, const bool &completed);
    bool updateAppointment(const Appointment &app);
    Appointment getAppointmentById(const int &id);
};

#endif // DB_H
