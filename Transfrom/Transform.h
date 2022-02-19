#pragma once
#include "Float4x4.h"
__declspec(dllexport) class Transform
{
public:
	const Float4x4& ObjectToWorld() const;//返回模型空间到世界空间的矩阵
	const Float4x4& WorldToObject() const;//返回世界空间到模型空间的矩阵

	void MoveTo(const Vector3& pos);//移动到pos点
	void Move(const Vector3& vec);//从当前位置进行位移vec

	void RotateTo(const Vector3& rot);//旋转到rot度
	void Rotate(const Vector3& degree);//旋转degree


	Transform(Vector3 pos, Vector3 rot = Vector3::ZERO);
	Transform();

private:
	Vector3 position;
	Vector3 rotation; 

	Float4x4 objectToWorldMatrix;
	Float4x4 worldToObjectMatrix;
};

