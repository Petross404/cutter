#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QFormLayout>
#include <memory>
#include "CutterDockWidget.h"

QT_BEGIN_NAMESPACE
QT_FORWARD_DECLARE_CLASS(QLineEdit)
QT_FORWARD_DECLARE_CLASS(QJsonObject)
QT_END_NAMESPACE

class MainWindow;

namespace Ui {
class Dashboard;
}

class Dashboard : public CutterDockWidget
{
    Q_OBJECT

#if QT_VERSION < QT_VERSION_CHECK(5, 13, 0)
#    define Q_DISABLE_COPY(Dashboard)                                                              \
        Dashboard(const Dashboard &w) = delete;                                                    \
        Dashboard &operator=(const Dashboard &w) = delete;

#    define Q_DISABLE_MOVE(Dashboard)                                                              \
        Dashboard(Dashboard &&w) = delete;                                                         \
        Dashboard &operator=(Dashboard &&w) = delete;

#    define Q_DISABLE_COPY_MOVE(Dashboard)                                                         \
        Q_DISABLE_COPY(Dashboard)                                                                  \
        Q_DISABLE_MOVE(Dashboard)
#endif

    Q_DISABLE_COPY_MOVE(Dashboard)

public:
    explicit Dashboard(MainWindow *main);
    ~Dashboard() override;

private slots:
    void updateContents();
    void on_certificateButton_clicked();
    void on_versioninfoButton_clicked();

private:
    std::unique_ptr<Ui::Dashboard> ui;
    void setPlainText(QLineEdit *textBox, const QString &text);
    void setBool(QLineEdit *textBox, const QJsonObject &jsonObject, const QString &key);

    QWidget *hashesWidget = nullptr;
};

#endif // DASHBOARD_H
