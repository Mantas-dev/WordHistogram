#ifndef UICONTROLLLER_H
#define UICONTROLLLER_H

#include <QObject>
#include <QSharedPointer>

#include "app/core/filereadertask.h"
#include "app/macros/AutoPropertyHelpers.h"
#include "app/model/histogramlistmodel.h"

class UIControlller : public QObject
{
    Q_OBJECT

    READONLY_AUTO_PROPERTY(double, readFileProgress)
    READONLY_AUTO_PROPERTY(bool, readFileProccessing)
    READONLY_AUTO_PROPERTY(bool, readFilePaused)
    CONSTANT_AUTO_PROPERTY(HistogramListModel *, histogramModel)

public:
    explicit UIControlller(QObject *parent = nullptr);

public slots:
    void loadFile(const QString &fileUrl);
    void readFile();
    void pauseReadFile();
    void continueReadFile();
    void stopReadFile();

private:
    QSharedPointer<FileReaderTask> m_fileReaderTask;
    QString m_filePath;

};

#endif // UICONTROLLLER_H
