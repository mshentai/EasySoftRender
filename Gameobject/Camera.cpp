#include "Camera.h"
#include "Transform.h"
#include "..\Transfrom\Float4x4.h"

Float4x4 Camera::ModelToViewMatrix(const Transform & cTran, const Transform & mTran) const
{
	return mTran.ObjectToWorld() * cTran.WorldToObject();
}

void Camera::GetFrustum(float & rMin, float & rMax, float & uMin, float & uMax, float & dMin, float & dMax) const
{
	uMax = m_DMin * tanf(m_HalfViewRad);
	uMin = -uMax;
	rMax = m_AspectRatio * uMax;
	rMin = -rMax;
	dMax = m_DMax;
	dMin = m_DMin;
}

void Camera::SetFrustum(float viewRad, float aspectRatio, float dmin, float dmax)
{
	this->m_HalfViewRad = viewRad / 2;
	this->m_AspectRatio = aspectRatio;
	this->m_DMin = dmin;
	this->m_DMax = dmax;
}

Float4x4 Camera::GetProjectMatrix() const
{
	float rMin, rMax, uMin, uMax, dMin, dMax;
	GetFrustum(rMin, rMax, uMin, uMax, dMin, dMax);
	float invRDiff = 1.0f / (rMax - rMin);
	float invUDiff = 1.0f / (uMax - uMin);
	float invDDiff = 1.0f / (dMax - dMin);
	float mat[4][4];
	if (IsPerspective())
	{
		mat[0][0] = 2.0f*dMin*invRDiff;
		mat[0][1] = 0.0f;
		mat[0][2] = 0.0f;
		mat[0][3] = 0.0f;
		mat[1][0] = 0.0f;
		mat[1][1] = 2.0f*dMin*invUDiff;
		mat[1][2] = 0.0f;
		mat[1][3] = 0.0f;
		mat[2][0] = -(rMin + rMax)*invRDiff;
		mat[2][1] = -(uMin + uMax)*invUDiff;
		mat[2][2] = dMax * invDDiff;
		mat[2][3] = 1.0f;
		mat[3][0] = 0.0f;
		mat[3][1] = 0.0f;
		mat[3][2] = -2 * dMax*dMin*invDDiff;
		mat[3][3] = 0.0f;

		//mat[0][0] = 2.0f * dMin * invRDiff;
		//mat[0][1] = 0.0f;
		//mat[0][2] = 0.0f;
		//mat[0][3] = 0.0f;
		//mat[1][0] = 0.0f;
		//mat[1][1] = 2.0f * dMin * invUDiff;
		//mat[1][2] = 0.0f;
		//mat[1][3] = 0.0f;
		//mat[2][0] = (rMin + rMax) * invRDiff;
		//mat[2][1] = (uMin + uMax) * invUDiff;
		//mat[2][2] = -(dMax + dMin) * invDDiff;
		//mat[2][3] = -1.0f;
		//mat[3][0] = 0.0f;
		//mat[3][1] = 0.0f;
		//mat[3][2] = -2.0 *dMax * dMin * invDDiff;
		//mat[3][3] = 0.0f;

		//mat[0][0] = 2.0f * dMin * invRDiff;
		//mat[0][1] = 0.0f;
		//mat[0][2] = 0.0f;
		//mat[0][3] = 0.0f;
		//mat[1][0] = 0.0f;
		//mat[1][1] = 2.0f * dMin * invUDiff;
		//mat[1][2] = 0.0f;
		//mat[1][3] = 0.0f;
		//mat[2][0] = (rMin + rMax) * invRDiff;
		//mat[2][1] = (uMin + uMax) * invUDiff;
		//mat[2][2] = -(dMax + dMin) * invDDiff;
		//mat[2][3] = -1.0f;
		//mat[3][0] = 0.0f;
		//mat[3][1] = 0.0f;
		//mat[3][2] = -2.0 * dMax * dMin * invDDiff;
		//mat[3][3] = 0.0f;
	}
	else
	{
		mat[0][0] = 2.0f*invRDiff;
		mat[0][1] = 0.0f;
		mat[0][2] = 0.0f;
		mat[0][3] = 0.0f;
		mat[1][0] = 0.0f;
		mat[1][1] = 2.0f*invUDiff;
		mat[1][2] = 0.0f;
		mat[1][3] = 0.0f;
		mat[2][0] = 0.0f;
		mat[2][1] = 0.0f;
		mat[2][2] = invDDiff;
		mat[2][3] = 0.0f;
		mat[3][0] = -(rMin + rMax)*invRDiff;
		mat[3][1] = -(uMin + uMax)*invUDiff;
		mat[3][2] = - dMin * invDDiff;
		mat[3][3] = 1.0f;
	}
	return Float4x4(mat);
}

bool Camera::IsPerspective() const
{
	return this->m_IsPerspective;
}

void Camera::SetProjectMode(bool isPerspective)
{
	m_IsPerspective = isPerspective;
}

Float4x4 Camera::GetViewMatrix() const
{
	float mat[4][4];
	const Vector3& pos = this->GetTransform()->GetPosition();
	const Vector3& rve = this->GetTransform()->GetRVector();
	const Vector3& uve = -this->GetTransform()->GetUVector();
	const Vector3& fve = this->GetTransform()->GetFVector();
	
	mat[0][0] = rve[0];
	mat[0][1] = uve[0];
	mat[0][2] = fve[0];
	mat[0][3] = 0.0f;
	mat[1][0] = rve[1];
	mat[1][1] = uve[1];
	mat[1][2] = fve[1];
	mat[1][3] = 0.0f;
	mat[2][0] = rve[2];
	mat[2][1] = uve[2];
	mat[2][2] = fve[2];
	mat[2][3] = 0.0f;
	mat[3][0] = -rve.Dot(pos);
	mat[3][1] = -uve.Dot(pos);
	mat[3][2] = -fve.Dot(pos);
	mat[3][3] = 1.0f;
	return Float4x4(mat);
}

void Camera::SetViewPort(float l, float r, float t, float b, float n, float f) 
{
	m_VP_l = l;
	m_VP_r = r;
	m_VP_t = t;
	m_VP_b = b;
	m_VP_n = n;
	m_VP_f = f;
}

Float4x4 Camera::GetScreenMatrix(float width, float heigth) const
{
	float l = m_VP_l;
	float r = m_VP_r;
	float t = m_VP_t;
	float b = m_VP_b;
	float f = m_VP_f;
	float n = m_VP_n;
	float diff = 1.0f / 2.0f;
	float mat[4][4];
	mat[0][0] = width * (r - l) * diff;
	mat[0][1] = 0.0f;
	mat[0][2] = 0.0f;
	mat[0][3] = 0.0f;
	mat[1][0] = 0.0f;
	mat[1][1] = heigth * (b - t) * diff;
	mat[1][2] = 0.0f;
	mat[1][3] = 0.0f;
	mat[2][0] = 0.0f;
	mat[2][1] = 0.0f; 
	mat[2][2] = f - n;
	mat[2][3] = 0.0f;
	mat[3][0] = width * (r + l) * diff;
	mat[3][1] = heigth * (2 - t - b) * diff;
	mat[3][2] = n;
	mat[3][3] = 1.0f;
	return Float4x4(mat);
}

Float4x4 Camera::GetMVPMatrix(const Transform* obj_Tran) const
{
	return (obj_Tran->ObjectToWorld()) * (GetViewMatrix()) * (GetProjectMatrix());
}
