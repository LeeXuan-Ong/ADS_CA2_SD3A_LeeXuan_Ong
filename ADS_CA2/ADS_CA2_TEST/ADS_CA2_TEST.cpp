#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_CA2/FileManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ADSCA2TEST
{
	TEST_CLASS(ADSCA2TEST)
	{
	public:

		TEST_METHOD(TestLoadXMLAndValidate)
		{
			string fileName = "test.xml";
			FileManager<MyItem> engine;
			engine.setFileName(fileName);
			Assert::IsTrue(engine.loadAndValidateXML());
		}

		TEST_METHOD(TestLoadToTree)
		{
			string fileName = "test.xml";
			FileManager<MyItem> engine;
			engine.setFileName(fileName);
			Assert::AreNotEqual(engine.getCountTree(), 0);
			//Assert::AreEqual(engine.getCountTree() > 0)
		}

		TEST_METHOD(TestLoadToTreeAndSearch)
		{
		//	string fileName = "test.xml";
		//	FileManager<MyItem> engine;
		//	engine.setFileName(fileName);
		//	Assert::AreNotEqual(engine.getCountTree(), 0);
		//	//Assert::AreEqual(engine.getCountTree() > 0)
		//	Assert::IsTrue(engine.findFile("1));
		}

		TEST_METHOD(TestToDisplayCurrentDirectoryFiles) {
			string fileName = "test.xml";
			FileManager<MyItem> engine;
			engine.setFileName(fileName);
			Assert::AreNotEqual(engine.getCountTree(), 0);
			TreeIterator<MyItem> iterator (engine.getTree());
			iterator.down();
			vector<MyItem> vector1 = engine.returnCurrentDirectory(iterator);
			int size = vector1.size();
			Assert::AreNotEqual(size, 0);
		}

	};
}