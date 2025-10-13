// XLWorksheet.h
#pragma once
#include "XLRow.h"
#include "XLXmlData.h"
#include "XLSheetBase.h"

namespace XLSXCreator {

    class XLInternalError : public std::runtime_error {
    public:

        explicit XLInternalError(const std::string& _Message) : std::runtime_error(_Message.c_str()) {}

        explicit XLInternalError(const char* _Message) : std::runtime_error(_Message) {}

    };

    class XLWorksheet final : public XLSheetBase {
    public:
        XLWorksheet() : XLSheetBase(nullptr) {};
        explicit XLWorksheet(XLXmlData* xmlData);

        XLRowRange rows(uint32_t rowCount) const;

    };

} // namespace XLSXCreator
