#include "pch.h"
#include "XLRow.h"

namespace XLSXCreator {

    inline XMLNode getRowNode(XMLNode sheetDataNode, uint32_t rowNumber) {
        if (rowNumber < 1 || rowNumber > MAX_ROWS) {    // 2024-05-28: added range check
            using namespace std::literals::string_literals;
            throw XLCellAddressError("rowNumber "s + std::to_string(rowNumber) + " is outside valid range [1;"s + std::to_string(MAX_ROWS) + "]"s);
        }

        // ===== Get the last child of sheetDataNode that is of type node_element.
        XMLNode result = sheetDataNode.last_child_of_type(pugi::node_element);

        // ===== If there are now rows in the worksheet, or the requested row is beyond the current max row, append a new row to the end.
        if (result.empty() || (rowNumber > result.attribute("r").as_ullong())) {
            result = sheetDataNode.append_child("row");
            result.append_attribute("r") = rowNumber;
            //            result.append_attribute("x14ac:dyDescent") = "0.2";
            //            result.append_attribute("spans")           = "1:1";
        }

        // ===== If the requested node is closest to the end, start from the end and search backwards.
        else if (result.attribute("r").as_ullong() - rowNumber < rowNumber) {
            while (not result.empty() && (result.attribute("r").as_ullong() > rowNumber)) result = result.previous_sibling_of_type(pugi::node_element);
            // ===== If the backwards search failed to locate the requested row
            if (result.empty() || (result.attribute("r").as_ullong() != rowNumber)) {
                if (result.empty())
                    result = sheetDataNode.prepend_child("row"); // insert a new row node at datasheet begin. When saving, this will keep whitespace formatting towards next row node
                else
                    result = sheetDataNode.insert_child_after("row", result);
                result.append_attribute("r") = rowNumber;
                //                result.append_attribute("x14ac:dyDescent") = "0.2";
                //                result.append_attribute("spans")           = "1:1";
            }
        }

        // ===== Otherwise, start from the beginning
        else {
            // ===== At this point, it is guaranteed that there is at least one node_element in the row that is not empty.
            result = sheetDataNode.first_child_of_type(pugi::node_element);

            // ===== It has been verified above that the requested rowNumber is <= the row number of the last node_element, therefore this loop will halt.
            while (result.attribute("r").as_ullong() < rowNumber) result = result.next_sibling_of_type(pugi::node_element);
            // ===== If the forwards search failed to locate the requested row
            if (result.attribute("r").as_ullong() > rowNumber) {
                result = sheetDataNode.insert_child_before("row", result);

                result.append_attribute("r") = rowNumber;
                //                result.append_attribute("x14ac:dyDescent") = "0.2";
                //                result.append_attribute("spans")           = "1:1";
            }
        }

        return result;
    }

    XLRow::XLRow()
        : m_rowNode(nullptr),
        m_sharedStrings(XLSharedStringsDefaulted),
        m_rowDataProxy(this, m_rowNode.get()) {
    }

    /**
     * @details Constructs a new XLRow object from information in the underlying XML file. A pointer to the corresponding
     * node in the underlying XML file must be provided.
     * @pre
     * @post
     */
    XLRow::XLRow(const XMLNode& rowNode, const XLSharedStrings& sharedStrings)
        : m_rowNode(std::make_unique<XMLNode>(rowNode)),
        m_sharedStrings(sharedStrings),
        m_rowDataProxy(this, m_rowNode.get()) {
    }

    XLRowDataProxy& XLRow::values() { return m_rowDataProxy; }

    bool XLRow::empty() const { return (!m_rowNode) || m_rowNode->empty(); }

    /**
     * @brief update m_currentRow by fetching (or inserting) a row at m_currentRowNumber
     */
    void XLRowIterator::updateCurrentRow(bool createIfMissing) {
        // ===== Quick exit checks - can't be true when m_endReached
        if (m_currentRowStatus == XLLoaded) return;                           // nothing to do, row is already loaded
        if (!createIfMissing && m_currentRowStatus == XLNoSuchRow) return;    // nothing to do, row has already been determined as missing

        // ===== At this stage, m_currentRowStatus is XLUnloaded or XLNoSuchRow and createIfMissing == true

        if (m_endReached)
            throw XLInputError("XLRowIterator updateCurrentRow: iterator should not be dereferenced when endReached() == true");

        // ===== Row needs to be updated

        if (m_hintRow.empty()) {  // no hint has been established: fetch first row node the "tedious" way
            if (createIfMissing)     // getRowNode creates missing rows
                m_currentRow = XLRow(getRowNode(*m_dataNode, m_currentRowNumber), m_sharedStrings.get());
            else                    // findRowNode returns an empty row for missing rows
                m_currentRow = XLRow(findRowNode(*m_dataNode, m_currentRowNumber), m_sharedStrings.get());
        }
        else {
            // ===== Find or create, and fetch an XLRow at m_currentRowNumber
            if (m_currentRowNumber > m_hintRowNumber) {
                // ===== Start from m_hintRow and search forwards...
                XMLNode rowNode = m_hintRow.next_sibling_of_type(pugi::node_element);
                uint32_t rowNo = 0;
                while (not rowNode.empty()) {
                    rowNo = rowNode.attribute("r").as_ullong();
                    if (rowNo >= m_currentRowNumber) break; // if desired row was reached / passed, break before incrementing rowNode
                    rowNode = rowNode.next_sibling_of_type(pugi::node_element);
                }
                if (rowNo != m_currentRowNumber) rowNode = XMLNode{}; // if a higher row number was found, set empty node (means: "missing")

                // ===== Create missing row node if createIfMissing == true
                if (createIfMissing && rowNode.empty()) {
                    rowNode = m_dataNode->insert_child_after("row", m_hintRow);
                    rowNode.append_attribute("r").set_value(m_currentRowNumber);
                }
                if (rowNode.empty())    // if row could not be found / created
                    m_currentRow = XLRow{}; // make sure m_currentRow is set to an empty cell
                else
                    m_currentRow = XLRow(rowNode, m_sharedStrings.get());
            }
            else
                throw XLInternalError("XLRowIterator::updateCurrentRow: an internal error occured (m_currentRowNumber <= m_hintRowNumber)");
        }

        if (m_currentRow.empty())   // if row is confirmed missing
            m_currentRowStatus = XLNoSuchRow;   // mark this status for further calls to updateCurrentRow()
        else {
            // ===== If the current row exists, update the hints
            m_hintRow = *m_currentRow.m_rowNode;   // don't store a full XLRow, just the XMLNode, for better performance
            m_hintRowNumber = m_currentRowNumber;
            m_currentRowStatus = XLLoaded;                  // mark row status for further calls to updateCurrentRow()
        }
    }

    /**
     * @details
     * @pre
     * @post
     */
    XLRowIterator& XLRowIterator::operator++()    // 2024-04-29: patched for whitespace
    {
        if (m_endReached)
            throw XLInputError("XLRowIterator: tried to increment beyond end operator");

        if (m_currentRowNumber < m_lastRow)
            ++m_currentRowNumber;
        else
            m_endReached = true;

        m_currentRowStatus = XLNotLoaded; // trigger a new attempt to locate / create the row via updateRowCell

        return *this;
    }

    /**
     * @details
     * @pre
     * @post
     */
    XLRowIterator XLRowIterator::operator++(int)    // NOLINT
    {
        auto oldIter(*this);
        ++(*this);
        return oldIter;
    }

    /**
     * @details
     * @pre
     * @post
     */
    XLRow& XLRowIterator::operator*() {
        updateCurrentRow(XLCreateIfMissing);
        return m_currentRow;
    }

    /**
     * @details
     * @pre
     * @post
     */
    XLRowIterator::pointer XLRowIterator::operator->() {
        updateCurrentRow(XLCreateIfMissing);
        return &m_currentRow;
    }

    /**
     * @details
     * @pre
     * @post
     */
    bool XLRowIterator::operator==(const XLRowIterator& rhs) const {
        if (m_endReached && rhs.m_endReached) return true;    // If both iterators are end iterators

        if (m_currentRowNumber != rhs.m_currentRowNumber)     // If iterators point to a different row
            return false;                                         // that means no match

        // CAUTION: for performance reasons, disabled all checks whether this and rhs are iterators on the same worksheet & row range
        return true;

        // if (*m_dataNode != *rhs.m_dataNode) return false;     // TBD: iterators over different worksheets may never match
        // TBD if iterators shall be considered not equal if they were created on different XLRowRanges
        // this would require checking the m_firstRow and m_lastRow, potentially costing CPU time

        // return m_currentRow == rhs.m_currentRow;   // match only if row nodes are equal
        // CAUTION: in the current code, that means iterators that point to the same row in different worksheets,
        // and rows that do not exist in both sheets, will be considered equal
    }

    /**
     * @details
     * @pre
     * @post
     */
    bool XLRowIterator::operator!=(const XLRowIterator& rhs) const { return !(*this == rhs); }

    /**
     * @details
     * @pre
     * @post
     */
    XLRowIterator::operator bool() const { return false; }

    XLRowRange::XLRowRange(const XMLNode& dataNode, uint32_t first, uint32_t last, const XLSharedStrings& sharedStrings)
        : m_dataNode(std::make_unique<XMLNode>(dataNode)),
        m_firstRow(first),
        m_lastRow(last),
        m_sharedStrings(sharedStrings) {
    }

} // namespace XLSXCreator
