#include <cassert>
#include <initializer_list>
#include <cmath>

#include "tablestyle.h"

Alignment::Alignment(Tables table, const initializer_list<string> &list):
    m_table(table)
{
    //copying to array from initializer_list, using foreach, because initializer_list don`t have overloaded operator []
    for(const auto &item : list){
        m_pads.push_back(item.length());
        m_columnNames.push_back(item);
    }
}
Alignment* Alignment::printColumnNames(){
    cout << Borders::LEFT << left;
    for(size_t i = 0; i < m_columnNames.size(); i++){
        cout << setw(getRowPad(i)) << m_columnNames[i];
        if(i == (m_columnNames.size() - 1)){
            cout << Borders::RIGHT << endl;
            break;
        }
        cout << Borders::CENTER;
    }
    return this;
}
int Alignment::addColumn(string columnName){
    m_columnNames.push_back(columnName);
    m_pads.push_back(columnName.length());
    return 0;
}
int Alignment::removeColumn(int index){
    m_columnNames.erase(m_columnNames.begin() + index);
    m_pads.erase(m_pads.begin() + index);
    return 0;
}
int Alignment::getRowPad(const int rowIndex) const{
    return m_pads.at(rowIndex);
}
Alignment* Alignment::setRowPad(const int rowIndex, const int rowLength){
    if(rowLength > m_pads.at(rowIndex)){
        m_pads.at(rowIndex) = rowLength;
    }
    return this;
}
int Alignment::getGeneralRowLength() const{
    int sum = 0;
    for(const int pad : m_pads){
        sum += pad;
    }
    //count borders symbols count
    int bordersDelta = (m_columnNames.size()-1)*Borders::CENTER.length() + Borders::LEFT.length() + Borders::RIGHT.length();
    return sum + bordersDelta;
}
Alignment* Alignment::printHR(){
    cout << string(getGeneralRowLength(), '-') << endl;
    return this;
}
Alignment* Alignment::printHeader(string newHeader){
    string header = (newHeader != "") ? newHeader : getTableName();
    int padding = round(getGeneralRowLength() / 2) - round(header.length()/2);
    cout << string(padding, ' ') << header << endl;
    return this;
}
Alignment* Alignment::printNoRecordsFound(){
    printHR();
    printHeader(getTextInCurrentLanguage(textNoRecords));
    printHR();
    return this;
}
Alignment* Alignment::printFullHeader(string newHeader){
    printHR();
    printHeader(newHeader);
    printHR();
    printColumnNames();
    printHR();
    return this;
}
string Alignment::getTableName() const{
    switch(m_table){
        case Tables::WORK_POSITION: return "ÏÎÑÀÄÀ";
        case Tables::STRUCTURAL_UNIT: return "ÑÒÐÓÊÒÓÐÍÀ ÎÄÈÍÈÖß";
        case Tables::PRODUCER: return "ÂÈÐÎÁÍÈÊ";
        case Tables::PRODUCT: return "ÒÎÂÀÐ";
        case Tables::CLIENT: return "ÊË²ªÍÒ";
        case Tables::EMPLOYEE: return "ÏÐÀÖ²ÂÍÈÊ";
        case Tables::DELIVERY: return "ÄÎÑÒÀÂÊÀ";
        case Tables::ORDER: return "ÇÀÌÎÂËÅÍÍß";
        default: return "";
    }
}
