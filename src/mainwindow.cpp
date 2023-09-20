#include "mainwindow.h"
#include <QFile>
#include <QScrollBar>
#include <QDebug>

namespace SvgIcon
{

MainWindow::MainWindow(QWidget* parent) noexcept:
    m_configWidget{new ConfigWidget},
    m_configDock{new QDockWidget},
    m_iconViewArea{new QScrollArea},
    m_iconView{new IconView}
{
    m_configDock->setWidget(m_configWidget);
    m_configDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    addDockWidget(Qt::LeftDockWidgetArea, m_configDock);

    m_iconViewArea->setWidget(m_iconView);
    m_iconViewArea->setWidgetResizable(true);
    setCentralWidget(m_iconViewArea);

    m_iconView->setColumns(20);
    display();

    connect(m_configWidget, &ConfigWidget::changed, this, &MainWindow::display);
}

MainWindow::~MainWindow() noexcept
{

}

QSize MainWindow::sizeHint() const noexcept
{
    return QSize(1080, 720);
}

void MainWindow::resizeEvent(QResizeEvent* event)
{
    (void)(event);
    display();
}

void MainWindow::display() const noexcept
{
    int width = m_iconViewArea->width() - m_iconViewArea->verticalScrollBar()->width();
    m_iconView->setIcons(m_configWidget->currentModule()->icons(), width);
}
    
} // namespace SvgIcon