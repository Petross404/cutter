#ifndef SEGMENTSWIDGET_H
#define SEGMENTSWIDGET_H

#include <memory>

#include <QAbstractListModel>
#include <QSortFilterProxyModel>

#include "core/Cutter.h"
#include "widgets/ListDockWidget.h"

class QAbstractItemView;
class SegmentsWidget;

class SegmentsModel : public AddressableItemModel<QAbstractListModel>
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(SegmentsModel)                                                          \
        SegmentsModel(const SegmentsModel &m) = delete;                                            \
        SegmentsModel &operator=(const SegmentsModel &m) = delete;

#    define Q_DISABLE_MOVE(SegmentsModel)                                                          \
        SegmentsModel(SegmentsModel &&m) = delete;                                                 \
        SegmentsModel &operator=(SegmentsModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(SegmentsModel)                                                     \
        Q_DISABLE_COPY(SegmentsModel)                                                              \
        Q_DISABLE_MOVE(SegmentsModel)
#endif

    Q_DISABLE_COPY_MOVE(SegmentsModel)

    friend SegmentsWidget;

private:
    QList<SegmentDescription> *segments;

public:
    enum Column {
        NameColumn = 0,
        SizeColumn,
        AddressColumn,
        EndAddressColumn,
        PermColumn,
        CommentColumn,
        ColumnCount
    };
    enum Role { SegmentDescriptionRole = Qt::UserRole };

    SegmentsModel(QList<SegmentDescription> *segments, QObject *parent = nullptr);
    ~SegmentsModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int segment, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    RVA address(const QModelIndex &index) const override;
    QString name(const QModelIndex &index) const override;
};

class SegmentsProxyModel : public AddressableFilterProxyModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(SegmentsProxyModel)                                                     \
        SegmentsProxyModel(const SegmentsProxyModel &m) = delete;                                  \
        SegmentsProxyModel &operator=(const SegmentsProxyModel &m) = delete;

#    define Q_DISABLE_MOVE(SegmentsProxyModel)                                                     \
        SegmentsProxyModel(SegmentsProxyModel &&m) = delete;                                       \
        SegmentsProxyModel &operator=(SegmentsProxyModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(SegmentsProxyModel)                                                \
        Q_DISABLE_COPY(SegmentsProxyModel)                                                         \
        Q_DISABLE_MOVE(SegmentsProxyModel)
#endif

    Q_DISABLE_COPY_MOVE(SegmentsProxyModel)

public:
    SegmentsProxyModel(SegmentsModel *sourceModel, QObject *parent = nullptr);
    ~SegmentsProxyModel() override;

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

class SegmentsWidget : public ListDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(SegmentsWidget)                                                         \
        SegmentsWidget(const SegmentsWidget &w) = delete;                                          \
        SegmentsWidget &operator=(const SegmentsWidget &w) = delete;

#    define Q_DISABLE_MOVE(SegmentsWidget)                                                         \
        SegmentsWidget(SegmentsWidget &&w) = delete;                                               \
        SegmentsWidget &operator=(SegmentsWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(SegmentsWidget)                                                    \
        Q_DISABLE_COPY(SegmentsWidget)                                                             \
        Q_DISABLE_MOVE(SegmentsWidget)
#endif

    Q_DISABLE_COPY_MOVE(SegmentsWidget)

public:
    explicit SegmentsWidget(MainWindow *main);
    ~SegmentsWidget() override;

private slots:
    void refreshSegments();

private:
    QList<SegmentDescription> segments;
    SegmentsModel *segmentsModel;
};

#endif // SEGMENTSWIDGET_H
