/*!
 *  \file       test_member_pointers.c++
 *  \brief      
 *  
 */


#include <gtest/gtest.h>
#include <cmath>

#include "member_function_pointers.hpp"

TEST(UTest4MemberPointers, CheckHowToAccessMemberFunctionPointers)
{
    Interpreter interpreter;

    interpreter.call_member("launch", "start");
    interpreter.call_member("quit", "quit");
    interpreter.call_member("suspend", "suspend");
    interpreter.call_member("resume", "resume");

    interpreter.call_member("quit", "start");
}

TEST(UTest4MemberPointers, CheckDataMemberPointers)
{
    class Body
    {
    public:
        const char* val;
        int data;
    public:
        Body(const char* v) : val{v} {}

        void print(int x)
        {
            std::cout << val << " --- " << x << std::endl;
        }
        int access(int);
        void visit();
    };

    using Pmfi = void (Body::*)(int);       // pointer to member function of class Body
    using Pm = const char* Body::*;         // pointer to data member of class Body

    auto fn = [](Body& obj1, Body& obj2)
    {
        Body* pobj = &obj2;
        Pmfi pfn = &Body::print;
        Pm pmember = &Body::val;

        obj1.print(1);
        (obj1.*pfn)(2);

        obj1.*pmember = "nv1";
        pobj->*pmember = "nv2";

        obj2.print(3);
        (pobj->*pfn)(4);

        // pfn = &Body::access;        // error: return type mismatch
        // pfn = &Body::visit;         // error: argument type mismatch
        // pmember = &Body::data;      // error: pmember's type is const char*, but the Body::data is int, so type mismatch
        // pmember = pfn;              // error: pmember is data member pointer, but pfn is member function pointer, type mismatch
    };

    Body vessel("vessel");
    Body vehicle("vehicle");
    fn(vessel, vehicle);
}

TEST(UTest4MemberPointers, AssignBaseMemberPointerToDerivedMemberPointer)
{
    /*!
     *  \def        逆变性 (contravariance)
     *  \details    一个派生类至少包含从基类那里继承而来的成员，通常还包含其他成员。这意味着我们可以安全地将一个基类成员指针赋给
     *              一个派生类成员指针，但反方向赋值则不行。 
     *              这一特性被称为逆变性 contravariance
     * 
     *  \note       这一逆变规则看起来与另一规则正好相反，即我们可以将一个派生类指针赋给基类的指针。
     */
    class Text : public StdInterface
    {
    public:
        Text() : numbers(10)
        {
            for (auto index = 0U; index < numbers.size(); ++index)
            {
                numbers[index] = std::pow(index + 1, 2);
            }
        }
        virtual ~Text() {}
    public:
        void start() override { std::cout << "execute Text::start action" << std::endl; }
        void suspend() override { std::cout << "execute Text::suspend action" << std::endl; }

        virtual void print()
        {
            for (auto number : numbers)
            {
                std::cout << number << "  ";
            }
            std::cout << "\n" << std::endl;
        }
    private:
        std::vector<int> numbers;
    private:
        void resume() override {}
        void quit() override {}
        void full_size() override {}
        void small() override {}
    };

    // void (StdInterface::* pmember_fn)() = &Text::print;
    void (Text::* pstart)() = &StdInterface::start;

    Text* ptext = new Text();
    ptext->print();
    (ptext->*pstart)();

    delete ptext;
}