#include "cdialog.h"
int cdialog::state=0;
cdialog::cdialog() {
}
void cdialog::onpressed()
{
    state=!state;
}
