#ifndef _Als_PRINTF_
#define _Als_PRINTF_

#include <stdarg.h>

void printf_init(void (*sendc) (char));
void a_printf(char *fmt, ...);

#define printf a_printf 


#endif /*_Als_PRINTF_ */