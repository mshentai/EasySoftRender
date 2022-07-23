#pragma once
#include "Reference.h"
class Float4x4;
class __declspec(dllexport) Vector3
{
	//�����ӷ�
	friend __declspec(dllexport) Vector3 operator+(const Vector3&lhs, const Vector3&rhs);
	//��������
	friend __declspec(dllexport) Vector3 operator-(const Vector3&lhs, const Vector3&rhs);
	//�����˷�
	friend __declspec(dllexport) float operator*(const Vector3&lhs, const Vector3&rhs);
	//���������˷�
	friend __declspec(dllexport) Vector3 operator*(const Vector3&vec, const float n);
	//������������
	friend __declspec(dllexport) Vector3 operator/(const Vector3& vec, const float n);
	//�ж������Ƿ����
	friend __declspec(dllexport) bool operator==(const Vector3&lhs, const Vector3&rhs);
public:
	//----��Ա����----//
	
	//��ά�������캯����x,y,z�ֱ��Ӧ����
	Vector3(float x, float y, float z) noexcept;
	//��ά�������캯����Ĭ��Ϊԭ������
	Vector3() noexcept;
	//��ά�������ƹ��캯��
	Vector3(const Vector3 & rhs) noexcept;
	//��ά�������캯��
	Vector3(float x, float y, float z, float w) noexcept : v3{x,y,z,w}{}
	
	//ȡ�����ķ�����
	float operator[](const int i) const { return v3[i]; }
	float& operator[](const int i) { return v3[i]; }
	//+=���������
	Vector3& operator+=(const Vector3 & rhs);
	//�������������
	Vector3& operator=(const Vector3 & rhs);
	//��һ��
	Vector3 Normalize() const;
	//���
	float Dot(const Vector3 & rhs) const;
	//���
	Vector3 Cross(const Vector3 & rhs) const;

	//Vector3 Dot(const Float4x4& mat, bool isPositon);
	
	Vector3 operator-() const { return Vector3(-v3[0], -v3[1], -v3[2]); }

	Vector3 OX(const Vector3 rhs) const;

	float Norm() const;

	void Init()
	{
		v3[0] = 0;
		v3[1] = 0;
		v3[2] = 0;
		v3[3] = 0;
	}

	//----��Ա����-----//

	static const Vector3 UP;//��������
	static const Vector3 RIGHT;//��������
	static const Vector3 FORWARD;//��ǰ����
	static const Vector3 ZERO;//������
private:
	//----��Ա����----//

	float v3[4];

};


