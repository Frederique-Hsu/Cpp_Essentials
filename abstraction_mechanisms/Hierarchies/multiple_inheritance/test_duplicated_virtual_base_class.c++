/*!
 *  \file       test_duplicated_virtual_base_class.c++
 *  \brief      
 *  
 */


#include <boost/test/unit_test.hpp>

class Ival_slider
{
public:
    virtual ~Ival_slider() = default;
public:
    virtual int get_value() const = 0;
    virtual void set_value(int val) = 0;
    virtual bool was_changed() const = 0;
};

class BBslider
{
public:
    BBslider(const std::string& str);
    virtual ~BBslider() = default;
private:
    std::string slider;
public:
    virtual std::string show_slider_progress();
};

BBslider::BBslider(const std::string& str) : slider{str} {}

std::string BBslider::show_slider_progress()
{
    return slider;
}

BOOST_AUTO_TEST_SUITE(Virtual_Bases_Multiple_Inheritance)
    
    class BB_ival_slider : public virtual Ival_slider, protected BBslider
    {
    public:
        BB_ival_slider(const std::string& str) : BBslider(str) {}
        virtual ~BB_ival_slider() = default;
    };
    
    class Popup_ival_slider : public virtual Ival_slider
    {
    public:
        Popup_ival_slider() {}
        virtual ~Popup_ival_slider() {}
    protected:
        bool was_changed() const override { return false; }
    };
    
    class BB_popup_ival_slider : public virtual Popup_ival_slider, protected BB_ival_slider
    {
    public:
        BB_popup_ival_slider(const std::string& args) : Popup_ival_slider(), BB_ival_slider(args) {}
        ~BB_popup_ival_slider() = default;
    public:
        int get_value() const override { return int{}; }
        void set_value(int val) override {}
        bool was_changed() const override { return true; }
        
        std::string show_slider_progress() override
        {
            return BBslider::show_slider_progress();
        }
    };

    bool access(Ival_slider* ptr)
    {
        return ptr->was_changed();
    }
    
    bool call(BB_popup_ival_slider* ptr)
    {
        /*!
         *  \remark     During the scenario of virtual base multiple inheritance, 
         *              BB_popup_ival_slider can be converted to Ival_slider
         */
        return access(ptr);
    }
    
    Popup_ival_slider* popup_slider_factory(const std::string& args)
    {
        return new BB_popup_ival_slider(args);
    }
    
    BOOST_AUTO_TEST_CASE(CheckHowVirtualBasesToSolveAmbiguousnessIssue)
    {
        Popup_ival_slider* popup = popup_slider_factory("This is actual a BB popup");
        
        bool result = access(popup);
        BOOST_CHECK_EQUAL(result, true);
        
        auto bb_popup = std::make_shared<BB_popup_ival_slider>("Yes, also create an BB popup");
        BOOST_CHECK_EQUAL(bb_popup->was_changed(), true);
        
        BOOST_CHECK(bb_popup->show_slider_progress() == "Yes, also create an BB popup");
        BOOST_CHECK(dynamic_cast<BB_popup_ival_slider*>(popup)->show_slider_progress() == "This is actual a BB popup");
                
        delete popup;
    }
BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE(Replicatede_Bases_Multiple_Inheritance)

    class BB_ival_slider : public Ival_slider, protected BBslider
    {
    public:
        BB_ival_slider(const std::string& str) : BBslider(str) {}
        virtual ~BB_ival_slider() = default;
    };
    
    class Popup_ival_slider : public Ival_slider
    {
    public:
        Popup_ival_slider() {}
        virtual ~Popup_ival_slider() = default;
    public:
        bool was_changed() const override { return false; }
    protected:
        int get_value() const override { return -1; }
        void set_value(int val) override {};
    };
    
    class BB_popup_ival_slider : public Popup_ival_slider, protected BB_ival_slider
    {
    public:
        BB_popup_ival_slider(const std::string& args) : BB_ival_slider(args) {}
        ~BB_popup_ival_slider() {}
    public:
        int get_value() const override { return int{}; }
        void set_value(int val) override {}
        bool was_changed() const override { return true; }
        
        std::string show_slider_progress() override
        {
            return BBslider::show_slider_progress();
        }
    };

    bool access(Ival_slider* ptr)
    {
        return ptr->was_changed();
    }
    
    void call(BB_popup_ival_slider* ptr)
    {
        /*!
         *  \remark     But in the scenario of replicated base multiple inheritance,
         *              BB_popup_ival_slider cannot be converted implicitly to Ival_slider
         */
        // access(ptr);
    }
    
    Popup_ival_slider* popup_slider_factory(const std::string& args)
    {
        return new BB_popup_ival_slider(args);
    }
    
    BOOST_AUTO_TEST_CASE(CheckHowReplicatedBasesToSolveAmbiguousnessIssue)
    {
        BB_popup_ival_slider* bb_popup = new BB_popup_ival_slider("This is BB popup");        
        Popup_ival_slider* popup = popup_slider_factory("Another BB popup");
        
        BOOST_CHECK(bb_popup->show_slider_progress() == "This is BB popup");
        BOOST_CHECK(dynamic_cast<BB_popup_ival_slider*>(popup)->show_slider_progress() == "Another BB popup");
        
        BOOST_CHECK_EQUAL(bb_popup->was_changed(), true);
        BOOST_CHECK_EQUAL(popup->was_changed(), true);
        
        Ival_slider* slider = new Popup_ival_slider();
        BOOST_CHECK(slider->was_changed() == false);
        
        delete bb_popup;
        delete popup;
        delete slider;
    }
BOOST_AUTO_TEST_SUITE_END()