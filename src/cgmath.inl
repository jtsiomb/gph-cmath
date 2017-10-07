static inline void cgm_vzero(cgm_vec3 *v)
{
	v->x = v->y = v->z = 0.0f;
}

static inline void cgm_vone(cgm_vec3 *v)
{
	v->x = v->y = v->z = 1.0f;
}

static inline void cgm_vadd(cgm_vec3 *a, const cgm_vec3 *b)
{
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
}

static inline void cgm_vsub(cgm_vec3 *a, const cgm_vec3 *b)
{
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
}

static inline void cgm_vmul(cgm_vec3 *a, const cgm_vec3 *b)
{
	a->x *= b->x;
	a->y *= b->y;
	a->z *= b->z;
}

static inline void cgm_vscale(cgm_vec3 *v, float s)
{
	v->x *= s;
	v->y *= s;
	v->z *= s;
}

static inline float cgm_vdot(const cgm_vec3 *a, const cgm_vec3 *b)
{
	return a->x * b->x + a->y * b->y + a->z * b->z;
}

static inline void cgm_vcross(cgm_vec3 *res, const cgm_vec3 *a, const cgm_vec3 *b)
{
	res->x = a->y * b->z - a->z * b->y;
	res->y = a->z * b->x - a->x * b->z;
	res->z = a->x * b->y - a->y * b->x;
}

static inline float cgm_vlength(const cgm_vec3 *v)
{
	return sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
}

static inline float cgm_vlength_sq(const cgm_vec3 *v)
{
	return v->x * v->x + v->y * v->y + v->z * v->z;
}

static inline float cgm_vdist(const cgm_vec3 *a, const cgm_vec3 *b)
{
	float dx = a->x - b->x;
	float dy = a->y - b->y;
	float dz = a->z - b->z;
	return sqrt(dx * dx + dy * dy + dz * dz);
}

static inline float cgm_vdist_sq(const cgm_vec3 *a, const cgm_vec3 *b)
{
	float dx = a->x - b->x;
	float dy = a->y - b->y;
	float dz = a->z - b->z;
	return dx * dx + dy * dy + dz * dz;
}

static inline void cgm_vnormalize(cgm_vec3 *v)
{
	float len = cgm_vlength(v);
	if(len != 0.0f) {
		float s = 1.0f / len;
		v->x *= s;
		v->y *= s;
		v->z *= s;
	}
}

static inline void cgm_qident(cgm_quat *q)
{
	q->x = q->y = q->z = 0.0f;
	q->w = 1.0f;
}

static inline void cgm_qneg(cgm_quat *q)
{
	q->x = -q->x;
	q->y = -q->y;
	q->z = -q->z;
	q->w = -q->w;
}

static inline void cgm_qadd(cgm_quat *a, const cgm_quat *b)
{
	a->x += b->x;
	a->y += b->y;
	a->z += b->z;
	a->w += b->w;
}

static inline void cgm_qsub(cgm_quat *a, const cgm_quat *b)
{
	a->x -= b->x;
	a->y -= b->y;
	a->z -= b->z;
	a->w -= b->w;
}

static inline void cgm_qmul(cgm_quat *a, const cgm_quat *b)
{
	float axb_x = a->y * b->z - a->z * b->y;
	float axb_y = a->z * b->x - a->x * b->z;
	float axb_z = a->x * b->y - a->y * b->x;

	float im_x = a->w * b->x + b->w * a->x + axb_x;
	float im_y = a->w * b->y + b->w * a->y + axb_y;
	float im_z = a->w * b->z + b->w * a->z + axb_z;

	a->w = a->w * b->w - (a->x * b->x + a->y * b->y + a->z * b->z);
	a->x = im_x;
	a->y = im_y;
	a->z = im_z;
}

static inline float cgm_qlength(const cgm_quat *q)
{
	return sqrt(q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w);
}

static inline float cgm_qlength_sq(const cgm_quat *q)
{
	return q->x * q->x + q->y * q->y + q->z * q->z + q->w * q->w;
}

static inline void cgm_qnormalize(cgm_quat *q)
{
	float len = cgm_qlength(q);
	if(len != 0.0f) {
		float inv_len = 1.0f / len;
		q->x *= inv_len;
		q->y *= inv_len;
		q->z *= inv_len;
		q->w *= inv_len;
	}
}

static inline void cgm_qconjugate(cgm_quat *q)
{
	q->x = -q->x;
	q->y = -q->y;
	q->z = -q->z;
}

static inline void cgm_qinvert(cgm_quat *q)
{
	cgm_qconjugate(q);
	float len_sq = cgm_qlength_sq(q);
	if(len_sq != 0.0) {
		float s = 1.0f / len_sq;
		q->x *= s;
		q->y *= s;
		q->z *= s;
		q->w *= s;
	}
}

static inline void cgm_qrot_axis(cgm_quat *q, float angle, float x, float y, float z)
{
	float half_angle = angle * 0.5f;
	float sin_ha = sin(half_angle);
	q->w = cos(half_angle);
	q->x = x * sin_ha;
	q->y = y * sin_ha;
	q->z = z * sin_ha;
}

static inline void cgm_qrot_quat(cgm_quat *q, const cgm_quat *rq)
{
	cgm_quat qrot = *rq;
	cgm_quat rqconj = *rq;
	cgm_qconjugate(&rqconj);
	cgm_qmul(&qrot, q);
	cgm_qmul(&qrot, &rqconj);
	*q = qrot;
}

static inline void cgm_qmatrix(float *mat, const cgm_quat *q)
{
	float xsq2 = 2.0f * q->x * q->x;
	float ysq2 = 2.0f * q->y * q->y;
	float zsq2 = 2.0f * q->z * q->z;
	float sx = 1.0f - ysq2 - zsq2;
	float sy = 1.0f - xsq2 - zsq2;
	float sz = 1.0f - xsq2 - ysq2;

	mat[0] = sx;
	mat[1] = 2.0f * q->x * q->y + 2.0f * q->w * q->z;
	mat[2] = 2.0f * q->z * q->x - 2.0f * q->w * q->y;
	mat[3] = 0.0f;

	mat[4] = 2.0f * q->x * q->y - 2.0f * q->w * q->z;
	mat[5] = sy;
	mat[6] = 2.0f * q->y * q->z + 2.0f * q->w * q->x;
	mat[7] = 0.0f;

	mat[8] = 2.0f * q->z * q->x + 2.0f * q->w * q->y;
	mat[9] = 2.0f * q->y * q->z - 2.0f * q->w * q->x;
	mat[10] = sz;
	mat[11] = 0.0f;

	mat[12] = mat[13] = mat[14] = 0.0f;
	mat[15] = 1.0f;
}

static inline void cgm_qslerp(cgm_quat *res, const cgm_quat *a, const cgm_quat *b, float t)
{
	cgm_quat qa = *a;
	float dot = a->x * b->x + a->y * b->y + a->z * b->z + a->w * b->w;
	float angle, sin_angle, ta, tb;

	if(dot < 0.0f) {
		/* make sure we interpolate across the shortest arc */
		qa.x = -qa.x;
		qa.y = -qa.y;
		qa.z = -qa.z;
		qa.w = -qa.w;
		dot = -dot;
	}

	/* clamp dot to [-1, 1] in order to avoid domain errors in acos */
	if(dot < -1.0f) dot = -1.0f;
	if(dot > 1.0f) dot = 1.0f;
	angle = acos(dot);
	sin_angle = sin(angle);

	if(sin_angle == 0.0f) {
		/* use linear interpolation to avoid div/zero */
		ta = 1.0f - t;
		tb = t;
	} else {
		ta = sin((1.0f - t) * angle) / sin_angle;
		tb = sin(t * angle) / sin_angle;
	}

	res->x = a->x * ta + b->x * tb;
	res->y = a->y * ta + b->y * tb;
	res->z = a->z * ta + b->z * tb;
	res->w = a->w * ta + b->w * tb;
}
