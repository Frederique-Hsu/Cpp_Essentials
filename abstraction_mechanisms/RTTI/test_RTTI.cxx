/*!
 *  \file       test_RTTI.cxx
 *  \brief      
 *  
 */


#include <CppUTest/TestHarness.h>

#include <queue>

TEST_GROUP(UTest4_MisuseRTTI)
{
    class Object
    {
    public:
        virtual ~Object() = default;
    };
    
    class Container : public Object
    {
    public:
        Container() : Object(), m_objects() {}
        ~Container() = default;
    public:
        void put(Object* pobj)
        {
            m_objects.push(pobj);
        }
        Object* get()
        {
            Object* pobj = m_objects.front();
            m_objects.pop();
            return pobj;
        }
    private:
        std::queue<Object*> m_objects;
    };
    
    class Ship : public Object
    {
    public:
        Ship() : Object() {}
        ~Ship() = default;
    };
    
    Ship* fn(Ship* ptr_ship, Container* ptr_container)
    {
        ptr_container->put(ptr_ship);
        Object* ptr_obj = ptr_container->get();
        if (Ship* pship = dynamic_cast<Ship*>(ptr_obj))
        {
            return pship;
        }
        else
        {
            throw std::bad_cast();
        }
    }
    
    Ship* gc(Ship* ptr_ship, std::vector<Ship*>& container)
    {
        container.push_back(ptr_ship);
        
        Ship* pship = container.front();
        container.pop_back();
        return pship;
    }
};

TEST(UTest4_MisuseRTTI, CheckMisuseOfRTTI)
{
    Ship raw_ship;
    Container container;
    
    Ship* pship = fn(&raw_ship, &container);
    
    CHECK_EQUAL(static_cast<void*>(&raw_ship), static_cast<void*>(pship));
    
    std::vector<Ship*> ship_container;
    Ship* retrieved_ship = gc(&raw_ship, ship_container);
    CHECK(&raw_ship == retrieved_ship);
}