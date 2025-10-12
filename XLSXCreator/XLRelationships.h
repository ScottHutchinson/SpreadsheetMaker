#pragma once
#include "XLXmlFile.h"

namespace XLSXCreator {

    class XLRelationshipItem {
    private:                                         // ---------- Private Member Variables ---------- //
        std::unique_ptr<XMLNode> m_relationshipNode; /**< An XMLNode object with the relationship item */
    public:

        /**
         * @brief Constructor. New items should only be created through an XLRelationship object.
         * @param node An XMLNode object with the relationship item. If no input is provided, a null node is used.
         */
        explicit XLRelationshipItem(const XMLNode& node);

        /**
         * @brief Get the target, i.e. the path to the XML file the relationship item refers to.
         * @return An XMLAttribute object containing the Target getValue.
         */
        std::string target() const;

    };

    class XLRelationships : public XLXmlFile {
    public:
        /**
         * @brief Look up a relationship item by ID.
         * @param id The ID string of the relationship item to retrieve.
         * @return An XLRelationshipItem object.
         */
        XLRelationshipItem relationshipById(const std::string& id) const;

    };

} // namespace XLSXCreator
