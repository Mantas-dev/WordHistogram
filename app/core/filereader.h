#ifndef FILEREADER_H
#define FILEREADER_H

#include <QObject>
#include <QThread>

#include "filereaderworker.h"

class FileReader : public QObject
{
    Q_OBJECT

public:
    explicit FileReader(QObject *parent = nullptr);
    ~FileReader();

signals:
    void readFile(const QString &fileName);
    void readFileStarted();
    void readFileFinished();
    void readFileProgressUpdated(const double &progressValue);

private:
    QThread m_workerThread;
    FileReaderWorker *m_worker;
};

#endif // FILEREADER_H
