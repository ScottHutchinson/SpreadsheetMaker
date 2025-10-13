#include "pch.h"
#include "XLWorksheet.h"
#include "XLDocument.h"
#include "external/pugixml/pugixml.hpp"

namespace XLSXCreator {

    /**
     * @details determine the first xml_node child whose xml_node_type matches type_
     * @date 2024-04-25
     */
    //static XMLNode first_child_of_type(XMLNode const& node, pugi::xml_node_type type_) {
    //    if (node.root()) {
    //        XMLNode x = node.first_child();
    //        XMLNode l = node.last_child();
    //        while (x != l && x.type() != type_) x = x.next_sibling();
    //        if (x.type() == type_)
    //            return XMLNode(x);
    //    }
    //    return XMLNode();    // if no node matching type_ was found: return an empty node
    //}

    // ===== Copy definition of PUGI_IMPL_NODETYPE, which is defined in pugixml.cpp, within namespace pugi::impl(?), and somehow doesn't work here
#   define PUGI_IMPL_NODETYPE(n) static_cast<pugi::xml_node_type>((n)->header & pugi::impl::xml_memory_page_type_mask)

    /**
     * @details The constructor does some slight reconfiguration of the XML file, in order to make parsing easier.
     * For example, columns with identical formatting are by default grouped under the same node. However, this makes it more difficult to
     * parse, so the constructor reconfigures it so each column has it's own formatting.
     */
    XLWorksheet::XLWorksheet(XLXmlData* xmlData) : XLSheetBase(xmlData) {
        // ===== Read the dimensions of the Sheet and set data members accordingly.
    //    if (const std::string dimensions = xmlDocument().document_element().child("dimension").attribute("ref").value();
    //        dimensions.find(':') == std::string::npos)
    //        xmlDocument().document_element().child("dimension").set_value("A1");
    //    else
    //        xmlDocument().document_element().child("dimension").set_value(dimensions.substr(dimensions.find(':') + 1).c_str());

    //    // If Column properties are grouped, divide them into properties for individual Columns.
    //    if (xmlDocument().document_element().child("cols").type() != pugi::node_null) {
    //        auto currentNode = first_child_of_type(xmlDocument().document_element().child("cols"), pugi::node_element);
    //        while (not currentNode.empty()) {
    //            uint16_t min{};
    //            uint16_t max{};
    //            try {
    //                min = static_cast<uint16_t>(std::stoul(currentNode.attribute("min").value()));
    //                max = static_cast<uint16_t>(std::stoul(currentNode.attribute("max").value()));
    //            }
    //            catch (...) {
    //                throw XLInternalError("Worksheet column min and/or max attributes are invalid.");
    //            }
    //            if (min != max) {
    //                currentNode.attribute("min").set_value(max);
    //                for (uint16_t i = min; i < max; i++) {    // NOLINT
    //                    auto newnode = xmlDocument().document_element().child("cols").insert_child_before("col", currentNode);
    //                    auto attr = currentNode.first_attribute();
    //                    while (not attr.empty()) {    // NOLINT
    //                        newnode.append_attribute(attr.name()) = attr.value();
    //                        attr = attr.next_attribute();
    //                    }
    //                    newnode.attribute("min") = i;
    //                    newnode.attribute("max") = i;
    //                }
    //            }
    //            currentNode = currentNode.next_sibling_of_type(pugi::node_element);
    //        }
    //    }
    } // XLWorksheet::XLWorksheet

    XLRowRange XLWorksheet::rows(uint32_t rowCount) const {
        return XLRowRange(xmlDocument().document_element().child("sheetData"),
            1,
            rowCount,
            parentDoc().sharedStrings());
    }

} // namespace XLSXCreator
