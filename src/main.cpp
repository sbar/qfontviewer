#include <QApplication>
#include <QTextStream>
#include <csignal>
#include "mainwindow.h"

class MainWindow;

static void setupUnixSignalHandlers()
{
    struct sigaction sigint, sigterm;
    sigint.sa_handler = MainWindow::signalsHandler;
    sigterm.sa_handler = MainWindow::signalsHandler;
    sigemptyset(&sigint.sa_mask);
    sigemptyset(&sigterm.sa_mask);
    sigint.sa_flags = 0;
    sigterm.sa_flags = 0;
    sigaction(SIGINT, &sigint, 0);
    sigaction(SIGTERM, &sigterm, 0);
}

static void showHelp(const QStringList & args)
{
    QTextStream qout(stdout);
    qout << QObject::tr("Usage: %1 [OPTION]... [FILE]\n\n\
Available options:\n\
  -b, --bold                 set bold font\n\
  -B, --no-bold              unset bold font\n\
  -c, --chars                show character table\n\
  -h, --help                 show this help\n\
  -i, --italic               set italic font\n\
  -I, --no-italic            unset italic font\n\
  -p, --pangram              show pangram tab\n\
").arg(args[0]);
}

int main(int argc, char *argv[])
{
    setupUnixSignalHandlers();

    QApplication app(argc, argv);

    QStringList args = app.arguments();
    if (args.size() > 1 && (args[1] == QString("--help") ||
                            args[1] == QString("-h"))) {
        showHelp(args);
        return 0;
    }

    app.setApplicationName("qfontviewer");
    app.setApplicationVersion(VERSION);

    MainWindow window(args);
    window.show();

    return app.exec();
}
