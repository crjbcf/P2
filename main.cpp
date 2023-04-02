#include <iostream>
#include <fstream>
#include "parser.h"
#include "parser.cpp"


using namespace std;

int main(int argc, char* argv[])
{
    fstream inputFile;
    string filename = "C://Users//chris//CLionProjects//P2(new)//myRandom.txt";

//    if (argc > 2)
//    {
//        cout << "Error: arguments should be no more than 2.\n"
//             << "P1 file1 file2\nFatal: Improper usage\nUsage: P0 [filename]\nPlease restart program, terminating....";
//        exit(0);
//    }
//    else if (argc == 2) //file provided
//    {
//        filename = argv[1];
//        inputFile.open(filename); //attempt to open file
//    }
//    else if (argc == 1) //no file provided take user input.
//    {
//        ofstream outFile;
//        outFile.open("userInput.txt");
//        string input;
//
//        if (outFile)
//        {
//            cout << "Enter your input (Type Ctrl+D when done): ";
//            while (getline(cin, input))
//            {
//                outFile << input;
//            }
//
//            outFile.close();
//
//            inputFile.open("userInput.txt");//attempt to open new file created with userInput
//        }
//    }

    inputFile.open(filename, ios::in);

    if (inputFile)
    {
        //cout << "File opened successfully\n";

        if(inputFile.get()== std::char_traits<char>::eof())
        {
            std::cout << "Error: File is Empty\nTerminating program...." << std:: endl;
            exit(0);
        }
        else
        {
            //cout << "file not empty\n";
            inputFile.unget();
        }

        parser(inputFile); //needs to be replaced with parser.
    }
    else
    {
        cout << "Error in opening the file";
    }

    inputFile.close();

    return 0;
}
