#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include <QMessageBox>
#include <QDate>
#include <record.h>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->fee->setEnabled(false);

    ui->startDate->setMinimumDate(QDate(QDate::currentDate().year(), 1, 1));
    ui->startDate->setMaximumDate(QDate(QDate::currentDate().year(), 11, 30));
    ui->endDate->setMinimumDate(QDate(QDate::currentDate().year(), 1, 1));
    ui->endDate->setMaximumDate(QDate(QDate::currentDate().year(), 12, 30));

    connect(ui->compitition, SIGNAL(valueChanged(double)), this, SLOT(toggleTuitionFee(double)));
    connect(ui->startDate, SIGNAL(dateChanged(QDate)), this, SLOT(validateDate()));
    connect(ui->endDate, SIGNAL(dateChanged(QDate)), this, SLOT(validateDate()));
    connect(ui->show_note_1, SIGNAL(clicked()), this, SLOT(showFirstNote()));
    connect(ui->show_note_2, SIGNAL(clicked()), this, SLOT(showSecondNote()));
    connect(ui->save_note_1, SIGNAL(clicked()), this, SLOT(saveFirstNote()));
    connect(ui->save_note_2, SIGNAL(clicked()), this, SLOT(saveSecondNote()));

    // Validators
    QRegExp regex("[А-Яа-я ]{1,50}");
    QRegExpValidator *v = new QRegExpValidator(regex, this);
    ui->spec->setValidator(v);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::showNote(int idx)
{
//    qDebug() << "Current Note Index:" << idx;

//    QString uni = records[idx].getUni();
//    QString spec = records[idx].getSpec();
//    double comp = records[idx].getCompetition();
//    int fee = records[idx].getFee();
//    bool isMaster = records[idx].getIsMasters();
//    QDate startDate = records[idx].getStartDate();
//    QDate endDate = records[idx].getEndDate();

//    qDebug() << "NOTE SHOWN:";
//    qDebug() << "uni:" << uni;
//    qDebug() << "spec:" << spec;
//    qDebug() << "comp:" << comp;
//    qDebug() << "fee:" << fee;
//    qDebug() << "isMaster:" << isMaster;
//    qDebug() << "startDate:" << startDate;
//    qDebug() << "endDate:" << endDate;

    ui->uni->setCurrentText(records[idx].getUni());
    ui->spec->setText(records[idx].getSpec());
    ui->compitition->setValue(records[idx].getCompetition());
    ui->fee->setValue(records[idx].getFee());
    ui->master->setChecked(records[idx].getIsMasters());
    ui->startDate->setDate(records[idx].getStartDate());
    ui->endDate->setDate(records[idx].getEndDate());

    ui->statusbar->showMessage(QString("Выбранная запись: %1").arg(selectedRecord + 1));
}

void MainWindow::showFirstNote()
{
    this->selectedRecord = 0;
    showNote(selectedRecord);
}

void MainWindow::showSecondNote()
{
    this->selectedRecord = 1;
    showNote(selectedRecord);
}

void MainWindow::saveNote(int idx)
{
//    int uniIdx = ui->uni->currentIndex();
//    QString spec = ui->spec->text();
//    double comp = ui->compitition->value();
//    int fee = ui->fee->value();
//    bool isMaster = ui->master->isChecked();
//    QDate startDate = ui->startDate->date();
//    QDate endDate = ui->endDate->date();

//    qDebug() << "NOTE SAVED:";
//    qDebug() << "uniIdx:" << uniIdx;
//    qDebug() << "spec:" << spec;
//    qDebug() << "comp:" << comp;
//    qDebug() << "fee:" << fee;
//    qDebug() << "isMaster:" << isMaster;
//    qDebug() << "startDate:" << startDate;
//    qDebug() << "endDate:" << endDate;

    bool isInputValid = ui->spec->hasAcceptableInput();

    bool isDataValid = validateDate();

    if (!isInputValid && isDataValid)
    {
        QMessageBox::warning(this, "Ошибка!", "Не удалось сохранить запись. Проверьте правильность написания специальности", QMessageBox::Ok);
        return;
    }


    if (!isDataValid && isInputValid)
    {
        QMessageBox::warning(this, "Ошибка!", "Не удалось сохранить запись. Проверьте правильность написания даты", QMessageBox::Ok);
        return;
    }

    if (!isDataValid && !isInputValid)
    {
        QMessageBox::warning(this, "Ошибка!", "Не удалось сохранить запись. Проверьте правильность написания даты и специальности", QMessageBox::Ok);
        return;
    }

    records[idx].setUni(ui->uni->currentText());
    records[idx].setSpec(ui->spec->text());
    records[idx].setCompetition(ui->compitition->value());
    records[idx].setFee(ui->fee->value());
    records[idx].setIsMasters(ui->master->isChecked());
    records[idx].setStartDate(ui->startDate->date());
    records[idx].setEndDate(ui->endDate->date());
}

void MainWindow::saveFirstNote()
{
    this->selectedRecord = 0;
    saveNote(selectedRecord);
}

void MainWindow::saveSecondNote()
{
    this->selectedRecord = 1;
    saveNote(selectedRecord);
}

void MainWindow::toggleTuitionFee(double comp)
{
    ui->fee->setEnabled(comp > 1);
}

bool MainWindow::validateDate()
{
    int currentYear = QDate::currentDate().year();
    int startYear = ui->startDate->date().year();

    int startMonth = ui->startDate->date().month();
    int endMonth = ui->endDate->date().month();

    if (startYear != currentYear )
    {
        QMessageBox::warning(this, "Предупреждение!", "Прием документов проводится в 2024 году!", QMessageBox::Ok);
        return false;
    }

    if (endMonth < startMonth)
    {
        QMessageBox::warning(this, "Предупреждение!", "Окончание подачи документов не может быть раньше, чем начало!", QMessageBox::Ok);
        return false;
    }

    if (endMonth - startMonth > 1)
    {
        QMessageBox::warning(this, "Предупреждение!", "Длительность подачи документов 1 месяц!", QMessageBox::Ok);
        return false;
    }

    return true;
}
