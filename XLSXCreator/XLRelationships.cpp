#include "pch.h"
#include "XLRelationships.h"

namespace XLSXCreator {

    /**
     * @details Constructor. Initializes the member variables for the new XLRelationshipItem object.
     */
    XLRelationshipItem::XLRelationshipItem(const XMLNode& node) : m_relationshipNode(std::make_unique<XMLNode>(node)) {}

    /**
     * @details Returns the m_relationshipTarget member variable by getValue.
     */
    std::string XLRelationshipItem::target() const {
        // 2024-12-15 Returned to old behavior: do not strip leading slashes as this loses info about path being absolute.
        //            Instead, treat absolute vs. relative path distinction in caller
        return m_relationshipNode->attribute("Target").value();
    }

    /**
     * @details Returns the XLRelationshipItem with the given ID, by looking it up in the m_relationships map.
     */
    XLRelationshipItem XLRelationships::relationshipById(const std::string& id) const {
        return XLRelationshipItem(xmlDocument().document_element().find_child_by_attribute("Id", id.c_str()));
    }

} // namespace XLSXCreator
