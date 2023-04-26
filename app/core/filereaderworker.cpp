#include <QFile>
#include <QLoggingCategory>

#include "filereaderworker.h"

Q_LOGGING_CATEGORY(fileReaderWorker, "FileReader.Worker")

void FileReaderWorker::readFile(const QString &fileName)
{
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCDebug(fileReaderWorker) << "Failed to open file: " << fileName;
        return;
    }

    if (file.size() == 0) {
        qCDebug(fileReaderWorker) << "File is empty: " << fileName;
        return;
    }

    emit readFileStarted();

    while (!file.atEnd()) {
        QByteArray fileLine = file.readLine();
        emit readFileProgressUpdated((double) file.pos() / file.size());
    }

    emit readFileFinished();
}
