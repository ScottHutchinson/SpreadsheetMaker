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
    
    constexpr const unsigned int pugi_parse_settings = pugi::parse_default | pugi::parse_ws_pcdata; // TBD: | pugi::parse_comments

    class XLDocument {
        XLRelationships m_wbkRelationships{};
        XLWorkbook m_workbook{};
        IZipArchive m_archive{};
        std::string m_filePath;      /**< The path to the original file*/
        std::list<XLXmlData> m_data;
        std::deque<std::string> m_sharedStringCache;
        XLSharedStrings m_sharedStrings{};

        void close();
        void create(std::string_view xlsxFilePath);
        void open(std::string_view xlsxFilePath);

        /**
         * @brief Save the document with a new name. If a file exists with that name, it will be overwritten.
         * @param fileName The path of the file
         * @param forceOverwrite If not true (XLForceOverwrite) and fileName exists, saveAs will throw an exception
         * @throw XLException (OpenXLSX failed checks)
         * @throw ZipRuntimeError (zippy failed archive / file access)
         */
        void saveAs(const std::string& fileName, const bool forceOverwrite);
        void save();

    public:

        XLQuery execQuery(const XLQuery& query) const;
        const XLSharedStrings& sharedStrings() const { return m_sharedStrings; }

        /**
         * @brief Get the underlying workbook object, as a const object.
         * @return A const pointer to the XLWorkbook object.
         */
        XLWorkbook workbook() const;

        static void DLLEXPORT FromTextFile(const uint32_t numRows, std::string_view textFilePath, std::string_view xlsxFilePath, const char delimiter = ',');

        /**
         * @brief Get an XML file from the .xlsx archive.
         * @param path The relative path of the file.
         * @return A std::string with the content of the file
         */
        std::string extractXmlFromArchive(const std::string& path);
    };

} // namespace XLSXCreator
