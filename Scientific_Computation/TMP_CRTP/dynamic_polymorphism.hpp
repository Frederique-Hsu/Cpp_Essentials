/*!
 *  \file       dynamic_polymorphism.hpp
 *  \brief      
 *  
 */


#pragma once

class LocalHeap;

class NumProc       // NGSolve's base class for numerical procedures
{
public:
    virtual ~NumProc() = default;
public:
    virtual void Do(LocalHeap& lh) = 0;
};

class NumProcError : public NumProc
{
public:
    virtual void Do(LocalHeap& lh) override;
};

class NumProcBVP : public NumProc
{
public:
    virtual void Do(LocalHeap& lh) override;
};

/*============================================================================*/

class Matrix
{
public:
    virtual ~Matrix() = default;
public:
    virtual double operator()(int row_index, int col_index) = 0;
};

class SymmetricMatrix : public Matrix
{
public:
    virtual double operator()(int row_index, int col_index) override;
};

class UpperTriangleMatrix : public Matrix
{
public:
    virtual double operator()(int row_index, int col_index) override;
};