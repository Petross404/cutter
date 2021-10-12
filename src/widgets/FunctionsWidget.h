#ifndef FUNCTIONSWIDGET_H
#define FUNCTIONSWIDGET_H

#include <memory>

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "widgets/ListDockWidget.h"

class MainWindow;
class FunctionsTask;
class FunctionsWidget;

class FunctionModel : public AddressableItemModel<>
{
    Q_OBJECT

    friend FunctionsWidget;

private:
    QList<FunctionDescription> *functions;
    QSet<RVA> *importAddresses;
    ut64 *mainAdress;

    QFont highlightFont;
    QFont defaultFont;
    bool nested;

    int currentIndex;

    QIcon iconFuncImpDark;
    QIcon iconFuncImpLight;
    QIcon iconFuncMainDark;
    QIcon iconFuncMainLight;
    QIcon iconFuncDark;
    QIcon iconFuncLight;

    bool functionIsImport(ut64 addr) const;

    bool functionIsMain(ut64 addr) const;

public:
    static const int FunctionDescriptionRole = Qt::UserRole;
    static const int IsImportRole = Qt::UserRole + 1;

    enum Column {
        NameColumn = 0,
        SizeColumn,
        ImportColumn,
        OffsetColumn,
        NargsColumn,
        NlocalsColumn,
        NbbsColumn,
        CalltypeColumn,
        EdgesColumn,
        FrameColumn,
        CommentColumn,
        ColumnCount
    };

    FunctionModel(QList<FunctionDescription> *functions, QSet<RVA> *importAddresses,
                  ut64 *mainAdress, bool nested, const QFont &defaultFont,
                  const QFont &highlightFont, QObject *parent = nullptr);

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex &index) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    /**
     * @return true if the index changed
     */
    bool updateCurrentIndex();

    void setNested(bool nested);
    bool isNested() const { return nested; }

    RVA address(const QModelIndex &index) const override;
    QString name(const QModelIndex &index) const override;
private slots:
    void seekChanged(RVA addr);
    void functionRenamed(const RVA offset, const QString &new_name);
};

class FunctionSortFilterProxyModel : public AddressableFilterProxyModel
{
    Q_OBJECT

public:
    FunctionSortFilterProxyModel(FunctionModel *source_model, QObject *parent = nullptr);

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

class FunctionsWidget : public ListDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(FunctionsWidget)                                                        \
        FunctionsWidget(const FunctionsWidget &w) = delete;                                        \
        FunctionsWidget &operator=(const FunctionsWidget &w) = delete;

#    define Q_DISABLE_MOVE(FunctionsWidget)                                                        \
        FunctionsWidget(FunctionsWidget &&w) = delete;                                             \
        FunctionsWidget &operator=(FunctionsWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(FunctionsWidget)                                                   \
        Q_DISABLE_COPY(FunctionsWidget)                                                            \
        Q_DISABLE_MOVE(FunctionsWidget)
#endif

    Q_DISABLE_COPY_MOVE(FunctionsWidget)

public:
    explicit FunctionsWidget(MainWindow *main);
    ~FunctionsWidget() override;
    void changeSizePolicy(QSizePolicy::Policy hor, QSizePolicy::Policy ver);

private slots:
    void onActionFunctionsRenameTriggered();
    void onActionFunctionsUndefineTriggered();
    void onActionHorizontalToggled(bool enable);
    void onActionVerticalToggled(bool enable);
    void showTitleContextMenu(const QPoint &pt);
    void setTooltipStylesheet();
    void refreshTree();

private:
    QSharedPointer<FunctionsTask> task;
    QList<FunctionDescription> functions;
    QSet<RVA> importAddresses;
    ut64 mainAdress;
    FunctionModel *functionModel;
    FunctionSortFilterProxyModel *functionProxyModel;

    QMenu *titleContextMenu;

    QAction actionRename;
    QAction actionUndefine;
    QAction actionHorizontal;
    QAction actionVertical;
};

#endif // FUNCTIONSWIDGET_H
