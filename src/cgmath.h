/* C version of the graphene math library
 * Copyright (C) 2018 John Tsiombikas <nuclear@member.fsf.org>
 *
 * This program is free software. Feel free to use, modify, and/or redistribute
 * it under the terms of the MIT/X11 license. See LICENSE for details.
 * If you intend to redistribute parts of the code without the LICENSE file
 * replace this paragraph with the full contents of the LICENSE file.
 *
 * Function prefixes signify the data type of their operand(s):
 * - cgm_v... functions are operations on cgm_vec3 vectors
 * - cgm_w... functions are operations on cgm_vec4 vectors
 * - cgm_q... functions are operations on cgm_quat quaternions (w + xi + yj + zk)
 * - cgm_m... functions are operations on 4x4 matrices (stored as linear 16 float arrays)
 *
 * NOTE: *ALL* matrix arguments are pointers to 16 floats. Even the functions
 * which operate on 3x3 matrices, actually use the upper 3x3 of a 4x4 matrix,
 * and still expect an array of 16 floats.
 *
 * NOTE: matrices are treated by all operations as column-major, to match OpenGL
 * conventions, so everything is pretty much transposed.
 */
#ifndef CGMATH_H_
#define CGMATH_H_

#include <math.h>
#include <string.h>

typedef struct {
	float x, y, z;
} cgm_vec3;

typedef struct {
	float x, y, z, w;
} cgm_vec4, cgm_quat;

typedef enum cgm_euler_mode {
	CGM_EULER_XYZ,
	CGM_EULER_XZY,
	CGM_EULER_YXZ,
	CGM_EULER_YZX,
	CGM_EULER_ZXY,
	CGM_EULER_ZYX,
	CGM_EULER_ZXZ,
	CGM_EULER_ZYZ,
	CGM_EULER_YXY,
	CGM_EULER_YZY,
	CGM_EULER_XYX,
	CGM_EULER_XZX
} cgm_euler_mode;

#ifdef __cplusplus
extern "C" {
#endif

/* --- operations on cgm_vec3 --- */
static inline void cgm_vcons(cgm_vec3 *v, float x, float y, float z);

static inline void cgm_vadd(cgm_vec3 *a, const cgm_vec3 *b);
static inline void cgm_vsub(cgm_vec3 *a, const cgm_vec3 *b);
static inline void cgm_vmul(cgm_vec3 *a, const cgm_vec3 *b);
static inline void cgm_vscale(cgm_vec3 *v, float s);
static inline void cgm_vmul_m4v3(cgm_vec3 *v, const float *m);	/* m4x4 * v */
static inline void cgm_vmul_v3m4(cgm_vec3 *v, const float *m);	/* v * m4x4 */
static inline void cgm_vmul_m3v3(cgm_vec3 *v, const float *m);	/* m3x3 * v (m still 16 floats) */
static inline void cgm_vmul_v3m3(cgm_vec3 *v, const float *m);	/* v * m3x3 (m still 16 floats) */

static inline float cgm_vdot(const cgm_vec3 *a, const cgm_vec3 *b);
static inline void cgm_vcross(cgm_vec3 *res, const cgm_vec3 *a, const cgm_vec3 *b);
static inline float cgm_vlength(const cgm_vec3 *v);
static inline float cgm_vlength_sq(const cgm_vec3 *v);
static inline float cgm_vdist(const cgm_vec3 *a, const cgm_vec3 *b);
static inline float cgm_vdist_sq(const cgm_vec3 *a, const cgm_vec3 *b);
static inline void cgm_vnormalize(cgm_vec3 *v);

static inline void cgm_vreflect(cgm_vec3 *v, const cgm_vec3 *n);
static inline void cgm_vrefract(cgm_vec3 *v, const cgm_vec3 *n, float ior);

static inline void cgm_vrotate_quat(cgm_vec3 *v, const cgm_quat *q);
static inline void cgm_vrotate_axis(cgm_vec3 *v, int axis, float angle);
static inline void cgm_vrotate(cgm_vec3 *v, float angle, float x, float y, float z);
static inline void cgm_vrotate_euler(cgm_vec3 *v, float a, float b, float c, enum cgm_euler_mode mode);

static inline void cgm_vlerp(cgm_vec3 *res, const cgm_vec3 *a, const cgm_vec3 *b, float t);

/* --- operations on cgm_vec4 --- */
static inline void cgm_wcons(cgm_vec4 *v, float x, float y, float z, float w);

static inline void cgm_wadd(cgm_vec4 *a, const cgm_vec4 *b);
static inline void cgm_wsub(cgm_vec4 *a, const cgm_vec4 *b);
static inline void cgm_wmul(cgm_vec4 *a, const cgm_vec4 *b);
static inline void cgm_wscale(cgm_vec4 *v, float s);

static inline void cgm_wmul_m4v4(cgm_vec4 *v, const float *m);
static inline void cgm_wmul_v4m4(cgm_vec4 *v, const float *m);
static inline void cgm_wmul_m34v4(cgm_vec4 *v, const float *m);	/* doesn't affect w */
static inline void cgm_wmul_v4m43(cgm_vec4 *v, const float *m);	/* doesn't affect w */
static inline void cgm_wmul_m3v4(cgm_vec4 *v, const float *m); /* (m still 16 floats) */
static inline void cgm_wmul_v4m3(cgm_vec4 *v, const float *m); /* (m still 16 floats) */

static inline float cgm_wlength(const cgm_vec4 *v);
static inline float cgm_wlength_sq(const cgm_vec4 *v);
static inline float cgm_wdist(const cgm_vec4 *a, const cgm_vec4 *b);
static inline float cgm_wdist_sq(const cgm_vec4 *a, const cgm_vec4 *b);
static inline void cgm_wnormalize(cgm_vec4 *v);

static inline void cgm_wlerp(cgm_vec4 *res, const cgm_vec4 *a, const cgm_vec4 *b, float t);

/* --- operations on quaternions --- */
static inline void cgm_qcons(cgm_quat *q, float x, float y, float z, float w);

static inline void cgm_qneg(cgm_quat *q);
static inline void cgm_qadd(cgm_quat *a, const cgm_quat *b);
static inline void cgm_qsub(cgm_quat *a, const cgm_quat *b);
static inline void cgm_qmul(cgm_quat *a, const cgm_quat *b);

static inline float cgm_qlength(const cgm_quat *q);
static inline float cgm_qlength_sq(const cgm_quat *q);
static inline void cgm_qnormalize(cgm_quat *q);
static inline void cgm_qconjugate(cgm_quat *q);
static inline void cgm_qinvert(cgm_quat *q);

static inline void cgm_qrotation(cgm_quat *q, const cgm_vec3 *axis, float angle);
static inline void cgm_qrotate(cgm_quat *q, const cgm_vec3 *axis, float angle);

static inline void cgm_qslerp(cgm_quat *res, const cgm_quat *a, const cgm_quat *b, float t);
static inline void cgm_qlerp(cgm_quat *res, const cgm_quat *a, const cgm_quat *b, float t);

/* --- operations on matrices --- */
static inline void cgm_mcopy(float *dest, const float *src);
static inline void cgm_mzero(float *m);
static inline void cgm_midentity(float *m);

static inline void cgm_mmul(float *a, const float *b);

static inline void cgm_msubmatrix(float *m, int row, int col);
static inline void cgm_mupper3(float *m);
static inline float cgm_msubdet(float *m, int row, int col);
static inline float cgm_mcofactor(float *m, int row, int col);
static inline float cgm_mdet(float *m);
static inline void cgm_mtranspose(float *m);
static inline void cgm_mcofmatrix(float *m);
static inline int cgm_minverse(float *m);	/* returns 0 on success, -1 for singular */

static inline void cgm_mtranslation(float *m, float x, float y, float z);
static inline void cgm_mscaling(float *m, float sx, float sy, float sz);
static inline void cgm_mrotation_x(float *m, float angle);
static inline void cgm_mrotation_y(float *m, float angle);
static inline void cgm_mrotation_z(float *m, float angle);
static inline void cgm_mrotation_axis(float *m, int idx, float angle);
static inline void cgm_mrotation(float *m, float angle, float x, float y, float z);
static inline void cgm_mrotation_euler(float *m, float a, float b, float c, int mode);

static inline void cgm_mtranslate(float *m, float x, float y, float z);
static inline void cgm_mscale(float *m, float sx, float sy, float sz);
static inline void cgm_mrotate_x(float *m, float angle);
static inline void cgm_mrotate_y(float *m, float angle);
static inline void cgm_mrotate_z(float *m, float angle);
static inline void cgm_mrotate_axis(float *m, int idx, float angle);
static inline void cgm_mrotate(float *m, float angle, float x, float y, float z);
static inline void cgm_mrotate_euler(float *m, float a, float b, float c, int mode);

static inline void cgm_mpretranslate(float *m, float x, float y, float z);
static inline void cgm_mprescale(float *m, float sx, float sy, float sz);
static inline void cgm_mprerotate_x(float *m, float angle);
static inline void cgm_mprerotate_y(float *m, float angle);
static inline void cgm_mprerotate_z(float *m, float angle);
static inline void cgm_mprerotate_axis(float *m, int idx, float angle);
static inline void cgm_mprerotate(float *m, float angle, float x, float y, float z);
static inline void cgm_mprerotate_euler(float *m, float a, float b, float c, int mode);

#include "cgmvec3.inl"
#include "cgmvec4.inl"
#include "cgmquat.inl"
#include "cgmmat.inl"

#ifdef __cplusplus
}
#endif

#endif	/* CGMATH_H_ */
