/*!
 *  \file       test_dynamic_cast.c++
 *  \brief
 *
 */


#include "test_dynamic_cast.h++"

#include "dynamic_cast.hpp"

#include <iostream>


/*!
 *  \remarks    在运行时使用类型信息通常被称为“运行时类型信息”  RTTI:  Run-Time Type Information
 *
 *  \list
 *      \li     从基类到派生类的转换通常称为向下转换(downcast)
 *              因为我们画继承树的习惯是从基类（作为根）向下画的。
 *
 *      \li     从派生类到基类的转换称为向上转换(upcast)
 *
 *      \li     从基类到兄弟类的转换，例如从BBwindow转换到Ival_box，则称为交叉转换(crosscast)
 *  \endlist
 */
void TEST_GROUP_CppUTestGroupUTest4DynamicCast::cast(BB_ival_slider* pslider)
{
    // upcast : from child class "BB_ival_slider" to parent class "Ival_slider"
    Ival_slider* p_val_slider1 = pslider;
    Ival_slider* p_val_slider2 = dynamic_cast<Ival_slider*>(pslider);

    CHECK(typeid(p_val_slider1) == typeid(p_val_slider2));

    std::cout << "\nThe class name of pslider object is " << typeid(pslider).name() << std::endl;

    // BBslider* p_bb_slider1 = pslider;    // BBslider is a protected base
    // BBslider* p_bb_slider2 = dynamic_cast<BBslider*>(pslider);  // cannot cast "BB_ival_slider" to its protected base "BBslider"
}

TEST(UTest4DynamicCast, CheckHowToConvertUnderClassHierarchy)
{
    BB_ival_slider* pslider = new BB_ival_slider();

    bool is_pointer = typeid(pslider).__is_pointer_p();
    std::cout << "\nthe pslider is a pointer? " << (is_pointer ? "Yes" : "No") << std::endl;
    CHECK(is_pointer == true);

    auto type_name = typeid(decltype(pslider)).name();
    std::cout << "the type name is " << type_name << std::endl;

    cast(pslider);
    delete pslider;
}

class MySlider : public Ival_slider
{
public:
    int get_value() const override
    {
        return 5;
    }
};

class Date
{
public:
    enum class Month : unsigned char
    {
        Jan = 1,    Feb,    Mar,    Apr,    May,    Jun,
        Jul,        Aug,    Sep,    Oct,    Nov,    Dec
    };

    Date(int year, Month month, int day);
    ~Date() = default;
protected:
    int m_year;
    Month m_month;
    int m_day;
public:
    int getYear() const;
    Month getMonth() const;
    int getDay() const;
};

Date::Date(int year, Month month, int day) : m_year{year}, m_month{month}, m_day{day} {}

int Date::getYear() const { return m_year; }
Date::Month Date::getMonth() const { return m_month; }
int Date::getDay() const { return m_day; }

class MyDate : public Date
{
public:
    MyDate(int year, Month month, int day);
public:
    enum class WeekDay
    {
        Mon = 1,    Tue,    Wed,    Thu,    Fri,    Sat,    Sun
    };
    WeekDay whichDay() const;
};

TEST(UTest4DynamicCast, CannotDynamicCastIfBaseHasNoVirtualFunction)
{
    auto failToCast = [](Ival_box* pbox, Date* pdate)
    {
        MySlider* pmyslider = dynamic_cast<MySlider*>(pbox);    // OK: Ival_box有虚函数，可downcast为MySlider
        // MyDate* pmydate = dynamic_cast<MyDate*>(pdate);     // error: Date没有虚函数，无多态性。不能转换

        std::cout << "\ntypeid(pbox).name() = " << typeid(pbox).name() << std::endl;
        std::cout << "typeid(pmyslider).name() = " << typeid(pmyslider).name() << std::endl;
    };

    Ival_box* pbox = new MySlider;
    Date* pdate = new Date(2024, Date::Month::Aug, 27);

    failToCast(pbox, pdate);

    delete pbox;
    delete pdate;
}

TEST(UTest4DynamicCast, CheckDynamicCastTargetTypeIsNotNecessaryPolymorphic)
{
    class IO_obj
    {
    public:
        virtual ~IO_obj() = default;
    public:
        virtual IO_obj* clone() = 0;
    };

    class IO_date : public Date, public IO_obj
    {
    public:
        IO_date() : Date(2024, Date::Month::Aug, 27), IO_obj() {}
        ~IO_date() = default;
    public:
        IO_date* clone() override
        {
            return new IO_date(*this);
        }
    };

    auto cast_to_non_polymorphic_object = [](IO_obj* pio)
    {
        /*! \remark dynamic_cast向目标类型Date转换，不必要求Date是一个多态，有虚函数的类型. */
        Date* pdate = dynamic_cast<Date*>(pio);
        return pdate->getDay();
    };

    auto cast_to_void_pointer = [](IO_obj* pio, Date* pdate)
    {
        /*! \remark dynamic_cast向void*转换，可以用来确定一个多态类型IO_obj对象的起始地址 */
        void* io_void_ptr = dynamic_cast<void*>(pio);
        std::printf("\nThe start address of 'pbox' polymorphic object is %p\n", io_void_ptr);

        // void* date_void_ptr = dynamic_cast<void*>(pdate);   // error: 'Date' class is not polymorphic

        return io_void_ptr;
    };

    IO_obj* pio = new IO_date();
    auto day = cast_to_non_polymorphic_object(pio);
    CHECK_EQUAL(day, 27);

    void* void_ptr = cast_to_void_pointer(pio, nullptr);
    std::printf("The pio address = %p\n", pio);
    std::printf("The void_ptr address = %p\n", void_ptr);
    CHECK(pio == void_ptr);

    delete pio;
}