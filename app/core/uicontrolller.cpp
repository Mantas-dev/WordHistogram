#include "uicontrolller.h"
#include <QUrl>
#include <QDir>
#include <QThreadPool>

UIControlller::UIControlller(QObject *parent) : QObject(parent)
{
    m_fileReaderTask.reset(new FileReaderTask());
    m_fileReaderTask->setAutoDelete(false);

    update_readFileProccessing(false);
    update_readFilePaused(false);
    update_readFileProgress(0);

    connect(m_fileReaderTask.get(), &FileReaderTask::readFileProgressUpdated,
            this, &UIControlller::update_readFileProgress);
    connect(m_fileReaderTask.get(), &FileReaderTask::readFileStarted,
            this, [&](){ update_readFileProccessing(true); });
    connect(m_fileReaderTask.get(), &FileReaderTask::readFileFinished,
            this, [&](){ update_readFileProccessing(false); });
}

void UIControlller::loadFile(const QString &fileUrl)
{
    const QUrl url(fileUrl);

    m_filePath = fileUrl;

    if (url.isLocalFile())
        m_filePath = QDir::toNativeSeparators(url.toLocalFile());

    update_readFileProccessing(false);
}

void UIControlller::readFile()
{
    m_fileReaderTask->setFileName(m_filePath);
    QThreadPool::globalInstance()->start(m_fileReaderTask.get());
}

void UIControlller::pauseReadFile()
{
    update_readFilePaused(true);
    m_fileReaderTask->pauseReadFile();
}

void UIControlller::continueReadFile()
{
    update_readFilePaused(false);
    m_fileReaderTask->continueReadFile();
}

void UIControlller::stopReadFile()
{
    m_fileReaderTask->stopReadFile();
    update_readFilePaused(false);
    update_readFileProccessing(false);
}
