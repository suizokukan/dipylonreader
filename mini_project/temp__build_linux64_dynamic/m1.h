#ifndef M1_H
#define M1_H

#include "./fixedparameters.h"

void m1_foo1(void);

struct CC {
  CC(void);
  CC& a;
};
inline CC::CC(void) : a(CC()) {
}

#endif
