#include "pch.h"
#include "CppUnitTest.h"
#include "../ADS_CA2/FileManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ADSCA2TEST
{
	TEST_CLASS(ADSCA2TEST)
	{
	public:
		string fileName = "test.xml";

		TEST_METHOD(TestLoadXMLAndValidate)
		{
			FileManager<MyItem> engine;
			engine.setFileName(fileName);
			Assert::IsTrue(engine.loadAndValidateXML());
		}

		TEST_METHOD(TestLoadToTree)
		{
			FileManager<MyItem> engine;
			engine.setFileName(fileName);
			engine.loadToTree(); 
			Assert::AreNotEqual(engine.getCountTree(), 0);
			// Add more assertions based on the expected structure of your tree
		}


		TEST_METHOD(TestToFindFile)
		{
			FileManager<MyItem> engine(fileName);
			engine.loadToTree();
			
			vector<string> result = engine.findFile("config");
			Assert::IsTrue(result.size() > 0);
		}

		TEST_METHOD(TestPruneEmptyFolders)
		{
			
			FileManager<MyItem> engine(fileName);
			Tree<MyItem>* tree = engine.getTree();
			engine.loadToTree();
			engine.toPruneFolders();

		}

		TEST_METHOD(TestReturnFolderContent) {
			FileManager<MyItem> engine(fileName);
			engine.loadToTree();
			vector<MyItem> results = engine.toPrinTheWholeDirectory("Debug");
			Assert::IsTrue(results.size() > 0);
		}

		TEST_METHOD(TestCalculateSize)
		{
			FileManager<MyItem> engine(fileName);
			engine.loadToTree();
			int expected = 2966521;
			Tree<MyItem>* tree = engine.getTree();
			Assert::AreEqual(engine.calculateSize(tree), expected);
		}



	};
}