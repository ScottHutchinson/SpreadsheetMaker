#pragma once
#include "XLConstants.h"
#include "XLSharedStrings.h"
#include "XLXmlNode.h" // for using XMLNode...

namespace XLSXCreator {

    class XLCellValue;
    class XLRow;

    class XLRowDataProxy {
        XLRow* m_row{ nullptr };     /**< Pointer to the parent XLRow object. */
        XMLNode* m_rowNode{ nullptr }; /**< Pointer the the XML node representing the row. */

    public:
        /**
         * @brief Templated assignment operator taking any container supporting bidirectional iterators.
         * @tparam T The container and value type (will be auto deducted by the compiler).
         * @param values The container of the values to be assigned.
         * @return A reference to the copied-to object.
         * @throws XLOverflowError if size of container exceeds maximum number of columns.
         */
        template<typename T,
            typename = std::enable_if_t<!std::is_same_v<T, XLRowDataProxy>&&
            std::is_base_of_v<std::bidirectional_iterator_tag,
            typename std::iterator_traits<typename T::iterator>::iterator_category>,
            T>>
            XLRowDataProxy & operator=(const T& values)    // 2024-04-30: whitespace support
        {
            if (values.size() > MAX_COLS) throw XLOverflowError("Container size exceeds maximum number of columns.");
            if (values.size() == 0) return *this;

            // ===== If the container value_type is XLCellValue, the values can be copied directly.
            if constexpr (std::is_same_v<typename T::value_type, XLCellValue>) {
                // ===== First, delete the values in the first N columns.
                deleteCellValues(values.size());    // 2024-04-30: whitespace support

                // ===== Then, prepend new cell nodes to current row node
                auto colNo = values.size();
                for (auto value = values.rbegin(); value != values.rend(); ++value) {    // NOLINT
                    prependCellValue(*value, colNo);    // 2024-04-30: whitespace support: this is safe because only prependCellValue (with
                    // whitespace support) touches the row data
                    --colNo;
                }
            }

            // ===== If the container value_type is a POD type, use the overloaded operator= on each cell.
            else {
                auto range = XLRowDataRange(*m_rowNode, 1, values.size(), getSharedStrings());
                auto dst = range.begin();    // 2024-04-30: whitespace support: safe because XLRowDataRange::begin invokes whitespace-safe
                // getCellNode for column 1
                auto src = values.begin();

                while (true) {
                    dst->value() = *src;
                    ++src;
                    if (src == values.end()) break;
                    ++dst;    // 2024-04-30: whitespace support: XLRowDataIterator::operator++ is whitespace-safe
                }
            }

            return *this;
        }

    };

    class XLRow {
        friend class XLRowIterator;
        friend class XLRowDataProxy;

        std::unique_ptr<XMLNode> m_rowNode;       /**< The XMLNode object for the row. */
        XLSharedStringsRef       m_sharedStrings;
        XLRowDataProxy           m_rowDataProxy;

    public:
        XLRow();

        /**
         * @brief
         * @param rowNode
         * @param sharedStrings
         */
        XLRow(const XMLNode& rowNode, const XLSharedStrings& sharedStrings);

        XLRowDataProxy& values();

        /**
         * @brief test if row object has no (valid) content
         * @return
         */
        bool empty() const;

    };

    class XLRowIterator {
        static constexpr const bool XLCreateIfMissing = true;     // code readability for updateCurrentRow parameter createIfMissing
        static constexpr const bool XLDoNotCreateIfMissing = false;    //   "

        std::unique_ptr<XMLNode> m_dataNode;       /**< */
        uint32_t                 m_firstRow{ 1 }; /**< The cell reference of the first cell in the range */
        uint32_t                 m_lastRow{ 1 };  /**< The cell reference of the last cell in the range */
        XLRow                    m_currentRow;     /**< */
        XLSharedStringsRef       m_sharedStrings;  /**< */

        // helper variables for non-creating iterator functionality
        bool                     m_endReached;           /**< */
        XMLNode                  m_hintRow;              /**< The cell node of the last existing row found up to current iterator position */
        uint32_t                 m_hintRowNumber;        /**<   the row number for m_hintRow */
        static constexpr const int XLNotLoaded = 0;    // code readability for m_currentRowStatus
        static constexpr const int XLNoSuchRow = 1;    //   "
        static constexpr const int XLLoaded = 2;    //   "
        int                      m_currentRowStatus;    /**< Status of m_currentRow: XLNotLoaded, XLNoSuchRow or XLLoaded */
        uint32_t                 m_currentRowNumber;

    public:
        using pointer = XLRow*;
        using reference = XLRow&;
        /**
         * @brief update m_currentRow by fetching (or inserting) a row at m_currentRowNumber
         * @param createIfMissing m_currentRow will only be inserted if createIfMissing is true
         */
        void updateCurrentRow(bool createIfMissing);

        /**
         * @brief
         * @return
         */
        XLRowIterator& operator++();

        /**
         * @brief
         * @return
         */
        XLRowIterator operator++(int);    // NOLINT

        /**
         * @brief
         * @return
         */
        reference operator*();

        /**
         * @brief
         * @return
         */
        pointer operator->();

        /**
         * @brief
         * @param rhs
         * @return
         */
        bool operator==(const XLRowIterator& rhs) const;

        /**
         * @brief
         * @param rhs
         * @return
         */
        bool operator!=(const XLRowIterator& rhs) const;

        /**
         * @brief
         * @return
         */
        explicit operator bool() const;

        XLRowDataProxy& values();
    };

    class XLRowRange {
        std::unique_ptr<XMLNode> m_dataNode;      /**< */
        uint32_t                 m_firstRow;      /**< The cell reference of the first cell in the range */
        uint32_t                 m_lastRow;       /**< The cell reference of the last cell in the range */
        XLSharedStringsRef       m_sharedStrings; /**< */
    public:
        explicit XLRowRange(const XMLNode& dataNode, uint32_t first, uint32_t last, const XLSharedStrings& sharedStrings);
        XLRowIterator begin();
        XLRowIterator end();

    };

} // namespace XLSXCreator
