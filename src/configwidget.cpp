#include "configwidget.h"
#include "module/ikonate/ikonatemodule.h"

#include <QSpacerItem>
#include <QFile>
#include <QFileDialog>
#include <QDebug>

namespace SvgIcon
{

ConfigWidget::ConfigWidget(QWidget* parent) noexcept:
    m_layout{new QGridLayout},
    m_moduleLabel{new QLabel(tr("Module:"))},
    m_moduleComboBox{new QComboBox},
    m_moduleConfigWidget{new QWidget},
    m_exportButton{new QPushButton(tr("Export"))},
    m_moduleStack{new QStackedLayout},
    m_packager{new Packager{this}}
    
{
    m_moduleConfigWidget->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_moduleConfigWidget->setLayout(m_moduleStack);

    m_layout->addWidget(m_moduleLabel, 0, 0);
    m_layout->addWidget(m_moduleComboBox, 0, 1);
    m_layout->addWidget(m_moduleConfigWidget, 1, 0, 1, 2);
    m_layout->addItem(new QSpacerItem{0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding}, 2, 0, 1, 2);
    m_layout->addWidget(m_exportButton, 3, 0, 1, 2);
    setLayout(m_layout);

    connect(m_exportButton, &QPushButton::clicked, this, &ConfigWidget::exportPackage);

    addModule(new IkonateModule);
}

ConfigWidget::~ConfigWidget() noexcept
{
    for (AbstractModule* module : m_modules)
    {
        delete module;
    }
}

void ConfigWidget::addModule(AbstractModule* module) noexcept
{
    m_moduleComboBox->addItem(module->name());
    m_moduleStack->addWidget(module->configWidget());
    module->configWidget()->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
    m_modules[module->name()] = module;

    connect(module, &AbstractModule::changed, this, &ConfigWidget::changed);
}


bool ConfigWidget::setCurrentModule(const QString& name) noexcept
{
    if (!m_modules.contains(name))
        return false;

    m_moduleStack->setCurrentWidget(m_modules[name]->configWidget());
    return true;
}

AbstractModule* ConfigWidget::currentModule() const noexcept
{
    return m_modules[m_moduleComboBox->currentText()];
}

void ConfigWidget::exportPackage() const noexcept
{
    m_packager->open();

    QMapIterator<QString, QByteArray> iter{currentModule()->icons()};
    while (iter.hasNext())
    {
        iter.next();
        m_packager->addFile(QString("%1.svg").arg(iter.key()), iter.value());
    }

    QFileDialog::saveFileContent(m_packager->data(), "icons.zip");
}

} // namespace SvgIcon
