#ifndef TYPESWIDGET_H
#define TYPESWIDGET_H

#include <memory>

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "CutterTreeWidget.h"

#include <QAbstractListModel>
#include <QSortFilterProxyModel>

class MainWindow;
class QTreeWidget;
class TypesWidget;

namespace Ui {
class TypesWidget;
}

class MainWindow;
class QTreeWidgetItem;

class TypesModel : public QAbstractListModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(TypesModel)                                                             \
        TypesModel(const TypesModel &m) = delete;                                                  \
        TypesModel &operator=(const TypesModel &m) = delete;

#    define Q_DISABLE_MOVE(TypesModel)                                                             \
        TypesModel(TypesModel &&m) = delete;                                                       \
        TypesModel &operator=(TypesModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(TypesModel)                                                        \
        Q_DISABLE_COPY(TypesModel)                                                                 \
        Q_DISABLE_MOVE(TypesModel)
#endif

    Q_DISABLE_COPY_MOVE(TypesModel)

    friend TypesWidget;

private:
    QList<TypeDescription> *types;

public:
    enum Columns { TYPE = 0, SIZE, CATEGORY, FORMAT, COUNT };
    static const int TypeDescriptionRole = Qt::UserRole;

    TypesModel(QList<TypeDescription> *types, QObject *parent = nullptr);
    ~TypesModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
};

class TypesSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(TypesSortFilterProxyModel)                                              \
        TypesSortFilterProxyModel(const TypesSortFilterProxyModel &w) = delete;                    \
        TypesSortFilterProxyModel &operator=(const TypesSortFilterProxyModel &w) = delete;

#    define Q_DISABLE_MOVE(TypesSortFilterProxyModel)                                              \
        TypesSortFilterProxyModel(TypesSortFilterProxyModel &&w) = delete;                         \
        TypesSortFilterProxyModel &operator=(TypesSortFilterProxyModel &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(TypesSortFilterProxyModel)                                         \
        Q_DISABLE_COPY(TypesSortFilterProxyModel)                                                  \
        Q_DISABLE_MOVE(TypesSortFilterProxyModel)
#endif

    Q_DISABLE_COPY_MOVE(TypesSortFilterProxyModel)

public:
    TypesSortFilterProxyModel(TypesModel *source_model, QObject *parent = nullptr);
    ~TypesSortFilterProxyModel() override;

    void setCategory(QString category);

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

    QString selectedCategory;
};

class TypesWidget : public CutterDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(TypesWidget)                                                            \
        TypesWidget(const TypesWidget &w) = delete;                                                \
        TypesWidget &operator=(const TypesWidget &w) = delete;

#    define Q_DISABLE_MOVE(TypesWidget)                                                            \
        TypesWidget(TypesWidget &&w) = delete;                                                     \
        TypesWidget &operator=(TypesWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(TypesWidget)                                                       \
        Q_DISABLE_COPY(TypesWidget)                                                                \
        Q_DISABLE_MOVE(TypesWidget)
#endif

    Q_DISABLE_COPY_MOVE(TypesWidget)

public:
    explicit TypesWidget(MainWindow *main);
    ~TypesWidget() override;

private slots:
    void refreshTypes();

    /**
     * @brief Show custom context menu
     * @param pt Position of the place where the right mouse button was clicked
     */
    void showTypesContextMenu(const QPoint &pt);

    /**
     * @brief Executed on clicking the Export Types option in the context menu
     * It shows the user a file dialog box to select a file where the types
     * will be exported.
     */
    void on_actionExport_Types_triggered();

    /**
     * @brief Executed on clicking the Load New types option in the context menu
     * It will open the TypesInteractionDialog where the user can either enter the
     * types manually, or can select a file from where the types will be loaded
     */
    void on_actionLoad_New_Types_triggered();

    /**
     * @brief Executed on clicking either the Edit Type or View Type options in the context menu
     * It will open the TypesInteractionDialog filled with the selected type. Depends on Edit or
     * View mode the text view would be read-only or not.
     */
    void viewType(bool readOnly = true);

    /**
     * @brief Executed on clicking the Delete Type option in the context menu
     * Upon confirmation from the user, it will delete the selected type.
     */
    void on_actionDelete_Type_triggered();

    /**
     * @brief triggers when the user double-clicks an item. This will open
     * a dialog that shows the Type's content
     */
    void typeItemDoubleClicked(const QModelIndex &index);

private:
    std::unique_ptr<Ui::TypesWidget> ui;

    TypesModel *types_model;
    TypesSortFilterProxyModel *types_proxy_model;
    QList<TypeDescription> types;
    CutterTreeWidget *tree;
    QAction *actionViewType;
    QAction *actionEditType;

    void setScrollMode();

    /**
     * @brief Sets the contents of the ComboBox to the supplied contents
     * @param categories The list of categories which has to be added to the ComboBox
     */
    void refreshCategoryCombo(const QStringList &categories);
};

#endif // TYPESWIDGET_H
