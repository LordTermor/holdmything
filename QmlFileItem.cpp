#include "QmlFileItem.h"
#include <QUrl>
#include <libfm-qt6/core/thumbnailjob.h>
#include <QBuffer>

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
    :m_url(url)
{
    auto* gfile = g_file_new_for_path(url.toString(QUrl::RemoveScheme).toUtf8());
    GError* err = nullptr;
    Fm::GObjectPtr<GFileInfo> ginfo(g_file_query_info(gfile, "*", GFileQueryInfoFlags(), nullptr, &err));
    
    info = std::make_shared<Fm::FileInfo>(ginfo, Fm::FilePath(gfile, false));
}

QUrl QmlFileItem::icon() const
{
    return imageToUrl(info->icon()->qicon().pixmap({64,64}));
    
}

QString QmlFileItem::name() const
{
    return QString::fromStdString(info->name());
}
