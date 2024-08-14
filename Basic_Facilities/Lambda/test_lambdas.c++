/*!
 *  \file       test_lambdas.c++
 *  \brief
 *
 */


#include "lambdas.hpp"
#include "test_lambdas.h++"

#include <gtest/gtest.h>

#include <random>
#include <typeinfo>

TEST(UTest4Lambdas, CheckHowLambdaWorks)
{
    std::vector<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    print_modulo(numbers, std::cout, 3);

    std::cout << "\n=====================================================\n" << std::endl;

    Modulo_print modulo(std::cout, 3);
    modulo(numbers);

    std::cout << "\n=====================================================\n" << std::endl;
    print_modulo<std::vector<int>>(numbers, std::cout, 3);

    std::cout << "\n=====================================================\n" << std::endl;
    printModule(numbers, std::cout, 3);
}

TEST(UTest4lambdas, CheckLambdaNamedVariables)
{
    using namespace std;

    using city = string;
    using population = int;
    const map<city, population> cityPopulations{pair<city, population>{"Beijing", 2189'3095},       // 使用限定{}列表
                                                {"Shanghai", 2487'0895},                            // 使用未限定{}列表
                                                {"Shenzhen", 1100'0000},
                                                {"Wuhan",    1100'0000},
                                                {"Hangzhou",  870'0000},
                                                {"成都",      1500'0000},
                                                {"香港",       747'4200},
                                                {"Amoi (厦门)",560'0000}};
    printAll(cityPopulations, "City \t Population");
}

std::vector<std::uint64_t> UTester4LambdaFunctions::generateFibonacci(int n)
{
    std::vector<std::uint64_t> fibonacci(n);
    fibonacci[0] = 1;
    fibonacci[1] = 1;
    for (int index = 2; index < n; ++index)
    {
        fibonacci[index] = fibonacci[index-1] + fibonacci[index-2];
    }
    return fibonacci;
}

TEST_F(UTester4LambdaFunctions, CheckLambdaCapture)
{
    using namespace std;

    auto fibonacci = generateFibonacci(30);

    auto printFibonacci = [&fibonacci]() mutable {
        for (auto fib : fibonacci)
        {
            cout << fib << "\t";
        }
        cout << endl;
    };

    cout << "The raw fibonacci series is: " << endl;
    printFibonacci();

    cout << "After shuffle, it becomes: " << endl;
    shuffle(fibonacci.begin(), fibonacci.end(), mt19937_64(random_device()()));
    printFibonacci();

    bool reverse = true;
    sort(fibonacci.begin(), fibonacci.end(),
         [reverse](auto a, auto b)
         {
            return reverse ? (std::labs(a) > std::labs(b)) : (a < b);
         });
    printFibonacci();
}

void UTester4LambdaFunctions::userAlgo(std::vector<int>& vec)
{
    int count = vec.size();

    /*!
     *  \note   通常情况下，人们不希望修改函数对象（也即 闭包）的状态，因此默认设置为不可修改。
     *          即：生成的函数对象的operator()()是一个const成员函数。只有在极少数情况下，如果我们确实希望
     *          修改状态（注意：不是修改通过引用捕获的变量的状态），则可以把lambda声明为mutable。
     */
    std::generate(vec.begin(),
                  vec.end(),
                  [&count]() mutable
                  {
                      return --count;
                  });
    EXPECT_EQ(count, 0);
}

TEST_F(UTester4LambdaFunctions, CheckLambdaModifyState)
{
    std::vector<int> odds{1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    auto rawSize = odds.size();

    userAlgo(odds);
}

auto deduceFunctionReturnType(int x)
{
    return x;
}

void fn(double val)
{
    (void)val;
}

void g(double y)
{
    auto calc = [&] { fn(y); };
    auto result = std::is_same<typeof(calc()), void>::value;
    EXPECT_EQ(result, true);

    auto z1 = [=](int x) { return x + y; };
    result = (std::is_same<decltype(z1(5)), double>::value == true);
    EXPECT_EQ(result, true);

    auto z2 = [&, y]() {
        if (y)
            return 1;
        else
            return 2;
    };
    EXPECT_EQ(typeid(z2()), typeid(int));

    auto z3 = [y]() { return y ? 1 : 2; };
    EXPECT_EQ(typeid(z3()), typeid(int));

    auto z4 = [=, &y]() -> double {
        if (y)
            return int{1};
        else
            return double{2};
    };
    result = std::is_same<decltype(z4()), double>::value;
    EXPECT_EQ(result, true);
}

TEST(UTest4Lambdas, CheckDeduceLambdaFunctionReturnedType)
{
    auto fn_returned_value = deduceFunctionReturnType(5);
    EXPECT_EQ(typeid(fn_returned_value), typeid(int));

    g(std::atan(1.0) * 4);

    auto my = [](int) -> int {
        return 1;
    };
    auto your = [](int) -> int {
        return 1;
    };
    /*!
     *  \warning    任意两个lambda表达式的类型都不相同，即使他们具有完全相同的参数列表，捕获列表和返回类型。
     *              一旦两个lambda具有相同的类型，那么模板实例化机制就无法辨识他们了。
     */
    EXPECT_NE(typeid(my), typeid(your));
}

static void reverse(std::string& s1, std::string& s2)
{
    /*!
     *  \note   但我们可以给lambda起一个新的名字，以std::function<>作为它的类型。
     *          这样还可以递归地调用lambda函数了。 如下：
     *
     *          为什么？ 因为std::function<>可以明确地知道返回类型。编译器可以正常编译。
     */
    std::function<void(char* b, char* e)> rev = [&](char* b, char* e) {
        if (1 < (e - b))
        {
            std::swap(*b, *--e);
            rev(++b, e);
        }
    };

    rev(&s1[0], &s1[0] + s1.size());
    rev(&s2[0], &s2[0] + s2.size());
}

static void auto_reverse(std::vector<char>& vecstr1, std::vector<char>& vecstr2)
{
    /*!
     *  \note   如果不需要递归地调用lambda函数，只是起一个新名字，仍然可以使用auto
     */
    auto rev = [&](char* begin, char* end) {
        while (1 < (end - begin))
        {
            std::swap(*begin++, *--end);
        }
    };

    rev(&vecstr1[0], &vecstr1[0] + vecstr1.size());
    rev(&vecstr2[0], &vecstr2[0] + vecstr2.size());
}

TEST(UTest4Lambdas, CheckLambdaType)
{
#if false
    auto rev = [](char* b, char* e) {
        if (1 < (e - b))
        {
            std::swap(*b, *--e);
            // rev(++b, e);     // 错误：因为我们无法推断出来一个auto变量之前便使用它，编译器无法为该变量分配多大的栈空间。
        }
    };
#endif

    std::string s1("hello"), s2("world");
    reverse(s1, s2);
    std::cout << "s1 = " << s1 << std::endl
              << "s2 = " << s2 << std::endl;
    EXPECT_STRCASEEQ(s1.c_str(), "olleh");
    EXPECT_STRCASEEQ(s2.c_str(), "dlrow");

    std::vector<char> love{'A', 'l', 'i', 'c', 'e', ' ', 'l', 'o', 'v', 'e', ' ', 'B', 'o', 'b'};
    std::string chinese_love("徐赞爱着余学琴");

    std::vector<char> chinese_love_oauth(chinese_love.size());
    std::copy(chinese_love.begin(), chinese_love.end(), chinese_love_oauth.begin());
    auto_reverse(love, chinese_love_oauth);

    auto speakLove = [](const std::vector<char>& love_str) {
        for (char love_char : love_str)
        {
            std::cout << love_char;
        }
        std::cout << std::endl;
    };
    speakLove(love);
    speakLove(chinese_love_oauth);
}

TEST(UTest4Lambdas, ConvertLambdaToFunctionPointer)
{
    /*!
     *  \remark     如果一个lambda什么也不捕获，则可以将它赋给一个指向完全一致类型的函数指针。
     */
    double (*p1)(double) = [](double a) {
        return std::sqrt(a);
    };

#if false
    double (*p2)(double) = [&](double a) {      // Error: 此处lambda捕获了内容
        return std::sqrt(a);
    };

    double (*p3)(unsigned int) = [](int a) {      // Error: 参数类型不匹配
        return std::sqrt(a);
    };
#endif

    EXPECT_DOUBLE_EQ(p1(4.0), 2.0);
}
