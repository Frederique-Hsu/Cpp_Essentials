/*!
 *  \file       MyVector.cpp
 *  \brief      
 *  
 */


#include "MyVector.hpp"

#include <gtest/gtest.h>


#define YES     1
#define NO      0
#define PREVENT_EXPLICIT_TEMPLATE_INSTANTIATION_REQUEST     YES

#if (PREVENT_EXPLICIT_TEMPLATE_INSTANTIATION_REQUEST == YES)
    /*!
    *  \attention  显式不实例化请求
    *              外部模板，禁止隐式实例化，在其他某处显式实例化.
    */
    extern template class MyVector<char*>;
#endif


TEST(UTest4MyVector, CheckTheExternTemplateDoesNotInstantiateRequest)
{
    char hello[] = "hello", world[] = "world", that[] = "that", is[] = "is", cpp[] = "C++", programming[] = "programming";
    
    /*!
     *  \note   因为前面已经使用 extern template class<char*> 来阻止编译器为char*具体类型实参的代码生成了。
     *          所以下面的 MyVector<char*> word_vector 对象就不能创建成功了。 
     *          因为编译器找不到 MyVector<char*> 这个类型了。
     * 
     *  \attention  若将前面的 extern template class MyVector<char*> 给注释掉，那么下面的 MyVector<char*> word_vector 就可以创建成功了。
     *              因为编译器可以套用 MyVector.hpp 文件里的那个主模板 template<typename T> class MyVector 来实例化。
     */
#if (PREVENT_EXPLICIT_TEMPLATE_INSTANTIATION_REQUEST == NO)
    MyVector<char*> word_vector{hello, world, that, is, cpp, programming};
    EXPECT_EQ(word_vector.size(), 6);
#endif
}