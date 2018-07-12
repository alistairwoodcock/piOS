#ifndef	_BOOT_H
#define	_BOOT_H

extern void delay ( unsigned long);
extern void put32 ( unsigned long, unsigned int );
extern unsigned int get32 ( unsigned long );
extern unsigned int getcpuid(void);
extern unsigned int getsp(void);
extern int get_el(void);
extern void set_pgd(unsigned long pgd);
extern unsigned long get_pgd();

#endif  /*_BOOT_H */
