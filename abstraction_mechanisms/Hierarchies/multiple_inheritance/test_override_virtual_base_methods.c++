/*!
 *  \file       test_override_virtual_base_methods.c++
 *  \brief      
 *  
 */


#include <boost/test/unit_test.hpp>
#include <memory>

#define interface struct

BOOST_AUTO_TEST_SUITE(OverrideVirtualBaseMethods)

    class Color
    {
    public:
    };
    
    interface IWindow
    {
        virtual void set_color(Color) = 0;
        virtual void prompt() = 0;
        
        virtual ~IWindow() = default;
    };
    
    class IWindow_With_Border : public virtual IWindow
    {
    public:
        void set_color(Color) override;
    };
    
    class IWindow_With_Menu : public virtual IWindow
    {
    public:
        void prompt() override;
    };
    
    class My_Window : public IWindow_With_Border, public IWindow_With_Menu
    {
    public:
        void prompt() override;
    };
    
    void IWindow_With_Border::set_color(Color)
    {
        std::cout << "Override IWindow_With_Border::set_color(Color)" << std::endl;
    }
    
    void IWindow_With_Menu::prompt()
    {
        std::cout << "Override IWindow_With_Menu::prompt()" << std::endl;
    }
    
    void My_Window::prompt()
    {
        std::cout << "Override My_Window::prompt()" << std::endl;
    }
    
    BOOST_AUTO_TEST_CASE(CheckHowToOverrideVirtualBaseMethods)
    {
        IWindow* pwind = new My_Window();
        IWindow_With_Border* pborder = dynamic_cast<IWindow_With_Border*>(pwind);
        pborder->set_color(Color());
        pwind->prompt();
        
        IWindow_With_Menu* pmenu = dynamic_cast<IWindow_With_Menu*>(pwind);
        pmenu->prompt();
        
        delete pwind;
    }

BOOST_AUTO_TEST_SUITE_END()