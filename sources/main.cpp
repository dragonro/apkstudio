#include <QApplication>
#include <QFontDatabase>
#include <QProcess>
#include <QStyleFactory>
#include <QTimer>
#include <QTranslator>
#include "constants.h"
#include "ide.h"
#include "fileutils.h"
#include "process.h"

int main(int argc, char *argv[])
{
    qRegisterMetaType<As::Process::Result>("Result");
    QCoreApplication::setApplicationName(APP_NAME);
    QCoreApplication::setOrganizationName(APP_ORGANIZATION);
    QFontDatabase::addApplicationFont(QString(QRC_FONTS).append("scp_regular.ttf"));
    QFontDatabase::addApplicationFont(QString(QRC_FONTS).append("scp_bold.ttf"));
    QApplication app(argc, argv);
#ifdef Q_OS_WIN
    app.setStyle(QStyleFactory::create("fusion"));
#endif
    QTranslator translator;
    translator.load("en", QRC_LANG);
    app.installTranslator(&translator);
    app.setStyleSheet(As::FileUtils::read(QString(QRC_STYLES).arg("default")));
    As::Ide ide;
    ide.show();
    QTimer::singleShot(0, &ide, &As::Ide::onInit);
    return app.exec();
}
