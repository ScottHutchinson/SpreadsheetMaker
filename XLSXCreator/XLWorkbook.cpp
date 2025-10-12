#include "pch.h"
#include "XLDocument.h"
#include "XLSheet.h"
#include "XLWorkbook.h"
#include "XLCommandQuery.h"

namespace XLSXCreator {

    XLWorksheet XLWorkbook::worksheet(const std::string& sheetName) {
        // ===== First determine if the sheet exists.
        if (xmlDocument().document_element().child("sheets").find_child_by_attribute("name", sheetName.c_str()) == nullptr)
            throw XLInputError("Sheet \"" + sheetName + "\" does not exist");

        // ===== Find the sheet data corresponding to the sheet with the requested name
        const std::string xmlID =
            xmlDocument().document_element().child("sheets").find_child_by_attribute("name", sheetName.c_str()).attribute("r:id").value();

        XLQuery pathQuery(XLQueryType::QuerySheetRelsTarget);
        pathQuery.setParam("sheetID", xmlID);
        auto xmlPath = parentDoc().execQuery(pathQuery).result<std::string>();

        //// Some spreadsheets use absolute rather than relative paths in relationship items.
        if (xmlPath.substr(0, 4) == "/xl/") {
            xmlPath = xmlPath.substr(4);
        }
        XLQuery xmlQuery(XLQueryType::QueryXmlData);
        xmlQuery.setParam("xmlPath", "xl/" + xmlPath);
        auto sheet = XLSheet(parentDoc().execQuery(xmlQuery).result<XLXmlData*>());
        return sheet.get<XLWorksheet>();
    }

} // namespace XLSXCreator
