#ifndef SECTIONSWIDGET_H
#define SECTIONSWIDGET_H

#include <memory>
#include <map>

#include <QtWidgets/QToolButton>
#include <QAbstractListModel>
#include <QSortFilterProxyModel>
#include <QGraphicsScene>
#include <QLabel>
#include <QHash>

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "widgets/ListDockWidget.h"

class QAbstractItemView;
class SectionsWidget;
class AbstractAddrDock;
class AddrDockScene;
class QGraphicsSceneMouseEvent;
class RawAddrDock;
class VirtualAddrDock;
class QuickFilterView;
class QGraphicsView;
class QGraphicsRectItem;

class SectionsModel : public AddressableItemModel<QAbstractListModel>
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(SectionsModel)                                                          \
        SectionsModel(const SectionsModel &m) = delete;                                            \
        SectionsModel &operator=(const SectionsModel &m) = delete;

#    define Q_DISABLE_MOVE(SectionsModel)                                                          \
        SectionsModel(SectionsModel &&m) = delete;                                                 \
        SectionsModel &operator=(SectionsModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(SectionsModel)                                                     \
        Q_DISABLE_COPY(SectionsModel)                                                              \
        Q_DISABLE_MOVE(SectionsModel)
#endif

    Q_DISABLE_COPY_MOVE(SectionsModel)

    friend SectionsWidget;

private:
    QList<SectionDescription> *sections;

public:
    enum Column {
        NameColumn = 0,
        SizeColumn,
        AddressColumn,
        EndAddressColumn,
        VirtualSizeColumn,
        PermissionsColumn,
        EntropyColumn,
        CommentColumn,
        ColumnCount
    };
    enum Role { SectionDescriptionRole = Qt::UserRole };

    SectionsModel(QList<SectionDescription> *sections, QObject *parent = nullptr);
    ~SectionsModel() override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    RVA address(const QModelIndex &index) const override;
    QString name(const QModelIndex &index) const override;
};

class SectionsProxyModel : public AddressableFilterProxyModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(SectionsProxyModel)                                                     \
        SectionsProxyModel(const SectionsProxyModel &w) = delete;                                  \
        SectionsProxyModel &operator=(const SectionsProxyModel &w) = delete;

#    define Q_DISABLE_MOVE(SectionsProxyModel)                                                     \
        SectionsProxyModel(SectionsProxyModel &&w) = delete;                                       \
        SectionsProxyModel &operator=(SectionsProxyModel &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(SectionsProxyModel)                                                \
        Q_DISABLE_COPY(SectionsProxyModel)                                                         \
        Q_DISABLE_MOVE(SectionsProxyModel)
#endif

    Q_DISABLE_COPY_MOVE(SectionsProxyModel)

public:
    SectionsProxyModel(SectionsModel *sourceModel, QObject *parent = nullptr);
    ~SectionsProxyModel() override;

protected:
    bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
};

class SectionsWidget : public ListDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(SectionsWidget)                                                         \
        SectionsWidget(const SectionsWidget &w) = delete;                                          \
        SectionsWidget &operator=(const SectionsWidget &w) = delete;

#    define Q_DISABLE_MOVE(SectionsWidget)                                                         \
        SectionsWidget(SectionsWidget &&w) = delete;                                               \
        SectionsWidget &operator=(SectionsWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(SectionsWidget)                                                    \
        Q_DISABLE_COPY(SectionsWidget)                                                             \
        Q_DISABLE_MOVE(SectionsWidget)
#endif

    Q_DISABLE_COPY_MOVE(SectionsWidget)

public:
    explicit SectionsWidget(MainWindow *main);
    ~SectionsWidget() override;

private slots:
    void refreshSections();
    void refreshDocks();

protected:
    void resizeEvent(QResizeEvent *event) override;

private:
    QList<SectionDescription> sections;
    SectionsModel *sectionsModel;
    SectionsProxyModel *proxyModel;

    QWidget *addrDockWidget;
    RawAddrDock *rawAddrDock;
    VirtualAddrDock *virtualAddrDock;
    QToolButton *toggleButton;

    /**
     * RefreshDeferrer for loading the section data
     */
    RefreshDeferrer *sectionsRefreshDeferrer;

    /**
     * RefreshDeferrer for updating the visualization docks
     */
    RefreshDeferrer *dockRefreshDeferrer;

    void initSectionsTable();
    void initQuickFilter();
    void initConnects();
    void initAddrMapDocks();
    void drawIndicatorOnAddrDocks();
    void updateToggle();
};

class AbstractAddrDock : public QDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(AbstractAddrDock)                                                       \
        AbstractAddrDock(const AbstractAddrDock &w) = delete;                                      \
        AbstractAddrDock &operator=(const AbstractAddrDock &w) = delete;

#    define Q_DISABLE_MOVE(AbstractAddrDock)                                                       \
        AbstractAddrDock(AbstractAddrDock &&w) = delete;                                           \
        AbstractAddrDock &operator=(AbstractAddrDock &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(AbstractAddrDock)                                                  \
        Q_DISABLE_COPY(AbstractAddrDock)                                                           \
        Q_DISABLE_MOVE(AbstractAddrDock)
#endif

    Q_DISABLE_COPY_MOVE(AbstractAddrDock)

    friend SectionsWidget;

public:
    explicit AbstractAddrDock(SectionsModel *model, QWidget *parent = nullptr);
    ~AbstractAddrDock() override;

    virtual void updateDock();

protected:
    int indicatorHeight;
    int indicatorParamPosY;
    float heightThreshold;
    float heightDivisor;
    int rectOffset;
    int rectWidthMin;
    int rectWidthMax;
    QColor indicatorColor;
    QColor textColor;
    AddrDockScene *addrDockScene;
    QGraphicsView *graphicsView;
    SectionsProxyModel *proxyModel;

    void addTextItem(QColor color, QPoint pos, QString string);
    int getAdjustedSize(int size, int validMinSize) const;
    int getRectWidth();
    int getIndicatorWidth();
    int getValidMinSize();

    virtual RVA getSizeOfSection(const SectionDescription &section) = 0;
    virtual RVA getAddressOfSection(const SectionDescription &section) = 0;

private:
    void drawIndicator(const QString &name, float ratio);
};

class AddrDockScene : public QGraphicsScene
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(AddrDockScene)                                                          \
        AddrDockScene(const AddrDockScene &w) = delete;                                            \
        AddrDockScene &operator=(const AddrDockScene &w) = delete;

#    define Q_DISABLE_MOVE(AddrDockScene)                                                          \
        AddrDockScene(AddrDockScene &&w) = delete;                                                 \
        AddrDockScene &operator=(AddrDockScene &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(AddrDockScene)                                                     \
        Q_DISABLE_COPY(AddrDockScene)                                                              \
        Q_DISABLE_MOVE(AddrDockScene)
#endif

    Q_DISABLE_COPY_MOVE(AddrDockScene)

public:
    explicit AddrDockScene(QWidget *parent = nullptr);
    ~AddrDockScene() override;

    bool disableCenterOn;

    QHash<QString, RVA> nameAddrMap;
    QHash<QString, RVA> nameAddrSizeMap;
    QHash<QString, RVA> seekAddrMap;
    QHash<QString, RVA> seekAddrSizeMap;
    QHash<QString, int> namePosYMap;
    QHash<QString, int> nameHeightMap;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

private:
    RVA getAddrFromPos(int posY, bool seek);
};

class RawAddrDock : public AbstractAddrDock
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(RawAddrDock)                                                            \
        RawAddrDock(const RawAddrDock &w) = delete;                                                \
        RawAddrDock &operator=(const RawAddrDock &w) = delete;

#    define Q_DISABLE_MOVE(RawAddrDock)                                                            \
        RawAddrDock(RawAddrDock &&w) = delete;                                                     \
        RawAddrDock &operator=(RawAddrDock &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(RawAddrDock)                                                       \
        Q_DISABLE_COPY(RawAddrDock)                                                                \
        Q_DISABLE_MOVE(RawAddrDock)
#endif

    Q_DISABLE_COPY_MOVE(RawAddrDock)

public:
    explicit RawAddrDock(SectionsModel *model, QWidget *parent = nullptr);
    ~RawAddrDock() override;

    void updateDock() override;

protected:
    RVA getSizeOfSection(const SectionDescription &section) override { return section.size; };
    RVA getAddressOfSection(const SectionDescription &section) override { return section.paddr; };
};

class VirtualAddrDock : public AbstractAddrDock
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(VirtualAddrDock)                                                        \
        VirtualAddrDock(const VirtualAddrDock &w) = delete;                                        \
        VirtualAddrDock &operator=(const VirtualAddrDock &w) = delete;

#    define Q_DISABLE_MOVE(VirtualAddrDock)                                                        \
        VirtualAddrDock(VirtualAddrDock &&w) = delete;                                             \
        VirtualAddrDock &operator=(VirtualAddrDock &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(VirtualAddrDock)                                                   \
        Q_DISABLE_COPY(VirtualAddrDock)                                                            \
        Q_DISABLE_MOVE(VirtualAddrDock)
#endif

    Q_DISABLE_COPY_MOVE(VirtualAddrDock)

public:
    explicit VirtualAddrDock(SectionsModel *model, QWidget *parent = nullptr);
    ~VirtualAddrDock() override;

    void updateDock() override;

protected:
    RVA getSizeOfSection(const SectionDescription &section) override { return section.vsize; };
    RVA getAddressOfSection(const SectionDescription &section) override { return section.vaddr; };
};

#endif // SECTIONSWIDGET_H
