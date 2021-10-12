#ifndef GLIBCHEAPWIDGET_H
#define GLIBCHEAPWIDGET_H

#include <QDockWidget>
#include "CutterDockWidget.h"
#include "core/Cutter.h"
#include <QTableView>
#include <QComboBox>
#include <AddressableItemContextMenu.h>

namespace Ui {
class GlibcHeapWidget;
}

class GlibcHeapModel : public QAbstractTableModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(GlibcHeapModel)                                                         \
        GlibcHeapModel(const GlibcHeapModel &m) = delete;                                          \
        GlibcHeapModel &operator=(const GlibcHeapModel &m) = delete;

#    define Q_DISABLE_MOVE(GlibcHeapModel)                                                         \
        GlibcHeapModel(GlibcHeapModel &&m) = delete;                                               \
        GlibcHeapModel &operator=(GlibcHeapModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(GlibcHeapModel)                                                    \
        Q_DISABLE_COPY(GlibcHeapModel)                                                             \
        Q_DISABLE_MOVE(GlibcHeapModel)
#endif

    Q_DISABLE_COPY_MOVE(GlibcHeapModel)

public:
    explicit GlibcHeapModel(QObject *parent = nullptr);
    enum Column { OffsetColumn = 0, SizeColumn, StatusColumn, ColumnCount };
    void reload();
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
    RVA arena_addr = 0;

private:
    QVector<Chunk> values;
};

class GlibcHeapWidget : public QWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(GlibcHeapWidget)                                                        \
        GlibcHeapWidget(const GlibcHeapWidget &w) = delete;                                        \
        GlibcHeapWidget &operator=(const GlibcHeapWidget &w) = delete;

#    define Q_DISABLE_MOVE(GlibcHeapWidget)                                                        \
        GlibcHeapWidget(GlibcHeapWidget &&w) = delete;                                             \
        GlibcHeapWidget &operator=(GlibcHeapWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(GlibcHeapWidget)                                                   \
        Q_DISABLE_COPY(GlibcHeapWidget)                                                            \
        Q_DISABLE_MOVE(GlibcHeapWidget)
#endif

    Q_DISABLE_COPY_MOVE(GlibcHeapWidget)

public:
    explicit GlibcHeapWidget(MainWindow *main, QWidget *parent);
    ~GlibcHeapWidget() override;
private slots:
    void updateContents();
    void onDoubleClicked(const QModelIndex &index);
    void onArenaSelected(int index);
    void customMenuRequested(QPoint pos);
    void onCurrentChanged(const QModelIndex &current, const QModelIndex &previous);
    void viewChunkInfo();
    void viewBinInfo();
    void viewArenaInfo();

private:
    void updateArenas();
    void updateChunks();
    std::unique_ptr<Ui::GlibcHeapWidget> ui;
    QTableView *viewHeap;
    QComboBox *arenaSelectorView;
    GlibcHeapModel *modelHeap = new GlibcHeapModel(this);
    QVector<Arena> arenas;
    QAction *chunkInfoAction;
    QAction *binInfoAction;
    AddressableItemContextMenu addressableItemContextMenu;
    RefreshDeferrer *refreshDeferrer {};
    MainWindow *main;
};

#endif // GLIBCHEAPWIDGET_H
