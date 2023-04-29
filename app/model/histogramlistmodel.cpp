#include "histogramlistmodel.h"

HistogramListModel::HistogramListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_roles[word] = "word";
    m_roles[count] = "count";
    m_roles[itemColor] = "itemColor";

    m_colors.append("#ff6400");
    m_colors.append("#4169e1");
    m_colors.append("#ff69b4");
    m_colors.append("#00c37f");
    m_colors.append("#94faff");
    m_colors.append("#db0482");
    m_colors.append("#ffff3c");
    m_colors.append("#d186ff");
    m_colors.append("#f62b80");
    m_colors.append("#ff9da5");
    m_colors.append("#9370db");
    m_colors.append("#dc143c");
    m_colors.append("#00926c");
    m_colors.append("#ffd700");
    m_colors.append("#00e583");

    update_maxEntriesCount(0);
}

QVariant HistogramListModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > m_items.size())
        return QVariant();

    QVariant ret = QVariant();

    switch (role) {
    case word:
        ret = m_items.at(index.row()).word;
        break;
    case count:
        ret = m_items.at(index.row()).count;
        break;
    case itemColor:
        ret = m_colors.at(index.row());
        break;
    }

    return ret;
}

int HistogramListModel::rowCount(const QModelIndex &parent) const
{
    return m_items.size();
}

QHash<int, QByteArray> HistogramListModel::roleNames() const
{
    return m_roles;
}

void HistogramListModel::loadData(const QMultiMap<QString, int> &dataMap)
{
    beginResetModel();
    m_items.clear();

    for (const auto &key : dataMap.keys()) {
        HistogramItem item;
        item.word = key;
        item.count = dataMap.value(key);
        update_maxEntriesCount(qMax(get_maxEntriesCount(), item.count));
        m_items.append(item);
    }

    endResetModel();
}

void HistogramListModel::resetModel()
{
    beginResetModel();
    m_items.clear();
    update_maxEntriesCount(0);
    endResetModel();
}
