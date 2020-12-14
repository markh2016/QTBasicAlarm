#ifndef MTHREAD_H
#define MTHREAD_H

#include <QObject>
#include <QThread>
#include <QtCore>



class mThread : public QThread
{
    Q_OBJECT
public:
    explicit mThread(QObject *parent = nullptr);
    void run();
    bool stop=false ;
signals:
   void AlarmFired();

public slots:



};

#endif // MTHREAD_H
