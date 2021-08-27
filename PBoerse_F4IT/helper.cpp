#include "helper.h"
Helper::Helper()
{ }
/*Icon Info:
 * 0: QMessageBox::NoIcon
 * 1: QMessageBox::Information
 * 2: QMessageBox::Warning
 * 3: QMessageBox::Critical
 * 4: QMessageBox::Question */

//1)---------helper-msg-box-------------------------------------------------------------------------
void Helper::openMsgBox(QString title, QString text, QString info, int icon) {
    QMessageBox msgBox;
    msgBox.setWindowTitle(title);
    msgBox.setText(text);
    msgBox.setInformativeText(info);
    msgBox.setIcon(Helper::getIcon(icon));
    msgBox.exec();
}
//2)--------Switch-case-Message-Box--------------------------------------------------------------------------
QMessageBox::Icon Helper::getIcon(int i) {
    switch (i) {
    case 1:
        return QMessageBox::Information;
    case 2:
        return QMessageBox::Warning;
    case 3:
        return QMessageBox::Critical;
    case 4:
        return QMessageBox::Question;
    default:
        return QMessageBox::NoIcon;
    }}
