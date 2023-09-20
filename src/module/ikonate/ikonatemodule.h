#ifndef IKONATE_MODULE_H
#define IKONATE_MODULE_H

#include "../abstractmodule.h"

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QSpinBox>
#include <QComboBox>
#include <QLineEdit>
#include <QGroupBox>

namespace SvgIcon
{

class IkonateModule : public AbstractModule
{
    Q_OBJECT
public:
    IkonateModule() noexcept;
    virtual ~IkonateModule() noexcept override;

    /************************************
     * @brief get module name
     * @return module name
     ************************************/
    virtual QString name() const noexcept override;

    /************************************
     * @brief get config widget
     * @return config widget
     ************************************/
    virtual QWidget* configWidget() const noexcept override;

    /************************************
     * @brief get SVG icons
     * @return icons
     ************************************/
    virtual QMap<QString, QByteArray> icons() const noexcept override;

    /************************************
     * @brief get SVG icons
     * @return icons
     ************************************/
    virtual int iconSize() const noexcept override;

private:
    QGroupBox* m_groupBox;
    QGridLayout* m_layout;
    QLabel* m_lineWidthLabel;
    QSpinBox* m_lineWidthSpinBox;
    QLabel* m_iconSizeLabel;
    QSpinBox* m_iconSizeSpinBox;
    QLabel* m_lineCapLabel;
    QComboBox* m_lineCapComboBox;
    QLabel* m_lineJoinLabel;
    QComboBox* m_lineJoinComboBox;
    QLabel* m_colorLabel;
    QLineEdit* m_colorEdit;

    QByteArray getIcon(const QString& path,
                    int lineWidth,
                    int iconSize,
                    const QString& lineCap,
                    const QString& lineJoin,
                    const QString& color) const noexcept;
};
    
} // namespace SvgIcon

#endif // IKONATE_MODULE_H