/*!
 *  \file       test_base_hierarchy.c++
 *  \brief      
 *  
 */


#include "base_hierarchy.hxx"
#include "../../utils/finalize.hpp"
#include "../../utils/finalize.cpp"

#include <boost/test/unit_test.hpp>
#include <memory>

BOOST_AUTO_TEST_SUITE(UTest4BaseClassHierarchy)

    BOOST_AUTO_TEST_CASE(CheckHowVirtualBaseClassWorks)
    {
        // Storable* pradio = new Radio("current_file");
        // Transmitter* pradio = new Radio("current_file");
        Receiver* pradio = new Radio("current_file");
        
        std::string filename = pradio->get_file();
        std::cout << "file name is " << filename << std::endl;
        
        BOOST_CHECK(filename == "current_file");
        
        delete pradio;
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(ConstructVirtualBaseClass)

    struct V
    {
        V(int i);
    private:
        int num;
    public:
        int get_num() const;
    };

    struct A
    {
        A();
    };

    struct B : virtual V, virtual A
    {
        B();
    };

    V::V(int i) : num{i} {}
    
    int V::get_num() const
    {
        return num;
    }

    A::A() {}

    B::B() : V(int{}), A() {}

    class C : virtual V
    {
    public:
        C(int i);
    };

    C::C(int i) : V(i) {}

    class D : virtual public B, virtual public C
    {
    public:
        D();
        D(int i);
        D(int i, int j);
    };
    
    // D::D() {}   // error: 虚基类C和V没有默认构造函数
    D::D(int i) : C(i), V(0), B() {}
    D::D(int i, int j) : V(i), C(j) {}  // OK
    
    BOOST_AUTO_TEST_CASE(CheckHowToInitializeVirtualBaseConstructor)
    {
        D dobj(1, 2);
        
        BOOST_CHECK_EQUAL(dobj.get_num(), 1);
        
        D single_arg_obj(15);
        BOOST_CHECK_EQUAL(single_arg_obj.get_num(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(InvokeVirtualBaseClassMember)

    class Window
    {
    public:
        virtual ~Window();
    public:
        virtual void draw();
    };
    
    class Window_With_Border : public virtual Window
    {
    public:
        virtual ~Window_With_Border();
    protected:
        void own_draw();    // draw the border
    public:
        void draw() override;
    };
    
    class Window_With_Menu : public virtual Window
    {
    public:
        virtual ~Window_With_Menu();
    protected:
        void own_draw();    // draw the menu
    public:
        void draw() override;
    };
    
    class Clock : public Window_With_Border, public Window_With_Menu
    {
    public:
        ~Clock();
    protected:
        void own_draw();    // display the dial and pointer
    public:
        void draw() override;
    };
    
    Window::~Window()
    {
    #ifdef DEBUG_WITH_LOG
        std::cout << "destruct the virtual base class Window" << std::endl;
    #endif
    }
    
    Window_With_Border::~Window_With_Border()
    {
    #ifdef DEBUG_WITH_LOG
        std::cout << "destruct the middle layer base class Window_With_Border" << std::endl;
    #endif
    }
    
    Window_With_Menu::~Window_With_Menu()
    {
    #ifdef DEBUG_WITH_LOG
        std::cout << "destruct the middle layer base class Window_With_Menu" << std::endl;
    #endif
    }
    
    void Window::draw()
    {
        std::cout << "Draw the window" << std::endl;
    }
    
    void Window_With_Border::draw()
    {
        Window::draw();
        own_draw();     // display the border
    }
    
    void Window_With_Border::own_draw()
    {
        std::cout << "Draw the border for window" << std::endl;
    }
    
    void Window_With_Menu::draw()
    {
        Window::draw();
        own_draw();     // draw the menu
    }
    
    void Window_With_Menu::own_draw()
    {
        std::cout << "Draw the menu for window" << std::endl;
    }
    
    void Clock::draw()
    {
        Window::draw();
        Window_With_Border::own_draw();
        Window_With_Menu::own_draw();
        own_draw();
    }
    
    void Clock::own_draw()
    {
        std::cout << "Draw the dial and pointer for a clock" << std::endl;
    }
    
    Clock::~Clock()
    {
    #ifdef DEBUG_WITH_LOG
        std::cout << "destruct the final concrete class Clock" << std::endl;
    #endif
    }
    
    BOOST_AUTO_TEST_CASE(CheckHowToInvokeVirtualBaseClassMethod)
    {
        Clock clock;
        clock.draw();
        std::cout << "\n========================================================" << std::endl;
        
        Window* pclock = new Clock();
        Window_With_Border* pborder = new Window_With_Border();
        Window* pmenu = new Window_With_Menu();
        auto pwin = std::unique_ptr<Window>(new Window());
        
        
        auto deleter = finalize([&]() {
            delete pborder;
            std::cout << std::endl;
            
            delete pclock;
            std::cout << std::endl;
            
            delete pmenu;
            std::cout << std::endl;
        });
        
        std::vector<Window*> ctrls{pclock, pborder, pmenu};
        for (auto ctrl : ctrls)
        {
            ctrl->draw();
            std::cout << "\n" << std::endl;
        }
        
        pwin->draw();
        std::cout << "========================================================\n" << std::endl;
    }
    
BOOST_AUTO_TEST_SUITE_END()