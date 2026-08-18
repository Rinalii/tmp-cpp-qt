#include "toupperworker.h"

ToUpperWorker::ToUpperWorker() {}

QString ToUpperWorker::ConvertToUpper(const QString &str) {
    return str.toUpper() + QString::number(++counter_);
}
