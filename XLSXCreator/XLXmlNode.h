#pragma once
#include "external/pugixml/pugixml.hpp"

namespace XLSXCreator {

    extern bool NO_XML_NS; // defined in XLXmlParser.cpp - default: no XML namespaces

    class XLXmlNode;

    using XMLNode = XLXmlNode;

    class XLXmlNode : public pugi::xml_node {
        int  name_begin; // nameBegin holds the position in xml_node::name() where the actual node name begins - 0 for non-namespaced nodes
        // for nodes with a namespace: the position following namespace + delimiter colon, e.g. "x:c" -> nameBegin = 2
    public:
        /**
         * @brief Default constructor. Constructs a null object.
         */
        XLXmlNode() : pugi::xml_node(), name_begin(0) {}

        /**
         * @brief Inherit all constructors with parameters from pugi::xml_node
         */
        template<class base>
        // explicit OpenXLSX_xml_node(base b) : pugi::xml_node(b), name_begin(0) // TBD on explicit keyword
        XLXmlNode(base b) : pugi::xml_node(b), name_begin(0) {
            if (NO_XML_NS) return;
            const char* name = xml_node::name();
            int pos = 0;
            while (name[pos] && name[pos] != ':') ++pos; // find name delimiter
            if (name[pos] == ':') name_begin = pos + 1;  // if delimiter was found: update name_begin to point behind that position
        }

        XMLNode find_child_by_attribute(const pugi::char_t* name_, const pugi::char_t* attr_name, const pugi::char_t* attr_value) const {
            return static_cast<XMLNode>(xml_node::find_child_by_attribute(NAMESPACED_NAME(name_, false), attr_name, attr_value));
        }
        XMLNode find_child_by_attribute(const pugi::char_t* attr_name, const pugi::char_t* attr_value) const {
            return xml_node::find_child_by_attribute(attr_name, attr_value);
        }

        /**
         * @brief get first node child that matches type
         * @param type_ the pugi::xml_node_type to match
         * @return a valid child matching the node type or an empty XMLNode
         */
        XMLNode first_child_of_type(pugi::xml_node_type type_ = pugi::node_element) const;

        /**
         * @brief get last node child that matches type
         * @param type_ the pugi::xml_node_type to match
         * @return a valid child matching the node type or an empty XMLNode
         */
        XMLNode last_child_of_type(pugi::xml_node_type type_ = pugi::node_element) const;

        /**
         * @brief count node children that match type
         * @param type_ the pugi::xml_node_type to match
         * @return the amount of node children matching type
         */
        size_t child_count_of_type(pugi::xml_node_type type_ = pugi::node_element) const;

        /**
         * @brief get next node sibling that matches type
         * @param type_ the pugi::xml_node_type to match
         * @return a valid sibling matching the node type or an empty XMLNode
         */
        XMLNode next_sibling_of_type(pugi::xml_node_type type_ = pugi::node_element) const;

        /**
         * @brief get previous node sibling that matches type
         * @param type_ the pugi::xml_node_type to match
         * @return a valid sibling matching the node type or an empty XMLNode
         */
        XMLNode previous_sibling_of_type(pugi::xml_node_type type_ = pugi::node_element) const;

        /**
         * @brief get next node sibling that matches name_ and type
         * @param name_ the xml_node::name() to match
         * @param type_ the pugi::xml_node_type to match
         * @return a valid sibling matching the node type or an empty XMLNode
         */
        XMLNode next_sibling_of_type(const pugi::char_t* name_, pugi::xml_node_type type_ = pugi::node_element) const;

        /**
         * @brief get previous node sibling that matches name_ and type
         * @param name_ the xml_node::name() to match
         * @param type_ the pugi::xml_node_type to match
         * @return a valid sibling matching the node type or an empty XMLNode
         */
        XMLNode previous_sibling_of_type(const pugi::char_t* name_, pugi::xml_node_type type_ = pugi::node_element) const;

    };

} // namespace XLSXCreator
