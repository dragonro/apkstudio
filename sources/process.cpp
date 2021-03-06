#include <QProcess>
#include "constants.h"
#include "pathutils.h"
#include "process.h"

AS_NAMESPACE_START

Process::Process(const QString &exe, QObject *parent)
    : QObject(parent), _exe(PathUtils::find(exe)), _lf(QRegularExpression(REGEX_LF))
{
}

Process::Result Process::exec(const QStringList &args)
{
    emit executing(args);
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    // process.setProcessEnvironment(QProcessEnvironment::systemEnvironment());
    process.start(_exe, args, QIODevice::ReadOnly);
    Result result;
    if (process.waitForStarted(CLI_TIMEOUT))
    {
        if (!process.waitForFinished(CLI_TIMEOUT))
        {
            process.kill();
        }
        QString error(process.readAllStandardError());
        QString output(process.readAllStandardOutput());
        result.code = process.exitCode();
        result.error = error.split(_lf, QString::SkipEmptyParts);
        result.output = output.split(_lf, QString::SkipEmptyParts);
    } else {
        result.code = -1;
    }
    emit executed(result);
    return result;
}

AS_NAMESPACE_END
