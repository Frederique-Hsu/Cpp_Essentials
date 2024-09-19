/*!
 *  \file       member_templates_impl.hpp
 *  \brief      
 *  
 */


template<typename Scalar>
Complex<Scalar>::Complex() : m_real{}, m_imag{}
{
}

template<typename Scalar> template<typename T>
Complex<Scalar>::Complex(T re, T im) : m_real{re}, m_imag{im}
{
}

/*!
 *  \warning    在构造函数中，初始化类的数据成员尽量使用{}初始化语法。
 *              因为{}初始化语法不允许窄化转换，如从double向float转换
 *              而旧的()初始化语法则不检查窄化转换，这会带来一些预料之外的截断的错误。
 *              你可以分别使用{}和()进行测试，来验证是否如此。
 */
template<typename Scalar> template<typename T>
Complex<Scalar>::Complex(const Complex<T>& rhs) : m_real{rhs.real()}, m_imag{rhs.imag()}
{
}

template<typename Scalar>
Scalar& Complex<Scalar>::real()
{
    return m_real;
}

template<typename Scalar>
const Scalar& Complex<Scalar>::real() const
{
    return m_real;
}

template<typename Scalar>
Scalar& Complex<Scalar>::imag()
{
    return m_imag;
}

template<typename Scalar>
const Scalar& Complex<Scalar>::imag() const
{
    return m_imag;
}