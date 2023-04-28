#ifndef WORDSPARSER_H
#define WORDSPARSER_H

#include <QObject>
#include <QMultiMap>
#include <map>

using namespace std;

class WordsParser : public QObject
{
    Q_OBJECT
public:
    explicit WordsParser(QObject *parent = nullptr);

    void parseString(QString &wordsString);
    void loadParsedData();
    void clear();
    const QMultiMap<QString, int>& getWordsEntries();

signals:
    void wordEntriesUpdated();

private:
    multimap<int, QString> m_wordsCountMap;
    QMultiMap<QString, int> m_entriesMap;
};

#endif // WORDSPARSER_H
