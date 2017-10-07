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

/* vectors */
static inline void cgm_vzero(cgm_vec3 *v);
static inline void cgm_vone(cgm_vec3 *v);

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

/* quaternions */
static inline void cgm_qident(cgm_quat *q);

static inline void cgm_qneg(cgm_quat *q);
static inline void cgm_qadd(cgm_quat *a, const cgm_quat *b);
static inline void cgm_qsub(cgm_quat *a, const cgm_quat *b);
static inline void cgm_qmul(cgm_quat *a, const cgm_quat *b);

static inline float cgm_qlength(const cgm_quat *q);
static inline float cgm_qlength_sq(const cgm_quat *q);

static inline void cgm_qnormalize(cgm_quat *q);

static inline void cgm_qconjugate(cgm_quat *q);
static inline void cgm_qinvert(cgm_quat *q);

static inline void cgm_qrot_axis(cgm_quat *q, float axis, float x, float y, float z);
static inline void cgm_qrot_quat(cgm_quat *q, const cgm_quat *rq);

static inline void cgm_qmatrix(float *mat, const cgm_quat *q);

static inline void cgm_qslerp(cgm_quat *res, const cgm_quat *a, const cgm_quat *b, float t);

#include "cgmath.inl"

#endif	/* CGMATH_H_ */
