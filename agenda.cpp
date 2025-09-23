#include "agenda.h"

#include <vector>
#include <string>
#include <QDebug>

Agenda::Agenda() {}


void Agenda::addAppointment(const Patient& newapp)
{
    Appointments.push_back(newapp);
}


void Agenda::removeAppointment(int index)
{
    Appointments.erase(Appointments.begin() + index);
}


