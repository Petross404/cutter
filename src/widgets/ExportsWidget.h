#ifndef EXPORTSWIDGET_H
#define EXPORTSWIDGET_H

#include <memory>

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "widgets/ListDockWidget.h"

#include <QAbstractListModel>
#include <QSortFilterProxyModel>

class MainWindow;
class QTreeWidget;
class ExportsWidget;

namespace Ui {
class ExportsWidget;
}

class ExportsModel : public AddressableItemModel<QAbstractListModel>
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(ExportsModel)                                                           \
        ExportsModel(const ExportsModel &m) = delete;                                              \
        ExportsModel &operator=(const ExportsModel &m) = delete;

#    define Q_DISABLE_MOVE(ExportsModel)                                                           \
        ExportsModel(ExportsModel &&m) = delete;                                                   \
        ExportsModel &operator=(ExportsModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(ExportsModel)                                                      \
        Q_DISABLE_COPY(ExportsModel)                                                               \
        Q_DISABLE_MOVE(ExportsModel)
#endif

    Q_DISABLE_COPY_MOVE(ExportsModel)

    friend ExportsWidget;

private:
    QList<ExportDescription> *exports;

public:
    enum Column {
        OffsetColumn = 0,
        SizeColumn,
        TypeColumn,
        NameColumn,
        CommentColumn,
        ColumnCount
    };
    enum Role { ExportDescriptionRole = Qt::UserRole };

    ExportsModel(QList<ExportDescription> *exports, QObject *parent = nullptr);
    ~ExportsModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    RVA address(const QModelIndex &index) const override;
    QString name(const QModelIndex &index) const override;
};

class ExportsProxyModel : public AddressableFilterProxyModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(ExportsProxyModel)                                                      \
        ExportsProxyModel(const ExportsProxyModel &m) = delete;                                    \
        ExportsProxyModel &operator=(const ExportsProxyModel &m) = delete;

#    define Q_DISABLE_MOVE(ExportsProxyModel)                                                      \
        ExportsProxyModel(ExportsProxyModel &&m) = delete;                                         \
        ExportsProxyModel &operator=(ExportsProxyModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(ExportsProxyModel)                                                 \
        Q_DISABLE_COPY(ExportsProxyModel)                                                          \
        Q_DISABLE_MOVE(ExportsProxyModel)
#endif

    Q_DISABLE_COPY_MOVE(ExportsProxyModel)

public:
    ExportsProxyModel(ExportsModel *source_model, QObject *parent = nullptr);
    ~ExportsProxyModel() override;

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

class ExportsWidget : public ListDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(ExportsWidget)                                                          \
        ExportsWidget(const ExportsWidget &w) = delete;                                            \
        ExportsWidget &operator=(const ExportsWidget &w) = delete;

#    define Q_DISABLE_MOVE(ExportsWidget)                                                          \
        ExportsWidget(ExportsWidget &&w) = delete;                                                 \
        ExportsWidget &operator=(ExportsWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(ExportsWidget)                                                     \
        Q_DISABLE_COPY(ExportsWidget)                                                              \
        Q_DISABLE_MOVE(ExportsWidget)
#endif

    Q_DISABLE_COPY_MOVE(ExportsWidget)

public:
    explicit ExportsWidget(MainWindow *main);
    ~ExportsWidget() override;

private slots:
    void refreshExports();

private:
    ExportsModel *exportsModel;
    ExportsProxyModel *exportsProxyModel;
    QList<ExportDescription> exports;
};

#endif // EXPORTSWIDGET_H
