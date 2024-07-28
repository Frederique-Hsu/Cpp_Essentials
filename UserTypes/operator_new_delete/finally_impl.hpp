/*!
 *  \file       fianlly_impl.hpp
 *  \brief
 *
 */


/*!
 *  \section    Definitions
 */
template<typename FnType> struct FinalAction
{
    FinalAction(FnType fn);
    ~FinalAction();

    FnType clean;
};

/*================================================================================================*/

/*!
 *  \section    Implementations
 */

template<typename FnType>
FinalAction<FnType>::FinalAction(FnType fn) : clean(fn)
{
}

template<typename FnType>
FinalAction<FnType>::~FinalAction()
{
    clean();
}

template<class FnType>
FinalAction<FnType> finally(FnType fn)
{
    return FinalAction<FnType>(fn);
}
