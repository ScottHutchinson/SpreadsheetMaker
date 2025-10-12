// XLWorkbook.h
#pragma once
#include "XLWorksheet.h"
#include "XLXmlFile.h"

namespace XLSXCreator {

    using XLInputError = std::runtime_error;

    class XLWorkbook : public XLXmlFile {
    public:

        /**
         * @brief Get the worksheet with the given name.
         * @param sheetName The name of the desired worksheet.
         * @return
         */
        XLWorksheet worksheet(const std::string& sheetName);

        /**
         * @brief This function provides access to the underlying XMLDocument object.
         * @return A reference to the XMLDocument object.
         */
        XMLDocument& xmlDocument();

        /**
         * @brief This function provides access to the underlying XMLDocument object.
         * @return A const reference to the XMLDocument object.
         */
        const XMLDocument& xmlDocument() const;

    };

} // namespace XLSXCreator
