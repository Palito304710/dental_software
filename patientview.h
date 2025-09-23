 #ifndef PATIENTVIEW_H
#define PATIENTVIEW_H

#include <QObject>
#include <QWidget>

#include "agenda.h"
#include "db.h"

namespace Ui
{
class PatientView;
}

class PatientView : public QWidget
{
    Q_OBJECT
public:
    explicit PatientView(QWidget *parent = nullptr, db* database = nullptr);
    ~PatientView();
    void displayPatient(const Patient &patient);
    void addRow (const QString& field, const std::string &value);
    void addRowBool(const QString& field, const bool &value);
    void onCellChanges(int row, int col);
    int updatePrice();
    void onAppointmentCellChanges(int row, int col);
    void updateTotalPriceDisplay();


private:
    Ui::PatientView *ui;
    db* myDb;
    Patient currP;
    int totalPriceRow = -1;

private slots:
    void on_backToAgenda_clicked();
    void updateAppointments();

signals:
    void backToAgenda();
};

#endif // PATIENTVIEW_H
