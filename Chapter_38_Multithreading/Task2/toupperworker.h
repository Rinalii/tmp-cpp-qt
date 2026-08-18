#ifndef TOUPPERWORKER_H
#define TOUPPERWORKER_H

#include <QString>
#include <atomic>

class ToUpperWorker
{
public:
    ToUpperWorker();

    QString ConvertToUpper(const QString& str);

private:
    std::atomic<int> counter_;
};

#endif // TOUPPERWORKER_H
