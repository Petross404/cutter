#ifndef RESOURCESWIDGET_H
#define RESOURCESWIDGET_H

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "CutterTreeView.h"
#include "common/AddressableItemModel.h"
#include "widgets/ListDockWidget.h"

class MainWindow;
class ResourcesWidget;

class ResourcesModel : public AddressableItemModel<QAbstractListModel>
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(ResourcesModel)                                                         \
        ResourcesModel(const ResourcesModel &m) = delete;                                          \
        ResourcesModel &operator=(const ResourcesModel &m) = delete;

#    define Q_DISABLE_MOVE(ResourcesModel)                                                         \
        ResourcesModel(ResourcesModel &&m) = delete;                                               \
        ResourcesModel &operator=(ResourcesModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(ResourcesModel)                                                    \
        Q_DISABLE_COPY(ResourcesModel)                                                             \
        Q_DISABLE_MOVE(ResourcesModel)
#endif

    Q_DISABLE_COPY_MOVE(ResourcesModel)

    friend ResourcesWidget;

private:
    QList<ResourcesDescription> *resources;

public:
    enum Columns { INDEX = 0, NAME, VADDR, TYPE, SIZE, LANG, COMMENT, COUNT };
    explicit ResourcesModel(QList<ResourcesDescription> *resources, QObject *parent = nullptr);
    ~ResourcesModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    RVA address(const QModelIndex &index) const override;
};

class ResourcesWidget : public ListDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(ResourcesWidget)                                                        \
        ResourcesWidget(const ResourcesWidget &w) = delete;                                        \
        ResourcesWidget &operator=(const ResourcesWidget &w) = delete;

#    define Q_DISABLE_MOVE(ResourcesWidget)                                                        \
        ResourcesWidget(ResourcesWidget &&w) = delete;                                             \
        ResourcesWidget &operator=(ResourcesWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(ResourcesWidget)                                                   \
        Q_DISABLE_COPY(ResourcesWidget)                                                            \
        Q_DISABLE_MOVE(ResourcesWidget)
#endif

    Q_DISABLE_COPY_MOVE(ResourcesWidget)

private:
    ResourcesModel *model;
    AddressableFilterProxyModel *filterModel;
    QList<ResourcesDescription> resources;

public:
    explicit ResourcesWidget(MainWindow *main);
    ~ResourcesWidget() override;

private slots:
    void refreshResources();
};

#endif // RESOURCESWIDGET_H
