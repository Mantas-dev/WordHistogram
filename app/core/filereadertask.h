#ifndef FILEREADERTASK_H
#define FILEREADERTASK_H

#include <QObject>
#include <QRunnable>
#include <QFile>
#include <QAtomicInt>

class FileReaderTask : public QObject, public QRunnable
{
    Q_OBJECT

public:
    explicit FileReaderTask();
    ~FileReaderTask();

    virtual void run() override;
    void stopReadFile();
    void setFileName(const QString &fileName);
    void continueReadFile();
    void pauseReadFile();

signals:
    void readFileStarted();
    void readFileFinished();
    void readFileProgressUpdated(const double &progressValue);

private:
    QFile m_file;
    QAtomicInt m_stopReadFile, m_pauseReadFile;

    quint64 m_chunkSizeKb = 1000;
};

#endif // FILEREADERTASK_H
