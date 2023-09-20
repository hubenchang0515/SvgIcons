#ifndef ABSTRACTMODULE_H
#define ABSTRACTMODULE_H

#include <QString>
#include <QWidget>
#include <QMap>
#include <QPixmap>

namespace SvgIcon
{

class AbstractModule: public QObject
{
    Q_OBJECT
public:
    AbstractModule() noexcept = default;
    virtual ~AbstractModule() noexcept = default;

    /************************************
     * @brief get module name
     * @return module name
     ************************************/
    virtual QString name() const noexcept = 0;

    /************************************
     * @brief get config widget
     * @return config widget
     ************************************/
    virtual QWidget* configWidget() const noexcept = 0;

    /************************************
     * @brief get SVG icons
     * @return icons
     ************************************/
    virtual QMap<QString, QByteArray> icons() const noexcept = 0;

    /************************************
     * @brief get SVG icons
     * @return icons
     ************************************/
    virtual int iconSize() const noexcept = 0;

    virtual void notify() const noexcept final
    {
        emit changed();
    } ;

signals:
    void changed() const;
};
    
} // namespace SvgIcon


#endif // ABSTRACTMODULE_H