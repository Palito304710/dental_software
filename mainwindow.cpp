#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "agendaview.h"
#include "patientview.h"
#include <QMessageBox>
#include <QCalendar>
#include <QHBoxLayout>
#include <QCalendarWidget>
#include <QVBoxLayout>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mydb = new db();
    bool connected = mydb->connect("127.0.0.1", 3306, "clinic_db", "clinic_user", "vitoriasc47A");

    if (!connected) {
        QMessageBox::critical(this, "Database Error", "Failed to connect to database");
    }

    agendaView = new AgendaView(this, mydb);
    patientView = new PatientView(this, mydb);

    QWidget *centralWidget = new QWidget(this);
    mainLayout = new QHBoxLayout(centralWidget);

    stackedWidget = new QStackedWidget();
    stackedWidget->addWidget(agendaView);
    stackedWidget->addWidget(patientView);

    sidebarWidget = new QWidget();
    sidebarWidget->setFixedWidth(300);
    sidebarLayout = new QVBoxLayout(sidebarWidget);

    calendar = new QCalendarWidget();
    calendar->setSelectedDate(QDate::currentDate());
    sidebarLayout->addWidget(calendar);

    mainLayout->addWidget(stackedWidget, 1);
    mainLayout->addWidget(sidebarWidget, 0);

    setCentralWidget(centralWidget);

    connect(agendaView, &AgendaView::patientSelected, this, &MainWindow::switchToPatientView);
    connect(patientView, &PatientView::backToAgenda, this, &MainWindow::backToAgenda);
    connect(calendar, &QCalendarWidget::selectionChanged, this, &MainWindow::onDateSelected);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete mydb;
}

void MainWindow::switchToPatientView(const Patient &patient)
{
    patientView->displayPatient(patient);
    stackedWidget->setCurrentWidget(patientView);

    clearSidebar();
    addPatientSidebarContent(patient);
}

void MainWindow::backToAgenda()
{
    stackedWidget->setCurrentWidget(agendaView);

    clearSidebar();
    sidebarLayout->addWidget(calendar);
}

void MainWindow::onDateSelected()
{
    QDate selectedDate = calendar->selectedDate();
    agendaView->setDisplayDate(selectedDate);
}

void MainWindow::highlightCalendarDates()
{

}

void MainWindow::clearSidebar()
{
    while (QLayoutItem* item = sidebarLayout->takeAt(0)) {
        if (QWidget* widget = item->widget()) {
            widget->setParent(nullptr);
        }
        delete item;
    }
}

void MainWindow::addPatientSidebarContent(const Patient& patient)
{
}
