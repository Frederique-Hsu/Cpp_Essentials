/*!
 *  \file       implementation.cpp
 *  \brief      
 *  
 */


#include "implementation.hpp"

namespace impl
{
    template<typename T>
    void Node<T>::accept(ipr::Visitor& visitor) const
    {
        visitor.visit(*this);
    }

    template<typename Interface>
    Expr<Interface>::Expr() : constraint{nullptr}
    {
    }

    template<typename Interface>
    const ipr::Type& Expr<Interface>::type() const
    {
        return *util.check(constraint);
    }

    template<typename S>
    const ipr::UnitLocation& Stmt<S>::unit_location() const
    {
        return unit_locus;
    }

    template<typename S>
    const ipr::SourceLocation& Stmt<S>::source_location() const
    {
        return src_locus;
    }

    template<typename S>
    const ipr::Sequence<ipr::Annotation>& Stmt<S>::annotation() const
    {
        return notes;
    }

    template<typename D>
    Decl<D>::Decl() : decl_data(0), pat{nullptr}
    {
    }

    template<typename D>
    const ipr::Sequence<ipr::Substitution>& Decl<D>::substitutions() const
    {
        return args;
    }

    template<typename D>
    const ipr::NamedMap& Decl<D>::generating_map() const
    {
        return *util::check(pat);
    }
}