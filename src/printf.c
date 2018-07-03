#include "printf.h"

// typedef void (*outf) (void*, char);
static void (*output_func) (char);


void printf_init(void (*func) (char)){
    output_func = func;
}

void a_print_int(int val){
    if(val < 0){
        output_func('-');
        val = -val;
    }

    int i = 1;
    for(int c = val; c >= 10; c /= 10) i *= 10;
    
    for(; i > 0; i /= 10) output_func('0' + (unsigned char) ((val%(i*10)) / i));   
}

void a_print_ul(unsigned long val){
    
    int i = 1;
    for(int c = val; c >= 10; c /= 10) i *= 10;
    
    for(; i > 0; i /= 10) output_func('0' + (unsigned char) ((val%(i*10)) / i));
}

void a_printf(char* fmt, ...){
    
    va_list args;

    va_start(args, fmt);
    
    char* ch = fmt;

    for(;*ch != '\0';ch++){
        if(*ch != '%'){
            output_func(*ch);
            continue;
        }

        ch++;

        switch(*ch){
            case 'u': {
                unsigned long val = va_arg(args, unsigned long);
                a_print_ul(val);
            } break;

            case 'i': {
                int val = va_arg(args, int);
                a_print_int(val);
            } break;
        }
    }    


    va_end(args);    
}

