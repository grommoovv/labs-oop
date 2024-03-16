#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <record.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    Record records[100];

    int currentRecord = 0;

    int recordsCount = 0;

    int selectedRecord = 0;

    virtual bool eventFilter(QObject *watched, QEvent *event) override;

private slots:
    void onCreate();

    void onFill();

    void onSave();

    void onSelectListItem(QListWidgetItem* item);

    void onDelete();

    void handleSelectUni();

    void toggleTuitionFee(double compitition);

    bool validateDate();
};
#endif // MAINWINDOW_H
