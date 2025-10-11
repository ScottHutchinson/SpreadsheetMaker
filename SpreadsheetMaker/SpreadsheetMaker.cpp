// SpreadsheetMaker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <chrono>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>
#include "XLSXCreator/XLDocument.h"

using std::string;
using std::string_view;
using std::vector;

int main() {
    string suffix;
    std::cin >> suffix;
    using namespace std::filesystem;
    //const string inputFilePathStr{ "C:\\Users\\scott\\Downloads\\products-10000.csv" };
    const string inputFilePathStr{ "C:\\Users\\scott\\Downloads\\large_string_data.csv" };
    std::ifstream file(inputFilePathStr);
    const auto count = static_cast<uint32_t>(std::count_if(std::istreambuf_iterator<char>{file}, {}, [](char c) { return c == '\n'; }));
    std::cout << "Number of lines in the file = " << count << "\n";
    file.seekg(0); // return the stream to the beginning of the file.
    path inputFilePath{ inputFilePathStr };
    path outputFilePath = inputFilePath.stem(); // file name without extension
    outputFilePath += " ";
    outputFilePath += suffix;
    outputFilePath = inputFilePath.parent_path() / outputFilePath.replace_extension("xlsx");
    std::cout << outputFilePath << "\n";
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    XLSXCreator::XLDocument::FromTextFile(inputFilePathStr, outputFilePath.string());
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Total Elapsed Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " milliseconds" << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
