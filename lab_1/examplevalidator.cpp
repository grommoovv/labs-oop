#include "examplevalidator.h"
#include <QMessageBox>
#include <QDebug>

ExampleValidator::ExampleValidator(QObject *parent): QValidator(parent){}

ExampleValidator::~ExampleValidator(){}

QValidator::State ExampleValidator::validate( QString &input, int &pos ) const
{
    QStringList inputWords = input.toLower().split(" ", QString::SkipEmptyParts);

    bool isYearValid;

    switch (inputWords.size())
    {
        case 0:
        {
            return QValidator::Intermediate;
        }
        case 1:
        {
            if (inputWords[0].toInt(&isYearValid))
            {
                return QValidator::Intermediate;
            }
            else
            {
                return QValidator::Invalid;
            }
        }
        case 2:
        {
            if (inputWords[1] == "г")
            {
                return QValidator::Intermediate;
            }
            else if (inputWords[1] == "г.")
            {
                return QValidator::Intermediate;
            }
            else
            {
                return QValidator::Invalid;
            }
        }
        case 3:
        {
            if (inputWords[1] == "г." && (inputWords[2] == "д" || inputWords[2] == "до"))
            {
                return QValidator::Intermediate;
            }
            else if (inputWords[1] == "г." && inputWords[2] == "н")
            {
                return QValidator::Intermediate;
            }
            else if (inputWords[1] == "г." && inputWords[2] == "н.")
            {
                return QValidator::Intermediate;
            }
            else if (inputWords[1] == "г." && inputWords[2] == "н.э")
            {
                return QValidator::Intermediate;
            }
            else if (inputWords[1] == "г." && inputWords[2] == "н.э.")
            {
                return QValidator::Acceptable;
            }
            else
            {
                return QValidator::Invalid;
            }
        }
        case 4:
        {
            if (inputWords[1] == "г." && inputWords[2] == "до" && inputWords[3] == "н")
            {
                return QValidator::Intermediate;
            }
            else if (inputWords[1] == "г." && inputWords[2] == "до" && inputWords[3] == "н.")
            {
                return QValidator::Intermediate;
            }
            else if (inputWords[1] == "г." && inputWords[2] == "до" && inputWords[3] == "н.э")
            {
                return QValidator::Intermediate;
            }
            else if (inputWords[1] == "г." && inputWords[2] == "до" && inputWords[3] == "н.э.")
            {
                return QValidator::Acceptable;
            }
            else {
                return QValidator::Invalid;
            }
        }
    }
}
