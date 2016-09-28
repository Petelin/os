/*
 */

#ifndef INCLUDE_TYPES_H_
#define INCLUDE_TYPES_H_

#ifndef NULL
	#define NULL 0
#endif

#ifndef TRUE
	#define TRUE  1
	#define FALSE 0
#endif

typedef unsigned int   uint32_t;
typedef          int   int32_t;
typedef unsigned short uint16_t;
typedef          short int16_t;
typedef unsigned char  uint8_t;
typedef signed 	 char  int8_t;
typedef unsigned int       size_t;
typedef          int       ssize_t;

typedef uint32_t uintptr_t;
#endif 	// INCLUDE_TYPES_H_
