#include <vector>
#include <functional>
#include <iomanip>

#include "tables.h"
#include "resources.h"

//WORK POSITION////////////////////////////////////////////////////////////////////////////////////
int FurnitureWorkPosition::_instanceCounter = 1;
Alignment *const FurnitureWorkPosition::alignment = new Alignment(Tables::WORK_POSITION, {
    "№  ",
    "Назва посади",
    "Зарплата (грн)"
});

FurnitureWorkPosition::FurnitureWorkPosition(string &name, float salary):
    m_id(_instanceCounter++), m_name(name), m_salary(salary)
{
    alignment->setRowPad(1, name.length());
}

ostream& operator<<(ostream &out, FurnitureWorkPosition *wp){
    out << Borders::LEFT << fixed << setprecision(2);
    out << setw(wp->alignment->getRowPad(0)) << wp->m_id;
    out << Borders::CENTER;
    out << setw(wp->alignment->getRowPad(1)) << wp->m_name;
    out << Borders::CENTER;
    out << setw(wp->alignment->getRowPad(2)) << wp->m_salary;
    out << Borders::RIGHT;
    return out;
}

//STRUCTURAL UNIT///////////////////////////////////////////////////////////////////////////////////
int FurnitureStructuralUnit::_instanceCounter = 1;
Alignment *const FurnitureStructuralUnit::alignment = new Alignment(Tables::STRUCTURAL_UNIT, {
    "№  ",
    "Назва структурної одиниці",
    "Адреса",
    "Адресат доставки"
});

FurnitureStructuralUnit::FurnitureStructuralUnit(string &name, string &adress, FurnitureAddressees addressee):
    m_id(_instanceCounter++), m_name(name), m_adress(adress), m_addressee(addressee)
{
    alignment->setRowPad(2, adress.length());
}

ostream& operator<<(ostream &out, FurnitureStructuralUnit *su){
    out << Borders::LEFT;
    out << setw(su->alignment->getRowPad(0)) << su->m_id;
    out << Borders::CENTER;
    out << setw(su->alignment->getRowPad(1)) << su->m_name;
    out << Borders::CENTER;
    out << setw(su->alignment->getRowPad(2)) << su->m_adress;
    out << Borders::CENTER;
    out << setw(su->alignment->getRowPad(3)) << su->getAddressee();
    out << Borders::RIGHT;
    return out;
}

string FurnitureStructuralUnit::getAddressee(){
    switch(m_addressee){
        case FurnitureAddressees::OFFICE: return "Офіс";
        case FurnitureAddressees::DEPARTMENT: return "Цех";
        case FurnitureAddressees::SHOP: return "Магазин";
        case FurnitureAddressees::CLIENT: return "Клієнт";
    }
    return "";
}

//PRODUCER/////////////////////////////////////////////////////////////////////////////////////////
int FurnitureProducer::_instanceCounter = 1;
Alignment *const FurnitureProducer::alignment = new Alignment(Tables::PRODUCER, {
    "№  ",
    "Назва виробника",
    "Адреса",
    "Телефон     ",
    "Рейтинг"
});

FurnitureProducer::FurnitureProducer(string &name, string &adress, string &phone, string &rate):
    m_id(_instanceCounter++), m_name(name), m_adress(adress), m_phone(phone), m_rate(rate)
{
    alignment->setRowPad(1, name.length())
             ->setRowPad(2, adress.length());
}

ostream& operator<<(ostream &out, FurnitureProducer *p){
    out << Borders::LEFT;
    out << setw(p->alignment->getRowPad(0)) << p->m_id;
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(1)) << p->m_name;
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(2)) << p->m_adress;
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(3)) << p->m_phone;
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(4)) << p->m_rate;
    out << Borders::RIGHT;
    return out;
}

//PRODUCT/////////////////////////////////////////////////////////////////////////////////////////
int FurnitureProduct::_instanceCounter = 1;
Alignment *const FurnitureProduct::alignment = new Alignment(Tables::PRODUCT, {
    "№  ",
    "Категорія",
    "Назва товару",
    "Виробник",
    "Ціна (грн)",
    "Доставка",
    "Ширина",
    "Глибина",
    "Висота",
    "Матеріал",
    "Стиль",
    "На складі (шт)",
    "Гарантія"
});

FurnitureProduct::FurnitureProduct(
         FurnitureCategories category,
         string &name,
         FurnitureProducer *producer,
         int price,
         bool deliveryFlag,
         const FurnitureDimensions &dimensions,
         FurnitureMaterials material,
         FurnitureStyles style,
         int inStockCount,
         float warranty
    ):
        m_id(_instanceCounter++),
        m_category(category),
        m_name(name),
        m_producer(producer),
        m_price(price),
        m_deliveryFlag(deliveryFlag),
        m_dimensions(dimensions),
        m_material(material),
        m_style(style),
        m_inStockCount(inStockCount),
        m_warranty(warranty)
{
    alignment->setRowPad(1, getCategory().length())
             ->setRowPad(2, name.length())
             ->setRowPad(3, producer->getName().length())
             ->setRowPad(9, getMaterial().length())
             ->setRowPad(10, getStyle().length());
}

ostream& operator<<(ostream &out, FurnitureProduct *p){
    out << Borders::LEFT << boolalpha << fixed;
    out << setw(p->alignment->getRowPad(0)) << p->m_id;
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(1)) << p->getCategory();
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(2)) << p->m_name;
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(3)) << p->getProducerLink()->getName();
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(4)) << setprecision(2) << p->m_price;
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(5)) << p->m_deliveryFlag;
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(6)) << setprecision(1) << p->getWidth();
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(7)) << p->getDepth();
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(8)) << p->getHeight();
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(9)) << p->getMaterial();
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(10)) << p->getStyle();
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(11)) << p->m_inStockCount;
    out << Borders::CENTER;
    out << setw(p->alignment->getRowPad(12)) << p->m_warranty;
    out << Borders::RIGHT;
    return out;
}

string FurnitureProduct::getCategory(bool pluralFlag) const{
    switch(m_category){
        case FurnitureCategories::SHELVES: return pluralFlag ? "Полиці" : "Полиця";
        case FurnitureCategories::TABLES: return pluralFlag ? "Столи" : "Стіл";
        case FurnitureCategories::WARDROBES: return pluralFlag ? "Шафи" : "Шафа";
        case FurnitureCategories::CURBSTONES: return pluralFlag ? "Тумби" : "Тумба";
        case FurnitureCategories::RACKS: return pluralFlag ? "Стелажі" : "Стелаж";
    }
    return "";
}

string FurnitureProduct::getMaterial() const{
    switch(m_material){
        case FurnitureMaterials::LDSP: return "ЛДСП";
        case FurnitureMaterials::DSP: return "ДСП";
        case FurnitureMaterials::MDF: return "МДФ";
        case FurnitureMaterials::NATURAL_WOOD: return "Натуральне дерево";
        case FurnitureMaterials::OAK: return "Дуб";
        case FurnitureMaterials::BEECH: return "Бук";
        case FurnitureMaterials::PINE: return "Сосна";
        case FurnitureMaterials::APPLE: return "Яблуня";
        case FurnitureMaterials::NUT: return "Горіх";
        case FurnitureMaterials::WHILE_ACACIA: return "Біла акація";
        case FurnitureMaterials::ALDER: return "Вільха";
        case FurnitureMaterials::ASH: return "Ясен";
        case FurnitureMaterials::LARCH: return "Модрина";
    }
    return "";
}

string FurnitureProduct::getStyle() const{
    switch(m_style){
        case FurnitureStyles::MINIMALISM: return "Мінімалізм";
        case FurnitureStyles::MODERN: return "Модерн";
        case FurnitureStyles::HIGH_TECH: return "Хай-тек";
        case FurnitureStyles::AVANGARD: return "Авангард";
        case FurnitureStyles::LOFT: return "Лофт";
        case FurnitureStyles::CLASSIC: return "Класика";
        case FurnitureStyles::PROVENCE: return "Прованс";
    }
    return "";
}

//PERSON//////////////////////////////////////////////////////////////////////////////////////////
Person::Person(string &fullName, char sex, string &dateOfBirth, string &adress, string &phoneNumber):
    m_fullName(fullName), m_sex(sex), m_dateOfBirth(dateOfBirth), m_adress(adress), m_phone(phoneNumber)
{

}

//CLIENT//////////////////////////////////////////////////////////////////////////////////////////
int FurnitureClient::_instanceCounter = 1;
Alignment *const FurnitureClient::alignment = new Alignment(Tables::CLIENT, {
    "№  ",
    "ПІБ",
    "Стать",
    "Дата народження",
    "Адреса",
    "Телефон     "
});

FurnitureClient::FurnitureClient(string &fullName, char sex, string &dateOfBirth, string &adress, string &phoneNumber):
    Person(fullName, sex, dateOfBirth, adress, phoneNumber),
    m_id(_instanceCounter++)
{
    alignment->setRowPad(1, fullName.length())
             ->setRowPad(4, adress.length());
}

ostream& operator<<(ostream &out, FurnitureClient *c){
    out << Borders::LEFT;
    out << setw(c->alignment->getRowPad(0)) << c->m_id;
    out << Borders::CENTER;
    out << setw(c->alignment->getRowPad(1)) << c->m_fullName;
    out << Borders::CENTER;
    out << setw(c->alignment->getRowPad(2)) << c->m_sex;
    out << Borders::CENTER;
    out << setw(c->alignment->getRowPad(3)) << c->m_dateOfBirth;
    out << Borders::CENTER;
    out << setw(c->alignment->getRowPad(4)) << c->m_adress;
    out << Borders::CENTER;
    out << setw(c->alignment->getRowPad(5)) << c->m_phone;
    out << Borders::RIGHT;
    return out;
}

//EMPLOYEE/////////////////////////////////////////////////////////////////////////////////////////
int FurnitureEmployee::_instanceCounter = 1;
Alignment *const FurnitureEmployee::alignment = new Alignment(Tables::EMPLOYEE, {
    "№  ",
    "Посада",
    "ПІБ",
    "Структурна одиниця",
    "Стать",
    "Дата народження",
    "Телефон",
    "У відпустці/відрядженні"
});

FurnitureEmployee::FurnitureEmployee(
        FurnitureWorkPosition *workPosition,
        string &fullName,
        FurnitureStructuralUnit *structuralUnit,
        char sex,
        string &dateOfBirth,
        string &adress,
        string &phoneNumber,
        bool restFlag
    ):
        Person(fullName, sex, dateOfBirth, adress, phoneNumber),
        m_id(_instanceCounter++),
        m_workPosition(workPosition),
        m_structuralUnit(structuralUnit),
        m_restFlag(restFlag)
{
    alignment->setRowPad(1, getWorkPosition().length())
             ->setRowPad(2, fullName.length())
             ->setRowPad(6, phoneNumber.length());
}
ostream& operator<<(ostream &out, FurnitureEmployee *e){
    out << Borders::LEFT << boolalpha;
    out << setw(e->alignment->getRowPad(0)) << e->m_id;
    out << Borders::CENTER;
    out << setw(e->alignment->getRowPad(1)) << e->getWorkPosition();
    out << Borders::CENTER;
    out << setw(e->alignment->getRowPad(2)) << e->m_fullName;
    out << Borders::CENTER;
    out << setw(e->alignment->getRowPad(3)) << e->getStructuralUnit();
    out << Borders::CENTER;
    out << setw(e->alignment->getRowPad(4)) << e->m_sex;
    out << Borders::CENTER;
    out << setw(e->alignment->getRowPad(5)) << e->m_dateOfBirth;
    out << Borders::CENTER;
    out << setw(e->alignment->getRowPad(6)) << e->m_phone;
    out << Borders::CENTER;
    out << setw(e->alignment->getRowPad(7)) << e->m_restFlag;
    out << Borders::RIGHT;
    return out;
}

//DELIVERY/////////////////////////////////////////////////////////////////////////////////////////
int FurnitureDelivery::_instanceCounter = 1;
Alignment *const FurnitureDelivery::alignment = new Alignment(Tables::DELIVERY, {
    "№  ",
    "Кур'єр",
    "Адреса доставки",
    "Статус"
});

FurnitureDelivery::FurnitureDelivery(string &courier, string &adress, FurnitureDeliveryStatuses status):
    m_id(_instanceCounter++), m_courier(courier), m_adress(adress), m_status(status)
{
    alignment->setRowPad(1, courier.length())
             ->setRowPad(2, adress.length())
             ->setRowPad(3, getStatus().length());
}

string FurnitureDelivery::getStatus() const{
    switch(m_status){
        case FurnitureDeliveryStatuses::DELIVERING: return "Доставляється";
        case FurnitureDeliveryStatuses::COMPLETED: return "Виконано";
        case FurnitureDeliveryStatuses::CANCELED: return "Скасовано";
    }
    return "";
}

ostream& operator<<(ostream &out, FurnitureDelivery *d){
    out << Borders::LEFT;
    out << setw(d->alignment->getRowPad(0)) << d->m_id;
    out << Borders::CENTER;
    out << setw(d->alignment->getRowPad(1)) << d->m_courier;
    out << Borders::CENTER;
    out << setw(d->alignment->getRowPad(2)) << d->m_adress;
    out << Borders::CENTER;
    out << setw(d->alignment->getRowPad(3)) << d->getStatus();
    out << Borders::RIGHT;
    return out;
}

//ORDER////////////////////////////////////////////////////////////////////////////////////////////
int FurnitureOrder::_instanceCounter = 1;
Alignment *const FurnitureOrder::alignment = new Alignment(Tables::ORDER, {
    "№  ",
    "Товар",
    "Замовлено товару (шт)",
    "Клієнт",
    "Код доставки",
    "Дата замовлення",
    "Статус"
});

FurnitureOrder::FurnitureOrder(FurnitureProduct *product, int count, FurnitureClient *client, FurnitureDelivery *delivery, string &date, FurnitureOrderStatuses status):
    m_id(_instanceCounter++), m_product(product), m_count(count), m_client(client), m_delivery(delivery), m_date(date), m_status(status)
{
    alignment->setRowPad(1, getProductLink()->getName().length())
             ->setRowPad(3, getClient().length())
             ->setRowPad(6, 27);
}

ostream& operator<<(ostream &out, FurnitureOrderStatuses s){
    switch(s){
        case FurnitureOrderStatuses::DATA_CONFIRMED: out << "Дані підтверджено"; break;
        case FurnitureOrderStatuses::TRANSFERRED_TO_DELIVERY_SERVICE: out << "Передано до служби доставки"; break;
        case FurnitureOrderStatuses::IN_PROCESS: out << "Доставляється"; break;
        case FurnitureOrderStatuses::COMPLETED: out << "Виконано"; break;
        case FurnitureOrderStatuses::CANCELED: out << "Скасовано"; break;
    }
    return out;
}
ostream& operator<<(ostream &out, FurnitureOrder *o){
    out << Borders::LEFT;
    out << setw(o->alignment->getRowPad(0)) << o->m_id;
    out << Borders::CENTER;
    out << setw(o->alignment->getRowPad(1)) << o->getProductLink()->getName();
    out << Borders::CENTER;
    out << setw(o->alignment->getRowPad(2)) << o->m_count;
    out << Borders::CENTER;
    out << setw(o->alignment->getRowPad(3)) << o->getClient();
    out << Borders::CENTER;
    out << setw(o->alignment->getRowPad(4));
    if(!o->getDeliveryCode()) out << "(немає)";
    else out << o->getDeliveryCode();
    out << Borders::CENTER;
    out << setw(o->alignment->getRowPad(5)) << o->m_date;
    out << Borders::CENTER;
    out << setw(o->alignment->getRowPad(6)) << o->getStatus();
    out << Borders::RIGHT;
    return out;
}
