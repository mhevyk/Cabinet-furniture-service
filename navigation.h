#ifndef NAVIGATION_H_INCLUDED
#define NAVIGATION_H_INCLUDED

enum class CommandsPageChooseLanguage{
    QUIT,
    ENGLISH,
    UKRAINIAN,
    _COUNT
};
enum class CommandsPageMainMenu{
    QUIT,
    SHOW_TABLES,
    SHOW_QUERIES,
    BACK,
    _COUNT
};
enum class CommandsPageShowTable{
    BACK,
    PRODUCT,
    PRODUCER,
    WORK_POSITION,
    STRUCTURAL_UNIT,
    CLIENT,
    EMPLOYEE,
    DELIVERY,
    ORDER,
    _COUNT
};
enum class CommandsPageShowQueries{
    BACK,
    QUERY1,
    QUERY2,
    QUERY3,
    QUERY4,
    QUERY5,
    QUERY6,
    QUERY7,
    QUERY8,
    QUERY9,
    QUERY10,
    QUERY11,
    QUERY12,
    QUERY13,
    QUERY14,
    _COUNT
};
enum class CommandsPageQuery1Comparison{
    BACK,
    BIGGER,
    LESS,
    EQUAL,
    _COUNT
};
enum class CommandsPageOnlyBack{
    BACK,
    _COUNT
};
enum class CommandsPageTimeUnits{
    BACK,
    ALL_TIME,
    LAST_YEAR,
    LAST_MONTH,
    LAST_WEEK,
    _COUNT
};
enum class CommandsPageCategories{
    BACK,
    TABLES,
    SHELVES,
    WARDROBES,
    CURBSTONES,
    RACKS,
    _COUNT
};
enum class CommandsPageColumnNames{
    BACK,
    NAME,
    PRODUCER,
    PRICE,
    MATERIAL,
    STYLE,
    WARRANTY,
    _COUNT
};
enum class CommandsPageSortOrders{
    BACK,
    ASC,
    DESC,
    _COUNT
};
enum class CommandsWorkPositions{
    BACK,
    SALES_CONSULTANT,
    ACCOUNTANT,
    MAID,
    LOADER,
    COURIER,
    GUARDIAN,
    FURNITURE_ASSEMBLER,
    DESIGNER,
    _COUNT
};
enum class CommandsStructuralUnits{
    BACK,
    OFFICE,
    SHOP1,
    SHOP2,
    SHOP3,
    DEPARTMENT1,
    DEPARTMENT2,
    _COUNT
};

void loadAllTables();
void startPagesNavigation();
void getDigitCommand();
void showCurrentPage();

void parsePageChooseLanguageCommand(int command);
void parsePageMainMenu(int command);
void parsePageShowTable(int command);
void parsePageShowQueries(int command);

void parsePageQuery1Price();
void parsePageQuery1Comparison(int command);
void parsePageQuery2Category(int command);
void parsePageQuery2SelectionField(int command);
void parsePageQuery2SortOrder(int command);
void parsePageQuery7Category(int command);
void parsePageQuery9Category(int command);
void parsePageQuery9TimeUnit(int command);
void parsePageQuery10TimeUnit(int command);
void parsePageQuery13WorkPosition(int command);
void parsePageQuery14StructuralUnit(int command);
void parsePageOnlyBack(int command);


#endif // NAVIGATION_H_INCLUDED
