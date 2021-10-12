#ifndef RELOCSWIDGET_H
#define RELOCSWIDGET_H

#include <memory>
#include <QAbstractTableModel>
#include <QSortFilterProxyModel>

#include "CutterDockWidget.h"
#include "core/Cutter.h"
#include "widgets/ListDockWidget.h"

class MainWindow;
class RelocsWidget;

class RelocsModel : public AddressableItemModel<QAbstractTableModel>
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(RelocsModel)                                                            \
        RelocsModel(const RelocsModel &w) = delete;                                                \
        RelocsModel &operator=(const RelocsModel &w) = delete;

#    define Q_DISABLE_MOVE(RelocsModel)                                                            \
        RelocsModel(RelocsModel &&w) = delete;                                                     \
        RelocsModel &operator=(RelocsModel &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(RelocsModel)                                                       \
        Q_DISABLE_COPY(RelocsModel)                                                                \
        Q_DISABLE_MOVE(RelocsModel)
#endif

    Q_DISABLE_COPY_MOVE(RelocsModel)

    friend RelocsWidget;

private:
    QList<RelocDescription> relocs;

public:
    enum Column { VAddrColumn = 0, TypeColumn, NameColumn, CommentColumn, ColumnCount };
    enum Role { RelocDescriptionRole = Qt::UserRole, AddressRole };

    RelocsModel(QObject *parent = nullptr);
    ~RelocsModel() override;

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    RVA address(const QModelIndex &index) const override;
    QString name(const QModelIndex &index) const override;

    void reload();
};

class RelocsProxyModel : public AddressableFilterProxyModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(RelocsProxyModel)                                                       \
        RelocsProxyModel(const RelocsProxyModel &w) = delete;                                      \
        RelocsProxyModel &operator=(const RelocsProxyModel &w) = delete;

#    define Q_DISABLE_MOVE(RelocsProxyModel)                                                       \
        RelocsProxyModel(RelocsProxyModel &&w) = delete;                                           \
        RelocsProxyModel &operator=(RelocsProxyModel &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(RelocsProxyModel)                                                  \
        Q_DISABLE_COPY(RelocsProxyModel)                                                           \
        Q_DISABLE_MOVE(RelocsProxyModel)
#endif

    Q_DISABLE_COPY_MOVE(RelocsProxyModel)

public:
    RelocsProxyModel(RelocsModel *sourceModel, QObject *parent = nullptr);
    ~RelocsProxyModel() override;

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

class RelocsWidget : public ListDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(RelocsWidget)                                                           \
        RelocsWidget(const RelocsWidget &w) = delete;                                              \
        RelocsWidget &operator=(const RelocsWidget &w) = delete;

#    define Q_DISABLE_MOVE(RelocsWidget)                                                           \
        RelocsWidget(RelocsWidget &&w) = delete;                                                   \
        RelocsWidget &operator=(RelocsWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(RelocsWidget)                                                      \
        Q_DISABLE_COPY(RelocsWidget)                                                               \
        Q_DISABLE_MOVE(RelocsWidget)
#endif

    Q_DISABLE_COPY_MOVE(RelocsWidget)

public:
    explicit RelocsWidget(MainWindow *main);
    ~RelocsWidget() override;

private slots:
    void refreshRelocs();

private:
    RelocsModel *relocsModel;
    RelocsProxyModel *relocsProxyModel;
};

#endif // RELOCSWIDGET_H
