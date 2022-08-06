#include <windows.h>
#include <limits>
#include <sstream>
#include <ctime>

#include "resources.h"

//languages
Languages currentLanguage = LANGUAGE_ENGLISH;

void setCurrentLanguage(Languages language){
    currentLanguage = language;
}
//gets array of translates and prints language by languageIndex
string getTextInCurrentLanguage(const array<string, LANGUAGES_COUNT> &arrayOfTranslates){
    return arrayOfTranslates.at(currentLanguage);
}
//page commands validation
int prevCommandsRange, currentCommandsRange = 3;

bool isCommandInRangeOfPageCommands(int command){
    return 0 <= command && command < currentCommandsRange;
}
void setCommandsRange(int range){
    prevCommandsRange = currentCommandsRange;
    currentCommandsRange = range;
}

//pages
Pages prevPage, currentPage = PAGE_CHOOSE_LANGUAGE;

Pages getCurrentPage(){
    return currentPage;
}
int setCurrentPage(Pages page){
    prevPage = currentPage;
    currentPage = page;
    return 0;
}
void setPrevPage(){
    clearConsole();
    setCurrentPage(prevPage);
    setCommandsRange(prevCommandsRange);
}

//date validation
struct tm* stringToDate(const string &dateString){
	time_t now = time(0);
	tm *date;

	istringstream iss(dateString);
	int dateParts[3];
	for(int i = 0; i < 3; i++){
        dateParts[i] = readAsInt(iss, '.');
	}

	date = localtime(&now);
	date->tm_mday = dateParts[0];
	date->tm_mon = dateParts[1] - 1;
	date->tm_year = dateParts[2] - 1900;

	return date;
}
ostream& operator<<(ostream& out, struct tm *date){
    //������� ���� � ��������� ������ +1 ��� ����-���������
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d.%m.%Y", date);
    out << buffer;
    return out;
}


//interface text
const array<string, LANGUAGES_COUNT> textWrongCommand = {
    "Invalid input! Please, try again!\n",
    "����������� ���! ���� �����, ��������� �� ���!\n"
};
const array<string, LANGUAGES_COUNT> textGreeting = {
    "Hello! Welcome to our cabinet furniture service!\n\n",
    "³�����! ��������� �� ������ ������ � ������������ ��������� �����!\n\n"
};
const array<string, LANGUAGES_COUNT> textExit = {
    "Thank you for using our app! Good luck!\nPress any key to exit...",
    "������ �� ��, �� ����������� ����� ��������!\n�������� ����-��� ������ ��� ������..."
};
const array<string, LANGUAGES_COUNT> textPageChangeLanguage = {
    "Type in appropriate digit command to choose your interface language:\n 1 - English\n 2 - Ukrainian\n 0 - Quit\n",
    "������ ������� ������� ������� ��� ������ ���� ����������:\n 1 - ���������\n 2 - ���������\n 0 - �����\n"
};
const array<string, LANGUAGES_COUNT> textPageMainMenu = {
    "Choose an action:\n 1 - Show tables\n 2 - Show available queries\n 3 - Back\n 0 - Quit\n",
    "������� ��:\n 1 - �������� �������\n 2 - �������� ������� ������\n 3 - �����\n 0 - �����\n"
};
const array<string, LANGUAGES_COUNT> textPageShowTables = {
    "Choose a table:\n 1 - Product\n 2 - Producer\n 3 - Work position\n 4 - Structural unit\n 5 - Client\n 6 - Employee\n 7 - Delivery\n 8 - Order\n 0 - Back\n",
    "������� �������:\n 1 - �����\n 2 - ��������\n 3 - ������\n 4 - ���������� �������\n 5 - �볺��\n 6 - ���������\n 7 - ��������\n 8 - ����������\n 0 - �����\n"
};
const array<string, LANGUAGES_COUNT> textPageShowQueries = {
    "Choose query:\n 1  - Select product by price\n 2  - Select product by category, sorted by criteria\n 3  - Top-10 most sold products\n 4  - Product comparison\n 5  - Select product by dimensions\n 6  - Select products by warranty\n 7  - Select products by category, that are in stock\n 8  - Product characteristics\n 9  - Completed orders count per time unit by category\n 10 - Profit from orders by time unit\n 11 - Free couriers\n 12 - Select products by possibility of delivery\n 13 - Employee`s salary\n 14 - Structural unit staff\n 0 -  Back\n",
    "������� �����:\n 1  - ���� ������ �� ���\n 2  - ���� ������ �� �������, ����������� �� �������\n 3  - ���-10 ������� ���������� ������\n 4  - ��������� ������\n 5  - ���� ������ �� ���������\n 6  - ���� ������ �� ������\n 7  - ���� ������ �� �������, ���� � �� �����\n 8  - �������������� ������\n 9  - ʳ������ ��������� ��������� �� ������� ���� �� �������\n 10 - �������� �� ��������� �� ������ �����\n 11 - �������� ���'���\n 12 - ���� ������ �� ��������� ��������\n 13 - �������� ����� �����������\n 14 - �������� ���������� �������\n 0  - �����\n"
};
const array<string, LANGUAGES_COUNT> textPageTimeUnit = {
    "Select orders, that were made:\n 1 - For the whole time\n 2 - Last year\n 3 - Last month\n 4 - Last week\n 0 - Back\n",
    "������� ����������, �� ���� �������:\n 1 - �� ���� ���\n 2 - �������� ����\n 3 - �������� �����\n 4 - �������� �����\n 0 - �����\n",
};
const array<string, LANGUAGES_COUNT> textPageQuery1Price = {
    "Enter price:\n>>> ",
    "������ ����:\n>>> "
};
const array<string, LANGUAGES_COUNT> textPageQuery5Width = {
    "Enter width:\n>>> ",
    "������ �������:\n>>> ",
};
const array<string, LANGUAGES_COUNT> textPageQuery5Depth = {
    "Enter depth:\n>>> ",
    "������ �������:\n>>> ",
};
const array<string, LANGUAGES_COUNT> textPageQuery5Height = {
    "Enter height:\n>>> ",
    "������ ������:\n>>> ",
};
const array<string, LANGUAGES_COUNT> textPageQuery6Warranty = {
    "Enter warranty:\n>>> ",
    "������ �������:\n>>> ",
};
const array<string, LANGUAGES_COUNT> textPageQuery1Comparison = {
    "Select products with price, which:\n 1 - Is bigger than entered\n 2 - Is less than entered\n 3 - Equals entered\n 0 - Back\n",
    "������� �������� � �����, ���:\n 1 - ������ �� �������\n 2 - ����� �� �������\n 3 - ������� �������\n 0 - �����\n"
};
const array<string, LANGUAGES_COUNT> textPageQuery2Category = {
    "Choose category, which you want to select from table:\n 1 - Tables\n 2 - Shelves\n 3 - Wardrobes\n 4 - Curbstones\n 5 - Racks\n 0 - Back\n",
    "������� ��������, ��� ������ ������� � �������:\n 1 - �����\n 2 - ������\n 3 - ����\n 4 - �����\n 5 - ������\n 0 - �����\n"
};
const array<string, LANGUAGES_COUNT> textPageQuery2SelectionField = {
    "Choose field, by which to sort table\n 1 - Product name\n 2 - Producer\n 3 - Price\n 4 - Material\n 5 - Style\n 6 - Warranty\n 0 - Back\n",
    "������� ����, �� ���� ����������� �������:\n 1 - ����� ������\n 2 - ��������\n 3 - ֳ�� ������\n 4 - �������\n 5 - �����\n 6 - �������\n 0 - �����\n"
};
const array<string, LANGUAGES_COUNT> textPageQuery2SortOrder = {
    "Choose sort order:\n 1 - Ascending\n 2 - Descending\n 0 - Back\n",
    "������� ��� ����������:\n 1 - �� ����������\n 2 - �� ���������\n 0 - �����\n"
};
const array<string, LANGUAGES_COUNT> textPageOnlyBack = {
    "Choose an action:\n 0 - Back\n",
    "������� ��:\n 0 - �����\n "
};
const array<string, LANGUAGES_COUNT> textPageQuery13 = {
    "Select work position:\n 1 - Sales-consultant\n 2 - Accountant\n 3 - Maid\n 4 - Loader\n 5 - Courier\n 6 - Guardian\n 7 - Furniture assembler\n 8 - Designer\n 0 - Back\n",
    "������� ������:\n 1 - ���������-�����������\n 2 - ���������\n 3 - �������������\n 4 - ���������\n 5 - ���'��\n 6 - ���������\n 7 - ����������� �����\n 8 - ��������\n 0 - �����\n"
};
const array<string, LANGUAGES_COUNT> textPageQuery14 = {
    "Choose structural unit:\n 1 - Office\n 2 - Shop 1\n 3 - Shop 2\n 4 - Shop 3\n 5 - Department 1\n 6 - Department 2\n 0 - Back\n",
    "������� ���������� �������:\n 1 - ����\n 2 - ������� 1\n 3 - ������� 2\n 4 - ������� 3\n 5 - ��� 1\n 6 - ��� 2\n 0 - �����\n"
};
const array<string, LANGUAGES_COUNT> textNoRecords = {
    "RECORDS NOT FOUND!",
    "����Ѳ� �� ��������!"
};
const array<string, LANGUAGES_COUNT> textProductsAreSame{
    "Products are same!\n",
    "�������� �������!\n"
};
const array<string, LANGUAGES_COUNT> textNoProductInDatabase{
    "There is no such product in the database!\n",
    "������ ������ ���� � ��� �����!\n"
};
const array<string, LANGUAGES_COUNT> textEnterProductName{
    "(You can find out the name of the product by looking at the tables)\n 0 - Back\nEnter name of product: ",
    "(����� ������ ����� ��������, ������������ �������)\n 0 - �����\n������ ����� ������: "
};

//console app and streams
void setConsoleLanguageToUkrainian(){
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
}
void setConsoleFullScreen(){
    system("mode con COLS=700");
    ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
}
void clearConsole(){
    system("cls");
}
void exitProgram(){
    cout << endl << getTextInCurrentLanguage(textExit);
    resetStream();
    cin.get();
    exit(EXIT_SUCCESS);
}
void resetStream(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//data validation
string printFloatWithPrecision(float number, int fractionPartDigitCount){
    stringstream ss;
    ss << fixed << setprecision(fractionPartDigitCount) << number;
    return ss.str();
}
int readAsInt(const array<string, LANGUAGES_COUNT> &description){
    int value;
    while(1){
        cout << getTextInCurrentLanguage(description);
        cin >> value;
        resetStream();
        if(cin.fail() || value <= 0){
            cout << getTextInCurrentLanguage(textWrongCommand);
        }
        else{
            return value;
            break;
        }
    }
}
float readAsFloat(const array<string, LANGUAGES_COUNT> &description){
    float value;
    while(1){
        cout << getTextInCurrentLanguage(description);
        cin >> value;
        resetStream();
        if(cin.fail() || value <= 0){
            cout << getTextInCurrentLanguage(textWrongCommand);
        }
        else{
            return value;
            break;
        }
    }
}
//readers by type from file
int readAsInt(istringstream &iss, const char separator){
    string temp;
    getline(iss, temp, separator);
    return stoi(temp);
}
float readAsFloat(istringstream &iss, const char separator){
    string temp;
    getline(iss, temp, separator);
    return stof(temp);
}
string readAsString(istringstream &iss, const char separator){
    string temp;
    getline(iss, temp, separator);
    return temp;
}
bool readAsBool(istringstream &iss, const char separator){
    string temp;
    getline(iss, temp, separator);
    return static_cast<bool>(stoi(temp));
}
char readAsChar(istringstream &iss, const char separator){
    string temp;
    getline(iss, temp, separator);
    return static_cast<char>(temp[0]);
}
