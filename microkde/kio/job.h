#ifndef MICROKDE_KIO_JOB_H
#define MICROKDE_KIO_JOB_H

#include <KUrl>

class KJob;

namespace KIO {

enum LoadTypes { NoReload };
enum JobFlags { HideProgressInfo };

KJob *get( const KUrl &url, LoadTypes l, JobFlags f );

class Job
{

};

}

#endif
