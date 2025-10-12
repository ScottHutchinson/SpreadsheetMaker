// XLXmlFile.h
#pragma once
#include "XLXmlData.h"
#include "external/pugixml/pugixml.hpp"

namespace XLSXCreator {

    using XMLNode = pugi::xml_node;

    class XLDocument;

    using XMLDocument = pugi::xml_document;

    class XLXmlFile {
    public:
        XLXmlFile() = default;
        /**
         * @brief Constructor. Creates an object based on the xmlData input.
         * @param xmlData An XLXmlData object with the XML data to be represented by the object.
         */
        explicit XLXmlFile(XLXmlData* xmlData);

    protected:                            // ===== PROTECTED MEMBER VARIABLES
        XLXmlData* m_xmlData{ nullptr }; /**< The underlying XML data object. */

        /**
         * @brief This function provides access to the parent XLDocument object.
         * @return A reference to the parent XLDocument object.
         */
        XLDocument& parentDoc();

        /**
         * @brief This function provides access to the parent XLDocument object.
         * @return A const reference to the parent XLDocument object.
         */
        const XLDocument& parentDoc() const;

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
