#include "installrunnable.h"
#include "adb.h"

AS_NAMESPACE_START

InstallRunnable::InstallRunnable(const QString &a, QObject *p)
    : Runnable(p), _apk(a)
{
    _connections << connect(this, SIGNAL(installFailure(QString)), p, SLOT(onInstallFailure(QString)), Qt::QueuedConnection);
    _connections << connect(this, SIGNAL(installSuccess(QString)), p, SLOT(onInstallSuccess(QString)), Qt::QueuedConnection);
}

void InstallRunnable::run()
{
    emit runnableStarted();
    Process::Result r = Adb::get()->install(_apk);
    if (r.code == 0)
    {
        bool s = false;
        for (const QString &l : r.output)
        {
            if (l.startsWith("Success"))
            {
                s = true;
                break;
            }
        }
        if (s)
        {
            emit installSuccess(_apk);
        }
        else
        {
            emit installFailure(_apk);
        }
    }
    else
    {
    }
    emit runnableStopped();
}

AS_NAMESPACE_END
