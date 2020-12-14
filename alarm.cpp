#include "alarm.h"
#include "ui_alarm.h"

#include <QMessageBox>

Alarm::Alarm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Alarm)
{

    ui->setupUi(this);

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width()-this->width()) / 2;
    int y = (screenGeometry.height()-this->height()) / 2;
    this->move(x,y);

    QTimer *timer = new QTimer(this);



    // set  up signals and slots

    connect(timer, &QTimer::timeout, this, &Alarm::showTime);
    connect(ui->btnSetAlarm, &QPushButton::clicked, this, &Alarm::setalarmtime);
    connect(ui->btnEnableAlarm,&QPushButton::clicked,this,&Alarm::setAlarmStatus);
    connect(ui->btnStopAlarm,&QPushButton::clicked,this,&Alarm::on_btnStopAlarm_clicked);


    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");

    ui->timeLCD->display(text);

    QTime alarmtime = QTime::currentTime();
    text2 = alarmtime.toString("hh:mm");

    ui->alarmLCD->display(text2);
    m_thread = new mThread(this);

    // connect the thread
    connect(m_thread, &mThread::AlarmFired,this,&Alarm::soundAlarm) ;


    timer->start(1000);




}

Alarm::~Alarm()
{
    delete ui;
}

void Alarm::  showTime(){

    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
    {
        text[2] = ' ';
        if(flag==true){
         alarm_time[2]  = ' ';

        }
    }
    else
    {
       alarm_time[2]  = ':';

    }


     if(flag==true){
     alarm_time = hours + alarm_time[2] + minutes ;

     ui->alarmLCD->display(alarm_time);
     updateAlarm();

     }


    ui->timeLCD->display(text);



}
void Alarm:: updateAlarm()
{
 QTime time = QTime::currentTime();
 QString _now = time.toString("hh:mm");

 if((_now == alarm_time)&&(flag== true))
 {




    if(f_fired==false){
    m_thread->start() ;
    f_fired= true ;
    }


 }


}

void Alarm::setalarmtime(){

// get the int value from the spingbox


int ihours = ui->spinBoxHrs->value() ;
int iminutes =ui->spinBoxMinutes->value() ;

 if (ihours<10)
 {
   hours = "0"+ QString::number(ihours);
 }

 else
 {
    hours=QString::number(ihours);

 }

 if(iminutes <10 )
 {
   minutes ="0"+ QString::number(iminutes);

 }
 else
 {
    minutes = QString::number(iminutes);
 }


    alarm_time = hours + ':' + minutes ;




ui->alarmLCD->display(alarm_time);
isSetFlag = true ;

}

void Alarm::setAlarmStatus()
{
   if(isSetFlag){

    QString labeltext = ui->lblalarmstatus->text();

    if(labeltext=="Alarm Switched Off")
    {

    ui->lblalarmstatus->setText("Alarm Switched On");
    QPalette *p = new QPalette;  // change lcd color

    p->setColor(QPalette::WindowText, QColor(255, 0, 0));
    ui->lblalarmstatus->setPalette(*p);
    flag = true ;
    }


    if(labeltext=="Alarm Switched On")
    {

    ui->lblalarmstatus->setText("Alarm Switched Off");
    QPalette *p = new QPalette;  // change lcd color

    p->setColor(QPalette::WindowText, QColor(0, 0, 255));
    ui->lblalarmstatus->setPalette(*p);
    alarm_time = hours + ':' + minutes ;
    ui->alarmLCD->display(alarm_time);
    flag = false ;
    }

 }
   else
   {


       QMessageBox *msgBox = new QMessageBox(this);
       msgBox->setText("You havent set an alarm time ");
       msgBox->exec();



   }


}



void Alarm::on_btnStopAlarm_clicked()
{
 alarm_time ="00:00" ;
 ui->lblalarmstatus->setText("Alarm Switched Off");
 QPalette *p = new QPalette;  // change lcd color

 p->setColor(QPalette::WindowText, QColor(0, 0, 255));
 ui->lblalarmstatus->setPalette(*p);
 ui->alarmLCD->display(alarm_time);
 flag =false ;
 isSetFlag =false ;
 m_thread->stop= true ;
 f_fired= false ;

}

void Alarm::soundAlarm(){

    QSound::play(":/bells.wav");
}
