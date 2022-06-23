#include "Float4x4.h"
const Float4x4 Float4x4::IdentityMatrix = Float4x4();

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
	return Vector3(result[0], result[1], result[2]);
}

bool operator==(const Float4x4 & lhs, const Float4x4 & rhs)
{
	for (size_t row = 0; row < 4; row++)
	{
		for (size_t col = 0; col < 4; col++)
		{
			if (fabsf(lhs[row][col] - rhs[row][col]) > 1e-4)
				return false;
		}
	}
	return true;
}
//LU分解
void LUDecomp(Float4x4& mat, int p[4])
{
	for (int k = 0; k < 4; k++)
	{
		//-----------改变映射，选主元On-----------//
		float maxV = -999.0f;
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
			for (int j = k + 1; j < 4; j++)
			{
				mat.matrix[i][j] -= mat[i][k] * mat[k][j];
			}
		}
	}
}

Float4x4::Float4x4(const float mat[4][4])
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			matrix[i][j] = mat[i][j];
		}
	}
}

Float4x4::Float4x4()
{
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			matrix[i][j] = 0;
		}
	}
}

inline const float * Float4x4::operator[](const int i) const
{
	return matrix[i];
}

inline void Float4x4::SetValue(const int row, const int col, const float val) 
{
	matrix[row][col] = val;
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
	for (size_t i = 0; i < 4; i++)
	{
		mat[p[i]][i] = 1.0f;
	}
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
