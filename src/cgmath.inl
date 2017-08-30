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
