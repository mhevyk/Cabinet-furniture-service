#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <fstream>
#include <vector>

#include "tablestyle.h"
#include "tables.h"
#include "navigation.h"
#include "resources.h"

class Database{
    private:
        template<typename T> int resetTable(vector<T*> &table){
            for(const auto &record : table){
                delete record;
            }
            table.clear();
            return 0;
        }
        template<typename T> int parseTable(ifstream &fin, vector<T*> &table){
            Tables tableIndex = table[0]->alignment->getTable();
            string record;
            while(getline(fin, record)){
                istringstream iss(record);
                if(tableIndex == Tables::WORK_POSITION){
                    string name = readAsString(iss);
                    int salary = readAsInt(iss);
                    tableFurnitureWorkPosition.push_back(new FurnitureWorkPosition(name, salary));
                }
                else if(tableIndex == Tables::STRUCTURAL_UNIT){
                    string name = readAsString(iss);
                    string adress = readAsString(iss);
                    FurnitureAddressees addressee = static_cast<FurnitureAddressees>(readAsInt(iss) - 1);
                    tableFurnitureStructuralUnit.push_back(new FurnitureStructuralUnit(name, adress, addressee));
                }
                else if(tableIndex == Tables::PRODUCER){
                    string name = readAsString(iss);
                    string adress = readAsString(iss);
                    string phone = readAsString(iss);
                    string rate = readAsString(iss);
                    tableFurnitureProducer.push_back(new FurnitureProducer(name, adress, phone, rate));
                }
                else if(tableIndex == Tables::PRODUCT){
                    FurnitureCategories category = static_cast<FurnitureCategories>(readAsInt(iss) - 1);
                    string name = readAsString(iss);
                    FurnitureProducer *producer = getRecordById(tableFurnitureProducer, readAsInt(iss));
                    int price = readAsFloat(iss);
                    bool deliveryFlag = readAsBool(iss);
                    FurnitureDimensions dimensions{readAsFloat(iss), readAsFloat(iss), readAsFloat(iss)};
                    FurnitureMaterials material = static_cast<FurnitureMaterials>(readAsInt(iss) - 1);
                    FurnitureStyles style = static_cast<FurnitureStyles>(readAsInt(iss) - 1);
                    int inStockCount = readAsInt(iss);
                    float warranty = readAsFloat(iss);
                    tableFurnitureProduct.push_back(new FurnitureProduct(category, name, producer, price, deliveryFlag, dimensions, material, style, inStockCount, warranty));
                }
                else if(tableIndex == Tables::CLIENT){
                    string fullName = readAsString(iss);
                    char sex = readAsChar(iss);
                    string date = readAsString(iss);
                    string adress = readAsString(iss);
                    string phone = readAsString(iss);
                    tableFurnitureClient.push_back(new FurnitureClient(fullName, sex, date, adress, phone));
                }
                else if(tableIndex == Tables::EMPLOYEE){
                    FurnitureWorkPosition *workPosition = getRecordById(tableFurnitureWorkPosition, readAsInt(iss));
                    string fullName = readAsString(iss);
                    FurnitureStructuralUnit *structuralUnit = getRecordById(tableFurnitureStructuralUnit, readAsInt(iss));
                    char sex = readAsChar(iss);
                    string date = readAsString(iss);
                    string adress = readAsString(iss);
                    string phone = readAsString(iss);
                    bool restFlag = readAsBool(iss);
                    tableFurnitureEmployee.push_back(new FurnitureEmployee(workPosition, fullName, structuralUnit, sex, date, adress, phone, restFlag));
                }
                else if(tableIndex == Tables::DELIVERY){
                    string courier = readAsString(iss);
                    string adress = readAsString(iss);
                    FurnitureDeliveryStatuses status = static_cast<FurnitureDeliveryStatuses>(readAsInt(iss));
                    tableFurnitureDelivery.push_back(new FurnitureDelivery(courier, adress, status));
                }
                else if(tableIndex == Tables::ORDER){
                    FurnitureProduct *product = getRecordById(tableFurnitureProduct, readAsInt(iss));
                    int count = readAsInt(iss);
                    FurnitureClient *client = getRecordById(tableFurnitureClient, readAsInt(iss));
                    FurnitureDelivery *delivery = getRecordById(tableFurnitureDelivery, readAsInt(iss));
                    string date = readAsString(iss);
                    FurnitureOrderStatuses status = static_cast<FurnitureOrderStatuses>(readAsInt(iss));
                    tableFurnitureOrder.push_back(new FurnitureOrder(product, count, client, delivery, date, status));
                }
            }
            return 1;
        }
        template<typename T> T* getRecordById(vector<T*> &table, int id){
            if(table.empty()) return nullptr;
            for(const auto &record : table){
                if(id == record->getId()){
                    return record;
                }
            }
            return nullptr;
        }

        vector<FurnitureProduct*> selectByCategory(int categoryCode);
        vector<FurnitureOrder*> selectByTimeUnit(int timeUnitCode);
    public:
        //tables
        vector<FurnitureWorkPosition*> tableFurnitureWorkPosition;
        vector<FurnitureStructuralUnit*> tableFurnitureStructuralUnit;
        vector<FurnitureProducer*> tableFurnitureProducer;
        vector<FurnitureProduct*> tableFurnitureProduct;
        vector<FurnitureClient*> tableFurnitureClient;
        vector<FurnitureEmployee*> tableFurnitureEmployee;
        vector<FurnitureDelivery*> tableFurnitureDelivery;
        vector<FurnitureOrder*> tableFurnitureOrder;

        //queries
        int querySelectProductsByPrice(int price, int comparisonCode);
        int querySelectProductsByCategoryAndSortThemByField(int categoryCode, int sortColumnCode, int sortTypeCode);
        int querySelectTop10BestSoldProducts();
        int queryCompareProducts(string firstProductName, string secondProductName);
        int querySelectProductsByDimensions(float width, float depth, float height);
        int querySelectProductsByWarranty(float warranty);
        int querySelectProductsByAvailabilityInCategory(int categoryCode);
        int queryGetProductCharacteristics(string productName);
        int queryCountOrdersPerTimeUnitByCategory(int categoryCode, int timeUnitCode);
        int queryCountProfitPerTimeUnitFromCompletedOrders(int timeUnitCode);
        int querySelectFreeCouriers();
        int querySelectProductsByPossibilityOfDelivery();
        int queryCountTheCostOfKeepingEmployeesAtWorkPosition(int workPositionCode);
        int querySelectStructuralUnitStaff(int structuralUnitCode);

        template<typename T> T* getRecordByName(vector<T*> &table, string &name){
            if(table.empty()) return nullptr;
            for(const auto &record : table){
                if(name == record->getName()){
                    return record;
                }
            }
            return nullptr;
        }
        template<typename T> int loadTable(vector<T*> &table, string fileName){
            resetTable(table);
            ifstream fin;
            fin.open(fileName);
            if(fin.is_open()){
                parseTable(fin, table);
                fin.close();
                return 0;
            }
            cout << "File \"" << fileName << "\" not opened!\n";
            return -1;
        }
        template<typename T> int printTable(vector<T*> &table, string header = ""){
            clearConsole();
            Alignment *algn = table[0]->alignment;
            if(table.empty()){
                algn->printNoRecordsFound();
                return -1;
            }
            algn->printFullHeader(header);
            for(auto const &record : table){
                cout << record << endl;
            }
            algn->printHR();
            return 0;
        }
};

#endif // DATABASE_H_INCLUDED
