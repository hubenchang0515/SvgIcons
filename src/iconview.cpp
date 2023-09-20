#include "iconview.h"

#include <QSvgWidget>
#include <QDebug>

namespace SvgIcon
{

IconView::IconView(QWidget* parent) noexcept:
    m_vbox{new QVBoxLayout},
    m_grid{new QGridLayout},
    m_columns{0}
{
    m_grid->setSpacing(10);
    m_vbox->setSpacing(10);
    m_vbox->addLayout(m_grid);
    m_vbox->addSpacerItem(new QSpacerItem{0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding});
    setLayout(m_vbox);
}

IconView::~IconView() noexcept
{

}

int IconView::columns() const noexcept
{
    return m_columns;
}

void IconView::setColumns(int n) noexcept
{
    m_columns = n;
}


void IconView::clear() const noexcept
{
    while (m_grid->count() > 0)
    {
        auto item = m_grid->takeAt(0);
        delete item->widget();
        delete item;
    }
}

void IconView::setIcons(const QMap<QString, QByteArray>& icons, int width) noexcept
{
    clear();
    QMargins margins = m_vbox->contentsMargins();

    int row=0;
    int col=0;
    for (auto iter = icons.begin(); iter != icons.end(); ++iter)
    {
        QSvgWidget* label = new QSvgWidget;
        label->load(iter.value());
        label->setFixedSize(label->sizeHint());
        int rowWidth = label->sizeHint().width() * (col + 1)
                        + m_grid->horizontalSpacing() * col
                        + margins.left() 
                        + margins.right();

        if (rowWidth >= width)
        {
            col = 0;
            row += 1;
        }

        m_grid->addWidget(label, row, col);
        col += 1;
    }
}

QSize IconView::sizeHint() const noexcept
{
    if (m_grid->itemAt(0) == nullptr || m_grid->itemAt(0)->widget() == nullptr)
        return QSize{0, 0};

    QWidget* widget = m_grid->itemAt(0)->widget();
    QSize size = widget->sizeHint();
    QMargins margins = m_vbox->contentsMargins();

    int width = size.width() * m_grid->columnCount() 
                + m_grid->horizontalSpacing() * (m_grid->columnCount()-1) 
                + margins.left() + margins.right();

    int height = size.height() * m_grid->rowCount() 
                + m_grid->verticalSpacing() * (m_grid->rowCount() - 1) 
                + margins.top() + margins.bottom();

    return QSize{width, height};
}

} // namespace SvgIcon