#ifndef STRINGSWIDGET_H
#define STRINGSWIDGET_H

#include <memory>

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "common/StringsTask.h"
#include "CutterTreeWidget.h"
#include "AddressableItemModel.h"

#include <QAbstractListModel>
#include <QSortFilterProxyModel>

class MainWindow;
class QTreeWidgetItem;
class StringsWidget;

namespace Ui {
class StringsWidget;
}

class StringsModel : public AddressableItemModel<QAbstractListModel>
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(StringsModel)                                                           \
        StringsModel(const StringsModel &m) = delete;                                              \
        StringsModel &operator=(const StringsModel &m) = delete;

#    define Q_DISABLE_MOVE(StringsModel)                                                           \
        StringsModel(StringsModel &&m) = delete;                                                   \
        StringsModel &operator=(StringsModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(StringsModel)                                                      \
        Q_DISABLE_COPY(StringsModel)                                                               \
        Q_DISABLE_MOVE(StringsModel)
#endif

    Q_DISABLE_COPY_MOVE(StringsModel)

    friend StringsWidget;

private:
    QList<StringDescription> *strings;

public:
    enum Column {
        OffsetColumn = 0,
        StringColumn,
        TypeColumn,
        LengthColumn,
        SizeColumn,
        SectionColumn,
        CommentColumn,
        ColumnCount
    };
    static const int StringDescriptionRole = Qt::UserRole;

    StringsModel(QList<StringDescription> *strings, QObject *parent = nullptr);
    ~StringsModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    RVA address(const QModelIndex &index) const override;
    const StringDescription *description(const QModelIndex &index) const;
};

class StringsProxyModel : public AddressableFilterProxyModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(StringsProxyModel)                                                      \
        StringsProxyModel(const StringsProxyModel &w) = delete;                                    \
        StringsProxyModel &operator=(const StringsProxyModel &w) = delete;

#    define Q_DISABLE_MOVE(StringsProxyModel)                                                      \
        StringsProxyModel(StringsProxyModel &&w) = delete;                                         \
        StringsProxyModel &operator=(StringsProxyModel &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(StringsProxyModel)                                                 \
        Q_DISABLE_COPY(StringsProxyModel)                                                          \
        Q_DISABLE_MOVE(StringsProxyModel)
#endif

    Q_DISABLE_COPY_MOVE(StringsProxyModel)

public:
    StringsProxyModel(StringsModel *sourceModel, QObject *parent = nullptr);
    ~StringsProxyModel() override;

    void setSelectedSection(QString section);

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

    QString selectedSection;
};

class StringsWidget : public CutterDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(StringsWidget)                                                          \
        StringsWidget(const StringsWidget &w) = delete;                                            \
        StringsWidget &operator=(const StringsWidget &w) = delete;

#    define Q_DISABLE_MOVE(StringsWidget)                                                          \
        StringsWidget(StringsWidget &&w) = delete;                                                 \
        StringsWidget &operator=(StringsWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(StringsWidget)                                                     \
        Q_DISABLE_COPY(StringsWidget)                                                              \
        Q_DISABLE_MOVE(StringsWidget)
#endif

    Q_DISABLE_COPY_MOVE(StringsWidget)

public:
    explicit StringsWidget(MainWindow *main);
    ~StringsWidget() override;

private slots:
    void refreshStrings();
    void stringSearchFinished(const QList<StringDescription> &strings);
    void refreshSectionCombo();

    void on_actionCopy();

private:
    std::unique_ptr<Ui::StringsWidget> ui;

    QSharedPointer<StringsTask> task;

    StringsModel *model;
    StringsProxyModel *proxyModel;
    QList<StringDescription> strings;
    CutterTreeWidget *tree;
};

#endif // STRINGSWIDGET_H
