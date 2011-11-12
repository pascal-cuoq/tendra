/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */
    
#ifndef SZS_ALS_INCLUDED
#define SZS_ALS_INCLUDED

/*
    SIZES AND ALIGNMENTS OF BASIC SHAPES
*/

#ifdef SUN

#define  TOP_SZ		 L0		/* size of void */
#define  TOP_ALIGN	 const_al1	/* alignment of void */

#define  SCHAR_SZ	 L8		/* size of signed char */
#define  SCHAR_ALIGN	 const_al8	/* alignment of signed char */
#define  UCHAR_SZ	 L8		/* size of unsigned char */
#define  UCHAR_ALIGN	 const_al8	/* alignment of unsigned char */

#define  SWORD_SZ	 L16		/* size of signed short */
#define  SWORD_ALIGN	 const_al16	/* alignment of signed short */
#define  UWORD_SZ	 L16		/* size of unsigned short */
#define  UWORD_ALIGN	 const_al16	/* alignment of unsigned short */

#define  SLONG_SZ	 L32		/* size of signed long */
#define  SLONG_ALIGN	 const_al16	/* alignment of signed long */
#define  ULONG_SZ	 L32		/* size of unsigned long */
#define  ULONG_ALIGN	 const_al16	/* alignment of unsigned long */

#define  SHREAL_SZ	 L32		/* size of float */
#define  SHREAL_ALIGN	 const_al16	/* alignment of float */

#define  REAL_SZ	 L64		/* size of double */
#define  REAL_ALIGN	 const_al16	/* alignment of double */

#define  DOUBLE_SZ	 L64		/* size of long double */
#define  DOUBLE_ALIGN	 const_al16	/* alignment of long double */

#define  STRUCT_ALIGN	 const_al16	/* alignment of struct */

#define  BF_ALIGN	 const_al1	/* alignment of bit */
#define  BF_STORE_UNIT	 L16		/* alignment of bitfield */
#define  MAX_BF_SIZE_CC	 const_al32	/* cc bitfield rule */
#define  MAX_BF_SIZE_GCC const_al64	 /* gcc bitfield rule */
extern alignment MAX_BF_SIZE ;	 	/* bitfield rule */

#define  PROC_SZ	 L32		/* size of ptr proc */
#define  PROC_ALIGN	 const_al16	/* alignment of ptr proc */

#define  PTR_SZ		 L32		/* size of pointer */
#define  PTRBIT_SZ	 L32		/* size of ptr bit */
#define  PTR_ALIGN	 const_al16	/* alignment of pointer */

#define  OFFSET_SZ	 L32		/* size of offset */
#define  OFFSET_ALIGN	 const_al16	/* alignment of offset */

#define  LLVALUE_SZ	 L32		/* size of label value */
#define  LLVALUE_ALIGN	 const_al16	/* alignment of label value */

#define  ALLOCA_ALIGN	 const_al32
#define  FRAME_ALIGN	 const_al32
#define  VAR_PARAM_ALIGN const_al32
#define  CODE_ALIGN	 const_al16

#define  PARAM_ALIGN	 L32		/* alignment of proc arguments */
#define  STACK_ALIGN	 L16		/* alignment of stack objects */
#define  DBL_ALIGN	 L16		/* alignment of doubles */

#define MIN_PAR_ALIGNMENT const_al32

#define U64_SZ ((long)64)
#define U64_ALIGN const_al16

#define S64_SZ ((long)64)
#define S64_ALIGN const_al16


#else

#define  TOP_SZ		 L0		/* size of void */
#define  TOP_ALIGN	 const_al1	/* alignment of void */

#define  SCHAR_SZ	 L8		/* size of signed char */
#define  SCHAR_ALIGN	 const_al8	/* alignment of signed char */
#define  UCHAR_SZ	 L8		/* size of unsigned char */
#define  UCHAR_ALIGN	 const_al8	/* alignment of unsigned char */

#define  SWORD_SZ	 L16		/* size of signed short */
#define  SWORD_ALIGN	 const_al16	/* alignment of signed short */
#define  UWORD_SZ	 L16		/* size of unsigned short */
#define  UWORD_ALIGN	 const_al16	/* alignment of unsigned short */

#define  SLONG_SZ	 L32		/* size of signed long */
#define  SLONG_ALIGN	 const_al16	/* alignment of signed long */
#define  ULONG_SZ	 L32		/* size of unsigned long */
#define  ULONG_ALIGN	 const_al16	/* alignment of unsigned long */

#define  SHREAL_SZ	 L32		/* size of float */
#define  SHREAL_ALIGN	 const_al16	/* alignment of float */

#define  REAL_SZ	 L64		/* size of double */
#define  REAL_ALIGN	 const_al16	/* alignment of double */

#define  DOUBLE_SZ	 L64		/* size of long double */
#define  DOUBLE_ALIGN	 const_al16	/* alignment of long double */

#define  STRUCT_ALIGN	 const_al16	/* alignment of struct */

#define  BF_ALIGN	 const_al1	/* alignment of bit */
#define  BF_STORE_UNIT	 L16		/* alignment of bitfield */
#define  MAX_BF_SIZE_CC	 const_al32	/* cc bitfield rule */
#define  MAX_BF_SIZE_GCC const_al64	 /* gcc bitfield rule */
extern alignment MAX_BF_SIZE ;	 	/* bitfield rule */

#define  PROC_SZ	 L32		/* size of ptr proc */
#define  PROC_ALIGN	 const_al16	/* alignment of ptr proc */

#define  PTR_SZ		 L32		/* size of pointer */
#define  PTRBIT_SZ	 L64		/* size of ptr bit */
#define  PTR_ALIGN	 const_al16	/* alignment of pointer */

#define  OFFSET_SZ	 L32		/* size of offset */
#define  OFFSET_ALIGN	 const_al16	/* alignment of offset */

#define  LLVALUE_SZ	 L32		/* size of label value */
#define  LLVALUE_ALIGN	 const_al16	/* alignment of label value */

#define  ALLOCA_ALIGN	 const_al16
#define  FRAME_ALIGN	 const_al16
#define  VAR_PARAM_ALIGN const_al16
#define  CODE_ALIGN	 const_al16

#define  PARAM_ALIGN	 L16		/* alignment of proc arguments */
#define  STACK_ALIGN	 L16		/* alignment of stack objects */
#define  DBL_ALIGN	 L16		/* alignment of doubles */

#define MIN_PAR_ALIGNMENT const_al16

#define U64_SZ ((long)64)
#define U64_ALIGN const_al16

#define S64_SZ ((long)64)
#define S64_ALIGN const_al16

#endif

/*
    SIZES OF MANTISSAS OF FLOATING POINT NUMBERS
*/

#define  FLOAT_BITS	 24		/* mantissa size for float */
#define  DOUBLE_BITS	 53		/* mantissa size for double */
#define  LDOUBLE_BITS	 53		/* mantissa size for long double */


/*
    MAXIMUM EXPONENT ALLOWED IN FLOATING-POINT CONSTANTS
*/

extern int target_dbl_maxexp ;

#endif
