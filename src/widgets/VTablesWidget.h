#ifndef VTABLESWIDGET_H
#define VTABLESWIDGET_H

#include <memory>

#include <QTreeView>
#include <QSortFilterProxyModel>

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "CutterTreeWidget.h"

namespace Ui {
class VTablesWidget;
}

class MainWindow;
class VTablesWidget;

class VTableModel : public QAbstractItemModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(VTableModel)                                                            \
        VTableModel(const VTableModel &m) = delete;                                                \
        VTableModel &operator=(const VTableModel &m) = delete;

#    define Q_DISABLE_MOVE(VTableModel)                                                            \
        VTableModel(VTableModel &&m) = delete;                                                     \
        VTableModel &operator=(VTableModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(VTableModel)                                                       \
        Q_DISABLE_COPY(VTableModel)                                                                \
        Q_DISABLE_MOVE(VTableModel)
#endif

    Q_DISABLE_COPY_MOVE(VTableModel)

    friend VTablesWidget;

private:
    QList<VTableDescription> *vtables;

public:
    enum Columns { NAME = 0, ADDRESS, COUNT };
    static const int VTableDescriptionRole = Qt::UserRole;

    VTableModel(QList<VTableDescription> *vtables, QObject *parent = nullptr);
    ~VTableModel() override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
};

class VTableSortFilterProxyModel : public QSortFilterProxyModel
{
public:
    VTableSortFilterProxyModel(VTableModel *model, QObject *parent = nullptr);
    ~VTableSortFilterProxyModel() override;

protected:
    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
};

class VTablesWidget : public CutterDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(VTablesWidget)                                                          \
        VTablesWidget(const VTablesWidget &w) = delete;                                            \
        VTablesWidget &operator=(const VTablesWidget &w) = delete;

#    define Q_DISABLE_MOVE(VTablesWidget)                                                          \
        VTablesWidget(VTablesWidget &&w) = delete;                                                 \
        VTablesWidget &operator=(VTablesWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(VTablesWidget)                                                     \
        Q_DISABLE_COPY(VTablesWidget)                                                              \
        Q_DISABLE_MOVE(VTablesWidget)
#endif

    Q_DISABLE_COPY_MOVE(VTablesWidget)

public:
    explicit VTablesWidget(MainWindow *main);
    ~VTablesWidget() override;

private slots:
    void refreshVTables();
    void on_vTableTreeView_doubleClicked(const QModelIndex &index);

private:
    std::unique_ptr<Ui::VTablesWidget> ui;

    VTableModel *model;
    QSortFilterProxyModel *proxy;
    QList<VTableDescription> vtables;
    CutterTreeWidget *tree;
    RefreshDeferrer *refreshDeferrer;
};

#endif // VTABLESWIDGET_H
