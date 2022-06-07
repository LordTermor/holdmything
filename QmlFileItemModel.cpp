#include "QmlFileItemModel.h"

#include <QUrl>
#include <QStringList>
#include <QVariant>

void QmlFileItemModel::addItem(const QUrl &url, const QStringList& keys)
{
    beginInsertRows(QModelIndex(), 0, 0);
    
    QmlFileItem item(url);
    item.setKeys(keys);
    m_list.insert(0, item);
    
    endInsertRows();
}

void QmlFileItemModel::removeItem(const QUrl &url)
{
    auto it = std::find_if(m_list.begin(), m_list.end(), [url](const QmlFileItem& item){
        return item.url() == url;
    });
    
    auto index = std::distance(m_list.begin(), it);
    beginRemoveRows(QModelIndex(), index, index);
    
    m_list.removeAt(index);
    
    endRemoveRows();
    
}

int QmlFileItemModel::rowCount(const QModelIndex &parent) const
{
    return m_list.count();
}

QVariant QmlFileItemModel::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    
    switch(role){
    case Qt::UserRole+1:
        return m_list[row].name();
    case Qt::UserRole+2:
        return m_list[row].icon();
    case Qt::UserRole+3:
        return m_list[row].url();
    case Qt::UserRole+4:
        return m_list[row].keys();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> QmlFileItemModel::roleNames() const
{
    return {
        {Qt::UserRole+1, "name"},
        {Qt::UserRole+2, "icon"},
        {Qt::UserRole+3, "url"},
        {Qt::UserRole+4, "keys"}
    };
}
