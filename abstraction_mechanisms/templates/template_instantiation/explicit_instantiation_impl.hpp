/*!
 *  \file       explicit_instantiation_impl.hpp
 *  \brief      
 *  
 */



/*!
 *  \section    template specialization
 */
template<> int convert<int>(double value)    // SourceType可以从参数value出推断出来
{
    return static_cast<int>(value);
}