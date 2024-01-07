#include <iostream>
#include <fstream>
// #include "gtest/gtest.h"
using namespace std;

class textEditor
{
public:
    int choice;
    string fileName;
    // Menu
    void mainMenu()
    {
        cout << "1.  Create File." << endl;
        cout << "2.  Edit File." << endl;
        cout << "3.  Display File." << endl;
        cout << "4.  Delete File." << endl;
        cout << "5.  Remove All Occurances." << endl;
        cout << "6.  Remove Comments." << endl;
        cout << "0.  Exit." << endl;
        cout << ": ";
        cin >> choice;
        cin.ignore(); // Clearing the input buffer
    }

    // Choice
    void mainChoice()
    {
        while (choice != 0)
        {
            switch (choice)
            {
            case 1:
                createFile();
                break;
            case 2:
                editFile();
                break;
            case 3:
                displayFile();
                break;
            case 4:
                deleteFile();
                break;
            case 5:
                removeOccurance();
                break;
            case 6:
                removeComments();
                break;
            case 0:
                break;
            defualt:
                cout << "Somethings wrong!" << endl;
                break;
            }
            mainMenu(); // Display the menu again
        }
        cout << "Exiting the text Editor!" << endl;
    }

    // 1 Create File Function
    void createFile()
    {
        cout << "Enter file name: ";
        getline(cin, fileName);
        ofstream File(fileName); // Create and open file

        if (File.is_open())
        {
            cout << "File: '" << fileName << "' created successfully." << endl;
        }
    }

    // 2 Edit File Function
    void editFile()
    {
        string fileName;
        string text, line;

        // Prompt user to enter file name
        cout << "Enter the file name to append text: ";
        getline(cin, fileName);

        // Display current text
        ifstream File(fileName);
        if (File.is_open())
        {
            cout << "Content of file '" << fileName << "': " << endl;
            while (getline(File, line))
            {
                cout << line << endl;
            }
            File.close();
        }
        else
        {
            cout << "Error opening file '" << fileName << "'" << endl;
        }

        // Open the file in append mode
        ofstream outputFile(fileName, ios::app);

        if (!outputFile.is_open())
        {
            cerr << "Error opening file '" << fileName << "' for appending." << endl;
            return;
        }

        // Prompt user to enter text to append
        cout << "Enter the text to append (press Ctrl+D on a new line to finish):\n";
        text.clear(); // Clear the text to get user input

        while (cin >> ws && getline(cin, text))
        {
            text += '\n';
            outputFile << text; // Append the text to the file
        }

        outputFile.close();
        cout << "Text appended to the file successfully." << endl;
    }

    // 3 Display file function
    void displayFile()
    {
        string line;
        cout << "Enter file name: ";
        getline(cin, fileName);

        ifstream File(fileName);
        if (File.is_open())
        {
            cout << "Content of file '" << fileName << "': " << endl;
            while (getline(File, line))
            {
                cout << line << endl;
            }
            File.close();
        }
        else
        {
            cout << "Error opening file '" << fileName << "'" << endl;
        }
    }

    // 4 Delete File Function
    void deleteFile()
    {
        cout << "Enter file name: ";
        getline(cin, fileName);

        if (remove(fileName.c_str()) == 0)
        {
            cout << "File deleted!" << endl;
        }
        else
        {
            cout << "Error deleting file!" << endl;
        }
    }

    // 5 Remove Occurances Function
    void removeOccurance() {
    string fileName;
    string searchStr, replacementStr;

    // Prompt user to enter file name
    cout << "Enter the file name: ";
    getline(cin, fileName);

    // Open the file for reading
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cerr << "Error opening file '" << fileName << "' for reading." << endl;
        return;
    }

    // Read the entire content of the file into a string
    string content((istreambuf_iterator<char>(inFile)), (istreambuf_iterator<char>()));
    inFile.close();

    // Prompt user to enter search string
    cout << "Enter the search string: ";
    getline(cin, searchStr);

    // Prompt user to enter replacement string
    cout << "Enter the replacement string: ";
    getline(cin, replacementStr);

    // Perform replacement
    size_t startPos = 0;
    while ((startPos = content.find(searchStr, startPos)) != string::npos) {
        content.replace(startPos, searchStr.length(), replacementStr);
        startPos += replacementStr.length();
    }

    // Open the file for writing (truncate existing content)
    ofstream outFile(fileName, ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Error opening file '" << fileName << "' for writing." << endl;
        return;
    }

    // Write the modified content back to the file
    outFile << content;
    outFile.close();

    cout << "Replacement completed successfully." << endl;
}

    // 6 Remove Comments
    void removeComments() {
    string fileName;
    cout << "Enter file Name: ";
    getline(cin, fileName);


    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cerr << "Error opening file '" << fileName << "' for reading." << endl;
        return;
    }

    // Read the entire content of the file into a string
    string content((istreambuf_iterator<char>(inFile)), (istreambuf_iterator<char>()));
    inFile.close();

    // Remove single-line comments
    size_t singleLinePos = 0;
    while ((singleLinePos = content.find("//", singleLinePos)) != string::npos) {
        size_t lineEnd = content.find('\n', singleLinePos);
        if (lineEnd != string::npos) {
            content.erase(singleLinePos, lineEnd - singleLinePos);
        } else {
            content.erase(singleLinePos);
        }
    }

    // Remove multi-line comments
    size_t multiLinePos = 0;
    while ((multiLinePos = content.find("/*", multiLinePos)) != string::npos) {
        size_t commentEnd = content.find("*/", multiLinePos);
        if (commentEnd != string::npos) {
            content.erase(multiLinePos, commentEnd - multiLinePos + 2); // Including "*/"
        } else {
            cerr << "Error: Unclosed multi-line comment in file '" << fileName << "'." << endl;
            return;
        }
    }

    // Open the file for writing (truncate existing content)
    ofstream outFile(fileName, ios::trunc);
    if (!outFile.is_open()) {
        cerr << "Error opening file '" << fileName << "' for writing." << endl;
        return;
    }

    // Write the modified content back to the file
    outFile << content;
    outFile.close();

    cout << "Comments removed successfully. Modified content saved to '" << fileName << "'." << endl;
}
};