#ifndef RESOURCES_H_INCLUDED
#define RESOURCES_H_INCLUDED

#include <iostream>
#include <iomanip>
#include <string>
#include <array>

using namespace std;

enum Languages{
    LANGUAGE_ENGLISH,
    LANGUAGE_UKRAINIAN,
    LANGUAGES_COUNT
};
enum Pages{
    PAGE_CHOOSE_LANGUAGE,
    PAGE_MAIN_MENU,
    PAGE_SHOW_TABLES,
    PAGE_SHOW_QUERIES,
    PAGE_QUERY1_COMPARISON,
    PAGE_QUERY2_CATEGORY,
    PAGE_QUERY2_SELECTION_FIELD,
    PAGE_QUERY2_SORT_ORDER,
    PAGE_QUERY7_CATEGORY,
    PAGE_QUERY9_CATEGORY,
    PAGE_QUERY9_TIME_UNIT,
    PAGE_QUERY10_TIME_UNIT,
    PAGE_QUERY13_WORK_POSITION,
    PAGE_QUERY14_STRUCTURAL_UNIT,
    PAGE_ONLY_BACK
};
enum class Tables{
    WORK_POSITION,
    STRUCTURAL_UNIT,
    PRODUCER,
    PRODUCT,
    CLIENT,
    EMPLOYEE,
    DELIVERY,
    ORDER
};

void clearConsole();

void setCurrentLanguage(Languages language);
string getTextInCurrentLanguage(const array<string, LANGUAGES_COUNT> &arrayOfTranslates);

bool isCommandInRangeOfPageCommands(int command);
void setCommandsRange(int range);

Pages getCurrentPage();
int setCurrentPage(Pages page);
void setPrevPage();
template<typename T>
void setPage(Pages page, T commandsCount, bool clearConsoleFlag = true){
    if(clearConsoleFlag) clearConsole();
    setCurrentPage(page);
    setCommandsRange(static_cast<int>(commandsCount));
}

struct tm* stringToDate(const string &dateString);
ostream& operator<<(ostream& out, struct tm *date);

extern const array<string, LANGUAGES_COUNT> textGreeting;
extern const array<string, LANGUAGES_COUNT> textPageChangeLanguage;
extern const array<string, LANGUAGES_COUNT> textPageMainMenu;
extern const array<string, LANGUAGES_COUNT> textWrongCommand;
extern const array<string, LANGUAGES_COUNT> textPageShowTables;
extern const array<string, LANGUAGES_COUNT> textPageShowQueries;
extern const array<string, LANGUAGES_COUNT> textPageTimeUnit;
extern const array<string, LANGUAGES_COUNT> textPageQuery1Price;
extern const array<string, LANGUAGES_COUNT> textPageQuery1Comparison;
extern const array<string, LANGUAGES_COUNT> textPageQuery2Category;
extern const array<string, LANGUAGES_COUNT> textPageQuery2SelectionField;
extern const array<string, LANGUAGES_COUNT> textPageQuery2SortOrder;
extern const array<string, LANGUAGES_COUNT> textPageQuery5Width;
extern const array<string, LANGUAGES_COUNT> textPageQuery5Depth;
extern const array<string, LANGUAGES_COUNT> textPageQuery5Height;
extern const array<string, LANGUAGES_COUNT> textPageQuery6Warranty;
extern const array<string, LANGUAGES_COUNT> textPageQuery13;
extern const array<string, LANGUAGES_COUNT> textPageQuery14;
extern const array<string, LANGUAGES_COUNT> textPageOnlyBack;
extern const array<string, LANGUAGES_COUNT> textNoRecords;
extern const array<string, LANGUAGES_COUNT> textProductsAreSame;
extern const array<string, LANGUAGES_COUNT> textNoProductInDatabase;
extern const array<string, LANGUAGES_COUNT> textEnterProductName;

void setConsoleLanguageToUkrainian();
void setConsoleFullScreen();
void exitProgram();
void resetStream();

int readAsInt(const array<string, LANGUAGES_COUNT> &description);
float readAsFloat(const array<string, LANGUAGES_COUNT> &description);

string printFloatWithPrecision(float number, int fractionPartDigitCount);

int readAsInt(istringstream &iss, const char separator = '\t');
float readAsFloat(istringstream &iss, const char separator = '\t');
string readAsString(istringstream &iss, const char separator = '\t');
bool readAsBool(istringstream &iss, const char separator = '\t');
char readAsChar(istringstream &iss, const char separator = '\t');

#endif // RESOURCES_H_INCLUDED

