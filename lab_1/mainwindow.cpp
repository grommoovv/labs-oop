#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "examplevalidator.h"
#include <QValidator>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QValidator *validator = new ExampleValidator(this);

    ui->lineEdit->setValidator(validator);

    connect(ui->checkButton,SIGNAL(clicked()),this,SLOT(isCorrect()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::isCorrect()
{
    if (ui->lineEdit->hasAcceptableInput())
    {
        QMessageBox::information(this,"Корректность строки", "Строка введена правильно");
    }
    else
    {
        QMessageBox::warning(this,"Корректность строки", "Строка введена неправильно");
    }

}
