#pragma once

#include "core/Cutter.h"
#include "dialogs/RemoteDebugDialog.h"

#include <QAction>

class MainWindow;
class QToolBar;
class QToolButton;

class DebugActions : public QObject
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(DebugActions)                                                           \
        DebugActions(const DebugActions &w) = delete;                                              \
        DebugActions &operator=(const DebugActions &w) = delete;

#    define Q_DISABLE_MOVE(DebugActions)                                                           \
        DebugActions(DebugActions &&w) = delete;                                                   \
        DebugActions &operator=(DebugActions &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(DebugActions)                                                      \
        Q_DISABLE_COPY(DebugActions)                                                               \
        Q_DISABLE_MOVE(DebugActions)
#endif

    Q_DISABLE_COPY_MOVE(DebugActions)

public:
    explicit DebugActions(QToolBar *toolBar, MainWindow *main);
    ~DebugActions() override;

    void addToToolBar(QToolBar *toolBar);

    QAction *actionStart;
    QAction *actionStartRemote;
    QAction *actionStartEmul;
    QAction *actionAttach;
    QAction *actionContinue;
    QAction *actionContinueUntilMain;
    QAction *actionContinueUntilCall;
    QAction *actionContinueUntilSyscall;
    QAction *actionContinueBack;
    QAction *actionStep;
    QAction *actionStepOver;
    QAction *actionStepOut;
    QAction *actionStepBack;
    QAction *actionStop;
    QAction *actionAllContinues;
    QAction *actionTrace;

    // Continue/suspend and start/restart interchange during runtime
    QIcon continueIcon;
    QIcon suspendIcon;
    QIcon restartIcon;
    QIcon startDebugIcon;
    QIcon startTraceIcon;
    QIcon stopTraceIcon;
    QString continueLabel;
    QString suspendLabel;
    QString restartDebugLabel;
    QString startDebugLabel;
    QString startTraceLabel;
    QString stopTraceLabel;

    // Stop and Detach interchange during runtime
    QIcon detachIcon;
    QIcon stopIcon;

private:
    /**
     * @brief buttons that will be disabled/enabled on (disable/enable)DebugToolbar
     */
    QList<QAction *> toggleActions;
    QList<QAction *> toggleConnectionActions;
    QList<QAction *> reverseActions;
    QList<QAction *> allActions;
    QToolButton *continueUntilButton;
    RemoteDebugDialog *remoteDialog = nullptr;
    MainWindow *main;
    bool acceptedDebugWarning = false;

    // TODO: Remove once debug is stable
    void showDebugWarning();

private slots:
    void continueUntilMain();
    void startDebug();
    void attachProcessDialog();
    void attachProcess(int pid);
    void attachRemoteDialog();
    void attachRemoteDebugger();
    void onAttachedRemoteDebugger(bool successfully);
    void setAllActionsVisible(bool visible);
    void setButtonVisibleIfMainExists();
    void chooseThemeIcons();
};
