#ifndef OMNIBAR_H
#define OMNIBAR_H

#include <QLineEdit>

class MainWindow;

class Omnibar : public QLineEdit
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(Omnibar)                                                                \
        Omnibar(const Omnibar &w) = delete;                                                        \
        Omnibar &operator=(const Omnibar &w) = delete;

#    define Q_DISABLE_MOVE(Omnibar)                                                                \
        Omnibar(Omnibar &&w) = delete;                                                             \
        Omnibar &operator=(Omnibar &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(Omnibar)                                                           \
        Q_DISABLE_COPY(Omnibar)                                                                    \
        Q_DISABLE_MOVE(Omnibar)
#endif

    Q_DISABLE_COPY_MOVE(Omnibar)

public:
    explicit Omnibar(MainWindow *main, QWidget *parent = nullptr);
    ~Omnibar() override;

    void refresh(const QStringList &flagList);

private slots:
    void on_gotoEntry_returnPressed();

    void restoreCompleter();

public slots:
    void clear();

private:
    void setupCompleter();

    MainWindow *main;
    QStringList flags;
};

#endif // OMNIBAR_H
