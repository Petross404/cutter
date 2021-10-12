#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <memory>

#include <QAbstractItemModel>
#include <QSortFilterProxyModel>

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "AddressableItemList.h"

class MainWindow;
class QTreeWidgetItem;
class SearchWidget;

class SearchModel : public AddressableItemModel<QAbstractListModel>
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(SearchModel)                                                            \
        SearchModel(const SearchModel &m) = delete;                                                \
        SearchModel &operator=(const SearchModel &m) = delete;

#    define Q_DISABLE_MOVE(SearchModel)                                                            \
        SearchModel(SearchModel &&m) = delete;                                                     \
        SearchModel &operator=(SearchModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(SearchModel)                                                       \
        Q_DISABLE_COPY(SearchModel)                                                                \
        Q_DISABLE_MOVE(SearchModel)
#endif

    Q_DISABLE_COPY_MOVE(SearchModel)

    friend SearchWidget;

private:
    QList<SearchDescription> *search;

public:
    enum Columns { OFFSET = 0, SIZE, CODE, DATA, COMMENT, COUNT };
    static const int SearchDescriptionRole = Qt::UserRole;

    SearchModel(QList<SearchDescription> *search, QObject *parent = nullptr);
    ~SearchModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    RVA address(const QModelIndex &index) const override;
};

class SearchSortFilterProxyModel : public AddressableFilterProxyModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(SearchSortFilterProxyModel)                                             \
        SearchSortFilterProxyModel(const SearchSortFilterProxyModel &m) = delete;                  \
        SearchSortFilterProxyModel &operator=(const SearchSortFilterProxyModel &m) = delete;

#    define Q_DISABLE_MOVE(SearchSortFilterProxyModel)                                             \
        SearchSortFilterProxyModel(SearchSortFilterProxyModel &&m) = delete;                       \
        SearchSortFilterProxyModel &operator=(SearchSortFilterProxyModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(SearchSortFilterProxyModel)                                        \
        Q_DISABLE_COPY(SearchSortFilterProxyModel)                                                 \
        Q_DISABLE_MOVE(SearchSortFilterProxyModel)
#endif

    Q_DISABLE_COPY_MOVE(SearchSortFilterProxyModel)

public:
    SearchSortFilterProxyModel(SearchModel *source_model, QObject *parent = nullptr);
    ~SearchSortFilterProxyModel() override;

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

namespace Ui {
class SearchWidget;
}

class SearchWidget : public CutterDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(SearchWidget)                                                           \
        SearchWidget(const SearchWidget &w) = delete;                                              \
        SearchWidget &operator=(const SearchWidget &w) = delete;

#    define Q_DISABLE_MOVE(SearchWidget)                                                           \
        SearchWidget(SearchWidget &&w) = delete;                                                   \
        SearchWidget &operator=(SearchWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(SearchWidget)                                                      \
        Q_DISABLE_COPY(SearchWidget)                                                               \
        Q_DISABLE_MOVE(SearchWidget)
#endif

    Q_DISABLE_COPY_MOVE(SearchWidget)

public:
    explicit SearchWidget(MainWindow *main);
    ~SearchWidget() override;

private slots:
    void searchChanged();
    void updateSearchBoundaries();
    void refreshSearchspaces();

private:
    std::unique_ptr<Ui::SearchWidget> ui;

    SearchModel *search_model;
    SearchSortFilterProxyModel *search_proxy_model;
    QList<SearchDescription> search;

    void refreshSearch();
    void checkSearchResultEmpty();
    void setScrollMode();
    void updatePlaceholderText(int index);
};

#endif // SEARCHWIDGET_H
