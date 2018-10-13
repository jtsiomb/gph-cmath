#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <gmath/gmath.h>
#include "cgmath.h"

bool test_vec3();
bool test_mat();
float frand(float low, float high);

int main(void)
{
	srand(time(0));

	if(!test_vec3()) {
		fprintf(stderr, "test_vec3 failed\n");
		return 1;
	}
	if(!test_mat()) {
		fprintf(stderr, "test_mat failed\n");
		return 1;
	}
	return 0;
}

#define ASSERT_EQ(a, b)	assert(memcmp(&a, &b, sizeof a) == 0)

bool test_vec3()
{
	Vec3 rv3[2];
	cgm_vec3 crv3[2];
	Vec3 v3;
	cgm_vec3 cv3;

	for(int i=0; i<2; i++) {
		rv3[i].x = crv3[i].x = frand(-100, 100);
		rv3[i].y = crv3[i].y = frand(-100, 100);
		rv3[i].z = crv3[i].z = frand(-100, 100);
	}

	cgm_vcross(&cv3, crv3, crv3 + 1);
	v3 = cross(rv3[0], rv3[1]);
	ASSERT_EQ(v3, cv3);

	cv3 = crv3[0];
	cgm_vreflect(&cv3, crv3 + 1);
	v3 = reflect(rv3[0], rv3[1]);
	ASSERT_EQ(v3, cv3);

	float ior = frand(1, 2);
	cv3 = crv3[0];
	cgm_vrefract(&cv3, crv3 + 1, ior);
	v3 = refract(rv3[0], rv3[1], ior);
	ASSERT_EQ(v3, cv3);

	return true;
}

bool test_mat()
{
	float ca[16], cb[16], cc[16];
	Mat4 a, b, c;

	float angle = frand(-100, 100);
	Vec3 axis = Vec3(frand(-10, 10), frand(-10, 10), frand(-10, 10));
	cgm_mrotation(ca, angle, axis.x, axis.y, axis.z);
	a.rotation(angle, axis.x, axis.y, axis.z);
	ASSERT_EQ(a, ca);

	Vec3 trans = Vec3(frand(-100, 100), frand(-100, 100), frand(-100, 100));
	Vec3 scale = Vec3(frand(0.1, 10), frand(0.1, 10), frand(0.1, 10));
	cgm_mtranslate(ca, trans.x, trans.y, trans.z);
	cgm_mscale(ca, scale.x, scale.y, scale.z);
	a.translate(trans.x, trans.y, trans.z);
	a.scale(scale.x, scale.y, scale.z);
	ASSERT_EQ(a, ca);

	cgm_mprerotate_y(ca, trans.x);
	a.pre_rotate_y(trans.x);
	ASSERT_EQ(a, ca);

	cgm_mcopy(cb, ca);
	cgm_mtranspose(cb);
	b = a;
	b.transpose();
	ASSERT_EQ(b, cb);

	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			cgm_mcopy(cb, ca);
			b = a;

			cgm_msubmatrix(cb, i, j);
			Mat3 sub = b.submatrix(i, j);
			b = Mat4::identity;
			float *bp = b[0];
			float *sp = sub[0];
			bp[0] = sp[0]; bp[1] = sp[1]; bp[2] = sp[2];
			bp[4] = sp[3]; bp[5] = sp[4]; bp[6] = sp[5];
			bp[8] = sp[6]; bp[9] = sp[7]; bp[10] = sp[8];

			ASSERT_EQ(b, cb);
		}
	}

	cgm_minverse(ca);
	a.inverse();
	ASSERT_EQ(a, ca);

	return true;
}

float frand(float low, float high)
{
	float range = high - low;
	return ((float)rand() / (float)RAND_MAX) * range + low;
}
