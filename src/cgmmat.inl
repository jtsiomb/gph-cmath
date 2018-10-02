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

static inline void cgm_mmul(float *a, const float *b)
{
	int i, j;
	float res[16];
	float *resptr = res;
	float *arow = a;

	for(i=0; i<4; i++) {
		for(j=0; j<4; j++) {
			*resptr++ = arow[0] * b[j] + arow[1] * b[4 + j] +
				arow[2] * b[8 + j] + arow[3] * b[12 + j];
		}
		arow += 4;
	}
	cgm_mcopy(a, res);
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

static inline void cgm_mtranslation(float *m, float x, float y, float z)
{
	cgm_midentity(m);
	m[12] = x;
	m[13] = y;
	m[14] = z;
}

static inline void cgm_mscaling(float *m, float sx, float sy, float sz)
{
	cgm_mzero(m);
	m[0] = sx;
	m[5] = sy;
	m[10] = sz;
	m[15] = 1.0f;
}

static inline void cgm_mrotation_x(float *m, float angle)
{
	float sa = sin(angle);
	float ca = cos(angle);

	cgm_midentity(m);
	m[5] = ca;
	m[6] = sa;
	m[9] = -sa;
	m[10] = ca;
}

static inline void cgm_mrotation_y(float *m, float angle)
{
	float sa = sin(angle);
	float ca = cos(angle);

	cgm_midentity(m);
	m[0] = ca;
	m[2] = -sa;
	m[8] = sa;
	m[10] = ca;
}

static inline void cgm_mrotation_z(float *m, float angle)
{
	float sa = sin(angle);
	float ca = cos(angle);

	cgm_midentity(m);
	m[0] = ca;
	m[1] = sa;
	m[4] = -sa;
	m[5] = ca;
}

static inline void cgm_mrotation_axis(float *m, int idx, float angle)
{
	switch(idx) {
	case 0:
		cgm_mrotation_x(m, angle);
		break;
	case 1:
		cgm_mrotation_y(m, angle);
		break;
	case 2:
		cgm_mrotation_z(m, angle);
		break;
	}
}

static inline void cgm_mrotation(float *m, float angle, float x, float y, float z)
{
	float sa = sin(angle);
	float ca = cos(angle);
	float invca = 1.0f - ca;
	float xsq = x * x;
	float ysq = y * y;
	float zsq = z * z;

	cgm_mzero(m);
	m[15] = 1.0f;

	m[0] = xsq + (1.0f - xsq) * ca;
	m[4] = x * y * invca - z * sa;
	m[8] = x * z * invca + y * sa;

	m[1] = x * y * invca + z * sa;
	m[5] = ysq + (1.0f - ysq) * ca;
	m[9] = y * z * invca - x * sa;

	m[2] = x * z * invca - y * sa;
	m[6] = y * z * invca + x * sa;
	m[10] = zsq + (1.0f - zsq) * ca;
}

static inline void cgm_mrotation_euler(float *m, float a, float b, float c, int mode)
{
	/* this array must match the EulerMode enum */
	static const int axis[][3] = {
		{0, 1, 2}, {0, 2, 1},
		{1, 0, 2}, {1, 2, 0},
		{2, 0, 1}, {2, 1, 0},
		{2, 0, 2}, {2, 1, 2},
		{1, 0, 1}, {1, 2, 1},
		{0, 1, 0}, {0, 2, 0}
	};

	float ma[16], mb[16];
	cgm_mrotation_axis(ma, axis[mode][0], a);
	cgm_mrotation_axis(mb, axis[mode][1], b);
	cgm_mrotation_axis(m, axis[mode][2], c);
	cgm_mmul(m, mb);
	cgm_mmul(m, ma);
}

static inline void cgm_mtranslate(float *m, float x, float y, float z)
{
	float tm[16];
	cgm_mtranslation(tm, x, y, z);
	cgm_mmul(m, tm);
}

static inline void cgm_mscale(float *m, float sx, float sy, float sz)
{
	float sm[16];
	cgm_mscaling(sm, sx, sy, sz);
	cgm_mmul(m, sm);
}

static inline void cgm_mrotate_x(float *m, float angle)
{
	float rm[16];
	cgm_mrotation_x(rm, angle);
	cgm_mmul(m, rm);
}

static inline void cgm_mrotate_y(float *m, float angle)
{
	float rm[16];
	cgm_mrotation_y(rm, angle);
	cgm_mmul(m, rm);
}

static inline void cgm_mrotate_z(float *m, float angle)
{
	float rm[16];
	cgm_mrotation_z(rm, angle);
	cgm_mmul(m, rm);
}

static inline void cgm_mrotate_axis(float *m, int idx, float angle)
{
	float rm[16];
	cgm_mrotation_axis(rm, idx, angle);
	cgm_mmul(m, rm);
}

static inline void cgm_mrotate(float *m, float angle, float x, float y, float z)
{
	float rm[16];
	cgm_mrotation(rm, angle, x, y, z);
	cgm_mmul(m, rm);
}

static inline void cgm_mrotate_euler(float *m, float a, float b, float c, int mode)
{
	float rm[16];
	cgm_mrotation_euler(rm, a, b, c, mode);
	cgm_mmul(m, rm);
}


static inline void cgm_mpretranslate(float *m, float x, float y, float z)
{
	float tmp[16];
	cgm_mcopy(tmp, m);
	cgm_mtranslation(m, x, y, z);
	cgm_mmul(m, tmp);
}

static inline void cgm_mprescale(float *m, float sx, float sy, float sz)
{
	float tmp[16];
	cgm_mcopy(tmp, m);
	cgm_mscaling(m, sx, sy, sz);
	cgm_mmul(m, tmp);
}

static inline void cgm_mprerotate_x(float *m, float angle)
{
	float tmp[16];
	cgm_mcopy(tmp, m);
	cgm_mrotation_x(m, angle);
	cgm_mmul(m, tmp);
}

static inline void cgm_mprerotate_y(float *m, float angle)
{
	float tmp[16];
	cgm_mcopy(tmp, m);
	cgm_mrotation_y(m, angle);
	cgm_mmul(m, tmp);
}

static inline void cgm_mprerotate_z(float *m, float angle)
{
	float tmp[16];
	cgm_mcopy(tmp, m);
	cgm_mrotation_z(m, angle);
	cgm_mmul(m, tmp);
}

static inline void cgm_mprerotate_axis(float *m, int idx, float angle)
{
	float tmp[16];
	cgm_mcopy(tmp, m);
	cgm_mrotation_axis(m, idx, angle);
	cgm_mmul(m, tmp);
}

static inline void cgm_mprerotate(float *m, float angle, float x, float y, float z)
{
	float tmp[16];
	cgm_mcopy(tmp, m);
	cgm_mrotation(m, angle, x, y, z);
	cgm_mmul(m, tmp);
}

static inline void cgm_mprerotate_euler(float *m, float a, float b, float c, int mode)
{
	float tmp[16];
	cgm_mcopy(tmp, m);
	cgm_mrotation_euler(m, a, b, c, mode);
	cgm_mmul(m, tmp);
}
