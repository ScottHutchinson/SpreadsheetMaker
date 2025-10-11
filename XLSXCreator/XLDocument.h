// XLDocument.h
#pragma once
#include <string_view>

#ifdef  XLSXCREATOR_EXPORTS 
   /*Enabled as "export" while compiling the dll project*/
#define DLLEXPORT __declspec(dllexport)  
#else
   /*Enabled as "import" in the Client side for using already created dll file*/
#define DLLEXPORT __declspec(dllimport)  
#endif

namespace XLSXCreator {

    class DLLEXPORT XLDocument {
    public:
        static void FromTextFile(std::string_view textFilePath, std::string_view xlsxFilePath, const char delimiter = ',');
        void Create(std::string_view xlsxFilePath);
    };

} // namespace XLSXCreator
