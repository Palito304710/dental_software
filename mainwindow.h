#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>
#include "agendaview.h"
#include "patientview.h"
#include "db.h"
#include <QCalendar>
#include <QCalendarWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void switchToPatientView(const Patient &patient);
    void backToAgenda();
    void onDateSelected();
    void highlightCalendarDates();

private:
    Ui::MainWindow *ui;
    AgendaView *agendaView;
    PatientView *patientView;
    QStackedWidget *stackedWidget;
    db *mydb;
    QCalendarWidget *calendar;
    QHBoxLayout *mainLayout;
    QWidget *sidebarWidget;
    QVBoxLayout *sidebarLayout;

    void clearSidebar();
    void addPatientSidebarContent(const Patient& patient);
};
#endif // MAINWINDOW_H
