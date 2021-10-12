
#ifndef QUICKFILTERVIEW_H
#define QUICKFILTERVIEW_H

#include "core/CutterCommon.h"

#include <memory>

#include <QWidget>

namespace Ui {
class QuickFilterView;
}

class CUTTER_EXPORT QuickFilterView : public QWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(QuickFilterView)                                                        \
        QuickFilterView(const QuickFilterView &w) = delete;                                        \
        QuickFilterView &operator=(const QuickFilterView &w) = delete;

#    define Q_DISABLE_MOVE(QuickFilterView)                                                        \
        QuickFilterView(QuickFilterView &&w) = delete;                                             \
        QuickFilterView &operator=(QuickFilterView &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(QuickFilterView)                                                   \
        Q_DISABLE_COPY(QuickFilterView)                                                            \
        Q_DISABLE_MOVE(QuickFilterView)
#endif

    Q_DISABLE_COPY_MOVE(QuickFilterView)

public:
    explicit QuickFilterView(QWidget *parent = nullptr, bool defaultOn = true);
    ~QuickFilterView() override;

public slots:
    void showFilter();
    void closeFilter();
    void clearFilter();

signals:
    void filterTextChanged(const QString &text);
    void filterClosed();

private:
    std::unique_ptr<Ui::QuickFilterView> ui;
};

#endif // QUICKFILTERVIEW_H
