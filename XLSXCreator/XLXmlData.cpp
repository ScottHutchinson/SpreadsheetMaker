#include "pch.h"
#include "XLDocument.h"
#include "XLXmlData.h"

namespace XLSXCreator {

    XLDocument* XLXmlData::getParentDoc() {
        return m_parentDoc;
    }

    const XLDocument* XLXmlData::getParentDoc() const {
        return m_parentDoc;
    }

} // namespace XLSXCreator
