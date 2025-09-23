#ifndef AGENDA_H
#define AGENDA_H

#include <string>
#include <vector>


struct Patient
{
    int patientId;
    std::string patientName;
    std::string phoneNumber;
    std::string telPhone;
    std::string occupation;
    int value = 0;
};

struct Appointment
{
    int appointmentId;
    int patientId;
    std::string doctor;
    std::string timeSlot;
    std::string appointmentDate;
    bool completed;
    std::string notes;
    int price;
    bool paid;
};



class Agenda
{
private:
    std::vector<Patient> Appointments;

public:
    Agenda();

    void addAppointment(const Patient& newapp);
    void removeAppointment(int index);
};

#endif // AGENDA_H

