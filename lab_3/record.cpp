#include "record.h"

Record::Record():
    uni_(""), spec_(""), competition_(0), fee_(0), isMasters_(false),
    startDate_(QDate(2024,1,1)), endDate_(QDate(2024,1,1))
{}

Record::Record(QString uni, QString spec, double comp, int fee,
               bool isMasters, QDate startDate, QDate endDate):
    uni_(uni), spec_(spec), competition_(comp),
    fee_(fee), isMasters_(isMasters),
    startDate_(startDate), endDate_(endDate)
{}


bool Record::operator==(const Record& other) const {
    return (uni_ == other.uni_ &&
            spec_ == other.spec_ &&
            competition_ == other.competition_ &&
            fee_ == other.fee_ &&
            isMasters_ == other.isMasters_ &&
            startDate_ == other.startDate_ &&
            endDate_ == other.endDate_);
}


bool Record::operator!=(const Record& other) const {
    return !(*this == other);
}


bool Record::operator<(const Record& other) const {}

bool Record::operator<=(const Record& other) const {
    return (*this < other) || (*this == other);
}

bool Record::operator>(const Record& other) const {
    return !(*this <= other);
}

bool Record::operator>=(const Record& other) const {
    return !(*this < other);
}

Record& Record::operator=(const Record& other) {
    if (this != &other) {
        uni_ = other.uni_;
        spec_ = other.spec_;
        competition_ = other.competition_;
        fee_ = other.fee_;
        isMasters_ = other.isMasters_;
        startDate_ = other.startDate_;
        endDate_ = other.endDate_;
    }
    return *this;
}

// GET SET Uni
void Record::setUni(QString uni) {
    this->uni_ = uni;
}

QString Record::getUni() {
    return this->uni_;
}

// GET SET Spec
void Record::setSpec(QString spec) {
    this->spec_ = spec;
}

QString Record::getSpec() {
    return this->spec_;
}

// GET SET LastYearCompetition
void Record::setCompetition(double competition) {
    this->competition_ = competition;
}

double Record::getCompetition() {
    return this->competition_;
}

// GET SET TuitionFee
void Record::setFee(int fee) {
    this->fee_ = fee;
}

int Record::getFee() {
    return this->fee_;
}

// GET SET MastersDegree
void Record::setIsMasters(bool isMastersDegree) {
    this->isMasters_ = isMastersDegree;
}

bool Record::getIsMasters() {
    return this->isMasters_;
}

// GET SET StartDateSubmissionDocs
void Record::setStartDate(QDate startDate) {
    this->startDate_ = startDate;
}

QDate Record::getStartDate() {
    return this->startDate_;
}

// GET SET EndDateSubmissionDocs
void Record::setEndDate(QDate endDate) {
    this->endDate_ = endDate;
}

QDate Record::getEndDate() {
    return this->endDate_;
}
