#ifndef __TYPES_H__
#define __TYPES_H__

/* *********** includes ***************************************************** */


/* *********** types ******************************************************** */
#ifndef PLUS
typedef char                CHAR; 
typedef int                 INT;
#endif
//bla bla bla

typedef unsigned char       BYTE;
typedef signed short        SHORT;
typedef unsigned short      WORD;
typedef signed long         LONG;
typedef unsigned long       ULONG;
typedef unsigned long       DWORD;
typedef unsigned long long  DULONG;
typedef double              DOUBLE;
typedef SHORT               BOOL;

typedef signed char         INT8;
typedef unsigned char       UINT8;
typedef signed short        INT16;
typedef unsigned short      UINT16;
typedef signed long         INT32;
typedef unsigned long       UINT32;
typedef signed long long    INT64;
typedef unsigned long long  UINT64;

typedef unsigned char 		uint8;
typedef unsigned short		uint16;


typedef UINT32         SIZE_T;

typedef volatile unsigned long   UINT32_REG;
typedef volatile unsigned short  UINT16_REG;
typedef volatile unsigned char   UINT8_REG;

typedef unsigned long 		uint32;	

#ifndef VOID
#define VOID           void
#endif

#ifndef NULL
#define NULL           ((void *) 0)
#endif

/* ************************************************************************** */
#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#endif

/* *********** Modifiers **************************************************** */
#define CONST     const
#define EXTERN    extern
#define VOLATILE  volatile

#define HUGE      huge
#define FAR       far
#define TINY      tiny

#ifdef __arm
#define PACKED __packed
#else
#define PACKED
#endif

/* *********** Defines ****************************************************** */
#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef LOW
#define LOW 0
#endif

#ifndef HIGH
#define HIGH 1
#endif

#ifndef LITTLE
#define LITTLE 0
#endif

#ifndef BIG
#define BIG 1
#endif

#define BYTE_ORDER      LITTLE
#define BITFIELD_ORDER  LITTLE



/* *********** Unions ******************************************************* */
#if (BYTE_ORDER==BIG)

typedef union u_ulong 
{
   ULONG ul;

   struct 
   {
     WORD hw,lw;
   } ulw;

   struct 
   {
     BYTE hb,mhb,mlb,lb;
   } ulb;

   BYTE ular[4];

} U_ULONG;

typedef union  u_word 
{
   WORD w;

   struct 
   {
     BYTE hb,lb;
   } wb;

   BYTE war[2];

} U_WORD;

/* BYTE_ORDER==LITTLE */
#else

typedef union u_ulong 
{
   ULONG ul;

   struct 
   {
     WORD lw,hw;
   } ulw;

   struct 
   {
     BYTE lb,mlb,mhb,hb;
   } ulb;

   BYTE ular[4];

} U_ULONG;


typedef union  u_word 
{
   WORD w;

   struct 
   {
     BYTE lb,hb;
   } wb;

   BYTE war[2];

} U_WORD;

#endif


typedef union 
{
	UINT8_REG   b[4];
	UINT16_REG  w[2];
	UINT32_REG  dw;
} U_UINT32_REG;



/* data types used in different levels but those .h files are not always switched on */


/* ************************************************************************** */

#endif /* __TYPES_H__ */

