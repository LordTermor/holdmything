#include "QmlFileItem.h"
#include <QUrl>
#include <QBuffer>
#include <QPixmap>
#include <QFileIconProvider>

static QFileIconProvider provider;

QUrl imageToUrl(const QPixmap& image)
{
    QByteArray byteArray;
    QBuffer buffer(&byteArray);
    buffer.open(QIODevice::WriteOnly);
    image.save(&buffer, "png");
    QString base64 = QString::fromUtf8(byteArray.toBase64());
    return QString("data:image/png;base64,") + base64;
}

QmlFileItem::QmlFileItem(const QUrl &url)
    :m_url(url), info(url.toString(QUrl::RemoveScheme))
{
  
}

QUrl QmlFileItem::icon() const
{
    return imageToUrl(provider.icon(info).pixmap({64,64}));
    
}

QString QmlFileItem::name() const
{
    return info.fileName();
}
