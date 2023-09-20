#ifndef ICON_VIEW_H
#define ICON_VIEW_H

#include <QWidget>
#include <QLayout>
#include <QMap>
#include <QString>
#include <QPixmap>

namespace SvgIcon
{

class IconView : public QWidget
{
    Q_OBJECT
public:
    IconView(QWidget* parent=nullptr) noexcept;
    ~IconView() noexcept;

    int columns() const noexcept;
    void setColumns(int n) noexcept;
    void clear() const noexcept;
    void setIcons(const QMap<QString, QByteArray>& icons, int width) noexcept;

    virtual QSize sizeHint() const noexcept override;

private:
    QVBoxLayout* m_vbox;
    QGridLayout* m_grid;
    int m_columns;
};

} // namespace SvgIcon

#endif // ICON_VIEW_H