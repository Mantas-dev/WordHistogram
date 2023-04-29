#ifndef FILEREADERTASK_H
#define FILEREADERTASK_H

#include <QObject>
#include <QRunnable>
#include <QFile>
#include <QAtomicInt>

#include "app/core/wordsparser.h"

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
    const QMultiMap<QString, int>& getWordsEntries();

signals:
    void readFileStarted();
    void readFileFinished();
    void readFileProgressUpdated(const double &progressValue);
    void wordEntriesUpdated();

private:
    QFile m_file;
    QAtomicInt m_stopReadFile, m_pauseReadFile;
    WordsParser m_wordsParser;
};

#endif // FILEREADERTASK_H
