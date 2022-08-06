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
    //довжина дати у короткому форматі +1 для нуль-термінанта
    char buffer[11];
    strftime(buffer, sizeof(buffer), "%d.%m.%Y", date);
    out << buffer;
    return out;
}


//interface text
const array<string, LANGUAGES_COUNT> textWrongCommand = {
    "Invalid input! Please, try again!\n",
    "Некоректний ввід! Будь ласка, спробуйте ще раз!\n"
};
const array<string, LANGUAGES_COUNT> textGreeting = {
    "Hello! Welcome to our cabinet furniture service!\n\n",
    "Вітання! Запрошуємо до нашого сервісу з виготовлення корпусних меблів!\n\n"
};
const array<string, LANGUAGES_COUNT> textExit = {
    "Thank you for using our app! Good luck!\nPress any key to exit...",
    "Дякуємо за те, що користуєтеся нашим додатком!\nНатисніть будь-яку клавішу для виходу..."
};
const array<string, LANGUAGES_COUNT> textPageChangeLanguage = {
    "Type in appropriate digit command to choose your interface language:\n 1 - English\n 2 - Ukrainian\n 0 - Quit\n",
    "Введіть потрібну цифрову команду для вибору мови інтерфейсу:\n 1 - Англійська\n 2 - Українська\n 0 - Вихід\n"
};
const array<string, LANGUAGES_COUNT> textPageMainMenu = {
    "Choose an action:\n 1 - Show tables\n 2 - Show available queries\n 3 - Back\n 0 - Quit\n",
    "Виберіть дію:\n 1 - Показати таблиці\n 2 - Показати доступні запити\n 3 - Назад\n 0 - Вихід\n"
};
const array<string, LANGUAGES_COUNT> textPageShowTables = {
    "Choose a table:\n 1 - Product\n 2 - Producer\n 3 - Work position\n 4 - Structural unit\n 5 - Client\n 6 - Employee\n 7 - Delivery\n 8 - Order\n 0 - Back\n",
    "Виберіть таблицю:\n 1 - Товар\n 2 - Виробник\n 3 - Посада\n 4 - Структурна одиниця\n 5 - Клієнт\n 6 - Працівник\n 7 - Доставка\n 8 - Замовлення\n 0 - Назад\n"
};
const array<string, LANGUAGES_COUNT> textPageShowQueries = {
    "Choose query:\n 1  - Select product by price\n 2  - Select product by category, sorted by criteria\n 3  - Top-10 most sold products\n 4  - Product comparison\n 5  - Select product by dimensions\n 6  - Select products by warranty\n 7  - Select products by category, that are in stock\n 8  - Product characteristics\n 9  - Completed orders count per time unit by category\n 10 - Profit from orders by time unit\n 11 - Free couriers\n 12 - Select products by possibility of delivery\n 13 - Employee`s salary\n 14 - Structural unit staff\n 0 -  Back\n",
    "Виберіть запит:\n 1  - Вибір товару по ціні\n 2  - Вибір товару по категорії, відсортованій по критерію\n 3  - Топ-10 найбільш продаваних товарів\n 4  - Порівняння товарів\n 5  - Вибір товару по габаритах\n 6  - Вибір товару по гарантії\n 7  - Вибір товару по категорії, який є на складі\n 8  - Характеристика товару\n 9  - Кількість виконаних замовлень за одиницю часу по категорії\n 10 - Прибуток від замовлень за певний період\n 11 - Незайняті кур'єри\n 12 - Вибір товару по можливості доставки\n 13 - Заробітна плата працівникам\n 14 - Персонал структурної одиниці\n 0  - Назад\n"
};
const array<string, LANGUAGES_COUNT> textPageTimeUnit = {
    "Select orders, that were made:\n 1 - For the whole time\n 2 - Last year\n 3 - Last month\n 4 - Last week\n 0 - Back\n",
    "Вибрати замовлення, які були зроблені:\n 1 - За весь час\n 2 - Минулого року\n 3 - Минулого місяця\n 4 - Минулого тижня\n 0 - Назад\n",
};
const array<string, LANGUAGES_COUNT> textPageQuery1Price = {
    "Enter price:\n>>> ",
    "Введіть ціну:\n>>> "
};
const array<string, LANGUAGES_COUNT> textPageQuery5Width = {
    "Enter width:\n>>> ",
    "Введіть довжину:\n>>> ",
};
const array<string, LANGUAGES_COUNT> textPageQuery5Depth = {
    "Enter depth:\n>>> ",
    "Введіть глибину:\n>>> ",
};
const array<string, LANGUAGES_COUNT> textPageQuery5Height = {
    "Enter height:\n>>> ",
    "Введіть висоту:\n>>> ",
};
const array<string, LANGUAGES_COUNT> textPageQuery6Warranty = {
    "Enter warranty:\n>>> ",
    "Введіть гарантію:\n>>> ",
};
const array<string, LANGUAGES_COUNT> textPageQuery1Comparison = {
    "Select products with price, which:\n 1 - Is bigger than entered\n 2 - Is less than entered\n 3 - Equals entered\n 0 - Back\n",
    "Вибрати продукти з ціною, яка:\n 1 - Більша за введену\n 2 - Менша за введену\n 3 - Дорівнює введеній\n 0 - Назад\n"
};
const array<string, LANGUAGES_COUNT> textPageQuery2Category = {
    "Choose category, which you want to select from table:\n 1 - Tables\n 2 - Shelves\n 3 - Wardrobes\n 4 - Curbstones\n 5 - Racks\n 0 - Back\n",
    "Виберіть категорію, яку бажаєте вибрати з таблиці:\n 1 - Столи\n 2 - Полиці\n 3 - Шафи\n 4 - Тумби\n 5 - Стелажі\n 0 - Назад\n"
};
const array<string, LANGUAGES_COUNT> textPageQuery2SelectionField = {
    "Choose field, by which to sort table\n 1 - Product name\n 2 - Producer\n 3 - Price\n 4 - Material\n 5 - Style\n 6 - Warranty\n 0 - Back\n",
    "Виберіть поле, за яким відсортувати таблицю:\n 1 - Назва товару\n 2 - Виробник\n 3 - Ціна товару\n 4 - Матеріал\n 5 - Стиль\n 6 - Гарантія\n 0 - Назад\n"
};
const array<string, LANGUAGES_COUNT> textPageQuery2SortOrder = {
    "Choose sort order:\n 1 - Ascending\n 2 - Descending\n 0 - Back\n",
    "Виберіть вид сортування:\n 1 - За зростанням\n 2 - За спаданням\n 0 - Назад\n"
};
const array<string, LANGUAGES_COUNT> textPageOnlyBack = {
    "Choose an action:\n 0 - Back\n",
    "Виберіть дію:\n 0 - Назад\n "
};
const array<string, LANGUAGES_COUNT> textPageQuery13 = {
    "Select work position:\n 1 - Sales-consultant\n 2 - Accountant\n 3 - Maid\n 4 - Loader\n 5 - Courier\n 6 - Guardian\n 7 - Furniture assembler\n 8 - Designer\n 0 - Back\n",
    "Виберіть посаду:\n 1 - Продавець-консультант\n 2 - Бухгалтер\n 3 - Прибиральниця\n 4 - Вантажник\n 5 - Кур'єр\n 6 - Охоронець\n 7 - Складальник меблів\n 8 - Дизайнер\n 0 - Назад\n"
};
const array<string, LANGUAGES_COUNT> textPageQuery14 = {
    "Choose structural unit:\n 1 - Office\n 2 - Shop 1\n 3 - Shop 2\n 4 - Shop 3\n 5 - Department 1\n 6 - Department 2\n 0 - Back\n",
    "Виберіть структурну одиницю:\n 1 - Офіс\n 2 - Магазин 1\n 3 - Магазин 2\n 4 - Магазин 3\n 5 - Цех 1\n 6 - Цех 2\n 0 - Назад\n"
};
const array<string, LANGUAGES_COUNT> textNoRecords = {
    "RECORDS NOT FOUND!",
    "ЗАПИСІВ НЕ ЗНАЙДЕНО!"
};
const array<string, LANGUAGES_COUNT> textProductsAreSame{
    "Products are same!\n",
    "Продукти однакові!\n"
};
const array<string, LANGUAGES_COUNT> textNoProductInDatabase{
    "There is no such product in the database!\n",
    "Такого товару немає в базі даних!\n"
};
const array<string, LANGUAGES_COUNT> textEnterProductName{
    "(You can find out the name of the product by looking at the tables)\n 0 - Back\nEnter name of product: ",
    "(Назву товару можна дізнатися, переглянувши таблиці)\n 0 - Назад\nВведіть назву товару: "
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
