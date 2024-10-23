/*!
 *  \file       internal_program_representation.hpp
 *  \brief      
 *  
 */


#pragma once


namespace ipr   // internal program representation
{
    enum class CategoryCode
    {
    };

    class Visitor;

    struct Node     // 基类 Node 节点
    {
        const int node_id;
        const CategoryCode category;

        virtual void accept(Visitor&) const = 0;
    protected:
        Node(CategoryCode);
    };

    class Type;
    struct Expr : Node      // 表达式
    {
        virtual const Type& type() const = 0;
    protected:
        Expr(CategoryCode c);
    };

    class UnitLocation;
    class SourceLocation;
    template<typename T> class Sequence;
    class Annotation;
    struct Stmt : Expr
    {
        virtual const UnitLocation& unit_location() const = 0;
        virtual const SourceLocation& source_location() const = 0;
        virtual const Sequence<Annotation>& annotation() const = 0;
    protected:
        Stmt(CategoryCode c);
    };

    class Linkage;
    class Name;
    class Region;
    class NamedMap;
    class Substitution;
    struct Decl : Stmt
    {
        enum Specifier
        {
        };

        virtual Specifier specifiers() const = 0;
        virtual const Linkage& lang_linkage() const = 0;
        virtual const Name& name() const = 0;
        virtual const Region& home_region() const = 0;
        virtual const Region& lexial_region() const = 0;
        virtual bool has_initializer() const = 0;
        virtual const Expr& initializer() const = 0;
    protected:
        Decl(CategoryCode c);
    };

    struct Var : Category<var_cat, Decl>
    {
    };

    template<CategoryCode, typename T = Expr>
    struct Category : T
    {
    protected:
        Category() : T(Cat)
        {
        }
    };
}