#include "pch.h"
#include "CppUnitTest.h"
#include "../WordCount/Function.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{
	TEST_CLASS(UnitTest)
	{
	public:
		
		TEST_METHOD(WordCountTest)
		{
			// 此处单元测试只有一个用例，请完善
			char* teststr = "F://test.c";
			int num = WordCount(teststr);
			// 11 为已知的正确结果
			Assert::AreEqual(11, num);
		}
		TEST_METHOD(CodeCountTest) {
			// 此处单元测试只有一个用例，请完善
			char* teststr = "F://test.c";
			int num = CodeCount(teststr);
			Assert::AreEqual(66, num);
		}
	};
}
