#include "HidrometroApp.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    HidrometroApp window;
    window.show();
    return app.exec();
}
