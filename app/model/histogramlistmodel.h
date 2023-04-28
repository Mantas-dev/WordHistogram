#ifndef HISTOGRAMLISTMODEL_H
#define HISTOGRAMLISTMODEL_H

#include <QAbstractListModel>
#include <QMultiMap>

#include "app/macros/AutoPropertyHelpers.h"

struct HistogramItem {
    QString word;
    int count = 0;
};

class HistogramListModel : public QAbstractListModel
{
    Q_OBJECT

    READONLY_AUTO_PROPERTY(int, maxEntriesCount)

public:
    enum Roles {
        word = Qt::UserRole + 1,
        count
    };

    explicit HistogramListModel(QObject *parent = nullptr);

    virtual QVariant data(const QModelIndex &index,
                          int role = Qt::DisplayRole) const override;
    virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    virtual QHash<int,QByteArray> roleNames() const override;

    void loadData(const QMultiMap<QString, int> &dataMap);
    void resetModel();

private:
    QList<HistogramItem> m_items;
    QHash<int, QByteArray> m_roles;

};

#endif // HISTOGRAMLISTMODEL_H
