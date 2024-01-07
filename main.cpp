#include <iostream>
#include <fstream>
#include "textEditor.h"
#include "gtest/gtest.h"
using namespace std;

TEST(CreateFileTest, BasicTest){
    string testFileName = "rahat1.txt";

    textEditor editor;
    editor.createFile();

    ifstream testFile(testFileName); // check if file is created
    ASSERT_TRUE(testFile.is_open()); // check if file is open
    testFile.close();

    // clean up: remove test file
    remove(testFileName.c_str());
}

// TEST(EditFileTest, BasicTest) {
//     string testFileName = "rahat_edit_test.txt";

//     // Create an instance of the textEditor class
//     textEditor editor;

//     // Create the initial content for the test file
//     ofstream initialFile(testFileName);
//     initialFile << "Initial content line 1\n"
//                 << "Initial content line 2\n";
//     initialFile.close();

//     // Call the editFile function
//     editor.editFile();  // Assuming editFile is a member function of textEditor

//     // Check if the file is modified as expected
//     ifstream modifiedFile(testFileName);
//     string line;
//     getline(modifiedFile, line); // Read the first line after edit
//     ASSERT_EQ(line, "Modified content line 1");

//     getline(modifiedFile, line); // Read the second line after edit
//     ASSERT_EQ(line, "Modified content line 2");

//     // Clean up: remove the test file
//     modifiedFile.close();
//     remove(testFileName.c_str());
// }

TEST(DisplayFileTest, BasicTest2) {
    string testFileName = "rahat_display_test.txt";

    // Create an instance of the textEditor class
    textEditor editor;

    // Create the test file with content
    ofstream testFile(testFileName);
    testFile << "Line 1\n"
             << "Line 2\n"
             << "Line 3\n";
    testFile.close();

    // Redirect cout to a stringstream for testing
    std::stringstream buffer;
    std::streambuf* oldCout = std::cout.rdbuf(buffer.rdbuf());

    // Call the displayFile function
    editor.displayFile();  // Assuming displayFile is a member function of textEditor

    // Reset cout to its normal state
    std::cout.rdbuf(oldCout);

    // Check if the output matches the expected content
    std::string output = buffer.str();
    ASSERT_EQ(output, "Line 1\nLine 2\nLine 3\n");

    // Clean up: remove the test file
    remove(testFileName.c_str());
}





int main()
{
    textEditor t1; // Class object creation
    t1.mainMenu();
    t1.mainChoice();

    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}