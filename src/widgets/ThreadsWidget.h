#pragma once

#include <QJsonObject>
#include <memory>
#include <QStandardItem>
#include <QTableView>
#include <QSortFilterProxyModel>

#include "core/Cutter.h"
#include "CutterDockWidget.h"

class MainWindow;

namespace Ui {
class ThreadsWidget;
}

class ThreadsFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(ThreadsFilterModel)                                                     \
        ThreadsFilterModel(const ThreadsFilterModel &m) = delete;                                  \
        ThreadsFilterModel &operator=(const ThreadsFilterModel &m) = delete;

#    define Q_DISABLE_MOVE(ThreadsFilterModel)                                                     \
        ThreadsFilterModel(ThreadsFilterModel &&m) = delete;                                       \
        ThreadsFilterModel &operator=(ThreadsFilterModel &&m) = delete;

#    define Q_DISABLE_COPY_MOVE(ThreadsFilterModel)                                                \
        Q_DISABLE_COPY(ThreadsFilterModel)                                                         \
        Q_DISABLE_MOVE(ThreadsFilterModel)
#endif

    Q_DISABLE_COPY_MOVE(ThreadsFilterModel)

public:
    ThreadsFilterModel(QObject *parent = nullptr);
    ~ThreadsFilterModel() override;

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
};

class ThreadsWidget : public CutterDockWidget
{
    Q_OBJECT
#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(ThreadsWidget)                                                          \
        ThreadsWidget(const ThreadsWidget &w) = delete;                                            \
        ThreadsWidget &operator=(const ThreadsWidget &w) = delete;

#    define Q_DISABLE_MOVE(ThreadsWidget)                                                          \
        ThreadsWidget(ThreadsWidget &&w) = delete;                                                 \
        ThreadsWidget &operator=(ThreadsWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(ThreadsWidget)                                                     \
        Q_DISABLE_COPY(ThreadsWidget)                                                              \
        Q_DISABLE_MOVE(ThreadsWidget)
#endif

    Q_DISABLE_COPY_MOVE(ThreadsWidget)

public:
    explicit ThreadsWidget(MainWindow *main);
    ~ThreadsWidget() override;

private slots:
    void updateContents();
    void setThreadsGrid();
    void fontsUpdatedSlot();
    void onActivated(const QModelIndex &index);

private:
    QString translateStatus(QString status);
    std::unique_ptr<Ui::ThreadsWidget> ui;
    QStandardItemModel *modelThreads;
    ThreadsFilterModel *modelFilter;
    RefreshDeferrer *refreshDeferrer;
};
