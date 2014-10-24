#include "m1.h"
#include <QDebug>

void m1_foo1(void) {
  qDebug() << "m1_foo1 : application_name=" << fixedparameters::application_name;
}

C::C(void) {
  qDebug() << "C()";
  this->a = 2;
}

C::~C(void) {
  qDebug() << "~C";
}
