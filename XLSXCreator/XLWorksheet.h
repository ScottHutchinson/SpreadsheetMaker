// XLWorksheet.h
#pragma once
#include "XLXmlData.h"
#include "XLXmlFile.h"

namespace XLSXCreator {

    class XLInternalError : public std::runtime_error {
    public:

        explicit XLInternalError(const std::string& _Message) : std::runtime_error(_Message.c_str()) {}

        explicit XLInternalError(const char* _Message) : std::runtime_error(_Message) {}

    };

    class XLWorksheet : public XLXmlFile { // TODO: inherit XLSheetBase?
    public:
        explicit XLWorksheet(XLXmlData* xmlData);

    };

} // namespace XLSXCreator
