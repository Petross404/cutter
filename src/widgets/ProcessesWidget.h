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
class ProcessesWidget;
}

class ProcessesFilterModel : public QSortFilterProxyModel
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(ProcessesFilterModel)                                                   \
        ProcessesFilterModel(const ProcessesFilterModel &w) = delete;                              \
        ProcessesFilterModel &operator=(const ProcessesFilterModel &w) = delete;

#    define Q_DISABLE_MOVE(ProcessesFilterModel)                                                   \
        ProcessesFilterModel(ProcessesFilterModel &&w) = delete;                                   \
        ProcessesFilterModel &operator=(ProcessesFilterModel &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(ProcessesFilterModel)                                              \
        Q_DISABLE_COPY(ProcessesFilterModel)                                                       \
        Q_DISABLE_MOVE(ProcessesFilterModel)
#endif

    Q_DISABLE_COPY_MOVE(ProcessesFilterModel)

public:
    ProcessesFilterModel(QObject *parent = nullptr);
    ~ProcessesFilterModel() override;

protected:
    bool filterAcceptsRow(int row, const QModelIndex &parent) const override;
};

class ProcessesWidget : public CutterDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(ProcessesWidget)                                                        \
        ProcessesWidget(const ProcessesWidget &w) = delete;                                        \
        ProcessesWidget &operator=(const ProcessesWidget &w) = delete;

#    define Q_DISABLE_MOVE(ProcessesWidget)                                                        \
        ProcessesWidget(ProcessesWidget &&w) = delete;                                             \
        ProcessesWidget &operator=(ProcessesWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(ProcessesWidget)                                                   \
        Q_DISABLE_COPY(ProcessesWidget)                                                            \
        Q_DISABLE_MOVE(ProcessesWidget)
#endif

    Q_DISABLE_COPY_MOVE(ProcessesWidget)

public:
    explicit ProcessesWidget(MainWindow *main);
    ~ProcessesWidget() override;

private slots:
    void updateContents();
    void setProcessesGrid();
    void fontsUpdatedSlot();
    void onActivated(const QModelIndex &index);

private:
    QString translateStatus(QString status);
    std::unique_ptr<Ui::ProcessesWidget> ui;
    QStandardItemModel *modelProcesses;
    ProcessesFilterModel *modelFilter;
    RefreshDeferrer *refreshDeferrer;
};
