#include <QLoggingCategory>

#include "filereadertask.h"

Q_LOGGING_CATEGORY(fileReaderTask, "FileReaderTask")

FileReaderTask::FileReaderTask()
    : m_stopReadFile(false), m_pauseReadFile(false)
{
}

FileReaderTask::~FileReaderTask()
{
    m_file.close();
    stopReadFile();
}

void FileReaderTask::run()
{
    if (!m_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCDebug(fileReaderTask) << "Failed to open file: " << m_file.fileName();
        return;
    }

    if (m_file.size() == 0) {
        qCDebug(fileReaderTask) << "File is empty: " << m_file.fileName();
        return;
    }

    qCDebug(fileReaderTask) << "Reading file was started";
    emit readFileStarted();

    while (!m_file.atEnd()) {
        if (m_stopReadFile.testAndSetAcquire(true, false)) {
            qCDebug(fileReaderTask) << "Reading file was stopped";
            m_file.close();
            emit readFileProgressUpdated(0);
            return;
        }
        if (m_pauseReadFile.testAndSetAcquire(true, true)) {
            continue;
        }

        QByteArray fileChunk = m_file.read(m_chunkSizeKb * 1024);
//        qCDebug(fileReaderTask) << "fileLine - " << fileChunk;
        emit readFileProgressUpdated((double) m_file.pos() / m_file.size());
    }

    m_file.close();

    qCDebug(fileReaderTask) << "Reading file was finished";
    emit readFileFinished();
}

void FileReaderTask::stopReadFile()
{
    qCDebug(fileReaderTask) << "Stop read file";
    m_stopReadFile.fetchAndStoreAcquire(true);
    m_pauseReadFile.fetchAndStoreAcquire(false);
}

void FileReaderTask::setFileName(const QString &fileName)
{
    m_file.setFileName(fileName);
}

void FileReaderTask::continueReadFile()
{
    qCDebug(fileReaderTask) << "Continue read file";
    m_pauseReadFile.fetchAndStoreAcquire(false);
}

void FileReaderTask::pauseReadFile()
{
    qCDebug(fileReaderTask) << "Pause read file";
    m_pauseReadFile.fetchAndStoreAcquire(true);
}
