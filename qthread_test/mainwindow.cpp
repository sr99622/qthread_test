#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    btnStart = new QPushButton("start");
    connect(btnStart, SIGNAL(clicked()), this, SLOT(start()));
    btnStart->setMaximumWidth(100);

    QWidget *panel = new QWidget();
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(btnStart,       0, 0, 1, 1);
    panel->setLayout(layout);
    setCentralWidget(panel);

    nessy = new Runner(this);
    yeti = new Runner(this);
    kraken = new Runner(this);

}

void MainWindow::loop()
{
    auto start = std::chrono::high_resolution_clock::now();
    int count = 0;
    while(count < 100) {
        count++;

        unsigned long width = 1920;
        unsigned long height = 1080;
        unsigned long channels = 3;

        uint8_t *buffer = (uint8_t*)malloc(width * height * channels);
        srand(time(0));

        for (unsigned long y = 0; y < height; y++) {
            for (unsigned long x = 0; x < width; x++) {
                for (unsigned long z = 0; z < channels; z++) {
                    unsigned long i = y * width + x * channels + z;
                    uint8_t sample = (uint8_t)(rand() % 255);
                    buffer[i] = sample;
                }
            }
        }

        free(buffer);

        QString stamp = QDateTime::currentDateTime().toString("ddd MMMM d yy hh:mm:ss.zzz");
        std::cout << "count: " << count << " thread_id: " << QThread::currentThreadId() << " - " << stamp.toStdString() << std::endl;
    }
    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
    std::cout << "THREAD ELAPSED TIME: " << elapsed << std::endl;
}

bool MainWindow::isFinished()
{
    bool result = false;
    result = nessy->finished && yeti->finished && kraken->finished;
    return result;
}

void MainWindow::start()
{
    std::cout << "MainWindow::start" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    nessy->finished = false;
    QThreadPool::globalInstance()->tryStart(nessy);
    yeti->finished = false;
    QThreadPool::globalInstance()->tryStart(yeti);
    kraken->finished = false;
    QThreadPool::globalInstance()->tryStart(kraken);

    while (!isFinished()) {
        QThread::msleep(1);
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();

    std::cout << "END OF PARALLEL EXECUTION elapsed time: " << elapsed << std::endl;
}

MainWindow::~MainWindow()
{
}

Runner::Runner(QMainWindow *parent)
{
    mainWindow = parent;
    setAutoDelete(false);
}

void Runner::run()
{
    ((MainWindow*)mainWindow)->loop();
    finished = true;
}
