#pragma once
#include <Windows.h>
#include "Component.h"
class Transform;
class Float4x4;
class Camera :
	public Component
{
	//����
private:
	bool m_IsPerspective;
	float m_DMin;
	float m_DMax;
	float m_HalfViewRad;
	float m_AspectRatio;
	float m_VP_l;//�ӿ���߽�
	float m_VP_r;//��
	float m_VP_b;//��
	float m_VP_t;//��
	float m_VP_f;//Զ
	float m_VP_n;//��

	//����
public:
	//�����ģ�Ϳռ�ת��������ռ����ξ���
	Float4x4 ModelToViewMatrix(const Transform & cTran, const Transform & mTran) const;
	void GetFrustum(float &rMin, float &rMax,
		float &uMin, float &uMax,
		float &dMin, float & dMax) const;
	void SetFrustum(float viewRad, float aspectRatio, float dmin, float dmax);
	Float4x4 GetProjectMatrix() const;
	bool IsPerspective() const;
	void SetProjectMode(bool isPerspective);
	Float4x4 GetViewMatrix() const;
	void SetViewPort(float l, float r, float t, float b, float n, float f);
	Float4x4 GetScreenMatrix(float width, float heigth) const;
	Float4x4 GetMVPMatrix(const Transform* obj_Tran)const;
};

