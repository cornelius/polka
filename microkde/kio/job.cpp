#include <kio/job.h>

#include <KJob>

using namespace KIO;

KJob *KIO::get( const KUrl &url, LoadTypes l, JobFlags f )
{
    return new KJob();
}
