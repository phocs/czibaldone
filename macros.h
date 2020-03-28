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

 #include <errno.h>
 #include <string.h>
 #include <libgen.h>

 #define __SUFFIX_JOIN(prefix, suffix)   prefix##suffix
 #define __FILENAME__ (basename(__FILE__))

 #ifdef NDEBUG
 #	define debugf(/*fmt,*/...)
 #	define warningf(/*fmt,*/...)
 #	define errorf(/*fmt,*/...)
 #	define void_tracef()
 #	define tracef(...)
 #else /* NDEBUG */
 #	ifdef __APPLE__
 #	pragma GCC diagnostic push
 #	pragma GCC diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
 #	endif
 #	include <stdio.h>
 #	define __VA_ARGS_FST(_1, ...)  _1                // (a,b,c) => a
 #	define __VA_ARGS_POP(del, ...) __VA_ARGS__       // (a,b,c) => b,c
 #	define __VA_ARGS_POP_L(del, ...) (__VA_ARGS__)   // (a,b,c) => (b,c)

 #	define __VA_ARGS_SELECTOR64(                                          \
       	_1, _2, _3, _4, _5, _6, _7, _8, _9,_10,_11,_12,_13,_14,_15,_16,   \
      	_17,_18,_19,_20,_21,_22,_23,_24,_25,_26,_27,_28,_29,_30,_31,_32,   \
      	_33,_34,_35,_36,_37,_38,_39,_40,_41,_42,_43,_44,_45,_46,_47,_48,   \
      	_49,_50,_51,_52,_53,_54,_55,_56,_57,_58,_59,_60,_61,_62,_63, _N,   \
      	...) _N

 #	define __VA_ARGS_SEQ64()                               	\
     	63,62,61,60,59,58,57,56,55,54,53,52,51,50,49,48,    \
     	47,46,45,44,43,42,41,40,39,38,37,36,35,34,33,32,    \
     	31,30,29,28,27,26,25,24,23,22,21,20,19,18,17,16,    \
     	15,14,13,12,11,10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0

 #	define __VA_ARGS_NARG64_(...) __VA_ARGS_SELECTOR64(__VA_ARGS__)
 #	define __VA_ARGS_NARG64(...) \
 	__VA_ARGS_NARG64_(__VA_ARGS__, __VA_ARGS_SEQ64())

 #	define __f(f, i, x) f(i, x)

 #	define __VA_ARGS_RECUR_0(...)
 #	define __VA_ARGS_RECUR_1(f,x,va)  __f(f, __VA_ARGS_FST va, x##_END)  __VA_ARGS_RECUR_0(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_2(f,x,va)  __f(f, __VA_ARGS_FST va, x)  __VA_ARGS_RECUR_1(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_3(f,x,va)  __f(f, __VA_ARGS_FST va, x)  __VA_ARGS_RECUR_2(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_4(f,x,va)  __f(f, __VA_ARGS_FST va, x)  __VA_ARGS_RECUR_3(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_5(f,x,va)  __f(f, __VA_ARGS_FST va, x)  __VA_ARGS_RECUR_4(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_6(f,x,va)  __f(f, __VA_ARGS_FST va, x)  __VA_ARGS_RECUR_5(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_7(f,x,va)  __f(f, __VA_ARGS_FST va, x)  __VA_ARGS_RECUR_6(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_8(f,x,va)  __f(f, __VA_ARGS_FST va, x)  __VA_ARGS_RECUR_7(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_9(f,x,va)  __f(f, __VA_ARGS_FST va, x)  __VA_ARGS_RECUR_8(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_10(f,x,va) __f(f, __VA_ARGS_FST va, x)  __VA_ARGS_RECUR_9(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_11(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_10(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_12(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_11(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_13(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_12(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_14(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_13(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_15(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_14(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_16(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_15(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_17(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_16(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_18(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_17(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_19(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_18(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_20(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_19(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_21(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_20(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_22(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_21(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_23(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_22(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_24(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_23(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_25(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_24(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_26(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_25(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_27(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_26(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_28(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_27(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_29(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_28(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_30(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_29(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_31(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_30(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_32(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_31(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_33(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_32(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_34(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_33(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_35(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_34(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_36(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_35(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_37(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_36(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_38(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_37(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_39(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_38(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_40(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_39(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_41(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_40(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_42(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_41(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_43(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_42(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_44(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_43(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_45(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_44(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_46(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_45(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_47(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_46(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_48(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_47(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_49(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_48(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_50(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_49(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_51(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_50(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_52(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_51(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_53(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_52(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_54(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_53(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_55(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_54(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_56(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_55(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_57(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_56(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_58(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_57(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_59(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_58(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_60(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_59(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_61(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_60(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_62(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_61(f, x, __VA_ARGS_POP_L va)
 #	define __VA_ARGS_RECUR_63(f,x,va) __f(f, __VA_ARGS_FST va, x) __VA_ARGS_RECUR_62(f, x, __VA_ARGS_POP_L va)

 #	define __VA_ARGS_RECUR_SELECTOR(recur, num) __SUFFIX_JOIN(recur, num)
 /*
  * for each i in __VA_ARGS__ do f(i, x)
  * where x is some user const parameter passed to f for each i
  * at last i: x is x##_END for end detection
 */
 #	define 	__VA_ARGS_RECURSIVE_EXEC(f, x, ...)                                     \
     	__VA_ARGS_RECUR_SELECTOR(__VA_ARGS_RECUR_, __VA_ARGS_NARG64(__VA_ARGS__))   \
     	(f, x, (__VA_ARGS__))


 #	define _VA_OPT_SELECTOR(_1, _2, _3, ...) _3
 #	define _VA_OPT_SUPPORT(...) _VA_OPT_SELECTOR(__VA_OPT__(,) , 1, 0, unused)
 #	define VA_OPT_SUPPORT _VA_OPT_SUPPORT(unused)
 #	if 0 //VA_OPT_SUPPORT
 		/* One or zero -> return none (e.g. fmt, args => many) */
 #		define __VA_OPT(unused, ...) __VA_OPT__(,) __VA_ARGS__
 #	else
 #		define __VA_OPT_SEQ64()                                \
     		MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY, \
     		MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY, \
     		MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY, \
     		MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY, \
     		MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY, \
     		MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY,MANY, \
     		MANY,MANY, NONE, unused

 #		define __VA_OPT_DETECT(...) __VA_ARGS_SELECTOR64(__VA_ARGS__)
 #		define __VA_OPT_MANY_DETECT(...) \
 			__VA_OPT_DETECT(__VA_ARGS__, __VA_OPT_SEQ64())


 #		define __VA_OPT_NONE(unused)
 #		define __VA_OPT_MANY(unused, ...) , __VA_ARGS__
 #		define __VA_OPT_SELECTOR(suffix) __SUFFIX_JOIN(__VA_OPT_, suffix)
 		/* One or zero -> return none (e.g. fmt, args => many) */
 #		define __VA_OPT(...) \
 			__VA_OPT_SELECTOR( __VA_OPT_MANY_DETECT(__VA_ARGS__))(__VA_ARGS__)
 #	endif

 #	define _FUNC_PARAM_NEXT() 	,
 #	define _FUNC_PARAM_NEXT_END()
 #	define _FUNC_PARAM_FORMAT(param, next) \
 	#param, (unsigned long long) param next()

 #	define _FUNC_PARAM_PARSER(...) 									\
     	__VA_ARGS_RECURSIVE_EXEC									\
 			(_FUNC_PARAM_FORMAT, _FUNC_PARAM_NEXT, __VA_ARGS__)

 #	define _FUNC_PARAM_FMT_NEXT()	"%s: 0x%llX, "
 #	define _FUNC_PARAM_FMT_NEXT_END() "%s: 0x%llX"
 #	define _FUNC_PARAM_FMT_FORMAT(unused, next) next()

 #	define _FUNC_PARAM_FMT_PARSER(...) 									\
     	__VA_ARGS_RECURSIVE_EXEC										\
 			(_FUNC_PARAM_FMT_FORMAT, _FUNC_PARAM_FMT_NEXT, __VA_ARGS__)

 #	define ANSI_COLOR_RED 		"\033[1;31m"
 #	define ANSI_COLOR_CYAN 		"\033[0;36m"
 #	define ANSI_COLOR_BLACK 	"\033[0m"
 #	define ANSI_COLOR_GREEN 	"\x1b[32m"
 #	define ANSI_COLOR_YELLOW 	"\x1b[33m"

 #	define _DEBUG_EXFMT(/*fmt,*/...) 								\
 		ANSI_COLOR_CYAN  "%s:%d: debug in %s\n- " 					\
 		ANSI_COLOR_BLACK __VA_ARGS_FST(__VA_ARGS__, unused)  "\n"
 #	define _DEBUG_EXARGS(/*fmt,*/...) 								\
 		__FILENAME__, __LINE__, __func__ __VA_OPT(__VA_ARGS__)

 #	define _WARNING_EXFMT(/*fmt,*/...)  							\
 		ANSI_COLOR_YELLOW "%s:%d: warning in %s\n- " 				\
 		ANSI_COLOR_BLACK __VA_ARGS_FST(__VA_ARGS__, unused)  "\n"

 #	define _ERROR_EXFMT(/*fmt,*/...) 								\
 		ANSI_COLOR_RED   "%s:%d: error \"%s\" in %s\n- " 			\
 		ANSI_COLOR_BLACK __VA_ARGS_FST(__VA_ARGS__, unused)  "\n"
 #	define _ERROR_EXARGS(/*fmt,*/...)										\
 		__FILENAME__, __LINE__, (errno != 0)? strerror(errno):"internal", 	\
 		__func__  __VA_OPT(__VA_ARGS__)

 #	define _TRACE_VOID_EXFMT() \
 		ANSI_COLOR_GREEN "%s:%d: trace-> %s(void)"	ANSI_COLOR_BLACK "\n"
 #	define _TRACE_VOID_EXARGS() __FILENAME__, __LINE__, __func__

 #	define _TRACE_FUNC_EXFMT(...) 										\
 		ANSI_COLOR_GREEN "%s:%d: trace-> %s("							\
 		_FUNC_PARAM_FMT_PARSER(__VA_ARGS__)	")" ANSI_COLOR_BLACK "\n"
 #	define _TRACE_FUNC_EXARGS(...)											\
 		__FILENAME__, __LINE__, __func__, _FUNC_PARAM_PARSER(__VA_ARGS__)

 #	define debugf(/*fmt,*/...)	\
 		printf(_DEBUG_EXFMT(__VA_ARGS__), _DEBUG_EXARGS(__VA_ARGS__))

 #	define warningf(/*fmt,*/...)	\
 		printf(_WARNING_EXFMT(__VA_ARGS__), _DEBUG_EXARGS(__VA_ARGS__))

 #	define errorf(/*fmt,*/...)	\
 		printf(_ERROR_EXFMT(__VA_ARGS__), _ERROR_EXARGS(__VA_ARGS__))

 #	define void_tracef()	\
 		printf(_TRACE_VOID_EXFMT(), _TRACE_VOID_EXARGS())

 #	define tracef(...)	\
 		printf(_TRACE_FUNC_EXFMT(__VA_ARGS__), _TRACE_FUNC_EXARGS(__VA_ARGS__))
 #endif /* NDEBUG */

 #define __asser_if(exp) 		if(__builtin_expect(!(exp), 0))
 #define __asser_errorf(exp) 	errorf("(%s) fail", #exp)
 #define assert_return(exp, ret) do {		\
 		__asser_if(exp) {					\
 			__asser_errorf(exp);			\
 			return ret;						\
 		}									\
 	} while(0)

 #define assert_return_errno(exp, ret, err) do {		\
 		__asser_if(exp) {							\
 			errno = err;							\
 			__asser_errorf(exp);					\
 			return ret;								\
 		}											\
 	} while(0)
