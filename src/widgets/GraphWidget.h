#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include "MemoryDockWidget.h"
#include <QLineEdit>

class MainWindow;
class DisassemblerGraphView;

class GraphWidget : public MemoryDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(GraphWidget)                                                            \
        GraphWidget(const GraphWidget &w) = delete;                                                \
        GraphWidget &operator=(const GraphWidget &w) = delete;

#    define Q_DISABLE_MOVE(GraphWidget)                                                            \
        GraphWidget(GraphWidget &&w) = delete;                                                     \
        GraphWidget &operator=(GraphWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(GraphWidget)                                                       \
        Q_DISABLE_COPY(GraphWidget)                                                                \
        Q_DISABLE_MOVE(GraphWidget)
#endif

    Q_DISABLE_COPY_MOVE(GraphWidget)

public:
    explicit GraphWidget(MainWindow *main);
    ~GraphWidget() override;

    DisassemblerGraphView *getGraphView() const;

    static QString getWidgetType();

signals:
    void graphClosed();

protected:
    QWidget *widgetToFocusOnRaise() override;

private:
    void closeEvent(QCloseEvent *event) override;

    QString getWindowTitle() const override;
    void prepareHeader();

    DisassemblerGraphView *graphView;
    QLineEdit *header = nullptr;
};

#endif // GRAPHWIDGET_H
