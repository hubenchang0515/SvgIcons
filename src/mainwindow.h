#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include <QScrollArea>

#include "configwidget.h"
#include "iconview.h"

namespace SvgIcon
{

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent=nullptr) noexcept;
    ~MainWindow() noexcept;

    virtual QSize sizeHint() const noexcept override;

protected:
    virtual void resizeEvent(QResizeEvent* event) override;

private:
    ConfigWidget* m_configWidget;
    QDockWidget* m_configDock;
    QScrollArea* m_iconViewArea;
    IconView* m_iconView;

    void display() const noexcept;
};
    
} // namespace SvgIcon


#endif // MAINWINDOW_H