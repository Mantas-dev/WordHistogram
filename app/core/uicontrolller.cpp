#include "uicontrolller.h"
#include <QUrl>
#include <QDir>

UIControlller::UIControlller(QObject *parent) : QObject(parent)
{
    update_readFileProccessing(false);
    update_readFileProgress(0);

    connect(&m_reader, &FileReader::readFileProgressUpdated,
            this, &UIControlller::update_readFileProgress);
    connect(&m_reader, &FileReader::readFileStarted,
            this, [&](){ update_readFileProccessing(true); });
    connect(&m_reader, &FileReader::readFileFinished,
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
    emit m_reader.readFile(m_filePath);
}
