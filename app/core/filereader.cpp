#include "filereader.h"

FileReader::FileReader(QObject *parent) : QObject(parent)
{
    m_worker = new FileReaderWorker();
    m_worker->moveToThread(&m_workerThread);

    //Signals from thread
    connect(&m_workerThread, &QThread::finished, m_worker, &QObject::deleteLater);

    //Signals to worker
    connect(this, &FileReader::readFile, m_worker, &FileReaderWorker::readFile);

    //Signals from worker
    connect(m_worker, &FileReaderWorker::readFileStarted, this, &FileReader::readFileStarted);
    connect(m_worker, &FileReaderWorker::readFileFinished, this, &FileReader::readFileFinished);
    connect(m_worker, &FileReaderWorker::readFileProgressUpdated, this, &FileReader::readFileProgressUpdated);

    m_workerThread.start();
}

FileReader::~FileReader()
{
    m_workerThread.quit();
    m_workerThread.wait();
}
