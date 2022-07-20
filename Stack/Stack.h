#ifndef _STACK_H_
#define _STACK_H_

#ifdef T
#undef T
#endif

#define T double
#include "Stack_as_template.h"
#ifdef T
#undef T
#endif

#define T int
#include "Stack_as_template.h"

#endif