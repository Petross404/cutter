#ifndef ENTRYPOINTWIDGET_H
#define ENTRYPOINTWIDGET_H

#include <memory>
#include <QStyledItemDelegate>
#include <QTreeWidgetItem>

#include "CutterDockWidget.h"

class MainWindow;
class QTreeWidget;

namespace Ui {
class EntrypointWidget;
}

class EntrypointWidget : public CutterDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(EntrypointWidget)                                                       \
        EntrypointWidget(const EntrypointWidget &w) = delete;                                      \
        EntrypointWidget &operator=(const EntrypointWidget &w) = delete;

#    define Q_DISABLE_MOVE(EntrypointWidget)                                                       \
        EntrypointWidget(EntrypointWidget &&w) = delete;                                           \
        EntrypointWidget &operator=(EntrypointWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(EntrypointWidget)                                                  \
        Q_DISABLE_COPY(EntrypointWidget)                                                           \
        Q_DISABLE_MOVE(EntrypointWidget)
#endif

    Q_DISABLE_COPY_MOVE(EntrypointWidget)

public:
    explicit EntrypointWidget(MainWindow *main);
    ~EntrypointWidget() override;

private slots:
    void on_entrypointTreeWidget_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void fillEntrypoint();

private:
    std::unique_ptr<Ui::EntrypointWidget> ui;

    void setScrollMode();
};

#endif // ENTRYPOINTWIDGET_H
