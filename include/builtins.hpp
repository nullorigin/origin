//===--- Builtins.def - Builtin function info database ----------*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file defines the standard builtin function database.  Users of this file
// must define the BUILTIN macro to make use of this information.
//
//===----------------------------------------------------------------------===//

// FIXME: This should really be a .td file, but that requires modifying tblgen.
// Perhaps tblgen should have plugins.

// The first value provided to the macro specifies the function name of the
// builtin, and results in a clang::builtin::BIXX enum value for XX.

// The second value provided to the macro specifies the type of the function
// (result value, then each argument) as follows:
//  v -> void
//  b -> boolean
//  c -> char
//  s -> short
//  i -> int
//  h -> half (__fp16, OpenCL)
//  x -> half (_Float16)
//  y -> half (__bf16)
//  f -> float
//  d -> double
//  z -> size_t
//  w -> wchar_t
//  F -> constant CFString
//  G -> id
//  H -> SEL
//  M -> struct objc_super
//  a -> __builtin_va_list
//  A -> "reference" to __builtin_va_list
//  V -> Vector, followed by the number of elements and the base type.
//  q -> Scalable vector, followed by the number of elements and the base type.
//  Q -> target builtin type, followed by a character to distinguish the builtin
//  type
//    Qa -> AArch64 svcount_t builtin type.
//  E -> ext_vector, followed by the number of elements and the base type.
//  X -> _Complex, followed by the base type.
//  Y -> ptrdiff_t
//  P -> FILE
//  J -> jmp_buf
//  SJ -> sigjmp_buf
//  K -> ucontext_t
//  p -> pid_t
//  . -> "...".  This may only occur at the end of the function list.
//
// Types may be prefixed with the following modifiers:
//  L   -> long (e.g. Li for 'long int', Ld for 'long double')
//  LL  -> long long (e.g. LLi for 'long long int', LLd for __float128)
//  LLL -> __int128_t (e.g. LLLi)
//  Z   -> int32_t (require a native 32-bit integer type on the target)
//  W   -> int64_t (require a native 64-bit integer type on the target)
//  N   -> 'int' size if target is LP64, 'L' otherwise.
//  O   -> long for OpenCL targets, long long otherwise.
//  S   -> signed
//  U   -> unsigned
//  I   -> Required to constant fold to an integer constant expression.
//
// Types may be postfixed with the following modifiers:
// * -> pointer (optionally followed by an address space number, if no address
//               space is specified than any address space will be accepted)
// & -> reference (optionally followed by an address space number)
// C -> const
// D -> volatile
// R -> restrict

// The third value provided to the macro specifies information about attributes
// of the function.  These must be kept in sync with the predicates in the
// Builtin::Context class.  Currently we have:
//  n -> nothrow
//  r -> noreturn
//  U -> pure
//  c -> const
//  t -> signature is meaningless, use custom typechecking
//  T -> type is not important to semantic analysis and codegen; recognize as
//       builtin even if type doesn't match signature, and don't warn if we
//       can't be sure the type is right
//  F -> this is a libc/libm function with a '__builtin_' prefix added.
//  f -> this is a libc/libm function without a '__builtin_' prefix, or with
//       'z', a C++ standard library function in namespace std::. This builtin
//       is disableable by '-fno-builtin-foo' / '-fno-builtin-std-foo'.
//  h -> this function requires a specific header or an explicit declaration.
//  i -> this is a runtime library implemented function without the
//       '__builtin_' prefix. It will be implemented in compiler-rt or libgcc.
//  p:N: -> this is a printf-like function whose Nth argument is the format
//          string.
//  P:N: -> similar to the p:N: attribute, but the function is like vprintf
//          in that it accepts its arguments as a va_list rather than
//          through an ellipsis
//  s:N: -> this is a scanf-like function whose Nth argument is the format
//          string.
//  S:N: -> similar to the s:N: attribute, but the function is like vscanf
//          in that it accepts its arguments as a va_list rather than
//          through an ellipsis
//  e -> const, but only when -fno-math-errno and FP exceptions are ignored
//  g -> const when FP exceptions are ignored
//  j -> returns_twice (like setjmp)
//  u -> arguments are not evaluated for their side-effects
//  V:N: -> requires vectors of at least N bits to be legal
//  C<N,M_0,...,M_k> -> callback behavior: argument N is called with argument
//                      M_0, ..., M_k as payload
//  z -> this is a function in (possibly-versioned) namespace std
//  E -> this function can be constant evaluated by Clang frontend
//  FIXME: gcc has nonnull

#include <cstdarg>
#include <cstring>

#if defined(BUILTIN) && !defined(LIBBUILTIN)
#define LIBBUILTIN(ID, TYPE, ATTRS, HEADER, BUILTIN_LANG)                      \
  BUILTIN(ID, TYPE, ATTRS)
#endif

#if defined(BUILTIN) && !defined(LANGBUILTIN)
#define LANGBUILTIN(ID, TYPE, ATTRS, BUILTIN_LANG) BUILTIN(ID, TYPE, ATTRS)
#endif
/*template<typename T>
class BUILTIN
{
    char* TYPES;
    char* ATTRS;
    BUILTIN<T>(char* types, char* attrs)
    {
        TYPES = types;
        ATTRS = attrs;
    }
    void print(char* types, char* attrs, va_list args...)
    {
        std::stringstream ss;
        ss << "BUILTIN(";
        ss << types;
        ss << ", ";
        ss << attrs;
        ss << ")";
        for (int i = 0; types[i] != 0; i++)
        {
            char type = types[i];
            T val = va_arg(args, T);
            switch (val)
            {
            case 'v':
            {
                ss << "void";
                break;
            }
            case 'b':
            {
                ss << "bool";
                break;
            }
            case 'c':
            {
                ss << "char";
                break;
            }
            case 's':
            {
                ss << "short";
                break;
            }
            case 'i':
            {
                ss << "int";
                break;
            }
            case 'h':
            {
                ss << "half";
                break;
            }
            case 'x':
            {
                ss << "half";
                break;
            }
            case 'y':
            {
                ss << "half";
                break;
            }
            case 'f':
            {
                ss << "float";
                break;
            }
            case 'd':
            {
                ss << "double";
                break;
            }
            case 'z':
            {
                ss << "size_t";
                break;
            }
            case 'w':
            {
                ss << "wchar_t";
                break;
            }
            case 'a':
            {
                ss << "__builtin_va_list";
                break;
            }
            case 'Y':
            {
                ss << "ptrdiff_t";
                break;
            }
            case 'P':
            {
                ss << "FILE";
                break;
            }
            case 'J':
            {
                ss << "jmp_buf";
                break;
            }
            case 'S':
            {
                ss << "sigjmp_buf";
                break;
            }
            case 'K':
            {
                ss << "ucontext_t";
                break;
            }
            case 'p':
            {
                ss << "pid_t";
                break;
            }
            case '.':
            {
                ss << "...";
                break;
            }
            case '*':
            {
                ss << "*";
                break;
            }
            }
            TYPES = types;
            ATTRS = attrs;
        }
    }
};
template<typename...>
using function = std::function<std::string (*)(std::string...)>;
using string = std::string;
#define BUILTIN(ID, TYPE, ATTRS)                                        \
    auto s##ID(char* attr, char* type, char* args...)->std::string      \
    {                                                                   \
        std::string ret = std::string(TYPE) + " " + std::string(ATTRS); \
A = __builtin_va_list B = null C = const D = volatile E = ext_vector F =
constant CFString G = id H = SEL I = constexpr integer J = jmp_buf R = restrict
const string rep[128] = {
    "__builtin_va_list",
    "bool",
    "char",
    "short",
    "int",
    "half",
    "float",
    "double",
    "size_t",
    "wchar_t",
    "__builtin_va_list",
    "ptrdiff_t",
    "FILE",
    "jmp_buf",
    "sigjmp_buf",
    "ucontext_t",
    "pid_t",
    "",
};
for (int i = 0; type[i] != 0; i++)
    ret.replace(ret.find(type[i], 0), 1, rep[types[i]]);
return ret;
} */
#define BUILTIN(ID, TYPE, ATTRS)
#define LIBBUILTIN(ID, TYPE, ATTRS, HEADER, BUILTIN_LANG)
#define LANGBUILTIN(ID, TYPE, ATTRS, LANG)
// Standard libc/libm functions:
BUILTIN(__builtin_atan2, "ddd", "Fne")
BUILTIN(__builtin_atan2f, "fff", "Fne")
BUILTIN(__builtin_atan2l, "LdLdLd", "Fne")
BUILTIN(__builtin_atan2f128, "LLdLLdLLd", "Fne")
BUILTIN(__builtin_abs, "ii", "ncF")
BUILTIN(__builtin_copysign, "ddd", "ncFE")
BUILTIN(__builtin_copysignf, "fff", "ncFE")
BUILTIN(__builtin_copysignf16, "hhh", "ncF")
BUILTIN(__builtin_copysignl, "LdLdLd", "ncFE")
BUILTIN(__builtin_copysignf128, "LLdLLdLLd", "ncFE")
BUILTIN(__builtin_fabs, "dd", "ncFE")
BUILTIN(__builtin_fabsf, "ff", "ncFE")
BUILTIN(__builtin_fabsl, "LdLd", "ncFE")
BUILTIN(__builtin_fabsf16, "hh", "ncF")
BUILTIN(__builtin_fabsf128, "LLdLLd", "ncFE")
BUILTIN(__builtin_fmod, "ddd", "Fne")
BUILTIN(__builtin_fmodf, "fff", "Fne")
BUILTIN(__builtin_fmodf16, "hhh", "Fne")
BUILTIN(__builtin_fmodl, "LdLdLd", "Fne")
BUILTIN(__builtin_fmodf128, "LLdLLdLLd", "Fne")
BUILTIN(__builtin_frexp, "ddi*", "Fn")
BUILTIN(__builtin_frexpf, "ffi*", "Fn")
BUILTIN(__builtin_frexpl, "LdLdi*", "Fn")
BUILTIN(__builtin_frexpf128, "LLdLLdi*", "Fn")
BUILTIN(__builtin_frexpf16, "hhi*", "Fn")
BUILTIN(__builtin_huge_val, "d", "ncE")
BUILTIN(__builtin_huge_valf, "f", "ncE")
BUILTIN(__builtin_huge_vall, "Ld", "ncE")
BUILTIN(__builtin_huge_valf16, "x", "ncE")
BUILTIN(__builtin_huge_valf128, "LLd", "ncE")
BUILTIN(__builtin_inf, "d", "ncE")
BUILTIN(__builtin_inff, "f", "ncE")
BUILTIN(__builtin_infl, "Ld", "ncE")
BUILTIN(__builtin_inff16, "x", "ncE")
BUILTIN(__builtin_inff128, "LLd", "ncE")
BUILTIN(__builtin_labs, "LiLi", "Fnc")
BUILTIN(__builtin_llabs, "LLiLLi", "Fnc")
BUILTIN(__builtin_ldexp, "ddi", "Fne")
BUILTIN(__builtin_ldexpf, "ffi", "Fne")
BUILTIN(__builtin_ldexpl, "LdLdi", "Fne")
BUILTIN(__builtin_ldexpf128, "LLdLLdi", "Fne")
BUILTIN(__builtin_ldexpf16, "hhi", "Fne")
BUILTIN(__builtin_modf, "ddd*", "Fn")
BUILTIN(__builtin_modff, "fff*", "Fn")
BUILTIN(__builtin_modfl, "LdLdLd*", "Fn")
BUILTIN(__builtin_modff128, "LLdLLdLLd*", "Fn")
BUILTIN(__builtin_nan, "dcC*", "FnUE")
BUILTIN(__builtin_nanf, "fcC*", "FnUE")
BUILTIN(__builtin_nanl, "LdcC*", "FnUE")
BUILTIN(__builtin_nanf16, "xcC*", "FnUE")
BUILTIN(__builtin_nanf128, "LLdcC*", "FnUE")
BUILTIN(__builtin_nans, "dcC*", "FnUE")
BUILTIN(__builtin_nansf, "fcC*", "FnUE")
BUILTIN(__builtin_nansl, "LdcC*", "FnUE")
BUILTIN(__builtin_nansf16, "xcC*", "FnUE")
BUILTIN(__builtin_nansf128, "LLdcC*", "FnUE")
BUILTIN(__builtin_powi, "ddi", "Fnc")
BUILTIN(__builtin_powif, "ffi", "Fnc")
BUILTIN(__builtin_powil, "LdLdi", "Fnc")
BUILTIN(__builtin_pow, "ddd", "Fne")
BUILTIN(__builtin_powf, "fff", "Fne")
BUILTIN(__builtin_powf16, "hhh", "Fne")
BUILTIN(__builtin_powl, "LdLdLd", "Fne")
BUILTIN(__builtin_powf128, "LLdLLdLLd", "Fne")

// Standard unary libc/libm functions with double/float/long double variants:
BUILTIN(__builtin_acos, "dd", "Fne")
BUILTIN(__builtin_acosf, "ff", "Fne")
BUILTIN(__builtin_acosl, "LdLd", "Fne")
BUILTIN(__builtin_acosf128, "LLdLLd", "Fne")
BUILTIN(__builtin_acosh, "dd", "Fne")
BUILTIN(__builtin_acoshf, "ff", "Fne")
BUILTIN(__builtin_acoshl, "LdLd", "Fne")
BUILTIN(__builtin_acoshf128, "LLdLLd", "Fne")
BUILTIN(__builtin_asin, "dd", "Fne")
BUILTIN(__builtin_asinf, "ff", "Fne")
BUILTIN(__builtin_asinl, "LdLd", "Fne")
BUILTIN(__builtin_asinf128, "LLdLLd", "Fne")
BUILTIN(__builtin_asinh, "dd", "Fne")
BUILTIN(__builtin_asinhf, "ff", "Fne")
BUILTIN(__builtin_asinhl, "LdLd", "Fne")
BUILTIN(__builtin_asinhf128, "LLdLLd", "Fne")
BUILTIN(__builtin_atan, "dd", "Fne")
BUILTIN(__builtin_atanf, "ff", "Fne")
BUILTIN(__builtin_atanl, "LdLd", "Fne")
BUILTIN(__builtin_atanf128, "LLdLLd", "Fne")
BUILTIN(__builtin_atanh, "dd", "Fne")
BUILTIN(__builtin_atanhf, "ff", "Fne")
BUILTIN(__builtin_atanhl, "LdLd", "Fne")
BUILTIN(__builtin_atanhf128, "LLdLLd", "Fne")
BUILTIN(__builtin_cbrt, "dd", "Fnc")
BUILTIN(__builtin_cbrtf, "ff", "Fnc")
BUILTIN(__builtin_cbrtl, "LdLd", "Fnc")
BUILTIN(__builtin_cbrtf128, "LLdLLd", "Fnc")
BUILTIN(__builtin_ceil, "dd", "Fnc")
BUILTIN(__builtin_ceilf, "ff", "Fnc")
BUILTIN(__builtin_ceilf16, "hh", "Fnc")
BUILTIN(__builtin_ceill, "LdLd", "Fnc")
BUILTIN(__builtin_ceilf128, "LLdLLd", "Fnc")
BUILTIN(__builtin_cos, "dd", "Fne")
BUILTIN(__builtin_cosf, "ff", "Fne")
BUILTIN(__builtin_cosf16, "hh", "Fne")
BUILTIN(__builtin_cosh, "dd", "Fne")
BUILTIN(__builtin_coshf, "ff", "Fne")
BUILTIN(__builtin_coshl, "LdLd", "Fne")
BUILTIN(__builtin_coshf128, "LLdLLd", "Fne")
BUILTIN(__builtin_cosl, "LdLd", "Fne")
BUILTIN(__builtin_cosf128, "LLdLLd", "Fne")
BUILTIN(__builtin_erf, "dd", "Fne")
BUILTIN(__builtin_erff, "ff", "Fne")
BUILTIN(__builtin_erfl, "LdLd", "Fne")
BUILTIN(__builtin_erff128, "LLdLLd", "Fne")
BUILTIN(__builtin_erfc, "dd", "Fne")
BUILTIN(__builtin_erfcf, "ff", "Fne")
BUILTIN(__builtin_erfcl, "LdLd", "Fne")
BUILTIN(__builtin_erfcf128, "LLdLLd", "Fne")
BUILTIN(__builtin_exp, "dd", "Fne")
BUILTIN(__builtin_expf, "ff", "Fne")
BUILTIN(__builtin_expf16, "hh", "Fne")
BUILTIN(__builtin_expl, "LdLd", "Fne")
BUILTIN(__builtin_expf128, "LLdLLd", "Fne")
BUILTIN(__builtin_exp2, "dd", "Fne")
BUILTIN(__builtin_exp2f, "ff", "Fne")
BUILTIN(__builtin_exp2f16, "hh", "Fne")
BUILTIN(__builtin_exp2l, "LdLd", "Fne")
BUILTIN(__builtin_exp2f128, "LLdLLd", "Fne")
BUILTIN(__builtin_exp10, "dd", "Fne")
BUILTIN(__builtin_exp10f, "ff", "Fne")
BUILTIN(__builtin_exp10f16, "hh", "Fne")
BUILTIN(__builtin_exp10l, "LdLd", "Fne")
BUILTIN(__builtin_exp10f128, "LLdLLd", "Fne")
BUILTIN(__builtin_expm1, "dd", "Fne")
BUILTIN(__builtin_expm1f, "ff", "Fne")
BUILTIN(__builtin_expm1l, "LdLd", "Fne")
BUILTIN(__builtin_expm1f128, "LLdLLd", "Fne")
BUILTIN(__builtin_fdim, "ddd", "Fne")
BUILTIN(__builtin_fdimf, "fff", "Fne")
BUILTIN(__builtin_fdiml, "LdLdLd", "Fne")
BUILTIN(__builtin_fdimf128, "LLdLLdLLd", "Fne")
BUILTIN(__builtin_floor, "dd", "Fnc")
BUILTIN(__builtin_floorf, "ff", "Fnc")
BUILTIN(__builtin_floorf16, "hh", "Fnc")
BUILTIN(__builtin_floorl, "LdLd", "Fnc")
BUILTIN(__builtin_floorf128, "LLdLLd", "Fnc")
BUILTIN(__builtin_fma, "dddd", "Fne")
BUILTIN(__builtin_fmaf, "ffff", "Fne")
BUILTIN(__builtin_fmaf16, "hhhh", "Fne")
BUILTIN(__builtin_fmal, "LdLdLdLd", "Fne")
BUILTIN(__builtin_fmaf128, "LLdLLdLLdLLd", "Fne")
BUILTIN(__builtin_fmax, "ddd", "FncE")
BUILTIN(__builtin_fmaxf, "fff", "FncE")
BUILTIN(__builtin_fmaxf16, "hhh", "FncE")
BUILTIN(__builtin_fmaxl, "LdLdLd", "FncE")
BUILTIN(__builtin_fmaxf128, "LLdLLdLLd", "FncE")
BUILTIN(__builtin_fmin, "ddd", "FncE")
BUILTIN(__builtin_fminf, "fff", "FncE")
BUILTIN(__builtin_fminf16, "hhh", "FncE")
BUILTIN(__builtin_fminl, "LdLdLd", "FncE")
BUILTIN(__builtin_fminf128, "LLdLLdLLd", "FncE")
BUILTIN(__builtin_hypot, "ddd", "Fne")
BUILTIN(__builtin_hypotf, "fff", "Fne")
BUILTIN(__builtin_hypotl, "LdLdLd", "Fne")
BUILTIN(__builtin_hypotf128, "LLdLLdLLd", "Fne")
BUILTIN(__builtin_ilogb, "id", "Fne")
BUILTIN(__builtin_ilogbf, "if", "Fne")
BUILTIN(__builtin_ilogbl, "iLd", "Fne")
BUILTIN(__builtin_ilogbf128, "iLLd", "Fne")
BUILTIN(__builtin_lgamma, "dd", "Fn")
BUILTIN(__builtin_lgammaf, "ff", "Fn")
BUILTIN(__builtin_lgammal, "LdLd", "Fn")
BUILTIN(__builtin_lgammaf128, "LLdLLd", "Fn")
BUILTIN(__builtin_llrint, "LLid", "Fne")
BUILTIN(__builtin_llrintf, "LLif", "Fne")
BUILTIN(__builtin_llrintl, "LLiLd", "Fne")
BUILTIN(__builtin_llrintf128, "LLiLLd", "Fne")
BUILTIN(__builtin_llround, "LLid", "Fne")
BUILTIN(__builtin_llroundf, "LLif", "Fne")
BUILTIN(__builtin_llroundl, "LLiLd", "Fne")
BUILTIN(__builtin_llroundf128, "LLiLLd", "Fne")
BUILTIN(__builtin_log, "dd", "Fne")
BUILTIN(__builtin_log10, "dd", "Fne")
BUILTIN(__builtin_log10f, "ff", "Fne")
BUILTIN(__builtin_log10f16, "hh", "Fne")
BUILTIN(__builtin_log10l, "LdLd", "Fne")
BUILTIN(__builtin_log10f128, "LLdLLd", "Fne")
BUILTIN(__builtin_log1p, "dd", "Fne")
BUILTIN(__builtin_log1pf, "ff", "Fne")
BUILTIN(__builtin_log1pl, "LdLd", "Fne")
BUILTIN(__builtin_log1pf128, "LLdLLd", "Fne")
BUILTIN(__builtin_log2, "dd", "Fne")
BUILTIN(__builtin_log2f, "ff", "Fne")
BUILTIN(__builtin_log2f16, "hh", "Fne")
BUILTIN(__builtin_log2l, "LdLd", "Fne")
BUILTIN(__builtin_log2f128, "LLdLLd", "Fne")
BUILTIN(__builtin_logb, "dd", "Fne")
BUILTIN(__builtin_logbf, "ff", "Fne")
BUILTIN(__builtin_logbl, "LdLd", "Fne")
BUILTIN(__builtin_logbf128, "LLdLLd", "Fne")
BUILTIN(__builtin_logf, "ff", "Fne")
BUILTIN(__builtin_logf16, "hh", "Fne")
BUILTIN(__builtin_logl, "LdLd", "Fne")
BUILTIN(__builtin_logf128, "LLdLLd", "Fne")
BUILTIN(__builtin_lrint, "Lid", "Fne")
BUILTIN(__builtin_lrintf, "Lif", "Fne")
BUILTIN(__builtin_lrintl, "LiLd", "Fne")
BUILTIN(__builtin_lrintf128, "LiLLd", "Fne")
BUILTIN(__builtin_lround, "Lid", "Fne")
BUILTIN(__builtin_lroundf, "Lif", "Fne")
BUILTIN(__builtin_lroundl, "LiLd", "Fne")
BUILTIN(__builtin_lroundf128, "LiLLd", "Fne")
BUILTIN(__builtin_nearbyint, "dd", "Fnc")
BUILTIN(__builtin_nearbyintf, "ff", "Fnc")
BUILTIN(__builtin_nearbyintl, "LdLd", "Fnc")
BUILTIN(__builtin_nearbyintf128, "LLdLLd", "Fnc")
BUILTIN(__builtin_nextafter, "ddd", "Fne")
BUILTIN(__builtin_nextafterf, "fff", "Fne")
BUILTIN(__builtin_nextafterl, "LdLdLd", "Fne")
BUILTIN(__builtin_nextafterf128, "LLdLLdLLd", "Fne")
BUILTIN(__builtin_nexttoward, "ddLd", "Fne")
BUILTIN(__builtin_nexttowardf, "ffLd", "Fne")
BUILTIN(__builtin_nexttowardl, "LdLdLd", "Fne")
BUILTIN(__builtin_nexttowardf128, "LLdLLdLLd", "Fne")
BUILTIN(__builtin_remainder, "ddd", "Fne")
BUILTIN(__builtin_remainderf, "fff", "Fne")
BUILTIN(__builtin_remainderl, "LdLdLd", "Fne")
BUILTIN(__builtin_remainderf128, "LLdLLdLLd", "Fne")
BUILTIN(__builtin_remquo, "dddi*", "Fn")
BUILTIN(__builtin_remquof, "fffi*", "Fn")
BUILTIN(__builtin_remquol, "LdLdLdi*", "Fn")
BUILTIN(__builtin_remquof128, "LLdLLdLLdi*", "Fn")
BUILTIN(__builtin_rint, "dd", "Fnc")
BUILTIN(__builtin_rintf, "ff", "Fnc")
BUILTIN(__builtin_rintf16, "hh", "Fnc")
BUILTIN(__builtin_rintl, "LdLd", "Fnc")
BUILTIN(__builtin_rintf128, "LLdLLd", "Fnc")
BUILTIN(__builtin_round, "dd", "Fnc")
BUILTIN(__builtin_roundf, "ff", "Fnc")
BUILTIN(__builtin_roundf16, "hh", "Fnc")
BUILTIN(__builtin_roundl, "LdLd", "Fnc")
BUILTIN(__builtin_roundf128, "LLdLLd", "Fnc")
BUILTIN(__builtin_roundeven, "dd", "Fnc")
BUILTIN(__builtin_roundevenf, "ff", "Fnc")
BUILTIN(__builtin_roundevenf16, "hh", "Fnc")
BUILTIN(__builtin_roundevenl, "LdLd", "Fnc")
BUILTIN(__builtin_roundevenf128, "LLdLLd", "Fnc")
BUILTIN(__builtin_scalbln, "ddLi", "Fne")
BUILTIN(__builtin_scalblnf, "ffLi", "Fne")
BUILTIN(__builtin_scalblnl, "LdLdLi", "Fne")
BUILTIN(__builtin_scalblnf128, "LLdLLdLi", "Fne")
BUILTIN(__builtin_scalbn, "ddi", "Fne")
BUILTIN(__builtin_scalbnf, "ffi", "Fne")
BUILTIN(__builtin_scalbnl, "LdLdi", "Fne")
BUILTIN(__builtin_scalbnf128, "LLdLLdi", "Fne")
BUILTIN(__builtin_sin, "dd", "Fne")
BUILTIN(__builtin_sinf, "ff", "Fne")
BUILTIN(__builtin_sinf16, "hh", "Fne")
BUILTIN(__builtin_sinh, "dd", "Fne")
BUILTIN(__builtin_sinhf, "ff", "Fne")
BUILTIN(__builtin_sinhl, "LdLd", "Fne")
BUILTIN(__builtin_sinhf128, "LLdLLd", "Fne")
BUILTIN(__builtin_sinl, "LdLd", "Fne")
BUILTIN(__builtin_sinf128, "LLdLLd", "Fne")
BUILTIN(__builtin_sqrt, "dd", "Fne")
BUILTIN(__builtin_sqrtf, "ff", "Fne")
BUILTIN(__builtin_sqrtf16, "hh", "Fne")
BUILTIN(__builtin_sqrtl, "LdLd", "Fne")
BUILTIN(__builtin_sqrtf128, "LLdLLd", "Fne")
BUILTIN(__builtin_tan, "dd", "Fne")
BUILTIN(__builtin_tanf, "ff", "Fne")
BUILTIN(__builtin_tanh, "dd", "Fne")
BUILTIN(__builtin_tanhf, "ff", "Fne")
BUILTIN(__builtin_tanhl, "LdLd", "Fne")
BUILTIN(__builtin_tanhf128, "LLdLLd", "Fne")
BUILTIN(__builtin_tanl, "LdLd", "Fne")
BUILTIN(__builtin_tanf128, "LLdLLd", "Fne")
BUILTIN(__builtin_tgamma, "dd", "Fne")
BUILTIN(__builtin_tgammaf, "ff", "Fne")
BUILTIN(__builtin_tgammal, "LdLd", "Fne")
BUILTIN(__builtin_tgammaf128, "LLdLLd", "Fne")
BUILTIN(__builtin_trunc, "dd", "Fnc")
BUILTIN(__builtin_truncf, "ff", "Fnc")
BUILTIN(__builtin_truncl, "LdLd", "Fnc")
BUILTIN(__builtin_truncf128, "LLdLLd", "Fnc")
BUILTIN(__builtin_truncf16, "hh", "Fnc")

// Access to floating point environment
BUILTIN(__builtin_flt_rounds, "i", "n")
BUILTIN(__builtin_set_flt_rounds, "vi", "n")

// C99 complex builtins
BUILTIN(__builtin_cabs, "dXd", "Fne")
BUILTIN(__builtin_cabsf, "fXf", "Fne")
BUILTIN(__builtin_cabsl, "LdXLd", "Fne")
BUILTIN(__builtin_cacos, "XdXd", "Fne")
BUILTIN(__builtin_cacosf, "XfXf", "Fne")
BUILTIN(__builtin_cacosh, "XdXd", "Fne")
BUILTIN(__builtin_cacoshf, "XfXf", "Fne")
BUILTIN(__builtin_cacoshl, "XLdXLd", "Fne")
BUILTIN(__builtin_cacosl, "XLdXLd", "Fne")
BUILTIN(__builtin_carg, "dXd", "Fne")
BUILTIN(__builtin_cargf, "fXf", "Fne")
BUILTIN(__builtin_cargl, "LdXLd", "Fne")
BUILTIN(__builtin_casin, "XdXd", "Fne")
BUILTIN(__builtin_casinf, "XfXf", "Fne")
BUILTIN(__builtin_casinh, "XdXd", "Fne")
BUILTIN(__builtin_casinhf, "XfXf", "Fne")
BUILTIN(__builtin_casinhl, "XLdXLd", "Fne")
BUILTIN(__builtin_casinl, "XLdXLd", "Fne")
BUILTIN(__builtin_catan, "XdXd", "Fne")
BUILTIN(__builtin_catanf, "XfXf", "Fne")
BUILTIN(__builtin_catanh, "XdXd", "Fne")
BUILTIN(__builtin_catanhf, "XfXf", "Fne")
BUILTIN(__builtin_catanhl, "XLdXLd", "Fne")
BUILTIN(__builtin_catanl, "XLdXLd", "Fne")
BUILTIN(__builtin_ccos, "XdXd", "Fne")
BUILTIN(__builtin_ccosf, "XfXf", "Fne")
BUILTIN(__builtin_ccosl, "XLdXLd", "Fne")
BUILTIN(__builtin_ccosh, "XdXd", "Fne")
BUILTIN(__builtin_ccoshf, "XfXf", "Fne")
BUILTIN(__builtin_ccoshl, "XLdXLd", "Fne")
BUILTIN(__builtin_cexp, "XdXd", "Fne")
BUILTIN(__builtin_cexpf, "XfXf", "Fne")
BUILTIN(__builtin_cexpl, "XLdXLd", "Fne")
BUILTIN(__builtin_cimag, "dXd", "Fnc")
BUILTIN(__builtin_cimagf, "fXf", "Fnc")
BUILTIN(__builtin_cimagl, "LdXLd", "Fnc")
BUILTIN(__builtin_conj, "XdXd", "Fnc")
BUILTIN(__builtin_conjf, "XfXf", "Fnc")
BUILTIN(__builtin_conjl, "XLdXLd", "Fnc")
BUILTIN(__builtin_clog, "XdXd", "Fne")
BUILTIN(__builtin_clogf, "XfXf", "Fne")
BUILTIN(__builtin_clogl, "XLdXLd", "Fne")
BUILTIN(__builtin_cproj, "XdXd", "Fnc")
BUILTIN(__builtin_cprojf, "XfXf", "Fnc")
BUILTIN(__builtin_cprojl, "XLdXLd", "Fnc")
BUILTIN(__builtin_cpow, "XdXdXd", "Fne")
BUILTIN(__builtin_cpowf, "XfXfXf", "Fne")
BUILTIN(__builtin_cpowl, "XLdXLdXLd", "Fne")
BUILTIN(__builtin_creal, "dXd", "Fnc")
BUILTIN(__builtin_crealf, "fXf", "Fnc")
BUILTIN(__builtin_creall, "LdXLd", "Fnc")
BUILTIN(__builtin_csin, "XdXd", "Fne")
BUILTIN(__builtin_csinf, "XfXf", "Fne")
BUILTIN(__builtin_csinl, "XLdXLd", "Fne")
BUILTIN(__builtin_csinh, "XdXd", "Fne")
BUILTIN(__builtin_csinhf, "XfXf", "Fne")
BUILTIN(__builtin_csinhl, "XLdXLd", "Fne")
BUILTIN(__builtin_csqrt, "XdXd", "Fne")
BUILTIN(__builtin_csqrtf, "XfXf", "Fne")
BUILTIN(__builtin_csqrtl, "XLdXLd", "Fne")
BUILTIN(__builtin_ctan, "XdXd", "Fne")
BUILTIN(__builtin_ctanf, "XfXf", "Fne")
BUILTIN(__builtin_ctanl, "XLdXLd", "Fne")
BUILTIN(__builtin_ctanh, "XdXd", "Fne")
BUILTIN(__builtin_ctanhf, "XfXf", "Fne")
BUILTIN(__builtin_ctanhl, "XLdXLd", "Fne")

// GCC-compatible C99 CMPLX implementation.
BUILTIN(__builtin_complex, "v.", "nctE")

// FP Comparisons.
BUILTIN(__builtin_isgreater, "i.", "Fnct")
BUILTIN(__builtin_isgreaterequal, "i.", "Fnct")
BUILTIN(__builtin_isless, "i.", "Fnct")
BUILTIN(__builtin_islessequal, "i.", "Fnct")
BUILTIN(__builtin_islessgreater, "i.", "Fnct")
BUILTIN(__builtin_isunordered, "i.", "Fnct")

// Unary FP classification
BUILTIN(__builtin_fpclassify, "iiiiii.", "FnctE")
BUILTIN(__builtin_isfinite, "i.", "FnctE")
BUILTIN(__builtin_isinf, "i.", "FnctE")
BUILTIN(__builtin_isinf_sign, "i.", "FnctE")
BUILTIN(__builtin_isnan, "i.", "FnctE")
BUILTIN(__builtin_isnormal, "i.", "FnctE")
BUILTIN(__builtin_issubnormal, "i.", "FnctE")
BUILTIN(__builtin_iszero, "i.", "FnctE")
BUILTIN(__builtin_issignaling, "i.", "FnctE")
BUILTIN(__builtin_isfpclass, "i.", "nctE")

// FP signbit builtins
BUILTIN(__builtin_signbit, "i.", "Fnct")
BUILTIN(__builtin_signbitf, "if", "Fnc")
BUILTIN(__builtin_signbitl, "iLd", "Fnc")

// Special FP builtins.
BUILTIN(__builtin_canonicalize, "dd", "nc")
BUILTIN(__builtin_canonicalizef, "ff", "nc")
BUILTIN(__builtin_canonicalizef16, "hh", "nc")
BUILTIN(__builtin_canonicalizel, "LdLd", "nc")

// Builtins for arithmetic.
BUILTIN(__builtin_clzs, "iUs", "ncE")
BUILTIN(__builtin_clz, "iUi", "ncE")
BUILTIN(__builtin_clzl, "iULi", "ncE")
BUILTIN(__builtin_clzll, "iULLi", "ncE")
// TODO: int clzimax(uintmax_t)
BUILTIN(__builtin_ctzs, "iUs", "ncE")
BUILTIN(__builtin_ctz, "iUi", "ncE")
BUILTIN(__builtin_ctzl, "iULi", "ncE")
BUILTIN(__builtin_ctzll, "iULLi", "ncE")
// TODO: int ctzimax(uintmax_t)
BUILTIN(__builtin_ffs, "ii", "FncE")
BUILTIN(__builtin_ffsl, "iLi", "FncE")
BUILTIN(__builtin_ffsll, "iLLi", "FncE")
BUILTIN(__builtin_parity, "iUi", "ncE")
BUILTIN(__builtin_parityl, "iULi", "ncE")
BUILTIN(__builtin_parityll, "iULLi", "ncE")
BUILTIN(__builtin_popcount, "iUi", "ncE")
BUILTIN(__builtin_popcountl, "iULi", "ncE")
BUILTIN(__builtin_popcountll, "iULLi", "ncE")
BUILTIN(__builtin_clrsb, "ii", "ncE")
BUILTIN(__builtin_clrsbl, "iLi", "ncE")
BUILTIN(__builtin_clrsbll, "iLLi", "ncE")

// The following builtins rely on that char == 8 bits, short == 16 bits and that
// there exists native types on the target that are 32- and 64-bits wide, unless
// these conditions are fulfilled these builtins will operate on a not intended
// bitwidth.
BUILTIN(__builtin_bswap16, "UsUs", "ncE")
BUILTIN(__builtin_bswap32, "UZiUZi", "ncE")
BUILTIN(__builtin_bswap64, "UWiUWi", "ncE")

BUILTIN(__builtin_bitreverse8, "UcUc", "ncE")
BUILTIN(__builtin_bitreverse16, "UsUs", "ncE")
BUILTIN(__builtin_bitreverse32, "UZiUZi", "ncE")
BUILTIN(__builtin_bitreverse64, "UWiUWi", "ncE")

BUILTIN(__builtin_rotateleft8, "UcUcUc", "ncE")
BUILTIN(__builtin_rotateleft16, "UsUsUs", "ncE")
BUILTIN(__builtin_rotateleft32, "UZiUZiUZi", "ncE")
BUILTIN(__builtin_rotateleft64, "UWiUWiUWi", "ncE")
BUILTIN(__builtin_rotateright8, "UcUcUc", "ncE")
BUILTIN(__builtin_rotateright16, "UsUsUs", "ncE")
BUILTIN(__builtin_rotateright32, "UZiUZiUZi", "ncE")
BUILTIN(__builtin_rotateright64, "UWiUWiUWi", "ncE")

// Random GCC builtins
BUILTIN(__builtin_calloc, "v*zz", "nF")
BUILTIN(__builtin_constant_p, "i.", "nctuE")
BUILTIN(__builtin_classify_type, "i.", "nctuE")
BUILTIN(__builtin___CFStringMakeConstantString, "FC*cC*", "ncE")
BUILTIN(__builtin___NSStringMakeConstantString, "FC*cC*", "ncE")
BUILTIN(__builtin_va_start, "vA.", "nt")
BUILTIN(__builtin_va_end, "vA", "n")
BUILTIN(__builtin_va_copy, "vAA", "n")
BUILTIN(__builtin_stdarg_start, "vA.", "nt")
BUILTIN(__builtin_assume_aligned, "v*vC*z.", "nctE")
BUILTIN(__builtin_bcmp, "ivC*vC*z", "FnE")
BUILTIN(__builtin_bcopy, "vvC*v*z", "nF")
BUILTIN(__builtin_bzero, "vv*z", "nF")
BUILTIN(__builtin_free, "vv*", "nF")
BUILTIN(__builtin_malloc, "v*z", "nF")
BUILTIN(__builtin_memchr, "v*vC*iz", "nFE")
BUILTIN(__builtin_memcmp, "ivC*vC*z", "nFE")
BUILTIN(__builtin_memcpy, "v*v*vC*z", "nFE")
BUILTIN(__builtin_memcpy_inline, "vv*vC*Iz", "n")
BUILTIN(__builtin_memmove, "v*v*vC*z", "nFE")
BUILTIN(__builtin_mempcpy, "v*v*vC*z", "nF")
BUILTIN(__builtin_memset, "v*v*iz", "nF")
BUILTIN(__builtin_memset_inline, "vv*iIz", "n")
BUILTIN(__builtin_stpcpy, "c*c*cC*", "nF")
BUILTIN(__builtin_stpncpy, "c*c*cC*z", "nF")
BUILTIN(__builtin_strcasecmp, "icC*cC*", "nF")
BUILTIN(__builtin_strcat, "c*c*cC*", "nF")
BUILTIN(__builtin_strchr, "c*cC*i", "nFE")
BUILTIN(__builtin_strcmp, "icC*cC*", "nFE")
BUILTIN(__builtin_strcpy, "c*c*cC*", "nF")
BUILTIN(__builtin_strcspn, "zcC*cC*", "nF")
BUILTIN(__builtin_strdup, "c*cC*", "nF")
BUILTIN(__builtin_strlen, "zcC*", "nFE")
BUILTIN(__builtin_strncasecmp, "icC*cC*z", "nF")
BUILTIN(__builtin_strncat, "c*c*cC*z", "nF")
BUILTIN(__builtin_strncmp, "icC*cC*z", "nFE")
BUILTIN(__builtin_strncpy, "c*c*cC*z", "nF")
BUILTIN(__builtin_strndup, "c*cC*z", "nF")
BUILTIN(__builtin_strpbrk, "c*cC*cC*", "nF")
BUILTIN(__builtin_strrchr, "c*cC*i", "nF")
BUILTIN(__builtin_strspn, "zcC*cC*", "nF")
BUILTIN(__builtin_strstr, "c*cC*cC*", "nF")
BUILTIN(__builtin_wcschr, "w*wC*w", "nFE")
BUILTIN(__builtin_wcscmp, "iwC*wC*", "nFE")
BUILTIN(__builtin_wcslen, "zwC*", "nFE")
BUILTIN(__builtin_wcsncmp, "iwC*wC*z", "nFE")
BUILTIN(__builtin_wmemchr, "w*wC*wz", "nFE")
BUILTIN(__builtin_wmemcmp, "iwC*wC*z", "nFE")
BUILTIN(__builtin_wmemcpy, "w*w*wC*z", "nFE")
BUILTIN(__builtin_wmemmove, "w*w*wC*z", "nFE")
BUILTIN(__builtin_realloc, "v*v*z", "nF")
BUILTIN(__builtin_return_address, "v*IUi", "n")
BUILTIN(__builtin_extract_return_addr, "v*v*", "n")
BUILTIN(__builtin_frame_address, "v*IUi", "n")
BUILTIN(__builtin___clear_cache, "vc*c*", "n")
BUILTIN(__builtin_setjmp, "iv**", "j")
BUILTIN(__builtin_longjmp, "vv**i", "r")
BUILTIN(__builtin_unwind_init, "v", "")
BUILTIN(__builtin_eh_return_data_regno, "iIi", "ncE")
BUILTIN(__builtin_fprintf, "iP*RcC*R.", "nFp:1:")
BUILTIN(__builtin_printf, "icC*R.", "nFp:0:")
BUILTIN(__builtin_sprintf, "ic*RcC*R.", "nFp:1:")
BUILTIN(__builtin_snprintf, "ic*RzcC*R.", "nFp:2:")
BUILTIN(__builtin_vprintf, "icC*Ra", "nFP:0:")
BUILTIN(__builtin_vfprintf, "iP*RcC*Ra", "nFP:1:")
BUILTIN(__builtin_vsprintf, "ic*RcC*Ra", "nFP:1:")
BUILTIN(__builtin_vsnprintf, "ic*RzcC*Ra", "nFP:2:")
BUILTIN(__builtin_fscanf, "iP*RcC*R.", "Fs:1:")
BUILTIN(__builtin_scanf, "icC*R.", "Fs:0:")
BUILTIN(__builtin_sscanf, "icC*RcC*R.", "Fs:1:")
BUILTIN(__builtin_vfscanf, "iP*RcC*Ra", "FS:1:")
BUILTIN(__builtin_vscanf, "icC*Ra", "FS:0:")
BUILTIN(__builtin_vsscanf, "icC*RcC*Ra", "FS:1:")
BUILTIN(__builtin_thread_pointer, "v*", "nc")
BUILTIN(__builtin_launder, "v*v*", "ntE")
LANGBUILTIN(__builtin_is_constant_evaluated, "b", "nE", CXX_LANG)

// GCC exception builtins
BUILTIN(__builtin_eh_return, "vzv*", "r") // FIXME: Takes intptr_t, not size_t!
BUILTIN(__builtin_frob_return_addr, "v*v*", "n")
BUILTIN(__builtin_dwarf_cfa, "v*", "n")
BUILTIN(__builtin_init_dwarf_reg_size_table, "vv*", "n")
BUILTIN(__builtin_dwarf_sp_column, "Ui", "n")
BUILTIN(__builtin_extend_pointer, "ULLiv*", "n") // _Unwind_Word == uint64_t

// GCC Object size checking builtins
BUILTIN(__builtin_object_size, "zvC*i", "nuE")
BUILTIN(__builtin_dynamic_object_size, "zvC*i", "nuE") // Clang only.
BUILTIN(__builtin___memcpy_chk, "v*v*vC*zz", "nF")
BUILTIN(__builtin___memccpy_chk, "v*v*vC*izz", "nF")
BUILTIN(__builtin___memmove_chk, "v*v*vC*zz", "nF")
BUILTIN(__builtin___mempcpy_chk, "v*v*vC*zz", "nF")
BUILTIN(__builtin___memset_chk, "v*v*izz", "nF")
BUILTIN(__builtin___stpcpy_chk, "c*c*cC*z", "nF")
BUILTIN(__builtin___strcat_chk, "c*c*cC*z", "nF")
BUILTIN(__builtin___strcpy_chk, "c*c*cC*z", "nF")
BUILTIN(__builtin___strlcat_chk, "zc*cC*zz", "nF")
BUILTIN(__builtin___strlcpy_chk, "zc*cC*zz", "nF")
BUILTIN(__builtin___strncat_chk, "c*c*cC*zz", "nF")
BUILTIN(__builtin___strncpy_chk, "c*c*cC*zz", "nF")
BUILTIN(__builtin___stpncpy_chk, "c*c*cC*zz", "nF")
BUILTIN(__builtin___snprintf_chk, "ic*RzizcC*R.", "Fp:4:")
BUILTIN(__builtin___sprintf_chk, "ic*RizcC*R.", "Fp:3:")
BUILTIN(__builtin___vsnprintf_chk, "ic*RzizcC*Ra", "FP:4:")
BUILTIN(__builtin___vsprintf_chk, "ic*RizcC*Ra", "FP:3:")
BUILTIN(__builtin___fprintf_chk, "iP*RicC*R.", "Fp:2:")
BUILTIN(__builtin___printf_chk, "iicC*R.", "Fp:1:")
BUILTIN(__builtin___vfprintf_chk, "iP*RicC*Ra", "FP:2:")
BUILTIN(__builtin___vprintf_chk, "iicC*Ra", "FP:1:")

BUILTIN(__builtin_unpredictable, "LiLi", "nc")
BUILTIN(__builtin_expect, "LiLiLi", "ncE")
BUILTIN(__builtin_expect_with_probability, "LiLiLid", "ncE")
BUILTIN(__builtin_prefetch, "vvC*.", "nc")
BUILTIN(__builtin_readcyclecounter, "ULLi", "n")
BUILTIN(__builtin_trap, "v", "nr")
BUILTIN(__builtin_debugtrap, "v", "n")
BUILTIN(__builtin_unreachable, "v", "nr")
BUILTIN(__builtin_shufflevector, "v.", "nct")
BUILTIN(__builtin_convertvector, "v.", "nct")
BUILTIN(__builtin_vectorelements, "v.", "nct")
BUILTIN(__builtin_alloca, "v*z", "Fn")
BUILTIN(__builtin_alloca_uninitialized, "v*z", "Fn")
BUILTIN(__builtin_alloca_with_align, "v*zIz", "Fn")
BUILTIN(__builtin_alloca_with_align_uninitialized, "v*zIz", "Fn")
BUILTIN(__builtin_call_with_static_chain, "v.", "nt")
BUILTIN(__builtin_nondeterministic_value, "v.", "nt")

BUILTIN(__builtin_elementwise_abs, "v.", "nct")
BUILTIN(__builtin_elementwise_bitreverse, "v.", "nct")
BUILTIN(__builtin_elementwise_max, "v.", "nct")
BUILTIN(__builtin_elementwise_min, "v.", "nct")
BUILTIN(__builtin_elementwise_ceil, "v.", "nct")
BUILTIN(__builtin_elementwise_cos, "v.", "nct")
BUILTIN(__builtin_elementwise_exp, "v.", "nct")
BUILTIN(__builtin_elementwise_exp2, "v.", "nct")
BUILTIN(__builtin_elementwise_floor, "v.", "nct")
BUILTIN(__builtin_elementwise_log, "v.", "nct")
BUILTIN(__builtin_elementwise_log2, "v.", "nct")
BUILTIN(__builtin_elementwise_log10, "v.", "nct")
BUILTIN(__builtin_elementwise_pow, "v.", "nct")
BUILTIN(__builtin_elementwise_roundeven, "v.", "nct")
BUILTIN(__builtin_elementwise_round, "v.", "nct")
BUILTIN(__builtin_elementwise_rint, "v.", "nct")
BUILTIN(__builtin_elementwise_nearbyint, "v.", "nct")
BUILTIN(__builtin_elementwise_sin, "v.", "nct")
BUILTIN(__builtin_elementwise_sqrt, "v.", "nct")
BUILTIN(__builtin_elementwise_trunc, "v.", "nct")
BUILTIN(__builtin_elementwise_canonicalize, "v.", "nct")
BUILTIN(__builtin_elementwise_copysign, "v.", "nct")
BUILTIN(__builtin_elementwise_fma, "v.", "nct")
BUILTIN(__builtin_elementwise_add_sat, "v.", "nct")
BUILTIN(__builtin_elementwise_sub_sat, "v.", "nct")
BUILTIN(__builtin_reduce_max, "v.", "nct")
BUILTIN(__builtin_reduce_min, "v.", "nct")
BUILTIN(__builtin_reduce_xor, "v.", "nct")
BUILTIN(__builtin_reduce_or, "v.", "nct")
BUILTIN(__builtin_reduce_and, "v.", "nct")
BUILTIN(__builtin_reduce_add, "v.", "nct")
BUILTIN(__builtin_reduce_mul, "v.", "nct")

BUILTIN(__builtin_matrix_transpose, "v.", "nFt")
BUILTIN(__builtin_matrix_column_major_load, "v.", "nFt")
BUILTIN(__builtin_matrix_column_major_store, "v.", "nFt")

// "Overloaded" Atomic operator builtins.  These are overloaded to support data
// types of i8, i16, i32, i64, and i128.  The front-end sees calls to the
// non-suffixed version of these (which has a bogus type) and transforms them to
// the right overloaded version in Sema (plus casts).

// FIXME: These assume that char -> i8, short -> i16, int -> i32,
// long long -> i64.

BUILTIN(__sync_fetch_and_add, "v.", "t")
BUILTIN(__sync_fetch_and_add_1, "ccD*c.", "nt")
BUILTIN(__sync_fetch_and_add_2, "ssD*s.", "nt")
BUILTIN(__sync_fetch_and_add_4, "iiD*i.", "nt")
BUILTIN(__sync_fetch_and_add_8, "LLiLLiD*LLi.", "nt")
BUILTIN(__sync_fetch_and_add_16, "LLLiLLLiD*LLLi.", "nt")

BUILTIN(__sync_fetch_and_sub, "v.", "t")
BUILTIN(__sync_fetch_and_sub_1, "ccD*c.", "nt")
BUILTIN(__sync_fetch_and_sub_2, "ssD*s.", "nt")
BUILTIN(__sync_fetch_and_sub_4, "iiD*i.", "nt")
BUILTIN(__sync_fetch_and_sub_8, "LLiLLiD*LLi.", "nt")
BUILTIN(__sync_fetch_and_sub_16, "LLLiLLLiD*LLLi.", "nt")

BUILTIN(__sync_fetch_and_or, "v.", "t")
BUILTIN(__sync_fetch_and_or_1, "ccD*c.", "nt")
BUILTIN(__sync_fetch_and_or_2, "ssD*s.", "nt")
BUILTIN(__sync_fetch_and_or_4, "iiD*i.", "nt")
BUILTIN(__sync_fetch_and_or_8, "LLiLLiD*LLi.", "nt")
BUILTIN(__sync_fetch_and_or_16, "LLLiLLLiD*LLLi.", "nt")

BUILTIN(__sync_fetch_and_and, "v.", "t")
BUILTIN(__sync_fetch_and_and_1, "ccD*c.", "tn")
BUILTIN(__sync_fetch_and_and_2, "ssD*s.", "tn")
BUILTIN(__sync_fetch_and_and_4, "iiD*i.", "tn")
BUILTIN(__sync_fetch_and_and_8, "LLiLLiD*LLi.", "tn")
BUILTIN(__sync_fetch_and_and_16, "LLLiLLLiD*LLLi.", "tn")

BUILTIN(__sync_fetch_and_xor, "v.", "t")
BUILTIN(__sync_fetch_and_xor_1, "ccD*c.", "tn")
BUILTIN(__sync_fetch_and_xor_2, "ssD*s.", "tn")
BUILTIN(__sync_fetch_and_xor_4, "iiD*i.", "tn")
BUILTIN(__sync_fetch_and_xor_8, "LLiLLiD*LLi.", "tn")
BUILTIN(__sync_fetch_and_xor_16, "LLLiLLLiD*LLLi.", "tn")

BUILTIN(__sync_fetch_and_nand, "v.", "t")
BUILTIN(__sync_fetch_and_nand_1, "ccD*c.", "tn")
BUILTIN(__sync_fetch_and_nand_2, "ssD*s.", "tn")
BUILTIN(__sync_fetch_and_nand_4, "iiD*i.", "tn")
BUILTIN(__sync_fetch_and_nand_8, "LLiLLiD*LLi.", "tn")
BUILTIN(__sync_fetch_and_nand_16, "LLLiLLLiD*LLLi.", "tn")

BUILTIN(__sync_add_and_fetch, "v.", "t")
BUILTIN(__sync_add_and_fetch_1, "ccD*c.", "tn")
BUILTIN(__sync_add_and_fetch_2, "ssD*s.", "tn")
BUILTIN(__sync_add_and_fetch_4, "iiD*i.", "tn")
BUILTIN(__sync_add_and_fetch_8, "LLiLLiD*LLi.", "tn")
BUILTIN(__sync_add_and_fetch_16, "LLLiLLLiD*LLLi.", "tn")

BUILTIN(__sync_sub_and_fetch, "v.", "t")
BUILTIN(__sync_sub_and_fetch_1, "ccD*c.", "tn")
BUILTIN(__sync_sub_and_fetch_2, "ssD*s.", "tn")
BUILTIN(__sync_sub_and_fetch_4, "iiD*i.", "tn")
BUILTIN(__sync_sub_and_fetch_8, "LLiLLiD*LLi.", "tn")
BUILTIN(__sync_sub_and_fetch_16, "LLLiLLLiD*LLLi.", "tn")

BUILTIN(__sync_or_and_fetch, "v.", "t")
BUILTIN(__sync_or_and_fetch_1, "ccD*c.", "tn")
BUILTIN(__sync_or_and_fetch_2, "ssD*s.", "tn")
BUILTIN(__sync_or_and_fetch_4, "iiD*i.", "tn")
BUILTIN(__sync_or_and_fetch_8, "LLiLLiD*LLi.", "tn")
BUILTIN(__sync_or_and_fetch_16, "LLLiLLLiD*LLLi.", "tn")

BUILTIN(__sync_and_and_fetch, "v.", "t")
BUILTIN(__sync_and_and_fetch_1, "ccD*c.", "tn")
BUILTIN(__sync_and_and_fetch_2, "ssD*s.", "tn")
BUILTIN(__sync_and_and_fetch_4, "iiD*i.", "tn")
BUILTIN(__sync_and_and_fetch_8, "LLiLLiD*LLi.", "tn")
BUILTIN(__sync_and_and_fetch_16, "LLLiLLLiD*LLLi.", "tn")

BUILTIN(__sync_xor_and_fetch, "v.", "t")
BUILTIN(__sync_xor_and_fetch_1, "ccD*c.", "tn")
BUILTIN(__sync_xor_and_fetch_2, "ssD*s.", "tn")
BUILTIN(__sync_xor_and_fetch_4, "iiD*i.", "tn")
BUILTIN(__sync_xor_and_fetch_8, "LLiLLiD*LLi.", "tn")
BUILTIN(__sync_xor_and_fetch_16, "LLLiLLLiD*LLLi.", "tn")

BUILTIN(__sync_nand_and_fetch, "v.", "t")
BUILTIN(__sync_nand_and_fetch_1, "ccD*c.", "tn")
BUILTIN(__sync_nand_and_fetch_2, "ssD*s.", "tn")
BUILTIN(__sync_nand_and_fetch_4, "iiD*i.", "tn")
BUILTIN(__sync_nand_and_fetch_8, "LLiLLiD*LLi.", "tn")
BUILTIN(__sync_nand_and_fetch_16, "LLLiLLLiD*LLLi.", "tn")

BUILTIN(__sync_bool_compare_and_swap, "v.", "t")
BUILTIN(__sync_bool_compare_and_swap_1, "bcD*cc.", "tn")
BUILTIN(__sync_bool_compare_and_swap_2, "bsD*ss.", "tn")
BUILTIN(__sync_bool_compare_and_swap_4, "biD*ii.", "tn")
BUILTIN(__sync_bool_compare_and_swap_8, "bLLiD*LLiLLi.", "tn")
BUILTIN(__sync_bool_compare_and_swap_16, "bLLLiD*LLLiLLLi.", "tn")

BUILTIN(__sync_val_compare_and_swap, "v.", "t")
BUILTIN(__sync_val_compare_and_swap_1, "ccD*cc.", "tn")
BUILTIN(__sync_val_compare_and_swap_2, "ssD*ss.", "tn")
BUILTIN(__sync_val_compare_and_swap_4, "iiD*ii.", "tn")
BUILTIN(__sync_val_compare_and_swap_8, "LLiLLiD*LLiLLi.", "tn")
BUILTIN(__sync_val_compare_and_swap_16, "LLLiLLLiD*LLLiLLLi.", "tn")

BUILTIN(__sync_lock_test_and_set, "v.", "t")
BUILTIN(__sync_lock_test_and_set_1, "ccD*c.", "tn")
BUILTIN(__sync_lock_test_and_set_2, "ssD*s.", "tn")
BUILTIN(__sync_lock_test_and_set_4, "iiD*i.", "tn")
BUILTIN(__sync_lock_test_and_set_8, "LLiLLiD*LLi.", "tn")
BUILTIN(__sync_lock_test_and_set_16, "LLLiLLLiD*LLLi.", "tn")

BUILTIN(__sync_lock_release, "v.", "t")
BUILTIN(__sync_lock_release_1, "vcD*.", "tn")
BUILTIN(__sync_lock_release_2, "vsD*.", "tn")
BUILTIN(__sync_lock_release_4, "viD*.", "tn")
BUILTIN(__sync_lock_release_8, "vLLiD*.", "tn")
BUILTIN(__sync_lock_release_16, "vLLLiD*.", "tn")

BUILTIN(__sync_swap, "v.", "t")
BUILTIN(__sync_swap_1, "ccD*c.", "tn")
BUILTIN(__sync_swap_2, "ssD*s.", "tn")
BUILTIN(__sync_swap_4, "iiD*i.", "tn")
BUILTIN(__sync_swap_8, "LLiLLiD*LLi.", "tn")
BUILTIN(__sync_swap_16, "LLLiLLLiD*LLLi.", "tn")

// Some of our atomics builtins are handled by AtomicExpr rather than
// as normal builtin CallExprs. This macro is used for such builtins.
#ifndef ATOMIC_BUILTIN
#define ATOMIC_BUILTIN(ID, TYPE, ATTRS) BUILTIN(ID, TYPE, ATTRS)
#endif

// C11 _Atomic operations for <stdatomic.h>.
ATOMIC_BUILTIN(__c11_atomic_init, "v.", "t")
ATOMIC_BUILTIN(__c11_atomic_load, "v.", "t")
ATOMIC_BUILTIN(__c11_atomic_store, "v.", "t")
ATOMIC_BUILTIN(__c11_atomic_exchange, "v.", "t")
ATOMIC_BUILTIN(__c11_atomic_compare_exchange_strong, "v.", "t")
ATOMIC_BUILTIN(__c11_atomic_compare_exchange_weak, "v.", "t")
ATOMIC_BUILTIN(__c11_atomic_fetch_add, "v.", "t")
ATOMIC_BUILTIN(__c11_atomic_fetch_sub, "v.", "t")
ATOMIC_BUILTIN(__c11_atomic_fetch_and, "v.", "t")
ATOMIC_BUILTIN(__c11_atomic_fetch_or, "v.", "t")
ATOMIC_BUILTIN(__c11_atomic_fetch_xor, "v.", "t")
ATOMIC_BUILTIN(__c11_atomic_fetch_nand, "v.", "t")
ATOMIC_BUILTIN(__c11_atomic_fetch_max, "v.", "t")
ATOMIC_BUILTIN(__c11_atomic_fetch_min, "v.", "t")
BUILTIN(__c11_atomic_thread_fence, "vi", "n")
BUILTIN(__c11_atomic_signal_fence, "vi", "n")
BUILTIN(__c11_atomic_is_lock_free, "bz", "nE")

// GNU atomic builtins.
ATOMIC_BUILTIN(__atomic_load, "v.", "t")
ATOMIC_BUILTIN(__atomic_load_n, "v.", "t")
ATOMIC_BUILTIN(__atomic_store, "v.", "t")
ATOMIC_BUILTIN(__atomic_store_n, "v.", "t")
ATOMIC_BUILTIN(__atomic_exchange, "v.", "t")
ATOMIC_BUILTIN(__atomic_exchange_n, "v.", "t")
ATOMIC_BUILTIN(__atomic_compare_exchange, "v.", "t")
ATOMIC_BUILTIN(__atomic_compare_exchange_n, "v.", "t")
ATOMIC_BUILTIN(__atomic_fetch_add, "v.", "t")
ATOMIC_BUILTIN(__atomic_fetch_sub, "v.", "t")
ATOMIC_BUILTIN(__atomic_fetch_and, "v.", "t")
ATOMIC_BUILTIN(__atomic_fetch_or, "v.", "t")
ATOMIC_BUILTIN(__atomic_fetch_xor, "v.", "t")
ATOMIC_BUILTIN(__atomic_fetch_nand, "v.", "t")
ATOMIC_BUILTIN(__atomic_add_fetch, "v.", "t")
ATOMIC_BUILTIN(__atomic_sub_fetch, "v.", "t")
ATOMIC_BUILTIN(__atomic_and_fetch, "v.", "t")
ATOMIC_BUILTIN(__atomic_or_fetch, "v.", "t")
ATOMIC_BUILTIN(__atomic_xor_fetch, "v.", "t")
ATOMIC_BUILTIN(__atomic_max_fetch, "v.", "t")
ATOMIC_BUILTIN(__atomic_min_fetch, "v.", "t")
ATOMIC_BUILTIN(__atomic_nand_fetch, "v.", "t")
BUILTIN(__atomic_test_and_set, "bvD*i", "n")
BUILTIN(__atomic_clear, "vvD*i", "n")
BUILTIN(__atomic_thread_fence, "vi", "n")
BUILTIN(__atomic_signal_fence, "vi", "n")
BUILTIN(__atomic_always_lock_free, "bzvCD*", "nE")
BUILTIN(__atomic_is_lock_free, "bzvCD*", "nE")

// GNU atomic builtins with atomic scopes.
ATOMIC_BUILTIN(__scoped_atomic_load, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_load_n, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_store, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_store_n, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_exchange, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_exchange_n, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_compare_exchange, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_compare_exchange_n, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_fetch_add, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_fetch_sub, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_fetch_and, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_fetch_or, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_fetch_xor, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_fetch_nand, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_add_fetch, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_sub_fetch, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_and_fetch, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_or_fetch, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_xor_fetch, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_max_fetch, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_min_fetch, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_nand_fetch, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_fetch_min, "v.", "t")
ATOMIC_BUILTIN(__scoped_atomic_fetch_max, "v.", "t")

// OpenCL 2.0 atomic builtins.
ATOMIC_BUILTIN(__opencl_atomic_init, "v.", "t")
ATOMIC_BUILTIN(__opencl_atomic_load, "v.", "t")
ATOMIC_BUILTIN(__opencl_atomic_store, "v.", "t")
ATOMIC_BUILTIN(__opencl_atomic_exchange, "v.", "t")
ATOMIC_BUILTIN(__opencl_atomic_compare_exchange_strong, "v.", "t")
ATOMIC_BUILTIN(__opencl_atomic_compare_exchange_weak, "v.", "t")
ATOMIC_BUILTIN(__opencl_atomic_fetch_add, "v.", "t")
ATOMIC_BUILTIN(__opencl_atomic_fetch_sub, "v.", "t")
ATOMIC_BUILTIN(__opencl_atomic_fetch_and, "v.", "t")
ATOMIC_BUILTIN(__opencl_atomic_fetch_or, "v.", "t")
ATOMIC_BUILTIN(__opencl_atomic_fetch_xor, "v.", "t")
ATOMIC_BUILTIN(__opencl_atomic_fetch_min, "v.", "t")
ATOMIC_BUILTIN(__opencl_atomic_fetch_max, "v.", "t")

// GCC does not support these, they are a Clang extension.
ATOMIC_BUILTIN(__atomic_fetch_min, "v.", "t")
ATOMIC_BUILTIN(__atomic_fetch_max, "v.", "t")

// HIP atomic builtins.
ATOMIC_BUILTIN(__hip_atomic_load, "v.", "t")
ATOMIC_BUILTIN(__hip_atomic_store, "v.", "t")
ATOMIC_BUILTIN(__hip_atomic_compare_exchange_weak, "v.", "t")
ATOMIC_BUILTIN(__hip_atomic_compare_exchange_strong, "v.", "t")
ATOMIC_BUILTIN(__hip_atomic_exchange, "v.", "t")
ATOMIC_BUILTIN(__hip_atomic_fetch_add, "v.", "t")
ATOMIC_BUILTIN(__hip_atomic_fetch_sub, "v.", "t")
ATOMIC_BUILTIN(__hip_atomic_fetch_and, "v.", "t")
ATOMIC_BUILTIN(__hip_atomic_fetch_or, "v.", "t")
ATOMIC_BUILTIN(__hip_atomic_fetch_xor, "v.", "t")
ATOMIC_BUILTIN(__hip_atomic_fetch_min, "v.", "t")
ATOMIC_BUILTIN(__hip_atomic_fetch_max, "v.", "t")

#undef ATOMIC_BUILTIN

// Non-overloaded atomic builtins.
BUILTIN(__sync_synchronize, "v", "n")
// GCC does not support these, they are a Clang extension.
BUILTIN(__sync_fetch_and_min, "iiD*i", "n")
BUILTIN(__sync_fetch_and_max, "iiD*i", "n")
BUILTIN(__sync_fetch_and_umin, "UiUiD*Ui", "n")
BUILTIN(__sync_fetch_and_umax, "UiUiD*Ui", "n")

// Random libc builtins.
BUILTIN(__builtin_abort, "v", "Fnr")
BUILTIN(__builtin_index, "c*cC*i", "Fn")
BUILTIN(__builtin_rindex, "c*cC*i", "Fn")

// ignored glibc builtin, see
// https://sourceware.org/bugzilla/show_bug.cgi?id=25399
BUILTIN(__warn_memset_zero_len, "v", "nU")

// Microsoft builtins.  These are only active with -fms-extensions.
LANGBUILTIN(_alloca, "v*z", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__annotation, "wC*.", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__assume, "vb", "nE", ALL_MS_LANGUAGES)
LANGBUILTIN(_bittest, "UcNiC*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_bittestandcomplement, "UcNi*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_bittestandreset, "UcNi*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_bittestandset, "UcNi*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_bittest64, "UcWiC*Wi", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_bittestandcomplement64, "UcWi*Wi", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_bittestandreset64, "UcWi*Wi", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_bittestandset64, "UcWi*Wi", "n", ALL_MS_LANGUAGES)
LIBBUILTIN(_byteswap_ushort, "UsUs", "fnc", STDLIB_H, ALL_MS_LANGUAGES)
LIBBUILTIN(_byteswap_ulong, "UNiUNi", "fnc", STDLIB_H, ALL_MS_LANGUAGES)
LIBBUILTIN(_byteswap_uint64, "ULLiULLi", "fnc", STDLIB_H, ALL_MS_LANGUAGES)
LANGBUILTIN(__debugbreak, "v", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__exception_code, "UNi", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_exception_code, "UNi", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__exception_info, "v*", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_exception_info, "v*", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__abnormal_termination, "i", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_abnormal_termination, "i", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__GetExceptionInfo, "v*.", "zntu", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedAnd8, "ccD*c", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedAnd16, "ssD*s", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedAnd, "NiNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedCompareExchange8, "ccD*cc", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedCompareExchange16, "ssD*ss", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedCompareExchange, "NiNiD*NiNi", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedCompareExchange64, "LLiLLiD*LLiLLi", "n",
            ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedCompareExchangePointer, "v*v*D*v*v*", "n",
            ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedCompareExchangePointer_nf, "v*v*D*v*v*", "n",
            ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedDecrement16, "ssD*", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedDecrement, "NiNiD*", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedExchange, "NiNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedExchange8, "ccD*c", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedExchange16, "ssD*s", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedExchangeAdd8, "ccD*c", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedExchangeAdd16, "ssD*s", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedExchangeAdd, "NiNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedExchangePointer, "v*v*D*v*", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedExchangeSub8, "ccD*c", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedExchangeSub16, "ssD*s", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedExchangeSub, "NiNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedIncrement16, "ssD*", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedIncrement, "NiNiD*", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedOr8, "ccD*c", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedOr16, "ssD*s", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedOr, "NiNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedXor8, "ccD*c", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedXor16, "ssD*s", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_InterlockedXor, "NiNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_interlockedbittestandreset, "UcNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_interlockedbittestandreset64, "UcWiD*Wi", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_interlockedbittestandreset_acq, "UcNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_interlockedbittestandreset_nf, "UcNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_interlockedbittestandreset_rel, "UcNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_interlockedbittestandset, "UcNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_interlockedbittestandset64, "UcWiD*Wi", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_interlockedbittestandset_acq, "UcNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_interlockedbittestandset_nf, "UcNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_interlockedbittestandset_rel, "UcNiD*Ni", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__iso_volatile_load8, "ccCD*", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__iso_volatile_load16, "ssCD*", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__iso_volatile_load32, "iiCD*", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__iso_volatile_load64, "LLiLLiCD*", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__iso_volatile_store8, "vcD*c", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__iso_volatile_store16, "vsD*s", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__iso_volatile_store32, "viD*i", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__iso_volatile_store64, "vLLiD*LLi", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__noop, "i.", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(__lzcnt16, "UsUs", "ncE", ALL_MS_LANGUAGES)
LANGBUILTIN(__lzcnt, "UiUi", "ncE", ALL_MS_LANGUAGES)
LANGBUILTIN(__lzcnt64, "UWiUWi", "ncE", ALL_MS_LANGUAGES)
LANGBUILTIN(__popcnt16, "UsUs", "ncE", ALL_MS_LANGUAGES)
LANGBUILTIN(__popcnt, "UiUi", "ncE", ALL_MS_LANGUAGES)
LANGBUILTIN(__popcnt64, "UWiUWi", "ncE", ALL_MS_LANGUAGES)
LANGBUILTIN(_ReturnAddress, "v*", "n", ALL_MS_LANGUAGES)
LANGBUILTIN(_rotl8, "UcUcUc", "nE", ALL_MS_LANGUAGES)
LANGBUILTIN(_rotl16, "UsUsUc", "nE", ALL_MS_LANGUAGES)
LANGBUILTIN(_rotl, "UiUii", "nE", ALL_MS_LANGUAGES)
LANGBUILTIN(_lrotl, "ULiULii", "nE", ALL_MS_LANGUAGES)
LANGBUILTIN(_rotl64, "UWiUWii", "nE", ALL_MS_LANGUAGES)
LANGBUILTIN(_rotr8, "UcUcUc", "nE", ALL_MS_LANGUAGES)
LANGBUILTIN(_rotr16, "UsUsUc", "nE", ALL_MS_LANGUAGES)
LANGBUILTIN(_rotr, "UiUii", "nE", ALL_MS_LANGUAGES)
LANGBUILTIN(_lrotr, "ULiULii", "nE", ALL_MS_LANGUAGES)
LANGBUILTIN(_rotr64, "UWiUWii", "nE", ALL_MS_LANGUAGES)
LANGBUILTIN(__va_start, "vc**.", "nt", ALL_MS_LANGUAGES)
LANGBUILTIN(__fastfail, "vUi", "nr", ALL_MS_LANGUAGES)

// Microsoft library builtins.
LIBBUILTIN(_setjmpex, "iJ", "fjT", SETJMPEX_H, ALL_MS_LANGUAGES)

// C99 library functions
// C99 stdarg.h
LIBBUILTIN(va_start, "vA.", "fn", STDARG_H, ALL_LANGUAGES)
LIBBUILTIN(va_end, "vA", "fn", STDARG_H, ALL_LANGUAGES)
LIBBUILTIN(va_copy, "vAA", "fn", STDARG_H, ALL_LANGUAGES)
// C99 stdlib.h
LIBBUILTIN(abort, "v", "fr", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(calloc, "v*zz", "f", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(exit, "vi", "fr", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(_Exit, "vi", "fr", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(malloc, "v*z", "f", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(realloc, "v*v*z", "f", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(free, "vv*", "f", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(strtod, "dcC*c**", "f", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(strtof, "fcC*c**", "f", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(strtold, "LdcC*c**", "f", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(strtol, "LicC*c**i", "f", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(strtoll, "LLicC*c**i", "f", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(strtoul, "ULicC*c**i", "f", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(strtoull, "ULLicC*c**i", "f", STDLIB_H, ALL_LANGUAGES)
// C11 stdlib.h
LIBBUILTIN(aligned_alloc, "v*zz", "f", STDLIB_H, ALL_LANGUAGES)
// C99 string.h
LIBBUILTIN(memcpy, "v*v*vC*z", "fE", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(memcmp, "ivC*vC*z", "fE", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(memmove, "v*v*vC*z", "fE", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strcpy, "c*c*cC*", "f", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strncpy, "c*c*cC*z", "f", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strcmp, "icC*cC*", "fE", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strncmp, "icC*cC*z", "fE", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strcat, "c*c*cC*", "f", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strncat, "c*c*cC*z", "f", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strxfrm, "zc*cC*z", "f", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(memchr, "v*vC*iz", "fE", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strchr, "c*cC*i", "fE", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strcspn, "zcC*cC*", "f", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strpbrk, "c*cC*cC*", "f", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strrchr, "c*cC*i", "f", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strspn, "zcC*cC*", "f", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strstr, "c*cC*cC*", "f", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strtok, "c*c*cC*", "f", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(memset, "v*v*iz", "f", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strerror, "c*i", "f", STRING_H, ALL_LANGUAGES)
LIBBUILTIN(strlen, "zcC*", "fE", STRING_H, ALL_LANGUAGES)
// C99 stdio.h
// FIXME: This list is incomplete.
LIBBUILTIN(printf, "icC*.", "fp:0:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(fprintf, "iP*cC*.", "fp:1:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(snprintf, "ic*zcC*.", "fp:2:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(sprintf, "ic*cC*.", "fp:1:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(vprintf, "icC*a", "fP:0:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(vfprintf, "iP*cC*a", "fP:1:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(vsnprintf, "ic*zcC*a", "fP:2:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(vsprintf, "ic*cC*a", "fP:1:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(scanf, "icC*R.", "fs:0:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(fscanf, "iP*RcC*R.", "fs:1:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(sscanf, "icC*RcC*R.", "fs:1:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(vscanf, "icC*Ra", "fS:0:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(vfscanf, "iP*RcC*Ra", "fS:1:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(vsscanf, "icC*RcC*Ra", "fS:1:", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(fopen, "P*cC*cC*", "f", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(fread, "zv*zzP*", "f", STDIO_H, ALL_LANGUAGES)
LIBBUILTIN(fwrite, "zvC*zzP*", "f", STDIO_H, ALL_LANGUAGES)

// C99 ctype.h
LIBBUILTIN(isalnum, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
LIBBUILTIN(isalpha, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
LIBBUILTIN(isblank, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
LIBBUILTIN(iscntrl, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
LIBBUILTIN(isdigit, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
LIBBUILTIN(isgraph, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
LIBBUILTIN(islower, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
LIBBUILTIN(isprint, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
LIBBUILTIN(ispunct, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
LIBBUILTIN(isspace, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
LIBBUILTIN(isupper, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
LIBBUILTIN(isxdigit, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
LIBBUILTIN(tolower, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
LIBBUILTIN(toupper, "ii", "fnU", CTYPE_H, ALL_LANGUAGES)
// C99 wchar.h
// FIXME: This list is incomplete. We should cover at least the functions that
// take format strings.
LIBBUILTIN(wcschr, "w*wC*w", "fE", WCHAR_H, ALL_LANGUAGES)
LIBBUILTIN(wcscmp, "iwC*wC*", "fE", WCHAR_H, ALL_LANGUAGES)
LIBBUILTIN(wcslen, "zwC*", "fE", WCHAR_H, ALL_LANGUAGES)
LIBBUILTIN(wcsncmp, "iwC*wC*z", "fE", WCHAR_H, ALL_LANGUAGES)
LIBBUILTIN(wmemchr, "w*wC*wz", "fE", WCHAR_H, ALL_LANGUAGES)
LIBBUILTIN(wmemcmp, "iwC*wC*z", "fE", WCHAR_H, ALL_LANGUAGES)
LIBBUILTIN(wmemcpy, "w*w*wC*z", "fE", WCHAR_H, ALL_LANGUAGES)
LIBBUILTIN(wmemmove, "w*w*wC*z", "fE", WCHAR_H, ALL_LANGUAGES)

// C99
// In some systems setjmp is a macro that expands to _setjmp. We undefine
// it here to avoid having two identical LIBBUILTIN entries.
#undef setjmp
LIBBUILTIN(setjmp, "iJ", "fjT", SETJMP_H, ALL_LANGUAGES)
LIBBUILTIN(longjmp, "vJi", "frT", SETJMP_H, ALL_LANGUAGES)

// Non-C library functions, active in GNU mode only.
// Functions with (returns_twice) attribute (marked as "j") are still active in
// all languages, because losing this attribute would result in miscompilation
// when these functions are used in non-GNU mode. PR16138.
LIBBUILTIN(alloca, "v*z", "f", STDLIB_H, ALL_GNU_LANGUAGES)
// POSIX malloc.h
LIBBUILTIN(memalign, "v*zz", "f", MALLOC_H, ALL_GNU_LANGUAGES)
// POSIX string.h
LIBBUILTIN(memccpy, "v*v*vC*iz", "f", STRING_H, ALL_GNU_LANGUAGES)
LIBBUILTIN(mempcpy, "v*v*vC*z", "f", STRING_H, ALL_GNU_LANGUAGES)
LIBBUILTIN(stpcpy, "c*c*cC*", "f", STRING_H, ALL_GNU_LANGUAGES)
LIBBUILTIN(stpncpy, "c*c*cC*z", "f", STRING_H, ALL_GNU_LANGUAGES)
LIBBUILTIN(strdup, "c*cC*", "f", STRING_H, ALL_GNU_LANGUAGES)
LIBBUILTIN(strndup, "c*cC*z", "f", STRING_H, ALL_GNU_LANGUAGES)
// POSIX strings.h
LIBBUILTIN(index, "c*cC*i", "f", STRINGS_H, ALL_GNU_LANGUAGES)
LIBBUILTIN(rindex, "c*cC*i", "f", STRINGS_H, ALL_GNU_LANGUAGES)
LIBBUILTIN(bzero, "vv*z", "f", STRINGS_H, ALL_GNU_LANGUAGES)
LIBBUILTIN(bcopy, "vvC*v*z", "f", STRINGS_H, ALL_GNU_LANGUAGES)
LIBBUILTIN(bcmp, "ivC*vC*z", "fE", STRINGS_H, ALL_GNU_LANGUAGES)
// In some systems str[n]casejmp is a macro that expands to _str[n]icmp.
// We undefine then here to avoid wrong name.
#undef strcasecmp
#undef strncasecmp
LIBBUILTIN(strcasecmp, "icC*cC*", "f", STRINGS_H, ALL_GNU_LANGUAGES)
LIBBUILTIN(strncasecmp, "icC*cC*z", "f", STRINGS_H, ALL_GNU_LANGUAGES)
// POSIX unistd.h
LIBBUILTIN(_exit, "vi", "fr", UNISTD_H, ALL_GNU_LANGUAGES)
LIBBUILTIN(vfork, "p", "fjT", UNISTD_H, ALL_LANGUAGES)
// POSIX pthread.h
// FIXME: Should specify argument types.
LIBBUILTIN(pthread_create, "", "fC<2,3>", PTHREAD_H, ALL_GNU_LANGUAGES)

// POSIX setjmp.h

// FIXME: MinGW _setjmp has an additional void* parameter.
LIBBUILTIN(_setjmp, "iJ", "fjT", SETJMP_H, ALL_LANGUAGES)
LIBBUILTIN(__sigsetjmp, "iSJi", "fjT", SETJMP_H, ALL_LANGUAGES)
LIBBUILTIN(sigsetjmp, "iSJi", "fjT", SETJMP_H, ALL_LANGUAGES)
LIBBUILTIN(savectx, "iJ", "fjT", SETJMP_H, ALL_LANGUAGES)
LIBBUILTIN(getcontext, "iK*", "fjT", SETJMP_H, ALL_LANGUAGES)

LIBBUILTIN(_longjmp, "vJi", "frT", SETJMP_H, ALL_GNU_LANGUAGES)
LIBBUILTIN(siglongjmp, "vSJi", "frT", SETJMP_H, ALL_GNU_LANGUAGES)
// non-standard but very common
LIBBUILTIN(strlcpy, "zc*cC*z", "f", STRING_H, ALL_GNU_LANGUAGES)
LIBBUILTIN(strlcat, "zc*cC*z", "f", STRING_H, ALL_GNU_LANGUAGES)
//   id objc_msgSend(id, SEL, ...)
LIBBUILTIN(objc_msgSend, "GGH.", "f", OBJC_MESSAGE_H, OBJC_LANG)
// long double objc_msgSend_fpret(id self, SEL op, ...)
LIBBUILTIN(objc_msgSend_fpret, "LdGH.", "f", OBJC_MESSAGE_H, OBJC_LANG)
// _Complex long double objc_msgSend_fp2ret(id self, SEL op, ...)
LIBBUILTIN(objc_msgSend_fp2ret, "XLdGH.", "f", OBJC_MESSAGE_H, OBJC_LANG)
// void objc_msgSend_stret (id, SEL, ...)
LIBBUILTIN(objc_msgSend_stret, "vGH.", "f", OBJC_MESSAGE_H, OBJC_LANG)
// id objc_msgSendSuper(struct objc_super *super, SEL op, ...)
LIBBUILTIN(objc_msgSendSuper, "GM*H.", "f", OBJC_MESSAGE_H, OBJC_LANG)
// void objc_msgSendSuper_stret(struct objc_super *super, SEL op, ...)
LIBBUILTIN(objc_msgSendSuper_stret, "vM*H.", "f", OBJC_MESSAGE_H, OBJC_LANG)
//   id objc_getClass(const char *name)
LIBBUILTIN(objc_getClass, "GcC*", "f", OBJC_RUNTIME_H, OBJC_LANG)
//   id objc_getMetaClass(const char *name)
LIBBUILTIN(objc_getMetaClass, "GcC*", "f", OBJC_RUNTIME_H, OBJC_LANG)
// void objc_enumerationMutation(id)
LIBBUILTIN(objc_enumerationMutation, "vG", "f", OBJC_RUNTIME_H, OBJC_LANG)

// id objc_read_weak(id *location)
LIBBUILTIN(objc_read_weak, "GG*", "f", OBJC_OBJC_AUTO_H, OBJC_LANG)
// id objc_assign_weak(id value, id *location)
LIBBUILTIN(objc_assign_weak, "GGG*", "f", OBJC_OBJC_AUTO_H, OBJC_LANG)
// id objc_assign_ivar(id value, id dest, ptrdiff_t offset)
LIBBUILTIN(objc_assign_ivar, "GGGY", "f", OBJC_OBJC_AUTO_H, OBJC_LANG)
// id objc_assign_global(id val, id *dest)
LIBBUILTIN(objc_assign_global, "GGG*", "f", OBJC_OBJC_AUTO_H, OBJC_LANG)
// id objc_assign_strongCast(id val, id *dest
LIBBUILTIN(objc_assign_strongCast, "GGG*", "f", OBJC_OBJC_AUTO_H, OBJC_LANG)

// id objc_exception_extract(void *localExceptionData)
LIBBUILTIN(objc_exception_extract, "Gv*", "f", OBJC_OBJC_EXCEPTION_H, OBJC_LANG)
// void objc_exception_try_enter(void *localExceptionData)
LIBBUILTIN(objc_exception_try_enter, "vv*", "f", OBJC_OBJC_EXCEPTION_H,
           OBJC_LANG)
// void objc_exception_try_exit(void *localExceptionData)
LIBBUILTIN(objc_exception_try_exit, "vv*", "f", OBJC_OBJC_EXCEPTION_H,
           OBJC_LANG)
// int objc_exception_match(Class exceptionClass, id exception)
LIBBUILTIN(objc_exception_match, "iGG", "f", OBJC_OBJC_EXCEPTION_H, OBJC_LANG)
// void objc_exception_throw(id exception)
LIBBUILTIN(objc_exception_throw, "vG", "f", OBJC_OBJC_EXCEPTION_H, OBJC_LANG)

// int objc_sync_enter(id obj)
LIBBUILTIN(objc_sync_enter, "iG", "f", OBJC_OBJC_SYNC_H, OBJC_LANG)
// int objc_sync_exit(id obj)
LIBBUILTIN(objc_sync_exit, "iG", "f", OBJC_OBJC_SYNC_H, OBJC_LANG)

BUILTIN(__builtin_objc_memmove_collectable, "v*v*vC*z", "nF")

// void NSLog(NSString *fmt, ...)
LIBBUILTIN(NSLog, "vG.", "fp:0:", FOUNDATION_NSOBJCRUNTIME_H, OBJC_LANG)
// void NSLogv(NSString *fmt, va_list args)
LIBBUILTIN(NSLogv, "vGa", "fP:0:", FOUNDATION_NSOBJCRUNTIME_H, OBJC_LANG)

// Builtin math library functions
LIBBUILTIN(atan2, "ddd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(atan2f, "fff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(atan2l, "LdLdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(abs, "ii", "fnc", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(labs, "LiLi", "fnc", STDLIB_H, ALL_LANGUAGES)
LIBBUILTIN(llabs, "LLiLLi", "fnc", STDLIB_H, ALL_LANGUAGES)

LIBBUILTIN(copysign, "ddd", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(copysignf, "fff", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(copysignl, "LdLdLd", "fnc", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(fabs, "dd", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(fabsf, "ff", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(fabsl, "LdLd", "fnc", MATH_H, ALL_LANGUAGES)

// Some systems define finitef as alias of _finitef.
#if defined(finitef)
#undef finitef
#endif
LIBBUILTIN(finite, "id", "fnc", MATH_H, GNU_LANG)
LIBBUILTIN(finitef, "if", "fnc", MATH_H, GNU_LANG)
LIBBUILTIN(finitel, "iLd", "fnc", MATH_H, GNU_LANG)
// glibc's math.h generates calls to __finite
LIBBUILTIN(__finite, "id", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(__finitef, "if", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(__finitel, "iLd", "fnc", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(fmod, "ddd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(fmodf, "fff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(fmodl, "LdLdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(frexp, "ddi*", "fn", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(frexpf, "ffi*", "fn", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(frexpl, "LdLdi*", "fn", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(ldexp, "ddi", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(ldexpf, "ffi", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(ldexpl, "LdLdi", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(modf, "ddd*", "fn", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(modff, "fff*", "fn", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(modfl, "LdLdLd*", "fn", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(nan, "dcC*", "fUn", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(nanf, "fcC*", "fUn", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(nanl, "LdcC*", "fUn", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(pow, "ddd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(powf, "fff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(powl, "LdLdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(acos, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(acosf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(acosl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(acosh, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(acoshf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(acoshl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(asin, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(asinf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(asinl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(asinh, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(asinhf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(asinhl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(atan, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(atanf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(atanl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(atanh, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(atanhf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(atanhl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(cbrt, "dd", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(cbrtf, "ff", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(cbrtl, "LdLd", "fnc", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(ceil, "dd", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(ceilf, "ff", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(ceill, "LdLd", "fnc", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(cos, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(cosf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(cosl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(cosh, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(coshf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(coshl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(erf, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(erff, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(erfl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(erfc, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(erfcf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(erfcl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(exp, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(expf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(expl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(exp2, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(exp2f, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(exp2l, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(expm1, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(expm1f, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(expm1l, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(fdim, "ddd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(fdimf, "fff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(fdiml, "LdLdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(floor, "dd", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(floorf, "ff", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(floorl, "LdLd", "fnc", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(fma, "dddd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(fmaf, "ffff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(fmal, "LdLdLdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(fmax, "ddd", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(fmaxf, "fff", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(fmaxl, "LdLdLd", "fnc", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(fmin, "ddd", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(fminf, "fff", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(fminl, "LdLdLd", "fnc", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(hypot, "ddd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(hypotf, "fff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(hypotl, "LdLdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(ilogb, "id", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(ilogbf, "if", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(ilogbl, "iLd", "fne", MATH_H, ALL_LANGUAGES)

// POSIX math.h declares a global, signgam, that lgamma writes to, so these
// shouldn't have "e", "c" or "g" attributes
LIBBUILTIN(lgamma, "dd", "fn", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(lgammaf, "ff", "fn", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(lgammal, "LdLd", "fn", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(llrint, "LLid", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(llrintf, "LLif", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(llrintl, "LLiLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(llround, "LLid", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(llroundf, "LLif", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(llroundl, "LLiLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(log, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(logf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(logl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(log10, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(log10f, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(log10l, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(log1p, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(log1pf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(log1pl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(log2, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(log2f, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(log2l, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(logb, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(logbf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(logbl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(lrint, "Lid", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(lrintf, "Lif", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(lrintl, "LiLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(lround, "Lid", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(lroundf, "Lif", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(lroundl, "LiLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(nearbyint, "dd", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(nearbyintf, "ff", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(nearbyintl, "LdLd", "fnc", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(nextafter, "ddd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(nextafterf, "fff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(nextafterl, "LdLdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(nexttoward, "ddLd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(nexttowardf, "ffLd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(nexttowardl, "LdLdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(remainder, "ddd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(remainderf, "fff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(remainderl, "LdLdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(remquo, "dddi*", "fn", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(remquof, "fffi*", "fn", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(remquol, "LdLdLdi*", "fn", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(rint, "dd", "fng", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(rintf, "ff", "fng", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(rintl, "LdLd", "fng", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(round, "dd", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(roundf, "ff", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(roundl, "LdLd", "fnc", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(roundeven, "dd", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(roundevenf, "ff", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(roundevenl, "LdLd", "fnc", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(scalbln, "ddLi", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(scalblnf, "ffLi", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(scalblnl, "LdLdLi", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(scalbn, "ddi", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(scalbnf, "ffi", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(scalbnl, "LdLdi", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(sin, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(sinf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(sinl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(sinh, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(sinhf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(sinhl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(sqrt, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(sqrtf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(sqrtl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(tan, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(tanf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(tanl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(tanh, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(tanhf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(tanhl, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(tgamma, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(tgammaf, "ff", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(tgammal, "LdLd", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(trunc, "dd", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(truncf, "ff", "fnc", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(truncl, "LdLd", "fnc", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(cabs, "dXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cabsf, "fXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cabsl, "LdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(cacos, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cacosf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cacosl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(cacosh, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cacoshf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cacoshl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(carg, "dXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cargf, "fXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cargl, "LdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(casin, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(casinf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(casinl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(casinh, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(casinhf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(casinhl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(catan, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(catanf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(catanl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(catanh, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(catanhf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(catanhl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(ccos, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(ccosf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(ccosl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(ccosh, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(ccoshf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(ccoshl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(cexp, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cexpf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cexpl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(cimag, "dXd", "fnc", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cimagf, "fXf", "fnc", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cimagl, "LdXLd", "fnc", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(conj, "XdXd", "fnc", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(conjf, "XfXf", "fnc", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(conjl, "XLdXLd", "fnc", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(clog, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(clogf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(clogl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(cproj, "XdXd", "fnc", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cprojf, "XfXf", "fnc", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cprojl, "XLdXLd", "fnc", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(cpow, "XdXdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cpowf, "XfXfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(cpowl, "XLdXLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(creal, "dXd", "fnc", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(crealf, "fXf", "fnc", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(creall, "LdXLd", "fnc", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(csin, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(csinf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(csinl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(csinh, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(csinhf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(csinhl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(csqrt, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(csqrtf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(csqrtl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(ctan, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(ctanf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(ctanl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

LIBBUILTIN(ctanh, "XdXd", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(ctanhf, "XfXf", "fne", COMPLEX_H, ALL_LANGUAGES)
LIBBUILTIN(ctanhl, "XLdXLd", "fne", COMPLEX_H, ALL_LANGUAGES)

// __sinpi and friends are OS X specific library functions, but otherwise much
// like the standard (non-complex) sin (etc).
LIBBUILTIN(__sinpi, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(__sinpif, "ff", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(__cospi, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(__cospif, "ff", "fne", MATH_H, ALL_LANGUAGES)

LIBBUILTIN(__tanpi, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(__tanpif, "ff", "fne", MATH_H, ALL_LANGUAGES)

// Similarly, __exp10 is OS X only
LIBBUILTIN(__exp10, "dd", "fne", MATH_H, ALL_LANGUAGES)
LIBBUILTIN(__exp10f, "ff", "fne", MATH_H, ALL_LANGUAGES)

// Blocks runtime Builtin math library functions
LIBBUILTIN(_Block_object_assign, "vv*vC*iC", "f", BLOCKS_H, ALL_LANGUAGES)
LIBBUILTIN(_Block_object_dispose, "vvC*iC", "f", BLOCKS_H, ALL_LANGUAGES)
// FIXME: Also declare NSConcreteGlobalBlock and NSConcreteStackBlock.

// C++ standard library builtins in namespace 'std'.
LIBBUILTIN(addressof, "v*v&", "zfncThE", MEMORY, CXX_LANG)
// Synonym for addressof used internally by libstdc++.
LANGBUILTIN(__addressof, "v*v&", "zfncTE", CXX_LANG)
LIBBUILTIN(as_const, "v&v&", "zfncThE", UTILITY, CXX_LANG)
LIBBUILTIN(forward, "v&v&", "zfncThE", UTILITY, CXX_LANG)
LIBBUILTIN(forward_like, "v&v&", "zfncThE", UTILITY, CXX_LANG)
LIBBUILTIN(move, "v&v&", "zfncThE", UTILITY, CXX_LANG)
LIBBUILTIN(move_if_noexcept, "v&v&", "zfncThE", UTILITY, CXX_LANG)

// Annotation function
BUILTIN(__builtin_annotation, "v.", "tn")

// Invariants
BUILTIN(__builtin_assume, "vb", "nE")
BUILTIN(__builtin_assume_separate_storage, "vvCD*vCD*", "nE")

// Multiprecision Arithmetic Builtins.
BUILTIN(__builtin_addcb, "UcUcCUcCUcCUc*", "n")
BUILTIN(__builtin_addcs, "UsUsCUsCUsCUs*", "n")
BUILTIN(__builtin_addc, "UiUiCUiCUiCUi*", "n")
BUILTIN(__builtin_addcl, "ULiULiCULiCULiCULi*", "n")
BUILTIN(__builtin_addcll, "ULLiULLiCULLiCULLiCULLi*", "n")
BUILTIN(__builtin_subcb, "UcUcCUcCUcCUc*", "n")
BUILTIN(__builtin_subcs, "UsUsCUsCUsCUs*", "n")
BUILTIN(__builtin_subc, "UiUiCUiCUiCUi*", "n")
BUILTIN(__builtin_subcl, "ULiULiCULiCULiCULi*", "n")
BUILTIN(__builtin_subcll, "ULLiULLiCULLiCULLiCULLi*", "n")

// Checked Arithmetic Builtins for Security.
BUILTIN(__builtin_add_overflow, "b.", "ntE")
BUILTIN(__builtin_sub_overflow, "b.", "ntE")
BUILTIN(__builtin_mul_overflow, "b.", "ntE")
BUILTIN(__builtin_uadd_overflow, "bUiCUiCUi*", "nE")
BUILTIN(__builtin_uaddl_overflow, "bULiCULiCULi*", "nE")
BUILTIN(__builtin_uaddll_overflow, "bULLiCULLiCULLi*", "nE")
BUILTIN(__builtin_usub_overflow, "bUiCUiCUi*", "nE")
BUILTIN(__builtin_usubl_overflow, "bULiCULiCULi*", "nE")
BUILTIN(__builtin_usubll_overflow, "bULLiCULLiCULLi*", "nE")
BUILTIN(__builtin_umul_overflow, "bUiCUiCUi*", "nE")
BUILTIN(__builtin_umull_overflow, "bULiCULiCULi*", "nE")
BUILTIN(__builtin_umulll_overflow, "bULLiCULLiCULLi*", "nE")
BUILTIN(__builtin_sadd_overflow, "bSiCSiCSi*", "nE")
BUILTIN(__builtin_saddl_overflow, "bSLiCSLiCSLi*", "nE")
BUILTIN(__builtin_saddll_overflow, "bSLLiCSLLiCSLLi*", "nE")
BUILTIN(__builtin_ssub_overflow, "bSiCSiCSi*", "nE")
BUILTIN(__builtin_ssubl_overflow, "bSLiCSLiCSLi*", "nE")
BUILTIN(__builtin_ssubll_overflow, "bSLLiCSLLiCSLLi*", "nE")
BUILTIN(__builtin_smul_overflow, "bSiCSiCSi*", "nE")
BUILTIN(__builtin_smull_overflow, "bSLiCSLiCSLi*", "nE")
BUILTIN(__builtin_smulll_overflow, "bSLLiCSLLiCSLLi*", "nE")

// Clang builtins (not available in GCC).
BUILTIN(__builtin_addressof, "v*v&", "nctE")
BUILTIN(__builtin_function_start, "v*v&", "nctE")
BUILTIN(__builtin_operator_new, "v*z", "tcE")
BUILTIN(__builtin_operator_delete, "vv*", "tnE")
BUILTIN(__builtin_char_memchr, "c*cC*iz", "nE")
BUILTIN(__builtin_dump_struct, "v.", "t")
BUILTIN(__builtin_preserve_access_index, "v.", "t")

// Alignment builtins (uses custom parsing to support pointers and integers)
BUILTIN(__builtin_is_aligned, "bvC*z", "nctE")
BUILTIN(__builtin_align_up, "v*vC*z", "nctE")
BUILTIN(__builtin_align_down, "v*vC*z", "nctE")

// Safestack builtins
BUILTIN(__builtin___get_unsafe_stack_start, "v*", "Fn")
BUILTIN(__builtin___get_unsafe_stack_bottom, "v*", "Fn")
BUILTIN(__builtin___get_unsafe_stack_top, "v*", "Fn")
BUILTIN(__builtin___get_unsafe_stack_ptr, "v*", "Fn")

// Nontemporal loads/stores builtins
BUILTIN(__builtin_nontemporal_store, "v.", "t")
BUILTIN(__builtin_nontemporal_load, "v.", "t")

// Coroutine intrinsics.
LANGBUILTIN(__builtin_coro_resume, "vv*", "", COR_LANG)
LANGBUILTIN(__builtin_coro_destroy, "vv*", "", COR_LANG)
LANGBUILTIN(__builtin_coro_done, "bv*", "n", COR_LANG)
LANGBUILTIN(__builtin_coro_promise, "v*v*IiIb", "n", COR_LANG)

LANGBUILTIN(__builtin_coro_size, "z", "n", COR_LANG)
LANGBUILTIN(__builtin_coro_align, "z", "n", COR_LANG)
LANGBUILTIN(__builtin_coro_frame, "v*", "n", COR_LANG)
LANGBUILTIN(__builtin_coro_noop, "v*", "n", COR_LANG)
LANGBUILTIN(__builtin_coro_free, "v*v*", "n", COR_LANG)

LANGBUILTIN(__builtin_coro_id, "v*Iiv*v*v*", "n", COR_LANG)
LANGBUILTIN(__builtin_coro_alloc, "b", "n", COR_LANG)
LANGBUILTIN(__builtin_coro_begin, "v*v*", "n", COR_LANG)
LANGBUILTIN(__builtin_coro_end, "bv*Ib", "n", COR_LANG)
LANGBUILTIN(__builtin_coro_suspend, "cIb", "n", COR_LANG)

// OpenCL v2.0 s6.13.16, s9.17.3.5 - Pipe functions.
// We need the generic prototype, since the packet type could be anything.
LANGBUILTIN(read_pipe, "i.", "tn", OCL_PIPE)
LANGBUILTIN(write_pipe, "i.", "tn", OCL_PIPE)

LANGBUILTIN(reserve_read_pipe, "i.", "tn", OCL_PIPE)
LANGBUILTIN(reserve_write_pipe, "i.", "tn", OCL_PIPE)

LANGBUILTIN(commit_write_pipe, "v.", "tn", OCL_PIPE)
LANGBUILTIN(commit_read_pipe, "v.", "tn", OCL_PIPE)

LANGBUILTIN(sub_group_reserve_read_pipe, "i.", "tn", OCL_PIPE)
LANGBUILTIN(sub_group_reserve_write_pipe, "i.", "tn", OCL_PIPE)

LANGBUILTIN(sub_group_commit_read_pipe, "v.", "tn", OCL_PIPE)
LANGBUILTIN(sub_group_commit_write_pipe, "v.", "tn", OCL_PIPE)

LANGBUILTIN(work_group_reserve_read_pipe, "i.", "tn", OCL_PIPE)
LANGBUILTIN(work_group_reserve_write_pipe, "i.", "tn", OCL_PIPE)

LANGBUILTIN(work_group_commit_read_pipe, "v.", "tn", OCL_PIPE)
LANGBUILTIN(work_group_commit_write_pipe, "v.", "tn", OCL_PIPE)

LANGBUILTIN(get_pipe_num_packets, "Ui.", "tn", OCL_PIPE)
LANGBUILTIN(get_pipe_max_packets, "Ui.", "tn", OCL_PIPE)

// OpenCL v2.0 s6.13.17 - Enqueue kernel functions.
// Custom builtin check allows to perform special check of passed block
// arguments.
LANGBUILTIN(enqueue_kernel, "i.", "tn", OCL_DSE)
LANGBUILTIN(get_kernel_work_group_size, "Ui.", "tn", OCL_DSE)
LANGBUILTIN(get_kernel_preferred_work_group_size_multiple, "Ui.", "tn", OCL_DSE)
LANGBUILTIN(get_kernel_max_sub_group_size_for_ndrange, "Ui.", "tn", OCL_DSE)
LANGBUILTIN(get_kernel_sub_group_count_for_ndrange, "Ui.", "tn", OCL_DSE)

// OpenCL v2.0 s6.13.9 - Address space qualifier functions.
// FIXME: Pointer parameters of OpenCL builtins should have their address space
// requirement defined.
LANGBUILTIN(to_global, "v*v*", "tn", OCL_GAS)
LANGBUILTIN(to_local, "v*v*", "tn", OCL_GAS)
LANGBUILTIN(to_private, "v*v*", "tn", OCL_GAS)

// OpenCL half load/store builtin
LANGBUILTIN(__builtin_store_half, "vdh*", "n", ALL_OCL_LANGUAGES)
LANGBUILTIN(__builtin_store_halff, "vfh*", "n", ALL_OCL_LANGUAGES)
LANGBUILTIN(__builtin_load_half, "dhC*", "nc", ALL_OCL_LANGUAGES)
LANGBUILTIN(__builtin_load_halff, "fhC*", "nc", ALL_OCL_LANGUAGES)

// Builtins for os_log/os_trace
BUILTIN(__builtin_os_log_format_buffer_size, "zcC*.", "p:0:nutE")
BUILTIN(__builtin_os_log_format, "v*v*cC*.", "p:0:nt")

// CUDA/HIP
LANGBUILTIN(__builtin_get_device_side_mangled_name, "cC*.", "ncT", CUDA_LANG)

// HLSL
LANGBUILTIN(__builtin_hlsl_wave_active_count_bits, "Uib", "nc", HLSL_LANG)
LANGBUILTIN(__builtin_hlsl_create_handle, "v*Uc", "nc", HLSL_LANG)

// Builtins for XRay
BUILTIN(__xray_customevent, "vcC*z", "")
BUILTIN(__xray_typedevent, "vzcC*z", "")

// Win64-compatible va_list functions
BUILTIN(__builtin_ms_va_start, "vc*&.", "nt")
BUILTIN(__builtin_ms_va_end, "vc*&", "n")
BUILTIN(__builtin_ms_va_copy, "vc*&c*&", "n")

// Arithmetic Fence: to prevent FP reordering and reassociation optimizations
LANGBUILTIN(__arithmetic_fence, "v.", "tE", ALL_LANGUAGES)

#undef BUILTIN
#undef LIBBUILTIN
#undef LANGBUILTIN