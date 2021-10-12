#ifndef VISUALNAVBAR_H
#define VISUALNAVBAR_H

#include <QToolBar>
#include <QGraphicsScene>

#include "core/Cutter.h"

class MainWindow;
class QGraphicsView;

class VisualNavbar : public QToolBar
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(VisualNavbar)                                                           \
        VisualNavbar(const VisualNavbar &b) = delete;                                              \
        VisualNavbar &operator=(const VisualNavbar &b) = delete;

#    define Q_DISABLE_MOVE(VisualNavbar)                                                           \
        VisualNavbar(VisualNavbar &&b) = delete;                                                   \
        VisualNavbar &operator=(VisualNavbar &&b) = delete;

#    define Q_DISABLE_COPY_MOVE(VisualNavbar)                                                      \
        Q_DISABLE_COPY(VisualNavbar)                                                               \
        Q_DISABLE_MOVE(VisualNavbar)
#endif

    Q_DISABLE_COPY_MOVE(VisualNavbar)

    struct XToAddress
    {
        double x_start;
        double x_end;
        RVA address_from;
        RVA address_to;
    };

public:
    explicit VisualNavbar(MainWindow *main, QWidget *parent = nullptr);
    ~VisualNavbar() override;

public slots:
    void paintEvent(QPaintEvent *event) override;
    void updateGraphicsScene();

private slots:
    void fetchAndPaintData();
    void fetchStats();
    void drawSeekCursor();
    void drawPCCursor();
    void drawCursor(RVA addr, QColor color, QGraphicsRectItem *&graphicsItem);
    void on_seekChanged(RVA addr);

private:
    QGraphicsView *graphicsView;
    QGraphicsScene *graphicsScene;
    QGraphicsRectItem *seekGraphicsItem;
    QGraphicsRectItem *PCGraphicsItem;
    MainWindow *main;

    BlockStatistics stats;
    unsigned int statsWidth = 0;
    unsigned int previousWidth = 0;

    QList<XToAddress> xToAddress;

    RVA localXToAddress(double x);
    double addressToLocalX(RVA address);
    QList<QString> sectionsForAddress(RVA address);
    QString toolTipForAddress(RVA address);

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // VISUALNAVBAR_H
