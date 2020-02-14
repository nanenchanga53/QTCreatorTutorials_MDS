#ifndef CONT_H
#define CONT_H

#include <QWidget>

namespace Ui {
class cont;
}

class cont : public QWidget
{
    Q_OBJECT

public:
    explicit cont(QWidget *parent = nullptr);
    ~cont();

signals:
    void connLidar(QString, QString);
    void connCam(QString, QString);
    void connImu(QString, QString);
    void connSonar(QString, QString);

    void disconn();

public slots:
    void connectDevice();
    void disconnectDevice();

private slots:
    void on_accel_clicked();
    void on_brake_clicked();
    void on_left_clicked();
    void on_right_clicked();
    void on_emgr_clicked();
    void on_gear_valueChanged(int value);

    void on_lidarrad_textChanged(const QString &arg1);

private:
    Ui::cont *ui;
};

#endif // CONT_H
