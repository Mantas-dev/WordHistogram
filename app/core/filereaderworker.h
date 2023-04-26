#ifndef FILEREADERWORKER_H
#define FILEREADERWORKER_H

#include <QObject>

class FileReaderWorker : public QObject
{
    Q_OBJECT

public slots:
    void readFile(const QString &fileName);

signals:
    void readFileStarted();
    void readFileFinished();
    void readFileProgressUpdated(const double &progressValue);

};

#endif // FILEREADERWORKER_H
