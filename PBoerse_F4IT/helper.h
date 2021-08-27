#ifndef HELPER_H
#define HELPER_H

#include <QMessageBox>


class Helper
{
private:
    static QMessageBox::Icon getIcon(int i); // TODO: gefällt mir gar nicht

public:
    Helper();
    static void openMsgBox(QString title, QString text, QString info = "", int icon = 0);
};

#endif // HELPER_H
