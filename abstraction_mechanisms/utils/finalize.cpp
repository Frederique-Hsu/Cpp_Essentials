/*!
 *  \file       finalize.cpp
 *  \brief      
 *  
 */


#include "finalize.hpp"

#ifdef DEBUG_WITH_LOG
    #include <iostream>
#endif

template<typename FnType>
class FinalAction
{
public:
    FinalAction(FnType fn_obj);
    ~FinalAction();

private:
    FnType clean;
};


template<typename FnType>
FinalAction<FnType>::FinalAction(FnType fn_obj) : clean{fn_obj}
{
#ifdef DEBUG_WITH_LOG
    std::clog << "Called FinalAction<FnType>::FinalAction(FnType fn_obj) constructor" << std::endl;
#endif
}

template<typename FnType>
FinalAction<FnType>::~FinalAction()
{
    clean();
#ifdef DEBUG_WITH_LOG
    std::clog << "Called FinalAction<FnType>::~FinalAction() destructor" << std::endl;
#endif
}

template<typename FnType>
FinalAction<FnType> finalize(FnType fn)
{
#ifdef DEBUG_WITH_LOG
    std::clog << "Called FinalAction<FnType> finalize(FnType fn) function template" << std::endl;
#endif
    return FinalAction<FnType>(fn);
}