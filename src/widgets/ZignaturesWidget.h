#ifndef ZIGNATURESWIDGET_H
#define ZIGNATURESWIDGET_H

#include <memory>

#include "core/Cutter.h"
#include "CutterDockWidget.h"

#include <QAbstractListModel>
#include <QSortFilterProxyModel>

class MainWindow;
class QTreeWidget;
class QTreeWidgetItem;
class ZignaturesWidget;

namespace Ui {
class ZignaturesWidget;
}

class ZignaturesModel : public QAbstractListModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(ZignaturesModel)                                                        \
        ZignaturesModel(const ZignaturesModel &m) = delete;                                        \
        ZignaturesModel &operator=(const ZignaturesModel &m) = delete;

#    define Q_DISABLE_MOVE(ZignaturesModel)                                                        \
        ZignaturesModel(ZignaturesModel &&m) = delete;                                             \
        ZignaturesModel &operator=(ZignaturesModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(ZignaturesModel)                                                   \
        Q_DISABLE_COPY(ZignaturesModel)                                                            \
        Q_DISABLE_MOVE(ZignaturesModel)
#endif

    Q_DISABLE_COPY_MOVE(ZignaturesModel)

    friend ZignaturesWidget;

public:
    enum Column { OffsetColumn = 0, NameColumn, ValueColumn, ColumnCount };
    enum Role { ZignatureDescriptionRole = Qt::UserRole };

    ZignaturesModel(QList<ZignatureDescription> *zignatures, QObject *parent = nullptr);
    ~ZignaturesModel() override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

private:
    QList<ZignatureDescription> *zignatures;
};

class ZignaturesProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(ZignaturesProxyModel)                                                   \
        ZignaturesProxyModel(const ZignaturesProxyModel &m) = delete;                              \
        ZignaturesProxyModel &operator=(const ZignaturesProxyModel &m) = delete;

#    define Q_DISABLE_MOVE(ZignaturesProxyModel)                                                   \
        ZignaturesProxyModel(ZignaturesProxyModel &&m) = delete;                                   \
        ZignaturesProxyModel &operator=(ZignaturesProxyModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(ZignaturesProxyModel)                                              \
        Q_DISABLE_COPY(ZignaturesProxyModel)                                                       \
        Q_DISABLE_MOVE(ZignaturesProxyModel)
#endif

    Q_DISABLE_COPY_MOVE(ZignaturesProxyModel)

public:
    ZignaturesProxyModel(ZignaturesModel *sourceModel, QObject *parent = nullptr);
    ~ZignaturesProxyModel() override;

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

class ZignaturesWidget : public CutterDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(ZignaturesWidget)                                                       \
        ZignaturesWidget(const ZignaturesWidget &w) = delete;                                      \
        ZignaturesWidget &operator=(const ZignaturesWidget &w) = delete;

#    define Q_DISABLE_MOVE(ZignaturesWidget)                                                       \
        ZignaturesWidget(ZignaturesWidget &&w) = delete;                                           \
        ZignaturesWidget &operator=(ZignaturesWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(ZignaturesWidget)                                                  \
        Q_DISABLE_COPY(ZignaturesWidget)                                                           \
        Q_DISABLE_MOVE(ZignaturesWidget)
#endif

    Q_DISABLE_COPY_MOVE(ZignaturesWidget)

public:
    explicit ZignaturesWidget(MainWindow *main);
    ~ZignaturesWidget() override;

private slots:
    void on_zignaturesTreeView_doubleClicked(const QModelIndex &index);

    void refreshZignatures();

private:
    std::unique_ptr<Ui::ZignaturesWidget> ui;

    ZignaturesModel *zignaturesModel;
    ZignaturesProxyModel *zignaturesProxyModel;
    QList<ZignatureDescription> zignatures;

    void setScrollMode();
};

#endif // ZIGNATURESWIDGET_H
