#include <algorithm>

#include "wordsparser.h"

WordsParser::WordsParser(QObject *parent) : QObject(parent)
{

}

/**
 * @brief Выполняет парсинг строки для подсчета слов в ней
 * @param wordsString - строка, содержащая слова
 */

void WordsParser::parseString(QString &wordsString)
{
    wordsString = wordsString.remove(QRegExp("[.,:;!?\\-\\[\\]\"\']")).toLower().simplified();

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

/**
 * @brief Загружает данные из multimap<int, QString> (количество вхождений - слово)
 * в QMultiMap<QString, int> (слово - количество вхождений) для сортировки слов в
 * алфавитном порядке
 */

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

/**
 * @brief Очищает данные класса
 */

void WordsParser::clear()
{
    m_wordsCountMap.clear();
    m_entriesMap.clear();
}

/**
 * @brief Возвращает данные о количестве вхождений слов в файле
 * @return Объект QMultiMap<QString, int>, ключ - слово, значение - количество вхождений
 */

const QMultiMap<QString, int> &WordsParser::getWordsEntries()
{
    return m_entriesMap;
}
