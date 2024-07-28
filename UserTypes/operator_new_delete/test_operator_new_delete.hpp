/*!
 *  \file       test_operator_new_delete.hpp
 *  \brief
 *
 */


#pragma once


void UTest_CheckOrdinaryOperatorNewDelete();
void UTest_CheckOrdinaryOperatorNewDelete_Array();
void UTest_CheckOperatorNewDelete_NoThrow();
void UTest_CheckOperatorNewDelete_NoThrow_Array();
void UTest_CheckOperatorNewDelete_Alignment();
void UTest_CheckOperatorNewDelete_Alignment_NoThrow_Array();
void UTest_CheckOperatorNewDelete_WithWrongAlignment();
void UTest_CheckPlacementNewDelete();

class Complex
{
public:
    explicit Complex(double real = double{}, double imag = double{});
    ~Complex();

private:
    double m_real;
    double m_imag;

public:
    double norm() const;
    void print();

    void set_real(double real);
    void set_imag(double imag);
};

void UTest_CheckHowToDeleteMemoryAllocatedByPlacementNew();
void UTest_WhenWillPlacementNewDeleteShowSegmentFault();

void UTest_CheckClassSpecificOperatorNewDelete();
void UTest_CheckClassSpecificOperatorNewDelete_WithConstructorDestructor();
void UTest_CheckClassSpecificOperatorNewDelete_Array();
void UTest_CheckClassSpecificPlacementNewDelete();
void UTest_CheckClassSpecificOperatorNewDelete_WithAlignment();