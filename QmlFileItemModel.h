#pragma once

#include <QAbstractListModel>

#include <QmlFileItem.h>

class QmlFileItemModel: public QAbstractListModel {
    Q_OBJECT
public:
    Q_INVOKABLE void addItem(const QUrl&, const QStringList& keys = QStringList());
    Q_INVOKABLE void removeItem(const QUrl&);
    
protected:
    QList<QmlFileItem> m_list;
    
    // QAbstractItemModel interface
public:
    virtual int rowCount(const QModelIndex &parent) const override;
    virtual QVariant data(const QModelIndex &index, int role) const override;
    virtual QHash<int, QByteArray> roleNames() const override;    
};
