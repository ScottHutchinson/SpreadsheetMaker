// SpreadsheetMaker.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "OpenXLSX/OpenXLSX.hpp"

using std::string;
using std::vector;

int main() {
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    using namespace OpenXLSX;
    const string inputFilePath{ "C:\\Users\\scott\\Downloads\\products-10000.csv" };
    XLDocument doc;
    doc.create("C:\\Users\\scott\\Downloads\\products-10000.xlsx", true);
    XLWorkbook wb = doc.workbook();
    XLWorksheet ws = wb.worksheet("Sheet1");

    std::ifstream file(inputFilePath);
    string line;
    uint32_t row{ 1 };
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        string cellValue;
        uint16_t col{ 1 };
        while (std::getline(ss, cellValue, ',')) {
            ws.cell(row, col).value() = cellValue;
            col++;
        }
        row++;
    }
    doc.save();
    doc.close();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Elapsed Time = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() << " seconds" << std::endl;
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
