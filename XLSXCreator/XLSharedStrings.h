// XLSharedStrings.h
#pragma once

namespace XLSXCreator {


    class XLSharedStrings; // forward declaration
    using XLSharedStringsRef = std::reference_wrapper<const XLSharedStrings>;
    extern const XLSharedStrings XLSharedStringsDefaulted; // to be used for default initialization of all references of type XLSharedStrings

    class XLSharedStrings /*: public XLXmlFile*/ {
    };

} // namespace XLSXCreator
