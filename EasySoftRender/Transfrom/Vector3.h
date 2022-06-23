#pragma once
#include "Reference.h"
class __declspec(dllexport) Vector3
{
	//�����ӷ�
	friend __declspec(dllexport) Vector3 operator+(Vector3&lhs, Vector3&rhs);
	//��������
	friend __declspec(dllexport) Vector3 operator-(Vector3&lhs, Vector3&rhs);
	//�����˷�
	friend __declspec(dllexport) float operator*(Vector3&lhs, Vector3&rhs);
	//�ж������Ƿ����
	friend __declspec(dllexport) bool operator==(Vector3&lhs, Vector3&rhs);
public:
	//----��Ա����----//
	
	//��ά�������캯����x,y,z�ֱ��Ӧ����
	Vector3(float x, float y, float z) noexcept;
	//��ά�������캯����Ĭ��Ϊԭ������
	Vector3() noexcept;
	//��ά�������ƹ��캯��
	Vector3(const Vector3 & rhs) noexcept;
	//ȡ�����ķ�����
	float operator[](const int i) const;
	//�������������
	Vector3& operator+=(const Vector3 & rhs);
	

	//----��Ա����-----//

	static const Vector3 UP;//��������
	static const Vector3 RIGHT;//��������
	static const Vector3 FORWARD;//��ǰ����
	static const Vector3 ZERO;//������
private:
	//----��Ա����----//

	float v3[3];
	
	

};

