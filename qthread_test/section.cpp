#include "section.h"
#include "mainwindow.h"

Section::Section()
{
    thread = new QThread();
    moveToThread(thread);

    connect(this, SIGNAL(starting()), thread, SLOT(start()));
    connect(this, SIGNAL(stopping()), thread, SLOT(quit()));
    connect(thread, SIGNAL(started()), this, SLOT(run()));
    connect(thread, SIGNAL(finished()), this, SLOT(done()));

    running = false;
}

void Section::work()
{

}

void Section::finish()
{

}

QThread* Section::getThread()
{
    return thread;
}

Section::~Section()
{
    if (running)
        stop();
    thread->wait();
    delete this;
}

void Section::run()
{
    while (running) {
        work();
    }
    //emit stopping();
    thread->quit();
}

void Section::start()
{
    mutex.lock();
    running = true;
    mutex.unlock();
    //emit starting();
    thread->start();
}

void Section::stop()
{
    mutex.lock();
    running = false;
    mutex.unlock();
}

void Section::done()
{
    std::cout << "Section::done" << std::endl;
    finish();
}

bool Section::isRunning()
{
    return running;
}
