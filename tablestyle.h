#ifndef TABLESTYLE_H_INCLUDED
#define TABLESTYLE_H_INCLUDED

#include <vector>
#include "resources.h"

using namespace std;

namespace Borders{
    const string LEFT = "| ";
    const string RIGHT = " |";
    const string CENTER = " | ";
}
class Alignment{
    private:
        Tables m_table;
        vector<int> m_pads;
        vector<string> m_columnNames;
    public:
        Alignment(Tables table, const initializer_list<string> &list);
        Alignment(const initializer_list<string> &list);

        Alignment* printHR();
        Alignment* printHeader(string newHeader = "");
        Alignment* printColumnNames();
        Alignment* printFullHeader(string newHeader);
        Alignment* printNoRecordsFound();

        int getRowPad(const int rowIndex) const;
        Alignment* setRowPad(const int rowIndex, const int rowLength);

        int getGeneralRowLength() const;
        Tables getTable() const{ return m_table; }
        string getTableName() const;

        int addColumn(string columnName);
        int removeColumn(int index);
};

#endif // TABLESTYLE_H_INCLUDED
