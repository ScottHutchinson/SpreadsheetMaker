#include "pch.h"
#include "XLXmlFile.h"

namespace XLSXCreator {

    /**
     * @details The constructor creates a new object with the parent XLDocument and the file path as input, with
     * an optional input being a std::string with the XML data. If the XML data is provided by a string, any file with
     * the same path in the .zip file will be overwritten upon saving of the document. If no xmlData is provided,
     * the data will be read from the .zip file, using the given path.
     */
    XLXmlFile::XLXmlFile(XLXmlData* xmlData) : m_xmlData(xmlData) {}

    /**
     * @details
     */
    const XLDocument& XLXmlFile::parentDoc() const {
        return *m_xmlData->getParentDoc();
    }

    /**
     * @details
     */
    XLDocument& XLXmlFile::parentDoc() {
        return *m_xmlData->getParentDoc();
    }

} // namespace XLSXCreator
