#pragma once
#include "Vector3.h"
class __declspec(dllexport) Float4x4
{
	//矩阵乘法
	friend __declspec(dllexport) Float4x4 operator*(const Float4x4& lhs, const Float4x4& rhs);


	//LU分解
	friend void LUDecomp(Float4x4& mat, int p[4]);
public:
	//------成员变量------//

	//单位矩阵
	static const Float4x4 IdentityMatrix;

	//------成员函数------//

	//构造函数
	//mat：4*4二维浮点型数组
	Float4x4(const float mat[4][4]);
	//默认构造函数，默认为单位矩阵
	Float4x4();
	//取矩阵行向量分量
	Float4x4(const Float4x4 & other);
	const float * operator[](const int i) const;
	//乘法赋值重载
	Float4x4& operator*=(const Float4x4& rhs);
	//赋值符号重载
	Float4x4& operator=(const Float4x4& rhs);
	//在矩阵指定位置设置指定值
	//row:行号，col:列号，val:指定值
	void SetValue(const int row, const int col, const float val);
	//在矩阵所有值全部设置
	void SetValue(const float mat[4][4]);
	//在矩阵指定位置加上指定值
	//row:行号，col:列号，val:指定值
	void AddValue(const int row, const int col, const float val);
	//得出当前矩阵的逆矩阵
	Float4x4 Inverse() const;
	//得出当前矩阵的转置矩阵
	Float4x4 Transpose() const;
	//获取绕X轴旋转的矩阵
	static Float4x4 GetXRotationMatrix(float degree);
	//获取绕Y轴旋转的矩阵
	static Float4x4 GetYRotationMatrix(float degree);
	//获取绕Z轴旋转的矩阵
	static Float4x4 GetZRotationMatrix(float degree);

private:
	//------成员变量------//

	//矩阵变量
	float matrix[4][4];

	//------成员函数------//


};
//判断两矩阵是否相等
__declspec(dllexport) bool operator==(const Float4x4& lhs, const Float4x4& rhs);
__declspec(dllexport) Vector3 Dot(const Vector3& v3, const Float4x4& mat4, bool isPosition = false);