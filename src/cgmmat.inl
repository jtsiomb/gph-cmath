static inline void cgm_mcopy(float *dest, const float *src)
{
	memcpy(dest, src, 16 * sizeof(float));
}

static inline void cgm_mzero(float *m)
{
	static float z[16];
	cgm_mcopy(m, z);
}

static inline void cgm_midentity(float *m)
{
	static float id[16] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
	cgm_mcopy(m, id);
}

static inline void cgm_msetrow_v3(float *m, int idx, const cgm_vec3 *v)
{
	m[idx] = v->x;
	m[idx + 4] = v->y;
	m[idx + 8] = v->z;
	m[idx + 12] = 0.0f;
}

static inline void cgm_msetrow_v4(float *m, int idx, const cgm_vec4 *v)
{
	m[idx] = v->x;
	m[idx + 4] = v->y;
	m[idx + 8] = v->z;
	m[idx + 12] = v->w;
}

static inline void cgm_msetcol_v3(float *m, int idx, const cgm_vec3 *v)
{
	m[idx * 4] = v->x;
	m[idx * 4 + 1] = v->y;
	m[idx * 4 + 2] = v->z;
	m[idx * 4 + 3] = 0.0f;
}

static inline void cgm_msetcol_v4(float *m, int idx, const cgm_vec4 *v)
{
	m[idx * 4] = v->x;
	m[idx * 4 + 1] = v->y;
	m[idx * 4 + 2] = v->z;
	m[idx * 4 + 3] = v->w;
}

static inline void cgm_mgetrow_v3(cgm_vec3 *v, const float *m, int idx)
{
	v->x = m[idx];
	v->y = m[idx + 4];
	v->z = m[idx + 8];
}

static inline void cgm_mgetrow_v4(cgm_vec4 *v, const float *m, int idx)
{
	v->x = m[idx];
	v->y = m[idx + 4];
	v->z = m[idx + 8];
	v->w = m[idx + 12];
}

static inline void cgm_mgetcol_v3(cgm_vec3 *v, const float *m, int idx)
{
	v->x = m[idx * 4];
	v->y = m[idx * 4 + 1];
	v->z = m[idx * 4 + 2];
}

static inline void cgm_mgetcol_v4(cgm_vec4 *v, const float *m, int idx)
{
	v->x = m[idx * 4];
	v->y = m[idx * 4 + 1];
	v->z = m[idx * 4 + 2];
	v->w = m[idx * 4 + 3];
}

static inline void cgm_msubmatrix(float *m, int row, int col)
{
	int i, j;
	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			int si = i;
			int sj = j;
			if(i >= col) si++;
			if(j >= row) sj++;

			if(si == i && sj == j) continue;

			m[i * 4 + j] = m[si * 4 + sj];
		}
	}
}

static inline void cgm_mupper3(float *m)
{
	m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0.0f;
	m[15] = 1.0f;
}
