/*!
 *  \file       factorial_sum.hpp
 *  \brief  
 *      
 *  
 */


 /*!
  * \example    算 1! 到 n! 的和
  *             基本描述：
  *             求 1! + 2! + 3! + ... + n! 的结果
  *             输入描述：
  *             一些整数 n (1 <= n <= 12)
  *             输出描述：
  *             对于每个 n, 输出计算结果。每个计算结果独占一行。
  */

#pragma once

/*!
 *  \fn         factorial
 *  \brief      Sum of Factorial
 *  \version    Non_TMP_1.0
 *  \details    简单的实现： 将 n! 计算做成函数 factorial(n)，将阶乘和计算任务写成循环调用阶乘函数。
 */
int factorial(int n);

void print_Factorial();


/*!
 *  \brief      Sum of Factorial
 *  \version    Non_TMP_2.0
 *  \details    改进函数的优化： 将阶乘计算函数 factorial(n) 优化成阶乘之和的函数 sumOfFactorial
 */
int sumOfFactorial(int n);

void print_SumOfFactorial();

/*!
 *  \brief      Sum of Factorial
 *  \version    Non_TMP_3.0
 *  \details    空间换时间的优化： 用空间换时间，开设一个数组，把中间结果填好，以应付频繁取用这些数据，
 *              不用每次计算都去调用阶乘和函数。
 */
void print_OptimizedFactorialSum();

void print_StaticFactorialSum();
