#include <QDir>
#include <QDesktopServices>
#include <QFile>
#include <QProcess>
#include <QTextCodec>
#include <QTextStream>
#include <QUrl>
#include "fileutils.h"

AS_NAMESPACE_START

QString FileUtils::read(const QString &p, const char *enc)
{
    QString c;
    QFile file(p);
    if (file.exists() && file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        in.setCodec(enc);
        while (!in.atEnd())
        {
            c.append(in.readLine());
            c.append("\n");
        }
        file.close();
    }
    return c;
}

bool FileUtils::rimraf(const QString &d)
{
    bool s = true;
    QDir dir(d);
    if (dir.exists())
    {
        QFileInfoList files = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot, QDir::DirsFirst);
        if (!files.isEmpty())
        {
            for (QFileInfo fi : files)
            {
                if (fi.isDir())
                {
                    s = rimraf(fi.absoluteFilePath());
                }
                else
                {
                    s = QFile::remove(fi.absoluteFilePath());
                }
                if (!s)
                {
                    return false;
                }
            }
        }
        s = dir.rmdir(d);
    }
    return s;
}

/**
 * @brief From http://lynxline.com/show-in-finder-show-in-explorer/
 */
void FileUtils::show(const QString &p)
{
#ifdef Q_OS_WIN
    QStringList args;
    args << "/select," << QDir::toNativeSeparators(p);
    QProcess::startDetached("explorer", args);
#elif defined(Q_OS_MAC)
    QStringList args;
    args << "-e" << "tell application \"Finder\"";
    args << "-e" << "activate" << "-e";
    args << "select POSIX file \"" + p + "\"";
    args << "-e" << "end tell";
    QProcess::startDetached("osascript", args);
#else
    QDesktopServices::openUrl(QUrl("file:///" + QFileInfo(p).absolutePath()));
#endif
}

AS_NAMESPACE_END
