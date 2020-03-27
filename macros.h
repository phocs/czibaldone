/**
 *   Copyright (C) 2020  Alessio Volpe <alessio.volpe@aol.com>.
 *
 *   This library is free software; you can redistribute it and/or modify it
 *   under the terms of the GNU Lesser General Public License as published by
 *   the Free Software Foundation; either version 2.1 of the License, or (at
 *   your option) any later version.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   along with this library; if not, write to the Free Software Foundation,
 *   Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
 */

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>

#define __FILENAME__ (basename(__FILE__))

#define _VA_OPT_SELECTOR(_1, _2, _3, ...) _3
#define _VA_OPT_SUPPORT(...) _VA_OPT_SELECTOR(__VA_OPT__(,) , 1, 0, unused)
#define VA_OPT_SUPPORT _VA_OPT_SUPPORT(unused)

#if VA_OPT_SUPPORT
// #	pragma message("VA_OPT_SUPPORT 1")
#	define __opt_args_resolve(unused, ...) __VA_OPT__(,) __VA_ARGS__
#   define __opt_args(...) __opt_args_resolve(__VA_ARGS__)
#else
#	pragma message("VA_OPT_SUPPORT 0")
#	define __opt_args_selector_64(											\
		_1, _2, _3, _4, _5, _6, _7, _8, _9,_10, _11,_12,_13,_14,_15,_16,	\
		_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,	\
		_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,	\
		_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63,_64,	\
		...) _64
#	define __opt_args_suffix(...) 											\
		__opt_args_selector_64(__VA_ARGS__,                    				\
			_many,_many,_many,_many,_many,_many,_many,_many,_many,_many,	\
			_many,_many,_many,_many,_many,_many,_many,_many,_many,_many,	\
			_many,_many,_many,_many,_many,_many,_many,_many,_many,_many,	\
			_many,_many,_many,_many,_many,_many,_many,_many,_many,_many,	\
			_many,_many,_many,_many,_many,_many,_many,_many,_many,_many,	\
			_many,_many,_many,_many,_many,_many,_many,_many,_many,_many,	\
			_many,_many, _none, unused)
#	define __opt_args_none(unused)
#	define __opt_args_many(unused, ...) , __VA_ARGS__
#	define __opt_args_select(suffix, ...) __opt_args##suffix(__VA_ARGS__)
#	define __opt_args_resolve(suffix, ...) \
	__opt_args_select(suffix, __VA_ARGS__)
#	define __opt_args(...)	\
		__opt_args_resolve( __opt_args_suffix(__VA_ARGS__), __VA_ARGS__)
#endif

#define __opt_fmt(fmt, ...) fmt

#define ANSI_COLOR_RED 		"\033[1;31m"
#define ANSI_COLOR_CYAN 	"\033[0;36m"
#define ANSI_COLOR_BLACK 	"\033[0m"
#define ANSI_COLOR_YELLOW 	"\x1b[33m"

#define _DEBUG_EXFMT(...) 									\
	ANSI_COLOR_CYAN  "%s:%d: debug in %s\n- " 				\
	ANSI_COLOR_BLACK __opt_fmt(__VA_ARGS__, unused)  "\n"

#define _DEBUG_EXARGS(...) \
	__FILENAME__, __LINE__, __func__ __opt_args(__VA_ARGS__)

#define _WARNING_EXFMT(...) 								\
	ANSI_COLOR_YELLOW "%s:%d: warning in %s\n- " 			\
	ANSI_COLOR_BLACK __opt_fmt(__VA_ARGS__, unused)  "\n"

#define _ERROR_EXFMT(...) 									\
	ANSI_COLOR_RED   "%s:%d: error \"%s\" in %s\n- " 		\
	ANSI_COLOR_BLACK __opt_fmt(__VA_ARGS__, unused)  "\n"

#define _ERROR_EXARGS(...)	\
	__FILENAME__, __LINE__, strerror(errno), __func__  __opt_args(__VA_ARGS__)

#define debugf(/*fmt,*/...)	\
	printf(_DEBUG_EXFMT(__VA_ARGS__), _DEBUG_EXARGS(__VA_ARGS__))

#define warningf(/*fmt,*/...)	\
	printf(_WARNING_EXFMT(__VA_ARGS__), _DEBUG_EXARGS(__VA_ARGS__))

#define errorf(/*fmt,*/...)	\
	printf(_ERROR_EXFMT(__VA_ARGS__), _ERROR_EXARGS(__VA_ARGS__))
