#ifndef SYMBOLSWIDGET_H
#define SYMBOLSWIDGET_H

#include <memory>
#include <QAbstractListModel>
#include <QSortFilterProxyModel>

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "widgets/ListDockWidget.h"

class MainWindow;
class QTreeWidgetItem;
class SymbolsWidget;

class SymbolsModel : public AddressableItemModel<QAbstractListModel>
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(SymbolsModel)                                                           \
        SymbolsModel(const SymbolsModel &m) = delete;                                              \
        SymbolsModel &operator=(const SymbolsModel &m) = delete;

#    define Q_DISABLE_MOVE(SymbolsModel)                                                           \
        SymbolsModel(SymbolsModel &&m) = delete;                                                   \
        SymbolsModel &operator=(SymbolsModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(SymbolsModel)                                                      \
        Q_DISABLE_COPY(SymbolsModel)                                                               \
        Q_DISABLE_MOVE(SymbolsModel)
#endif

    Q_DISABLE_COPY_MOVE(SymbolsModel)

    friend SymbolsWidget;

private:
    QList<SymbolDescription> *symbols;

public:
    enum Column { AddressColumn = 0, TypeColumn, NameColumn, CommentColumn, ColumnCount };
    enum Role { SymbolDescriptionRole = Qt::UserRole };

    SymbolsModel(QList<SymbolDescription> *exports, QObject *parent = nullptr);
    ~SymbolsModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    RVA address(const QModelIndex &index) const override;
    QString name(const QModelIndex &index) const override;
};

class SymbolsProxyModel : public AddressableFilterProxyModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(SymbolsProxyModel)                                                      \
        SymbolsProxyModel(const SymbolsProxyModel &m) = delete;                                    \
        SymbolsProxyModel &operator=(const SymbolsProxyModel &m) = delete;

#    define Q_DISABLE_MOVE(SymbolsProxyModel)                                                      \
        SymbolsProxyModel(SymbolsProxyModel &&m) = delete;                                         \
        SymbolsProxyModel &operator=(SymbolsProxyModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(SymbolsProxyModel)                                                 \
        Q_DISABLE_COPY(SymbolsProxyModel)                                                          \
        Q_DISABLE_MOVE(SymbolsProxyModel)
#endif

    Q_DISABLE_COPY_MOVE(SymbolsProxyModel)

public:
    SymbolsProxyModel(SymbolsModel *sourceModel, QObject *parent = nullptr);
    ~SymbolsProxyModel() override;

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

class SymbolsWidget : public ListDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(SymbolsWidget)                                                          \
        SymbolsWidget(const SymbolsWidget &w) = delete;                                            \
        SymbolsWidget &operator=(const SymbolsWidget &w) = delete;

#    define Q_DISABLE_MOVE(SymbolsWidget)                                                          \
        SymbolsWidget(SymbolsWidget &&w) = delete;                                                 \
        SymbolsWidget &operator=(SymbolsWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(SymbolsWidget)                                                     \
        Q_DISABLE_COPY(SymbolsWidget)                                                              \
        Q_DISABLE_MOVE(SymbolsWidget)
#endif

    Q_DISABLE_COPY_MOVE(SymbolsWidget)

public:
    explicit SymbolsWidget(MainWindow *main);
    ~SymbolsWidget() override;

private slots:
    void refreshSymbols();

private:
    QList<SymbolDescription> symbols;
    SymbolsModel *symbolsModel;
    SymbolsProxyModel *symbolsProxyModel;
};

#endif // SYMBOLSWIDGET_H
