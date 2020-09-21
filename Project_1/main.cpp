#include "print_window.h"
#include <QApplication>
#include "form_info.h"
#include <QDebug>
#include <QString>

using namespace  std;

Form* FormList;
int numberList;

int main(int argc, char *argv[])
{
    FormList = new Form[100];

    QApplication a(argc, argv);
    Print_window w;
    w.show();

    return a.exec();
}
