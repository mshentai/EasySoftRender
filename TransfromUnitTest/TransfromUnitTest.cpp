#include "pch.h"
#include "CppUnitTest.h"
#include "../Transfrom/Vector4.h"
#include "../Transfrom/Float4x4.h"
#include <assert.h>
#pragma comment(lib,"../Debug/Transfrom.lib")

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TransfromUnitTest
{
	TEST_CLASS(TransfromUnitTest)
	{
	public:
		
		TEST_METHOD(Test_Vector4_Dot)
		{
			Vector4 v1(1, 2, 3, 4);
			Vector4 v2(2, 3, 4, 5);
			Assert::IsTrue(abs(v1.Dot(v2) - 40) < ACC);
			float mat[4][4]{ {1,2,3,4},{2,3,4,5},{3,4,5,6},{4,5,6,7} };
			Float4x4 f4x4(mat);

		}
	};
}
