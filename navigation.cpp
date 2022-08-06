#include "resources.h"
#include "navigation.h"
#include "database.h"

vector<int> tempStorage;

Database DB;

string readProduct(const array<string, LANGUAGES_COUNT> &description, string anotherProductName = ""){
    string productName;
    while(1){
        cout << getTextInCurrentLanguage(description);
        getline(cin, productName);
        if(productName == "0") break;
        if(productName == anotherProductName){
            cout << getTextInCurrentLanguage(textProductsAreSame);
            continue;
        }
        if(!DB.getRecordByName(DB.tableFurnitureProduct, productName)){
            cout << getTextInCurrentLanguage(textNoProductInDatabase);
        }
        else break;
    }
    return productName;
}

void loadAllTables(){
//    DB.loadTable(DB.tableFurnitureWorkPosition, "../../data/workPosition.txt");
//    DB.loadTable(DB.tableFurnitureStructuralUnit, "../../data/structuralUnit.txt");
//    DB.loadTable(DB.tableFurnitureProducer, "../../data/producer.txt");
//    DB.loadTable(DB.tableFurnitureProduct, "../../data/product.txt");
//    DB.loadTable(DB.tableFurnitureClient, "../../data/client.txt");
//    DB.loadTable(DB.tableFurnitureEmployee, "../../data/employee.txt");
//    DB.loadTable(DB.tableFurnitureDelivery, "../../data/delivery.txt");
//    DB.loadTable(DB.tableFurnitureOrder, "../../data/order.txt");
    DB.loadTable(DB.tableFurnitureWorkPosition, "data/workPosition.txt");
    DB.loadTable(DB.tableFurnitureStructuralUnit, "data/structuralUnit.txt");
    DB.loadTable(DB.tableFurnitureProducer, "data/producer.txt");
    DB.loadTable(DB.tableFurnitureProduct, "data/product.txt");
    DB.loadTable(DB.tableFurnitureClient, "data/client.txt");
    DB.loadTable(DB.tableFurnitureEmployee, "data/employee.txt");
    DB.loadTable(DB.tableFurnitureDelivery, "data/delivery.txt");
    DB.loadTable(DB.tableFurnitureOrder, "data/order.txt");
}

void startPagesNavigation(){
    setConsoleFullScreen();
    setConsoleLanguageToUkrainian();

    cout << getTextInCurrentLanguage(textGreeting);

    loadAllTables();

    while(1){
        showCurrentPage();
        getDigitCommand();
    }
}
void showCurrentPage(){
    switch(getCurrentPage()){
        case PAGE_CHOOSE_LANGUAGE:
            cout << getTextInCurrentLanguage(textPageChangeLanguage);
            break;
        case PAGE_MAIN_MENU:
            cout << getTextInCurrentLanguage(textPageMainMenu);
            break;
        case PAGE_SHOW_TABLES:
            cout << getTextInCurrentLanguage(textPageShowTables);
            break;
        case PAGE_SHOW_QUERIES:
            cout << getTextInCurrentLanguage(textPageShowQueries);
            break;
        case PAGE_QUERY1_COMPARISON:
            cout << getTextInCurrentLanguage(textPageQuery1Comparison);
            break;
        case PAGE_QUERY2_CATEGORY:
        case PAGE_QUERY7_CATEGORY:
        case PAGE_QUERY9_CATEGORY:
            cout << getTextInCurrentLanguage(textPageQuery2Category);
            break;
        case PAGE_QUERY2_SELECTION_FIELD:
            cout << getTextInCurrentLanguage(textPageQuery2SelectionField);
            break;
        case PAGE_QUERY2_SORT_ORDER:
            cout << getTextInCurrentLanguage(textPageQuery2SortOrder);
            break;
        case PAGE_QUERY9_TIME_UNIT:
        case PAGE_QUERY10_TIME_UNIT:
            cout << getTextInCurrentLanguage(textPageTimeUnit);
            break;
        case PAGE_QUERY13_WORK_POSITION:
            cout << getTextInCurrentLanguage(textPageQuery13);
            break;
        case PAGE_QUERY14_STRUCTURAL_UNIT:
            cout << getTextInCurrentLanguage(textPageQuery14);
            break;
        case PAGE_ONLY_BACK:
            cout << getTextInCurrentLanguage(textPageOnlyBack);
            break;
        default:
            break;
    }
}
void getDigitCommand(){
    cout << ">>> ";
    int command;
    cin >> command;

    if(cin.fail() || !isCommandInRangeOfPageCommands(command)){
        cout << getTextInCurrentLanguage(textWrongCommand);
        resetStream();
    }
    else{
        switch(getCurrentPage()){
            case PAGE_CHOOSE_LANGUAGE:
                parsePageChooseLanguageCommand(command);
                break;
            case PAGE_MAIN_MENU:
                parsePageMainMenu(command);
                break;
            case PAGE_SHOW_TABLES:
                parsePageShowTable(command);
                break;
            case PAGE_SHOW_QUERIES:
                parsePageShowQueries(command);
                break;
            case PAGE_QUERY1_COMPARISON:
                parsePageQuery1Comparison(command);
                break;
            case PAGE_QUERY2_CATEGORY:
                parsePageQuery2Category(command);
                break;
            case PAGE_QUERY7_CATEGORY:
                parsePageQuery7Category(command);
                break;
            case PAGE_QUERY2_SELECTION_FIELD:
                parsePageQuery2SelectionField(command);
                break;
            case PAGE_QUERY2_SORT_ORDER:
                parsePageQuery2SortOrder(command);
                break;
            case PAGE_ONLY_BACK:
                parsePageOnlyBack(command);
                break;
            case PAGE_QUERY9_CATEGORY:
                parsePageQuery9Category(command);
                break;
            case PAGE_QUERY9_TIME_UNIT:
                parsePageQuery9TimeUnit(command);
                break;
            case PAGE_QUERY10_TIME_UNIT:
                parsePageQuery10TimeUnit(command);
                break;
            case PAGE_QUERY13_WORK_POSITION:
                parsePageQuery13WorkPosition(command);
                break;
            case PAGE_QUERY14_STRUCTURAL_UNIT:
                parsePageQuery14StructuralUnit(command);
                break;
            default:
                break;
        }
    }
}
void parsePageChooseLanguageCommand(int command){
    CommandsPageChooseLanguage ecommand = static_cast<CommandsPageChooseLanguage>(command);
    switch(ecommand){
        case CommandsPageChooseLanguage::QUIT:
            exitProgram();
            break;
        case CommandsPageChooseLanguage::ENGLISH:
            setCurrentLanguage(LANGUAGE_ENGLISH);
            break;
        case CommandsPageChooseLanguage::UKRAINIAN:
            setCurrentLanguage(LANGUAGE_UKRAINIAN);
            break;
        default:
            break;
    }
    setPage(PAGE_MAIN_MENU, CommandsPageMainMenu::_COUNT);
}
void parsePageMainMenu(int command){
    CommandsPageMainMenu ecommand = static_cast<CommandsPageMainMenu>(command);
    switch(ecommand){
        case CommandsPageMainMenu::QUIT:
            exitProgram();
            break;
        case CommandsPageMainMenu::BACK:
            setPage(PAGE_CHOOSE_LANGUAGE, CommandsPageChooseLanguage::_COUNT);
            break;
        case CommandsPageMainMenu::SHOW_TABLES:
            setPage(PAGE_SHOW_TABLES, CommandsPageShowTable::_COUNT);
            break;
        case CommandsPageMainMenu::SHOW_QUERIES:
            setPage(PAGE_SHOW_QUERIES, CommandsPageShowQueries::_COUNT);
            break;
        default:
            break;
    }
}
void parsePageShowTable(int command){
    CommandsPageShowTable ecommand = static_cast<CommandsPageShowTable>(command);
    switch(ecommand){
        case CommandsPageShowTable::BACK:
            setPage(PAGE_MAIN_MENU, CommandsPageMainMenu::_COUNT);
            break;
        case CommandsPageShowTable::WORK_POSITION:
            DB.printTable(DB.tableFurnitureWorkPosition);
            break;
        case CommandsPageShowTable::STRUCTURAL_UNIT:
            DB.printTable(DB.tableFurnitureStructuralUnit);
            break;
        case CommandsPageShowTable::PRODUCER:
            DB.printTable(DB.tableFurnitureProducer);
            break;
        case CommandsPageShowTable::PRODUCT:
            DB.printTable(DB.tableFurnitureProduct);
            break;
        case CommandsPageShowTable::CLIENT:
            DB.printTable(DB.tableFurnitureClient);
            break;
        case CommandsPageShowTable::EMPLOYEE:
            DB.printTable(DB.tableFurnitureEmployee);
            break;
        case CommandsPageShowTable::DELIVERY:
            DB.printTable(DB.tableFurnitureDelivery);
            break;
        case CommandsPageShowTable::ORDER:
            DB.printTable(DB.tableFurnitureOrder);
            break;
        default:
            break;
    }
}
void parsePageShowQueries(int command){
    CommandsPageShowQueries ecommand = static_cast<CommandsPageShowQueries>(command);
    string firstProductName, secondProductName;
    switch(ecommand){
        case CommandsPageShowQueries::BACK:
            setPage(PAGE_MAIN_MENU, CommandsPageMainMenu::_COUNT);
            break;
        case CommandsPageShowQueries::QUERY1:
            clearConsole();
            int price;
            price = readAsInt(textPageQuery1Price);
            tempStorage.push_back(price);
            setPage(PAGE_QUERY1_COMPARISON, CommandsPageQuery1Comparison::_COUNT);
            break;
        case CommandsPageShowQueries::QUERY2:
            setPage(PAGE_QUERY2_CATEGORY, CommandsPageCategories::_COUNT);
            break;
        case CommandsPageShowQueries::QUERY3:
            clearConsole();
            DB.querySelectTop10BestSoldProducts();
            setPage(PAGE_ONLY_BACK, CommandsPageOnlyBack::_COUNT, false);
            break;
        case CommandsPageShowQueries::QUERY4:
            resetStream();
            clearConsole();
            firstProductName = readProduct(textEnterProductName);
            if(firstProductName == "0"){
                setPage(PAGE_SHOW_QUERIES, CommandsPageShowQueries::_COUNT);
                break;
            }
            secondProductName = readProduct(textEnterProductName, firstProductName);
            if(secondProductName == "0"){
                setPage(PAGE_SHOW_QUERIES, CommandsPageShowQueries::_COUNT);
                break;
            }
            DB.queryCompareProducts(firstProductName, secondProductName);
            setPage(PAGE_ONLY_BACK, CommandsPageOnlyBack::_COUNT, false);
            break;
        case CommandsPageShowQueries::QUERY5:
            clearConsole();
            float width, depth, height;
            width = readAsFloat(textPageQuery5Width);
            depth = readAsFloat(textPageQuery5Depth);
            height = readAsFloat(textPageQuery5Height);
            DB.querySelectProductsByDimensions(width, depth, height);
            setPage(PAGE_ONLY_BACK, CommandsPageOnlyBack::_COUNT, false);
            break;
        case CommandsPageShowQueries::QUERY6:
            clearConsole();
            float warranty;
            warranty = readAsFloat(textPageQuery6Warranty);
            DB.querySelectProductsByWarranty(warranty);
            setPage(PAGE_ONLY_BACK, CommandsPageOnlyBack::_COUNT, false);
            break;
        case CommandsPageShowQueries::QUERY7:
            setPage(PAGE_QUERY7_CATEGORY, CommandsPageCategories::_COUNT);
            break;
        case CommandsPageShowQueries::QUERY8:
            resetStream();
            clearConsole();
            firstProductName = readProduct(textEnterProductName);
            if(firstProductName == "0"){
                setPage(PAGE_SHOW_QUERIES, CommandsPageShowQueries::_COUNT);
                break;
            }
            clearConsole();
            DB.queryGetProductCharacteristics(firstProductName);
            setPage(PAGE_ONLY_BACK, CommandsPageOnlyBack::_COUNT, false);
            break;
        case CommandsPageShowQueries::QUERY9:
            setPage(PAGE_QUERY9_CATEGORY, CommandsPageCategories::_COUNT);
            break;
        case CommandsPageShowQueries::QUERY10:
            setPage(PAGE_QUERY10_TIME_UNIT, CommandsPageTimeUnits::_COUNT);
            break;
        case CommandsPageShowQueries::QUERY11:
            clearConsole();
            DB.querySelectFreeCouriers();
            setPage(PAGE_ONLY_BACK, CommandsPageOnlyBack::_COUNT, false);
            break;
        case CommandsPageShowQueries::QUERY12:
            clearConsole();
            DB.querySelectProductsByPossibilityOfDelivery();
            setPage(PAGE_ONLY_BACK, CommandsPageOnlyBack::_COUNT, false);
            break;
        case CommandsPageShowQueries::QUERY13:
            setPage(PAGE_QUERY13_WORK_POSITION, CommandsWorkPositions::_COUNT);
            break;
        case CommandsPageShowQueries::QUERY14:
            setPage(PAGE_QUERY14_STRUCTURAL_UNIT, CommandsStructuralUnits::_COUNT);
            break;
        default:
            break;
    }
}
void parsePageQuery1Comparison(int command){
    CommandsPageQuery1Comparison ecommand = static_cast<CommandsPageQuery1Comparison>(command);
    switch(ecommand){
        case CommandsPageQuery1Comparison::BACK:
            if(!tempStorage.empty()) tempStorage.pop_back();
            setPage(PAGE_SHOW_QUERIES, CommandsPageShowQueries::_COUNT);
            break;
        default:
            DB.querySelectProductsByPrice(tempStorage.at(0), command);
    }
}
void parsePageQuery2Category(int command){
    CommandsPageCategories ecommand = static_cast<CommandsPageCategories>(command);
    switch(ecommand){
        case CommandsPageCategories::BACK:
            setPage(PAGE_SHOW_QUERIES, CommandsPageShowQueries::_COUNT);
            break;
        default:
            tempStorage.push_back(command);
            setPage(PAGE_QUERY2_SELECTION_FIELD, CommandsPageColumnNames::_COUNT);
            break;
    }
}
void parsePageQuery2SelectionField(int command){
    CommandsPageColumnNames ecommand = static_cast<CommandsPageColumnNames>(command);
    switch(ecommand){
        case CommandsPageColumnNames::BACK:
            if(!tempStorage.empty()) tempStorage.pop_back();
            setPage(PAGE_QUERY2_CATEGORY, CommandsPageCategories::_COUNT);
            break;
        default:
            tempStorage.push_back(command);
            setPage(PAGE_QUERY2_SORT_ORDER, CommandsPageSortOrders::_COUNT);
            break;
    }
}
void parsePageQuery2SortOrder(int command){
    CommandsPageSortOrders ecommand = static_cast<CommandsPageSortOrders>(command);
    switch(ecommand){
        case CommandsPageSortOrders::BACK:
            if(!tempStorage.empty()) tempStorage.pop_back();
            setPage(PAGE_QUERY2_SELECTION_FIELD, CommandsPageColumnNames::_COUNT);
            break;
        default:
            DB.querySelectProductsByCategoryAndSortThemByField(tempStorage.at(0), tempStorage.at(1), command);
            break;
    }
}
void parsePageQuery7Category(int command){
    CommandsPageCategories ecommand = static_cast<CommandsPageCategories>(command);
    switch(ecommand){
        case CommandsPageCategories::BACK:
            setPage(PAGE_SHOW_QUERIES, CommandsPageShowQueries::_COUNT);
            break;
        default:
            DB.querySelectProductsByAvailabilityInCategory(command);
            break;
    }
}
void parsePageQuery9Category(int command){
    CommandsPageCategories ecommand = static_cast<CommandsPageCategories>(command);
    switch(ecommand){
        case CommandsPageCategories::BACK:
            if(!tempStorage.empty()) tempStorage.pop_back();
            setPage(PAGE_SHOW_QUERIES, CommandsPageShowQueries::_COUNT);
            break;
        default:
            tempStorage.push_back(command);
            setPage(PAGE_QUERY9_TIME_UNIT, CommandsPageTimeUnits::_COUNT);
            break;
    }
}
void parsePageQuery9TimeUnit(int command){
    CommandsPageTimeUnits ecommand = static_cast<CommandsPageTimeUnits>(command);
    switch(ecommand){
        case CommandsPageTimeUnits::BACK:
            if(!tempStorage.empty()) tempStorage.pop_back();
            setPage(PAGE_QUERY9_CATEGORY, CommandsPageCategories::_COUNT);
            break;
        default:
            DB.queryCountOrdersPerTimeUnitByCategory(tempStorage.at(0), command);
            break;
    }
}
void parsePageQuery10TimeUnit(int command){
    CommandsPageTimeUnits ecommand = static_cast<CommandsPageTimeUnits>(command);
    switch(ecommand){
        case CommandsPageTimeUnits::BACK:
            if(!tempStorage.empty()) tempStorage.pop_back();
            setPage(PAGE_SHOW_QUERIES, CommandsPageShowQueries::_COUNT);
            break;
        default:
            DB.queryCountProfitPerTimeUnitFromCompletedOrders(command);
            break;
    }
}
void parsePageQuery13WorkPosition(int command){
    CommandsWorkPositions ecommand = static_cast<CommandsWorkPositions>(command);
    switch(ecommand){
        case CommandsWorkPositions::BACK:
            setPage(PAGE_SHOW_QUERIES, CommandsPageShowQueries::_COUNT);
            break;
        default:
            DB.queryCountTheCostOfKeepingEmployeesAtWorkPosition(command);
            break;
    }
}
void parsePageQuery14StructuralUnit(int command){
    CommandsStructuralUnits ecommand = static_cast<CommandsStructuralUnits>(command);
    switch(ecommand){
        case CommandsStructuralUnits::BACK:
            setPage(PAGE_SHOW_QUERIES, CommandsPageShowQueries::_COUNT);
            break;
        default:
            DB.querySelectStructuralUnitStaff(command);
            break;
    }
}
void parsePageOnlyBack(int command){
    CommandsPageOnlyBack ecommand = static_cast<CommandsPageOnlyBack>(command);
    switch(ecommand){
        case CommandsPageOnlyBack::BACK:
            setPrevPage();
            break;
        default:
            break;
    }
}
