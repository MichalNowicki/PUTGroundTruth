// Using the Xsens CMT library. Do NOT change this file.

/*! \file
	
	\brief CMT library main header file.
	
	This file is intended for people that want to use the Xsens CMT library.
	This file was automatically generated, so do not judge it based on its layout or
	redundant definitions.

	If you find that this file needs some tweaking to work with your particular compiler,
	please let us know at support@xsens.com

	\section FileCopyright Copyright Notice 
	Copyright (C) Xsens Technologies B.V., 2006.  All rights reserved.

	This source code is intended for use only by Xsens Technologies BV and
	those that have explicit written permission to use it from
	Xsens Technologies BV.

	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
	PARTICULAR PURPOSE.
*/

#ifndef _CMT_LIB_H_2006_08_29
#define _CMT_LIB_H_2006_08_29

#define _CMT_STATIC_LIB

/*  A portable stdint.h
 ****************************************************************************
 *  BSD License:
 ****************************************************************************
 *
 *  Copyright (c) 2005-2007 Paul Hsieh
 *  All rights reserved.
 *  
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *  
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary form must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     documentation and/or other materials provided with the distribution.
 *  3. The name of the author may not be used to endorse or promote products
 *     derived from this software without specific prior written permission.
 *  
 *  THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 *  IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 *  OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 *  IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 *  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 *  THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************
 *
 *  Version 0.1.11
 *
 *  The ANSI C standard committee, for the C99 standard, specified the
 *  inclusion of a new standard include file called stdint.h.  This is
 *  a very useful and long desired include file which contains several
 *  very precise definitions for integer scalar types that is
 *  critically important for making portable several classes of
 *  applications including cryptography, hashing, variable length
 *  integer libraries and so on.  But for most developers its likely
 *  useful just for programming sanity.
 *
 *  The problem is that most compiler vendors have decided not to
 *  implement the C99 standard, and the next C++ language standard
 *  (which has a lot more mindshare these days) will be a long time in
 *  coming and its unknown whether or not it will include stdint.h or
 *  how much adoption it will have.  Either way, it will be a long time
 *  before all compilers come with a stdint.h and it also does nothing
 *  for the extremely large number of compilers available today which
 *  do not include this file, or anything comparable to it.
 *
 *  So that's what this file is all about.  Its an attempt to build a
 *  single universal include file that works on as many platforms as
 *  possible to deliver what stdint.h is supposed to.  A few things
 *  that should be noted about this file:
 *
 *    1) It is not guaranteed to be portable and/or present an identical
 *       interface on all platforms.  The extreme variability of the
 *       ANSI C standard makes this an impossibility right from the
 *       very get go. Its really only meant to be useful for the vast
 *       majority of platforms that possess the capability of
 *       implementing usefully and precisely defined, standard sized
 *       integer scalars.  Systems which are not intrinsically 2s
 *       complement may produce invalid constants.
 *
 *    2) There is an unavoidable use of non-reserved symbols.
 *
 *    3) Other standard include files are invoked.
 *
 *    4) This file may come in conflict with future platforms that do
 *       include stdint.h.  The hope is that one or the other can be
 *       used with no real difference.
 *
 *    5) In the current verison, if your platform can't represent
 *       int32_t, int16_t and int8_t, it just dumps out with a compiler
 *       error.
 *
 *    6) 64 bit integers may or may not be defined.  Test for their
 *       presence with the test: #ifdef INT64_MAX or #ifdef UINT64_MAX.
 *       Note that this is different from the C99 specification which
 *       requires the existence of 64 bit support in the compiler.  If
 *       this is not defined for your platform, yet it is capable of
 *       dealing with 64 bits then it is because this file has not yet
 *       been extended to cover all of your system's capabilities.
 *
 *    7) (u)intptr_t may or may not be defined.  Test for its presence
 *       with the test: #ifdef PTRDIFF_MAX.  If this is not defined
 *       for your platform, then it is because this file has not yet
 *       been extended to cover all of your system's capabilities, not
 *       because its optional.
 *
 *    8) The following might not been defined even if your platform is
 *       capable of defining it:
 *
 *       WCHAR_MIN
 *       WCHAR_MAX
 *       (u)int64_t
 *       PTRDIFF_MIN
 *       PTRDIFF_MAX
 *       (u)intptr_t
 *
 *    9) The following have not been defined:
 *
 *       WINT_MIN
 *       WINT_MAX
 *
 *   10) The criteria for defining (u)int_least(*)_t isn't clear,
 *       except for systems which don't have a type that precisely
 *       defined 8, 16, or 32 bit types (which this include file does
 *       not support anyways). Default definitions have been given.
 *
 *   11) The criteria for defining (u)int_fast(*)_t isn't something I
 *       would trust to any particular compiler vendor or the ANSI C
 *       committee.  It is well known that "compatible systems" are
 *       commonly created that have very different performance
 *       characteristics from the systems they are compatible with,
 *       especially those whose vendors make both the compiler and the
 *       system.  Default definitions have been given, but its strongly
 *       recommended that users never use these definitions for any
 *       reason (they do *NOT* deliver any serious guarantee of
 *       improved performance -- not in this file, nor any vendor's
 *       stdint.h).
 *
 *   12) The following macros:
 *
 *       PRINTF_INTMAX_MODIFIER
 *       PRINTF_INT64_MODIFIER
 *       PRINTF_INT32_MODIFIER
 *       PRINTF_INT16_MODIFIER
 *       PRINTF_LEAST64_MODIFIER
 *       PRINTF_LEAST32_MODIFIER
 *       PRINTF_LEAST16_MODIFIER
 *       PRINTF_INTPTR_MODIFIER
 *
 *       are strings which have been defined as the modifiers required
 *       for the "d", "u" and "x" printf formats to correctly output
 *       (u)intmax_t, (u)int64_t, (u)int32_t, (u)int16_t, (u)least64_t,
 *       (u)least32_t, (u)least16_t and (u)intptr_t types respectively.
 *       PRINTF_INTPTR_MODIFIER is not defined for some systems which
 *       provide their own stdint.h.  PRINTF_INT64_MODIFIER is not
 *       defined if INT64_MAX is not defined.  These are an extension
 *       beyond what C99 specifies must be in stdint.h.
 *
 *       In addition, the following macros are defined:
 *
 *       PRINTF_INTMAX_HEX_WIDTH
 *       PRINTF_INT64_HEX_WIDTH
 *       PRINTF_INT32_HEX_WIDTH
 *       PRINTF_INT16_HEX_WIDTH
 *       PRINTF_INT8_HEX_WIDTH
 *       PRINTF_INTMAX_DEC_WIDTH
 *       PRINTF_INT64_DEC_WIDTH
 *       PRINTF_INT32_DEC_WIDTH
 *       PRINTF_INT16_DEC_WIDTH
 *       PRINTF_INT8_DEC_WIDTH
 *
 *       Which specifies the maximum number of characters required to
 *       print the number of that type in either hexadecimal or decimal.
 *       These are an extension beyond what C99 specifies must be in
 *       stdint.h.
 *
 *  Compilers tested (all with 0 warnings at their highest respective
 *  settings): Borland Turbo C 2.0, WATCOM C/C++ 11.0 (16 bits and 32
 *  bits), Microsoft Visual C++ 6.0 (32 bit), Microsoft Visual Studio
 *  .net (VC7), Intel C++ 4.0, GNU gcc v3.3.3
 *
 *  This file should be considered a work in progress.  Suggestions for
 *  improvements, especially those which increase coverage are strongly
 *  encouraged.
 *
 *  Acknowledgements
 *
 *  The following people have made significant contributions to the
 *  development and testing of this file:
 *
 *  Chris Howie
 *  John Steele Scott
 *  Dave Thorup
 *
 */

#include <stddef.h>
#include <limits.h>
#include <signal.h>

/*
 *  For gcc with _STDINT_H, fill in the PRINTF_INT*_MODIFIER macros, and
 *  do nothing else.  On the Mac OS X version of gcc this is _STDINT_H_.
 */

#if (defined(__STDC__) && __STDC__ && __STDC_VERSION__ >= 199901L) || (defined (__WATCOMC__) && __WATCOMC__ >= 1250) || (defined(__GNUC__) && __GNUC__ > 2)
#include <stdint.h>
#endif

#if  (defined (_STDINT_H_INCLUDED) || defined (_STDINT_H) || defined (_STDINT_H_)) && !defined (_PSTDINT_H_INCLUDED)
#define _PSTDINT_H_INCLUDED
# ifndef PRINTF_INT64_MODIFIER
#  if __WORDSIZE == 64
#   define PRINTF_INT64_MODIFIER "l"
#  else
#   define PRINTF_INT64_MODIFIER "ll"
#  endif
# endif
# ifndef PRINTF_INT32_MODIFIER
#  if (LONG_MAX == INT32_MAX)
#   define PRINTF_INT32_MODIFIER "l"
#  else
#   define PRINTF_INT32_MODIFIER ""
#  endif
# endif
# ifndef PRINTF_INT16_MODIFIER
#  define PRINTF_INT16_MODIFIER "h"
# endif
# ifndef PRINTF_INTMAX_MODIFIER
#  define PRINTF_INTMAX_MODIFIER PRINTF_INT64_MODIFIER
# endif
# ifndef PRINTF_INT64_HEX_WIDTH
#  define PRINTF_INT64_HEX_WIDTH "16"
# endif
# ifndef PRINTF_INT32_HEX_WIDTH
#  define PRINTF_INT32_HEX_WIDTH "8"
# endif
# ifndef PRINTF_INT16_HEX_WIDTH
#  define PRINTF_INT16_HEX_WIDTH "4"
# endif
# ifndef PRINTF_INT8_HEX_WIDTH
#  define PRINTF_INT8_HEX_WIDTH "2"
# endif
# ifndef PRINTF_INT64_DEC_WIDTH
#  define PRINTF_INT64_DEC_WIDTH "20"
# endif
# ifndef PRINTF_INT32_DEC_WIDTH
#  define PRINTF_INT32_DEC_WIDTH "10"
# endif
# ifndef PRINTF_INT16_DEC_WIDTH
#  define PRINTF_INT16_DEC_WIDTH "5"
# endif
# ifndef PRINTF_INT8_DEC_WIDTH
#  define PRINTF_INT8_DEC_WIDTH "3"
# endif
# ifndef PRINTF_INTMAX_HEX_WIDTH
#  define PRINTF_INTMAX_HEX_WIDTH PRINTF_INT64_HEX_WIDTH
# endif
# ifndef PRINTF_INTMAX_DEC_WIDTH
#  define PRINTF_INTMAX_DEC_WIDTH PRINTF_INT64_DEC_WIDTH
# endif

/*
 *  Something really weird is going on with Open Watcom.  Just pull some of
 *  these duplicated definitions from Open Watcom's stdint.h file for now.
 */

# if defined (__WATCOMC__) && __WATCOMC__ >= 1250
#  if !defined (INT64_C)
#   define INT64_C(x)   (x + (INT64_MAX - INT64_MAX))
#  endif
#  if !defined (UINT64_C)
#   define UINT64_C(x)  (x + (UINT64_MAX - UINT64_MAX))
#  endif
#  if !defined (INT32_C)
#   define INT32_C(x)   (x + (INT32_MAX - INT32_MAX))
#  endif
#  if !defined (UINT32_C)
#   define UINT32_C(x)  (x + (UINT32_MAX - UINT32_MAX))
#  endif
#  if !defined (INT16_C)
#   define INT16_C(x)   (x)
#  endif
#  if !defined (UINT16_C)
#   define UINT16_C(x)  (x)
#  endif
#  if !defined (INT8_C)
#   define INT8_C(x)   (x)
#  endif
#  if !defined (UINT8_C)
#   define UINT8_C(x)  (x)
#  endif
#  if !defined (UINT64_MAX)
#   define UINT64_MAX  18446744073709551615ULL
#  endif
#  if !defined (INT64_MAX)
#   define INT64_MAX  9223372036854775807LL
#  endif
#  if !defined (UINT32_MAX)
#   define UINT32_MAX  4294967295UL
#  endif
#  if !defined (INT32_MAX)
#   define INT32_MAX  2147483647L
#  endif
#  if !defined (INTMAX_MAX)
#   define INTMAX_MAX INT64_MAX
#  endif
#  if !defined (INTMAX_MIN)
#   define INTMAX_MIN INT64_MIN
#  endif
# endif
#endif

#ifndef _PSTDINT_H_INCLUDED
#define _PSTDINT_H_INCLUDED

#ifndef SIZE_MAX
# define SIZE_MAX (~(size_t)0)
#endif

/*
 *  Deduce the type assignments from limits.h under the assumption that
 *  integer sizes in bits are powers of 2, and follow the ANSI
 *  definitions.
 */

#ifndef UINT8_MAX
# define UINT8_MAX 0xff
#endif
#ifndef uint8_t
# if (UCHAR_MAX == UINT8_MAX) || defined (S_SPLINT_S)
    typedef unsigned char uint8_t;
#   define UINT8_C(v) ((uint8_t) v)
# else
#   error "Platform not supported"
# endif
#endif

#ifndef INT8_MAX
# define INT8_MAX 0x7f
#endif
#ifndef INT8_MIN
# define INT8_MIN INT8_C(0x80)
#endif
#ifndef int8_t
# if (SCHAR_MAX == INT8_MAX) || defined (S_SPLINT_S)
    typedef signed char int8_t;
#   define INT8_C(v) ((int8_t) v)
# else
#   error "Platform not supported"
# endif
#endif

#ifndef UINT16_MAX
# define UINT16_MAX 0xffff
#endif
#ifndef uint16_t
#if (UINT_MAX == UINT16_MAX) || defined (S_SPLINT_S)
  typedef unsigned int uint16_t;
# ifndef PRINTF_INT16_MODIFIER
#  define PRINTF_INT16_MODIFIER ""
# endif
# define UINT16_C(v) ((uint16_t) (v))
#elif (USHRT_MAX == UINT16_MAX)
  typedef unsigned short uint16_t;
# define UINT16_C(v) ((uint16_t) (v))
# ifndef PRINTF_INT16_MODIFIER
#  define PRINTF_INT16_MODIFIER "h"
# endif
#else
#error "Platform not supported"
#endif
#endif

#ifndef INT16_MAX
# define INT16_MAX 0x7fff
#endif
#ifndef INT16_MIN
# define INT16_MIN INT16_C(0x8000)
#endif
#ifndef int16_t
#if (INT_MAX == INT16_MAX) || defined (S_SPLINT_S)
  typedef signed int int16_t;
# define INT16_C(v) ((int16_t) (v))
# ifndef PRINTF_INT16_MODIFIER
#  define PRINTF_INT16_MODIFIER ""
# endif
#elif (SHRT_MAX == INT16_MAX)
  typedef signed short int16_t;
# define INT16_C(v) ((int16_t) (v))
# ifndef PRINTF_INT16_MODIFIER
#  define PRINTF_INT16_MODIFIER "h"
# endif
#else
#error "Platform not supported"
#endif
#endif

#ifndef UINT32_MAX
# define UINT32_MAX (0xffffffffUL)
#endif
#ifndef uint32_t
#if (UINT_MAX == UINT32_MAX) && defined (__GNUC__) && (__GNUC__ > 3)
  typedef unsigned int uint32_t;
# ifndef PRINTF_INT32_MODIFIER
#  define PRINTF_INT32_MODIFIER ""
# endif
#elif (ULONG_MAX == UINT32_MAX) || defined (S_SPLINT_S)
  typedef unsigned long uint32_t;
# define UINT32_C(v) v ## UL
# ifndef PRINTF_INT32_MODIFIER
#  define PRINTF_INT32_MODIFIER "l"
# endif
#elif (UINT_MAX == UINT32_MAX)
  typedef unsigned int uint32_t;
# ifndef PRINTF_INT32_MODIFIER
#  define PRINTF_INT32_MODIFIER ""
# endif
# define UINT32_C(v) v ## U
#elif (USHRT_MAX == UINT32_MAX)
  typedef unsigned short uint32_t;
# define UINT32_C(v) ((unsigned short) (v))
# ifndef PRINTF_INT32_MODIFIER
#  define PRINTF_INT32_MODIFIER ""
# endif
#else
#error "Platform not supported"
#endif
#endif

#ifndef INT32_MAX
# define INT32_MAX (0x7fffffffL)
#endif
#ifndef INT32_MIN
# define INT32_MIN INT32_C(0x80000000)
#endif
#ifndef int32_t
#if (INT_MAX == INT32_MAX) && defined (__GNUC__) && (__GNUC__ > 3)
  typedef signed int int32_t;
# define INT32_C(v) v
# ifndef PRINTF_INT32_MODIFIER
#  define PRINTF_INT32_MODIFIER ""
# endif
#elif (LONG_MAX == INT32_MAX) || defined (S_SPLINT_S)
  typedef signed long int32_t;
# define INT32_C(v) v ## L
# ifndef PRINTF_INT32_MODIFIER
#  define PRINTF_INT32_MODIFIER "l"
# endif
#elif (INT_MAX == INT32_MAX)
  typedef signed int int32_t;
# define INT32_C(v) v
# ifndef PRINTF_INT32_MODIFIER
#  define PRINTF_INT32_MODIFIER ""
# endif
#elif (SHRT_MAX == INT32_MAX)
  typedef signed short int32_t;
# define INT32_C(v) ((short) (v))
# ifndef PRINTF_INT32_MODIFIER
#  define PRINTF_INT32_MODIFIER ""
# endif
#else
#error "Platform not supported"
#endif
#endif

/*
 *  The macro stdint_int64_defined is temporarily used to record
 *  whether or not 64 integer support is available.  It must be
 *  defined for any 64 integer extensions for new platforms that are
 *  added.
 */

#undef stdint_int64_defined
#if (defined(__STDC__) && defined(__STDC_VERSION__)) || defined (S_SPLINT_S)
# if (__STDC__ && __STDC_VERSION >= 199901L) || defined (S_SPLINT_S)
#  define stdint_int64_defined
   typedef long long int64_t;
   typedef unsigned long long uint64_t;
#  define UINT64_C(v) v ## ULL
#  define  INT64_C(v) v ## LL
#  ifndef PRINTF_INT64_MODIFIER
#   define PRINTF_INT64_MODIFIER "ll"
#  endif
# endif
#endif

#if !defined (stdint_int64_defined)
# if defined(__GNUC__) && __WORDSIZE == 64
#  define stdint_int64_defined
   __extension__ typedef long int64_t;
   __extension__ typedef unsigned long uint64_t;
#  define UINT64_C(v) v ## UL
#  define  INT64_C(v) v ## L
#  ifndef PRINTF_INT64_MODIFIER
#   define PRINTF_INT64_MODIFIER "l"
#  endif
#elif defined(__GNUC__)
#  define stdint_int64_defined
   __extension__ typedef long long int64_t;
   __extension__ typedef unsigned long long uint64_t;
#  define UINT64_C(v) v ## ULL
#  define  INT64_C(v) v ## LL
#  ifndef PRINTF_INT64_MODIFIER
#   define PRINTF_INT64_MODIFIER "ll"
#  endif
# elif defined(__MWERKS__) || defined (__SUNPRO_C) || defined (__SUNPRO_CC) || defined (__APPLE_CC__) || defined (_LONG_LONG) || defined (_CRAYC) || defined (S_SPLINT_S)
#  define stdint_int64_defined
   typedef long long int64_t;
   typedef unsigned long long uint64_t;
#  define UINT64_C(v) v ## ULL
#  define  INT64_C(v) v ## LL
#  ifndef PRINTF_INT64_MODIFIER
#   define PRINTF_INT64_MODIFIER "ll"
#  endif
# elif (defined(__WATCOMC__) && defined(__WATCOM_INT64__)) || (defined(_MSC_VER) && _INTEGRAL_MAX_BITS >= 64) || (defined (__BORLANDC__) && __BORLANDC__ > 0x460) || defined (__alpha) || defined (__DECC)
#  define stdint_int64_defined
   typedef __int64 int64_t;
   typedef unsigned __int64 uint64_t;
#  define UINT64_C(v) v ## UI64
#  define  INT64_C(v) v ## I64
#  ifndef PRINTF_INT64_MODIFIER
#   define PRINTF_INT64_MODIFIER "I64"
#  endif
# endif
#endif

#if !defined (LONG_LONG_MAX) && defined (INT64_C)
# define LONG_LONG_MAX INT64_C (9223372036854775807)
#endif
#ifndef ULONG_LONG_MAX
# define ULONG_LONG_MAX UINT64_C (18446744073709551615)
#endif

#if !defined (INT64_MAX) && defined (INT64_C)
# define INT64_MAX INT64_C (9223372036854775807)
#endif
#if !defined (INT64_MIN) && defined (INT64_C)
# define INT64_MIN INT64_C (-9223372036854775808)
#endif
#if !defined (UINT64_MAX) && defined (INT64_C)
# define UINT64_MAX UINT64_C (18446744073709551615)
#endif

/*
 *  Width of hexadecimal for number field.
 */

#ifndef PRINTF_INT64_HEX_WIDTH
# define PRINTF_INT64_HEX_WIDTH "16"
#endif
#ifndef PRINTF_INT32_HEX_WIDTH
# define PRINTF_INT32_HEX_WIDTH "8"
#endif
#ifndef PRINTF_INT16_HEX_WIDTH
# define PRINTF_INT16_HEX_WIDTH "4"
#endif
#ifndef PRINTF_INT8_HEX_WIDTH
# define PRINTF_INT8_HEX_WIDTH "2"
#endif

#ifndef PRINTF_INT64_DEC_WIDTH
# define PRINTF_INT64_DEC_WIDTH "20"
#endif
#ifndef PRINTF_INT32_DEC_WIDTH
# define PRINTF_INT32_DEC_WIDTH "10"
#endif
#ifndef PRINTF_INT16_DEC_WIDTH
# define PRINTF_INT16_DEC_WIDTH "5"
#endif
#ifndef PRINTF_INT8_DEC_WIDTH
# define PRINTF_INT8_DEC_WIDTH "3"
#endif

/*
 *  Ok, lets not worry about 128 bit integers for now.  Moore's law says
 *  we don't need to worry about that until about 2040 at which point
 *  we'll have bigger things to worry about.
 */

#ifdef stdint_int64_defined
  typedef int64_t intmax_t;
  typedef uint64_t uintmax_t;
# define  INTMAX_MAX   INT64_MAX
# define  INTMAX_MIN   INT64_MIN
# define UINTMAX_MAX  UINT64_MAX
# define UINTMAX_C(v) UINT64_C(v)
# define  INTMAX_C(v)  INT64_C(v)
# ifndef PRINTF_INTMAX_MODIFIER
#   define PRINTF_INTMAX_MODIFIER PRINTF_INT64_MODIFIER
# endif
# ifndef PRINTF_INTMAX_HEX_WIDTH
#  define PRINTF_INTMAX_HEX_WIDTH PRINTF_INT64_HEX_WIDTH
# endif
# ifndef PRINTF_INTMAX_DEC_WIDTH
#  define PRINTF_INTMAX_DEC_WIDTH PRINTF_INT64_DEC_WIDTH
# endif
#else
  typedef int32_t intmax_t;
  typedef uint32_t uintmax_t;
# define  INTMAX_MAX   INT32_MAX
# define UINTMAX_MAX  UINT32_MAX
# define UINTMAX_C(v) UINT32_C(v)
# define  INTMAX_C(v)  INT32_C(v)
# ifndef PRINTF_INTMAX_MODIFIER
#   define PRINTF_INTMAX_MODIFIER PRINTF_INT32_MODIFIER
# endif
# ifndef PRINTF_INTMAX_HEX_WIDTH
#  define PRINTF_INTMAX_HEX_WIDTH PRINTF_INT32_HEX_WIDTH
# endif
# ifndef PRINTF_INTMAX_DEC_WIDTH
#  define PRINTF_INTMAX_DEC_WIDTH PRINTF_INT32_DEC_WIDTH
# endif
#endif

/*
 *  Because this file currently only supports platforms which have
 *  precise powers of 2 as bit sizes for the default integers, the
 *  least definitions are all trivial.  Its possible that a future
 *  version of this file could have different definitions.
 */

#ifndef stdint_least_defined
  typedef   int8_t   int_least8_t;
  typedef  uint8_t  uint_least8_t;
  typedef  int16_t  int_least16_t;
  typedef uint16_t uint_least16_t;
  typedef  int32_t  int_least32_t;
  typedef uint32_t uint_least32_t;
# define PRINTF_LEAST32_MODIFIER PRINTF_INT32_MODIFIER
# define PRINTF_LEAST16_MODIFIER PRINTF_INT16_MODIFIER
# define  UINT_LEAST8_MAX  UINT8_MAX
# define   INT_LEAST8_MAX   INT8_MAX
# define UINT_LEAST16_MAX UINT16_MAX
# define  INT_LEAST16_MAX  INT16_MAX
# define UINT_LEAST32_MAX UINT32_MAX
# define  INT_LEAST32_MAX  INT32_MAX
# define   INT_LEAST8_MIN   INT8_MIN
# define  INT_LEAST16_MIN  INT16_MIN
# define  INT_LEAST32_MIN  INT32_MIN
# ifdef stdint_int64_defined
    typedef  int64_t  int_least64_t;
    typedef uint64_t uint_least64_t;
#   define PRINTF_LEAST64_MODIFIER PRINTF_INT64_MODIFIER
#   define UINT_LEAST64_MAX UINT64_MAX
#   define  INT_LEAST64_MAX  INT64_MAX
#   define  INT_LEAST64_MIN  INT64_MIN
# endif
#endif
#undef stdint_least_defined

/*
 *  The ANSI C committee pretending to know or specify anything about
 *  performance is the epitome of misguided arrogance.  The mandate of
 *  this file is to *ONLY* ever support that absolute minimum
 *  definition of the fast integer types, for compatibility purposes.
 *  No extensions, and no attempt to suggest what may or may not be a
 *  faster integer type will ever be made in this file.  Developers are
 *  warned to stay away from these types when using this or any other
 *  stdint.h.
 */

#ifndef int_fast8_t
typedef   int_least8_t   int_fast8_t;
#endif
#ifndef uint_fast8_t
typedef  uint_least8_t  uint_fast8_t;
#endif
#ifndef int_fast16_t
typedef  int_least16_t  int_fast16_t;
#endif
#ifndef uint_fast16_t
typedef uint_least16_t uint_fast16_t;
#endif
#ifndef int_fast32_t
typedef  int_least32_t  int_fast32_t;
#endif
#ifndef uint_fast32_t
typedef uint_least32_t uint_fast32_t;
#endif
#define  UINT_FAST8_MAX  UINT_LEAST8_MAX
#define   INT_FAST8_MAX   INT_LEAST8_MAX
#define UINT_FAST16_MAX UINT_LEAST16_MAX
#define  INT_FAST16_MAX  INT_LEAST16_MAX
#define UINT_FAST32_MAX UINT_LEAST32_MAX
#define  INT_FAST32_MAX  INT_LEAST32_MAX
#define   INT_FAST8_MIN   INT_LEAST8_MIN
#define  INT_FAST16_MIN  INT_LEAST16_MIN
#define  INT_FAST32_MIN  INT_LEAST32_MIN
#ifdef stdint_int64_defined
  typedef  int_least64_t  int_fast64_t;
  typedef uint_least64_t uint_fast64_t;
# define UINT_FAST64_MAX UINT_LEAST64_MAX
# define  INT_FAST64_MAX  INT_LEAST64_MAX
# define  INT_FAST64_MIN  INT_LEAST64_MIN
#endif

#undef stdint_int64_defined

/*
 *  Whatever piecemeal, per compiler thing we can do about the wchar_t
 *  type limits.
 */

#if defined(__WATCOMC__) || defined(_MSC_VER) || defined (__GNUC__)
# include <wchar.h>
# ifndef WCHAR_MIN
#  define WCHAR_MIN 0
# endif
# ifndef WCHAR_MAX
#  define WCHAR_MAX ((wchar_t)-1)
# endif
#endif

/*
 *  Whatever piecemeal, per compiler/platform thing we can do about the
 *  (u)intptr_t types and limits.
 */

#if defined (_MSC_VER) && defined (_UINTPTR_T_DEFINED)
# define STDINT_H_UINTPTR_T_DEFINED
#endif

#ifndef STDINT_H_UINTPTR_T_DEFINED
# if defined (__alpha__) || defined (__ia64__) || defined (__x86_64__) || defined (_WIN64)
#  define stdint_intptr_bits 64
# elif defined (__WATCOMC__) || defined (__TURBOC__)
#  if defined(__TINY__) || defined(__SMALL__) || defined(__MEDIUM__)
#    define stdint_intptr_bits 16
#  else
#    define stdint_intptr_bits 32
#  endif
# elif defined (__i386__) || defined (_WIN32) || defined (WIN32)
#  define stdint_intptr_bits 32
# elif defined (__INTEL_COMPILER)
/* TODO -- what will Intel do about x86-64? */
# endif

# ifdef stdint_intptr_bits
#  define stdint_intptr_glue3_i(a,b,c)  a##b##c
#  define stdint_intptr_glue3(a,b,c)    stdint_intptr_glue3_i(a,b,c)
#  ifndef PRINTF_INTPTR_MODIFIER
#    define PRINTF_INTPTR_MODIFIER      stdint_intptr_glue3(PRINTF_INT,stdint_intptr_bits,_MODIFIER)
#  endif
#  ifndef PTRDIFF_MAX
#    define PTRDIFF_MAX                 stdint_intptr_glue3(INT,stdint_intptr_bits,_MAX)
#  endif
#  ifndef PTRDIFF_MIN
#    define PTRDIFF_MIN                 stdint_intptr_glue3(INT,stdint_intptr_bits,_MIN)
#  endif
#  ifndef UINTPTR_MAX
#    define UINTPTR_MAX                 stdint_intptr_glue3(UINT,stdint_intptr_bits,_MAX)
#  endif
#  ifndef INTPTR_MAX
#    define INTPTR_MAX                  stdint_intptr_glue3(INT,stdint_intptr_bits,_MAX)
#  endif
#  ifndef INTPTR_MIN
#    define INTPTR_MIN                  stdint_intptr_glue3(INT,stdint_intptr_bits,_MIN)
#  endif
#  ifndef INTPTR_C
#    define INTPTR_C(x)                 stdint_intptr_glue3(INT,stdint_intptr_bits,_C)(x)
#  endif
#  ifndef UINTPTR_C
#    define UINTPTR_C(x)                stdint_intptr_glue3(UINT,stdint_intptr_bits,_C)(x)
#  endif
  typedef stdint_intptr_glue3(uint,stdint_intptr_bits,_t) uintptr_t;
  typedef stdint_intptr_glue3( int,stdint_intptr_bits,_t)  intptr_t;
# else
/* TODO -- This following is likely wrong for some platforms, and does
   nothing for the definition of uintptr_t. */
  typedef ptrdiff_t intptr_t;
# endif
# define STDINT_H_UINTPTR_T_DEFINED
#endif

/*
 *  Assumes sig_atomic_t is signed and we have a 2s complement machine.
 */

#ifndef SIG_ATOMIC_MAX
# define SIG_ATOMIC_MAX ((((sig_atomic_t) 1) << (sizeof (sig_atomic_t)*CHAR_BIT-1)) - 1)
#endif

#endif


/*! \cond NODOXYGEN */

#ifndef _XSENS_STD_H_2006_09_11
#	define _XSENS_STD_H_2006_09_11

//////////////////////////////////////////////////////////////////////////////////////////

#if defined(_WIN32) && !defined(_WIN32_WINNT)
#	define _WIN32_WINNT 0x0502
#endif

#ifdef _WIN32
#	include <windows.h>
#endif

/*! \endcond */

//////////////////////////////////////////////////////////////////////////////////////////
//! Xsens return values
// NOTE!!! When adding a value to this list, also add its description in xsens_std.cpp
typedef enum /*! \cond NODOXYGEN */ _XsensResultValue_ /*! \endcond */ {
	// general OK
	 XRV_OK					= 0		//!< Operation was performed successfully

	// communication protocol
	,XRV_NOBUS				= 1		//!< No bus communication possible
	,XRV_BUSNOTREADY		= 2		//!< InitBus and/or SetBID are not issued
	,XRV_INVALIDPERIOD		= 3		//!< Period sent is invalid
	,XRV_INVALIDMSG			= 4		//!< The message is invalid or not implemented
	,XRV_INITBUSFAIL1		= 16	//!< A slave did not respond to WaitForSetBID
	,XRV_INITBUSFAIL2		= 17	//!< An incorrect answer received after WaitForSetBID
	,XRV_INITBUSFAIL3		= 18	//!< After four bus-scans still undetected Motion Trackers
	,XRV_SETBIDFAIL1		= 20	//!< No reply to SetBID message during SetBID procedure
	,XRV_SETBIDFAIL2		= 21	//!< Other than SetBIDAck received
	,XRV_MEASUREMENTFAIL1	= 24	//!< Timer overflow - period too short to collect all data from Motion Trackers
	,XRV_MEASUREMENTFAIL2	= 25	//!< Motion Tracker responds with other than SlaveData message
	,XRV_MEASUREMENTFAIL3	= 26	//!< Total bytes of data of Motion Trackers including sample counter exceeds 255 bytes
	,XRV_MEASUREMENTFAIL4	= 27	//!< Timer overflows during measurement
	,XRV_MEASUREMENTFAIL5	= 28	//!< Timer overflows during measurement
	,XRV_MEASUREMENTFAIL6	= 29	//!< No correct response from Motion Tracker during measurement
	,XRV_TIMEROVERFLOW		= 30	//!< Timer overflows during measurement
	,XRV_BAUDRATEINVALID	= 32	//!< Baud rate does not comply with valid range
	,XRV_PARAMINVALID		= 33	//!< An invalid parameter is supplied
	,XRV_INVALIDPARAM		= 33	//!< An invalid parameter is supplied
	,XRV_MEASUREMENTFAIL7	= 35	//!< TX PC Buffer is full
	,XRV_MEASUREMENTFAIL8	= 36	//!< TX PC Buffer overflow, cannot fit full message
	,XRV_DEVICEERROR		= 40	//!< The device generated an error, try updating the firmware

	// CMT / XME / etc
	,XRV_ERROR				= 256	//!< A generic error occurred
	,XRV_NOTIMPLEMENTED		= 257	//!< Operation not implemented in this version (yet)
	,XRV_TIMEOUT			= 258	//!< A timeout occurred
	,XRV_TIMEOUTNODATA		= 259	//!< Operation aborted because of no data read
	,XRV_CHECKSUMFAULT		= 260	//!< Checksum fault occurred
	,XRV_OUTOFMEMORY		= 261	//!< No internal memory available
	,XRV_NOTFOUND			= 262	//!< The requested item was not found
	,XRV_UNEXPECTEDMSG		= 263	//!< Unexpected message received (e.g. no acknowledge message received)
	,XRV_INVALIDID			= 264	//!< Invalid id supplied
	,XRV_INVALIDOPERATION	= 265		//!< Operation is invalid at this point
	,XRV_INSUFFICIENTSPACE		= 266	//!< Insufficient buffer space available
	,XRV_INPUTCANNOTBEOPENED	= 267	//!< The specified i/o device can not be opened
	,XRV_OUTPUTCANNOTBEOPENED	= 268	//!< The specified i/o device can not be opened
	,XRV_ALREADYOPEN			= 269	//!< An I/O device is already opened with this object
	,XRV_ENDOFFILE			= 270		//!< End of file is reached
	,XRV_COULDNOTREADSETTINGS	= 271	//!< A required settings file could not be opened or is missing some data
	,XRV_NODATA				= 272	//!< No data is available
	,XRV_READONLY			= 273	//!< Tried to change a read-only value
	,XRV_NULLPTR			= 274	//!< Tried to supply a NULL value where it is not allowed
	,XRV_INSUFFICIENTDATA	= 275	//!< Insufficient data was supplied to a function
	,XRV_BUSY				= 276	//!< Busy processing, try again later
	,XRV_INVALIDINSTANCE	= 277	//!< Invalid instance called
	,XRV_DATACORRUPT		= 278	//!< A trusted data stream proves to contain corrupted data

	,XRV_READINITFAILED		= 279	//!< Failure during read of settings
	,XRV_NOXMFOUND			= 280	//!< Could not find any MVN-compatible hardware
	,XRV_ONLYONEXMFOUND		= 281	//!< Found only one responding Xbus Master
	,XRV_MTCOUNTZERO			= 282	//!< No sensors found
	,XRV_MTLOCATIONINVALID	= 283	//!< One or more sensors are not where they were expected
	,XRV_INSUFFICIENTMTS		= 284	//!< Not enough sensors were found
	,XRV_INITFUSIONFAILED		= 285	//!< Failure during initialization of Fusion Engine
	,XRV_OTHER					= 286	//!< Something else was received than was requested

	,XRV_NOFILEOPEN			= 287	//!< No file opened for reading/writing
	,XRV_NOPORTOPEN			= 288	//!< No serial port opened for reading/writing
	,XRV_NOFILEORPORTOPEN	= 289	//!< No file or serial port opened for reading/writing
	,XRV_PORTNOTFOUND		= 290	//!< A required port could not be found
	,XRV_INITPORTFAILED		= 291	//!< The low-level port handler failed to initialize
	,XRV_CALIBRATIONFAILED	= 292	//!< A calibration routine failed

	,XRV_CONFIGCHECKFAIL	= 293	//!< The in-config check of the device failed
	,XRV_ALREADYDONE		= 294	//!< The operation is once only and has already been performed

	,XRV_SYNC_SINGLE_SLAVE	= 295	//!< The single connected device is configured as a slave
	,XRV_SYNC_SECOND_MASTER	= 296	//!< More than one master was detected
	,XRV_SYNC_NO_SYNC		= 297	//!< A device was detected that was neither master nor slave
	,XRV_SYNC_NO_MASTER		= 298	//!< No master detected
	,XRV_SYNC_DATA_MISSING	= 299	//!< A device is not sending enough data

	,XRV_VERSION_TOO_LOW	= 300	//!< The version of the object is too low for the requested operation
	,XRV_VERSION_PROBLEM	= 301	//!< The object has an unrecognized version, so it's not safe to perform the operation

	,XRV_ABORTED			= 302	//!< The process was aborted by an external event, usually a user action or process termination
} XsensResultValue;

//////////////////////////////////////////////////////////////////////////////////////////

/*! \cond NODOXYGEN */
#ifndef DELNUL
//! This macro deletes a pointer and sets it to NULL
#define DELNUL(ptr)		{ delete ptr; ptr = NULL; }
//! This macro deletes a pointer if it is not NULL and then sets it to NULL
#define CHKDELNUL(ptr)	{ if (ptr != NULL) { delete ptr; ptr = NULL; } }
//! This macro deletes a multi-object pointer and sets it to NULL
#define LSTDELNUL(ptr)		{ delete[] ptr; ptr = NULL; }
//! This macro deletes a multi-object pointer if it is not NULL and then sets it to NULL
#define LSTCHKDELNUL(ptr)	{ if (ptr != NULL) { delete[] ptr; ptr = NULL; } }

//! This macro frees a pointer and then sets it to NULL
#define FREENUL(ptr)	{ free(ptr); ptr = NULL; }
//! This macro frees a pointer if it is not NULL and then sets it to NULL
#define CHKFREENUL(ptr)	{ if (ptr != NULL) { free(ptr); ptr = NULL; } }
#endif
/*! \endcond */

//////////////////////////////////////////////////////////////////////////////////////////

/* \brief Retrieve a string corresponding to the given result code.

	This function uses the CmtResultText list to return a string with the relevant result 
	code in a textual format. If the supplied result code is invalid the
	"!!Invalid result code!!" string is returned.
*/
#if !defined(_CMT_DLL_IMPORT) && !defined(_XME_DLL_IMPORT)
const char* xsensResultText(const XsensResultValue result);
#endif

//////////////////////////////////////////////////////////////////////////////////////////

#define XSENS_LABEL_SIZE			256		//!< The maximum length of a label
#define XSENS_SHORT_STRING_SIZE		256		//!< The maximum length of a short string
#define XSENS_LONG_STRING_SIZE		16384	//!< The maximum length of a long string

//////////////////////////////////////////////////////////////////////////////////////////

#endif	// _XSENS_STD_H_2006_09_11
#ifndef _XSENS_TIME_2006_09_12
#define _XSENS_TIME_2006_09_12

#ifndef _PSTDINT_H_INCLUDED
#	include "pstdint.h"
#endif

#include <time.h>

namespace xsens {

//! The number of seconds in a normal day
#define XSENS_SEC_PER_DAY	(60*60*24)
//! The number of milliseconds in a normal day
#define XSENS_MS_PER_DAY	(XSENS_SEC_PER_DAY*1000)

//! A real-time timestamp (ms)
typedef uint64_t TimeStamp;

/*! \brief A platform-independent clock.

	The function returns the time of day in ms since midnight. If the \c date parameter is
	non-NULL, corresponding the date is placed in the variable it points to.
*/
uint32_t getTimeOfDay(tm* date_ = NULL, time_t* secs_ = NULL);

/*! \brief A platform-independent sleep routine.

	Time is measured in ms. The function will not return until the specified
	number of ms have passed.
*/
void msleep(uint32_t ms);

TimeStamp timeStampNow(void);


}	// end of xsens namespace

#endif	// _XSENS_TIME_2006_09_12
#ifndef _CMT_FILE_DEF_H_2007_01_24
#define _CMT_FILE_DEF_H_2007_01_24

#include <stdio.h>

#ifndef _WIN32
#   include <sys/types.h>
#endif

#ifdef _CMT_STATIC_LIB
namespace xsens {
#endif

#ifdef _WIN32
	typedef  __int64	CmtFilePos;
#else
	typedef  off_t		CmtFilePos;
#endif

#ifdef _CMT_STATIC_LIB
}	// end of xsens namespace
#endif

// setFilePos defines
#ifdef _WIN32
#	define CMT_FILEPOS_BEGIN				FILE_BEGIN
#	define CMT_FILEPOS_CURRENT				FILE_CURRENT
#	define CMT_FILEPOS_END					FILE_END
#else
#	define CMT_FILEPOS_BEGIN				SEEK_SET
#	define CMT_FILEPOS_CURRENT				SEEK_CUR
#	define CMT_FILEPOS_END					SEEK_END
#endif

#endif
/*! \file
	\brief	Macros and types for use in the Xsens communication protocol and CMT classes

	This file contains useful macros for the Xsens CMT classes. These include
	Message Ids, sizes of messages, result/error codes, etc.
	
	The macros and enumerators in this file are either used on multiple levels (XsensResultValue)
	or so numerous (CMT_MID_...) that it would not be justifiable to put them in a header
	file of a particular level.

	\section FileCopyright Copyright Notice 
	Copyright (C) Xsens Technologies B.V., 2006.  All rights reserved.

	This source code is intended for use only by Xsens Technologies BV and
	those that have explicit written permission to use it from
	Xsens Technologies BV.

	THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
	KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
	IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
	PARTICULAR PURPOSE.

	\section FileChangelog	Changelog
	\par 2006-05-01, v0.0.1
	\li Job Mulder:	Created Cmtdef.h
	\par 2006-07-21, v0.1.0
	\li Job Mulder:	Updated file for release 0.1.0
*/

#ifndef _CMTDEF_H_2006_05_01
#define _CMTDEF_H_2006_05_01

#include <time.h>

#ifdef _WIN32
#else
#	include <termios.h>
#	include <string.h>
#	ifndef	B460800
#		undef	B230400
#		define	B230400	0010003
#		define  B460800 0010004
#		define  B921600 0010007
#	endif
// required for gnu c++ compiler due to difference in attribute declarations
#   define __cdecl __attribute__((cdecl))
#   define __stdcall __attribute__((stdcall))
#endif

#ifndef _XSENS_STD_H_2006_09_11
#	include "xsens_std.h"
#endif
#if !defined(_XSENS_TIME_2006_09_12) && !defined(_CMT_DLL_IMPORT)
#	include "xsens_time.h"
#endif

#ifndef _CMT_FILE_DEF_H_2007_01_24
#	include "cmtf.h"
#endif

//////////////////////////////////////////////////////////////////////////////////////////
// Field message indices
#define CMT_IND_PREAMBLE				0
#define CMT_IND_BID						1
#define CMT_IND_MID						2
#define CMT_IND_LEN						3
#define CMT_IND_DATA0					4
#define CMT_IND_LENEXTH					4
#define CMT_IND_LENEXTL					5
#define CMT_IND_DATAEXT0				6

#define CMT_PREAMBLE					0xFA
#define CMT_BID_MASTER					0xFF
#define CMT_BID_MT						0x01
#define CMT_EXTLENCODE					0xFF

#define CMT_LEN_MSGHEADER				4
#define CMT_LEN_MSGEXTHEADER			6
#define CMT_LEN_MSGHEADERCS				5
#define CMT_LEN_MSGEXTHEADERCS			7
#define CMT_LEN_CHECKSUM				1
#define CMT_LEN_UNSIGSHORT				2
#define CMT_LEN_UNSIGINT				4
#define CMT_LEN_FLOAT					4

// Maximum message/data length
#define CMT_MAXDATALEN					8192
#define CMT_MAXSHORTDATALEN				254
#define CMT_MAXMSGLEN					(CMT_MAXDATALEN+7)
#define CMT_MAXSHORTMSGLEN				(CMT_MAXSHORTDATALEN+5)
#define CMT_MAXGARBAGE					(CMT_MAXMSGLEN+1)


// DID Type (high nibble)
#define CMT_DID_TYPEH_MASK				0x00F00000
#define CMT_DID_TYPEL_MASK				0x000F0000
#define CMT_DID_TYPEH_MT				0x00000000
#define CMT_DID_TYPEH_XM				0x00100000
#define CMT_DID_TYPEH_MTI_MTX			0x00300000
#define CMT_DID_TYPEH_MTIG				0x00500000
#define CMT_DID_TYPE_MASK				0x00FF0000
#define CMT_DID_TYPE_MASK_MT_232		0x00300000
#define CMT_DID_TYPE_MASK_MT_422		0x00310000
#define CMT_DID_TYPE_MASK_MT_XM			0x00020000
#define CMT_DID_TYPE_MASK_MT_485		0x00330000

// All Message identifiers
// WakeUp state messages
#define CMT_MID_WAKEUP					0x3E
#define CMT_MID_WAKEUPACK				0x3F

// Config state messages
#define CMT_MID_REQDID					0x00
#define CMT_MID_DEVICEID				0x01
#define CMT_LEN_DEVICEID				4
#define CMT_MID_INITBUS					0x02
#define CMT_MID_INITBUSRESULTS			0x03
#define CMT_LEN_INITBUSRESULTS			4
#define CMT_MID_REQPERIOD				0x04
#define CMT_MID_REQPERIODACK			0x05
#define CMT_LEN_PERIOD					2
#define CMT_MID_SETPERIOD				0x04
#define CMT_MID_SETPERIODACK			0x05
// XbusMaster
#define CMT_MID_SETBID					0x06
#define CMT_MID_SETBIDACK				0x07
#define CMT_MID_AUTOSTART				0x06
#define CMT_MID_AUTOSTARTACK			0x07
#define CMT_MID_BUSPWR					0x08
#define CMT_LEN_BUSPWR					2
#define CMT_MID_BUSPWRACK				0x09
// End XbusMaster
#define CMT_MID_REQDATALENGTH			0x0A
#define CMT_MID_DATALENGTH				0x0B
#define CMT_LEN_DATALENGTH				2
#define CMT_MID_REQCONFIGURATION		0x0C
#define CMT_MID_CONFIGURATION			0x0D
#define CMT_LEN_CONFIGURATION			118
#define CMT_MID_RESTOREFACTORYDEF		0x0E
#define CMT_MID_RESTOREFACTORYDEFACK	0x0F

#define CMT_MID_GOTOMEASUREMENT			0x10
#define CMT_MID_GOTOMEASUREMENTACK		0x11
#define CMT_MID_REQFWREV				0x12
#define CMT_MID_FIRMWAREREV				0x13
#define CMT_LEN_FIRMWAREREV				3
// XbusMaster
#define CMT_MID_REQBTDISABLE			0x14
#define CMT_MID_REQBTDISABLEACK			0x15
#define CMT_LEN_BTDISABLE				1
#define CMT_MID_DISABLEBT				0x14
#define CMT_MID_DISABLEBTACK			0x15
#define CMT_MID_REQOPMODE				0x16
#define CMT_MID_REQOPMODEACK			0x17
#define CMT_LEN_OPMODE					1
#define CMT_MID_SETOPMODE				0x16
#define CMT_MID_SETOPMODEACK			0x17
// End XbusMaster
#define CMT_MID_REQBAUDRATE				0x18
#define CMT_MID_REQBAUDRATEACK			0x19
#define CMT_LEN_BAUDRATE				1
#define CMT_MID_SETBAUDRATE				0x18
#define CMT_MID_SETBAUDRATEACK			0x19
// XbusMaster
#define CMT_MID_REQSYNCMODE				0x1A
#define CMT_MID_REQSYNCMODEACK			0x1B
#define CMT_LEN_SYNCMODE				1
#define CMT_MID_SETSYNCMODE				0x1A
#define CMT_MID_SETSYNCMODEACK			0x1B
// End XbusMaster
#define CMT_MID_REQPRODUCTCODE			0x1C
#define CMT_MID_PRODUCTCODE				0x1D
#define CMT_LEN_PRODUCTCODE				20

#define CMT_MID_REQPROCESSINGFLAGS		0x20
#define CMT_MID_REQPROCESSINGFLAGSACK	0x21
#define CMT_LEN_PROCESSINGFLAGS			2
#define CMT_MID_SETPROCESSINGFLAGS		0x20
#define CMT_MID_SETPROCESSINGFLAGSACK	0x21

// XbusMaster
#define CMT_MID_XMPWROFF				0x44
#define CMT_LEN_XMPWROFF				0
// End XbusMaster

#define CMT_MID_REQOUTPUTMODE			0xD0
#define CMT_MID_REQOUTPUTMODEACK		0xD1
#define CMT_LEN_OUTPUTMODE		 		2
#define CMT_MID_SETOUTPUTMODE			0xD0
#define CMT_MID_SETOUTPUTMODEACK		0xD1

#define CMT_MID_REQOUTPUTSETTINGS		0xD2
#define CMT_MID_REQOUTPUTSETTINGSACK	0xD3
#define CMT_LEN_OUTPUTSETTINGS		 	4
#define CMT_MID_SETOUTPUTSETTINGS		0xD2
#define CMT_MID_SETOUTPUTSETTINGSACK	0xD3

#define CMT_MID_REQOUTPUTSKIPFACTOR		0xD4
#define CMT_MID_REQOUTPUTSKIPFACTORACK	0xD5
#define CMT_LEN_OUTPUTSKIPFACTOR		2
#define CMT_MID_SETOUTPUTSKIPFACTOR		0xD4
#define CMT_MID_SETOUTPUTSKIPFACTORACK	0xD5

#define CMT_MID_REQSYNCINSETTINGS		0xD6
#define CMT_MID_REQSYNCINSETTINGSACK	0xD7
#define CMT_LEN_SYNCINMODE				2
#define CMT_LEN_SYNCINSKIPFACTOR		2
#define CMT_LEN_SYNCINOFFSET			4
#define CMT_MID_SETSYNCINSETTINGS		0xD6
#define CMT_MID_SETSYNCINSETTINGSACK	0xD7

#define CMT_MID_REQSYNCOUTSETTINGS		0xD8
#define CMT_MID_REQSYNCOUTSETTINGSACK	0xD9
#define CMT_LEN_SYNCOUTMODE				2
#define CMT_LEN_SYNCOUTSKIPFACTOR		2
#define CMT_LEN_SYNCOUTOFFSET			4
#define CMT_LEN_SYNCOUTPULSEWIDTH		4
#define CMT_MID_SETSYNCOUTSETTINGS		0xD8
#define CMT_MID_SETSYNCOUTSETTINGSACK	0xD9

#define CMT_MID_REQERRORMODE			0xDA
#define CMT_MID_REQERRORMODEACK			0xDB
#define CMT_LEN_ERRORMODE				2
#define CMT_MID_SETERRORMODE			0xDA
#define CMT_MID_SETERRORMODEACK			0xDB

#define CMT_MID_REQTRANSMITDELAY		0xDC
#define CMT_MID_REQTRANSMITDELAYACK		0xDD
#define CMT_LEN_TRANSMITDELAY			2
#define CMT_MID_SETTRANSMITDELAY		0xDC
#define CMT_MID_SETTRANSMITDELAYACK		0xDD	

#define CMT_MID_REQOBJECTALIGNMENT		0xE0	
#define CMT_MID_REQOBJECTALIGNMENTACK	0xE1
#define CMT_LEN_OBJECTALIGNMENT			36
#define CMT_MID_SETOBJECTALIGNMENT		0xE0	
#define CMT_MID_SETOBJECTALIGNMENTACK	0xE1

// Xbus Master
#define CMT_MID_REQXMERRORMODE			0x82
#define CMT_MID_REQXMERRORMODEACK		0x83
#define CMT_LEN_XMERRORMODE				2
#define CMT_MID_SETXMERRORMODE			0x82
#define CMT_MID_SETXMERRORMODEACK		0x83

#define CMT_MID_REQBUFFERSIZE			0x84
#define CMT_MID_REQBUFFERSIZEACK		0x85
#define CMT_LEN_BUFFERSIZE				2
#define CMT_MID_SETBUFFERSIZE			0x84
#define CMT_MID_SETBUFFERSIZEACK		0x85			
// End Xbus Master

#define CMT_MID_REQHEADING				0x82
#define CMT_MID_REQHEADINGACK			0x83
#define CMT_LEN_HEADING		 			4
#define CMT_MID_SETHEADING				0x82
#define CMT_MID_SETHEADINGACK			0x83

#define CMT_MID_REQMAGNETICDECLINATION		0x6A
#define CMT_MID_REQMAGNETICDECLINATIONACK	0x6B
#define CMT_LEN_MAGNETICDECLINATION		 	4
#define CMT_MID_SETMAGNETICDECLINATION		0x6A
#define CMT_MID_SETMAGNETICDECLINATIONACK	0x6B

#define CMT_MID_REQLOCATIONID			0x84
#define CMT_MID_REQLOCATIONIDACK		0x85
#define CMT_LEN_LOCATIONID				2
#define CMT_MID_SETLOCATIONID			0x84
#define CMT_MID_SETLOCATIONIDACK		0x85

#define CMT_MID_REQEXTOUTPUTMODE		0x86
#define CMT_MID_REQEXTOUTPUTMODEACK		0x87
#define CMT_LEN_EXTOUTPUTMODE			2
#define CMT_MID_SETEXTOUTPUTMODE		0x86
#define CMT_MID_SETEXTOUTPUTMODEACK		0x87

// XbusMaster
#define CMT_MID_REQBATLEVEL				0x88
#define CMT_MID_BATLEVEL				0x89
// End XbusMaster

#define CMT_MID_REQINITTRACKMODE		0x88
#define CMT_MID_REQINITTRACKMODEACK		0x89
#define CMT_LEN_INITTRACKMODE			2
#define CMT_MID_SETINITTRACKMODE		0x88
#define CMT_MID_SETINITTRACKMODEACK		0x89

// obsolete
//#define CMT_MID_STOREFILTERSTATE		0x8A
//#define CMT_LEN_STOREFILTERSTATE		0
//#define CMT_MID_STOREFILTERSTATEACK	0x8B
// new definition
#define CMT_MID_STOREXKFSTATE			0x8A
#define CMT_LEN_STOREXKFSTATE			0
#define CMT_MID_STOREXKFSTATEACK		0x8B

#define CMT_MID_REQUTCTIME				0x60
#define CMT_MID_UTCTIME					0x61
#define CMT_LEN_UTCTIME					12

#define CMT_LEN_SCENARIOLABEL			20
#define CMT_LEN_SCENARIOFULL			(1+1+CMT_LEN_SCENARIOLABEL)
#define	CMT_MID_REQAVAILABLESCENARIOS	0x62
#define CMT_MID_AVAILABLESCENARIOS		0x63
#define CMT_LEN_AVAILABLESCENARIOS		(CMT_MAX_SCENARIOS_IN_MT*CMT_LEN_SCENARIOFULL)

#define CMT_MID_REQSCENARIO				0x64
#define CMT_MID_REQSCENARIOACK			0x65
#define CMT_LEN_REQSCENARIOACK			2
#define CMT_MID_SETSCENARIO				0x64
#define CMT_MID_SETSCENARIOACK			0x65
#define CMT_LEN_SETSCENARIO				1

#define CMT_MID_REQGRAVITYMAGNITUDE		0x66
#define CMT_MID_REQGRAVITYMAGNITUDEACK	0x67
#define CMT_MID_SETGRAVITYMAGNITUDE		0x66
#define CMT_MID_SETGRAVITYMAGNITUDEACK	0x67
#define CMT_LEN_GRAVITYMAGNITUDE		4

#define CMT_MID_REQGPSLEVERARM			0x68
#define CMT_MID_REQGPSLEVERARMACK		0x69
#define CMT_MID_SETGPSLEVERARM			0x68
#define CMT_MID_SETGPSLEVERARMACK		0x69
#define CMT_LEN_GPSLEVERARM				12

#define CMT_MID_REQLATLONALT			0x6E
#define CMT_MID_REQLATLONALTACK			0x6F
#define CMT_LEN_LATLONALT				18
#define CMT_MID_SETLATLONALT			0x6E
#define CMT_MID_SETLATLONALTACK			0x6F

// Measurement state
#define CMT_MID_GOTOCONFIG				0x30
#define CMT_MID_GOTOCONFIGACK			0x31
#define CMT_MID_BUSDATA					0x32
#define CMT_MID_MTDATA					0x32

#define CMT_MID_SETNOROTATION			0x22
#define CMT_MID_SETNOROTATIONACK		0x23
#define CMT_LEN_SETNOROTATION			2

// Manual
#define CMT_MID_PREPAREDATA				0x32
#define CMT_MID_REQDATA					0x34
#define CMT_MID_REQDATAACK				0x35

// MTData defines 
// Length of data blocks in bytes
#define CMT_LEN_RAWDATA					20
#define CMT_LEN_CALIBDATA				36
#define CMT_LEN_CALIB_ACCDATA			12
#define CMT_LEN_CALIB_GYRDATA			12
#define CMT_LEN_CALIB_MAGDATA			12
#define CMT_LEN_ORIENT_QUATDATA			16
#define CMT_LEN_ORIENT_EULERDATA		12
#define CMT_LEN_ORIENT_MATRIXDATA		36
#define CMT_LEN_SAMPLECNT				2
#define CMT_LEN_TEMPDATA				4

// Length of data blocks in floats
#define CMT_LEN_CALIBDATA_FLT			9
#define CMT_LEN_TEMPDATA_FLT			1
#define CMT_LEN_ORIENT_QUATDATA_FLT		4
#define CMT_LEN_ORIENT_EULERDATA_FLT	3
#define CMT_LEN_ORIENT_MATRIXDATA_FLT	9

// Indices of fields in DATA field of MTData message in bytes
// use in combination with LEN_CALIB etc
// Un-calibrated raw data
#define CMT_IND_RAW_ACCX				0
#define CMT_IND_RAW_ACCY				2
#define CMT_IND_RAW_ACCZ				4
#define CMT_IND_RAW_GYRX				6
#define CMT_IND_RAW_GYRY				8
#define CMT_IND_RAW_GYRZ				10
#define CMT_IND_RAW_MAGX				12
#define CMT_IND_RAW_MAGY				14
#define CMT_IND_RAW_MAGZ				16
#define CMT_IND_RAW_TEMP				18
// Calibrated data
#define CMT_IND_CALIB_ACCX				0
#define CMT_IND_CALIB_ACCY				4
#define CMT_IND_CALIB_ACCZ				8
#define CMT_IND_CALIB_GYRX				12
#define CMT_IND_CALIB_GYRY				16
#define CMT_IND_CALIB_GYRZ				20
#define CMT_IND_CALIB_MAGX				24
#define CMT_IND_CALIB_MAGY				28
#define CMT_IND_CALIB_MAGZ				32
// Orientation data - quat
#define CMT_IND_ORIENT_Q0				0
#define CMT_IND_ORIENT_Q1				4
#define CMT_IND_ORIENT_Q2				8
#define CMT_IND_ORIENT_Q3				12
// Orientation data - euler
#define CMT_IND_ORIENT_ROLL				0
#define CMT_IND_ORIENT_PITCH			4
#define CMT_IND_ORIENT_YAW				8
// Orientation data - matrix
#define CMT_IND_ORIENT_A				0
#define CMT_IND_ORIENT_B				4
#define CMT_IND_ORIENT_C				8
#define CMT_IND_ORIENT_D				12
#define CMT_IND_ORIENT_E				16
#define CMT_IND_ORIENT_F				20
#define CMT_IND_ORIENT_G				24
#define CMT_IND_ORIENT_H				28
#define CMT_IND_ORIENT_I				32
// Orientation data - euler
#define CMT_IND_SAMPLECNTH				0
#define CMT_IND_SAMPLECNTL				1

// Indices of fields in DATA field of MTData message
// Un-calibrated raw data
#define CMT_FLDNUM_RAW_ACCX				0
#define CMT_FLDNUM_RAW_ACCY				1
#define CMT_FLDNUM_RAW_ACCZ				2
#define CMT_FLDNUM_RAW_GYRX				3
#define CMT_FLDNUM_RAW_GYRY				4
#define CMT_FLDNUM_RAW_GYRZ				5
#define CMT_FLDNUM_RAW_MAGX				6
#define CMT_FLDNUM_RAW_MAGY				7
#define CMT_FLDNUM_RAW_MAGZ				8
#define CMT_FLDNUM_RAW_TEMP				9
// Calibrated data
#define CMT_FLDNUM_CALIB_ACCX			0
#define CMT_FLDNUM_CALIB_ACCY			1
#define CMT_FLDNUM_CALIB_ACCZ			2
#define CMT_FLDNUM_CALIB_GYRX			3
#define CMT_FLDNUM_CALIB_GYRY			4
#define CMT_FLDNUM_CALIB_GYRZ			5
#define CMT_FLDNUM_CALIB_MAGX			6
#define CMT_FLDNUM_CALIB_MAGY			7
#define CMT_FLDNUM_CALIB_MAGZ			8
// Orientation data - quat
#define CMT_FLDNUM_ORIENT_Q0			0
#define CMT_FLDNUM_ORIENT_Q1			1
#define CMT_FLDNUM_ORIENT_Q2			2
#define CMT_FLDNUM_ORIENT_Q3			3
// Orientation data - euler
#define CMT_FLDNUM_ORIENT_ROLL			0
#define CMT_FLDNUM_ORIENT_PITCH			1
#define CMT_FLDNUM_ORIENT_YAW			2
// Orientation data - matrix
#define CMT_FLDNUM_ORIENT_A				0
#define CMT_FLDNUM_ORIENT_B				1
#define CMT_FLDNUM_ORIENT_C				2
#define CMT_FLDNUM_ORIENT_D				3
#define CMT_FLDNUM_ORIENT_E				4
#define CMT_FLDNUM_ORIENT_F				5
#define CMT_FLDNUM_ORIENT_G				6
#define CMT_FLDNUM_ORIENT_H				7
#define CMT_FLDNUM_ORIENT_I				8
// Length
// Uncalibrated raw data
#define CMT_LEN_RAW_ACCX				2
#define CMT_LEN_RAW_ACCY				2
#define CMT_LEN_RAW_ACCZ				2
#define CMT_LEN_RAW_GYRX				2
#define CMT_LEN_RAW_GYRY				2
#define CMT_LEN_RAW_GYRZ				2
#define CMT_LEN_RAW_MAGX				2
#define CMT_LEN_RAW_MAGY				2
#define CMT_LEN_RAW_MAGZ				2
#define CMT_LEN_RAW_TEMP				2
// Calibrated data
#define CMT_LEN_CALIB_ACCX				4
#define CMT_LEN_CALIB_ACCY				4
#define CMT_LEN_CALIB_ACCZ				4
#define CMT_LEN_CALIB_GYRX				4
#define CMT_LEN_CALIB_GYRY				4
#define CMT_LEN_CALIB_GYRZ				4
#define CMT_LEN_CALIB_MAGX				4
#define CMT_LEN_CALIB_MAGY				4
#define CMT_LEN_CALIB_MAGZ				4
// Orientation data - quat
#define CMT_LEN_ORIENT_Q0				4
#define CMT_LEN_ORIENT_Q1				4
#define CMT_LEN_ORIENT_Q2				4
#define CMT_LEN_ORIENT_Q3				4
// Orientation data - euler
#define CMT_LEN_ORIENT_ROLL				4
#define CMT_LEN_ORIENT_PITCH			4
#define CMT_LEN_ORIENT_YAW				4
// Orientation data - matrix
#define CMT_LEN_ORIENT_A				4
#define CMT_LEN_ORIENT_B				4
#define CMT_LEN_ORIENT_C				4
#define CMT_LEN_ORIENT_D				4
#define CMT_LEN_ORIENT_E				4
#define CMT_LEN_ORIENT_F				4
#define CMT_LEN_ORIENT_G				4
#define CMT_LEN_ORIENT_H				4
#define CMT_LEN_ORIENT_I				4

// Defines for getDataValue
#define CMT_VALUE_RAW_ACC				0
#define CMT_VALUE_RAW_GYR				1
#define CMT_VALUE_RAW_MAG				2
#define CMT_VALUE_RAW_TEMP				3
#define CMT_VALUE_CALIB_ACC				4
#define CMT_VALUE_CALIB_GYR				5
#define CMT_VALUE_CALIB_MAG				6
#define CMT_VALUE_ORIENT_QUAT			7
#define CMT_VALUE_ORIENT_EULER			8
#define CMT_VALUE_ORIENT_MATRIX			9
#define CMT_VALUE_SAMPLECNT				10
#define CMT_VALUE_TEMP					11

#define CMT_INVALIDSETTINGVALUE			0xFFFFFFFF


// Valid in all states
#define CMT_MID_RESET					0x40
#define CMT_MID_RESETACK				0x41
#define CMT_MID_ERROR					0x42
// XbusMaster
#define CMT_MID_XMPWROFF				0x44
// End XbusMaster

#define CMT_MID_REQFILTERSETTINGS		0xA0
#define CMT_MID_REQFILTERSETTINGSACK	0xA1
#define CMT_LEN_FILTERSETTINGS			4
#define CMT_MID_SETFILTERSETTINGS		0xA0
#define CMT_MID_SETFILTERSETTINGSACK	0xA1
#define CMT_MID_REQAMD					0xA2
#define CMT_MID_REQAMDACK				0xA3
#define CMT_LEN_AMD						2
#define CMT_MID_SETAMD					0xA2
#define CMT_MID_SETAMDACK				0xA3
#define CMT_MID_RESETORIENTATION		0xA4
#define CMT_MID_RESETORIENTATIONACK		0xA5
#define CMT_LEN_RESETORIENTATION		2

#define CMT_MID_REQGPSSTATUS			0xA6
#define CMT_MID_GPSSTATUS				0xA7
#define CMT_LEN_GPSSTATUS				(1+5*16)

// Baudrate defines for SetBaudrate message
#define CMT_BAUDCODE_4K8				0x0B
#define CMT_BAUDCODE_9K6				0x09
//	#define CMT_BAUDCODE_14K4				0x08
#define CMT_BAUDCODE_19K2				0x07
//	#define CMT_BAUDCODE_28K8				0x06
#define CMT_BAUDCODE_38K4				0x05
#define CMT_BAUDCODE_57K6				0x04
//	#define CMT_BAUDCODE_76K8				0x03
#define CMT_BAUDCODE_115K2				0x02
#define CMT_BAUDCODE_230K4				0x01
#define CMT_BAUDCODE_460K8				0x00
#define CMT_BAUDCODE_921K6_ALT			0x0A		// only usable from FW 2.4.6
#define CMT_BAUDCODE_921K6				0x80

// Xbus protocol error codes (Error)
#define CMT_ERROR_NOBUSCOMM				0x01
#define CMT_ERROR_BUSNOTREADY			0x02
#define CMT_ERROR_PERIODINVALID			0x03
#define CMT_ERROR_MESSAGEINVALID		0x04
#define CMT_ERROR_INITOFBUSFAILED1		0x10
#define CMT_ERROR_INITOFBUSFAILED2		0x11
#define CMT_ERROR_INITOFBUSFAILED3		0x12
#define CMT_ERROR_SETBIDPROCFAILED1		0x14
#define CMT_ERROR_SETBIDPROCFAILED2		0x15
#define CMT_ERROR_MEASUREMENTFAILED1	0x18
#define CMT_ERROR_MEASUREMENTFAILED2	0x19
#define CMT_ERROR_MEASUREMENTFAILED3	0x1A
#define CMT_ERROR_MEASUREMENTFAILED4	0x1B
#define CMT_ERROR_MEASUREMENTFAILED5	0x1C
#define CMT_ERROR_MEASUREMENTFAILED6	0x1D
#define CMT_ERROR_TIMEROVERFLOW			0x1E
#define CMT_ERROR_BAUDRATEINVALID		0x20
#define CMT_ERROR_PARAMETERINVALID		0x21
#define CMT_ERROR_MEASUREMENTFAILED7	0x23

// Error modes (SetErrorMode)
#define CMT_ERRORMODE_IGNORE					0x0000
#define CMT_ERRORMODE_INCSAMPLECNT				0x0001
#define CMT_ERRORMODE_INCSAMPLECNT_SENDERROR	0x0002
#define CMT_ERRORMODE_SENDERROR_GOTOCONFIG		0x0003

// Configuration message defines
#define CMT_CONF_MASTERDID				0
#define CMT_CONF_PERIOD					4
#define CMT_CONF_OUTPUTSKIPFACTOR		6
#define CMT_CONF_SYNCIN_MODE			8
#define CMT_CONF_SYNCIN_SKIPFACTOR		10
#define CMT_CONF_SYNCIN_OFFSET			12
#define CMT_CONF_DATE					16
#define CMT_CONF_TIME					24
#define CMT_CONF_NUMDEVICES				96
// Configuration sensor block properties
#define CMT_CONF_DID					98
#define CMT_CONF_DATALENGTH				102
#define CMT_CONF_OUTPUTMODE				104
#define CMT_CONF_OUTPUTSETTINGS			106
#define CMT_CONF_BLOCKLEN				20
// To calculate the offset in data field for output mode of sensor #2 use
//		CONF_OUTPUTMODE + 1*CONF_BLOCKLEN
#define CMT_CONF_MASTERDIDLEN			4
#define CMT_CONF_PERIODLEN				2
#define CMT_CONF_OUTPUTSKIPFACTORLEN	2
#define CMT_CONF_SYNCIN_MODELEN			2
#define CMT_CONF_SYNCIN_SKIPFACTORLEN	2
#define CMT_CONF_SYNCIN_OFFSETLEN		4
#define CMT_CONF_DATELEN				8
#define CMT_CONF_TIMELEN				8
#define CMT_CONF_RESERVED_CLIENTLEN		32
#define CMT_CONF_RESERVED_HOSTLEN		32
#define CMT_CONF_NUMDEVICESLEN			2
// Configuration sensor block properties
#define CMT_CONF_DIDLEN					4
#define CMT_CONF_DATALENGTHLEN			2
#define CMT_CONF_OUTPUTMODELEN			2
#define CMT_CONF_OUTPUTSETTINGSLEN		4

// Clock frequency for offset & pulse width
#define CMT_SYNC_CLOCKFREQMHZ			29.4912
#define CMT_SYNC_CLOCK_NS_TO_TICKS		(CMT_SYNC_CLOCKFREQMHZ * 1.0e-3)
#define CMT_SYNC_CLOCK_TICKS_TO_NS		(1.0e3 / CMT_SYNC_CLOCKFREQMHZ)

// SyncIn params
#define CMT_PARAM_SYNCIN_MODE			0x00
#define CMT_PARAM_SYNCIN_SKIPFACTOR		0x01
#define CMT_PARAM_SYNCIN_OFFSET			0x02

// SyncIn mode
#define CMT_SYNCIN_DISABLED				0x0000
#define CMT_SYNCIN_EDGE_RISING			0x0001
#define CMT_SYNCIN_EDGE_FALLING			0x0002
#define CMT_SYNCIN_EDGE_BOTH			0x0003
#define CMT_SYNCIN_EDGE_MASK			0x0003
#define CMT_SYNCIN_TYPE_DOSAMPLING		0x0000
#define CMT_SYNCIN_TYPE_SENDLASTDATA	0x0004
#define CMT_SYNCIN_TYPE_CLOCK			0x0010
#define CMT_SYNCIN_TYPE_MASK			0x001C

// SyncOut params
#define CMT_PARAM_SYNCOUT_MODE			0x00
#define CMT_PARAM_SYNCOUT_SKIPFACTOR	0x01
#define CMT_PARAM_SYNCOUT_OFFSET		0x02
#define CMT_PARAM_SYNCOUT_PULSEWIDTH	0x03

// SyncOut mode
#define CMT_SYNCOUT_DISABLED		0x0000
#define CMT_SYNCOUT_TYPE_TOGGLE		0x0001
#define CMT_SYNCOUT_TYPE_PULSE		0x0002
#define CMT_SYNCOUT_POL_NEG			0x0000
#define CMT_SYNCOUT_POL_POS			0x0010
#define CMT_SYNCOUT_TYPE_MASK		0x000F
#define CMT_SYNCOUT_POL_MASK		0x0010

// OutputModes
#define CMT_OUTPUTMODE_MT9				0x8000
#define CMT_OUTPUTMODE_XM				0x0000
#define CMT_OUTPUTMODE_RAW				0x4000
//#define CMT_OUTPUTMODE_RAWGPSPRINT		0x1000	// Obsolete. Use CMT_OUTPUTMODE_GPSPVT_PRESSURE instead
#define CMT_OUTPUTMODE_GPSPVT_PRESSURE	0x1000
#define CMT_OUTPUTMODE_TEMP				0x0001
#define CMT_OUTPUTMODE_CALIB			0x0002
#define CMT_OUTPUTMODE_ORIENT			0x0004
#define CMT_OUTPUTMODE_AUXILIARY		0x0008
#define CMT_OUTPUTMODE_POSITION			0x0010
#define CMT_OUTPUTMODE_VELOCITY			0x0020
#define CMT_OUTPUTMODE_STATUS			0x0800


// CmtOutputSettings
#define CMT_OUTPUTSETTINGS_XM						0x00000001
#define CMT_OUTPUTSETTINGS_TIMESTAMP_NONE			0x00000000
#define CMT_OUTPUTSETTINGS_TIMESTAMP_SAMPLECNT		0x00000001
#define CMT_OUTPUTSETTINGS_TIMESTAMP_SAMPLEUTC		0x00000002
#define CMT_OUTPUTSETTINGS_ORIENTMODE_QUATERNION	0x00000000
#define CMT_OUTPUTSETTINGS_ORIENTMODE_EULER			0x00000004
#define CMT_OUTPUTSETTINGS_ORIENTMODE_MATRIX		0x00000008
#define CMT_OUTPUTSETTINGS_CALIBMODE_ACCGYRMAG		0x00000000
#define CMT_OUTPUTSETTINGS_CALIBMODE_ACC			0x00000060
#define CMT_OUTPUTSETTINGS_CALIBMODE_ACCGYR			0x00000040
#define CMT_OUTPUTSETTINGS_CALIBMODE_ACCMAG			0x00000020
#define CMT_OUTPUTSETTINGS_CALIBMODE_GYR			0x00000050
#define CMT_OUTPUTSETTINGS_CALIBMODE_GYRMAG			0x00000010
#define CMT_OUTPUTSETTINGS_CALIBMODE_MAG			0x00000030
#define CMT_OUTPUTSETTINGS_CALIBMODE_ACCGYRMAG_MASK	0x00000070
#define CMT_OUTPUTSETTINGS_DATAFORMAT_FLOAT			0x00000000
#define CMT_OUTPUTSETTINGS_DATAFORMAT_F1220			0x00000100
#define CMT_OUTPUTSETTINGS_DATAFORMAT_FP1632		0x00000200
#define CMT_OUTPUTSETTINGS_AUXILIARYMODE_AIN1		0x00000800			
#define CMT_OUTPUTSETTINGS_AUXILIARYMODE_AIN2		0x00000400
#define CMT_OUTPUTSETTINGS_POSITIONMODE_LLA_WGS84	0x00000000
#define CMT_OUTPUTSETTINGS_VELOCITYMODE_MS_XYZ		0x00000000
#define CMT_OUTPUTSETTINGS_TIMESTAMP_MASK			0x00000003
#define CMT_OUTPUTSETTINGS_ORIENTMODE_MASK			0x0000000C
#define CMT_OUTPUTSETTINGS_CALIBMODE_ACC_MASK		0x00000010
#define CMT_OUTPUTSETTINGS_CALIBMODE_GYR_MASK		0x00000020
#define CMT_OUTPUTSETTINGS_CALIBMODE_MAG_MASK		0x00000040
#define CMT_OUTPUTSETTINGS_CALIBMODE_MASK			0x00000070
#define CMT_OUTPUTSETTINGS_DATAFORMAT_MASK			0x00000300
#define CMT_OUTPUTSETTINGS_AUXILIARYMODE_AIN1_MASK	0x00000400
#define CMT_OUTPUTSETTINGS_AUXILIARYMODE_AIN2_MASK	0x00000800
#define CMT_OUTPUTSETTINGS_AUXILIARYMODE_MASK		0x00000C00
#define CMT_OUTPUTSETTINGS_POSITIONMODE_MASK		0x0001C000
#define CMT_OUTPUTSETTINGS_VELOCITYMODE_MASK		0x00060000
#define CMT_OUTPUTSETTINGS_COORDINATES_NED			0x80000000

// Extended (analog) Output Modes
#define CMT_EXTOUTPUTMODE_DISABLED			0x0000
#define CMT_EXTOUTPUTMODE_EULER				0x0001

// Initial tracking mode (SetInitTrackMode)
#define CMT_INITTRACKMODE_DISABLED		0x0000
#define CMT_INITTRACKMODE_ENABLED		0x0001

// Filter settings params
#define CMT_PARAM_FILTER_GAIN			0x00
#define CMT_PARAM_FILTER_RHO			0x01
#define CMT_DONOTSTORE					0x00
#define CMT_STORE						0x01

// AMDSetting (SetAMD)
#define CMT_AMDSETTING_DISABLED			0x0000
#define CMT_AMDSETTING_ENABLED			0x0001

// Processing flags
#define CMT_PROCESSINGFLAGS_IGBU_ENABLED	0x0001
#define CMT_PROCESSINGFLAGS_FIXED_GRAVITY	0x0002

// Send raw string mode
#define CMT_SENDRAWSTRING_INIT			0
#define CMT_SENDRAWSTRING_DEFAULT		1
#define CMT_SENDRAWSTRING_SEND			2

// Timeouts	
#define CMT_TO_DEFAULT					500
#define CMT_TO_INIT						250
#define CMT_TO_RETRY					50

#define	CMT_PERIOD_10HZ				11520		// invalid with gps pulse time correction
#define	CMT_PERIOD_12HZ				9600
#define	CMT_PERIOD_15HZ				7680		// invalid with gps pulse time correction
#define	CMT_PERIOD_16HZ				7200
#define	CMT_PERIOD_18HZ				6400		// invalid with gps pulse time correction
#define	CMT_PERIOD_20HZ				5760
#define	CMT_PERIOD_24HZ				4800
#define	CMT_PERIOD_25HZ				4608		// invalid with gps pulse time correction
#define	CMT_PERIOD_30HZ				3840
#define	CMT_PERIOD_32HZ				3600
#define	CMT_PERIOD_36HZ				3200
#define	CMT_PERIOD_40HZ				2880
#define	CMT_PERIOD_45HZ				2560		// invalid with gps pulse time correction
#define	CMT_PERIOD_48HZ				2400
#define	CMT_PERIOD_50HZ				2304		// invalid with gps pulse time correction
#define	CMT_PERIOD_60HZ				1920
#define	CMT_PERIOD_64HZ				1800
#define	CMT_PERIOD_72HZ				1600
#define	CMT_PERIOD_75HZ				1536		// invalid with gps pulse time correction
#define	CMT_PERIOD_80HZ				1440
#define	CMT_PERIOD_90HZ				1280		// invalid with gps pulse time correction
#define	CMT_PERIOD_96HZ				1200

#define	CMT_PERIOD_100HZ			1152
#define	CMT_PERIOD_120HZ			960
#define	CMT_PERIOD_128HZ			900
#define	CMT_PERIOD_144HZ			800
#define	CMT_PERIOD_150HZ			768			// invalid with gps pulse time correction
#define	CMT_PERIOD_160HZ			720
#define	CMT_PERIOD_180HZ			640
#define	CMT_PERIOD_192HZ			600
#define	CMT_PERIOD_200HZ			576
#define	CMT_PERIOD_225HZ			512			// invalid with gps pulse time correction
#define	CMT_PERIOD_240HZ			480
#define	CMT_PERIOD_256HZ			450
#define	CMT_PERIOD_288HZ			400
#define	CMT_PERIOD_300HZ			384
#define	CMT_PERIOD_320HZ			360
#define	CMT_PERIOD_360HZ			320
#define	CMT_PERIOD_384HZ			300
#define	CMT_PERIOD_400HZ			288
#define	CMT_PERIOD_450HZ			256			// invalid with gps pulse time correction
#define	CMT_PERIOD_480HZ			240
#define	CMT_PERIOD_512HZ			225

// openPort baudrates
#ifdef _WIN32
	#define CMT_BAUD_RATE_4800					CBR_4800
	#define CMT_BAUD_RATE_9600					CBR_9600
//	#define CMT_BAUD_RATE_14K4					CBR_14400
	#define CMT_BAUD_RATE_19K2					CBR_19200
//	#define CMT_BAUD_RATE_28K8					28800
	#define CMT_BAUD_RATE_38K4					CBR_38400
	#define CMT_BAUD_RATE_57K6					CBR_57600
	#define CMT_BAUD_RATE_115K2					CBR_115200
	#define CMT_BAUD_RATE_230K4					230400
	#define CMT_BAUD_RATE_460K8					460800
	#define CMT_BAUD_RATE_921K6					921600
#else
	#define CMT_BAUD_RATE_4800					B4800
	#define CMT_BAUD_RATE_9600					B9600
//	#define CMT_BAUD_RATE_14K4					B14400
	#define CMT_BAUD_RATE_19K2					B19200
//	#define CMT_BAUD_RATE_28K8					B28800
	#define CMT_BAUD_RATE_38K4					B38400
	#define CMT_BAUD_RATE_57K6					B57600
	#define CMT_BAUD_RATE_115K2					B115200
	#define CMT_BAUD_RATE_230K4					B230400
	#define CMT_BAUD_RATE_460K8					B460800
	#define CMT_BAUD_RATE_921K6					B921600
#endif

#define CMT_DEFAULT_OUTPUT_MODE			CMT_OUTPUTMODE_ORIENT
#define CMT_DEFAULT_OUTPUT_SETTINGS		(CMT_OUTPUTSETTINGS_ORIENTMODE_QUATERNION |\
										 CMT_OUTPUTSETTINGS_TIMESTAMP_SAMPLECNT)

#define CMT_GOTO_CONFIG_TRIES			3

#define CMT_MAX_DEVICES_PER_PORT		11
#define CMT_DEFAULT_SAMPLE_FREQUENCY	100
#define CMT_DEFAULT_PERIOD				1152
#define CMT_DEFAULT_SKIP				0
#define CMT_DEFAULT_FILTER_GAIN			1.0f
#define CMT_DEFAULT_FILTER_WEIGHTING	1.0f
#define CMT_SYNCOUT_DEFAULT_PULSE_WIDTH	1000000		// 1ms = 1M ns


#define CMT_MAX_PORTS_PER_THREAD	20
#define CMT_MAX_FILES_PER_THREAD	20
#if CMT_MAX_PORTS_PER_THREAD >= CMT_MAX_FILES_PER_THREAD
#	define CMT_MAX_DEVICES			(CMT_MAX_PORTS_PER_THREAD * CMT_MAX_DEVICES_PER_PORT)
#else
#	define CMT_MAX_DEVICES			(CMT_MAX_FILES_PER_THREAD * CMT_MAX_DEVICES_PER_PORT)
#endif
#define CMT_MAX_PACKETS_PER_BUNDLE	CMT_MAX_PORTS_PER_THREAD
#define CMT_BUNDLE_QUEUE_SIZE		256
#define CMT_MAX_ITEMS_IN_PACKET		10

	//! The default size of the serial read buffer in bytes
#define CMT_DEFAULT_READ_BUFFER_SIZE		(CMT_MAXDATALEN*8)
	//! The default size of the serial write buffer in bytes
#define CMT_DEFAULT_WRITE_BUFFER_SIZE		CMT_MAXDATALEN
	//! The default baud rate of the Cmt1s serial communication
#define CMT_DEFAULT_BAUD_RATE				CMT_BAUD_RATE_115K2
	//! The size of the L2 data-message fifo-queue
#define CMT2_DATA_QUEUE_SIZE				60

	//! The timeout value for "goto config"-message acknowledgement
#define CMT3_CONFIG_TIMEOUT				100
	//! The default timeout value for blocking CMT1s operations in ms
#define CMT1_DEFAULT_TIMEOUT			10
	//! Timeout in ms for level 2
#define CMT2_DEFAULT_TIMEOUT			50
	//! The default timeout value for L3 data reading
#define CMT3_DEFAULT_TIMEOUT_MEAS		16
	//! The default timeout value for L3 configuration settings
#define CMT3_DEFAULT_TIMEOUT_CONF		3000
	//! The default timeout value for L4 data reading at L2 and 3
#define CMT4_DEFAULT_TIMEOUT_MEAS		1
	//! The default timeout value for L4 configuration settings
#define CMT4_DEFAULT_TIMEOUT_CONF		CMT3_DEFAULT_TIMEOUT_CONF
	//! The timeout to use for requests during measurement mode
#define CMT4_MEASUREMENT_REQ_TIMEOUT	100
	//! The standard timeout to use for data receipt in measurement mode
#define CMT4_DEFAULT_TIMEOUT_DATA		3000
	//! The timeout used for reading a wakeup message in config mode
#define CMT4_CONFIGWAIT_TIMEOUT			50

enum CmtControlLine {
	CMT_CONTROL_DCD		= 0x0001,		// pin 1: Carrier Detect
	CMT_CONTROL_RD		= 0x0002,		// pin 2: Received Data
	CMT_CONTROL_TD		= 0x0004,		// pin 3: Transmitted Data
	CMT_CONTROL_DTR		= 0x0008,		// pin 4: Data Terminal Ready
	CMT_CONTROL_GND		= 0x0010,		// pin 5: Common Ground
	CMT_CONTROL_DSR		= 0x0020,		// pin 6: Data Set Ready
	CMT_CONTROL_RTS		= 0x0040,		// pin 7: Request To Send
	CMT_CONTROL_CTS		= 0x0080,		// pin 8: Clear To Send
	CMT_CONTROL_RI		= 0x0100		// pin 9: Ring Indicator
};

// Reset orientation message type
enum CmtResetMethod {
	CMT_RESETORIENTATION_STORE = 0,
	CMT_RESETORIENTATION_HEADING,
	CMT_RESETORIENTATION_GLOBAL,
	CMT_RESETORIENTATION_OBJECT,
	CMT_RESETORIENTATION_ALIGN
};

enum CmtXmSyncMode {
	CMT_XM_SYNC_OFF				= 0x00,
	CMT_XM_SYNC_PWM				= 0x01,
	CMT_XM_SYNC_MASTER			= 0x10,
	CMT_XM_SYNC_SLAVE			= 0x20,
	CMT_XM_SYNC_TOGGLE			= 0x30
};

//! The type of a Device Id
typedef uint32_t	CmtDeviceId;

//! A structure for storing the firmware version
struct CmtVersion {
	uint8_t m_major;
	uint8_t m_minor;
	uint8_t m_revision;
};

/* different alignment commands for gcc / MSVS, the structure needs to be 2-byte aligned
	because the deviceId field is 4 bytes long on offset 98.
*/
#ifdef _MSC_VER
	#pragma pack(push, 2)
#endif
//! Structure containing a full device configuration as returned by the ReqConfig message.
struct CmtDeviceConfiguration {
	uint32_t	m_masterDeviceId;
	uint16_t	m_samplingPeriod;
	uint16_t	m_outputSkipFactor;
	uint16_t	m_syncinMode;
	uint16_t	m_syncinSkipFactor;
	uint32_t	m_syncinOffset;
	uint8_t	m_date[8];
	uint8_t	m_time[8];
	uint8_t	m_reservedForHost[32];
	uint8_t	m_reservedForClient[32];
	uint16_t	m_numberOfDevices;
	struct _devInfo {
		uint32_t	m_deviceId;
		uint16_t	m_dataLength;
		uint16_t	m_outputMode;
		uint32_t	m_outputSettings;
		uint16_t	m_currentScenario;
		uint8_t		m_fwRevMajor;
		uint8_t		m_fwRevMinor;
		uint8_t		m_fwRevRevision;
		uint8_t		m_filterType;
		uint8_t		m_filterMajor;
		uint8_t		m_filterMinor;
	} m_deviceInfo[CMT_MAX_DEVICES_PER_PORT];

#ifndef _CMT_DLL_IMPORT
	void readFromMessage(const void* message);
#endif
}
// different alignment commands for gcc / MSVS
#ifdef _MSC_VER
	;
	#pragma pack(pop)
#else
	/*! \cond NODOXYGEN */	__attribute__((__packed__))	/*! \endcond */;
#endif

//////////////////////////////////////////////////////////////////////////////////////////

	//! An output mode bit-field
typedef uint32_t CmtOutputMode;
	//! An output settings bit-field
typedef uint64_t CmtOutputSettings;

	//! A structure for storing data formats
struct CmtDataFormat {
	CmtOutputMode		m_outputMode;
	CmtOutputSettings	m_outputSettings;

#ifndef _CMT_DLL_IMPORT
	//! default constructor, initializes to the given (default) MT settings
	CmtDataFormat(	const CmtOutputMode mode = CMT_DEFAULT_OUTPUT_MODE,
					const CmtOutputSettings settings = CMT_DEFAULT_OUTPUT_SETTINGS)
					: m_outputMode(mode), m_outputSettings(settings) {}
#endif
};

	//! An MT timestamp (sample count)
typedef uint16_t CmtMtTimeStamp;

#define CMT_MAX_FILENAME_LENGTH	512

#define CMT_DID_BROADCAST				0x80000000
#define CMT_DID_MASTER					0


//! A structure for storing sync in settings
struct CmtSyncInSettings {
	uint16_t	m_mode;
	uint16_t	m_skipFactor;
	uint32_t	m_offset;		//!< Offset in ns

#ifndef _CMT_DLL_IMPORT
	//! default constructor, initializes to the given (default) MT settings
	CmtSyncInSettings(	const uint16_t mode = 0,
						const uint16_t skip = 0,
						const uint32_t offset = 0)
						: m_mode(mode), m_skipFactor(skip), m_offset(offset) {}
#endif
};

//! A structure for storing sync out settings
struct CmtSyncOutSettings {
	uint16_t	m_mode;
	uint16_t	m_skipFactor;
	uint32_t	m_offset;		//!< Offset in ns
	uint32_t	m_pulseWidth;	//!< Pulse width in ns

#ifndef _CMT_DLL_IMPORT
	//! default constructor, initializes to the given (default) MT settings
	CmtSyncOutSettings( const uint16_t mode = 0,
						const uint16_t skip = 0,
						const uint32_t offset = 0,
						const uint32_t width = CMT_SYNCOUT_DEFAULT_PULSE_WIDTH) :
						m_mode(mode), m_skipFactor(skip), m_offset(offset),
						m_pulseWidth(width) {}
#endif
};

//! A structure for storing UTC Time values
struct CmtUtcTime
{
	uint32_t	m_nano;
	uint16_t	m_year;
	uint8_t	m_month;
	uint8_t	m_day;
	uint8_t	m_hour;
	uint8_t	m_minute;
	uint8_t	m_second;
	uint8_t	m_valid;	//!< When set to 1, the time is valid, when set to 2, the time part is valid, but the date may not be valid. when set to 0, the time is invalid and should be ignored.
};

//! A structure for storing device modes
struct CmtDeviceMode {
	CmtOutputMode		m_outputMode;
	CmtOutputSettings	m_outputSettings;
	uint16_t		m_sampleFrequency;

#ifndef _CMT_DLL_IMPORT
	//! default constructor, initializes to the given (default) MT settings
	CmtDeviceMode(	const CmtOutputMode mode = CMT_DEFAULT_OUTPUT_MODE,
					const CmtOutputSettings settings = CMT_DEFAULT_OUTPUT_SETTINGS,
					const uint16_t frequency = CMT_DEFAULT_SAMPLE_FREQUENCY) :
						m_outputMode(mode), m_outputSettings(settings),
						m_sampleFrequency(frequency) {}
	
	/*! \brief Compute the period and skip factor.
	
		This function computes the period and skipFactor fields from the stored 
		m_sampleFrequency field. The maximum error in the frequency is approximately 
		0.4%, which occurs at 510Hz (= actually 512 Hz). In general, the higher 
		frequencies are harder to set up exactly.
	*/
	void getPeriodAndSkipFactor(uint16_t& period, uint16_t& skip) const;
	/*! \brief Return the real sample frequency in Hz. 
	
		This may be up to 2Hz different from the value that is set.
	*/
	double getRealSampleFrequency(void) const;
	/*! \brief Compute the sample frequency from a period and skip factor.
	
		This function does the reverse of the getPeriodAndSkipFactor function, storing the
		value in the m_sampleFrequency field.
	*/
	void setPeriodAndSkipFactor(uint16_t period, uint16_t skip);

	//! Check if all fields of the two structures are equal
	bool operator == (const CmtDeviceMode& dev) const;
#endif
};

//! A structure for storing device modes using period and skip factor (new default)
struct CmtDeviceMode2 {
	CmtOutputMode		m_outputMode;
	CmtOutputSettings	m_outputSettings;
	uint16_t		m_period;
	uint16_t		m_skip;

#ifndef _CMT_DLL_IMPORT
	//! default constructor, initializes to the given (default) MT settings
	CmtDeviceMode2(	const CmtOutputMode mode = CMT_DEFAULT_OUTPUT_MODE,
		const CmtOutputSettings settings = CMT_DEFAULT_OUTPUT_SETTINGS,
		const uint16_t period = CMT_DEFAULT_PERIOD,
		const uint16_t skip = CMT_DEFAULT_SKIP) :
	m_outputMode(mode), m_outputSettings(settings),
		m_period(period), m_skip(skip) {}

	/*! \brief Return the real sample frequency in Hz. 

	This may be up to 2Hz different from the value that is set.
	*/
	double getRealSampleFrequency(void) const;
	/*! \brief Return the sample frequency in Hz. 

	This may be up to 2Hz different from the value that is set.
	*/
	uint16_t getSampleFrequency(void) const;
	/*! \brief Compute the period and skip factor from a sample frequency.

	This function does the reverse of the getPeriodAndSkipFactor function, storing the
	value in the m_period and m_skip field.
	*/
	void setSampleFrequency(uint16_t freq);

	//! Check if all fields of the two structures are equal
	bool operator == (const CmtDeviceMode2& dev) const;
#endif
};

#define CMT_MAX_SCENARIOS_IN_MT		5
#define CMT_MAX_SCENARIOS			254

//! A structure for storing scenario information
struct CmtScenario {
	uint8_t m_type;		//!< The type of the scenario. When set to 255 in an operation, the 'current' scenario is used.
	uint8_t m_version;	//!< The version of the scenario.
	char m_label[CMT_LEN_SCENARIOLABEL+1];		//!< The label of the scenario.
	char m_filterType;							//!< The type of the XKF filter this scenario is intended for '3': XKF-3, '6': XKF-6. \note The value is a character, so XKF-3 is '3', which is hex 0x33
	uint8_t m_filterMajor, m_filterMinor;		//!< The version of the XKF filter this scenario is intended for
};

enum CmtCallbackType {
	CMT_CALLBACK_LIST_TERMINATOR	= -1,//!< Not a callback function. Used to define the end of a CallbackSelector list

	CMT_CALLBACK_ONMEASUREMENTPREPARE,	//!< Called right before sending a GotoMeasurement message
	CMT_CALLBACK_ONMEASUREMENTSTART,	//!< Called right after successfully switching to Measurement mode
	CMT_CALLBACK_ONMEASUREMENTSTOP,		//!< Called right before switching from Measurement mode to Config mode
	CMT_CALLBACK_ONPOSTPROCESS,			//!< Called when a full data bundle is available and has been processed by the CMT. The first void* parameter supplied to this function can be handed as the bundle parameter in cmtData... functions to manipulate the newly received bundle.
	CMT_CALLBACK_ONBYTESRECEIVED,		//!< Called when bytes have been read from a port
	CMT_CALLBACK_ONMESSAGERECEIVED,		//!< Called when a full message has been received from a port
	CMT_CALLBACK_ONMESSAGESENT,			//!< Called when a full message has been sent by a port
	CMT_CALLBACK_ONMISSINGSAMPLES,		//!< Called when interpolation mode != 0 and missing samples are detected
	CMT_CALLBACK_ONWAKEUPRECEIVED,		//!< Called when receiving a wakeup message in config mode. Advise to refresh that port cache as soon as possible
	CMT_CALLBACK_ONINSTANCE,			//!< Called when a new CMT instance was created or an existing one is about to be destroyed. Also called once for all existing CMT instances when a plugin becomes enabled. If param is non-null, the instance is created, otherwise it is about to be destroyed. The return value of this callback is ignored.

	CMT_CALLBACK_COUNT					//!< Not a callback function. Used internally for list management
};

#define CmtCallbackSelector	CmtCallbackType

enum CmtQueueMode {
	CMT_QM_FIFO	= 0,
	CMT_QM_LAST = 1,
	CMT_QM_RAW  = 2
};

struct CmtBinaryData {
	int32_t m_size;
	uint8_t m_data[CMT_MAXMSGLEN];
	uint16_t m_portNr;
};

typedef void (__cdecl * CmtCallbackFunction)(int32_t instance, int32_t callbackType, void* param, void* userParam);

//! \brief Structure for storing information about a serial port
struct CmtPortInfo {
	uint32_t m_baudrate;	//!< The baudrate at which an Xsens device was detected
	uint32_t m_deviceId;	//!< The device Id of the detected Xsens device
	uint16_t m_portNr;		//!< The port number
	char m_portName[256];		//!< The port name
#ifdef __cplusplus
#	ifdef _WIN32
		//! greater than operator, used for sorting the list
	bool operator > (const CmtPortInfo& p) const { return m_portNr > p.m_portNr; }
		//! less than operator, used for sorting the list
	bool operator < (const CmtPortInfo& p) const { return m_portNr < p.m_portNr; }
		//! equality operator, used for finding items in a list
	bool operator == (const CmtPortInfo& p) const { return m_portNr == p.m_portNr; }
		//! equality operator, used for finding items in a list
	bool operator == (const uint16_t port) const { return m_portNr == port; }
#	else	// Linux
		//! greater than operator, used for sorting the list
	bool operator > (const CmtPortInfo& p) const { return strcmp(m_portName, p.m_portName) > 0; }
		//! less than operator, used for sorting the list
	bool operator < (const CmtPortInfo& p) const { return strcmp(m_portName, p.m_portName) < 0; }
		//! equality operator, used for finding items in a list
	bool operator == (const CmtPortInfo& p) const { return strcmp(m_portName, p.m_portName) == 0; }
		//! equality operator, used for finding items in a list
	bool operator == (const uint16_t port) const { (void)port; return false; }
#	endif // ifdef _WIN32/Linux
#endif
};

struct CmtShortVector {
	uint16_t m_data[3];
};
struct CmtRawData {
	CmtShortVector	m_acc,m_gyr,m_mag;
	uint16_t	m_temp;
};
struct CmtGpsPvtData {	uint16_t	m_pressure;
	uint8_t		m_pressureAge;
	uint32_t	m_itow;
	int32_t		m_latitude;
	int32_t		m_longitude;
	int32_t		m_height;
	int32_t		m_veln;
	int32_t		m_vele;
	int32_t		m_veld;
	uint32_t	m_hacc;
	uint32_t	m_vacc;
	uint32_t	m_sacc;
	uint8_t	m_gpsAge;
};
#define CmtRawGpsData	CmtGpsPvtData		//!< obsolete, use CmtGpsPvtData instead
struct CmtRawPressureData {
	uint16_t	m_pressure;
	uint8_t		m_pressureAge;
};
struct CmtAnalogInData
{
	uint16_t m_data;
};
struct CmtVector {
	double m_data[3];
};
struct CmtCalData {
	CmtVector	m_acc,m_gyr,m_mag;
};
struct CmtQuat {
	double m_data[4];
};
struct CmtEuler {
	double m_roll;		//!< The roll (rotation around x-axis / back-front-line)
	double m_pitch;		//!< The pitch (rotation around y-axis / right-left-line)
	double m_yaw;		//!< The yaw (rotation around z-axis / down-up-line)
};
struct CmtMatrix {
	double m_data[3][3];
};

#define CMT_MAX_SVINFO		16
struct CmtGpsSatelliteInfo {
	uint8_t m_id;
	uint8_t m_navigationStatus;
	uint8_t m_signalQuality;
	uint8_t m_signalStrength;
};
struct CmtGpsStatus {
	CmtGpsSatelliteInfo m_svInfo[CMT_MAX_SVINFO];
};

typedef uint64_t CmtTimeStamp;

#define CMT_AUTO_SAVE_FRAMES	5000
#define CMT_FILE_LAST_FRAME		0xFFFFFFFF

#define CMT_BID_BROADCAST		(const uint8_t)0x00
#define CMT_BID_INVALID			(const uint8_t)0xFE
#define CMT_MID_REQEMTS			(const uint8_t)0x90
#define CMT_MID_EMTSDATA		(const uint8_t)0x91
#define CMT_EMTS_SIZE			1320

#define CMT_STATUSFLAG_SELFTEST						0x01
#define CMT_STATUSFLAG_XKFVALID						0x02
#define CMT_STATUSFLAG_GPSVALID						0x04
#define CMT_STATUSFLAG_NOROTATION_MASK				0x18
#define CMT_STATUSFLAG_NOROTATION 					0x18
#define CMT_STATUSFLAG_NOROTATION_ABORTED 			0x10
#define CMT_STATUSFLAG_NOROTATION_SAMPLES_REJECTED 	0x08

#define CMT_MAX_VPORTNAME_LEN	32

#endif
#ifndef _CMT1_H_2006_04_12
#define _CMT1_H_2006_04_12

#ifndef _CMTDEF_H_2006_05_01
#	include <cmtdef.h>
#endif

#ifdef _WIN32
#	include <windows.h>
//#	include <sys/types.h>
#else
#	include <termios.h>
// these are not required by level 1, but to keep the higher levels platform-independent they are put here
#	include <stdlib.h>
#	include <string.h>
#	include <stddef.h>
#define _strnicmp	strncasecmp
#endif

#include <stdio.h>

//! The namespace of all Xsens software since 2006.
namespace xsens {

#ifndef CMTLOG
#	if defined(_DEBUG) || defined(_LOG_ALWAYS)
		void CMTLOG(const char *str, ...);
#		define CMTEXITLOG(str)	JanitorFunc2<const char*,XsensResultValue> _cmtExitLog(CMTLOG,str " returns %u",m_lastResult);
#	else
#		define CMTLOG(...)
#		define CMTEXITLOG(...)
#	endif
#endif

#ifndef _WIN32
int _wcsnicmp(const wchar_t* s1, const wchar_t* s2,int count);
#endif

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Cmt1s  /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/*! \brief The low-level serial communication class.
*/
class Cmt1s {
private:
	//! This object cannot be copied, so this function is not implemented.
	Cmt1s(const Cmt1s& ref);

	#ifdef _LOG_RX_TX
		FILE* rx_log;
		FILE* tx_log;
	#endif

	/*! \brief The bytes received function.
	
		This function is automatically called every time binary data is read from the 
		connected COM port.
	*/
	CmtCallbackFunction m_onBytesReceived;
	//! Custom, user supplied parameter for the OnBytesReceived callback function, passed as the first argument
	int32_t m_onBytesReceivedInstance;
	//! Custom, user supplied parameter for the OnBytesReceived callback function, passed as the last argument
	void* m_onBytesReceivedParam;
protected:
		//! The baudrate that was last set to be used by the port
	uint32_t m_baudrate;
		//! The time at which an operation will end in ms, used by several functions.
	uint32_t m_endTime;
		//! Indicates if the port is open or not
	bool m_isOpen;
		//! The last result of an operation
	mutable XsensResultValue m_lastResult;
		//! The opened COM port nr
	uint16_t m_port;
	char m_portname[32];
	/*! The default timeout value to use during blocking operations.
		A value of 0 means that all operations become non-blocking.
	*/
	uint32_t m_timeout;

	#ifdef _WIN32
		DCB		m_commState;		//!< Stored settings about the serial port
		HANDLE	m_handle;			//!< The serial port handle
	#else
		termios	m_commState;		//!< Stored settings about the serial port
		int32_t		m_handle;			//!< The serial port handle
		typedef int32_t HANDLE;
	#endif
public:
		//! Default constructor, initializes all members to their default values.
	Cmt1s();
		//! Destructor, de-initializes, frees memory allocated for buffers, etc.
	~Cmt1s();
		//! \brief Close the serial communication port.
	XsensResultValue close (void);
	/*! \brief Manipulate the Serial control lines

		The function manipulates the serial control lines that are indicated by the 
		mask parameter. Note that only the DTR and RTS lines can be set by win32.
		\param mask		Indicates which lines are to be manipulated and which should be
						left alone.
		\param state	Contains the new state of the control lines.
	*/
	XsensResultValue escape (const CmtControlLine mask, const CmtControlLine state);
	/*! \brief Flush all data to be transmitted / received.
	
		This function tries to send and receive any remaining data immediately 
		and does not return until the buffers are empty.
	*/
	XsensResultValue flushData (void);
		//! Return the baudrate that is currently being used by the port
	uint32_t getBaudrate(void) const { return m_baudrate; }
		//! Return the handle of the port
	HANDLE getHandle(void) const { return m_handle; }
		//! Retrieve the port number that was last successfully opened.
	uint16_t getPortNr (void) const { return m_port; }
		//! Retrieve the port name that was last successfully opened.
	void getPortName(char *portname) const { sprintf(portname, "%s", m_portname); }
		//! Return the error code of the last operation.
	XsensResultValue getLastResult(void) const { return m_lastResult; }
		//! Return the current timeout value
	uint32_t getTimeout (void) const { return m_timeout; }
		//! Return whether the communication port is open or not.
	bool isOpen (void) const { return m_isOpen; }
	
	/*! \brief Open a communcation channel to the given serial port name.
	
		The port is automatically initialized to the given baudrate.
		If the baudrate is set to 0, the baud rate is automatically detected. If possible.
	*/
	XsensResultValue open ( const char *portName,
							const uint32_t baudRate = CMT_DEFAULT_BAUD_RATE,
							uint32_t readBufSize = CMT_DEFAULT_READ_BUFFER_SIZE,
							uint32_t writeBufSize = CMT_DEFAULT_WRITE_BUFFER_SIZE);

#ifdef _WIN32
	/*! \brief Open a communication channel to the given COM port number.
	
		The port is automatically initialized to the given baud rate.
		If the baudrate is set to 0, the baud rate is automatically detected. If possible.
	*/
	XsensResultValue open ( const uint32_t portNumber,
							const uint32_t baudRate = CMT_DEFAULT_BAUD_RATE,
							uint32_t readBufSize = CMT_DEFAULT_READ_BUFFER_SIZE,
							uint32_t writeBufSize = CMT_DEFAULT_WRITE_BUFFER_SIZE);
#endif
	/*! \brief Read data from the serial port and put it into the data buffer.

		This function reads as much data as possible from the com port (non-blocking) and 
		put as much data as will fit into the data buffer. Any excess data is stored in 
		the \c m_readBuffer member variable. If there was enough data in m_readBuffer to 
		fulfill the request, the data parameter is first filled and the port is polled 
		afterwards.
		\param maxLength	The maximum amount of data read.
		\param data			Pointer to a buffer that will store the received data.
		\param length		The number of bytes placed into \c data.
	*/
	XsensResultValue readData (const uint32_t maxLength, uint8_t* data,
								uint32_t* length = NULL);
	//! Set the callback function for when bytes have been received
	XsensResultValue setCallbackFunction(CmtCallbackType tp, int32_t instance, CmtCallbackFunction func, void* param);
	/*! \brief Set the default timeout value to use in blocking operations.

		This function sets the value of m_timeout. There is no infinity value. The value 0 
		means that all blocking operations now become polling (non-blocking) operations. 
		If the value is set to or from 0, the low-level serial port settings may be 
		changed in addition to the m_timeout value.
	*/
	XsensResultValue setTimeout (const uint32_t ms = CMT1_DEFAULT_TIMEOUT);
	/*! \brief Wait for data to arrive or a timeout to occur.

		The function waits until \c maxLength data is available or until a timeout occurs.
		The function returns success if data is available or XsensResultValue::TIMEOUT if a 
		timeout occurred. A timeout value of 0 indicates that the default timeout stored
		in the class should be used.
	*/
	XsensResultValue waitForData (const uint32_t maxLength, uint8_t* data,
								uint32_t* length = NULL);
	/*! \brief Write the data to the serial port.

		The function writes the given data to the connected COM port.
		The default timeout is respected in this operation.
	*/
	XsensResultValue writeData (const uint32_t length, const uint8_t* data,
								uint32_t* written);

};

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Cmt1f  /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/*! \brief The low-level file communication class.
*/
class Cmt1f {
private:
		//! This object cannot be copied, so this function is not implemented.
	Cmt1f(const Cmt1f& ref);

protected:
		//! The file handle
	FILE* m_handle;
		//! Contains the size of the file
	CmtFilePos m_fileSize;
		//! The last read position in the file
	CmtFilePos m_readPos;
		//! The last write position in the file
	CmtFilePos m_writePos;
		//! The last result of an operation
	mutable XsensResultValue m_lastResult;
		//! Contains the name of the file that was last successfully opened.
	char m_filename[CMT_MAX_FILENAME_LENGTH];
		//! Contains the name of the file that was last successfully opened using unicode.
	wchar_t m_filename_w[CMT_MAX_FILENAME_LENGTH];
		//! Indicates if the file is open or not.
	bool m_isOpen;
		//! Indicates if we're using the unicode filename or the regular filename
	bool m_unicode;
	/*! \brief Indicates whether the last operation was a read or write operation.

		This value is used to check whether or not a seek is required to perform a 
		requested read or write operation.
	*/
	bool m_reading;
		//! Indicates if the file was opened in read-only mode
	bool m_readOnly;
		//! Change from writing to reading mode
	void gotoRead(void);
		//! Change from reading to writing mode
	void gotoWrite(void);
public:
		//! Default constructor, initializes all members to their default values.
	Cmt1f();
		//! Destructor.
	~Cmt1f();
	/*! \brief Write data to the end of the file.

		The function writes the given data to the file at the end. The current write
		position is also moved to the end of the file.
	*/
	XsensResultValue appendData(const uint32_t length,  const void* data);
		//! Close the file.
	XsensResultValue close(void);
		//! Close the file and delete it.
	XsensResultValue closeAndDelete(void);
		//! Open an empty file.
	XsensResultValue create(const char* filename);
		//! Open an empty file using a unicode path + filename.
	XsensResultValue create(const wchar_t* filename);
	/*! \brief Delete the given data from the file.
	
		The function erases the given data from the file at the given write position. This
		operation may take a while to complete, but is faster than insertData.

		The write position is not changed and the read position	is checked for validity.
	*/
	XsensResultValue deleteData(const CmtFilePos start, const uint32_t length);
	/*! \brief Find a string of bytes in the file

		The function searches from the current read position until the given \c needle is 
		found. If the needle is not found, XsensResultValue::NOT_FOUND is returned. The function
		will update the seek position to the first character of the found needle.
		\param needle		The byte string to find.
		\param needleLength	The length of the byte string.
		\param pos			Out: The position where the needle was found. This will point
							to the first character of the found needle.
	*/
	XsensResultValue find(const void* needle, const uint32_t needleLength, CmtFilePos& pos);
	/*! \brief Flush all data to be written.
		This function writes any remaining data immediately and does not return
		until this is done.
	*/
	XsensResultValue flushData(void);
		//! Return the size of the file.
	CmtFilePos getFileSize(void) const { return m_fileSize; }
		//! Return the result code of the last operation.
	XsensResultValue getLastResult(void) const	{ return m_lastResult; }
	/*! \brief Retrieve the filename that was last successfully opened.

		\param filename	A buffer for storing the filename. The buffer should be able 
				to hold the filename. A safe size is to make it at least 256 bytes.
	*/
	XsensResultValue getName(char* filename) const;
	/*! \brief Retrieve the filename that was last successfully opened in unicode.

		\param filename	A buffer for storing the filename. The buffer should be able 
				to hold the filename. A safe size is to make it at least 256 wide characters.
	*/
	XsensResultValue getName(wchar_t* filename) const;
		//! Return the current read position.
	CmtFilePos getReadPos(void) const { return m_readPos; }
		//! Return the current write position.
	CmtFilePos getWritePos(void) const { return m_writePos; }
	/*! \brief Insert the given data into the file.
	
		The function writes the given data to the file at the current write position. This
		operation may take a while to complete.
		
		The write position is placed at the end of the inserted data.
	*/
	XsensResultValue insertData(const CmtFilePos start, const uint32_t length,
								const void* data);
		//! Return whether the file is open or not.
	bool isOpen(void) const { return m_isOpen; }
		//! Return whether the file is readonly or not.
	bool isReadOnly(void) const { return !m_isOpen || m_readOnly; }
		//! Open a file.
	XsensResultValue open(const char* filename, const bool create, const bool readOnly);
		//! Open a file using a unicode filename.
	XsensResultValue open(const wchar_t* filename, const bool create, const bool readOnly);
	/*! \brief Read data from the file and put it into the data buffer.

		This function reads exactly the number of bytes as requested from the file.
		\param maxLength	The amount of data that will be read.
		\param data			Pointer to a buffer that will store the read data.
		\param length		pointer to a variable that will store the number of bytes
							that were actually read. The parameter may be NULL.
	*/
	XsensResultValue readData(const uint32_t maxLength, void* data, uint32_t* length);
	/*! \brief Read data from the file and put it into the data buffer.

		This function reads upp to the number of bytes as requested from the file.
		The function will also stop if the given terminator character is encountered.
		The terminator is included in the output buffer.
		\param maxLength	The amount of data that will be read.
		\param data			Pointer to a buffer that will store the read data.
		\param terminator	A character that will end the read operation if encountered.
		\param length		The actual number of bytes read, including the terminator
							character, if encountered.
	*/
	XsensResultValue readData(const uint32_t maxLength, const char terminator, void* data, uint32_t* length);
	/*! \brief Set the new absolute read position

		The read position is checked against the filesize before committing.
	*/
	XsensResultValue setReadPos(const CmtFilePos pos);
	/*! \brief Set the new absolute write position

		The write position is checked against the filesize before committing.
	*/
	XsensResultValue setWritePos(const CmtFilePos pos = -1);

	/*! \brief Write data to the file.

		The function writes the given data to the file at the current write position.
	*/
	XsensResultValue writeData(const uint32_t length,  const void* data);
};

}	// end of xsens namespace

#endif	// _CMT1_H_2006_04_12
#ifndef _CMTMESSAGE_H_2006_05_24
#define _CMTMESSAGE_H_2006_05_24


namespace xsens {

//////////////////////////////////////////////////////////////////////////////////////////
/*! \brief Compute the checksum of the given byte string.
*/
uint8_t computeChecksum(const uint8_t* buffer, uint32_t length);

//////////////////////////////////////////////////////////////////////////////////////////
/* different alignment commands for gcc / MSVS, the structure needs to be 1-byte aligned.
*/
#ifdef _MSC_VER
	#pragma pack(push, 1)
#endif
/*! \brief A message header.
	
	DO NOT REORDER THE MEMBERS!
*/
struct MessageHeader {
	uint8_t m_preamble;
	uint8_t m_busId;
	uint8_t m_messageId;
	uint8_t m_length;
	union _mdl {
		struct _mextd {
			struct _mlen {
				uint8_t m_high;
				uint8_t m_low;
			} m_length;
			uint8_t m_data[CMT_MAXDATALEN];
		} m_extended;
		uint8_t m_data[254];
	} m_datlen;
}
// different alignment commands for gcc / MSVS
#ifdef _MSC_VER
	;
	#pragma pack(pop)
#else
	/*! \cond NODOXYGEN */	__attribute__((__packed__))	/*! \endcond */;
#endif


#define swapEndian16(src) (((src) >> 8) | ((src) << 8))
#define swapEndian32(src) (((src) >> 24) | ((src) >> 8 & 0xFF00) | ((src) << 8 & 0xFF0000) | ((src) << 24))

//////////////////////////////////////////////////////////////////////////////////////////
//! \brief Class for storing a single message.
class Message {
protected:

		//! The message header is the data buffer with interpretation
	MessageHeader* m_buffer;
		//! The checksum in the m_data or m_extendedData buffer
	uint8_t* m_checksum;
		//! The maximum size of the message, including header and footer
	uint32_t m_maxLength;
	
		//! Internal checksum computation
	uint8_t calcChecksum(void) const
	{ return computeChecksum(((uint8_t*)m_buffer) + 1, getTotalMessageSize()-2); }
		//! Internal function to get the start of the data buffer.
	uint8_t* getDataStart(void) const;

public:
	bool m_autoUpdateChecksum;

	/*! \brief Create a Message object with the given data length and message Id.
	
		The function allocates enough memory to hold an entire message with the given 
		data length.
		\param msgId	The message Id that will be assigend to the m_messageId field.
		\param length	The length of the data in the message. This value is stored in 
						\c m_createdLength as well as \c m_length or \c m_extendedLength.
		\param maxLength	The maximum data length that can be stored in the structure.
	*/
	Message(const uint8_t msgId = 0, const uint16_t length = 0,	const uint16_t maxLength = CMT_MAXMSGLEN);

	/*! \brief Create a message from the given source string
	
		This is done through a simple memory copy. The number of bytes copied is taken
		from the data in the message (so the message is interpreted first).
		Note that this does NOT recompute the checksum, nor is it checked.
		
		\param source		The source string containing message data
		\param size			The size of the source string
		\param maxLength	The maximum data length that can be stored in the structure.
	*/
	Message(const uint8_t* source, const uint16_t size, const uint16_t maxLength = CMT_MAXMSGLEN);

	Message(const Message& src);

		//! Destructor
	~Message();

		//! Clear all data in the message
	void clear(void);

		//! Return the current value of the m_busId field.
	uint8_t getBusId(void) const { return m_buffer->m_busId; }
	/*! \brief Return a pointer to the data buffer.
	
		\param offset An optional offset in the data buffer from where to start reading.
	*/
	uint8_t* getDataBuffer(const uint16_t offset = 0)
		{ return &((getDataStart())[offset]); }
	const uint8_t* getDataBuffer(const uint16_t offset = 0) const
		{ return &((getDataStart())[offset]); }
	/*! \brief Return the current value of the data as an unsigned byte (8 bits).
	
		\param offset An optional offset in the data buffer from where to start reading.
	*/
	uint8_t getDataByte(const uint16_t offset = 0) const
		{ return (getDataStart()[offset]); }
	/*! \brief Return the current value of the data as a double (64 bits).
	
		\param offset An optional offset in the data buffer from where to start reading.
	*/
	double getDataDouble(const uint16_t offset=0) const;
	/*! \brief Return the current value of the data as a float (32 bits).
	
		\param offset An optional offset in the data buffer from where to start reading.
	*/
	float getDataFloat(const uint16_t offset=0) const;
	/*! \brief Return the current value of the data as a double, converting it from FP 12.20
	
		\param offset An optional offset in the data buffer from where to start reading.
	*/
	double getDataF1220(const uint16_t offset=0) const;
	/*! \brief Return the current value of the data as a double, converting it from FP 16.32
	
		\param offset An optional offset in the data buffer from where to start reading.
	*/
	double getDataFP1632(const uint16_t offset=0) const;
	/*! \brief Return current data value as double, conversion depends on outputSettings.
	
		\param outputSettings MT output settings
		\param offset An optional offset in the data buffer from where to start reading.
	*/
	double getDataFPValue(const uint64_t outputSettings, const uint16_t offset = 0) const;
	/*! \brief Return current data values as double, conversion depends on outputSetting.
	
		\param dest destination array
		\param outputSettings MT output settings
		\param offset offset in the data buffer from where to start reading.
		\param numValues number of values to be read
	*/
	void getDataFPValue(double *dest, const uint64_t outputSettings, uint16_t offset, const int16_t numValues) const;
	/*! \brief Return the current value of the data as an uint32_t (32 bits).
	
		\param offset An optional offset in the data buffer from where to start reading.
	*/
	uint32_t getDataLong(const uint16_t offset=0) const;
	/*! \brief Return the current value of the data as an uint16_t (16 bits).
	
		\param offset An optional offset in the data buffer from where to start reading.
	*/
	uint16_t getDataShort(const uint16_t offset=0) const;
		//! Return the length of the data part of the message.
	uint16_t getDataSize(void) const;
		//! Return the current value of the m_messageId field.
	uint8_t getMessageId(void) const { return m_buffer->m_messageId; }
	/*! \brief Return the start of the message buffer.
	
		The function returns the address of the \c m_preamble member.
	*/
	const uint8_t* getMessageStart(void) const
		{ return (uint8_t*) m_buffer; }
	/*! \brief Return the length of the message buffer.
	
		The function returns the total size of the message, including the checksum. This
		is in effect the number of bytes that would be transferred if the message were to
		be sent over a communications channel.
	*/
	uint16_t getTotalMessageSize(void) const;
		//! Compute the checksum and compare it with the stored checksum. Equal is ok.
	bool isChecksumOk(void) const;
	/*! \brief Read the entire message from the given source string
	
		This is done through a simple memory copy. The number of bytes copied is \c
		m_createdLength.
		\param source		The source string containing message data
		\param size			The size of the source string
	*/
	XsensResultValue loadFromString(const uint8_t* source, const uint16_t size);
	/*! \brief Compute the checksum field and fill it.
	
		The checksum field should normally be correct at all times, but if you have
		somehow managed to mess it up, this function can be used to recompute it.
	*/
	void recomputeChecksum(void) { m_checksum[0] = calcChecksum(); }
		//! Resize the data area to the given size
	void resizeData(const uint16_t newSize);
		//! Set the new value of the m_busId field and update the checksum.
	void setBusId(const uint8_t busId);
	/*! \brief Write a string of bytes into the data buffer.

		\param data		The data to write to the buffer.
		\param offset	An optional offset in the data buffer from where to start writing.
		\param count	An optional number of bytes to write, if set to 0 (not set), as
						many bytes as will fit into the buffer from the given point will 
						be written.
	*/
	void setDataBuffer(const uint8_t* data, const uint16_t offset = 0,
								const uint16_t count = 0);
	/*! \brief Write an unsigned byte (8 bits) into the data buffer.
	
		\param data		The data to write to the buffer.
		\param offset	An optional offset in the data buffer from where to start writing.
	*/
	void setDataByte(const uint8_t data, const uint16_t offset = 0);
	/*! \brief Write a double (64 bits) into the data buffer.
	
		\param data		The data to write to the buffer.
		\param offset An optional offset in the data buffer from where to start writing.
	*/
	void setDataDouble(const double data, const uint16_t offset=0);
	/*! \brief Write a float (32 bits) into the data buffer.
	
		\param data		The data to write to the buffer.
		\param offset An optional offset in the data buffer from where to start writing.
	*/
	void setDataFloat(const float data, const uint16_t offset = 0);
	/*! \brief Write a double (64 bits) into the data buffer, after converting it to F1220.
	
		\param data		The data to write to the buffer.
		\param offset	An optional offset in the data buffer from where to start writing.
	*/
	void setDataF1220(const double data, const uint16_t offset = 0);
	/*! \brief Write a double (64 bits) into the data buffer, after converting it to FP1632.
	
		\param data		The data to write to the buffer.
		\param offset	An optional offset in the data buffer from where to start writing.
	*/
	void setDataFP1632(const double data, const uint16_t offset = 0);
	/*! \brief Write a floating/fixed point value into to the data buffer, conversion depends on outputSettings
	
		\param outputSettings MT output settings
		\param data		The data to write to the buffer.
		\param offset An optional offset in the data buffer from where to start writing.
	*/
	void setDataFPValue(const uint64_t outputSettings, const double data, const uint16_t offset = 0);
	/*! \brief Write a floating/fixed point value into to the data buffer, conversion depends on outputSettings
	
		\param outputSettings MT output settings
		\param data		The data array to be written to the buffer.
		\param offset Offset in the data buffer from where to start writing.
		\param numValues number of values to be written
	*/
	void setDataFPValue(const uint64_t outputSettings, const double *data, uint16_t offset, const uint16_t numValues);
	/*! \brief Write an uint32_t (32 bits) into the data buffer.
	
		\param data		The data to write to the buffer.
		\param offset An optional offset in the data buffer from where to start writing.
	*/
	void setDataLong(const uint32_t data, const uint16_t offset = 0);
	/*! \brief Write an uint16_t (16 bits) into the data buffer.
	
		\param data		The data to write to the buffer.
		\param offset An optional offset in the data buffer from where to start writing.
	*/
	void setDataShort(const uint16_t data, const uint16_t offset = 0);
		//! Set the new value of the m_messageId field and update the checksum.
	void setMessageId(const uint8_t msgId);

		//! Copy message src into this
	void operator = (const Message& src);

		//! Remove a number of bytes from the message (this will reduce the message size)
	void deleteData(uint16_t size, uint16_t offset = 0);
		//! Insert a number of bytes into the message (this will increase the message size)
	void insertData(uint16_t size, uint16_t offset = 0);
};

}; // end of xsens namespace

#endif	// _CMTMESSAGE_H_2006_05_24
#ifndef _FIFOQUEUE_H_2006_05_03
#define _FIFOQUEUE_H_2006_05_03


namespace xsens {

//////////////////////////////////////////////////////////////////////////////////////////

/*! \brief A FIFO queue with limited length (cyclic).

	The class is based on the STL queue class, but has a limited size. If more items are
	inserted than would fit, the oldest item is overwritten. The class can only handle 
	pointer types.
*/
template <class T, bool E=true>
class FifoQueue {
protected:
	size_t m_maxCount;
	size_t m_currentCount;
	size_t m_first;
	bool m_deleteOnOverwrite;

	T*	m_list;
public:
	typedef T		value_type;		//!< The type of the value stored in this queue.
	typedef size_t	size_type;		//!< The type of a 'size' value.

	//! Create an empty queue with capacity size.
	FifoQueue(size_type size=16, bool delOnOverwrite = true)
	{
		if (size > 0)
			m_maxCount = size;
		else
			m_maxCount = 1;
		m_list = new T[m_maxCount];
		m_currentCount = 0;
		m_first = 0;
		m_deleteOnOverwrite = delOnOverwrite;
	}
	
	//! The copy constructor.
	template <bool E2>
	FifoQueue(const FifoQueue<T,E2>& q)
	{
		m_maxCount = q.m_maxCount;
		m_list = new T[m_maxCount];
		m_currentCount = q.m_currentCount;
		m_deleteOnOverwrite = q.m_deleteOnOverwrite;
		m_first = 0;
		for (size_t i = 0;i<m_currentCount;++i)
			m_list[i] = q.m_list[(i+q.m_first) % m_maxCount];
	}
	
	void eraseAndClear(void)
	{
		for (size_t i = 0;i<m_currentCount;++i)
			delete m_list[(i+m_first) % m_maxCount];
		m_currentCount = 0;
		m_first = 0;
	}

	//! The destructor.
	~FifoQueue()
	{
		if (E)
			eraseAndClear();
		m_maxCount = 0;
		delete[] m_list;
	}

	//! The assignment operator.
	template <bool E2>
	FifoQueue<T,E>& operator=(const FifoQueue<T,E2>& q)
	{
		if (m_maxCount != q.m_maxCount)
		{
			delete[] m_list;
			m_maxCount = q.m_maxCount;
			m_list = new T[m_maxCount];
		}
		m_currentCount = q.m_currentCount;
		m_first = 0;
		for (size_t i = 0;i<m_currentCount;++i)
			m_list[i] = q.m_list[(i+q.m_first) % m_maxCount];

		return *this;
	}
	
	//! Resize the queue, note that this function clears the queue.
	void resize(const size_t size)
	{
		if (E)
			eraseAndClear();
		delete[] m_list;
		if (size > 0)
			m_maxCount = size;
		else
			m_maxCount = 1;
		m_list = new T[m_maxCount];
		m_currentCount = 0;
		m_first = 0;
	}

	//! Return true if the queue is empty.
	bool empty() const
	{
		return (m_currentCount == 0);
	}
	
	//! Return the maximum number of elements in the queue.
	size_type size() const
	{
		return m_maxCount;
	}
	
	//! Return the number of elements currnetly in the queue.
	size_type length() const
	{
		return m_currentCount;
	}

	//! Return the oldest element in the queue.
	value_type& front()
	{
		return m_list[m_first];
	}
	
	//! Return the oldest element in the queue.
	const value_type& front() const
	{
		return m_list[m_first];
	}
	
	//! Return the newest element in the queue.
	value_type& back()
	{
		return m_list[(m_first + m_currentCount - 1) % m_maxCount];
	}
	
	//! Return the newest element in the queue.
	const value_type& back() const
	{
		return m_list[(m_first + m_currentCount - 1) % m_maxCount];
	}
	
	//! Insert x at the back of the queue.
	void push(const value_type& x)
	{
		if (m_currentCount == m_maxCount)
		{
			if (m_deleteOnOverwrite)
				delete (m_list[m_first]);
			
			m_list[m_first] = x;
			m_first = (m_first+1) % m_maxCount;
		}
		else
		{
			m_list[(m_first + m_currentCount++) % m_maxCount] = x;
		}
	}
	
	//! Remove the element at the front of the queue.
	void pop(void)
	{
		m_first = (m_first+1) % m_maxCount;
		--m_currentCount;
	}

	//! Remove the element at the back of the queue.
	void popBack(void)
	{
		--m_currentCount;
	}

	//! Return the index'th oldest item from the queue
	const value_type& operator[] (size_t index) const
	{
		if (index >= m_currentCount)
			return m_list[(m_first + m_currentCount - 1) % m_maxCount];
		else
			return m_list[(m_first + index) % m_maxCount];
	}

	//! Return the index'th oldest item from the queue
	value_type& operator[] (size_t index)
	{
		if (index >= m_currentCount)
			return m_list[(m_first + m_currentCount - 1) % m_maxCount];
		else
			return m_list[(m_first + index) % m_maxCount];
	}

	void clear(void)
	{
		m_currentCount = 0;
		m_first = 0;
	}

	void remove(size_t index)
	{
		if (index >= m_currentCount)
			return;
		if (index == 0)
			pop();
		else
		{
			--m_currentCount;
			for (size_t i=index;i<m_currentCount;++i)
				m_list[(m_first + i) % m_maxCount] = m_list[(1 + m_first + i) % m_maxCount];
		}
	}
};


//////////////////////////////////////////////////////////////////////////////////////////

/*! \brief A FIFO queue with limited length (cyclic).

	The class is based on the STL queue class, but has a limited size. If more items are
	inserted than would fit, the oldest item is overwritten. The class can only handle 
	non-pointer types.
*/
template <class T>
class FifoQueueBasic {
protected:
	size_t m_maxCount;
	size_t m_currentCount;
	size_t m_first;

	T*	m_list;
public:
	typedef T		value_type;		//!< The type of the value stored in this queue.
	typedef size_t	size_type;		//!< The type of a 'size' value.

	//! Create an empty queue with capacity 'size'.
	FifoQueueBasic(size_type size=16)
	{
		if (size > 0)
			m_maxCount = size;
		else
			m_maxCount = 1;
		m_list = new T[m_maxCount];
		m_currentCount = 0;
		m_first = 0;
	}
	
	//! The copy constructor.
	FifoQueueBasic(const FifoQueueBasic<T>& q)
	{
		m_maxCount = q.m_maxCount;
		m_list = new T[m_maxCount];
		m_currentCount = q.m_currentCount;
		m_first = 0;
		for (size_t i = 0;i<m_currentCount;++i)
			m_list[i] = q.m_list[(i+q.m_first) % m_maxCount];
	}
	
	void eraseAndClear(void)
	{
		for (size_t i = 0;i<m_currentCount;++i)
			delete m_list[(i+m_first) % m_maxCount];
		m_currentCount = 0;
		m_first = 0;
	}

	//! The destructor.
	~FifoQueueBasic()
	{
		m_maxCount = 0;
		delete[] m_list;
	}

	//! The assignment operator.
	FifoQueueBasic<T>& operator=(const FifoQueueBasic<T>& q)
	{
		if (m_maxCount != q.m_maxCount)
		{
			delete[] m_list;
			m_maxCount = q.m_maxCount;
			m_list = new T[m_maxCount];
		}
		m_currentCount = q.m_currentCount;
		m_first = 0;
		for (size_t i = 0;i<m_currentCount;++i)
			m_list[i] = q.m_list[(i+q.m_first) % m_maxCount];

		return *this;
	}
	
	//! Resize the queue, note that this function clears the queue.
	void resize(const size_t size)
	{
		delete[] m_list;
		if (size > 0)
			m_maxCount = size;
		else
			m_maxCount = 1;
		m_list = new T[m_maxCount];
		m_currentCount = 0;
		m_first = 0;
	}

	//! Return true if the queue is empty.
	bool empty() const
	{
		return (m_currentCount == 0);
	}
	
	//! Return the maximum number of elements in the queue.
	size_type size() const
	{
		return m_maxCount;
	}
	
	//! Return the number of elements currently in the queue.
	size_type length() const
	{
		return m_currentCount;
	}

	//! Return the oldest element in the queue.
	value_type& front()
	{
		return m_list[m_first];
	}
	
	//! Return the oldest element in the queue.
	const value_type& front() const
	{
		return m_list[m_first];
	}
	
	//! Return the newest element in the queue.
	value_type& back()
	{
		return m_list[(m_first + m_currentCount - 1) % m_maxCount];
	}
	
	//! Return the newest element in the queue.
	const value_type& back() const
	{
		return m_list[(m_first + m_currentCount - 1) % m_maxCount];
	}
	
	//! Insert x at the back of the queue.
	void push(const value_type& x)
	{
		if (m_currentCount == m_maxCount)
		{
			m_list[m_first] = x;
			m_first = (m_first+1) % m_maxCount;
		}
		else
		{
			m_list[(m_first + m_currentCount++) % m_maxCount] = x;
		}
	}

	//! Insert x at the front of the queue (LIFO operation).
	void push_front(const value_type& x)
	{
		m_first = (m_first+m_maxCount-1)%m_maxCount;
		if (m_currentCount == 0)
			m_first = 0;
		m_list[m_first] = x;
		if (m_currentCount < m_maxCount)
			++m_currentCount;
	}

	//! Remove the element at the front of the queue.
	void pop(void)
	{
		if (m_currentCount > 0)
		{
			m_first = (m_first+1) % m_maxCount;
			--m_currentCount;
		}
	}

	//! Remove the element at the back of the queue.
	void popBack(void)
	{
		if (m_currentCount > 0)
			--m_currentCount;
	}

	//! Return the index'th oldest item from the queue
	const value_type& operator[] (size_t index) const
	{
		if (index >= m_currentCount)
			return m_list[(m_first + m_currentCount - 1) % m_maxCount];
		else
			return m_list[(m_first + index) % m_maxCount];
	}

	//! Return the index'th oldest item from the queue
	value_type& operator[] (size_t index)
	{
		if (index >= m_currentCount)
			return m_list[(m_first + m_currentCount - 1) % m_maxCount];
		else
			return m_list[(m_first + index) % m_maxCount];
	}

	void clear(void)
	{
		m_currentCount = 0;
		m_first = 0;
	}

	void remove(size_t index)
	{
		if (index >= m_currentCount)
			return;
		if (index == 0)
			pop();
		else
		{
			--m_currentCount;
			for (size_t i=index;i<m_currentCount;++i)
				m_list[(m_first + i) % m_maxCount] = m_list[(1 + m_first + i) % m_maxCount];
		}
	}
};

} // end of xsens namespace

#endif	// _FIFOQUEUE_H_2006_05_03
#ifndef _CMT2_H_2006_04_13
#define _CMT2_H_2006_04_13


namespace xsens {

//////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////// Support  functions ///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

//! Find a valid message in the given buffer. If nothing is found, the function returns -1. Otherwise the index of the first character of the message is returned.
int32_t findValidMessage(const uint8_t* buffer, const uint16_t bufferLength);


//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Cmt2s  /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////
/*! \brief Mid-level serial communication class.

	The class uses CMT level 1, but does not inherit from it. If software needs to access 
	the level 1 component, it needs to be done through the getCmt1s() function.
*/
class Cmt2s {
private:
	//! This object cannot be copied, so this function is not implemented.
	Cmt2s(const Cmt2s& ref);

	/*! \brief The message received function.
	
		This function is automatically called every time a complete message was read from the 
		connected COM port.
	*/
	CmtCallbackFunction m_onMessageReceived;
	//! Custom, user supplied parameter for the OnMessageReceived callback function, passed as the first argument
	int32_t m_onMessageReceivedInstance;
	//! Custom, user supplied parameter for the OnMessageReceived callback function, passed as the last argument
	void* m_onMessageReceivedParam;

	/*! \brief The message sent function.
	
		This function is automatically called every time a complete message was sent to the 
		connected COM port.
	*/
	CmtCallbackFunction m_onMessageSent;
	//! Custom, user supplied parameter for the OnMessageSent callback function, passed as the first argument
	int32_t m_onMessageSentInstance;
	//! Custom, user supplied parameter for the OnMessageSent callback function, passed as the last argument
	void* m_onMessageSentParam;

protected:
		//! The baudrate that was last set to be used by the port
	uint32_t m_baudrate;
		//! The CMT level 1 object that this class operates on
	Cmt1s m_cmt1s;
		//! The last result of an operation
	mutable XsensResultValue m_lastResult;
		//! Buffer for reading data until a valid message is read. Should be rarely used.
	uint8_t m_readBuffer[CMT_DEFAULT_READ_BUFFER_SIZE];
		//! The number of valid bytes in the readBuffer.
	uint16_t m_readBufferCount;
		//! Timeout in ms for blocking operations
	uint32_t m_timeout;
		//! The timestamp at which to end an operation
	uint32_t m_toEnd;
public:
		//! Default constructor, initialize all members to their default values.
	Cmt2s();

		//! Destructor, de-initialize, free memory allocated for buffers, etc.
	~Cmt2s();

		//! Close the serial communication port.
	XsensResultValue close(void);

		//! Return the baudrate that is currently being used by the port
	uint32_t getBaudrate(void) { return (m_baudrate = m_cmt1s.getBaudrate()); }
	/*! \brief Return a reference to the embedded Cmt1s object.
	
		Any manipulation of the object should be done through Cmt2s. Cmt2s integrity is 
		not guaranteed if the Cmt1s object is manipulated directly.
	*/
	Cmt1s* getCmt1s(void) { return &m_cmt1s; }
		//! Return the error code of the last operation.
	XsensResultValue getLastResult(void) const { return m_lastResult; }
		//! Retrieve the port that the object is connected to.
	XsensResultValue getPortNr(uint16_t& port) const;
	XsensResultValue getPortNr(int32_t& port) const;
	XsensResultValue getPortName(char *portname) const;
		//! Return the current timeout value in ms.
	uint32_t getTimeout(void) const { return m_timeout; }
		//! Return whether the communication port is open or not.
	bool isOpen (void) const { return (m_cmt1s.isOpen()); }
		//! Open a communication channel to the given serial port name.
	XsensResultValue open(const char *portName, 
							const uint32_t baudRate = CMT_DEFAULT_BAUD_RATE,
							uint32_t readBufSize = CMT_DEFAULT_READ_BUFFER_SIZE,
							uint32_t writeBufSize = CMT_DEFAULT_WRITE_BUFFER_SIZE);
#ifdef _WIN32
		//! Open a communication channel to the given COM port number.
	XsensResultValue open(const uint32_t portNumber,
							const uint32_t baudRate = CMT_DEFAULT_BAUD_RATE,
							uint32_t readBufSize = CMT_DEFAULT_READ_BUFFER_SIZE,
							uint32_t writeBufSize = CMT_DEFAULT_WRITE_BUFFER_SIZE);
#endif	
	/*! \brief Read a message from the COM port.
	
		The function reads data from the embedded Cmt1s object. The data is then converted
		into a Message object.
		If an error occurred, a NULL pointer is returned and the error code can be
		retrieved with getLastError().
	*/
	XsensResultValue readMessage(Message* rcv);

	//! Set the callback function for when a message has been received or sent
	XsensResultValue setCallbackFunction(CmtCallbackType tp, int32_t instance, CmtCallbackFunction func, void* param);

	/*! \brief Set the default timeout value to use in blocking operations.

		This function sets the level 2 timeout value. The L1 value is set to half the given
		timeout value.
	*/
	XsensResultValue setTimeout(const uint32_t ms = CMT2_DEFAULT_TIMEOUT);

	/*! \brief Wait for a message to arrive.
	
		The function waits for a message to arrive or until a timeout occurs.
		If the msgId parameter is set to a value other than 0, the function will wait
		until a message has arrived with that particular msgId.
		
		\note msgId 0 is the ReqDeviceID MID, but that is an outgoing only message. It is
		illogical to wait for a message that will never be sent to the host. So 0 is a
		safe value for the 'all' messages option.
		
		\note If an error message is received, the contents are stored in the m_lastResult
		field and a NULL value is returned immediately.
	*/
	XsensResultValue waitForMessage(Message* rcv, const uint8_t msgId, uint32_t timeoutOverride, bool acceptErrorMessage);
	/*! \brief Send a message over the COM port.
	
		The function attempts to write the message over the connected COM port.
		\param msg	The message to send.
	*/
	XsensResultValue writeMessage(Message* msg);
};

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Cmt2f  /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////

/*! \brief The mid-level file communication class.

	The class uses CMT level 1, but does not inherit from it. If software needs to access 
	the level 1 component, it needs to be done through the getCmt1f() function.
*/
class Cmt2f {
private:
		//! This object cannot be copied, so this function is not implemented.
	Cmt2f(const Cmt2f& ref);

protected:
		//! The Cmt1f object that is used for the low-level operations
	Cmt1f m_cmt1f;
		//! The last result of an operation
	mutable XsensResultValue m_lastResult;

	bool m_readOnly;				//!< When set to true, the file is read-only and attempts to write to it will fail

public:
		//! Default constructor
	Cmt2f();
		//! Destructor.
	~Cmt2f();
		//! Close the file.
	XsensResultValue close(void);
		//! Close the file and delete it.
	XsensResultValue closeAndDelete(void);
		//! Create a new file with level 2 header
	XsensResultValue create(const char* filename);
		//! Create a new file with level 2 header
	XsensResultValue create(const wchar_t* filename);
		//! Get a reference to the embedded Cmt1f object
	Cmt1f* getCmt1f(void);

		//! Return the error code of the last operation.
	XsensResultValue getLastResult(void) const;
		//! Retrieve the filename that was last successfully opened.
	XsensResultValue getName(char* filename) const;
		//! Retrieve the filename that was last successfully opened.
	XsensResultValue getName(wchar_t* filename) const;
		//! Return whether the file is open or not.
	bool isOpen(void) const;
		//! Open a file and read the header
	XsensResultValue open(const char* filename, const bool readOnly = false);
		//! Open a file and read the header
	XsensResultValue open(const wchar_t* filename, const bool readOnly = false);
		//! Read the next message from the file, when msgId is non-zero, the first matching message will be returned
	XsensResultValue readMessage(Message* msg, const uint8_t msgId = 0);
		//! Get the current file size
	CmtFilePos getFileSize(void);
		//! Get the current read position
	CmtFilePos getReadPosition(void);
		//! Set the read position to the given position
	XsensResultValue setReadPosition(CmtFilePos pos);
		//! Write a message to the end of the file
	XsensResultValue writeMessage(const Message* msg);
};

} // end of xsens namespace

#endif	// _CMT2_H_2006_04_13
#ifndef _CMTPACKET_H_2006_05_10
#define _CMTPACKET_H_2006_05_10


namespace xsens {


	//! Indicates that a data item is not available in the packet
#define CMT_DATA_ITEM_NOT_AVAILABLE		65535

	//! A structure containing MT data + timestamp and formatting information.
class Packet
{
	friend class Cmt4;
protected:
		//! Contains information about data in the packet and the format of that data
	mutable struct PacketInfo {
		uint16_t m_offset;
		uint16_t m_rawData;
		uint16_t m_rawAcc;
		uint16_t m_rawGyr;
		uint16_t m_rawMag;
		uint16_t m_rawTemp;
		uint16_t m_temp;
		uint16_t m_calData;
		uint16_t m_calAcc;
		uint16_t m_calGyr;
		uint16_t m_calMag;
		uint16_t m_oriQuat;
		uint16_t m_oriEul;
		uint16_t m_oriMat;
		uint16_t m_analogIn1;
		uint16_t m_analogIn2;
		uint16_t m_posLLA;
		uint16_t m_velNEDorNWU;
		uint16_t m_status;
		uint16_t m_sc;
		uint16_t m_utcTime;
		uint16_t m_utcNano;
		uint16_t m_utcYear;
		uint16_t m_utcMonth;
		uint16_t m_utcDay;
		uint16_t m_utcHour;
		uint16_t m_utcMinute;
		uint16_t m_utcSecond;
		uint16_t m_utcValid;
		uint16_t m_acc_g;
		uint16_t m_gpsPvtData;
		uint16_t m_gpsPvtPressure;
		uint16_t m_gpsPvtPressureAge;
		uint16_t m_gpsPvtGpsData;
		uint16_t m_gpsPvtItow;
		uint16_t m_gpsPvtLatitude;
		uint16_t m_gpsPvtLongitude;
		uint16_t m_gpsPvtHeight;
		uint16_t m_gpsPvtVeln;
		uint16_t m_gpsPvtVele;
		uint16_t m_gpsPvtVeld;
		uint16_t m_gpsPvtHacc;
		uint16_t m_gpsPvtVacc;
		uint16_t m_gpsPvtSacc;
		uint16_t m_gpsPvtGpsAge;
		uint16_t m_size;
		uint16_t m_doubleBoundary;
	}*	m_infoList;
	CmtDataFormat*	m_formatList;	//!< A list of the formats of the data items
	bool m_xm;						//!< Indicates that xbus-formatting is used

public:
	uint16_t		m_itemCount;	//!< The number of data items in the message
	Message			m_msg;			//!< The message
	TimeStamp		m_rtc;			//!< Sample time in ms, based on the sample counter
	TimeStamp		m_toa;			//!< Time of arrival

	Packet(uint16_t items, bool xbus);
	Packet(const Packet& pack);
	~Packet();

	void operator = (const Packet& pack);

	bool setDataFormat(const CmtDataFormat& format, const uint16_t index = 0);
	bool setDataFormat(const CmtOutputMode outputMode, const CmtOutputSettings outputSettings, const uint16_t index = 0);
	CmtDataFormat getDataFormat(const uint16_t index = 0) const;
	void setXbus(bool xbus, bool convert = false);
	bool getXbus(void) const;

	/*! \brief Return the data size.

		\param index The index of the item of which the size should be returned.
	*/
	uint16_t getDataSize(const uint16_t index=0) const;

	/*! \brief Return the floating/fixed point value size

		\param index The index of the item whose fp size should be returned.
	*/
	uint16_t getFPValueSize(const uint16_t index) const;

	/*! \brief Return the Raw Accelerometer component of a data item.
	
		\param index The index of the item of which the data should be returned.
	*/
	CmtShortVector getRawAcc(const uint16_t index=0) const;
		//! Check if data item contains Raw Accelerometer data
	bool containsRawAcc(const uint16_t index=0) const;
		//! Add/update Raw Accelerometer data for the item
	bool updateRawAcc(const CmtShortVector& vec, const uint16_t index=0);
	/*! \brief Return the Raw Gyroscope component of a data item.
	
		\param index The index of the item of which the data should be returned.
	*/
	CmtShortVector getRawGyr(const uint16_t index=0) const;
		//! Check if data item contains Raw Gyroscope data
	bool containsRawGyr(const uint16_t index=0) const;
		//! Add/update Raw Gyroscope data for the item
	bool updateRawGyr(const CmtShortVector& vec, const uint16_t index=0);
	/*! \brief Return the Raw Magnetometer component of a data item.
	
		\param index The index of the item of which the data should be returned.
	*/
	CmtShortVector getRawMag(const uint16_t index=0) const;
		//! Check if data item contains Raw Magnetometer data
	bool containsRawMag(const uint16_t index=0) const;
		//! Add/update Raw Magnetometer data for the item
	bool updateRawMag(const CmtShortVector& vec, const uint16_t index=0);
	/*! \brief Return the Raw Temperature component of a data item.
	
		\param index The index of the item of which the data should be returned.
	*/
	uint16_t getRawTemp(const uint16_t index=0) const;
		//! Check if data item contains Raw Temperature data
	bool containsRawTemp(const uint16_t index=0) const;
		//! Add/update Raw Temperature data for the item
	bool updateRawTemp(uint16_t temp, const uint16_t index=0);
	/*! \brief Return the Raw Data component of a data item.
	
		\param index The index of the item of which the data should be returned.
	*/
	CmtRawData getRawData(const uint16_t index=0) const;
		//! Check if data item contains Raw Data
	bool containsRawData(const uint16_t index=0) const;
		//! Add/update Raw Data for the item
	bool updateRawData(const CmtRawData& data, const uint16_t index=0);
	/*! \brief Return the Gps PVT data component of a data item.
	\param index The index of the item of which the data should be returned.
	*/
	CmtGpsPvtData getGpsPvtData(const uint16_t index=0) const;
	//! Check if data item contains Gps PVT Data
	bool containsGpsPvtData(const uint16_t index=0) const;
	//! Add/update Gps PVT Data for the item
	bool updateGpsPvtData(const CmtGpsPvtData& data, const uint16_t index=0);

	//! This function is obsolete, use getGpsPvtData instead. This function will be removed in future versions of the MT SDK. \see getGpsPvtData
	#define	getRawGpsData getGpsPvtData
	//! This function is obsolete, use containsGpsPvtData instead. This function will be removed in future versions of the MT SDK. \see containsGpsPvtData
	#define	containsRawGpsData containsGpsPvtData
	//! This function is obsolete, use updateGpsPvtData instead. This function will be removed in future versions of the MT SDK. \see updateGpsPvtData
	#define	updateRawGpsData updateGpsPvtData

	/*! \brief Return the Raw Pressure Data component of a data item.
	\param index The index of the item of which the data should be returned.
	*/
	CmtRawPressureData getRawPressureData(const uint16_t index=0) const;
	//! Check if data item contains Raw Pressure Data
	bool containsRawPressureData(const uint16_t index=0) const;
	//! Add/update Raw Pressure Data for the item
	bool updateRawPressureData(const CmtRawPressureData& data, const uint16_t index=0);

	/*! \brief Return the Temperature component of a data item.

	\param index The index of the item of which the data should be returned.
	*/
	double getTemp(const uint16_t index=0) const;
	//! Check if data item contains Temperature data
	bool containsTemp(const uint16_t index=0) const;
	//! Add/update Calibrated Accelerometer data for the item
	bool updateTemp(const double& temp, const uint16_t index=0);
	/*! \brief Return the Calibrated Accelerometer component of a data item.
	
		\param index The index of the item of which the data should be returned.
	*/
	CmtVector getCalAcc(const uint16_t index=0) const;
		//! Check if data item contains Calibrated Accelerometer data
	bool containsCalAcc(const uint16_t index=0) const;
		//! Add/update Calibrated Accelerometer data for the item
	bool updateCalAcc(const CmtVector& vec, const uint16_t index=0);
	/*! \brief Return the Calibrated Gyroscope component of a data item.
	
		\param index The index of the item of which the data should be returned.
	*/
	CmtVector getCalGyr(const uint16_t index=0) const;
		//! Check if data item contains Calibrated Gyroscope data
	bool containsCalGyr(const uint16_t index=0) const;
		//! Add/update Calibrated Gyroscope data for the item
	bool updateCalGyr(const CmtVector& vec, const uint16_t index=0);
	/*! \brief Return the Calibrated Magnetometer component of a data item.
	
		\param index The index of the item of which the data should be returned.
	*/
	CmtVector getCalMag(const uint16_t index=0) const;
		//! Check if data item contains Calibrated Magnetometer data
	bool containsCalMag(const uint16_t index=0) const;
		//! Add/update Calibrated Magnetometer data for the item
	bool updateCalMag(const CmtVector& vec, const uint16_t index=0);
	/*! \brief Return the Calibrated Data component of a data item.
	
		\param index The index of the item of which the data should be returned.
	*/
	CmtCalData getCalData(const uint16_t index=0) const;
		//! Check if data item contains Calibrated Data
	bool containsCalData(const uint16_t index=0) const;
		//! Add/update Calibrated Data for the item
	bool updateCalData(const CmtCalData& data, const uint16_t index=0);

	/*! \brief Return the Orientation component of a data item as a Quaternion.
	
		\param index The index of the item of which the data should be returned.
	*/
	CmtQuat getOriQuat(const uint16_t index=0) const;
		//! Check if data item contains Quaternion Orientation data
	bool containsOriQuat(const uint16_t index=0) const;
		//! Add/update Quaternion Orientation data for the item
	bool updateOriQuat(const CmtQuat& data, const uint16_t index=0);
	/*! \brief Return the Orientation component of a data item as Euler angles.
	
		\param index The index of the item of which the data should be returned.
	*/
	CmtEuler getOriEuler(const uint16_t index=0) const;
		//! Check if data item contains Euler Orientation data
	bool containsOriEuler(const uint16_t index=0) const;
		//! Add/update Euler Orientation data for the item
	bool updateOriEuler(const CmtEuler& data, const uint16_t index=0);
	/*! \brief Return the Orientation component of a data item as an Orientation Matrix.
	
		\param index The index of the item of which the data should be returned.
	*/
	CmtMatrix getOriMatrix(const uint16_t index=0) const;
		//! Check if data item contains Matrix Orientation data
	bool containsOriMatrix(const uint16_t index=0) const;
		//! Add/update Matrix Orientation data for the item
	bool updateOriMatrix(const CmtMatrix& data, const uint16_t index=0);

		//! Check if data item contains Orientation Data of any kind
	bool containsOri(const uint16_t index=0) const;

	/*! \brief Return the AnalogIn 1 component of a data item.

	\param index The index of the item of which the data should be returned.
	*/
	CmtAnalogInData getAnalogIn1(const uint16_t index=0) const;
	//! Check if data item contains AnalogIn 1
	bool containsAnalogIn1(const uint16_t index=0) const;
	//! Add/update AnalogIn 1 for the item
	bool updateAnalogIn1(const CmtAnalogInData& data, const uint16_t index=0);

	/*! \brief Return the AnalogIn 2 component of a data item.

	\param index The index of the item of which the data should be returned.
	*/
	CmtAnalogInData getAnalogIn2(const uint16_t index=0) const;
	//! Check if data item contains AnalogIn 2
	bool containsAnalogIn2(const uint16_t index=0) const;
	//! Add/update AnalogIn 2 for the item
	bool updateAnalogIn2(const CmtAnalogInData& data, const uint16_t index=0);

	/*! \brief Return the Position Lat Lon Alt component of a data item.

	\param index The index of the item of which the data should be returned.
	*/
	CmtVector getPositionLLA(const uint16_t index=0) const;
	//! Check if data item contains Position Lat Lon Alt
	bool containsPositionLLA(const uint16_t index=0) const;
	//! Add/update Position Lat Lon Alt for the item
	bool updatePositionLLA(const CmtVector& data, const uint16_t index=0);

	/*! \brief Return the Velocity component of a data item.

	\param index The index of the item of which the data should be returned.
	*/
	CmtVector getVelocity(const uint16_t index=0) const;
	//! Check if data item contains Velocity
	bool containsVelocity(const uint16_t index=0) const;
	//! Add/update Velocity for the item
	bool updateVelocity(const CmtVector& data, const uint16_t index=0);

	/*! \brief Return the Status component of a data item.

	\param index The index of the item of which the data should be returned.
	*/
	uint8_t getStatus(const uint16_t index=0) const;
	//! Check if data item contains Status
	bool containsStatus(const uint16_t index=0) const;
	//! Add/update Status information for the item
	bool updateStatus(const uint8_t data, const uint16_t index=0);

	/*! \brief Return the Sample Counter component of the packet.
	
		\param index The index of the item of which the data should be returned. (ignored)
	*/
	uint16_t getSampleCounter(const uint16_t index=0) const;
		//! Check if data item contains Sample Counter
	bool containsSampleCounter(const uint16_t index=0) const;
		//! Add/update Sample Counter for all items
	bool updateSampleCounter(const uint16_t counter, const uint16_t index=0);

	/*! \brief Return the UTC Time component of the packet.
	
		\param index The index of the item of which the data should be returned. (ignored)
	*/
	CmtUtcTime getUtcTime(const uint16_t index=0) const;
		//! Check if data item contains UTC Time
	bool containsUtcTime(const uint16_t index=0) const;
		//! Add/update UTC Time for all items
	bool updateUtcTime(const CmtUtcTime& data, const uint16_t index=0);

	/*! \brief Return the RTC of the packet.
	
		\param index The index of the item of which the data should be returned. (ignored)
	*/
	CmtTimeStamp getRtc(const uint16_t index=0) const;


	/*! \brief Return the XKF-3 Acc-G component of the packet.
	
		\param index The index of the item of which the data should be returned.
	*/
	CmtVector getAccG(const uint16_t index=0) const;
		//! Check if data item contains XKF-3 Acc-G data
	bool containsAccG(const uint16_t index=0) const;
		//! Add/update XKF-3 Acc-G data for the item
	bool updateAccG(const CmtVector& g, const uint16_t index=0);

	#ifdef _CMT_DLL_EXPORT
		//! Interpolate so resulting packet is (1-f)*pa + pb OR pb if pa and pb are non-matching types
	void interpolate(const Packet& pa, const Packet& pb, const double f);
	#endif
};

}	// end of xsens namespace

#endif	// _CMTPACKET_H_2006_05_10
#ifndef _CMT3_H_2006_04_14
#define _CMT3_H_2006_04_14


namespace xsens {

//////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////// Cmt3  /////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////


/*! \brief High-level communication class.

	The class uses CMT level 2, but does not inherit from it. If software needs to access 
	the level 2 components, it needs to be done through the getCmt2s() and getCmt2f() functions.
	
	All device identification is done through device Ids in CMT level 3.
*/
class Cmt3 {
//// data & structures ////
protected:
	Cmt2s m_serial;					//!< The (optional) CMT level 2 serial object that this class operates on.
	Cmt2f m_logFile;				//!< The (optional) CMT level 2 logfile object that this class operates on. 
	double m_rtcMsPerSample;		//!< ms per sample = 1000 / sample frequency.
	//double m_sampleFrequency;		//!< The sample frequency of the port, computed from sampling period and output skip factor.
	uint16_t m_period;				//!< The sample period of the port.
	uint16_t m_skip;				//!< The skip factor of the port.
	TimeStamp m_rtcStart;			//!< The start of the RTC counter, the time of arrival of sample 0.
	uint32_t m_rtcCount;			//!< The long sample counter (normal counter wraps at 64k).
#ifdef _CORRECT_FOR_CLOCK_MISMATCH
	uint32_t m_lastToaTouch;		//!< The sample counter of the last sample that touched the Time Of Arrival
#endif
	CmtMtTimeStamp m_rtcLastSc;		//!< The last received sample counter, used to determine wrap-around.
	uint32_t m_baudrate;		//!< The baudrate that was last set to be used by the port.
	uint32_t m_timeoutConf;	//!< The config mode timeout.
	uint32_t m_timeoutMeas;			//!< The measurement mode timeout.
	mutable XsensResultValue m_lastResult;	//!< The last result of an operation.
	uint16_t m_firstItem;				//!< The index of the first formatting item.
	uint16_t m_gotoConfigTries;		//!< The number of times a goto config is attempted before the function fails.
	bool m_measuring;						//!< Keeps track of whether the connected device is measuring or being configured.
	bool m_detailedScan;			//!< Automatically scan for device details during open. Default is true (recommended).
	bool m_readFromFile;			//!< Indicates whether to read from the log file or from the serial port.
	bool m_rtcInitialized;			//!< Indicates if the rtc is initialised or not.
	bool m_logging;							//!< Indicates whether to write all received messages to the logfile or not, automatically set to true by createLogFile.
	XsensResultValue m_lastHwError;			//!< Contains the last error reported by hardware.
	CmtDeviceId m_lastHwErrorDeviceId;		//!< Contains the Device ID of the device that caused the last hardware error.

	uint32_t m_readBufSize;					//!< Contains the size of the serial read buffer
	uint32_t m_writeBufSize;				//!< Contains the size of the serial write buffer

public:
	bool m_useRtc;					//!< Indicates if the RTC should be computed or not (to save CPU time).
	void* m_eMtsData[CMT_MAX_DEVICES_PER_PORT];		//!< Cached eMTS data.
	CmtDeviceConfiguration m_config;				//!< Cached configuration data.

//// functions ///////////////////////////////////////////////////////////////////////////////////
protected:
	Cmt3(const Cmt3& ref);			//!< This object cannot be copied, so this function is not implemented.
	void fillRtc(Packet* pack);										//!< Internal function to compute the RTC value.
	uint8_t getBusIdInternal(const CmtDeviceId devId) const;	//!< \brief Find a device Id in the list and return its busId. \details CmtDeviceId 0= busId 0= broadcast. A CMT_BID_INVALID value is also possible and indicates that the devId was not found.

public:
		
	Cmt3();		//!< Default constructor, initializes all members to their default values.
	~Cmt3();	//!< Destructor, de-initializes, frees memory allocated for buffers, etc.

	XsensResultValue closePort(bool gotoConfigFirst=true);							//!< \brief Close the communication port. \details This function places the device in configuration mode and closes the communication port, ending all further communication with the device.
	XsensResultValue getBatteryLevel(uint8_t& level);		//!< \brief Get an Xbus Master's battery level. \details The battery level is a value between 0 and 255 that indicates the voltage of the batteries. The scale is not linear and the values should not be used as an absolute voltage. The amount of time remaining for measurement given any battery level greatly depends on the type of batteries used, the number of sensors attached to the Xbus Master and the used output options.
	XsensResultValue getBaudrate (uint32_t& baudrate);		//!< \brief Get the baudrate used by a port. \details This function returns the baud rate at which the port is currently connected. The function will return an error when no port is connected. \see getSerialBaudrate setSerialBaudrate setBaudrate
	XsensResultValue getBluetoothState(bool& enabled);														//!< \brief Get the state of the bluetooth communication. \details This function tells whether the Bluetooth connection of the Xbus Master is on (1) or off (0). \note This function is only valid in configuration mode.
	XsensResultValue getBusId (uint8_t& busId, const CmtDeviceId deviceId = CMT_DID_MASTER) const;	//!< \brief Retrieve the BusId of a device. \details The function checks its internal list for a match of deviceId. If it is found, the corresponding BusId is returned in busId. Otherwise, a 0 is placed in busId and XRV_NOTFOUND result is returned.
	XsensResultValue getBusPowerState(bool& enabled);														//!< \brief Get the state of the Xbus power. \details This function tells whether the Xbus of the connected Xbus Master is currently switched on (1) or not (0). When it is switched off, the attached MT devices have no power and communication with them is not possible. Before going to measurement mode, use setBusPowerState to restore power. \see setBusPowerState \note This function is only valid in configuration mode.

	Cmt2f* getCmt2f(void);	//!< \brief Return a reference to the embedded Cmt2f (logfile) object. \details Any manipulation of the object should be done through Cmt3. Cmt3's integrity is not guaranteed if the Cmt2f object is manipulated directly. \see refreshCache
	Cmt2s* getCmt2s(void);	//!< \brief Return a reference to the embedded Cmt2s (comm port) object. \details Any manipulation of the object should be done through Cmt3. Cmt3's integrity is not guaranteed if the Cmt2s object is manipulated directly. \see refreshCache

	XsensResultValue getConfiguration(CmtDeviceConfiguration& configuration);								//!< \brief Get device configuration. \details This function retrieves the complete device configuration of a single device. \note This information is cached by Cmt3, so it is available in measurement mode.
	XsensResultValue getDataLength(uint32_t& length, const CmtDeviceId deviceId = CMT_DID_MASTER);		//!< \brief Retrieve data size. \details This function retrieves the number of bytes that are in a data message as sent by the given device.
	uint32_t getDeviceCount(void) const;																//!< \brief Retrieve total device count. \details This function retrieves the total number of connected (master + slave) devices or 0 if not connected.
	XsensResultValue getDeviceId(const uint8_t busId, CmtDeviceId& deviceId) const;					//!< \brief Retrieve the DeviceId of a device given its Bus ID. \details This function retrieves the DeviceId for the device with the given Bus ID. When no devices are connected, a 0 ID is supplied.
	XsensResultValue getDeviceMode(CmtDeviceMode& mode, const CmtDeviceId deviceId = CMT_DID_MASTER);		//!< \brief Return device mode. \details This function retrieves the output-related settings of the device, such as the sample rate and output settings. \see setDeviceMode \note This function actually reads the device mode from the cached configuration, so it is available in measurement mode. \see refreshCache
	XsensResultValue getDeviceMode2(CmtDeviceMode2& mode, const CmtDeviceId deviceId = CMT_DID_MASTER);		//!< \brief Return device mode2. \details This function retrieves the output-related settings of the device, such as the period, skip factor and output settings. \see setDeviceMode \note This function actually reads the device mode from the cached configuration, so it is available in measurement mode. \see refreshCache
	XsensResultValue getEMtsData(void* buffer, const CmtDeviceId deviceId = CMT_DID_MASTER);				//!< \brief Retrieve the eMts data of the specified sensor(s). \details This function can be used to read proprietary data from one or more Motion Trackers. This data is required by higher level functions in combination with Configuration data to convert Raw data into Calibrated and Orientation data. The eMTs data is quite large, but it is cached. The first request should be done in configuration mode, but following requests can be done in measurement mode. When requesting eMTS data for a single sensor, the buffer should be at least CMT_EMTS_SIZE bytes long. When using CMT_DID_BROADCAST, the eMTS data of all connected sensors is placed into the buffer sequentially. In the latter case, the buffer should be able to hold at least sensorcount * CMT_EMTS_SIZE bytes.
	XsensResultValue getErrorMode(uint16_t& mode, const CmtDeviceId deviceId = CMT_DID_MASTER);		//!< \brief Return the error mode of the device. \details This function returns the error mode of the device. The error mode determines how the device handles errors. See the low-level communication documentation for more details. \see setErrorMode \note This function is only valid in configuration mode.
	XsensResultValue getFirmwareRevision(CmtVersion& revision, const CmtDeviceId deviceId = CMT_DID_MASTER);//!< \brief Return Firmware revision. \details This function retrieves the firmware version that is currently installed in the device. \note This function is only valid in configuration mode.
	XsensResultValue getHeading(double& heading, const CmtDeviceId deviceId = CMT_DID_MASTER);				//!< \brief Return the heading offset. \details This function retrieves the heading offset in radians used by the device. The valid range is -pi to +pi. The heading offset is used as a final correction on the output orientation. \see setHeading getMagneticDeclination setMagneticDeclination \note This function is only valid in configuration mode.

	XsensResultValue getLastResult(void) const				//!< \brief Return the error code of the last user function call.
		{ return m_lastResult; }
	XsensResultValue getHwError(CmtDeviceId& did) const		//!< \brief Return the last Hardware error code. \details This function returns the XsensResultValue of the last problem reported by hardware (if any). Hardware problems are all 'error' messages returned by a sensor. \param did If any problems were found, the responsible device ID will be returned in this parameter. \see clearHwError
		{ did = m_lastHwErrorDeviceId; return m_lastHwError; }
	void clearHwError(void)									//!< \brief Reset the hardware error code. \details Use this function to reset the hardware error code reported by getHwError. \see getHwError
		{ m_lastHwErrorDeviceId = 0; m_lastHwError = XRV_OK; }

	XsensResultValue getLatLonAlt(CmtVector& lla, const CmtDeviceId deviceId = CMT_DID_MASTER);					//!< \brief Retrieve the last stored sensor position. \details This function retrieves the last stored position in latitude, longitude, altitude. \see setLatLonAlt
	XsensResultValue getLocationId (uint16_t& locationId, const CmtDeviceId deviceId = CMT_DID_MASTER);	//!< \brief Return the location ID of a sensor. \details This function retrieves the location ID stored in the device. \see setLocationId \note This function is only valid in configuration mode.
	XsensResultValue getLogFileReadPosition(CmtFilePos& pos);													//!< \brief Retrieve the read position of the log file. \details This function will return the current read position in the open log file in bytes from the start. \note The read and write positions of log files are completely independent of each other. \remarks To change the read position, either use resetLogFileReadPos or manipulate the log file through getCmt2f. \see resetLogFileReadPos getCmt2f

	XsensResultValue getLogFileSize(CmtFilePos& size);															//!< \brief Retrieve the size of the open log file in bytes.
	XsensResultValue getLogFileName(char* filename);															//!< \brief Retrieve the name of the open log file or an empty string if no logfile is open
	XsensResultValue getLogFileName(wchar_t* filename);															//!< \brief Retrieve the name of the open log file or an empty string if no logfile is open
	XsensResultValue getMagneticDeclination(double& declination, const CmtDeviceId deviceId = CMT_DID_MASTER);	//!< \brief Return the stored magnetic declination. \details This function retrieves the stored local magnetic declination in radians. The valid range is -pi to +pi. The magnetic declination is used in the sensor fusion process to determine the output orientation. \see getHeading setHeading setMagneticDeclination \note This function is only valid in configuration mode.
	CmtDeviceId getMasterId(void);																				//! \brief Return the device Id of the first device (master). \details \note The deviceId is read from the cached configuration data, so it is also available in measurement mode.

	const uint16_t getMtCount(void) const;													//!< \brief Retrieve number of MT devices. \details This function will return the number of connected MT devices. Effectively, this returns the device count minus any Xbus Masters.
	XsensResultValue getMtDeviceId(const uint8_t index, CmtDeviceId& deviceId) const;			//! \brief Return the device Id of an MT device. \details This function returns the ID of the index'th MT (non-Xbus Master) device connected to this object. \note The deviceId is read from the cached configuration data, so it is also available in measurement mode.
	XsensResultValue getObjectAlignmentMatrix(CmtMatrix& matrix, const CmtDeviceId deviceId = CMT_DID_MASTER);					//!< \brief Retrieve the last stored object alignment matrix. \details Use this function to get the object matrix currently used as the sensor frame with respect to the reference frame. See the manual for more information on coordinate systems and object resets. \see setObjectAlignmentMatrix
	XsensResultValue getPortNr(uint16_t& port) const;											//!< \brief Return the port number that this object is connected to. \details If CMT is reading from a log file, an error will be returned.
	XsensResultValue getProductCode(char* productCode, const CmtDeviceId deviceId = CMT_DID_MASTER);//!< \brief Return product code. \details This function retrieves the product code of the given device. \param productCode The buffer that will store the product code. This buffer should be at least 20 bytes. \remarks The product code is NOT necessarily NULL-terminated. If it is less than 20 characters it will be, but if the product code is 20 characters it won't be. The recommended method is to create a buffer that is 21 bytes long and set the last byte to 0 before calling this function. \note This function is only valid in configuration mode.
	XsensResultValue getProcessingFlags (uint16_t& processingFlags, const CmtDeviceId deviceId = CMT_DID_MASTER);	//!< \brief Return the processing flags of a sensor. \details This function retrieves the processing flags stored in the device. \see setProcessingFlags \note This function is only valid in configuration mode.
	uint16_t getSampleFrequency(void);														//!< \brief Return current sample frequency. \details This function determines the sample frequency of the device from the cached sample rate and skip factor and returns it. For devices connected to an Xbus Master, the values used by the Xbus Master are returned. \see setDeviceMode getDeviceMode
	XsensResultValue getSerialBaudrate(uint32_t& baudrate);		//!< \brief Return the baud rate used for serial communication. \details This function retrieves the baud rate that is used when the device is connected by a serial connection. In most cases this is the same as getBaudrate, but when an Xbus Master is connected by a Bluetooth connection, it doesn't have to be. \see setSerialBaudrate setBaudrate getBaudrate \note This function is only valid in configuration mode.
	XsensResultValue getSyncInSettings(CmtSyncInSettings& settings);	//!< \brief Retrieve the inbound synchronization settings of the master MT device. \details This function retrieves the current inbound synchronization settings of the master MT device (sync mode, skip factor and offset). This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see setSyncInSettings getSyncOutSettings setSyncOutSettings getSyncMode setSyncMode \note This function is only valid in configuration mode.
	XsensResultValue getSyncInMode(uint16_t& mode);													//!< \brief Retrieve the inbound synchronization mode of an MT device. \details This function retrieves the current inbound synchronization mode of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see setSyncInMode setSyncInSettings getSyncInSettings getSyncInSkipFactor setSyncInSkipFactor getSyncInOffset setSyncInOffset getSyncOutSettings setSyncOutSettings getSyncMode setSyncMode
	XsensResultValue getSyncInSkipFactor(uint16_t& skipFactor);										//!< \brief Retrieve the inbound synchronization skip factor of an MT device. \details This function retrieves the current inbound synchronization skip factor of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see setSyncInSkipFactor setSyncInSettings getSyncInSettings getSyncInOffset setSyncInOffset getSyncOutSettings setSyncOutSettings getSyncMode setSyncMode
	XsensResultValue getSyncInOffset(uint32_t& offset);												//!< \brief Retrieve the inbound synchronization offset of an MT device. \details This function retrieves the current inbound synchronization offset of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see setSyncInOffset setSyncInSettings getSyncInSettings getSyncInSkipFactor setSyncInSkipFactor getSyncOutSettings setSyncOutSettings getSyncMode setSyncMode
	XsensResultValue getSyncMode(uint8_t& mode);					//!< \brief Retrieve the sync mode of the Xbus Master. \details This function requests the current synchronization mode used by the specified Xbus Master. This function is not valid for MT devices. \see setSyncMode getSyncInSettings setSyncInSettings getSyncOutSettings setSyncOutSettings \note This function is only valid in configuration mode.
	XsensResultValue getSyncOutSettings(CmtSyncOutSettings& settings);	//!< \brief Retrieve the outbound synchronization settings of the master MT device. \details This function retrieves the current outbound synchronization settings of the MT device (sync mode, skip factor, offset and pulse width). This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see setSyncOutSettings getSyncInSettings setSyncInSettings getSyncMode setSyncMode \note This function is only valid in configuration mode.
	XsensResultValue getSyncOutMode(uint16_t& mode);																		//!< \brief Retrieve the outbound synchronization mode of an MT device. \details This function retrieves the current outbound synchronization mode of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see setSyncOutMode setSyncOutSettings getSyncOutSettings getSyncOutPulseWidth setSyncOutPulseWidth getSyncOutSkipFactor setSyncOutSkipFactor getSyncOutOffset setSyncOutOffset getSyncInSettings setSyncInSettings getSyncMode setSyncMode
	XsensResultValue getSyncOutPulseWidth(uint32_t& pulseWidth);																//!< \brief Retrieve the outbound synchronization pulse width of an MT device. \details This function retrieves the current outbound synchronization pulse width of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see setSyncOutPulseWidth setSyncOutSettings getSyncOutSettings setSyncOutMode getSyncOutMode getSyncOutSkipFactor setSyncOutSkipFactor getSyncOutOffset setSyncOutOffset getSyncInSettings setSyncInSettings getSyncMode setSyncMode
	XsensResultValue getSyncOutSkipFactor(uint16_t& skipFactor);															//!< \brief Retrieve the outbound synchronization skip factor of an MT device. \details This function retrieves the current outbound synchronization skip factor of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see stSyncOutSkipFactor setSyncOutSettings getSyncOutSettings setSyncOutMode getSyncOutMode getSyncOutPulseWidth setSyncOutPulseWidth getSyncOutOffset setSyncOutOffset getSyncInSettings setSyncInSettings getSyncMode setSyncMode
	XsensResultValue getSyncOutOffset(uint32_t& offset);																		//!< \brief Retrieve the outbound synchronization offset of an MT device. \details This function retrieves the current outbound synchronization offset of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see setSyncOutOffset setSyncOutSettings getSyncOutSettings setSyncOutMode getSyncOutMode getSyncOutPulseWidth setSyncOutPulseWidth getSyncOutSkipFactor setSyncOutSkipFactor getSyncInSettings setSyncInSettings getSyncMode setSyncMode
	uint32_t getTimeoutConfig(void) const;							//!< \brief Return the configuration mode timeout. \details When in config mode, the system uses a different message timeout than in measurement mode, since configuration messages can take longer to process than measurement mode messages. This function can be used to determine the current config mode timeout in ms. \see setTimeoutConfig getTimeoutMeasurement setTimeoutMeasurement
	uint32_t getTimeoutMeasurement(void) const;							//!< \brief Return the measurement mode timeout. \details When in measurement mode, the system uses a different message timeout than in config mode, since measurement mode messages should be faster to process than config mode messages. This function can be used to determine the current measurement mode timeout in ms. \see setTimeoutMeasurement getTimeoutConfig setTimeoutConfig
	XsensResultValue getTransmissionDelay(uint16_t& delay, const CmtDeviceId deviceId = CMT_DID_MASTER);		//!< \brief Return the RS485 acknowledge transmission delay of the device. \details This function returns the RS485 acknowledge transmission delay of the device. The RS485 acknowledge transmission delay determines the minimal delay to response on request messages. See the low-level communication documentation for more details. \see setAckTransmissionDelay \note This function is only valid in configuration mode.
	XsensResultValue getUtcTime(CmtUtcTime& utc, const CmtDeviceId deviceId);	//!< \brief Return the UTC time of the last received sample. \details This function is only valid for MTi-G sensors. In measurement mode it will retrieve the UTC time of the last received sample. In Config mode, it will retrieve the most recent UTC time. In config mode, the time returned will be requested diectly from the GPS subsystem, with several layers of messaging between the original source and the host. In measurement mode, the UTC time is requested from the GPS subsystem periodically and estimated (with a very high precision) for the remaining samples. So in config mode, the time will probably jitter more than in measurement mode.
	XsensResultValue getXmOutputMode(uint8_t& mode);						//!< \brief Return the dual-output mode of the XM. \details This function retrieves the dual mode output mode of the Xbus Master. The dual output mode of the Xbus Master defines whether it will send data on the serial connection (at the same baud rate as the bluetooth connection) when it is connected via Bluetooth. When set to 0, the serial communication is disabled, data is sent over the serial bus. \note When dual-mode is enabled, the Xbus Master will NOT receive command messages on the serial bus. \see setXmOutputMode
	XsensResultValue gotoConfig(void);									//!< \brief Place all connected devices into Configuration Mode. \details This function places the sensors in configuration mode. \note This function has no effect when reading from a log file
	XsensResultValue gotoMeasurement(void);								//!< \brief Place all connected devices into Measurement Mode. \details This function places the sensors in measurement mode. \note This function has no effect when reading from a log file
	XsensResultValue initBus(void);										//!< \brief Perform an initBus request. \details See the low-level documentation for more information on the InitBus message. \see refreshCache setBusPowerState
	bool isLogging(void) const			//!< \brief Return whether the Cmt3 object is writing to a log file or not
		{ return m_logging; }
	bool isPortOpen(void) const			//!< \brief Return whether the communication port is open or not.
		{ return (m_serial.isOpen()); }
	bool isXm(void) const;				//!< \brief Return whether the main device is an Xbus Master or not.

	XsensResultValue openPort(const char *portName, const uint32_t baudRate = CMT_DEFAULT_BAUD_RATE,
							uint32_t readBufSize = CMT_DEFAULT_READ_BUFFER_SIZE,
							uint32_t writeBufSize = CMT_DEFAULT_WRITE_BUFFER_SIZE);	//! \brief Open a communication channel to the given COM port number. \details This function is first passed through to the Cmt2s object. Then, the device settings are retrieved and stored locally. This function automatically places the device(s) in config mode, using gotoConfig. \see gotoConfig closePort
#ifdef _WIN32
	XsensResultValue openPort(const uint32_t portNumber, const uint32_t baudRate = CMT_DEFAULT_BAUD_RATE,
							uint32_t readBufSize = CMT_DEFAULT_READ_BUFFER_SIZE,
							uint32_t writeBufSize = CMT_DEFAULT_WRITE_BUFFER_SIZE);	//! \brief Open a communication channel to the given COM port number. \details This function is first passed through to the Cmt2s object. Then, the device settings are retrieved and stored locally. This function automatically places the device(s) in config mode, using gotoConfig. \see gotoConfig closePort
#endif
	XsensResultValue peekLogMessageId(uint8_t& messageId);														//!< \brief Peek(take a look) at the message ID of the next message. \details This function can only be used when reading from a log file. It will find the next message in the file and place its message ID in the messageId parameter. Afterwards, the read position of the file will be restored. \remarks This function is mostly useful when dealing with a file that has more than just data messages. By using the peek function, it is possible to decide whether a readDataPacket should be called or for example getBatteryLevel or getGpsStatus. When the peek function is not used and for example getBatteryLevel is called, all messages between the current read position and the first battery level message in the file will be skipped. An alternative would be to get the read position, call the desired function (get battery level) and restore the read position, but then the moment at which the (battery level, UTC time, satellite info, etc) data becomes available will not be known.
	XsensResultValue readDataPacket (Packet* pack, bool acceptOther = false);										//!< \brief Retrieve a data message. \details This function will attempt to read a data message from the open port or from the log file, depending on the system state. When acceptOther is set to true, the first received message will be returned. If a data message is successfully read, XRV_OK will be returned. If another message is read, XRV_OTHER will be returned and the received message will be placed in the Packet. Otherwise, an appropriate error will be returned.
	XsensResultValue requestData(Packet* pack, const uint8_t *data = 0, const uint16_t count = 0);					//!\brief Request a data message and wait for it to arrive. \details This function is only useful when the skip factor is set to 0xFFFF.
	XsensResultValue reset(void);																					//!< \brief Reset all connected sensors.
	XsensResultValue resetOrientation(const CmtResetMethod method, const CmtDeviceId deviceId = CMT_DID_MASTER);	//!< \brief Perform an orientation reset on a device. \details This function performs an orientation reset. See the MT documentation for more information about Orientation resets. \note If you wish to save the setting to the device, perform the CMT_RESETORIENTATION_STORE operation while in Config mode after having performed the appropriate orientation reset in measurement mode.
	XsensResultValue setNoRotation(const uint16_t duration, const CmtDeviceId deviceId = CMT_DID_MASTER);	//!< \brief Initiates the XKF3 'no rotation' update procedure. \details This function Initiates the XKF3 'no rotation' update procedure. See the MT documentation for more information. \note Note that this message does not convey any status. Bits 3-4 of the MT status byte are used instead. Only valid in measurement mode.
	XsensResultValue restoreFactoryDefaults(const CmtDeviceId deviceId = CMT_DID_MASTER);							//!< \brief Restore the device to factory default settings. \details This function completely restores the selected device to the default settings (115k2 baud rate, 100Hz sample frequency, factory defined scenarios). \note This function is only available in configuration mode.
	XsensResultValue setBaudrate (const uint32_t baudrate, bool reconnect = true);								//!< \brief Set the baudrate and possibly reconnect. \details Use this function to change the baudrate of the device. This actually tries to change the baud rate of the current connection. When reconnect is set to true, the device receives a Reset message and the port is reopened at the new baudrate. Otherwise, make sure to perform a Reset manually, since the new baudrate will not be set until a Reset has been performed. \note To change the baudrate of the serial connection while connected via Bluetooth, use setSerialBaudrate. \see getBaudrate setSerialBaudrate getSerialBaudrate \note This function is only available in configuration mode.
	XsensResultValue setBluetoothState(const bool enabled);															//!< \brief Set the Bluetooth state of the Xbus Master. \details This function sets the state of the bluetooth communication to on or off. \note This function is only available in configuration mode.
	XsensResultValue setBusPowerState(const bool enabled);																	//!< \brief Switch the Xbus Master bus power on or off. \details Use this function to switch the Xbus Master Xbus power on or off. \remarks This function can be used to save a lot of power when not measuring, while still keeping a connection to the system. However, there is a relatively long startup time when restoring power as the sensors are reinitialized. \note You will need to perform an initBus and possibly a refreshCache call after switching the power back on with this function. \note This function is only available in configuration mode. \see initBus refreshCache
	XsensResultValue setDeviceMode (const CmtDeviceMode& mode, bool force, const CmtDeviceId deviceId = CMT_DID_MASTER);	//!< \brief Set the complete output mode of a device. \details This function updates the complete output mode of the specified device. It only updates values that are different than those reported by the device unless force is set to true. The function will automatically update only the part of the device mode that is relevant for the device. So it is possible to configure all devices, including an Xbus Master with the same mode (only the Xbus Master will update its period, while the Motion Trackers will update their output mode and settings). \note This function is only available in configuration mode. \see getDeviceMode getDeviceMode2 setDeviceMode2
	XsensResultValue setDeviceMode2 (const CmtDeviceMode2& mode, bool force, const CmtDeviceId deviceId = CMT_DID_MASTER);	//!< \brief Set the complete output mode2 of a device. \details This function updates the complete output mode of the specified device. It only updates values that are different than those reported by the device unless force is set to true. The function will automatically update only the part of the device mode that is relevant for the device. So it is possible to configure all devices, including an Xbus Master with the same mode (only the Xbus Master will update its period, while the Motion Trackers will update their output mode and settings). \note This function is only available in configuration mode. \see getDeviceMode2 getDeviceMode setDeviceMode
	XsensResultValue setErrorMode(const uint16_t mode);																//!< \brief Set the error mode of the device. \details This function sets the error mode of the device. The error mode determines how the device handles errors. See the low-level communication documentation for more details. \note This function is only available in configuration mode. \see getErrorMode
	XsensResultValue setGotoConfigTries(const uint16_t tries);												//!< \brief Set the number of times the gotoConfig function will attempt a gotoConfig before failing. \details This is especially useful when using RS485 communication or when for some reason the communication lines are not reliable.
	XsensResultValue setHeading (const double heading, const CmtDeviceId deviceId = CMT_DID_MASTER);				//!< \brief Set the heading offset. \details This function sets the heading offset in radians used by the device. The valid range is -pi to +pi. The heading offset is used as a final correction on the output orientation. \note This function is only available in configuration mode. \see getHeading getMagneticDeclination setMagneticDeclination
	XsensResultValue setLatLonAlt(const CmtVector& lla, const CmtDeviceId deviceId = CMT_DID_MASTER);			//!< \brief Set the current sensor position. \details Use this function to set the current position in latitude, longitude, altitude. \see getLatLonAlt
	XsensResultValue setLocationId (uint16_t locationId, const CmtDeviceId deviceId = CMT_DID_MASTER);		//!< \brief Set the location ID of a sensor. \details This function sets the location ID stored in the device. \note This function is only available in configuration mode. \see getLocationId
	XsensResultValue setMagneticDeclination(const double declination, const CmtDeviceId deviceId = CMT_DID_MASTER);	//!< \brief Set the stored magnetic declination. \details This function sets the stored local magnetic declination in radians. The valid range is -pi to +pi. The magnetic declination is used in the sensor fusion process to determine the output orientation. \note This function is only available in configuration mode. \see getHeading setHeading getMagneticDeclination
	XsensResultValue setObjectAlignmentMatrix(const CmtMatrix& matrix, const CmtDeviceId deviceId = CMT_DID_MASTER);		//!< \brief Set the currently used object alignment matrix. \details Use this function to set the object matrix to be used as the sensor frame with respect to the reference frame. See the manual for more information on coordinate systems and object resets. \see getObjectAlignmentMatrix
	XsensResultValue setProcessingFlags (uint16_t processingFlags, const CmtDeviceId deviceId = CMT_DID_MASTER);		//!< \brief Set the processing flags of a sensor. \details This function sets the processing flags stored in the device. \note This function is only available in configuration mode. \see getProcessingFlags
	XsensResultValue setSyncInSettings(const CmtSyncInSettings& settings);											//!< \brief Set the inbound synchronization settings of an MT device. \details This function sets the current inbound synchronization settings of the MT device (sync mode, skip factor and offset). This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \note This function is only available in configuration mode. \see getSyncInSettings getSyncOutSettings setSyncOutSettings getSyncMode setSyncMode
	XsensResultValue setSyncInMode (const uint16_t mode);		//!< \brief Set the inbound synchronization mode of an MT device. \details This function sets the current inbound synchronization mode of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see getSyncInMode setSyncInSettings getSyncInSettings getSyncInSkipFactor setSyncInSkipFactor getSyncInOffset setSyncInOffset getSyncOutSettings setSyncOutSettings getSyncMode setSyncMode
	XsensResultValue setSyncInSkipFactor (const uint16_t skipFactor);		//!< \brief Set the inbound synchronization skip factor of an MT device. \details This function sets the current inbound synchronization skip factor of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see getSyncInSkipFactor setSyncInSettings getSyncInSettings getSyncInOffset setSyncInOffset getSyncOutSettings setSyncOutSettings getSyncMode setSyncMode
	XsensResultValue setSyncInOffset (const uint32_t offset);			//!< \brief Set the inbound synchronization offset of an MT device. \details This function sets the current inbound synchronization offset of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see getSyncInOffset setSyncInSettings getSyncInSettings getSyncInSkipFactor setSyncInSkipFactor getSyncOutSettings setSyncOutSettings getSyncMode setSyncMode
	XsensResultValue setSyncMode(const uint8_t mode);						//!< \brief Set the sync mode of the Xbus Master. \details This function sets the current synchronization mode used by the specified Xbus Master. This function is not valid for MT devices. \note This function is only available in configuration mode. \see getSyncMode getSyncInSettings setSyncInSettings getSyncOutSettings setSyncOutSettings
	XsensResultValue setSyncOutSettings(const CmtSyncOutSettings& settings);	//!< \brief Set the outbound synchronization settings of an MT device. \details This function sets the current outbound synchronization settings of the MT device (sync mode, skip factor, offset and pulse width). This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \note This function is only available in configuration mode. \see setSyncOutSettings getSyncInSettings setSyncInSettings getSyncMode setSyncMode
	XsensResultValue setSyncOutMode (const uint16_t mode);		//!< \brief Set the outbound synchronization mode of an MT device. \details This function sets the current outbound synchronization mode of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see getSyncOutMode setSyncOutSettings getSyncOutSettings getSyncOutPulseWidth setSyncOutPulseWidth getSyncOutSkipFactor setSyncOutSkipFactor getSyncOutOffset setSyncOutOffset getSyncInSettings setSyncInSettings getSyncMode setSyncMode
	XsensResultValue setSyncOutPulseWidth (const uint32_t pulseWidth);		//!< \brief Set the outbound synchronization pulse width of an MT device. \details This function sets the current outbound synchronization pulse width of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see getSyncOutPulseWidth setSyncOutSettings getSyncOutSettings setSyncOutMode getSyncOutMode getSyncOutSkipFactor setSyncOutSkipFactor getSyncOutOffset setSyncOutOffset getSyncInSettings setSyncInSettings getSyncMode setSyncMode
	XsensResultValue setSyncOutSkipFactor (const uint16_t skipFactor);		//!< \brief Set the outbound synchronization skip factor of an MT device. \details This function sets the current outbound synchronization skip factor of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see setSyncOutSkipFactor setSyncOutSettings getSyncOutSettings setSyncOutMode getSyncOutMode getSyncOutPulseWidth setSyncOutPulseWidth getSyncOutOffset setSyncOutOffset getSyncInSettings setSyncInSettings getSyncMode setSyncMode
	XsensResultValue setSyncOutOffset (const uint32_t offset);		//!< \brief Set the outbound synchronization offset of an MT device. \details This function sets the current outbound synchronization offset of the MT device. This function does not work for Xbus Masters and should not be used for sensors connected to an Xbus Master. \see getSyncOutOffset setSyncOutSettings getSyncOutSettings setSyncOutMode getSyncOutMode getSyncOutPulseWidth setSyncOutPulseWidth getSyncOutSkipFactor setSyncOutSkipFactor getSyncInSettings setSyncInSettings getSyncMode setSyncMode
	XsensResultValue setTimeout (const uint32_t ms)						//!< \brief Set the default timeout value to use in blocking operations on the communication port.
		{ return (m_lastResult = m_serial.setTimeout(ms)); }
	XsensResultValue setTimeoutConfig (const uint32_t timeout = CMT3_DEFAULT_TIMEOUT_CONF);		//!< \brief Set the configuration mode timeout. \details When in config mode, the system uses a different message timeout than in measurement mode, since configuration messages can take longer to process than measurement mode messages. This function can be used to set the config mode timeout in ms. \note This function is only available in configuration mode. \see getTimeoutConfig getTimeoutMeasurement setTimeoutMeasurement setTimeout
	XsensResultValue setTimeoutMeasurement (const uint32_t timeout = CMT3_DEFAULT_TIMEOUT_MEAS);	//!< \brief Set the measurement mode timeout. \details When in measurement mode, the system uses a different message timeout than in config mode, since measurement mode messages should be faster to process than config mode messages. This function can be used to set the measurement mode timeout in ms. \note This function is only available in configuration mode. \see getTimeoutMeasurement getTimeoutConfig setTimeoutConfig setTimeout
	XsensResultValue setTransmissionDelay(const uint16_t delay);																//!< \brief Set the RS485 acknowledge transmission delay of the device. \details This function sets the RS485 acknowledge transmission delay of the device. The RS485 acknowledge transmission delay determines the minimal delay to response on request messages. See the low-level communication documentation for more details. \see getAckTransmissionDelay \note This function is only available in configuration mode.
	XsensResultValue setXmOutputMode(const uint8_t mode);											//!< \brief Set the dual-output mode of the XM. \details This function sets the dual mode output mode of the Xbus Master. The dual output mode of the Xbus Master defines whether it will send data on the serial connection (at the same baud rate as the bluetooth connection) when it is connected via Bluetooth. When set to 0, the serial communication is disabled, data is sent over the serial bus. \note When dual-mode is enabled, the Xbus Master will NOT receive commands on the serial bus. \note This function is only available in configuration mode. \see getXmDualOutputMode
	XsensResultValue setXmPowerOff(void);											//!< \brief Switch the connected Xbus Master. \details This function tell the connected Xbus Master to power down. This differs from setBusPowerState, because this function actually powers down the Xbus Master itself, while setBusPowerState only powers down the bus controlled by the Xbus Master. After This function is called, the Xbus Master must be manually switched on to make it operational again. \see setBusPowerState
	XsensResultValue refreshCache(const bool file = false);							//!< Update device information stored on host PC. \details Some device information is cached on the host PC for faster access. The Cmt3 automatically tries to keep the cache up to date. But when unexpected things happen, such as custom messages that change the settings, or a power-cycle, then the user may need to tell Cmt3 to update its cache. When both a file and a port are open, the file parameter can be used to indicate what data source to read from (true is file, false is port). \note This function is only available in configuration mode.
	XsensResultValue waitForDataMessage(Packet* pack);								//!< \brief Wait for a data message to arrive. \details The function waits for a data message to arrive or until a timeout occurs. The function will also accept error messages.
	XsensResultValue createLogFile(const char* filename,bool startLogging = false);	//!< \brief Create a log file for incoming messages. \details This function creates a log file for recording incoming messages. The Cmt3 object must be connected to a communication port or the function will fail. \param filename The name of the file to use as a log file. A fully qualified (local) path+filename is recommended. \param startLogging When set to true (default), Cmt3 will immediately start logging incoming messages to the file, otherwise setLogMode must be called first before logging is started. \remarks If a writable file of the same name already exists in the target location, it will be overwritten without warning. \see closeLogFile isLogFileOpen openLogFile setLogMode \note This function is available in configuration AND in measurement mode.
	XsensResultValue createLogFile(const wchar_t* filename,bool startLogging = false);	//!< \brief Create a log file for incoming messages. \details This function creates a log file for recording incoming messages. The Cmt3 object must be connected to a communication port or the function will fail. \param filename The name of the file to use as a log file. A fully qualified (local) path+filename is recommended. \param startLogging When set to true (default), Cmt3 will immediately start logging incoming messages to the file, otherwise setLogMode must be called first before logging is started. \remarks If a writable file of the same name already exists in the target location, it will be overwritten without warning. \see closeLogFile isLogFileOpen openLogFile setLogMode \note This function is available in configuration AND in measurement mode.
	XsensResultValue closeLogFile(bool del=false);									//!< \brief Close an open log file. \details This function closes the logfile if it was open. \param del When set to true, the file will be deleted after closing if it is not read-only. This is mostly useful for temporary log-files.	\see createLogFile isLogFileOpen openLogFile setLogMode
	bool isLogFileOpen(const char* filename) const;				//!< \brief Return whether or not(true or false) the supplied file is open. \details When the filename parameter is NULL or empty "", the function will simply return whether a log file is open. Otherwise, the supplied name will be checked against the name of the open log file as well. \return true if the log file is open, false if it isn't \see closeLogFile createLogFile openLogFile setLogMode
	bool isLogFileOpen(const wchar_t* filename) const;				//!< \brief Return whether or not(true or false) the supplied file is open. \details When the filename parameter is NULL or empty "", the function will simply return whether a log file is open. Otherwise, the supplied name will be checked against the name of the open log file as well. \return true if the log file is open, false if it isn't \see closeLogFile createLogFile openLogFile setLogMode
	XsensResultValue openLogFile(const char* filename);			//!< \brief Open a log file for input. \details This function opens the supplied log file for reading. The function will fail if a serial connection is currently open. \param filename The name of the file to open. It is recommended to use a fully qualified path+filename. \note This function is only available in configuration mode. \see closeLogFile createLogFile isLogFileOpen setLogMode
	XsensResultValue openLogFile(const wchar_t* filename);			//!< \brief Open a log file for input. \details This function opens the supplied log file for reading. The function will fail if a serial connection is currently open. \param filename The name of the file to open. It is recommended to use a fully qualified path+filename. \note This function is only available in configuration mode. \see closeLogFile createLogFile isLogFileOpen setLogMode
	XsensResultValue setDataSource(bool readFromFile);			//!< \brief Set whether to read from comm port or file. \details While it is not possible to open a port or file while the other is open, it is possible to create a log file while a port is open. In some rare cases it may be required to log data and read it back while the port remains open and then continue logging in the same file. This is not recommended. Instead, log to a file, close it and then open it in another Cmt3 object. However, if you must do this, then this function can be used to specify that you want to switch between reading from the log file (true) or port (false).
	XsensResultValue setLogMode(bool active);					//!< \brief Set the logging mode. \details This function sets the logging mode to enabled (true) or disabled (false). When enabled, all received messages are logged to the file. \remarks Some information that is cached on the host PC will generate faked messages in the log file. Eg. getConfiguration and some others.
	XsensResultValue resetLogFileReadPos(void);					//!< \brief Restart reading from the start of the open log file. \details This function resets the read position to the start of the open log file. Only the read position is affected, the write position remains the same. \see openLogFile
	XsensResultValue writeMessageToLogFile(const Message& msg);																				//! \brief Write the specified message to the open log file. \details This function can be used to add custom messages to a log file. \note A typical log file will only contain acknowledge messages, not request messages. \see createLogFile
	XsensResultValue getAvailableScenarios(CmtScenario* scenarios, const CmtDeviceId deviceId = CMT_DID_MASTER);							//!< \brief Retrieve a list of the available scenarios. \details Use this function to retrieve a list of all scenarios available in a Motion Tracker. See the supplied documentation for more information about scenarios. \param scenarios A buffer for storing the available scenarios. The supplied buffer should be able to contain at least 6 scenarios, but for future devices a larger buffer is advised. Use CMT_MAX_SCENARIOS_IN_MT+1. The list is terminated by a scenario that has type 0. \remarks The type of any of the returned scenarios can be safely supplied to the setScenario function. \see getScenario setScenario \note This function is only available in configuration mode.
	XsensResultValue getScenario(uint8_t& scenarioType, uint8_t& scenarioVersion, const CmtDeviceId deviceId = CMT_DID_MASTER);	//!< \brief Get the currently active scenario from a Motion Tracker. \details This function retrieves the scenario currently used by the specified device when outputting orientation and/or position data. \see getAvailableScenarios setScenario \note This function is only available in configuration mode.
	XsensResultValue setScenario(const uint8_t scenarioType, const CmtDeviceId deviceId = CMT_DID_MASTER);							//!< \brief Specify the scenario to use in the sensor. \details This function specifies the scenario that the sensor should use for converting raw data into orientation and/or position data. This must be one of the scenarios in the list supplied by getAvailableScenarios. \see getAvailableScenarios getScenario \note This function is only available in configuration mode.
	XsensResultValue getGravityMagnitude(double& magnitude, const CmtDeviceId deviceId = CMT_DID_MASTER);			//!< \brief Retrieve the currently used magnitude of the gravity vector. \details The magnitude of the gravity vector is used to determine absolute acceleration from measured acceleration. \see setGravityMagnitude \note This function is only available in configuration mode.
	XsensResultValue setGravityMagnitude(const double magnitude, const CmtDeviceId deviceId = CMT_DID_MASTER);		//!< \brief Set the currently used magnitude of the gravity vector. \details The magnitude of the gravity vector is used to determine absolute acceleration from measured acceleration. Use this function to set tit to a custom value in m/s2. The default value of 9.812687357684514m/s2 should be fine for most places on earth, but in some cases the gravity may be drastically different from standard Earth gravity (eg. space, deep subterranean/submarine, polar regions, gravitational anomalies. See also <A HREF="http://www.abc.net.au/science/news/stories/s911917.htm">http://www.abc.net.au/science/news/stories/s911917.htm</A> and <A HREF="http://en.wikipedia.org/wiki/Earth%27s_gravity#Comparative_gravities_in_various_cities_around_the_world">http://en.wikipedia.org/wiki/Earth%27s_gravity#Comparative_gravities_in_various_cities_around_the_world</A>) \note Correct orientation output cannot be guaranteed when an incorrect value is supplied for the gravity. Changing this value is at your own risk. \see getGravityMagnitude \remarks In future versions, the MTi-G may be able to estimate the local gravity magnitude on its own. \note This function is only available in configuration mode.
	XsensResultValue getGpsLeverArm(CmtVector& arm, const CmtDeviceId deviceId = CMT_DID_MASTER);					//!< \brief Get the currently used GPS lever arm. \details Use this function to retrieve the vector currently used as the GPS lever arm in meters. The GPS lever arm is the relative position of the GPS antenna to the MTi-G unit. The arm is specified in the object coordinate system. See the manual for more information on coordinate systems, alignment resets and the lever arm. \see setGpsLeverArm \note This function is only available in configuration mode. \note This function is only available for MTi-G devices.
	XsensResultValue getGpsStatus(CmtGpsStatus& status, const CmtDeviceId deviceId = CMT_DID_MASTER);		//!< \brief Request the status of the GPS satellites in orbit. \details This function requests the GPS satellite status information from the GPS subsystem. In config mode, this information is requested from the GPS subsystem immediately, which can cause a relatively long delay (250ms) before a reply is received. In measurement mode, the satellite status is regularly polled internally and the latest status is returned immediately when this function is called.
	XsensResultValue setGpsLeverArm(const CmtVector& arm, const CmtDeviceId deviceId = CMT_DID_MASTER);		//!< \brief Set the currently used GPS lever arm. \details Use this function to set the vector currently used as the GPS lever arm. The GPS lever arm is the relative position of the GPS antenna to the MTi-G unit. The arm is specified in the object coordinate system and in meters. See the manual for more information on coordinate systems, alignment resets and the lever arm. \see getGpsLeverArm \note This function is only available in configuration mode. \note This function is only available for MTi-G devices.
	XsensResultValue storeXkfState(const CmtDeviceId deviceId = CMT_DID_MASTER);							//!< \brief Store important components of the XKF filter state to non-volatile memory. \details This function allows you to store some critical components of the internal XKF filter state to non-volatile memory. The stored settings will be used to initialize the filter whenever the sensor is switched to Measurement mode. \note This function is only available in Config mode.
};

} // end of xsens namespace

#endif	// _CMT3_H_2006_04_14

#ifndef _JANITORS_H_2006_05_01
#define _JANITORS_H_2006_05_01

// required for older gnu c++ compiler versions due to difference in attribute declarations
#if defined(__GNUC__) && !defined(HAVE_CDECL)
#   define __cdecl __attribute__((cdecl))
#   define __stdcall __attribute__((stdcall))
#endif

namespace xsens {


//////////////////////////////////////////////////////////////////////////////////////////
/*! \brief Class function calling janitor class

	This class can be used to make sure that the given class function is called when the
	janitor leaves scope.
*/
template <class T, typename R = void>
class JanitorClassFunc {
public:
	typedef R (T::*t_func_JanitorClasssFunc)(void);
private:
	T& m_control;
	t_func_JanitorClasssFunc m_funcJCF;
	bool m_enabled;
public:
	
	JanitorClassFunc<T,R>(T& control, t_func_JanitorClasssFunc func, bool enabl = true) :
		m_control(control), m_funcJCF(func), m_enabled(enabl)
	{
	}
	~JanitorClassFunc<T,R>()
	{
		if (m_enabled)
			(m_control.*m_funcJCF)();
	}
	
	void disable(void)
		{ m_enabled = false; }
	
	void enable(void)
		{ m_enabled = true; }
};


}	// end of xsens namespace

#endif	// _JANITORS_H_2006_05_01
#ifndef _XSENS_LIST_H_2006_06_08
#define _XSENS_LIST_H_2006_06_08


#ifndef _JANITORS_H_2006_05_01
#	include "xsens_janitors.h"
#endif


#define XSENS_LIST_NOTFOUND	0xFFFFFFFF

#ifdef _XSENS_LIST_RANGE_CHECKS
#	ifdef _MSC_VER
#		define XSENS_LIST_THROW throw(...)
#	else
#		define XSENS_LIST_THROW
#	endif
#else
#	define XSENS_LIST_THROW
#endif

#include <stdlib.h>
#include <malloc.h>

namespace xsens {

#define CMT_LIST_LINEAR_SEARCH_TRESHOLD	10

	/*! \brief Dynamic list class

		This class can store items of the given type. If the type supports the < operator
		it can also be sorted.
		Items in the list can be accessed through the [] operator or the get() function.

		Do NOT use any item type that requires a constructor to work correctly. Pointers to these
		objects can work though.
	*/
	template <typename T>
	class List
	{
	private:
		void operator = (const List& list);	//!< intentionally NOT implemented due to ambiguous nature
			//! Sorts the list in an ascending order, using the T::< operator.
		void qSort(uint32_t left, uint32_t right);
			//! Sorts the list in an ascending order, using the T::< operator on dereferenced list items.
		void qSortDeref(uint32_t left, uint32_t right);

	protected:
		T* m_data;							//!< The array containing the items
		uint32_t m_max;				//!< The current size of the data array
		uint32_t m_count;				//!< The number of items currently in the list
		JanitorClassFunc<List<T> >* m_jcf;	//!< Used to clean up the list on exit
		bool m_manage;

			//! Construct a list as a reference to a raw list 
		List(const uint32_t size, T* src, bool manage);
	public:

			//! A comparison function type, should return -1, 0 or 1 for <, == and >
		typedef int32_t (*cmpFunc) (const T&,const T&);

			//! Standard constructor, creates an empty list with some room for items.
		List();
			//! Construct a list with a capacity of at least the given size.
		List(const uint32_t size);
			//! Construct a list as a direct copy of another list
		List(const List<T>& src);
			//! Construct a list as a copy of a raw list 
		List(const uint32_t size, const T* src);
			//! Destroy the list. This does NOT automatically delete items IN the list.
		~List();

			//! Calls delete for all items in the list and then clears the list.
		void deleteAndClear(void);
			//! Calls free for all items in the list and then clears the list.
		void freeAndClear(void);
			//! Clears the list without explicitly deleting anything.
		void clear(void);
			//! Resizes the list to at least the given size.
		void resize(uint32_t newSize);
			//! Adds an item to the end of the list.
		void append(const T& item);
			//! Adds a number of items to the end of the list.
		void appendList(uint32_t count, const T* lst);
			//! Adds the contents of the source list to the end of the list.
		void appendDeepCopy(const List<T>& source);
			//! Adds the contents of the source list to the end of the list.
		void appendShallowCopy(const List<T>& source);
			//! Adds a copy of a referenced item to the end of the list using newItem = new TB(item).
			template <typename TB>
		void appendCopy(const TB& item);
			//! Adds a related item to the end of the list, using the T = TR operator.
			template <typename TR>
		void appendRelated(const TR& item);
			//! Removes an item at the given index in the list.
		void remove(const uint32_t index) XSENS_LIST_THROW;
			//! Swaps two items in the list.
		void swap(const uint32_t i, const uint32_t j) XSENS_LIST_THROW;
			//! Removes an item at the given index in the list.
		void deleteAndRemove(const uint32_t index) XSENS_LIST_THROW;
			//! Removes an item at the given index in the list.
		void freeAndRemove(const uint32_t index) XSENS_LIST_THROW;
			//! Retrieves the last item.
		T& last(void) const XSENS_LIST_THROW;
			//! Retrieves the item at the given index. An index beyond the end returns the first item.
		T& get(const uint32_t index) const XSENS_LIST_THROW;
			//! Retrieves the item at the given index. An index beyond the end probably causes an exception.
		T& operator [] (const uint32_t index) const XSENS_LIST_THROW;
			//! Inserts an item at the given index, shifting any items below it down one spot.
		void insert(const T& item, const uint32_t index);
			//! Inserts a copy of the referenced item at the given index, shifting any items below it down one spot.
			template <typename TB>
		void insertCopy(const TB& item, const uint32_t index);
			//! Assumes the list is sorted and inserts the item at the appropriate spot.
		uint32_t insertSorted(const T& item);
			//! Assumes the list is sorted by dereferenced values and inserts the item at the appropriate spot.
		uint32_t insertSortedDeref(const T& item);
			//! Assumes the list is sorted and inserts a copy of the referenced item at the appropriate spot.
			template <typename TB>
		uint32_t insertSortedCopy(const TB& item);
			//! Returns the number of items currently in the list.
		uint32_t length(void) const { return m_count; }
			//! Sorts the list in an ascending order, using the T::< operator.
		void sortAscending(void);
			//! Sorts the list in an ascending order, using the T::< operator on dereferenced list items.
		void sortAscendingDeref(void);
			//! Sorts the first list in an ascending order, using the T::< operator, the second list will be updated the same way.
			template <typename T2>
		void twinSortAscending(List<T2>& twin);
			//! Finds an item in an unsorted list (walk over all items) using the T::== operator
			template <typename TB>
		uint32_t find(const TB& item) const;
			//! Finds an item in an unsorted list (walk over all items) using the T::== operator on dereferenced list items
			template <typename TB>
		uint32_t findDeref(const TB& item) const;
			//! Finds an item in a sorted list (binary search) using the T::== and T::< operators
			template <typename TB>
		uint32_t findSorted(const TB& item) const;
			//! Finds an item in a sorted list (binary search) using the T::== and T::< operators on dereferenced list items
			template <typename TB>
		uint32_t findSortedDeref(const TB& item) const;
			//! Reverse the order of the list, useful for sorted lists that are read/created in the reverse order
		void reverse(void);
			//! Removes items from the end of the list.
		void removeTail(const uint32_t count) XSENS_LIST_THROW;
		void deleteAndRemoveTail(const uint32_t count) XSENS_LIST_THROW;
		void freeAndRemoveTail(const uint32_t count) XSENS_LIST_THROW;

			//! Type for an equality compare function, should return true when NOT equal
		typedef int32_t (__cdecl * InequalityFunction)(const T&, const T&);
			//! Finds an item in an unsorted list (walk over all items) using the given inequality function
		uint32_t find(const T item, InequalityFunction fnc) const;

		void deleteItemsOnDestroy(void);
		void freeItemsOnDestroy(void);

			//! Removes any duplicate entries and returns the number of items removed. Items are compared directly.
		uint32_t removeDuplicateEntries(void);
			//! Removes any duplicate entries and returns the number of items removed. Items are compared after dereferencing.
		uint32_t removeDuplicateEntriesDeref(void);

			//! Make a copy of the list, duplicating list items i with: copy[i] = new TB(*source[i])
			template <typename TB>
		void isDeepCopyOf(const List<T>& source);
			//! Overwrites the current list with a direct copy (a=b) of another list.
		void isShallowCopyOf(const List<T>& source);

			//! Returns the start of the linear data buffer
		const T* getBuffer(void) const { return m_data; }
	};


template <typename T>
List<T>::List()
{
	m_max = 16;
	m_count = 0;
	m_data = (T*) malloc(m_max * sizeof(T));
	m_jcf = NULL;
	m_manage = true;
}

template <typename T>
List<T>::List(uint32_t size)
{
	m_max = size;
	if (m_max == 0)
		m_max = 1;
	m_count = 0;
	m_data = (T*) malloc(m_max * sizeof(T));
	m_jcf = NULL;
	m_manage = true;
}

template <typename T>
List<T>::List(const List<T>& src)
{
	m_max = src.m_max;
	if (m_max == 0)
		m_max = 1;
	m_count = src.m_count;
	m_data = (T*) malloc(m_max * sizeof(T));
	m_jcf = NULL;
	if (m_count > 0)
		memcpy(m_data,src.m_data,m_count*sizeof(T));
	m_manage = true;
}

template <typename T>
List<T>::List(const uint32_t size, const T* src)
{
	m_max = size;
	if (m_max == 0)
		m_max = 1;
	m_count = size;
	m_data = (T*) malloc(m_max * sizeof(T));
	m_jcf = NULL;
	if (m_count > 0)
		memcpy(m_data,src,m_count * sizeof(T));
	m_manage = true;
}

template <typename T>
List<T>::List(const uint32_t size, T* src, bool manage)
{
	m_max = size;
	m_count = size;
	m_data = src;
	m_jcf = NULL;
	m_manage = manage;
}

template <typename T>
List<T>::~List()
{
	if (m_jcf != NULL)
		delete m_jcf;
	if (m_manage && m_data != NULL)
		free(m_data);
	m_jcf = NULL;
	m_data = NULL;
}

template <typename T>
void List<T>::deleteAndClear(void)
{
	for (unsigned i=0;i<m_count;++i)
		delete m_data[i];
	m_count = 0;
}

template <typename T>
void List<T>::freeAndClear(void)
{
	for (unsigned i=0;i<m_count;++i)
		free(m_data[i]);
	m_count = 0;
}

template <typename T>
void List<T>::clear(void)
{
	m_count = 0;
}

template <typename T>
void List<T>::resize(uint32_t newSize)
{
	if (m_manage)
	{
		if (newSize == m_max)
			return;
		if (m_count > newSize)
			m_max = m_count;
		else
			m_max = newSize;
		if (m_max == 0)
			m_max = 1;	// size 0 is not allowed

		m_data = (T*) realloc(m_data,m_max * sizeof(T));
	}
}

template <typename T>
void List<T>::append(const T& item)
{
	if (m_count == m_max)
		resize(m_max + 1 + m_max/2);
	m_data[m_count++] = item;
}

template <typename T>
void List<T>::appendList(uint32_t count, const T* lst)
{
	if (m_count+count > m_max)
		resize(m_max + count + m_max/2);
	for (unsigned i = 0; i < count; ++i)
		m_data[m_count++] = lst[i];
}

template <typename T>
void List<T>::appendDeepCopy(const List<T>& source)
{
	if (m_max < source.m_count + m_count)
		resize(source.m_count + m_count);

	for (uint32_t i = 0;i<source.m_count;++i)
		m_data[m_count++] = new T(*source.m_data[i]);
}

template <typename T>
void List<T>::appendShallowCopy(const List<T>& source)
{
	if (m_max < source.m_count + m_count)
		resize(source.m_count + m_count);

	for (uint32_t i = 0;i<source.m_count;++i)
		m_data[m_count++] = source.m_data[i];
}

template <typename T>
template <typename TB>
void List<T>::appendCopy(const TB& item)
{
	if (m_count == m_max)
		resize(m_max + 1 + m_max/2);
	m_data[m_count++] = new TB(item);
}

template <typename T>
template <typename TR>
void List<T>::appendRelated(const TR& item)
{
	if (m_count == m_max)
		resize(m_max + 1 + m_max/2);
	m_data[m_count++] = item;
}

template <typename T>
T& List<T>::last(void) const XSENS_LIST_THROW
{
	#ifdef _XSENS_LIST_RANGE_CHECKS
		if (m_count == 0)
			throw "List.last: empty list";
	#endif
	return m_data[m_count-1];
}

template <typename T>
T& List<T>::get(const uint32_t index) const XSENS_LIST_THROW
{
	#ifdef _XSENS_LIST_RANGE_CHECKS
		if (index >= m_count)
			throw "List.get: index out of bounds";
	#endif
	if (index >= m_count)
		return m_data[m_count-1];
	return m_data[index];
}

template <typename T>
void List<T>::insert(const T& item, const uint32_t index)
{
	if (m_count == m_max)
		resize(1 + m_max + (m_max >> 1));
	for (unsigned i=m_count;i>index;--i)
		m_data[i] = m_data[i-1];
	if (index <= m_count)
		m_data[index] = item;
	else
		m_data[m_count] = item;
	m_count++;
}

template <typename T>
template <typename TB>
void List<T>::insertCopy(const TB& item, const uint32_t index)
{
	if (m_count == m_max)
		resize(1 + m_max + (m_max >> 1));
	for (unsigned i=m_count;i>index;--i)
		m_data[i] = m_data[i-1];
	if (index <= m_count)
		m_data[index] = new TB(item);
	else
		m_data[m_count] = new TB(item);
	m_count++;
}

template <typename T>
T& List<T>::operator [] (const uint32_t index) const XSENS_LIST_THROW
{
	#ifdef _XSENS_LIST_RANGE_CHECKS
		if (index >= m_count)
			throw "List[]: index out of bounds";
	#endif
	return m_data[index];
}


template <typename T>
void List<T>::qSort(uint32_t left, uint32_t right)
{
	uint32_t l_hold, r_hold;
	T pivot;

	l_hold = left;
	r_hold = right;
	pivot = m_data[left];
	while (left < right)
	{
		while (!(m_data[right] < pivot) && (left < right))
			right--;
		if (left != right)
		{
			m_data[left] = m_data[right];
			left++;
		}
		while (!(pivot < m_data[left]) && (left < right))
			left++;
		if (!(left == right))
		{
			m_data[right] = m_data[left];
			right--;
		}
	}
	m_data[left] = pivot;
	if (l_hold < left)
		qSort(l_hold, left-1);
	if (r_hold > left)
		qSort(left+1, r_hold);
}

template <typename T>
void List<T>::qSortDeref(uint32_t left, uint32_t right)
{
	uint32_t l_hold, r_hold;
	T pivot;

	l_hold = left;
	r_hold = right;
	pivot = m_data[left];
	while (left < right)
	{
		while (!(*m_data[right] < *pivot) && (left < right))
			right--;
		if (left != right)
		{
			m_data[left] = m_data[right];
			left++;
		}
		while (!(*pivot < *m_data[left]) && (left < right))
			left++;
		if (!(left == right))
		{
			m_data[right] = m_data[left];
			right--;
		}
	}
	m_data[left] = pivot;
	if (l_hold < left)
		qSortDeref(l_hold, left-1);
	if (r_hold > left)
		qSortDeref(left+1, r_hold);
}

template <typename T>
void List<T>::sortAscending(void)
{
	if (m_count <= 1)
		return;
	struct Linker {
		Linker *prev, *next;
		uint32_t index;

		T item;
	};

	Linker* list = (Linker*) malloc(m_count*sizeof(Linker));

	list[0].prev = NULL;
	list[0].next = NULL;
	list[0].index = 0;
	list[0].item = m_data[0];

	Linker* curr = list;

	for (uint32_t i = 1; i < m_count; ++i)
	{
		list[i].index = i;
		list[i].item = m_data[i];
		if (m_data[i] < m_data[curr->index])
		{
			while (curr->prev != NULL)
			{
				curr = curr->prev;
				if (!(m_data[i] < m_data[curr->index]))
				{
					// insert after this
					list[i].next = curr->next;
					list[i].prev = curr;
					curr->next->prev = &list[i];
					curr->next = &list[i];
					curr = &list[i];
					break;
				}
			}
			if (curr != &list[i])
			{
				list[i].prev = NULL;
				list[i].next = curr;
				curr->prev = &list[i];
				curr = &list[i];
			}
		}
		else
		{
			while (curr->next != NULL)
			{
				curr = curr->next;
				if (m_data[i] < m_data[curr->index])
				{
					// insert before this
					list[i].next = curr;
					list[i].prev = curr->prev;
					curr->prev->next = &list[i];
					curr->prev = &list[i];
					curr = &list[i];
					break;
				}
			}
			if (curr != &list[i])
			{
				list[i].prev = curr;
				list[i].next = NULL;
				curr->next = &list[i];
				curr = &list[i];
			}
		}
	}

	// go to start of list
	while (curr->prev != NULL) curr = curr->prev;

	// copy sorted list back
	for (uint32_t i = 0; i < m_count; ++i)
	{
		m_data[i] = curr->item;
		curr = curr->next;
	}

	free(list);
}

template <typename T>
void List<T>::sortAscendingDeref(void)
{
	if (m_count <= 1)
		return;
	struct Linker {
		Linker *prev, *next;
		uint32_t index;

		T item;
	};

	Linker* list = (Linker*) malloc(m_count*sizeof(Linker));

	list[0].prev = NULL;
	list[0].next = NULL;
	list[0].index = 0;
	list[0].item = m_data[0];

	Linker* curr = list;

	for (uint32_t i = 1; i < m_count; ++i)
	{
		list[i].index = i;
		list[i].item = m_data[i];
		if (*m_data[i] < *m_data[curr->index])
		{
			while (curr->prev != NULL)
			{
				curr = curr->prev;
				if (!(*m_data[i] < *m_data[curr->index]))
				{
					// insert after this
					list[i].next = curr->next;
					list[i].prev = curr;
					curr->next->prev = &list[i];
					curr->next = &list[i];
					curr = &list[i];
					break;
				}
			}
			if (curr != &list[i])
			{
				list[i].prev = NULL;
				list[i].next = curr;
				curr->prev = &list[i];
				curr = &list[i];
			}
		}
		else
		{
			while (curr->next != NULL)
			{
				curr = curr->next;
				if (*m_data[i] < *m_data[curr->index])
				{
					// insert before this
					list[i].next = curr;
					list[i].prev = curr->prev;
					curr->prev->next = &list[i];
					curr->prev = &list[i];
					curr = &list[i];
					break;
				}
			}
			if (curr != &list[i])
			{
				list[i].prev = curr;
				list[i].next = NULL;
				curr->next = &list[i];
				curr = &list[i];
			}
		}
	}

	// go to start of list
	while (curr->prev != NULL) curr = curr->prev;

	// copy sorted list back
	for (uint32_t i = 0; i < m_count; ++i)
	{
		m_data[i] = curr->item;
		curr = curr->next;
	}

	free(list);
}

template <typename T>
template <typename T2>
void List<T>::twinSortAscending(List<T2>& twin)
{
	if (m_count <= 1)
		return;

	#ifdef _XSENS_LIST_RANGE_CHECKS
		if (m_count != twin.m_count)
			throw "List.twinSortAscending: sizes do not match";
	#endif
	uint32_t iteration = 0;
	uint32_t mini;
	T tmp;
	T2 tmp2;
	if (m_count > 1)
	while (iteration < m_count-1)
	{
		mini = iteration;
		for (uint32_t i=iteration+1;i<m_count;++i)
		{
			if (m_data[i] < m_data[mini])
				mini = i;
		}
		if (mini != iteration)
		{
			tmp = m_data[mini];
			m_data[mini] = m_data[iteration];
			m_data[iteration] = tmp;

			tmp2 = twin.m_data[mini];
			twin.m_data[mini] = twin.m_data[iteration];
			twin.m_data[iteration] = tmp2;
		}
		++iteration;
	}
}

template <typename T>
void List<T>::remove(const uint32_t index) XSENS_LIST_THROW
{
	#ifdef _XSENS_LIST_RANGE_CHECKS
		if (index >= m_count)
			throw "List.remove: index out of bounds";
	#endif
	if (index == m_count-1)
	{
		--m_count;
		return;
	}
	--m_count;
	for (unsigned i = index;i < m_count;++i)
		m_data[i] = m_data[i+1];
}

template <typename T>
void List<T>::removeTail(const uint32_t count) XSENS_LIST_THROW
{
	#ifdef _XSENS_LIST_RANGE_CHECKS
		if (count > m_count)
			throw "List.removeTail: list size less than remove count";
	#endif
	if (m_count > count)
	{
		m_count -= count;
		return;
	}
	m_count = 0;
}

template <typename T>
void List<T>::deleteAndRemoveTail(const uint32_t count) XSENS_LIST_THROW
{
	#ifdef _XSENS_LIST_RANGE_CHECKS
		if (count > m_count)
			throw "List.deleteAndRemoveTail: list size less than remove count";
	#endif
	if (m_count > count)
	{
		for (unsigned i = 0;i < count;++i)
			delete m_data[--m_count];
		return;
	}
	deleteAndClear();
}

template <typename T>
void List<T>::freeAndRemoveTail(const uint32_t count) XSENS_LIST_THROW
{
	#ifdef _XSENS_LIST_RANGE_CHECKS
		if (count > m_count)
			throw "List.freeAndRemoveTail: list size less than remove count";
	#endif
	if (m_count > count)
	{
		for (unsigned i = 0;i < count;++i)
			free(m_data[--m_count]);
		return;
	}
	freeAndClear();
}

template <typename T>
uint32_t List<T>::removeDuplicateEntries(void)
{
	uint32_t removed = 0;
	for (uint32_t i=0;i < m_count; ++i)
	{
		for (uint32_t j=i+1;j < m_count; ++j)
		{
			if (m_data[i] == m_data[j])
			{
				remove(j);
				++removed;
				--j;
			}
		}
	}
	return removed;
}

template <typename T>
uint32_t List<T>::removeDuplicateEntriesDeref(void)
{
	uint32_t removed = 0;
	for (uint32_t i=0;i < m_count; ++i)
	{
		for (uint32_t j=i+1;j < m_count; ++j)
		{
			if (*(m_data[i]) == *(m_data[j]))
			{
				remove(j);
				++removed;
				--j;
			}
		}
	}
	return removed;
}

template <typename T>
void List<T>::deleteAndRemove(const uint32_t index) XSENS_LIST_THROW
{
	#ifdef _XSENS_LIST_RANGE_CHECKS
		if (index >= m_count)
			throw "List.deleteAndRemove: index out of bounds";
	#endif
	delete m_data[index];
	if (index == m_count-1)
	{
		--m_count;
		return;
	}
	--m_count;
	for (unsigned i = index;i < m_count;++i)
		m_data[i] = m_data[i+1];
}

template <typename T>
void List<T>::freeAndRemove(const uint32_t index) XSENS_LIST_THROW
{
	#ifdef _XSENS_LIST_RANGE_CHECKS
		if (index >= m_count)
			throw "List.freeAndRemove: index out of bounds";
	#endif
	free(m_data[index]);
	if (index == m_count-1)
	{
		--m_count;
		return;
	}
	--m_count;
	for (unsigned i = index;i < m_count;++i)
		m_data[i] = m_data[i+1];
}

template <typename T>
template <typename TB>
uint32_t List<T>::find(const TB& item) const
{
	for (uint32_t i=0;i<m_count;++i)
		if (((const T*)m_data)[i] == item)
			return i;
	return XSENS_LIST_NOTFOUND;
}

template <typename T>
uint32_t List<T>::find(const T item, InequalityFunction fnc) const
{
	for (uint32_t i=0;i<m_count;++i)
		if (!fnc(m_data[i],item))
			return i;
	return XSENS_LIST_NOTFOUND;
}

template <typename T>
template <typename TB>
uint32_t List<T>::findDeref(const TB& item) const
{
	for (uint32_t i=0;i<m_count;++i)
		if (*(m_data[i]) == item)
			return i;
	return XSENS_LIST_NOTFOUND;
}

template <typename T>
template <typename TB>
uint32_t List<T>::findSorted(const TB& item) const
{
	if (m_count < CMT_LIST_LINEAR_SEARCH_TRESHOLD)			// for small lists, it is faster to simply walk the list
		return find(item);

	uint32_t x = m_count;
	uint32_t n = 1;
	uint32_t i;

	while(x >= n)
	{
		i = (x + n) >> 1;

		if (m_data[i-1] == item)
			return i-1;
		if (m_data[i-1] < item)
			n = i+1;
		else
			x = i-1;
	}
	return XSENS_LIST_NOTFOUND;
}

template <typename T>
template <typename TB>
uint32_t List<T>::findSortedDeref(const TB& item) const
{
	if (m_count < CMT_LIST_LINEAR_SEARCH_TRESHOLD)			// for small lists, it is faster to simply walk the list
		return findDeref(item);

	uint32_t x = m_count;
	uint32_t n = 1;
	uint32_t i;

	while(x >= n)
	{
		i = (x + n) >> 1;

		if (*(m_data[i-1]) == item)
			return i-1;
		if (*(m_data[i-1]) < item)
			n = i+1;
		else
			x = i-1;
	}
	return XSENS_LIST_NOTFOUND;
}

template <typename T>
uint32_t List<T>::insertSorted(const T& item)
{
	uint32_t i;
	if (m_count < CMT_LIST_LINEAR_SEARCH_TRESHOLD)
	{
		for (i=0;i<m_count;++i)
			if (item < m_data[i])
			{
				insert(item,i);
				return i;
			}
		append(item);
		return m_count-1;
	}
	else
	{
		uint32_t x = m_count;
		uint32_t n = 1;

		while(x >= n)
		{
			i = (x + n) >> 1;

			if (m_data[i-1] == item)
			{
				insert(item,i-1);
				return i-1;
			}
			if (m_data[i-1] < item)
				n = i+1;
			else
				x = i-1;
		}
		insert(item,n-1);
		return n-1;
	}
}

template <typename T>
uint32_t List<T>::insertSortedDeref(const T& item)
{
	uint32_t i;
	if (m_count < CMT_LIST_LINEAR_SEARCH_TRESHOLD)
	{
		for (i=0;i<m_count;++i)
			if (*item < *m_data[i])
			{
				insert(item,i);
				return i;
			}
		append(item);
		return m_count-1;
	}
	else
	{
		uint32_t x = m_count;
		uint32_t n = 1;

		while(x >= n)
		{
			i = (x + n) >> 1;

			if (*(m_data[i-1]) == *item)
			{
				insert(item,i-1);
				return i-1;
			}
			if (*(m_data[i-1]) < *item)
				n = i+1;
			else
				x = i-1;
		}
		insert(item,n-1);
		return n-1;
	}
}

template <typename T>
template <typename TB>
uint32_t List<T>::insertSortedCopy(const TB& item)
{
	uint32_t i;
	if (m_count < CMT_LIST_LINEAR_SEARCH_TRESHOLD)
	{
		for (i=0;i<m_count;++i)
			if (item < m_data[i])
			{
				insertCopy<TB>(item,i);
				return i;
			}
		append(item);
		return m_count-1;
	}
	else
	{
		uint32_t x = m_count;
		uint32_t n = 1;

		while(x >= n)
		{
			i = (x + n) >> 1;

			if (m_data[i-1] == item)
			{
				insertCopy<TB>(item,i-1);
				return i-1;
			}
			if (m_data[i-1] < item)
				n = i+1;
			else
				x = i-1;
		}
		insertCopy<TB>(item,n-1);
		return n-1;
	}
}

template <typename T>
void List<T>::deleteItemsOnDestroy(void)
{
	if (m_jcf != NULL)
	{
		m_jcf->disable();
		delete m_jcf;
	}
	m_jcf = new JanitorClassFunc<List<T>, void>(*this,&List<T>::deleteAndClear);
}

template <typename T>
void List<T>::freeItemsOnDestroy(void)
{
	if (m_jcf != NULL)
	{
		m_jcf->disable();
		delete m_jcf;
	}
	m_jcf = new JanitorClassFunc<List<T>, void>(*this,&List<T>::freeAndClear);
}

template <typename T>
template <typename TB>
void List<T>::isDeepCopyOf(const List<T>& source)
{
	m_count = 0;
	if (m_max < source.m_count)
		resize(source.m_count);
	m_count = source.m_count;
	for (uint32_t i = 0;i<m_count;++i)
		m_data[i] = new TB(*source.m_data[i]);
}

template <typename T>
void List<T>::isShallowCopyOf(const List<T>& x)
{
	m_count = 0;
	if (m_max < x.m_count)
		resize(x.m_count);
	m_count = x.m_count;
	for (uint32_t i = 0;i<m_count;++i)
		m_data[i] = x.m_data[i];
}

template <typename T>
void List<T>::swap(const uint32_t i, const uint32_t j) XSENS_LIST_THROW
{
	#ifdef _XSENS_LIST_RANGE_CHECKS
		if (i >= m_count || j >= m_count)
			throw "List.swap: index out of bounds";
	#endif
	T tmp = m_data[i];
	m_data[i] = m_data[j];
	m_data[j] = tmp;
}

template <typename T>
void List<T>::reverse(void)
{
	uint32_t half = m_count / 2;
	for (uint32_t i = 0, end=m_count-1; i < half; ++i,--end)
	{
		T tmp = m_data[i];
		m_data[i] = m_data[end];
		m_data[end] = tmp;
	}
}

} // end of xsens namespace

#endif	// _XSENS_LIST_H_2006_06_08

#ifndef _SCANPORTS_H_2006_06_09
#define _SCANPORTS_H_2006_06_09


namespace xsens {

/*! \brief Scan COM ports for connected Xsens devices.

	The cmtScanPorts function will scan registered Xsens USB converters and serial COM ports
	for connected Xsens devices. If the baudrate parameter is 0 (default), it will try to
	connect at all supported baud rates, starting with the most common 115k2, 460k8 and 
	58k6. If the baudrate parameter is non-zero, only the specified baudrate is tried.
	Any detected devices are returned in the ports list, which is sorted by port nr.
	
*/
bool cmtScanPorts(List<CmtPortInfo>& ports, uint32_t baudrate = 0, uint32_t singleScanTimeout = 1000, uint32_t scanTries = 1);

/*! \brief Scan a single COM port for connected Xsens devices.

	The cmtScanPort function will scan a single port for connected Xsens devices. If the
	baudrate parameter is 0 (default), it will try to connect at all supported baud 
	rates, starting with the most common 115k2, 460k8 and 58k6. If the baudrate parameter
	is non-zero, only the specified baud rate is tried. Any detected devices are returned
	in the portInfo parameter.
	
*/
bool cmtScanPort(CmtPortInfo& portInfo, uint32_t baudrate = 0, uint32_t singleScanTimeout = 1000, uint32_t scanTries = 1);

//! Set to true from another thread to abort any scan currently in progress.
extern bool abortScan;

} // end of xsens namespace

#endif	// _SCANPORTS_H_2006_06_09
#endif	// _CMT_LIB_H_2006_08_29 or _CMT_DLL_H_2007_01_23

