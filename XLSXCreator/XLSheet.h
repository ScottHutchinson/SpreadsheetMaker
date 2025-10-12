// XLSheet.h
#pragma once
#include "XLXmlFile.h"
#include "XLWorksheet.h"
#include <variant>

namespace XLSXCreator {

    /**
     * @brief The XLAbstractSheet is a generalized sheet class, which functions as superclass for specialized classes,
     * such as XLWorksheet. It implements functionality common to all sheet types. This is a pure abstract class,
     * so it cannot be instantiated.
     */
    class XLSheet final : public XLXmlFile {
    private:   // ---------- Private Member Variables ---------- //
        std::variant<XLWorksheet, XLWorksheet> m_sheet; // TODO: XLChartsheet
    public:
        /**
         * @brief The constructor. There are no default constructor, so all parameters must be provided for
         * constructing an XLAbstractSheet object. Since this is a pure abstract class, instantiation is only
         * possible via one of the derived classes.
         * @param xmlData
         */
        explicit XLSheet(XLXmlData* xmlData);
    };

} // namespace XLSXCreator
