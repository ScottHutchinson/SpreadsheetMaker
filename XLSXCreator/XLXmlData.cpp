#include "pch.h"
#include "XLXmlData.h"
#include "XLDocument.h"

namespace XLSXCreator {

    XLDocument* XLXmlData::getParentDoc() {
        return m_parentDoc;
    }

    const XLDocument* XLXmlData::getParentDoc() const {
        return m_parentDoc;
    }

    XMLDocument* XLXmlData::getXmlDocument() {
        if (!m_xmlDoc->document_element())
            m_xmlDoc->load_string(m_parentDoc->extractXmlFromArchive(m_xmlPath).c_str(), pugi_parse_settings);

        return m_xmlDoc.get();
    }

    const XMLDocument* XLXmlData::getXmlDocument() const {
        if (!m_xmlDoc->document_element())
            m_xmlDoc->load_string(m_parentDoc->extractXmlFromArchive(m_xmlPath).c_str(), pugi_parse_settings);

        return m_xmlDoc.get();
    }

} // namespace XLSXCreator
