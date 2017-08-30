/* C version of the graphene math library */
#ifndef CGMATH_H_
#define CGMATH_H_

#include <math.h>

typedef struct {
	float x, y, z;
} cgm_vec3;

typedef struct {
	float x, y, z, w;
} cgm_quat;

static inline void cgm_vadd(cgm_vec3 *a, const cgm_vec3 *b);
static inline void cgm_vsub(cgm_vec3 *a, const cgm_vec3 *b);
static inline void cgm_vmul(cgm_vec3 *a, const cgm_vec3 *b);
static inline void cgm_vscale(cgm_vec3 *v, float s);

static inline float cgm_vdot(const cgm_vec3 *a, const cgm_vec3 *b);
static inline void cgm_vcross(cgm_vec3 *res, const cgm_vec3 *a, const cgm_vec3 *b);
static inline float cgm_vlength(const cgm_vec3 *v);
static inline float cgm_vlength_sq(const cgm_vec3 *v);
static inline float cgm_vdist(const cgm_vec3 *a, const cgm_vec3 *b);
static inline float cgm_vdist_sq(const cgm_vec3 *a, const cgm_vec3 *b);
static inline void cgm_vnormalize(cgm_vec3 *v);

#include "cgmath.inl"

#endif	/* CGMATH_H_ */
