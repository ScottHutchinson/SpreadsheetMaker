#include "pch.h"
#include "XLSheet.h"
#include "XLWorksheet.h"

namespace XLSXCreator {

    /**
     * @details The constructor begins by constructing an instance of its superclass, XLAbstractXMLFile. The default
     * sheet type is WorkSheet and the default sheet state is Visible.
     */
    XLSheet::XLSheet(XLXmlData* xmlData) : XLXmlFile(xmlData) {
        m_sheet = XLWorksheet(xmlData);
    }

    XLWorksheet XLSheet::get() {
        return m_sheet;
    }

} // namespace XLSXCreator
