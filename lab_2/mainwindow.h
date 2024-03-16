#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    Record records[2];

    int selectedRecord = 0;

    void showNote(int idx);

    void saveNote(int idx);

private slots:
    void showFirstNote();
    void showSecondNote();

    void saveFirstNote();
    void saveSecondNote();

    void toggleTuitionFee(double compitition);

    bool validateDate();
};
#endif // MAINWINDOW_H
