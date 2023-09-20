#include "packager.h"
#include <QDebug>

namespace SvgIcon
{

Packager::Packager(QObject* parent) noexcept:
    QObject{parent},
    m_source{nullptr},
    m_zip{nullptr}
{
    
}

Packager::~Packager() noexcept
{
    close();
}

bool Packager::open() noexcept
{
    close();
    zip_error_t error;
    zip_error_init(&error);
    
    m_source = zip_source_buffer_create(nullptr, 0, 0, &error);
    if (m_source == nullptr)
    {
        qDebug() << zip_error_strerror(&error);
        return false;
    }

    m_zip = zip_open_from_source(m_source, ZIP_CREATE, &error);
    if (m_zip == nullptr)
    {
        qDebug() << zip_error_strerror(&error);
        return false;
    }
    zip_source_keep(m_source);

    return true;
}


void Packager::close() noexcept
{
    if (m_zip != nullptr)
    {
        zip_close(m_zip);
        m_zip = nullptr;
    }

    if (m_source != nullptr)
    {
        zip_source_free(m_source);
        m_source = nullptr;
    }
}

bool Packager::addFile(const QString& filename, const QByteArray& data) noexcept
{
    if (m_zip == nullptr)
        return false;

    zip_error_t error;
    zip_error_init(&error);

    zip_source_t* source = zip_source_buffer(m_zip, data.data(), data.size(), 0);
    if (source == nullptr)
    {
        qDebug() << zip_error_strerror(&error);
        return false;
    }

    if (zip_file_add(m_zip, filename.toStdString().c_str(), source, ZIP_FL_ENC_UTF_8) < 0)
    {
        qDebug() << zip_error_strerror(zip_get_error(m_zip));
        return false;
    }
    return true;
}

QByteArray Packager::data() noexcept
{
    if (m_source == nullptr)
        return {};

    // zip_source_commit_write(m_source);
    zip_close(m_zip);

    zip_stat_t stat;
    zip_source_open(m_source);
    zip_source_stat(m_source, &stat);

    QByteArray buffer{static_cast<int>(stat.size), '\0'};
    zip_source_read(m_source, buffer.data(), stat.size);
    zip_source_close(m_source);

    m_zip = zip_open_from_source(m_source, ZIP_CREATE, nullptr);
    zip_source_keep(m_source);

    return buffer;
}

} // namespace SvgIcon