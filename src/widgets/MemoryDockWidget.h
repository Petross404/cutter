#ifndef MEMORYDOCKWIDGET_H
#define MEMORYDOCKWIDGET_H

#include "AddressableDockWidget.h"
#include "core/Cutter.h"

#include <QAction>

/* Disassembly/Graph/Hexdump/Decompiler view priority */
enum class MemoryWidgetType { Disassembly, Graph, Hexdump, Decompiler };

class CUTTER_EXPORT MemoryDockWidget : public AddressableDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(MemoryDockWidget)                                                       \
        MemoryDockWidget(const MemoryDockWidget &w) = delete;                                      \
        MemoryDockWidget &operator=(const MemoryDockWidget &w) = delete;

#    define Q_DISABLE_MOVE(MemoryDockWidget)                                                       \
        MemoryDockWidget(MemoryDockWidget &&w) = delete;                                           \
        MemoryDockWidget &operator=(MemoryDockWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(MemoryDockWidget)                                                  \
        Q_DISABLE_COPY(MemoryDockWidget)                                                           \
        Q_DISABLE_MOVE(MemoryDockWidget)
#endif

    Q_DISABLE_COPY_MOVE(MemoryDockWidget)

public:
    MemoryDockWidget(MemoryWidgetType type, MainWindow *parent);
    ~MemoryDockWidget() override;

    bool tryRaiseMemoryWidget();
    MemoryWidgetType getType() const { return mType; }
    bool eventFilter(QObject *object, QEvent *event) override;

private:
    MemoryWidgetType mType;
};

#endif // MEMORYDOCKWIDGET_H
