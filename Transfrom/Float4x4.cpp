#include "Float4x4.h"

Float4x4 operator*(const Float4x4 & lhs, const Float4x4 & rhs)
{
	float mat[4][4];
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			float val = 0;
			for (size_t k = 0; k < 4; ++k)
			{
				val += lhs[i][k] * rhs[k][j];
			}
			mat[i][j] = val;
		}
	}
	return Float4x4(mat);
}

Vector3 operator*(const Vector3 & v3, const Float4x4 & mat4)
{
	float v4[4]{ v3[0],v3[1],v3[2],1.0f };
	float result[4];
	for (size_t i = 0; i < 4; ++i)
	{
		float val = 0;
		for (size_t j = 0; j < 4; ++j)
		{
			val += v4[j] * mat4.matrix[j][i];
		}
		result[i] = val;
	}
	return Vector3(result[0], result[1], result[2], result[3]);
}

bool operator==(const Float4x4 & lhs, const Float4x4 & rhs)
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			if (fabsf(lhs[row][col] - rhs[row][col]) > ACC)
				return false;
		}
	}
	return true;
}
Vector3 Dot(const Vector3 & v3, const Float4x4 & mat4, bool isPositon)
{
	float v4[4]{ v3[0],v3[1],v3[2],isPositon };
	float result[4];
	for (size_t i = 0; i < 4; ++i)
	{
		float val = 0;
		for (size_t j = 0; j < 4; ++j)
		{
			val += v4[j] * mat4[j][i];
		}
		result[i] = val;
	}
	return Vector3(result[0], result[1], result[2], result[3]);
}
//LU分解
void LUDecomp(Float4x4& mat, int p[4])
{
	for (int k = 0; k < 4; k++)
	{
		//-----------改变映射，选主元On-----------//
		float maxV = -1.0f;
		int maxId = 0;
		for (int i = k; i < 4; i++)
		{
			float f = fabsf(mat[p[i]][k]);
			if (f > maxV)
			{
				maxV = f;
				maxId = i;
			}
		}
		int tem = p[k];
		p[k] = p[maxId];
		p[maxId] = tem;
		//-----------改变映射，选主元Off----------//
		//---------------行更新On---------------//
		float temp = 0.0f;
		for (size_t i = 0; i < 4; i++)
		{
			temp = mat[k][i];
			mat.matrix[k][i] = mat[maxId][i];
			mat.matrix[maxId][i] = temp;
		}
		//--------------行更新Off---------------//
		float x = 1.0f / mat[k][k];
		for (int i = k + 1; i < 4; i++)
		{
			mat.matrix[i][k] *= x;
			float l = mat[i][k];
			for (int j = k + 1; j < 4; j++)
			{
				mat.matrix[i][j] -= l * mat[k][j];
			}
		}
	}
}

Float4x4::Float4x4(const float mat[4][4]) : matrix
{
	{mat[0][0],mat[0][1],mat[0][2],mat[0][3]},
	{mat[1][0],mat[1][1],mat[1][2],mat[1][3]},
	{mat[2][0],mat[2][1],mat[2][2],mat[2][3]},
	{mat[3][0],mat[3][1],mat[3][2],mat[3][3]}
}
{
}

Float4x4::Float4x4() : matrix{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}
{
}

Float4x4::Float4x4(const Float4x4 & other) : matrix
{
	{other[0][0],other[0][1],other[0][2],other[0][3]},
	{other[1][0],other[1][1],other[1][2],other[1][3]},
	{other[2][0],other[2][1],other[2][2],other[2][3]},
	{other[3][0],other[3][1],other[3][2],other[3][3]}
}
{
}

inline const float * Float4x4::operator[](const int i) const
{
	return matrix[i];
}

Float4x4 & Float4x4::operator*=(const Float4x4 & rhs)
{
	float mat[4][4];
	for (size_t i = 0; i < 4; ++i)
	{
		for (size_t j = 0; j < 4; ++j)
		{
			float val = 0;
			for (size_t k = 0; k < 4; ++k)
			{
				val += matrix[i][k] * rhs[k][j];
			}
			mat[i][j] = val;
		}
	}
	SetValue(mat);
	return *this;
}

Float4x4 & Float4x4::operator=(const Float4x4 & rhs)
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			matrix[i][j] = rhs[i][j];
		}
	}
	return *this;
}

inline void Float4x4::SetValue(const int row, const int col, const float val) 
{
	matrix[row][col] = val;
}

void Float4x4::SetValue(const float mat[4][4])
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			matrix[i][j] = mat[i][j];
		}
	}
}

inline void Float4x4::AddValue(const int row, const int col, const float val)
{
	matrix[row][col] += val;
}

Float4x4 Float4x4::Inverse() const
{
	float mat[4][4]{
		{0.0f,0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f,0.0f},
		{0.0f,0.0f,0.0f,0.0f}};
	int p[4]{ 0,1,2,3 };
	Float4x4 lu(matrix);
	LUDecomp(lu, p);
	mat[0][p[0]] = 1.0f;
	mat[1][p[1]] = 1.0f;
	mat[2][p[2]] = 1.0f;
	mat[3][p[3]] = 1.0f;
	for (int n = 0; n < 4; n++)
	{
		for (int i = 1; i < 4; i++)
		{
			for (int j = 0; j < i; j++)
			{
				mat[i][n] -= lu[i][j] * mat[j][n];
			}
		}

		for (int i = 3; i >= 0; --i)
		{
			for (int j = i + 1; j < 4; ++j)
			{
				mat[i][n] -=  lu[i][j] * mat[j][n];
			}
			mat[i][n] /= lu[i][i];
		}
	}
	return Float4x4(mat);
}

Float4x4 Float4x4::Transpose() const
{
	float mat[4][4];
	for (size_t r = 0; r < 4; r++)
	{
		for (size_t c = 0; c < 4; c++)
		{
			mat[c][r] = matrix[r][c];
		}
	}
	return Float4x4(mat);
}

inline Float4x4 Float4x4::GetXRotationMatrix(float degree)
{
	float rad = degree / 180.0f*PI;
	float cf = cosf(rad);
	float sf = sinf(rad);
	float mat[4][4]{
		{1,0,0,0},
		{0,cf,sf,0},
		{0,-sf,cf,0},
		{0,0,0,1}
	};
	return Float4x4(mat);
}

Float4x4 Float4x4::GetYRotationMatrix(float degree)
{
	float rad = degree / 180.0f*PI;
	float cf = cosf(rad);
	float sf = sinf(rad);
	float mat[4][4]{
		{cf,0,-sf,0},
		{0,1,0,0},
		{sf,0,cf,0},
		{0,0,0,1}
	};
	return Float4x4(mat);
}

Float4x4 Float4x4::GetZRotationMatrix(float degree)
{
	float rad = degree / 180.0f*PI;
	float cf = cosf(rad);
	float sf = sinf(rad);
	float mat[4][4]{
		{cf,sf,0,0},
		{-sf,cf,0,0},
		{0,0,1,0},
		{0,0,0,1}
	};
	return Float4x4(mat);
}
