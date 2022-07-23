#pragma once
#include <Windows.h>
#include "Component.h"
class Transform;
class Float4x4;
class Camera :
	public Component
{
	//变量
private:
	bool m_IsPerspective;
	float m_DMin;
	float m_DMax;
	float m_HalfViewRad;
	float m_AspectRatio;
	float m_VP_l;//视口左边界
	float m_VP_r;//右
	float m_VP_b;//底
	float m_VP_t;//顶

	//函数
public:
	//获得由模型空间转换到相机空间的其次矩阵
	Float4x4 ModelToViewMatrix(const Transform & cTran, const Transform & mTran) const;
	void GetFrustum(float &rMin, float &rMax,
		float &uMin, float &uMax,
		float &dMin, float & dMax) const;
	void SetFrustum(float viewRad, float aspectRatio, float dmin, float dmax);
	Float4x4 GetProjectMatrix() const;
	bool IsPerspective() const;
	void SetProjectMode(bool isPerspective);
	Float4x4 GetViewMatrix() const;
	void SetViewPort(float l, float r, float t, float b);
	Float4x4 GetScreenMatrix(float width, float heigth) const;
	Float4x4 GetMVPMatrix(const Transform* obj_Tran)const;
};

