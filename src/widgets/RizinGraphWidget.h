#ifndef RZ_GRAPH_WIDGET_H
#define RZ_GRAPH_WIDGET_H

#include <memory>

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "widgets/SimpleTextGraphView.h"
#include "common/RefreshDeferrer.h"

class MainWindow;

namespace Ui {
class RizinGraphWidget;
}

class RizinGraphWidget;

/**
 * @brief Generic graph view for rizin graphs.
 * Not all rizin graph commands output the same kind of json. Only those that have following format
 * @code{.json}
 * { "nodes": [
 *      {
 *          "id": 0,
 *          "tittle": "node_0_tittle",
 *          "body": "".
 *          "out_nodes": [1, 2, 3]
 *      },
 *      ...
 * ]}
 * @endcode
 * Id don't have to be sequential. Simple text label is displayed containing concatenation of
 * label and body. No rizin builtin graph uses both. Duplicate edges and edges with target id
 * not present in the list of nodes are removed.
 */
class GenericRizinGraphView : public SimpleTextGraphView
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(GenericRizinGraphView)                                                  \
        GenericRizinGraphView(const GenericRizinGraphView &w) = delete;                            \
        GenericRizinGraphView &operator=(const GenericRizinGraphView &w) = delete;

#    define Q_DISABLE_MOVE(GenericRizinGraphView)                                                  \
        GenericRizinGraphView(GenericRizinGraphView &&w) = delete;                                 \
        GenericRizinGraphView &operator=(GenericRizinGraphView &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(GenericRizinGraphView)                                             \
        Q_DISABLE_COPY(GenericRizinGraphView)                                                      \
        Q_DISABLE_MOVE(GenericRizinGraphView)
#endif

    Q_DISABLE_COPY_MOVE(GenericRizinGraphView)

public:
    GenericRizinGraphView(RizinGraphWidget *parent, MainWindow *main);
    ~GenericRizinGraphView() override;
    void setGraphCommand(QString cmd);
    void refreshView() override;

protected:
    void loadCurrentGraph() override;

private:
    RefreshDeferrer refreshDeferrer;
    QString graphCommand;
    QString lastShownCommand;
};

class RizinGraphWidget : public CutterDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(RizinGraphWidget)                                                       \
        RizinGraphWidget(const RizinGraphWidget &w) = delete;                                      \
        RizinGraphWidget &operator=(const RizinGraphWidget &w) = delete;

#    define Q_DISABLE_MOVE(RizinGraphWidget)                                                       \
        RizinGraphWidget(RizinGraphWidget &&w) = delete;                                           \
        RizinGraphWidget &operator=(RizinGraphWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(RizinGraphWidget)                                                  \
        Q_DISABLE_COPY(RizinGraphWidget)                                                           \
        Q_DISABLE_MOVE(RizinGraphWidget)
#endif

    Q_DISABLE_COPY_MOVE(RizinGraphWidget)

public:
    explicit RizinGraphWidget(MainWindow *main);
    ~RizinGraphWidget() override;

private:
    std::unique_ptr<Ui::RizinGraphWidget> ui;
    GenericRizinGraphView *graphView;

    void typeChanged();
};

#endif // RZ_GRAPH_WIDGET_H
