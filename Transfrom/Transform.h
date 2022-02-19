#pragma once
#include "Float4x4.h"
__declspec(dllexport) class Transform
{
public:
	const Float4x4& ObjectToWorld() const;//����ģ�Ϳռ䵽����ռ�ľ���
	const Float4x4& WorldToObject() const;//��������ռ䵽ģ�Ϳռ�ľ���

	void MoveTo(const Vector3& pos);//�ƶ���pos��
	void Move(const Vector3& vec);//�ӵ�ǰλ�ý���λ��vec

	void RotateTo(const Vector3& rot);//��ת��rot��
	void Rotate(const Vector3& degree);//��תdegree


	Transform(Vector3 pos, Vector3 rot = Vector3::ZERO);
	Transform();

private:
	Vector3 position;
	Vector3 rotation; 

	Float4x4 objectToWorldMatrix;
	Float4x4 worldToObjectMatrix;
};

