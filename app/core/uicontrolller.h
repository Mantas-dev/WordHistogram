#ifndef UICONTROLLLER_H
#define UICONTROLLLER_H

#include <QObject>

#include "filereader.h"
#include "app/macros/AutoPropertyHelpers.h"

class UIControlller : public QObject
{
    Q_OBJECT

    READONLY_AUTO_PROPERTY(double, readFileProgress)
    READONLY_AUTO_PROPERTY(bool, readFileProccessing)

public:
    explicit UIControlller(QObject *parent = nullptr);

public slots:
    void loadFile(const QString &fileUrl);
    void readFile();

private:
    FileReader m_reader;
    QString m_filePath;

};

#endif // UICONTROLLLER_H
