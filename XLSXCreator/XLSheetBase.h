// XLSheetBase.h
#pragma once
#include "XLXmlFile.h"

namespace XLSXCreator {

    class XLSheetBase : public XLXmlFile {
    public:
        XLSheetBase() : XLXmlFile(nullptr) {};

        /**
         * @brief The constructor. There are no default constructor, so all parameters must be provided for
         * constructing an XLAbstractSheet object. Since this is a pure abstract class, instantiation is only
         * possible via one of the derived classes.
         * @param xmlData
         */
        explicit XLSheetBase(XLXmlData* xmlData) : XLXmlFile(xmlData) {}
    };

} // namespace XLSXCreator
