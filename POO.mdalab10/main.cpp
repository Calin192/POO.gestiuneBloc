#include "POOmdalab10.h"
#include "console.h"
#include "Bloc.h"
#include "LocatarRepo.h"
#include "validator.h"
#include <iostream>
#include "consoleGUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char* argv[])
{
    LocatarRepo rep;
    LocatarValidator val;
    Bloc ctr{ rep,val };

    QApplication a(argc, argv);
    ctr.addLocatar(1, "a", 1, "a");
    ctr.addLocatar(2, "b", 2, "b");
    ctr.addLocatar(3, "c", 3, "c");
    ctr.addLocatar(4, "d", 4, "d");
    ctr.addLocatar(5, "e", 5, "e");
    ctr.addLocatar(6, "f", 6, "f");

    GUI gui{ ctr };
    gui.setWindowIcon(QIcon("C:\\Photos\\Cursed\\pis"));
    gui.show();
    
    return a.exec();
}
