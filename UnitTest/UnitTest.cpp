#include "pch.h"
#include "CppUnitTest.h"
#include "../Transfrom/Float4x4.h"
#include "../Transfrom/Vector3.h"
#include "../Transfrom/Transform.h"
#pragma comment(lib,"../Debug/Transfrom.lib")
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(TransformUnitTest)
	{
	public:
		
		TEST_METHOD(Test_Vertor3xFloat4x4)
		{
			Vector3 v3(1, 2, 3);
			Float4x4 mat4;
			for (int i = 0; i < 3; i++)
			{
				mat4.SetValue(i, i, 1.0f);
			}
			Assert::IsTrue(v3 == (v3 * mat4));
			for (int i = 0; i < 3; i++)
			{
				mat4.SetValue(i, i, 0.5f);
			}
			for (int i = 0; i < 4; i++)
			{
				mat4.SetValue(3, i, 1.0f);
			}
			Vector3 result1(1.5f, 2.0f, 2.5f);
			Assert::IsTrue(result1 == (v3 * mat4));
			Vector3 result2(7.1f, 12.1f, 14.2f);
			float f[4][4] = { 
				{0.5f,1.7f,0.6f,0.0f},
				{1.0f,1.2f,0.8f,0.0f},
				{1.2f,2.0f,3.0f,0.0f},
				{1.0f,2.0f,3.0f,1.0f} };
			Float4x4 mat41(f);
			Assert::IsTrue(result2 == (v3*mat41));
		}

		TEST_METHOD(Test_Float4x4xFloat4x4)
		{
			float mat1[4][4] = {
				{0.7f,2.2f,3.1f,0.0f},
				{1.1f,2.0f,3.8f,0.0f},
				{2.5f,1.0f,2.3f,0.0f},
				{1.4f,2.7f,1.1f,1.0f} };
			float mat2[4][4] = {
				{0.2f,3.2f,1.3f,0.0f},
				{2.1f,1.7f,3.7f,0.0f},
				{5.2f,2.1f,3.1f,0.0f},
				{0.8f,6.1f,2.4f,1.0f} };
			Float4x4 fmat1(mat1);
			Float4x4 fmat2(mat2);

			float mat3[4][4] = {
				{20.88f,12.49f,18.66f,0.0f},
				{24.18f,14.90f,20.61f,0.0f},
				{14.56f,14.53f,14.08f,0.0f},
				{12.47f,17.48f,17.62f,1.0f} };

			Float4x4 result(mat3);

			Assert::IsTrue(result == (fmat1 * fmat2));
		}

		TEST_METHOD(Test_Transpose)
		{
			float mat1[4][4] = {
				{0,1,2,3},
				{0,1,2,3},
				{0,1,2,3},
				{0,1,2,3} };
			Float4x4 fmat1(mat1);
			Float4x4 fmat2 = fmat1.Transpose();

			float mat3[4][4] = {
				{0,0,0,0},
				{1,1,1,1},
				{2,2,2,2},
				{3,3,3,3} };

			Float4x4 result(mat3);

			Assert::IsTrue(fmat2 == result);
		}

		TEST_METHOD(Test_Inverse)
		{
			float mat1[4][4] = {
				{1,1,1,0},
				{1,2,3,0},
				{1,5,1,0},
				{0,1,0,1} };
			Float4x4 fmat1(mat1);
			Float4x4 fmat2 = fmat1.Inverse();

			float mat3[4][4] =
			{
				{1.6250f,-0.5000f,-0.1250f,-0.0000f},
				{-0.2500f,0.0000f,0.2500f,0.0000f},
				{-0.3750f,0.5000f,-0.1250f,-0.0000f},
				{0.2500f,0.0000f,-0.2500f,1.0000f}
			};

			Float4x4 result(mat3);

			Assert::IsTrue(fmat2 == result);
		}

		TEST_METHOD(Test_VecMul)
		{
			Vector3 l(1.0f, 2.0f, 3.0f);
			Vector3 r(10.0f, 250.5f, 3.1f);
			Assert::IsTrue(l*r == 10.0f+501.0f+9.3f);
		}

		TEST_METHOD(Test_TransformRot)
		{
			Vector3 rot(30.0f, 90.0f, 60.0f);
			Vector3 vec(1.0f, 2.0f, 50.0f);
			Transform tran(vec, rot);
			float mat[4][4] {
				{0.4330f,0.75f,-0.5f,0},
				{0.25f,0.433f,0.866f,0},
				{0.866f,-0.5f,0,0},
				{1.0f, 2.0f, 50.0f,1}
			};
			Float4x4 WTO(mat);
			Assert::IsTrue(WTO == tran.WorldToObject());
			Assert::IsTrue(WTO.Inverse() == tran.ObjectToWorld());
			Vector3 rot2(60.0f, 0.0f, 0.0f);
			Vector3 vec2(10.0f, 10.0f, 10.0f);
			tran.Move(vec2);
			tran.Rotate(rot2);
			WTO.AddValue(3, 0, vec2[0]);
			WTO.AddValue(3, 1, vec2[1]);
			WTO.AddValue(3, 2, vec2[2]);
			WTO *= Float4x4::GetXRotationMatrix(60);
			Assert::IsTrue(WTO == tran.WorldToObject());
			Assert::IsTrue(WTO.Inverse() == tran.ObjectToWorld());
		}
	};
}
