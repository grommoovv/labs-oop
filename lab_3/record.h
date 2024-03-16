#ifndef RECORD_H
#define RECORD_H

#include <QDate>
#include <QString>
#include <QVector>
#include <QMap>

class Record {
private:
    QString uni_;
    QString spec_;
    double competition_;
    int fee_;
    bool isMasters_;
    QDate startDate_;
    QDate endDate_;

public:
    Record();
    Record(QString uni, QString spec, double comp, int fee, bool isMasters, QDate startDate, QDate endDate);


    bool operator==(const Record& other) const;
    bool operator!=(const Record& other) const;
    bool operator<(const Record& other) const;
    bool operator<=(const Record& other) const;
    bool operator>(const Record& other) const;
    bool operator>=(const Record& other) const;

    Record& operator=(const Record& other);

    void setUni(QString uni);
    QString getUni();

    void setSpec(QString spec);
    QString getSpec();

    void setCompetition(double competition);
    double getCompetition();

    void setFee(int fee);
    int getFee();

    void setIsMasters(bool isMastersDegree);
    bool getIsMasters();

    void setStartDate(QDate startDate);
    QDate getStartDate();

    void setEndDate(QDate endDate);
    QDate getEndDate();
};

#endif // RECORD_H
