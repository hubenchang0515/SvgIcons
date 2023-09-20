#ifndef CONFIG_WIDGET_H
#define CONFIG_WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QMap>
#include <QString>
#include <QLayout>
#include <QStackedLayout>

#include "module/abstractmodule.h"
#include "packager.h"

namespace SvgIcon
{

class ConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigWidget(QWidget* parent=nullptr) noexcept;
    ~ConfigWidget() noexcept;
    
    void addModule(AbstractModule* module) noexcept;
    bool setCurrentModule(const QString& name) noexcept;

    AbstractModule* currentModule() const noexcept;

    void exportPackage() const noexcept;

signals:
    void changed();

private:
    QGridLayout* m_layout;
    QLabel* m_moduleLabel;
    QComboBox* m_moduleComboBox;
    QWidget* m_moduleConfigWidget;
    QPushButton* m_exportButton;

    QStackedLayout* m_moduleStack;
    QMap<QString, AbstractModule*> m_modules;

    Packager* m_packager;
};
    
} // namespace SvgIcon


#endif // CONFIG_WIDGET_H