#include <QLoggingCategory>

#include "filereadertask.h"

Q_LOGGING_CATEGORY(fileReaderTask, "FileReaderTask")

FileReaderTask::FileReaderTask()
    : m_stopReadFile(false), m_pauseReadFile(false)
{
    connect(&m_wordsParser, &WordsParser::wordEntriesUpdated,
            this, &FileReaderTask::wordEntriesUpdated);
}

FileReaderTask::~FileReaderTask()
{
    m_file.close();
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

    int lineCounter = 0, linesChunk = 30;
    bool parsedDataLoaded;

    m_wordsParser.clear();

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

        parsedDataLoaded = false;
        QString fileLine = m_file.readLine();

        m_wordsParser.parseString(fileLine);
        emit readFileProgressUpdated((double) m_file.pos() / m_file.size());

        //Уменьшает количество вызовов загрузок
        //для более плавного обновления гистограммы
        if (lineCounter % linesChunk == 0) {
            m_wordsParser.loadParsedData();
            parsedDataLoaded = true;
        }

        lineCounter++;
    }

    m_file.close();

    if (!parsedDataLoaded)
        m_wordsParser.loadParsedData();

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

const QMultiMap<QString, int> &FileReaderTask::getWordsEntries()
{
    return m_wordsParser.getWordsEntries();
}
