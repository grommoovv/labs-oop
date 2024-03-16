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

//    ui->uni->installEventFilter(this);
//    ui->spec->installEventFilter(this);
//    ui->compitition->installEventFilter(this);
//    ui->fee->installEventFilter(this);
//    ui->master->installEventFilter(this);
//    ui->startDate->installEventFilter(this);
//    ui->endDate->installEventFilter(this);

    connect(ui->uni, SIGNAL(currentIndexChanged(int)), this, SLOT(handleSelectUni(int)));

    connect(ui->compitition, SIGNAL(valueChanged(double)), this, SLOT(toggleTuitionFee(double)));

    connect(ui->startDate, SIGNAL(dateChanged(QDate)), this, SLOT(checkDate()));
    connect(ui->endDate, SIGNAL(dateChanged(QDate)), this, SLOT(checkDate()));

    connect(ui->listWidget, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(onSelectListItem(QListWidgetItem*)));

    connect(ui->createBtn, SIGNAL(clicked()), this, SLOT(onCreate()));
    connect(ui->fillBtn, SIGNAL(clicked()), this, SLOT(onFill()));
    connect(ui->saveBtn, SIGNAL(clicked()), this, SLOT(onSave()));
    connect(ui->deleteBtn, SIGNAL(clicked()), this, SLOT(onDelete()));

    // Validators
    QRegExp regex("[А-Яа-я ]{1,50}");
    QRegExpValidator *v = new QRegExpValidator(regex, this);
    ui->spec->setValidator(v);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::onCreate()
{
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

    if (recordsCount < 100)
    {
        QString uni = ui->uni->currentText();
        QString spec = ui->spec->text();
        double comp = ui->compitition->value();
        int fee = ui->fee->value();
        bool isMaster = ui->master->isChecked();
        QDate startDate = ui->startDate->date();
        QDate endDate = ui->endDate->date();

        records[recordsCount] = Record(uni, spec, comp, fee, isMaster, startDate, endDate);

        QString compitition = QString::number(comp);

        qDebug() << "ON_CREATE:";
        qDebug() << "spec:" << spec;
        qDebug() << "uni:" << uni;
        qDebug() << "compitition:" << compitition;

        QString newRecord = spec + "\t" + uni + "\t" + compitition;

        ui->listWidget->addItem(newRecord);

        ui->spec->clear();
        ui->uni->setCurrentIndex(0);
        ui->compitition->setValue(0);

        recordsCount++;
    }
    else
    {
        qDebug() << "Массив записей заполнен. Невозможно добавить новую запись.";
    }
}

void MainWindow::onFill() {

    QString Unis[10]
    {
        "ВолгГТУ", "ВолгГТУ", "ВолгГТУ", "ВолгГТУ", "ВолгГТУ",
        "ВолГУ", "ВолГУ", "ВолГУ", "ВолГУ", "ВолГУ",
    };

    QString Specs[10]
    {
        "Фронтенд разработчик", "Бекенд разработчик", "Разработчик игр", "Администратор баз данных",
        "Системный аналитик", "Инженер по тестированию", "Мобильный разработчик", "ДевОпс инженер",
        "Юай Юикс дизайнер", "Блокчейн разработчик"
    };

    double Comps[10] { 1.0, 2.0, 3.5, 4.5, 5, 6, 7, 8.5, 13.5, 14 };

    int Fees[10] { 10000, 12000, 14000, 16000, 18000, 20000, 22000, 24000, 26000, 28000 };

    bool Degrees[10] { true, true, true, true, true, false, false, false, false, false, };

    QDate StartDates[10]
    {
        QDate(2024, 1, 5), QDate(2024, 2, 10), QDate(2024, 3, 15), QDate(2024, 4, 20),
        QDate(2024, 5, 25), QDate(2024, 6, 1), QDate(2024, 7, 6), QDate(2024, 8, 11),
        QDate(2024, 9, 16), QDate(2024, 10, 21)
    };

    QDate EndDates[10]
    {
        QDate(2024, 1, 30), QDate(2024, 2, 14), QDate(2024, 3, 30), QDate(2024, 4, 26),
        QDate(2024, 5, 30), QDate(2024, 6, 30), QDate(2024, 7, 28), QDate(2024, 8, 31),
        QDate(2024, 9, 30), QDate(2024, 10, 20)
    };

    int count = 0;
    int maxCount = recordsCount + 10;

    for (int i = recordsCount; i < maxCount && recordsCount < 100; i++, count++)
    {
        records[i] = Record(Unis[count], Specs[count], Comps[count], Fees[count], Degrees[count], StartDates[count], EndDates[count]);

        recordsCount++;

        QString record = Specs[count] + "\t" + Unis[count] + "\t" + QString::number(Comps[count]);

        ui->listWidget->addItem(record);
    }
}

void MainWindow::onSelectListItem(QListWidgetItem* item) {

    int selectedItemIndex = ui->listWidget->row(item);

//    QString uni = records[selectedItemIndex].getUni();
//    QString spec = records[selectedItemIndex].getSpec();
//    double comp = records[selectedItemIndex].getCompetition();
//    int fee = records[selectedItemIndex].getFee();
//    bool isMasters = records[selectedItemIndex].getIsMasters();
//    QDate startDate = records[selectedItemIndex].getStartDate();
//    QDate endDate = records[selectedItemIndex].getEndDate();

    qDebug() << "ON_SELECT:";
    qDebug() << "records count:" << recordsCount;
    qDebug() << "index:" << selectedItemIndex;
//    qDebug() << "uni :" << spec;
//    qDebug() << "spec :" << spec;
//    qDebug() << "comp :" << comp;
//    qDebug() << "fee :" << fee;
//    qDebug() << "isMasters :" << isMasters;
//    qDebug() << "startDate :" << startDate;
//    qDebug() << "endDate :" << endDate;

    if (item)
    {
        ui->uni->setCurrentText(records[selectedItemIndex].getUni());
        ui->spec->setText(records[selectedItemIndex].getSpec());
        ui->compitition->setValue(records[selectedItemIndex].getCompetition());
        ui->fee->setValue(records[selectedItemIndex].getFee());
        ui->master->setChecked(records[selectedItemIndex].getIsMasters());
        ui->startDate->setDate(records[selectedItemIndex].getStartDate());
        ui->endDate->setDate(records[selectedItemIndex].getEndDate());
    }
}

void MainWindow::onSave() {
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();

    int currentIndex = ui->listWidget->row(selectedItem);

    qDebug() << "ON_SAVE:";
    qDebug() << "currentIndex:" << currentIndex;

    if (selectedItem)
    {
        QString uni = ui->uni->currentText();
        QString spec = ui->spec->text();
        double comp = ui->compitition->value();
        int fee = ui->fee->value();
        bool isMaster = ui->master->isChecked();
        QDate startDate = ui->startDate->date();
        QDate endDate = ui->endDate->date();

        records[currentIndex] = Record(uni, spec, comp, fee, isMaster, startDate, endDate);

        QString newRecord = spec + "\t" + uni + "\t" + QString::number(comp);

        selectedItem->setText(newRecord);

        ui->listWidget->update();
    }
}

void MainWindow::onDelete() {
    QListWidgetItem *selectedItem = ui->listWidget->currentItem();

    if (selectedItem)
    {
        delete ui->listWidget->takeItem(ui->listWidget->row(selectedItem));

        ui->uni->setCurrentIndex(0);
        ui->spec->setText("");
        ui->compitition->setValue(0);
        ui->fee->setValue(0);
        ui->startDate->setDate(QDate(2024,1,1));
        ui->endDate->setDate(QDate(2024,1,1));
    }
    else
    {
        QMessageBox::warning(this, "Ошибка", "Выберите запись для удаления.", QMessageBox::Ok);
    }
}

void MainWindow::handleSelectUni() {}

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

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::FocusOut)
    {
        if (watched == ui->spec)
        {
            if (ui->spec->hasAcceptableInput())
            {
                records[selectedRecord].setSpec(ui->spec->text());
            }
            else
            {
                QMessageBox::warning(this, "Предупреждение!", "Правильно заполните поле специальность!", QMessageBox::Ok);
            }
        }

        if (watched == ui->compitition)
        {
            records[selectedRecord].setCompetition(ui->compitition->value());
        }

        if (watched == ui->fee)
        {
            records[selectedRecord].setFee(ui->fee->value());
        }

        if (watched == ui->master)
        {
            records[selectedRecord].setIsMasters(ui->master->isChecked());
        }

        if (watched == ui->startDate)
        {
            records[selectedRecord].setStartDate(ui->startDate->date());
        }

        if (watched == ui->endDate)
        {
            records[selectedRecord].setEndDate(ui->endDate->date());
        }

        ui->centralwidget->clearFocus();
    }
}


