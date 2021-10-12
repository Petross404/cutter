#ifndef LISTDOCKWIDGET_H
#define LISTDOCKWIDGET_H

#include <memory>
#include <QAbstractItemModel>
#include <QSortFilterProxyModel>
#include <QMenu>

#include "core/Cutter.h"
#include "common/AddressableItemModel.h"
#include "CutterDockWidget.h"
#include "CutterTreeWidget.h"
#include "menus/AddressableItemContextMenu.h"

class MainWindow;
class QTreeWidgetItem;
class CommentsWidget;

namespace Ui {
class ListDockWidget;
}

class CUTTER_EXPORT ListDockWidget : public CutterDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(ListDockWidget)                                                         \
        ListDockWidget(const ListDockWidget &w) = delete;                                          \
        ListDockWidget &operator=(const ListDockWidget &w) = delete;

#    define Q_DISABLE_MOVE(ListDockWidget)                                                         \
        ListDockWidget(ListDockWidget &&w) = delete;                                               \
        ListDockWidget &operator=(ListDockWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(ListDockWidget)                                                    \
        Q_DISABLE_COPY(ListDockWidget)                                                             \
        Q_DISABLE_MOVE(ListDockWidget)
#endif

    Q_DISABLE_COPY_MOVE(ListDockWidget)

public:
    enum class SearchBarPolicy {
        ShowByDefault,
        HideByDefault,
        Hide,
    };

    explicit ListDockWidget(MainWindow *main,
                            SearchBarPolicy searchBarPolicy = SearchBarPolicy::ShowByDefault);
    ~ListDockWidget() override;

    void showCount(bool show);

protected:
    void setModels(AddressableFilterProxyModel *objectFilterProxyModel);

    std::unique_ptr<Ui::ListDockWidget> ui;

private:
    AddressableFilterProxyModel *objectFilterProxyModel = nullptr;
    CutterTreeWidget *tree;
    SearchBarPolicy searchBarPolicy;
};

#endif // LISTDOCKWIDGET_H
