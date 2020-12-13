#ifndef ALARM_H
#define ALARM_H

#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QRect>
#include <QDesktopWidget>
#include <QDebug>
#include <QScreen>

QT_BEGIN_NAMESPACE
namespace Ui { class Alarm; }
QT_END_NAMESPACE

class Alarm : public QWidget
{
    Q_OBJECT

public:
    Alarm(QWidget *parent = nullptr);
    ~Alarm();

    // variables global

    QString text2 ;
    QString alarm_time  ;
    QString minutes ="00";
    QString hours ="00";
    bool flag = false;
    bool isSetFlag = false ;

private slots:
    void showTime();
    void updateAlarm();
    void setalarmtime();
    void setAlarmStatus();
    void on_btnStopAlarm_clicked();

private:
    Ui::Alarm *ui;
};
#endif // ALARM_H
