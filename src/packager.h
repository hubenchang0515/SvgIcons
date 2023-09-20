#ifndef PACKAGER_H
#define PACKAGER_H

#include <zip.h>
#include <QObject>

namespace SvgIcon
{

class Packager : public QObject
{
    Q_OBJECT
public:
    Packager(QObject* parent=nullptr) noexcept;
    ~Packager() noexcept;

    bool open() noexcept;
    void close() noexcept;
    bool addFile(const QString& filename, const QByteArray& data) noexcept;
    QByteArray data() noexcept;

private:
    zip_source_t* m_source;
    zip_t* m_zip;
};

} // namespace SvgIcon


#endif // PACKAGER_H