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
	float orig[16];
	int i, j, subi, subj;

	cgm_mcopy(orig, m);

	subi = 0;
	for(i=0; i<4; i++) {
		if(i == col) continue;

		subj = 0;
		for(j=0; j<4; j++) {
			if(j == row) continue;

			m[subi * 4 + subj++] = orig[i * 4 + j];
		}
		subi++;
	}

	cgm_mupper3(m);
}

static inline void cgm_mupper3(float *m)
{
	m[3] = m[7] = m[11] = m[12] = m[13] = m[14] = 0.0f;
	m[15] = 1.0f;
}

static inline float cgm_msubdet(float *m, int row, int col)
{
	cgm_msubmatrix(m, row, col);
	return cgm_mdet(m);
}

static inline float cgm_mcofactor(float *m, int row, int col)
{
	float min = cgm_msubdet(m, row, col);
	return (row + col) & 1 ? -min : min;
}

static inline float cgm_mdet(float *m)
{
	return m[0] * cgm_msubdet(m, 0, 0) - m[1] * cgm_msubdet(m, 0, 1) +
		m[2] * cgm_msubdet(m, 0, 2) - m[3] * cgm_msubdet(m, 0, 3);
}

static inline void cgm_mtranspose(float *m)
{
	int i, j;
	for(i=0; i<4; i++) {
		for(j=0; j<i; j++) {
			int a = i * 4 + j;
			int b = j * 4 + i;
			float tmp = m[a];
			m[a] = m[b];
			m[b] = tmp;
		}
	}
}

static inline void cgm_mcofmatrix(float *m)
{
	float tmp[16];
	int i, j;

	cgm_mcopy(tmp, m);

	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			m[i * 4 + j] = cgm_mcofactor(tmp, i, j);
		}
	}
}

static inline int cgm_minverse(float *m)
{
	int i, j;
	float tmp[16];
	float inv_det;
	float det = cgm_mdet(m);
	if(det == 0.0f) return -1;
	inv_det = 1.0f / det;

	cgm_mcopy(tmp, m);

	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			m[i * 4 + j] = cgm_mcofactor(tmp, j, i) * inv_det;	/* transposed */
		}
	}
}
