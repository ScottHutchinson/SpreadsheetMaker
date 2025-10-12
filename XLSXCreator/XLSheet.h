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

        template<typename T, typename = std::enable_if_t<std::is_same_v<T, XLWorksheet> || std::is_same_v<T, XLChartsheet>>>
        T get() const {
            try {
                if constexpr (std::is_same<T, XLWorksheet>::value)
                    return std::get<XLWorksheet>(m_sheet);

                //else if constexpr (std::is_same<T, XLChartsheet>::value)
                //    return std::get<XLChartsheet>(m_sheet);
            }

            catch (const std::bad_variant_access&) {
                throw XLSheetError("XLSheet object does not contain the requested sheet type.");
            }
        }

    };

} // namespace XLSXCreator
