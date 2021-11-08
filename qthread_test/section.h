#ifndef SECTION_H
#define SECTION_H

#include <QThread>
#include <QMutex>

class Section : public QObject
{
    Q_OBJECT

public:
    Section();
    ~Section();

    virtual void work();
    virtual void finish();

    void start();
    void stop();
    bool isRunning();
    QThread* getThread();

private:
    bool running;
    QThread *thread;
    QMutex mutex;

signals:
    void starting();
    void stopping();
    void timestamp(const QString&);

public slots:
    void run();
    void done();

};

#endif // SECTION_H
