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
#include "OpenXLSX/OpenXLSX.hpp"

using std::string;
using std::string_view;
using std::vector;

int main() {
    string suffix;
    std::cin >> suffix;
    using namespace std::filesystem;
    using namespace OpenXLSX;
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
    XLDocument doc;
    doc.create(outputFilePath.string(), true);
    XLWorkbook wb = doc.workbook();
    XLWorksheet ws = wb.worksheet("Sheet1");
    vector<XLCellValue> cellValues;
    cellValues.reserve(600); // number of columns
    string line;
    for (auto& row : ws.rows(count)) {
        cellValues.clear();
        std::getline(file, line);
        std::stringstream ss(line);
        string cellValue;
        // TODO: Handle quoted string values.
        while (std::getline(ss, cellValue, ',')) {
            cellValues.emplace_back(cellValue);
        }

        row.values() = cellValues;
    }
    std::chrono::steady_clock::time_point xmlEnd = std::chrono::steady_clock::now();
    std::cout << "XML Elapsed Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(xmlEnd - begin).count() << " milliseconds" << std::endl;
    doc.save();
    std::chrono::steady_clock::time_point saveEnd = std::chrono::steady_clock::now();
    std::cout << "Save Elapsed Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(saveEnd - xmlEnd).count() << " milliseconds" << std::endl;
    doc.close();
    std::chrono::steady_clock::time_point closeEnd = std::chrono::steady_clock::now();
    std::cout << "Close Elapsed Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(closeEnd - saveEnd).count() << " milliseconds" << std::endl;
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
