#include "pch.h"
#include "XLDocument.h"

namespace XLSXCreator {

    void XLDocument::Create(std::string_view /*xlsxFilePath*/) {
    }

    void XLDocument::FromTextFile(std::string_view /*textFilePath*/, std::string_view xlsxFilePath, const char /*delimiter*/) {
        XLDocument doc;
        doc.Create(xlsxFilePath);
        //XLWorkbook wb = doc.workbook();
        //XLWorksheet ws = wb.worksheet("Sheet1");
        //vector<XLCellValue> cellValues;
        //cellValues.reserve(600); // number of columns
        //string line;
        //for (auto& row : ws.rows(count)) {
        //    cellValues.clear();
        //    std::getline(file, line);
        //    std::stringstream ss(line);
        //    string cellValue;
        //    // TODO: Handle quoted string values.
        //    while (std::getline(ss, cellValue, ',')) {
        //        cellValues.emplace_back(cellValue);
        //    }

        //    row.values() = cellValues;
        //}
        //std::chrono::steady_clock::time_point xmlEnd = std::chrono::steady_clock::now();
        //std::cout << "XML Elapsed Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(xmlEnd - begin).count() << " milliseconds" << std::endl;
        //doc.save();
        //std::chrono::steady_clock::time_point saveEnd = std::chrono::steady_clock::now();
        //std::cout << "Save Elapsed Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(saveEnd - xmlEnd).count() << " milliseconds" << std::endl;
        //doc.close();
        //std::chrono::steady_clock::time_point closeEnd = std::chrono::steady_clock::now();
        //std::cout << "Close Elapsed Time = " << std::chrono::duration_cast<std::chrono::milliseconds>(closeEnd - saveEnd).count() << " milliseconds" << std::endl;
    }

} // namespace XLSXCreator
