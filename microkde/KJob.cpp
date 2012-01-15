#include "KJob"

KJob::KJob()
{
}

QString KJob::errorText() const
{
    return QString();
}

bool KJob::error() const
{
    return false;
}
