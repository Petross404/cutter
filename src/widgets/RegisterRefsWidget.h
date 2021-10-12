#pragma once

#include <memory>

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "CutterTreeWidget.h"
#include "menus/AddressableItemContextMenu.h"

#include <QAbstractListModel>
#include <QSortFilterProxyModel>

class MainWindow;
class QTreeWidget;
class RegisterRefsWidget;

namespace Ui {
class RegisterRefsWidget;
}

class MainWindow;
class QTreeWidgetItem;

struct RegisterRefDescription
{
    QString reg;
    QString value;
    RefDescription refDesc;
};
Q_DECLARE_METATYPE(RegisterRefDescription)

class RegisterRefModel : public QAbstractListModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(RegisterRefModel)                                                       \
        RegisterRefModel(const RegisterRefModel &w) = delete;                                      \
        RegisterRefModel &operator=(const RegisterRefModel &w) = delete;

#    define Q_DISABLE_MOVE(RegisterRefModel)                                                       \
        RegisterRefModel(RegisterRefModel &&w) = delete;                                           \
        RegisterRefModel &operator=(RegisterRefModel &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(RegisterRefModel)                                                  \
        Q_DISABLE_COPY(RegisterRefModel)                                                           \
        Q_DISABLE_MOVE(RegisterRefModel)
#endif

    Q_DISABLE_COPY_MOVE(RegisterRefModel)

    friend RegisterRefsWidget;

private:
    QList<RegisterRefDescription> *registerRefs;

public:
    enum Column { RegColumn = 0, ValueColumn, RefColumn, CommentColumn, ColumnCount };
    enum Role { RegisterRefDescriptionRole = Qt::UserRole };

    RegisterRefModel(QList<RegisterRefDescription> *registerRefs, QObject *parent = nullptr);
    ~RegisterRefModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;
};

class RegisterRefProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(RegisterRefProxyModel)                                                  \
        RegisterRefProxyModel(const RegisterRefProxyModel &m) = delete;                            \
        RegisterRefProxyModel &operator=(const RegisterRefProxyModel &m) = delete;

#    define Q_DISABLE_MOVE(RegisterRefProxyModel)                                                  \
        RegisterRefProxyModel(RegisterRefProxyModel &&m) = delete;                                 \
        RegisterRefProxyModel &operator=(RegisterRefProxyModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(RegisterRefProxyModel)                                             \
        Q_DISABLE_COPY(RegisterRefProxyModel)                                                      \
        Q_DISABLE_MOVE(RegisterRefProxyModel)
#endif

    Q_DISABLE_COPY_MOVE(RegisterRefProxyModel)

public:
    RegisterRefProxyModel(RegisterRefModel *sourceModel, QObject *parent = nullptr);
    ~RegisterRefProxyModel() override;

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

class RegisterRefsWidget : public CutterDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(RegisterRefsWidget)                                                     \
        RegisterRefsWidget(const RegisterRefsWidget &m) = delete;                                  \
        RegisterRefsWidget &operator=(const RegisterRefsWidget &m) = delete;

#    define Q_DISABLE_MOVE(RegisterRefsWidget)                                                     \
        RegisterRefsWidget(RegisterRefsWidget &&m) = delete;                                       \
        RegisterRefsWidget &operator=(RegisterRefsWidget &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(RegisterRefsWidget)                                                \
        Q_DISABLE_COPY(RegisterRefsWidget)                                                         \
        Q_DISABLE_MOVE(RegisterRefsWidget)
#endif

    Q_DISABLE_COPY_MOVE(RegisterRefsWidget)

public:
    explicit RegisterRefsWidget(MainWindow *main);
    ~RegisterRefsWidget() override;

private slots:
    void on_registerRefTreeView_doubleClicked(const QModelIndex &index);
    void refreshRegisterRef();
    void copyClip(int column);
    void customMenuRequested(QPoint pos);
    void onCurrentChanged(const QModelIndex &current, const QModelIndex &previous);

private:
    std::unique_ptr<Ui::RegisterRefsWidget> ui;

    RegisterRefModel *registerRefModel;
    RegisterRefProxyModel *registerRefProxyModel;
    QList<RegisterRefDescription> registerRefs;
    CutterTreeWidget *tree;
    void setScrollMode();

    RefreshDeferrer *refreshDeferrer;

    QAction *actionCopyValue;
    QAction *actionCopyRef;
    AddressableItemContextMenu addressableItemContextMenu;
};
