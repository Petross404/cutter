#pragma once

#include <QTextEdit>
#include <QPlainTextEdit>
#include <QGridLayout>
#include <QJsonObject>
#include <memory>

#include "core/Cutter.h"
#include "CutterDockWidget.h"
#include "menus/AddressableItemContextMenu.h"

class MainWindow;

namespace Ui {
class RegistersWidget;
}

class RegistersWidget : public CutterDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(RegistersWidget)                                                        \
        RegistersWidget(const RegistersWidget &w) = delete;                                        \
        RegistersWidget &operator=(const RegistersWidget &w) = delete;

#    define Q_DISABLE_MOVE(RegistersWidget)                                                        \
        RegistersWidget(RegistersWidget &&w) = delete;                                             \
        RegistersWidget &operator=(RegistersWidget &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(RegistersWidget)                                                   \
        Q_DISABLE_COPY(RegistersWidget)                                                            \
        Q_DISABLE_MOVE(RegistersWidget)
#endif

    Q_DISABLE_COPY_MOVE(RegistersWidget)

public:
    explicit RegistersWidget(MainWindow *main);
    ~RegistersWidget() override;

private slots:
    void updateContents();
    void setRegisterGrid();
    void openContextMenu(QPoint point, QString address);

private:
    std::unique_ptr<Ui::RegistersWidget> ui;
    QGridLayout *registerLayout = new QGridLayout;
    AddressableItemContextMenu addressContextMenu;
    int numCols = 2;
    int registerLen = 0;
    RefreshDeferrer *refreshDeferrer;
};
