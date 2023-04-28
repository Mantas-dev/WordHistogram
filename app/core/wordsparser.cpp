#include <algorithm>

#include "wordsparser.h"

WordsParser::WordsParser(QObject *parent) : QObject(parent)
{

}

void WordsParser::parseString(QString &wordsString)
{
    wordsString = wordsString.remove(QRegExp("[.,:;!?\"\']")).toLower().simplified();

    for (const auto &word : wordsString.split(' ', Qt::SkipEmptyParts)) {

        auto it = find_if(m_wordsCountMap.begin(), m_wordsCountMap.end(),
                          [word](pair<int, QString> mapPair) -> bool
        {
            return mapPair.second == word;
        });

        if (it != m_wordsCountMap.end()) {
            int newCount = it->first + 1;
            m_wordsCountMap.erase(it);
            m_wordsCountMap.insert(make_pair(newCount, word));
        } else
            m_wordsCountMap.insert(make_pair(1, word));
    }
}

void WordsParser::loadParsedData()
{
    if (m_wordsCountMap.empty())
        return;

    m_entriesMap.clear();

    auto it = m_wordsCountMap.rbegin();

    for (int i = 0; i < 15 && it != m_wordsCountMap.rend(); i++, ++it)
        m_entriesMap.insert(it->second, it->first);

    emit wordEntriesUpdated();
}

void WordsParser::clear()
{
    m_wordsCountMap.clear();
    m_entriesMap.clear();
}

const QMultiMap<QString, int> &WordsParser::getWordsEntries()
{
    return m_entriesMap;
}
