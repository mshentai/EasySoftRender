#include "Quaternion.h"

Quaternion operator*(const Quaternion & lhs, const Quaternion & rhs)
{
	float c0 = lhs[0];
	float c1 = rhs[0];
	float s0 = sinf(acosf(c0));
	float s1 = sinf(acosf(c1));
	float tmp = 1.0f / s0;
	Vector3 w0(lhs[1] * tmp, lhs[2] * tmp, lhs[3] * tmp);
	tmp = 1.0f / s1;
	Vector3 w1(rhs[1] * tmp, rhs[2] * tmp, rhs[3] * tmp);
	float v[4];
	Vector3 ww = w0.Cross(w1);
	v[0] = c0 * c1 - s0 * s1 * (w0 * w1);
	v[1] = s0 * c1 * w0[0] + s1 * c0 * w1[0] + s0 * s1 * ww[0];
	v[2] = s0 * c1 * w0[1] + s1 * c0 * w1[1] + s0 * s1 * ww[1];
	v[3] = s0 * c1 * w0[2] + s1 * c0 * w1[2] + s0 * s1 * ww[2];
	return Quaternion(v);
}


