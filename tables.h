#ifndef TABLES_H_INCLUDED
#define TABLES_H_INCLUDED

#include "tablestyle.h"
#include <ctime>

enum class FurnitureCategories{
    TABLES,
    SHELVES,
    WARDROBES,
    CURBSTONES,
    RACKS
};
enum class FurnitureMaterials{
    LDSP,
    DSP,
    MDF,
    NATURAL_WOOD,
    OAK,
    BEECH,//бук
    PINE,//сосна
    APPLE,
    NUT,
    WHILE_ACACIA,
    ALDER,//вільха
    ASH,//ясен
    LARCH//модрина
};
enum class FurnitureStyles{
    MINIMALISM,
    MODERN,
    HIGH_TECH,
    AVANGARD,
    LOFT,
    CLASSIC,
    PROVENCE
};
enum class FurnitureDeliveryStatuses{
    DELIVERING,
    COMPLETED,
    CANCELED
};
enum class FurnitureOrderStatuses{
    DATA_CONFIRMED,
    TRANSFERRED_TO_DELIVERY_SERVICE,
    IN_PROCESS,
    COMPLETED,
    CANCELED
};
enum class FurnitureAddressees{
    OFFICE,
    DEPARTMENT,
    SHOP,
    CLIENT
};
struct FurnitureDimensions{
    float width;
    float depth;
    float height;
};

class FurnitureWorkPosition{
    private:
        static int _instanceCounter;
        const int m_id;
        string m_name;
        float m_salary;
    public:
        static Alignment *const alignment; //we cannot reassign this ptr

        FurnitureWorkPosition(string &name, float salary);
        ~FurnitureWorkPosition(){ delete alignment; }
        friend ostream& operator<<(ostream &out, FurnitureWorkPosition *wp);

        const int getId() const{ return m_id; }
        string getName() const{ return m_name; }
        int getSalary() const{ return m_salary; }
};

class FurnitureStructuralUnit{
    private:
        static int _instanceCounter;
        const int m_id;
        string m_name;
        string m_adress;
        FurnitureAddressees m_addressee;
    public:
        static Alignment *const alignment;

        FurnitureStructuralUnit(string &name, string &adress, FurnitureAddressees addressee);
        ~FurnitureStructuralUnit(){ delete alignment; }
        friend ostream& operator<<(ostream &out, FurnitureStructuralUnit *su);

        const int getId() const{ return m_id; }
        string getName(){ return m_name; }
        string getAdress(){ return m_adress; }
        string getAddressee();
};

class FurnitureProducer{
    private:
        static int _instanceCounter;
        const int m_id;
        string m_name;
        string m_adress;
        string m_phone;
        string m_rate;
    public:
        static Alignment *const alignment;

        FurnitureProducer(string &name, string &adress, string &phone, string &rate);
        ~FurnitureProducer(){ delete alignment; }
        friend ostream& operator<<(ostream &out, FurnitureProducer *p);

        const int getId() const{ return m_id; }
        string getName() const{ return m_name; }
        string getAdress() const{ return m_adress; }
        string getPhone() const{ return m_phone; }
        string getRate() const{ return m_rate; }
};

class FurnitureProduct{
    private:
        static int _instanceCounter;
        const int m_id;
        FurnitureCategories m_category;
        string m_name;
        FurnitureProducer *m_producer = nullptr;
        int m_price;
        bool m_deliveryFlag;
        FurnitureDimensions m_dimensions;
        FurnitureMaterials m_material;
        FurnitureStyles m_style;
        int m_inStockCount;
        float m_warranty;
    public:
        static Alignment *const alignment;

        FurnitureProduct(
            FurnitureCategories category,
            string &name,
            FurnitureProducer *producer,
            int price,
            bool deliveryFlag,
            const FurnitureDimensions &dimensions,
            FurnitureMaterials material,
            FurnitureStyles style,
            int intStockCount,
            float warranty
        );
        ~FurnitureProduct(){
            delete m_producer;
            delete alignment;
        }
        friend ostream& operator<<(ostream &out, FurnitureProduct *p);

        const int getId() const{ return m_id; }
        string getName() const{ return m_name; }
        string getCategory(bool pluralFlag = true) const;
        FurnitureCategories getCategoryLink() const{ return m_category; }
        FurnitureProducer* getProducerLink() const{ return m_producer; }
        int getPrice() const{ return m_price; }
        float getWidth() const{ return m_dimensions.width; }
        float getDepth() const{ return m_dimensions.depth; }
        float getHeight() const{ return m_dimensions.height; }
        bool getDeliveryFlag() const{ return m_deliveryFlag; }
        string getMaterial() const;
        string getStyle() const;
        int getInStockCount() const{ return m_inStockCount; }
        float getWarranty() const{ return m_warranty; }
};

class Person{
    protected:
        string m_fullName;
        char m_sex;
        string m_dateOfBirth;
        string m_adress;
        string m_phone;
        //it is not allowed to call Person constructor directly
        Person(string &fullName, const char sex, string &dateOfBirth, string &adress, string &phoneNumber);
    public:
        string getFullName() const{ return m_fullName; }
        char getSex() const{ return m_sex; }
        string getDateOfBirth() const{ return m_dateOfBirth; }
        string getAdress() const{ return m_adress; }
        string getPhone() const{ return m_phone; }
};

class FurnitureClient: public Person{
    private:
        static int _instanceCounter;
        const int m_id;
        const FurnitureAddressees m_addressee = FurnitureAddressees::CLIENT;
    public:
        static Alignment *const alignment;

        FurnitureClient(string &fullName, char sex, string &dateOfBirth, string &adress, string &phoneNumber);
        ~FurnitureClient(){ delete alignment; }
        friend ostream& operator<<(ostream &out, FurnitureClient *c);

        const int getId() const{ return m_id; }
};

class FurnitureEmployee: public Person{
    private:
        static int _instanceCounter;
        const int m_id;
        FurnitureWorkPosition *m_workPosition = nullptr;
        FurnitureStructuralUnit *m_structuralUnit = nullptr;
        bool m_restFlag;
    public:
        static Alignment *const alignment;

        FurnitureEmployee(
            FurnitureWorkPosition *workPosition,
            string &fullName,
            FurnitureStructuralUnit *structuralUnit,
            char sex,
            string &dateOfBirth,
            string &adress,
            string &phoneNumber,
            bool restFlag
        );
        ~FurnitureEmployee(){
            delete alignment;
            delete m_workPosition;
            delete m_structuralUnit;
        }
        friend ostream& operator<<(ostream &out, FurnitureEmployee *e);

        const int getId() const{ return m_id; }
        FurnitureWorkPosition *getWorkPositionLink() const{ return m_workPosition; }
        string getWorkPosition() const{ return m_workPosition->getName(); }
        string getStructuralUnit() const{ return m_structuralUnit->getName(); }
        bool getRestFlag() const{ return m_restFlag; }
};

class FurnitureDelivery{
    private:
        static int _instanceCounter;
        const int m_id;
        string m_courier;
        string m_adress;
        FurnitureDeliveryStatuses m_status;
    public:
        static Alignment *const alignment;

        FurnitureDelivery(string &courier, string &adress, FurnitureDeliveryStatuses status);
        ~FurnitureDelivery(){}
        friend ostream& operator<<(ostream &out, FurnitureDelivery *d);

        const int getId() const{ return m_id; }
        string getCourier() const{ return m_courier; }
        string getAdress() const{ return m_adress; }
        string getStatus() const;
};

class FurnitureOrder{
    private:
        static int _instanceCounter;
        const int m_id;
        FurnitureProduct *m_product = nullptr;
        int m_count;
        FurnitureClient *m_client = nullptr;
        FurnitureDelivery *m_delivery = nullptr;
        string m_date;
        FurnitureOrderStatuses m_status;
    public:
        static Alignment *const alignment;

        FurnitureOrder(FurnitureProduct *product, int count, FurnitureClient *client, FurnitureDelivery *delivery, string &dateOfBirth, FurnitureOrderStatuses status);
        ~FurnitureOrder(){
            delete alignment;
            delete m_product;
            delete m_client;
            delete m_delivery;
        }
        friend ostream& operator<<(ostream &out, FurnitureOrder *o);
        friend ostream& operator<<(ostream &out, FurnitureOrderStatuses s);

        const int getId() const{ return m_id; }
        FurnitureProduct* getProductLink() const{ return m_product; }
        string getDate() const{ return m_date; }
        int getCount() const{ return m_count; }
        string getClient() const{ return m_client ? m_client->getFullName() : ""; }
        int getDeliveryCode() const{ return m_delivery ? m_delivery->getId() : 0; }
        FurnitureOrderStatuses getStatus() const{ return m_status; };
};

#endif // TABLES_H_INCLUDED
