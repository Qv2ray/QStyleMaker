#include "maindialog.h"
#include "src/defines/defines.h"

#include <QApplication>
#include <QLocale>
#include <QTextCodec>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setApplicationName(D_PROG_NAME);

    QTextCodec *codec = QTextCodec::codecForName("UTF-8"); // set encoding for prog
    // QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);
    // QTextCodec::setCodecForTr(codec);

    MainDialog w;
    w.show();

    return a.exec();
}
