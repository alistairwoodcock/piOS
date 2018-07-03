#ifndef _EL_SWITCH
#define _EL_SWITCH

#ifndef __ASSEMBLER__

void switch_to_el1(unsigned long return_addr);
void switch_to_el2(unsigned long return_addr);

#endif

#endif /*_EL_SWITCH*/