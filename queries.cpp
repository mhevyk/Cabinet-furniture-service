#include <sstream>
#include "resources.h"
#include "database.h"

vector<FurnitureProduct*> Database::selectByCategory(int categoryCode){
    vector<FurnitureProduct*> filteredTable;
    for(const auto &product : tableFurnitureProduct){
        if((static_cast<int>(product->getCategoryLink()) + 1) == categoryCode){
            filteredTable.push_back(product);
        }
    }
    return filteredTable;
}
vector<FurnitureOrder*> Database::selectByTimeUnit(int timeUnitCode){
    time_t now = time(0);
    struct tm *today = localtime(&now);
    time_t weekAgo = now - (7*24*60*60);
    int lastMonth = today->tm_mon-1;
	int lastYear = today->tm_year-1;

	CommandsPageTimeUnits timeUnit = static_cast<CommandsPageTimeUnits>(timeUnitCode);

	vector<FurnitureOrder*> result;
    for(const auto &order : tableFurnitureOrder){
        struct tm* recordDate = stringToDate(order->getDate());
        if(timeUnit == CommandsPageTimeUnits::LAST_YEAR && (lastYear == recordDate->tm_year)) result.push_back(order);
        if(timeUnit == CommandsPageTimeUnits::LAST_MONTH && (lastMonth == recordDate->tm_mon)) result.push_back(order);
        if(timeUnit == CommandsPageTimeUnits::LAST_WEEK && (mktime(recordDate) > weekAgo)) result.push_back(order);
        if(timeUnit == CommandsPageTimeUnits::ALL_TIME) result.push_back(order);
    }
    return result;
}
int findPairIndex(vector<pair<FurnitureOrder*, int>> &v, FurnitureOrder* key){
    for(size_t i = 0; i < v.size(); i++){
        if(v[i].first->getProductLink()->getName() == key->getProductLink()->getName()){
            return i;
        }
    }
    return -1;
}


int Database::querySelectProductsByPrice(int price, int comparisonCode){
    CommandsPageQuery1Comparison comparison = static_cast<CommandsPageQuery1Comparison>(comparisonCode);
    vector<FurnitureProduct*> filteredTable;
    for(const auto &product : tableFurnitureProduct){
        if(comparison == CommandsPageQuery1Comparison::BIGGER && product->getPrice() > price){
            filteredTable.push_back(product);
        }
        else if(comparison == CommandsPageQuery1Comparison::LESS && product->getPrice() < price){
            filteredTable.push_back(product);
        }
        else if(comparison == CommandsPageQuery1Comparison::EQUAL && product->getPrice() == price){
            filteredTable.push_back(product);
        }
    }
    string filteredTableHeader = "�������� � ֲ��� ";
    switch(comparison){
        case CommandsPageQuery1Comparison::BIGGER: filteredTableHeader += "������� �� "; break;
        case CommandsPageQuery1Comparison::LESS: filteredTableHeader += "������ �� "; break;
        case CommandsPageQuery1Comparison::EQUAL: filteredTableHeader += "в���� "; break;
        default: break;
    }
    filteredTableHeader += to_string(price) + " ���";
    printTable(filteredTable, filteredTableHeader);
    return 0;
}
int Database::querySelectProductsByCategoryAndSortThemByField(int categoryCode, int sortColumnCode, int sortTypeCode){
    CommandsPageColumnNames sortColumn = static_cast<CommandsPageColumnNames>(sortColumnCode);
    CommandsPageSortOrders sortType = static_cast<CommandsPageSortOrders>(sortTypeCode);
    vector<FurnitureProduct*> filteredTable = selectByCategory(categoryCode);
    for(size_t i = 0; i < filteredTable.size() - 1; i++){
        for(size_t j = 0; j < filteredTable.size() - i - 1; j++){
            //Name
            if(CommandsPageColumnNames::NAME == sortColumn
               && filteredTable[j]->getName() > filteredTable[j + 1]->getName()
               && CommandsPageSortOrders::ASC == sortType
            ) swap(filteredTable[j], filteredTable[j + 1]);
            if(CommandsPageColumnNames::NAME == sortColumn
               && filteredTable[j]->getName() < filteredTable[j + 1]->getName()
               && CommandsPageSortOrders::DESC == sortType
            ) swap(filteredTable[j], filteredTable[j + 1]);
            //Producer
            if(CommandsPageColumnNames::PRODUCER == sortColumn
               && filteredTable[j]->getProducerLink()->getName() > filteredTable[j + 1]->getProducerLink()->getName()
               && CommandsPageSortOrders::ASC == sortType
            ) swap(filteredTable[j], filteredTable[j + 1]);
            if(CommandsPageColumnNames::PRODUCER == sortColumn
               && filteredTable[j]->getProducerLink()->getName() < filteredTable[j + 1]->getProducerLink()->getName()
               && CommandsPageSortOrders::DESC == sortType
            ) swap(filteredTable[j], filteredTable[j + 1]);
            //Price
            if(CommandsPageColumnNames::PRICE == sortColumn
               && filteredTable[j]->getPrice() > filteredTable[j + 1]->getPrice()
               && CommandsPageSortOrders::ASC == sortType
            ) swap(filteredTable[j], filteredTable[j + 1]);
            if(CommandsPageColumnNames::PRICE == sortColumn
               && filteredTable[j]->getPrice() < filteredTable[j + 1]->getPrice()
               && CommandsPageSortOrders::DESC == sortType
            ) swap(filteredTable[j], filteredTable[j + 1]);
            //Material
            if(CommandsPageColumnNames::MATERIAL == sortColumn
               && filteredTable[j]->getMaterial() > filteredTable[j + 1]->getMaterial()
               && CommandsPageSortOrders::ASC == sortType
            ) swap(filteredTable[j], filteredTable[j + 1]);
            if(CommandsPageColumnNames::MATERIAL == sortColumn
               && filteredTable[j]->getMaterial() < filteredTable[j + 1]->getMaterial()
               && CommandsPageSortOrders::DESC == sortType
            ) swap(filteredTable[j], filteredTable[j + 1]);
            //Style
            if(CommandsPageColumnNames::STYLE == sortColumn
               && filteredTable[j]->getStyle() > filteredTable[j + 1]->getStyle()
               && CommandsPageSortOrders::ASC == sortType
            ) swap(filteredTable[j], filteredTable[j + 1]);
            if(CommandsPageColumnNames::STYLE == sortColumn
               && filteredTable[j]->getStyle() < filteredTable[j + 1]->getStyle()
               && CommandsPageSortOrders::DESC == sortType
            ) swap(filteredTable[j], filteredTable[j + 1]);
            //Warranty
            if(CommandsPageColumnNames::WARRANTY == sortColumn
               && filteredTable[j]->getWarranty() > filteredTable[j + 1]->getWarranty()
               && CommandsPageSortOrders::ASC == sortType
            ) swap(filteredTable[j], filteredTable[j + 1]);
            if(CommandsPageColumnNames::WARRANTY == sortColumn
               && filteredTable[j]->getWarranty() < filteredTable[j + 1]->getWarranty()
               && CommandsPageSortOrders::DESC == sortType
            ) swap(filteredTable[j], filteredTable[j + 1]);
        }
    }
    printTable(filteredTable, "²���������� �������");
    return 0;
}
int Database::querySelectTop10BestSoldProducts(){
    vector<pair<FurnitureOrder*, int>> uniqueProductNames;
    //find unique product names and set each of them first occurence order count
    for(size_t i = 0; i < tableFurnitureOrder.size(); i++){
        size_t j;
        for(j = 0; j < i; j++){
            if(tableFurnitureOrder[i]->getProductLink()->getName() == tableFurnitureOrder[j]->getProductLink()->getName()){
                break;
            }
        }
        if(i == j){
            uniqueProductNames.push_back(make_pair(tableFurnitureOrder[i], tableFurnitureOrder[i]->getCount()));
        }
    }
    //accumulating orders count for each unique name
    for(size_t i = 0; i < tableFurnitureOrder.size(); i++){
        for(size_t temp = i + 1; temp < tableFurnitureOrder.size(); temp++){
            if(tableFurnitureOrder[i]->getProductLink()->getName() == tableFurnitureOrder[temp]->getProductLink()->getName()){
                uniqueProductNames[findPairIndex(uniqueProductNames, tableFurnitureOrder[temp])].second += tableFurnitureOrder[temp]->getCount();
                break;
            }
        }
    }
    //sort by product names
    for(size_t i = 0; i < uniqueProductNames.size() - 1; i++){
        for(size_t j = 0; j < uniqueProductNames.size() - i - 1; j++){
            if(uniqueProductNames[j].second < uniqueProductNames[j + 1].second){
                swap(uniqueProductNames[j], uniqueProductNames[j + 1]);
            }
        }
    }
    //print table with extra column "��������� ������ (��)"
    Alignment *alignment = tableFurnitureOrder[0]->getProductLink()->alignment;
	alignment->addColumn("��������� ������ (��)");
	alignment->printFullHeader("���-10 �������� ���������� ����в�");
    cout << left;
    for(int i = 0; i < 10; i++){
        cout << uniqueProductNames[i].first->getProductLink() << " " << setw(21) << uniqueProductNames[i].second << " |" << endl;
    }
    alignment->printHR();
    alignment->removeColumn(13);
    return 0;
}
int Database::queryCompareProducts(string firstProductName, string secondProductName){
    FurnitureProduct* firstProduct = getRecordByName(tableFurnitureProduct, firstProductName);
    FurnitureProduct* secondProduct = getRecordByName(tableFurnitureProduct, secondProductName);

    vector <FurnitureProduct*> filteredTable;
    filteredTable.push_back(firstProduct);
    filteredTable.push_back(secondProduct);
    printTable(filteredTable, "������, �� ��в��������");

    int price1 = firstProduct->getPrice();
    int price2 = secondProduct->getPrice();
    int rate1 = firstProduct->getProducerLink()->getRate().length();
    int rate2 = secondProduct->getProducerLink()->getRate().length();

    cout << "������ �����: ";
    if(price1 < price2){
        cout << firstProductName << " (��������)\n";
    }
    else if(price1 > price2){
        cout << secondProductName  << " (��������)\n";
    }
    else{
        if(rate1 > rate2){
        cout << firstProductName << " (�������� ��������)\n";
        }
        else if(rate1 < rate2){
            cout << secondProductName <<  " (�������� ��������)\n";
        }
        else{
            cout << " ����, ���� ���� ��������� �������\n";
        }
    }
    return 0;
}

int Database::querySelectProductsByDimensions(float width, float depth, float height){
    vector<FurnitureProduct*> filteredTable;
    for(const auto &product : tableFurnitureProduct){
        if(product->getWidth() < width && product->getDepth() < depth && product->getHeight() < height){
            filteredTable.push_back(product);
        }
    }
    string filteredTableHeader = "������, �ʲ ��̲������� � ����Ҳ� ���̲���� " + printFloatWithPrecision(width, 1) + " x " + printFloatWithPrecision(depth, 1) + " x " + printFloatWithPrecision(height, 1);
    printTable(filteredTable, filteredTableHeader);
    return 0;
}
int Database::querySelectProductsByWarranty(float warranty){
    vector<FurnitureProduct*> filteredTable;
    for(const auto &product : tableFurnitureProduct){
        if(product->getWarranty() > warranty){
            filteredTable.push_back(product);
        }
    }
    string filteredTableHeader = "������, �ʲ ����� �����Ҳ� ������ �� " + printFloatWithPrecision(warranty, 1) + " ��ʲ�";
    printTable(filteredTable, filteredTableHeader);
    return 0;
}
int Database::querySelectProductsByAvailabilityInCategory(int categoryCode){
    vector<FurnitureProduct*> filteredByCategory = selectByCategory(categoryCode);
    vector<FurnitureProduct*> finallyFilteredTable;
    for(const auto &product : filteredByCategory){
        if(product->getInStockCount() > 0){
            finallyFilteredTable.push_back(product);
        }
    }
    string header = "������, � ������в� " + filteredByCategory[0]->getCategory() + ", �ʲ � �� ����Ĳ";
    printTable(finallyFilteredTable, header);
    return 0;
}
int Database::queryGetProductCharacteristics(string productName){
    FurnitureProduct* p = getRecordByName(tableFurnitureProduct, productName);
    cout << string(60, '-') << endl;
    cout << "  �������������� ������ \"" << productName << "\":\n";
    cout << string(60, '-') << endl;
    cout << " -  �����: " << p->getCategory(false) << " \"" << p->getName() << "\"" << endl;
    cout << " -  ֳ��: " << p->getPrice() << " ���. \n";
    cout << " -  ������ (��): " << p->getWidth() << " x " << p->getDepth() << " x " << p->getHeight() << endl;
    cout << " -  ��������� ��������: ";
    p->getDeliveryFlag() ? cout << "���" : cout << "�";
    cout << endl;
    cout << " -  ��������: " << p->getProducerLink()->getName() << ", ������� ���������: " << p->getProducerLink()->getRate() << endl;
    cout << " -  �������: " << p->getMaterial() << endl;
    cout << " -  �����: " << p->getStyle() << endl;
    cout << " -  ������� (����): " << p->getWarranty() << endl;
    cout << string(60, '-') << endl;
    return 0;
}
int Database::queryCountOrdersPerTimeUnitByCategory(int categoryCode, int timeUnitCode){
	string headerPart;
	CommandsPageTimeUnits timeUnit = static_cast<CommandsPageTimeUnits>(timeUnitCode);
	switch(timeUnit){
        case CommandsPageTimeUnits::LAST_YEAR: headerPart = "������� в�"; break;
        case CommandsPageTimeUnits::LAST_MONTH: headerPart = "������� ̲����"; break;
        case CommandsPageTimeUnits::LAST_WEEK: headerPart = "������� �������"; break;
        default: headerPart = "���� ���"; break;
	}

	vector<FurnitureOrder*> filteredByTimeUnit = selectByTimeUnit(timeUnitCode);
	vector<FurnitureOrder*> finallyFilteredTable;
	int count = 0;
	for(const auto &order : filteredByTimeUnit){
        if(order->getStatus() == FurnitureOrderStatuses::COMPLETED){
            if((static_cast<int>(order->getProductLink()->getCategoryLink()) + 1) == categoryCode){
                finallyFilteredTable.push_back(order);
                count++;
            }
        }
	}
	Alignment *alignment = tableFurnitureOrder[0]->getProductLink()->alignment;
	alignment->addColumn("���� ����������");
	if(finallyFilteredTable.empty()){
        alignment->printNoRecordsFound();
        alignment->removeColumn(13);
        return -1;
	}
	clearConsole();
	alignment->printFullHeader("���������� �� " + headerPart);
    for(const auto &order : finallyFilteredTable){
        cout << order->getProductLink() << " " << setw(15) << order->getDate() << " |" << endl;
	}
    alignment->printHR();
    cout << "ʲ��ʲ��� ��������� �� " << headerPart << ": " << count << "\n\n";
    alignment->removeColumn(13);
    return 0;
}

int Database::queryCountProfitPerTimeUnitFromCompletedOrders(int timeUnitCode){
    Alignment *alignment = tableFurnitureOrder[0]->getProductLink()->alignment;
	string headerPart;
	CommandsPageTimeUnits timeUnit = static_cast<CommandsPageTimeUnits>(timeUnitCode);
	switch(timeUnit){
        case CommandsPageTimeUnits::LAST_YEAR: headerPart = "������� в�"; break;
        case CommandsPageTimeUnits::LAST_MONTH: headerPart = "������� ̲����"; break;
        case CommandsPageTimeUnits::LAST_WEEK: headerPart = "������� �������"; break;
        default: headerPart = "���� ���"; break;
	}

	vector<FurnitureOrder*> filteredByTimeUnit = selectByTimeUnit(timeUnitCode);
	vector<FurnitureOrder*> finallyFilteredTable;
	int sum = 0;
	for(const auto &order : filteredByTimeUnit){
        if(order->getStatus() == FurnitureOrderStatuses::COMPLETED){
            sum += order->getProductLink()->getPrice();
            finallyFilteredTable.push_back(order);
        }
	}
	alignment->addColumn("���� ����������");
	if(finallyFilteredTable.empty()){
        alignment->printNoRecordsFound();
        alignment->removeColumn(13);
        return -1;
	}
	clearConsole();
	alignment->printFullHeader("�������� �� " + headerPart);
    for(const auto &order : finallyFilteredTable){
        cout << order->getProductLink() << " " << setw(15) << order->getDate() << " |" << endl;
	}
    alignment->printHR();
    cout << "�������� ²� ��������� �� " << headerPart << ": " << sum << " ���\n\n";
    alignment->removeColumn(13);
    return 0;
}
int Database::querySelectFreeCouriers(){
    vector<FurnitureEmployee*> filteredTable;
    for(const auto &employee : tableFurnitureEmployee){
        if(employee->getWorkPosition() == "���'��" && !employee->getRestFlag()){
            filteredTable.push_back(employee);
        }
    }
    printTable(filteredTable, "�������Ҳ ���'���");
    return 0;
}
int Database::querySelectProductsByPossibilityOfDelivery(){
    vector<FurnitureProduct*> filteredTable;
    for(const auto &product : tableFurnitureProduct){
        if(product->getDeliveryFlag()){
            filteredTable.push_back(product);
        }
    }
    printTable(filteredTable, "��������, �ʲ ����� �����²��� ��������");
    return 0;
}
int Database::queryCountTheCostOfKeepingEmployeesAtWorkPosition(int workPositionCode){
    vector<FurnitureEmployee*> filteredTable;
    CommandsWorkPositions workPosition = static_cast<CommandsWorkPositions>(workPositionCode);
    string filteredTableHeader = "���ֲ�����, �ʲ �������� �� ����Ĳ ";
    switch(workPosition){
        case CommandsWorkPositions::SALES_CONSULTANT: filteredTableHeader += "���������-�����������"; break;
        case CommandsWorkPositions::ACCOUNTANT: filteredTableHeader += "���������"; break;
        case CommandsWorkPositions::MAID: filteredTableHeader += "�������������"; break;
        case CommandsWorkPositions::LOADER: filteredTableHeader += "���������"; break;
        case CommandsWorkPositions::COURIER: filteredTableHeader += "���'��"; break;
        case CommandsWorkPositions::GUARDIAN: filteredTableHeader += "���������"; break;
        case CommandsWorkPositions::FURNITURE_ASSEMBLER: filteredTableHeader += "����������� ���˲�"; break;
        case CommandsWorkPositions::DESIGNER: filteredTableHeader += "��������"; break;
        default: break;
    }
    for(const auto &employee : tableFurnitureEmployee){
        if(workPosition == CommandsWorkPositions::SALES_CONSULTANT && employee->getWorkPosition() == "���������-�����������"){
            filteredTable.push_back(employee);
        }
        if(workPosition == CommandsWorkPositions::ACCOUNTANT && employee->getWorkPosition() == "���������"){
            filteredTable.push_back(employee);
        }
        if(workPosition == CommandsWorkPositions::MAID && employee->getWorkPosition() == "�������������"){
            filteredTable.push_back(employee);
        }
        if(workPosition == CommandsWorkPositions::LOADER && employee->getWorkPosition() == "���������"){
            filteredTable.push_back(employee);
        }
        if(workPosition == CommandsWorkPositions::COURIER && employee->getWorkPosition() == "���'��"){
            filteredTable.push_back(employee);
        }
        if(workPosition == CommandsWorkPositions::GUARDIAN && employee->getWorkPosition() == "���������"){
            filteredTable.push_back(employee);
        }
        if(workPosition == CommandsWorkPositions::FURNITURE_ASSEMBLER && employee->getWorkPosition() == "����������� �����"){
            filteredTable.push_back(employee);
        }
        if(workPosition == CommandsWorkPositions::DESIGNER && employee->getWorkPosition() == "��������"){
            filteredTable.push_back(employee);
        }
    }
    Alignment *alignment = tableFurnitureEmployee[0]->alignment;
    alignment->addColumn("��������");
	if(filteredTable.empty()){
        alignment->printNoRecordsFound();
        alignment->removeColumn(8);
        return -1;
	}
	clearConsole();
	alignment->printFullHeader(filteredTableHeader);
	int amount = 0;
    for(const auto &employee : filteredTable){
        cout << employee << " " << setw(8) << employee->getWorkPositionLink()->getSalary() << " |" << endl;
        amount += employee->getWorkPositionLink()->getSalary();
	}
    alignment->printHR();
    cout << "�������� ����, ��� ���в��� ��Ĳ���� �� ��������� �Ѳ� ���ֲ���ʲ�: " << amount << " ���\n\n";
    alignment->removeColumn(8);
    return 0;
}
int Database::querySelectStructuralUnitStaff(int structuralUnitCode){
    vector<FurnitureEmployee*> filteredTable;
    CommandsStructuralUnits structuralUnit = static_cast<CommandsStructuralUnits>(structuralUnitCode);
    string headerPart;
    switch(structuralUnit){
        case CommandsStructuralUnits::OFFICE: headerPart = " �Բ��"; break;
        case CommandsStructuralUnits::SHOP1: headerPart = " �������� 1"; break;
        case CommandsStructuralUnits::SHOP2: headerPart = " �������� 2"; break;
        case CommandsStructuralUnits::SHOP3: headerPart = " �������� 3"; break;
        case CommandsStructuralUnits::DEPARTMENT1: headerPart = " ���� 1"; break;
        case CommandsStructuralUnits::DEPARTMENT2: headerPart = " ���� 2"; break;
        default: break;
    }
    for(const auto &employee : tableFurnitureEmployee){
        if(structuralUnit == CommandsStructuralUnits::OFFICE && employee->getStructuralUnit() == "����"){
            filteredTable.push_back(employee);
        }
        if(structuralUnit == CommandsStructuralUnits::SHOP1 && employee->getStructuralUnit() == "������� 1"){
            filteredTable.push_back(employee);
        }
        if(structuralUnit == CommandsStructuralUnits::SHOP2 && employee->getStructuralUnit() == "������� 2"){
            filteredTable.push_back(employee);
        }
        if(structuralUnit == CommandsStructuralUnits::SHOP3 && employee->getStructuralUnit() == "������� 3"){
            filteredTable.push_back(employee);
        }
        if(structuralUnit == CommandsStructuralUnits::DEPARTMENT1 && employee->getStructuralUnit() == "��� 1"){
            filteredTable.push_back(employee);
        }
        if(structuralUnit == CommandsStructuralUnits::DEPARTMENT2 && employee->getStructuralUnit() == "��� 2"){
            filteredTable.push_back(employee);
        }
    }
    printTable(filteredTable, "��������" + headerPart);
    return 0;
}
