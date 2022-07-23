#pragma once
#include "Vector3.h"
class __declspec(dllexport) Float4x4
{
	//����˷�
	friend __declspec(dllexport) Float4x4 operator*(const Float4x4& lhs, const Float4x4& rhs);


	//LU�ֽ�
	friend void LUDecomp(Float4x4& mat, int p[4]);
public:
	//------��Ա����------//

	//��λ����
	static const Float4x4 IdentityMatrix;

	//------��Ա����------//

	//���캯��
	//mat��4*4��ά����������
	Float4x4(const float mat[4][4]);
	//Ĭ�Ϲ��캯����Ĭ��Ϊ��λ����
	Float4x4();
	//ȡ��������������
	Float4x4(const Float4x4 & other);
	const float * operator[](const int i) const;
	//�˷���ֵ����
	Float4x4& operator*=(const Float4x4& rhs);
	//��ֵ��������
	Float4x4& operator=(const Float4x4& rhs);
	//�ھ���ָ��λ������ָ��ֵ
	//row:�кţ�col:�кţ�val:ָ��ֵ
	void SetValue(const int row, const int col, const float val);
	//�ھ�������ֵȫ������
	void SetValue(const float mat[4][4]);
	//�ھ���ָ��λ�ü���ָ��ֵ
	//row:�кţ�col:�кţ�val:ָ��ֵ
	void AddValue(const int row, const int col, const float val);
	//�ó���ǰ����������
	Float4x4 Inverse() const;
	//�ó���ǰ�����ת�þ���
	Float4x4 Transpose() const;
	//��ȡ��X����ת�ľ���
	static Float4x4 GetXRotationMatrix(float degree);
	//��ȡ��Y����ת�ľ���
	static Float4x4 GetYRotationMatrix(float degree);
	//��ȡ��Z����ת�ľ���
	static Float4x4 GetZRotationMatrix(float degree);

private:
	//------��Ա����------//

	//�������
	float matrix[4][4];

	//------��Ա����------//


};
//�ж��������Ƿ����
__declspec(dllexport) bool operator==(const Float4x4& lhs, const Float4x4& rhs);
__declspec(dllexport) Vector3 Dot(const Vector3& v3, const Float4x4& mat4, bool isPosition = false);