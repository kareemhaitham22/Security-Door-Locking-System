#ifndef COMMON_MACROS
#define COMMON_MACROS

#define SET_BIT(x,bit) ( x|=(1<<bit) )

#define CLEAR_BIT(x,bit) ( x&=(~(1<<bit)) )

#define TOGGLE_BIT(x,bit) ( x^=(1<<bit) )

#define ROR(x,num) ( x = (x>>num) | (x<<(8-num)) )

#define ROL(x,num) ( x = (x<<num) | (x>>(8-num)) )

#define BIT_IS_SET(x,bit) ( x & (1<<bit) )

#define BIT_IS_CLEAR(x,bit) (!( x & (1<<bit) ))

#endif
