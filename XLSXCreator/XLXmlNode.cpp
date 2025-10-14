#include "pch.h"
#include "XLXmlNode.h"

namespace XLSXCreator {

    /**
     * @details determine the first xml_node child whose xml_node_type matches type_
     * @date 2024-04-25
     */
    XMLNode XMLNode::first_child_of_type(pugi::xml_node_type type_) const {
        if (_root) {
            XMLNode x = first_child();
            XMLNode l = last_child();
            while (x != l && x.type() != type_) x = x.next_sibling();
            if (x.type() == type_)
                return XMLNode(x);
        }
        return XMLNode();    // if no node matching type_ was found: return an empty node
    }

    /**
     * @details determine the last xml_node child whose xml_node_type matches type_
     * @date 2024-04-25
     */
    XMLNode XMLNode::last_child_of_type(pugi::xml_node_type type_) const {
        if (_root) {
            XMLNode f = first_child();
            XMLNode x = last_child();
            while (x != f && x.type() != type_) x = x.previous_sibling();
            if (x.type() == type_)
                return XMLNode(x);
        }
        return XMLNode();    // if no node matching type_ was found: return an empty node
    }

    /**
     * @details determine amount of xml_node children child whose xml_node_type matches type_
     * @date 2024-04-28
     */
    size_t XMLNode::child_count_of_type(pugi::xml_node_type type_) const {
        size_t counter = 0;
        if (_root) {
            XMLNode c = first_child_of_type(type_);
            while (!c.empty()) {
                ++counter;
                c = c.next_sibling_of_type(type_);
            }
        }
        return counter;
    }

    /**
     * @details determine the next xml_node sibling whose xml_node_type matches type_
     * @date 2024-04-26
     */
    XMLNode XMLNode::next_sibling_of_type(pugi::xml_node_type type_) const {
        if (_root) {
            pugi::xml_node_struct* next = _root->next_sibling;
            while (next && (PUGI_IMPL_NODETYPE(next) != type_)) next = next->next_sibling;
            if (next)
                return XMLNode(next);
        }
        return XMLNode();    // if no node matching type_ was found: return an empty node
    }

    /**
     * @details determine the previous xml_node sibling whose xml_node_type matches type_
     * @date 2024-04-26
     */
    XMLNode XMLNode::previous_sibling_of_type(pugi::xml_node_type type_) const {
        if (_root) {
            pugi::xml_node_struct* prev = _root->prev_sibling_c;
            while (prev->next_sibling && (PUGI_IMPL_NODETYPE(prev) != type_)) prev = prev->prev_sibling_c;
            if (prev->next_sibling)
                return XMLNode(prev);
        }
        return XMLNode();    // if no node matching type_ was found: return an empty node
    }

    /**
     * @details determine the next xml_node sibling whose name() matches name_ and xml_node_type matches type_
     * @date 2024-04-26
     */
    XMLNode XMLNode::next_sibling_of_type(const pugi::char_t* name_, pugi::xml_node_type type_) const {
        if (_root) {
            for (pugi::xml_node_struct* i = _root->next_sibling; i; i = i->next_sibling) {
                const pugi::char_t* iname = i->name;
                if (iname && pugi::impl::strequal(name_, iname) && (PUGI_IMPL_NODETYPE(i) == type_))
                    return XMLNode(i);
            }
        }
        return XMLNode();    // if no node matching type_ was found: return an empty node
    }

    /**
     * @details determine the previous xml_node sibling whose name() matches name_ and xml_node_type matches type_
     * @date 2024-04-26
     */
    XMLNode XMLNode::previous_sibling_of_type(const pugi::char_t* name_, pugi::xml_node_type type_) const {
        if (_root) {
            for (pugi::xml_node_struct* i = _root->prev_sibling_c; i->next_sibling; i = i->prev_sibling_c) {
                const pugi::char_t* iname = i->name;
                if (iname && pugi::impl::strequal(name_, iname) && (PUGI_IMPL_NODETYPE(i) == type_))
                    return XMLNode(i);
            }
        }
        return XMLNode();    // if no node matching type_ was found: return an empty node
    }

} // namespace XLSXCreator
