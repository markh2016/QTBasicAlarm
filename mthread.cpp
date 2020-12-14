#include "mthread.h"

mThread::mThread(QObject *parent) :QThread(parent)
{

}

void mThread::run()
{
        QMutex mutex ;



        for(int i =0 ;i < 100 ;i++){

        mutex.lock() ;
        if (this->stop)
            break ;
        mutex.unlock();
        emit this->AlarmFired() ;
        this->sleep(10);
        }







}
