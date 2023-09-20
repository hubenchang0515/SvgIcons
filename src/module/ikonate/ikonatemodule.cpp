#include "ikonatemodule.h"

#include <QFileInfo>
#include <QDirIterator>
#include <QFile>
#include <QByteArray>
#include <QDomDocument>
#include <QDebug>

static inline void initResource()
{
    Q_INIT_RESOURCE(ikonate);
}

namespace SvgIcon
{

IkonateModule::IkonateModule() noexcept:
    m_groupBox{new QGroupBox(tr("Configure"))},
    m_layout{new QGridLayout},
    m_lineWidthLabel{new QLabel(tr("Line Width"))},
    m_lineWidthSpinBox{new QSpinBox},
    m_iconSizeLabel{new QLabel(tr("Icon Size"))},
    m_iconSizeSpinBox{new QSpinBox},
    m_lineCapLabel{new QLabel(tr("Line Cap"))},
    m_lineCapComboBox{new QComboBox},
    m_lineJoinLabel{new QLabel(tr("Line Join"))},
    m_lineJoinComboBox{new QComboBox},
    m_colorLabel{new QLabel(tr("Color"))},
    m_colorEdit{new QLineEdit("#000000")}
{
    initResource();

    m_lineWidthSpinBox->setRange(1, 10);
    m_lineWidthSpinBox->setValue(2);

    m_iconSizeSpinBox->setRange(1, 256);
    m_iconSizeSpinBox->setValue(24);

    m_lineCapComboBox->addItems({tr("square"), tr("round"), tr("butt")});
    m_lineJoinComboBox->addItems({tr("miter"), tr("round"), tr("bevel")});

    m_layout->addWidget(m_lineWidthLabel, 0, 0);
    m_layout->addWidget(m_lineWidthSpinBox, 0, 1);
    m_layout->addWidget(m_iconSizeLabel, 1, 0);
    m_layout->addWidget(m_iconSizeSpinBox, 1, 1);
    m_layout->addWidget(m_lineCapLabel, 2, 0);
    m_layout->addWidget(m_lineCapComboBox, 2, 1);
    m_layout->addWidget(m_lineJoinLabel, 3, 0);
    m_layout->addWidget(m_lineJoinComboBox, 3, 1);
    m_layout->addWidget(m_colorLabel, 4, 0);
    m_layout->addWidget(m_colorEdit, 4, 1);
    m_groupBox->setLayout(m_layout);

    connect(m_lineWidthSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &IkonateModule::notify);
    connect(m_iconSizeSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &IkonateModule::notify);
    connect(m_lineCapComboBox, &QComboBox::currentTextChanged, this, &IkonateModule::notify);
    connect(m_lineJoinComboBox, &QComboBox::currentTextChanged, this, &IkonateModule::notify);
    connect(m_colorEdit, &QLineEdit::textChanged, this, &IkonateModule::notify);
}

IkonateModule::~IkonateModule() noexcept
{
    // delete m_groupBox;
}

QString IkonateModule::name() const noexcept
{
    return "ikonate";
}

QWidget* IkonateModule::configWidget() const noexcept
{
    return dynamic_cast<QWidget*>(m_groupBox);
}

QMap<QString, QByteArray> IkonateModule::icons() const noexcept
{
    const QString dirPaht = ":/ikonate/svg";
    QMap<QString, QByteArray> iconMap;
    QDirIterator iter(dirPaht);
    while(iter.hasNext())
    {
        QFileInfo info(iter.next());
        iconMap[info.baseName()] = getIcon(info.filePath(), 
                                            m_lineWidthSpinBox->value(), 
                                            m_iconSizeSpinBox->value(), 
                                            m_lineCapComboBox->currentText(),
                                            m_lineJoinComboBox->currentText(),
                                            m_colorEdit->text());
    }
    return iconMap;
}

/************************************
 * @brief get SVG icons
 * @return icons
 ************************************/
int IkonateModule::iconSize() const noexcept
{
    return m_iconSizeSpinBox->text().toInt();
}

QByteArray IkonateModule::getIcon(const QString& path,
                                int lineWidth,
                                int iconSize,
                                const QString& lineCap,
                                const QString& lineJoin,
                                const QString& color) const noexcept
{
    QFile file{path};
    file.open(QFile::ReadOnly);
    QByteArray data = file.readAll();

    QDomDocument dom;
    dom.setContent(data);
    dom.documentElement().setAttribute("width", QString("%1px").arg(iconSize));
    dom.documentElement().setAttribute("height", QString("%1px").arg(iconSize));
    dom.documentElement().setAttribute("stroke-width", lineWidth);
    dom.documentElement().setAttribute("stroke-linecap", lineCap);
    dom.documentElement().setAttribute("stroke-linejoin", lineJoin);
    dom.documentElement().setAttribute("stroke", color);
    return dom.toByteArray();
}

} // namespace SvgIcon