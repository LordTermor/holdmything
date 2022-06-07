#pragma once

#include <QQuickItem>
#include <QAbstractListModel>
#include <QList>
#include <QFileInfo>

class QmlFileItem
{
    Q_GADGET
public:
    QmlFileItem(const QUrl& url);
    
    QUrl icon() const;
    QString name() const;
    QUrl url() const{return m_url;}
        
    QStringList keys()const{return m_keys;}
    void setKeys(const QStringList& keys){m_keys=keys;}
    
protected:
    QFileInfo info;
    QUrl m_url;
    QStringList m_keys;
};
