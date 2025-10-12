// XLDocument.h
#pragma once
#include "IZipArchive.hpp"
#include "XLCommandQuery.h"
#include "XLRelationships.h"
#include "XLSharedStrings.h"
#include "XLWorkbook.h"
#include "XLXmlData.h"
#include <deque>
#include <list>

#ifdef  XLSXCREATOR_EXPORTS 
   /*Enabled as "export" while compiling the dll project*/
#define DLLEXPORT __declspec(dllexport)  
#else
   /*Enabled as "import" in the Client side for using already created dll file*/
#define DLLEXPORT __declspec(dllimport)  
#endif

namespace XLSXCreator {
    
    class XLDocument {
        XLRelationships m_wbkRelationships{};
        XLWorkbook m_workbook{};
        IZipArchive m_archive{};
        std::string m_filePath;      /**< The path to the original file*/
        std::list<XLXmlData> m_data;
        std::deque<std::string> m_sharedStringCache;
        XLSharedStrings m_sharedStrings{};

        void close();
        void open(std::string_view xlsxFilePath);
        void create(std::string_view xlsxFilePath);

    public:

        XLQuery execQuery(const XLQuery& query) const;

        /**
         * @brief Get the underlying workbook object, as a const object.
         * @return A const pointer to the XLWorkbook object.
         */
        XLWorkbook workbook() const;

        static void DLLEXPORT FromTextFile(std::string_view textFilePath, std::string_view xlsxFilePath, const char delimiter = ',');
    };

} // namespace XLSXCreator
