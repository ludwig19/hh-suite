// SIMD helper
// optimze based on technolegy double, float and integer (32) SIMD instructions
// writen by Martin Steinegger

#include <limits>
#include <algorithm>
#include <iostream>

#ifndef SIMD_H
#define SIMD_H
#include <stdlib.h>

#include "log.h"

#ifdef AVX512
#define AVX2
#endif

#ifdef AVX2
#define AVX
#endif

#ifdef AVX
#define SSE
#endif

#ifdef AVX512
#include <zmmintrin.h.h> // AVX512
// double support
#ifndef SIMD_DOUBLE
#define SIMD_DOUBLE
#define ALIGN_DOUBLE    64
#define VECSIZE_DOUBLE  8
typedef __m512d simd_double;
#define simdf64_add(x,y)    _mm512_add_pd(x,y)
#define simdf64_sub(x,y)    _mm512_sub_pd(x,y)
#define simdf64_mul(x,y)    _mm512_mul_pd(x,y)
#define simdf64_div(x,y)    _mm512_div_pd(x,y)
#define simdf64_max(x,y)    _mm512_max_pd(x,y)
#define simdf64_load(x)     _mm512_load_pd(x)
#define simdf64_store(x,y)  _mm512_store_pd(x,y)
#define simdf64_set(x)      _mm512_set1_pd(x)
#define simdf64_set2(x,y)   _mm512_set_pd(x,y,x,y,x,y,x,y)
#define simdf64_set4(x,y,z,t) _mm512_set_pd(x,y,z,t,x,y,z,t)
#define simdf64_set8(x0,x1,x2,x3,x4,x5,x6,x7) _mm512_set_pd(x0,x1,x2,x3,x4,x5,x6,x7)
#define simdf64_setzero(x)  _mm512_setzero_pd()
#define simdf64_gt(x,y)     _mm512_cmpnle_pd_mask(x,y)
#define simdf64_lt(x,y)     _mm512_cmplt_pd_mask(x,y)
#define simdf64_or(x,y)     _mm512_or_si512(x,y)
#define simdf64_and(x,y)    _mm512_and_si512 (x,y)
#define simdf64_andnot(x,y) _mm512_andnot_si512(x,y)
#define simdf64_xor(x,y)    _mm512_xor_si512(x,y)
#endif //SIMD_DOUBLE
// float support
#ifndef SIMD_FLOAT
#define SIMD_FLOAT
#define ALIGN_FLOAT     64
#define VECSIZE_FLOAT   16
typedef __m512  simd_float;
#define simdf32_add(x,y)    _mm512_add_ps(x,y)
#define simdf32_sub(x,y)    _mm512_sub_ps(x,y)
#define simdf32_mul(x,y)    _mm512_mul_ps(x,y)
#define simdf32_div(x,y)    _mm512_div_ps(x,y)
#define simdf32_max(x,y)    _mm512_max_ps(x,y)
#define simdf32_min(x,y)    _mm512_min_ps(x,y)
#define simdf32_rcp(x)      _mm512_rcp14_ps(x)
#define simdf32_load(x)     _mm512_load_ps(x)
#define simdf32_store(x,y)  _mm512_store_ps(x,y)
#define simdf32_set(x)      _mm512_set1_ps(x)
#define simdf32_set2(x,y)   _mm512_set_ps(x,y,x,y,x,y,x,y,x,y,x,y,x,y,x,y)
#define simdf32_set4(x,y,z,t) _mm512_set_ps(x,y,z,t,x,y,z,t,x,y,z,t,x,y,z,t)
#define simdf32_set8(x0,x1,x2,x3,x4,x5,x6,x7) _mm512_set_ps(x0,x1,x2,x3,x4,x5,x6,x7,x0,x1,x2,x3,x4,x5,x6,x7)
#define simdf32_setzero(x)  _mm512_setzero_ps()
#define simdf32_gt(x,y)     _mm512_cmpnle_ps_mask(x,y)
#define simdf32_eq(x,y)     _mm512_cmpeq_ps_mask(x,y)
#define simdf32_lt(x,y)     _mm512_cmplt_ps_mask(x,y)
#define simdf32_or(x,y)     _mm512_or_si512(x,y)
#define simdf32_and(x,y)    _mm512_and_si512(x,y)
#define simdf32_andnot(x,y) _mm512_andnot_si512(x,y)
#define simdf32_xor(x,y)    _mm512_xor_si512(x,y)
#define simdf32_f2i(x) 	    _mm512_cvtps_epi32(x)  // convert s.p. float to integer
#define simdf_f2icast(x)    _mm512_castps_si512 (x)
#endif //SIMD_FLOAT
// integer support 
#ifndef SIMD_INT
#define SIMD_INT
#define ALIGN_INT       64
#define VECSIZE_INT     16
typedef __m512i simd_int;
#define simdi32_add(x,y)    _mm512_add_epi32(x,y)
#define simdui8_adds(x,y)   NOT_YET_IMP()
#define simdi32_sub(x,y)    _mm512_sub_epi32(x,y)
#define simdui8_subs(x,y)   NOT_YET_IMP()
#define simdi32_mul(x,y)    _mm512_mullo_epi32(x,y)
#define simdi32_max(x,y)    _mm512_max_epi32(x,y) 
#define simdui8_max(x,y)    NOT_YET_IMP()
#define simdi_load(x)       _mm512_load_si512(x)
#define simdi_store(x,y)    _mm512_store_si512(x,y)
#define simdi32_set(x)      _mm512_set1_epi32(x)
#define simdi32_set2(x,y)   _mm512_set_epi32(x,y,x,y,x,y,x,y,x,y,x,y,x,y,x,y)
#define simdi32_set4(x,y,z,t) _mm512_set_epi32(x,y,z,t,x,y,z,t,x,y,z,t,x,y,z,t)
#define simdi32_set8(x0,x1,x2,x3,x4,x5,x6,x7) _mm512_set_epi32(x0,x1,x2,x3,x4,x5,x6,x7,x0,x1,x2,x3,x4,x5,x6,x7)
#define simdi8_set(x)       _mm512_set1_epi8(x)
#define simdi_setzero(x)    _mm512_setzero_si512()
#define simdi32_gt(x,y)     _mm512_cmpgt_epi32(x,y)
#define simdi8_gt(x,y)      NOT_YET_IMP()
#define simdi8_eq(x,y)      NOT_YET_IMP()
#define simdi32_lt(x,y)     _mm512_cmplt_epi32(x,y)
#define simdi_or(x,y)       _mm512_or_si512(x,y)
#define simdi_and(x,y)      _mm512_and_si512(x,y)
#define simdi_andnot(x,y)   _mm512_andnot_si512(x,y)
#define simdi_xor(x,y)      _mm512_xor_si512(x,y)
#define simdi8_shiftl(x,y)  NOT_YET_IMP()
#define simdi8_shiftr(x,y)  NOT_YET_IMP()
#define simdi8_movemask(x)  NOT_YET_IMP()
#define simdi32_slli(x,y)	_mm512_slli_epi32(x,y) // shift integers in a left by y
#define simdi32_srli(x,y)	_mm512_srli_epi32(x,y) // shift integers in a right by y
#define simdi32_i2f(x) 	    _mm512_cvtepi32_ps(x)  // convert integer to s.p. float
#define simdi_i2fcast(x)    _mm512_castsi512_ps(x)

#endif //SIMD_INT
#endif //AVX512_SUPPORT

#ifdef AVX2
// integer support  (usable with AVX2)
#ifndef SIMD_INT
#define SIMD_INT
#include <immintrin.h> // AVX
#define ALIGN_INT   32
#define VECSIZE_INT 8

template  <unsigned int N> __m256i _mm256_shift_left(__m256i a)
{
    __m256i mask = _mm256_permute2x128_si256(a, a, _MM_SHUFFLE(0,0,3,0) );
    return _mm256_alignr_epi8(a,mask,16-N); 
}


typedef __m256i simd_int;
#define simdi32_add(x,y)    _mm256_add_epi32(x,y)
#define simdui8_adds(x,y)   _mm256_adds_epu8(x,y)
#define simdi32_sub(x,y)    _mm256_sub_epi32(x,y) 
#define simdui8_subs(x,y)   _mm256_subs_epu8(x,y)
//TODO add unsigned in mmseqs and hhblits
#define simdi32_mul(x,y)    _mm256_mullo_epi32 (x,y)
#define simdi32_max(x,y)    _mm256_max_epi32(x,y) 
#define simdui8_max(x,y)    _mm256_max_epu8(x,y)
#define simdi_load(x)       _mm256_load_si256(x)
#define simdi_store(x,y)    _mm256_store_si256(x,y)
#define simdi32_set(x)      _mm256_set1_epi32(x)
#define simdi32_set2(x,y)   _mm256_set_epi32(x,y,x,y,x,y,x,y)
#define simdi32_set4(x,y,z,t) _mm256_set_epi32(x,y,z,t,x,y,z,t)
#define simdi32_set8(x0,x1,x2,x3,x4,x5,x6,x7) _mm256_set_epi32(x0,x1,x2,x3,x4,x5,x6,x7)
#define simdi8_set(x)       _mm256_set1_epi8(x)
#define simdi_setzero(x)    _mm256_setzero_si256()
#define simdi32_gt(x,y)     _mm256_cmpgt_epi32(x,y)
#define simdi8_gt(x,y)      _mm256_cmpgt_epi8(x,y)
#define simdi8_eq(x,y)      _mm256_cmpeq_epi8(x,y)
#define simdi32_lt(x,y)     _mm256_cmpgt_epi32(y,x) // inverse
#define simdi_or(x,y)       _mm256_or_si256(x,y)
#define simdi_and(x,y)      _mm256_and_si256(x,y)
#define simdi_andnot(x,y)   _mm256_andnot_si256(x,y)
#define simdi_xor(x,y)      _mm256_xor_si256(x,y)
#define simdi8_shiftl(x,y)  _mm256_shift_left<y>(x)
#define simdi8_shiftr(x,y)  _mm256_srli_si256(x,y)
#define simdi8_movemask(x)  _mm256_movemask_epi8(x)
#define simdi32_slli(x,y)   _mm256_slli_epi32(x,y) // shift integers in a left by y
#define simdi32_srli(x,y)   _mm256_srli_epi32(x,y) // shift integers in a right by y
#define simdi32_i2f(x) 	    _mm256_cvtepi32_ps(x)  // convert integer to s.p. float
#define simdi_i2fcast(x)    _mm256_castsi256_ps(x)
#endif //SIMD_INT
#endif //AVX2

#ifdef AVX
#include <immintrin.h> // AVX
// double support (usable with AVX1)
#ifndef SIMD_DOUBLE
#define SIMD_DOUBLE
#define ALIGN_DOUBLE   32
#define VECSIZE_DOUBLE 4
typedef __m256d simd_double;
#define simdf64_add(x,y)    _mm256_add_pd(x,y)
#define simdf64_sub(x,y)    _mm256_sub_pd(x,y)
#define simdf64_mul(x,y)    _mm256_mul_pd(x,y)
#define simdf64_div(x,y)    _mm256_div_pd(x,y)
#define simdf64_max(x,y)    _mm256_max_pd(x,y)
#define simdf64_load(x)     _mm256_load_pd(x)
#define simdf64_store(x,y)  _mm256_store_pd(x,y)
#define simdf64_set(x)      _mm256_set1_pd(x)
#define simdf64_set2(x,y)   _mm256_set_pd(x,y,x,y)
#define simdf64_set4(x,y,z,t) _mm256_set_pd(x,y,z,t)
#define simdf64_setzero(x)  _mm256_setzero_pd()
#define simdf64_gt(x,y)     _mm256_cmp_pd(x,y,_CMP_GT_OS)
#define simdf64_lt(x,y)     _mm256_cmp_pd(x,y,_CMP_LT_OS)
#define simdf64_or(x,y)     _mm256_or_pd(x,y)
#define simdf64_and(x,y)    _mm256_and_pd(x,y)
#define simdf64_andnot(x,y) _mm256_andnot_pd(x,y)
#define simdf64_xor(x,y)    _mm256_xor_pd(x,y)
#endif //SIMD_DOUBLE
// float support (usable with AVX1)
#ifndef SIMD_FLOAT
#define SIMD_FLOAT
#define ALIGN_FLOAT    32
#define VECSIZE_FLOAT  8
typedef __m256 simd_float;
#define simdf32_add(x,y)    _mm256_add_ps(x,y)
#define simdf32_sub(x,y)    _mm256_sub_ps(x,y)
#define simdf32_mul(x,y)    _mm256_mul_ps(x,y)
#define simdf32_div(x,y)    _mm256_div_ps(x,y)
#define simdf32_max(x,y)    _mm256_max_ps(x,y)
#define simdf32_min(x,y)    _mm256_min_ps(x,y)
#define simdf32_rcp(x)      _mm256_rcp_ps(x)
#define simdf32_load(x)     _mm256_load_ps(x)
#define simdf32_store(x,y)  _mm256_store_ps(x,y)
#define simdf32_set(x)      _mm256_set1_ps(x)
#define simdf32_set2(x,y)   _mm256_set_ps(x,y,x,y,x,y,x,y)
#define simdf32_set4(x,y,z,t) _mm256_set_ps(x,y,z,t,x,y,z,t)
#define simdf32_set8(x0,x1,x2,x3,x4,x5,x6,x7) _mm256_set_ps(x0,x1,x2,x3,x4,x5,x6,x7)
#define simdf32_setzero(x)  _mm256_setzero_ps()
#define simdf32_gt(x,y)     _mm256_cmp_ps(x,y,_CMP_GT_OS)
#define simdf32_eq(x,y)     _mm256_cmp_ps(x,y,_CMP_EQ_OS)
#define simdf32_lt(x,y)     _mm256_cmp_ps(x,y,_CMP_LT_OS)
#define simdf32_or(x,y)     _mm256_or_ps(x,y)
#define simdf32_and(x,y)    _mm256_and_ps(x,y)
#define simdf32_andnot(x,y) _mm256_andnot_ps(x,y)
#define simdf32_xor(x,y)    _mm256_xor_ps(x,y)
#define simdf32_f2i(x) 	    _mm256_cvtps_epi32(x)  // convert s.p. float to integer
#define simdf32_extract(x,imm) _mm_extract_ps(_mm256_castps256_ps128(x),imm)
#define simdf_f2icast(x)    _mm256_castps_si256(x) // compile time cast
#endif //SIMD_FLOAT
#endif //AVX_SUPPORT


#ifdef SSE
#include <xmmintrin.h> // SSE
#include <emmintrin.h> // SSE2
// double support
#ifndef SIMD_DOUBLE
#define SIMD_DOUBLE
#define ALIGN_DOUBLE    16
#define VECSIZE_DOUBLE  2
typedef __m128d simd_double;
#define simdf64_add(x,y)    _mm_add_pd(x,y)
#define simdf64_sub(x,y)    _mm_sub_pd(x,y)
#define simdf64_mul(x,y)    _mm_mul_pd(x,y)
#define simdf64_div(x,y)    _mm_div_pd(x,y)
#define simdf64_max(x,y)    _mm_max_pd(x,y)
#define simdf64_load(x)     _mm_load_pd(x)
#define simdf64_store(x,y)  _mm_store_pd(x,y)
#define simdf64_set(x)      _mm_set1_pd(x)
#define simdf64_set2(x,y)   _mm_set_ps(x,y)
#define simdf64_setzero(x)  _mm_setzero_pd()
#define simdf64_gt(x,y)     _mm_cmpgt_pd(x,y)
#define simdf64_lt(x,y)     _mm_cmplt_pd(x,y)
#define simdf64_or(x,y)     _mm_or_pd(x,y)
#define simdf64_and(x,y)    _mm_and_pd(x,y)
#define simdf64_andnot(x,y) _mm_andnot_pd(x,y)
#define simdf64_xor(x,y)    _mm_xor_pd(x,y)
#endif //SIMD_DOUBLE

// float support
#ifndef SIMD_FLOAT
#define SIMD_FLOAT
#define ALIGN_FLOAT     16
#define VECSIZE_FLOAT   4
typedef __m128  simd_float;
#define simdf32_add(x,y)    _mm_add_ps(x,y)
#define simdf32_sub(x,y)    _mm_sub_ps(x,y)
#define simdf32_mul(x,y)    _mm_mul_ps(x,y)
#define simdf32_div(x,y)    _mm_div_ps(x,y)
#define simdf32_max(x,y)    _mm_max_ps(x,y)
#define simdf32_min(x,y)    _mm_min_ps(x,y)
#define simdf32_rcp(x)      _mm_rcp_ps(x)
#define simdf32_load(x)     _mm_load_ps(x)
#define simdf32_store(x,y)  _mm_store_ps(x,y)
#define simdf32_set(x)      _mm_set1_ps(x)
#define simdf32_set2(x,y)   _mm_set_ps(x,y,x,y)
#define simdf32_set4(x,y,z,t) _mm_set_ps(x,y,z,t)
#define simdf32_setzero(x)  _mm_setzero_ps()
#define simdf32_gt(x,y)     _mm_cmpgt_ps(x,y)
#define simdf32_eq(x,y)     _mm_cmpeq_ps(x,y)
#define simdf32_lt(x,y)     _mm_cmplt_ps(x,y)
#define simdf32_or(x,y)     _mm_or_ps(x,y)
#define simdf32_and(x,y)    _mm_and_ps(x,y)
#define simdf32_andnot(x,y) _mm_andnot_ps(x,y)
#define simdf32_xor(x,y)    _mm_xor_ps(x,y)
#define simdf32_f2i(x) 	    _mm_cvtps_epi32(x)  // convert s.p. float to integer
#define simdf32_extract(x,imm) _mm_extract_ps(x,imm)
#define simdf_f2icast(x)    _mm_castps_si128(x) // compile time cast
#endif //SIMD_FLOAT
// integer support 
#ifndef SIMD_INT
#define SIMD_INT
#define ALIGN_INT       16
#define VECSIZE_INT     4
typedef __m128i simd_int;
#define simdi32_add(x,y)    _mm_add_epi32(x,y)
#define simdui8_adds(x,y)   _mm_adds_epu8(x,y)
#define simdi32_sub(x,y)    _mm_sub_epi32(x,y)
#define simdui8_subs(x,y)   _mm_subs_epu8(x,y)
#define simdi32_mul(x,y)    _mm_mullo_epi32(x,y) // SSE4.1 (no overflow protection)
#define simdi32_max(x,y)    _mm_max_epi32(x,y) // SSE4.1
#define simdui8_max(x,y)    _mm_max_epu8(x,y)
#define simdi_load(x)       _mm_load_si128(x)
#define simdi_store(x,y)    _mm_store_si128(x,y)
#define simdi32_set(x)      _mm_set1_epi32(x)
#define simdi8_set(x)       _mm_set1_epi8(x)
#define simdi_setzero(x)    _mm_setzero_si128()
#define simdi32_gt(x,y)     _mm_cmpgt_epi32(x,y)
#define simdi8_gt(x,y)      _mm_cmpgt_epi8(x,y)
#define simdi8_eq(x,y)      _mm_cmpeq_epi8(x,y)
#define simdi32_lt(x,y)     _mm_cmplt_epi32(x,y)
#define simdi_or(x,y)       _mm_or_si128(x,y)
#define simdi_and(x,y)      _mm_and_si128(x,y)
#define simdi_andnot(x,y)   _mm_andnot_si128(x,y)
#define simdi_xor(x,y)      _mm_xor_si128(x,y)
#define simdi8_shiftl(x,y)  _mm_slli_si128(x,y)
#define simdi8_shiftr(x,y)  _mm_srli_si128(x,y)
#define simdi8_movemask(x)  _mm_movemask_epi8(x)
#define simdi32_slli(x,y)	_mm_slli_epi32(x,y) // shift integers in a left by y
#define simdi32_srli(x,y)	_mm_srli_epi32(x,y) // shift integers in a right by y
#define simdi32_i2f(x) 	    _mm_cvtepi32_ps(x)  // convert integer to s.p. float
#define simdi_i2fcast(x)    _mm_castsi128_ps(x)

#define simdi32_set4(x,y,z,t) _mm_set_epi32(x,y,z,t)  // Added with Power8, hhviterbialgorithm needs _set4

#endif //SIMD_INT
#endif //SSE


/*
 *  Power8/LE Altivec/VSX SIMD
 */
#ifdef __ALTIVEC__ // || __VSX__

#include <altivec.h>

// double support
#ifndef SIMD_DOUBLE
#define SIMD_DOUBLE
#define ALIGN_DOUBLE    16
#define VECSIZE_DOUBLE  2
typedef __vector double simd_double;
#define simdf64_add(x,y)    vec_add(x,y)
#define simdf64_sub(x,y)    vec_sub(x,y)
#define simdf64_mul(x,y)    vec_mul(x,y)
#define simdf64_div(x,y)    vec_div(x,y)
#define simdf64_max(x,y)    vec_max(x,y)
#define simdf64_load(x)     vec_vsx_ld(0,x)   // vec_ld
#define simdf64_store(x,y)  vec_vsx_st(y,0,x) // vec_st
#define simdf64_set(x)      vec_splats(x)
//#define simdf64_set2(x,y)   _mm_set_ps(x,y)
#define simdf64_setzero(x)  vec_splats(0)
#define simdf64_gt(x,y)     vec_cmpgt(x,y)
#define simdf64_lt(x,y)     vec_cmplt(x,y)
#define simdf64_or(x,y)     vec_or(x,y)
#define simdf64_and(x,y)    vec_and(x,y)
#define simdf64_andnot(x,y) vec_nand(x,y)
#define simdf64_xor(x,y)    vec_xor(x,y)
#endif // SIMD_DOUBLE

// float support
#ifndef SIMD_FLOAT
#define SIMD_FLOAT
#define ALIGN_FLOAT     16
#define VECSIZE_FLOAT   4
typedef __vector float simd_float;
#define simdf32_add(x,y)    x + y  //vec_add(x,y)
#define simdf32_sub(x,y)    x - y  //vec_sub(x,y)
#define simdf32_mul(x,y)    x * y  //vec_mul(x,y)
#define simdf32_div(x,y)    x / y  //vec_div(x,y)
#define simdf32_max(x,y)    vec_max(x,y)
#define simdf32_min(x,y)    vec_min(x,y)
#define simdf32_rcp(x)      vec_re(x)
#define simdf32_load(x)     vec_vsx_ld(0,x)   // vec_ld
#define simdf32_store(x,y)  vec_vsx_st(y,0,x) // vec_st
#define simdf32_set(x)      vec_splats((float)x)
//#define simdf32_set2(x,y)   _mm_set_ps(x,y)
//#define simdf32_set4(x,y,z,t)
#define simdf32_setzero(x)  vec_splats(0)
#define simdf32_gt(x,y)     (simd_float)vec_cmpgt(x,y)
#define simdf32_eq(x,y)     (simd_float)vec_cmpeq(x,y)
#define simdf32_lt(x,y)     (simd_float)vec_cmplt(x,y)
#define simdf32_or(x,y)     vec_or(x,y)
#define simdf32_and(x,y)    vec_and(x,y)
#define simdf32_andnot(x,y) vec_nand(x,y)
#define simdf32_xor(x,y)    vec_xor(x,y)
#define simdf32_extract(x,imm) vec_extract(x,imm)

#define simdf32_f2i(x)      vec_cts(x,0)  // convert s.p. float to integer
#define simdf_f2icast(x)    (simd_int)(x) // compile time cast
#endif // SIMD_FLOAT

// integer support 
#ifndef SIMD_INT
#define SIMD_INT
#define ALIGN_INT       16
#define VECSIZE_INT     4
typedef __vector int simd_int;
typedef __vector   signed char simd_s8;
typedef __vector unsigned char simd_u8;

#define simdi32_add(x,y)    vec_add(x,y)
#define simdi32_sub(x,y)    vec_sub(x,y)
#define simdi32_mul(x,y)    vec_mul(x,y)
#define simdi32_max(x,y)    vec_max(x,y)
#define simdi_load(x)       vec_vsx_ld(0,x)
#define simdi_store(x,y)    vec_vsx_st(y,0,x)
#define simdi32_set(x)      vec_splats((signed int)x)
#define simdi32_set4(x,y,z,t) (simd_int){x,y,z,t}
#define simdi_setzero(x)    vec_splats(0)
#define simdi32_gt(x,y)     (simd_int)vec_cmpgt(x,y)
#define simdi32_lt(x,y)     (simd_int)vec_cmplt(x,y)
#define simdi_or(x,y)       vec_or(x,y)
#define simdi_and(x,y)      vec_and(x,y)
#define simdi_andnot(x,y)   vec_nand(x,y)
#define simdi_xor(x,y)      vec_xor(x,y)
#define simdi32_slli(x,y)   vec_sll(x,vec_splats((unsigned)y)) // shift integers in a left by y
#define simdi32_srli(x,y)   vec_srl(x,vec_splats((unsigned)y)) // shift integers in a right by y
#define simdi32_i2f(x)      vec_ctf(x,0)  // convert integer to s.p. float
#define simdi_i2fcast(x)    (simd_float)(x)
#define simdi8_set(x)       (simd_int)vec_splats((unsigned char)x)
#define simdi8_gt(x,y)      (simd_int)vec_cmpgt((simd_s8)x,(simd_s8)y)
#define simdi8_eq(x,y)      (simd_int)vec_cmpeq((simd_s8)x,(simd_s8)y)
#define simdui8_max(x,y)    (simd_int)vec_max((vector unsigned char)x, (vector unsigned char)y)
#define simdui8_adds(x,y)   (simd_int)vec_adds((simd_u8)x,(simd_u8)y)
#define simdui8_subs(x,y)   (simd_int)vec_subs((simd_u8)x,(simd_u8)y)
#define simdi8_shiftl(x,y)   (simd_int)vec_sll(x,vec_splats((char)y)) // shift integers in a left by y
#define simdi8_shiftr(x,y)   (simd_int)vec_srl(x,vec_splats((char)y)) // shift integers in a right by y
#define simdi8_movemask(x)  v_movemask(x)


// There is no altivec/vsx equivalent, C version 
//
inline int v_movemask(simd_int x)
{
  unsigned int result=0;

  union {
    simd_int si;
    char as_char[16];
  } t;

  t.si = x;
  result |= (t.as_char[15] & 0x80) << (15-7);    
  result |= (t.as_char[14] & 0x80) << (14-7);   
  result |= (t.as_char[13] & 0x80) << (13-7);   
  result |= (t.as_char[12] & 0x80) << (12-7);   
  result |= (t.as_char[11] & 0x80) << (11-7);   
  result |= (t.as_char[10] & 0x80) << (10-7);   
  result |= (t.as_char[9]  & 0x80) <<  (9-7);   
  result |= (t.as_char[8]  & 0x80) <<  (8-7);   
  result |= (t.as_char[7]  & 0x80);   
  result |= (t.as_char[6]  & 0x80) >>  (7-6);   
  result |= (t.as_char[5]  & 0x80) >>  (7-5);   
  result |= (t.as_char[4]  & 0x80) >>  (7-4);   
  result |= (t.as_char[3]  & 0x80) >>  (7-3);   
  result |= (t.as_char[2]  & 0x80) >>  (7-2);   
  result |= (t.as_char[1]  & 0x80) >>  (7-1);   
  result |= (t.as_char[0]  & 0x80) >>   7;    

  return result;
}


#endif // SIMD_INT

#endif // __ALTIVEC__ || __VSX__





/* horizontal max */
template <typename F>
inline F simd_hmax(const F * in, unsigned int n)
{
    F current = std::numeric_limits<F>::min();
    do {
        current = std::max(current, *in++);
    } while(--n);
    
    return current;
}

/* horizontal min */
template <typename F>
inline F simd_hmin(const F * in, unsigned int n)
{
    F current = std::numeric_limits<F>::max();
    do {
        current = std::min(current, *in++);
    } while(--n);

    return current;
}

inline void *mem_align(size_t boundary, size_t size)
{
  void *pointer;
  if (posix_memalign(&pointer,boundary,size) != 0)
  {
      HH_LOG(ERROR) << "Could not allocate memory by memalign! Please report this bug to developers" << std::endl;
      exit(3);
  }
  return pointer;
}
#ifdef SIMD_FLOAT
inline simd_float * malloc_simd_float(const size_t size)
{
	return (simd_float *) mem_align(ALIGN_FLOAT,size);
}
#endif
#ifdef SIMD_DOUBLE
inline simd_double * malloc_simd_double(const size_t size)
{
	return (simd_double *) mem_align(ALIGN_DOUBLE,size);
}
#endif
#ifdef SIMD_INT
inline simd_int * malloc_simd_int(const size_t size)
{
	return (simd_int *) mem_align(ALIGN_INT,size);
}
#endif
#endif //SIMD_H
