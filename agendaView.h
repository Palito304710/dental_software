#ifndef AGENDAVIEW_H
#define AGENDAVIEW_H

#include <QObject>
#include <QWidget>
#include "agenda.h"
#include <vector>
#include "db.h"
#include "appointmentdelegate.h"
#include <QMenu>
#include <QInputDialog>
#include <QMessageBox>


namespace Ui {
class AgendaView;
}

class AgendaView : public QWidget
{
    Q_OBJECT
public:
    explicit AgendaView(QWidget *main = nullptr, db* database = nullptr);
    const Agenda& getAgenda() const { return myAgenda; }
    void setDisplayDate(const QDate& date);
    ~AgendaView();

private slots:
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_thirtyRatio_clicked();
    void on_hourRatio_clicked();
    void onCellChanges(int row, int column);
    void on_addDoctorButton_clicked();
    void on_appointmentTable_cellDoubleClicked(int row, int col);
    void onDataChange(const QModelIndex& left, const QModelIndex& right);
    void searchPSelected(const Patient& patient, const QModelIndex& index);
    void doctorSelected(const QItemSelection &sel, const QItemSelection &des);
    void displayDoctors();
    void showRCMenu(const QPoint &pos);
    void showDoctorsMenu(const QPoint &pos);




signals:
    void patientSelected(const Patient& selectedPatient);

private:
    Ui::AgendaView *ui;
    Agenda myAgenda;
    void updateTable();
    bool thirty = true;
    db* myDb;
    AppointmentDelegate* appointmentDelegate;
    std::vector<std::string> selectedDoctors;
    QDate currentDate = QDate::currentDate();
};

#endif // AGENDAVIEW_H
