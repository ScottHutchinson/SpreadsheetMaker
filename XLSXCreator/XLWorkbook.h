// XLWorkbook.h
#pragma once
#include "XLWorksheet.h"
#include "XLXmlFile.h"

namespace XLSXCreator {

    class XLInputError : public std::runtime_error {
    public:

        explicit XLInputError(const std::string& _Message) : std::runtime_error(_Message.c_str()) {}

        explicit XLInputError(const char* _Message) : std::runtime_error(_Message) {}

    };

    class XLWorkbook : public XLXmlFile {
    public:
        XLWorkbook() = default;

        /**
         * @brief Get the worksheet with the given name.
         * @param sheetName The name of the desired worksheet.
         * @return
         */
        XLWorksheet worksheet(const std::string& sheetName);

    };

} // namespace XLSXCreator
