/*!
 *  \file       implementation.hpp
 *  \brief      
 *  
 */


#pragma once

#include "internal_program_representation.hpp"

namespace impl
{
    template<typename T>
    struct Node : T
    {
        using Interface = T;
        void accept(ipr::Visitor& visitor) const override;
    };

    template<typename Interface>
    struct Expr : Node<Interface>
    {
        const ipr::Type* constraint;

        Expr();

        const ipr::Type& type() const override;
    };

    template<typename T> class RefSequence;
    template<typename S>
    struct Stmt : S
    {
        ipr::UnitLocation unit_locus;
        ipr::SourceLocation src_locus;
        RefSequence<ipr::Annotation> notes;

        const ipr::UnitLocation& unit_location() const override;
        const ipr::SourceLocation& source_location() const override;
        const ipr::Sequence<ipr::Annotation>& annotation() const override;
    };

    template<typename D> class BasicDeclDate;
    template<typename S> class ValSequence;
    template<typename D>
    struct Decl : Stmt<Node<D>>
    {
        BasicDeclData<D> decl_data;
        ipr::NamedMap* pat;
        ValSequence<ipr::Substitution> args;

        Decl();

        const ipr::Sequence<ipr::Substitution>& substitutions() const;
        const ipr::NamedMap& generating_map() const override;
        const ipr::Linkage& lang_linkage() const override;
        const ipr::Region& home_region() const override;
    };

    struct Var : Decl<ipr::Var>
    {
        const ipr::Expr* init;
        const ipr::Region* lexreg;

        Var();

        bool has_initializer() const override;
        const ipr::Expr& initializer() const override;
        const ipr::Region& lexial_region() const override;
    };
}