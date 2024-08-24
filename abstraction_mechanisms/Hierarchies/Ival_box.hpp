/*!
 *  \file       lval_box.hpp
 *  \brief      
 *  
 */


#pragma once

#define IMPLEMENTATION_INHERITANCE      1
#define INTERFACE_INHERITANCE           2
#define INHERITANCE_WAY                 INTERFACE_INHERITANCE

#define Big_Bucks_Inc       1
#define Imperial_Bananas    2
#define Liberated_Software  3
#define Compiler_Whizzes    4
#define ENVIRONMENT         Big_Bucks_Inc

#if (ENVIRONMENT == Big_Bucks_Inc)
    class BBwidget
    {
    public:
        virtual void draw() = 0;
    };
#elif (ENVIRONMENT == Imperial_Bananas)
    class IBwidget
    {
    };
#elif (ENVIRONMENT == Liberated_Software)
    class LSwindow
    {
    };
#elif (ENVIRONMENT == Compiler_Whizzes)
    class CWwidget
    {
    };
#endif

#if (INHERITANCE_WAY == IMPLEMENTATION_INHERITANCE)
    #if (ENVIRONMENT == Big_Bucks_Inc)
        class Ival_box : public BBwidget
    #elif (ENVIRONMENT == Imperial_Bananas)
        class Ival_box : public IBwidget
    #elif (ENVIRONMENT == Liberated_Software)
        class Ival_box : public LSwindow
    #elif (ENVIRONMENT == Compiler_Whizzes)
        class Ival_box : public CWwidget
    #endif
        {
        public:
            Ival_box(int low, int high);
            virtual ~Ival_box();
            
        protected:
            int m_val;
            int m_low;
            int m_high;
            bool changed{false};
            
        public:
            virtual int get_value();
            virtual void set_value(int val);
            virtual void reset_value(int val);
            virtual void prompt();
            virtual bool was_changed() const;
        };

    void interact(Ival_box* pb);
#elif (INHERITANCE_WAY == INTERFACE_INHERITANCE)
    class Ival_box
    {
    public:
        virtual ~Ival_box() = default;
    public:
        virtual int get_value() = 0;
        virtual void set_value(int val) = 0;
        virtual void reset_value(int val) = 0;
        virtual void prompt() = 0;
        virtual bool was_changed() const = 0;
    };
#endif