// XLDocument.h
#pragma once
#include "IZipArchive.hpp"

#ifdef  XLSXCREATOR_EXPORTS 
   /*Enabled as "export" while compiling the dll project*/
#define DLLEXPORT __declspec(dllexport)  
#else
   /*Enabled as "import" in the Client side for using already created dll file*/
#define DLLEXPORT __declspec(dllimport)  
#endif

namespace XLSXCreator {

    class DLLEXPORT XLDocument {
        IZipArchive m_archive{};
        std::string m_filePath;      /**< The path to the original file*/
        mutable std::list<XLXmlData>    m_data{};
        mutable std::deque<std::string> m_sharedStringCache{};
        mutable XLSharedStrings         m_sharedStrings{};

        void close();
        void open(std::string_view xlsxFilePath);
        void create(std::string_view xlsxFilePath);

    public:
        static void FromTextFile(std::string_view textFilePath, std::string_view xlsxFilePath, const char delimiter = ',');
    };

} // namespace XLSXCreator
