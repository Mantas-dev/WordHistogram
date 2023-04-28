#include "histogramlistmodel.h"

HistogramListModel::HistogramListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    m_roles[word] = "word";
    m_roles[count] = "count";

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
