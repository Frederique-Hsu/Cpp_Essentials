/*!
 *  \file       test_constructor_destructor.c++
 *  \brief
 *
 */


#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <algorithm>
#include <list>
#include <map>
#include <initializer_list>

#include "constructor_destructor.hpp"
#include "finally.hpp"
#include "pointers.hpp"

TEST_CASE("Check the constructor and destructor of Tracer", "[Tracer]")
{
    auto fn = [](const std::vector<int>& vec)
    {
        Tracer tr("in fn()\n");
        for (const int& elem : vec)
        {
            Tracer tracer{std::string("for-loop") + std::to_string(elem) + '\n'};
        }
    };

    fn(std::vector<int>{2, 3, 4, 5});
}

std::string ident(std::string arg)  // 传值方式传递string (拷贝到arg中)
{
    return arg;                     // 返回string (将arg的值移出ident()，移动到其调用者中)
}

SCENARIO("Check how to move the object", "[move]")
{
    GIVEN("Create two string objects")
    {
        std::string s1{"Adams"};
        std::string s2{"Practchett"};

        WHEN("Passing them into the ident() function")
        {
            std::string returned_s1 = ident(s1);
            std::string returned_s2 = ident(s2);

            THEN("Check whether the returned string is identical to the original raw string")
            {
                REQUIRE(returned_s1 == s1);
                REQUIRE(returned_s2 == s2);
            }
        }
    }
}

TEST_CASE("Initialize the class object", "[Initialization]")
{
    /*!
     *  \attention  We cannot define a constructor for a built-in type, yet we can
     *              initialize it with a value of suitable type.
     */
    int a{1};
    char* p{nullptr};
    /*!
     *  \note   Similarly, we can initialize objects of a class for which we have not
     *          defined a constructor using:
     *  \list
     *      \li memberwise initialization
     *      \li copy initialization
     *      \li default initialization (without an initializer or with an empty initializer list)
     *  \endlist
     */

    SECTION("Initialize the structure, without constructor")
    {
        Work s9{.author = "Beethoven",
                .name = "Symphony No.9 in D minor, Op. 125; Choral",
                .year = 1824};          // memberwise initialization
        Work currently_playing{s9};     // copy initialization
        Work none{};                    // default initialization, empty initializer list

        REQUIRE(currently_playing == s9);
        REQUIRE(none == Work{"", "", 0});
    }

    SECTION("But not initialize the local variable and dynamic object")
    {
        Work alpha;
        /*!
         *  \attention  对于静态分配的对象，结构体的初始化方式与使用Work{}相同。
         */
        std::cout << alpha << std::endl;

        auto fn = []() {
            Work beta;

            /*!
             *  \attention  但对于函数内局部变量或动态分配的对象，只对类类型的成员进行默认初始化，
             *              对于内置类型的成员是不进行初始化的。
             *              因此，beta.year是unknown的。
             */
            REQUIRE(beta.author == "");
            REQUIRE(beta.name == "");
            std::cout << "beta.year = " << beta.year << std::endl;
        };

        fn();
    }

    SECTION("造成这种复杂性的原因是为了提高极少数关键情况下的性能")
    {
        using namespace std;

        Buff buf0;      // 静态分配的对象，不一定完全初始化其成员。

        auto fn = []() {
            Buff buf1;      // 元素未被初始化
            Buff buf2{};    // 对于局部变量，提供一个初始化器{}，可以确保元素都被初始化。

            int* p1 = new int;      // *p1未被初始化，其内容是未知的。
            int* p2 = new int{};
            int* p3 = new int{7};

            auto cleanup = finally([&]() {
                delete p1;
                delete p2;
                delete p3;
            });

            REQUIRE(*p2 == 0);
            REQUIRE(*p3 == 7);

            cout << "*p1 = " << *p1 << endl;

            cout << "buf1.count = " << buf1.count << endl;
            REQUIRE(buf2.count == 0);

            auto size = sizeof(buf1.buff) / sizeof(buf1.buff[0]);
            for (auto index = 0U; index < size; ++index)
            {
                cout << "buf1.buff[" << index << "] = " << buf1.buff[index] << endl;
            }
            cout << "\n" << endl;

            std::for_each(buf2.buff,
                          buf2.buff + size,
                          [](const auto& elem)
                          {
                              static int index = 0;
                              cout << "buff2.buff[" << index++ << "] = " << elem << endl;
                          });
            cout << "\n" << endl;
        };
        fn();

        class Print
        {
        public:
            void operator()(const unsigned& elem)
            {
                static int index = 0;
                cout << "buf0.buff[" << index++ << "] = " << elem << endl;
            }
        };
        std::for_each(buf0.buff,
                      buf0.buff + sizeof(buf0.buff)/sizeof(buf0.buff[0]),
                      Print());
        cout << "\n" << endl;
    }

    SECTION("Naturally, memberwise initialization works only if we can access the members")
    {
        pointers::CheckedPointer<int> p{new int{7}};

        REQUIRE(*p == 7);
    }
}

SCENARIO("Adopt the constructor to initialize members", "[constructor to init]")
{
    GIVEN("Define a class with the ordinary constructor")
    {
        struct X
        {
            X(int) {}
        };

        THEN("If we have defined the constructor for a class, "
             "then each object should adopt this constructor")
        {
            // X x0;               // Error: no initializer
            // X x1{};             // Error: empty initializer
            X x2{2};            // OK
            // X X3{"three"};      // Error: wrong initializer type
            // X x4{1, 2};         // Error: wrong number of initializers
            X x5{x2};           // OK: copy constructor is implicitly defined.

            /*!
             *  \attention  当定义了一个接受参数的构造函数后，默认构造函数就不存在了。
             *              毕竟，X(int)表明我们需要一个int来构造一个X。
             *              但是，拷贝构造函数不会消失。
             */
        }

        WHEN("Used the {} notation to make explicit initialization")
        {
            /*!
             *  \note   使用{}语法来明确表示正在进行初始化，而不仅仅是在赋值、调用函数或者是声明函数。
             *          只要是在构造对象的地方，都可以用{}初始化语法来为构造函数提供参数。
             *
             *          {}初始化也被称为通用universal初始化： 这种语法可以用在任何地方。
             *          而且，{}初始化还是一致的：不论你在哪里用语法{v}将类型X的对象初始化为值v，
             *          都会创建相同的值X{v}
             *
             *          与{}相反，=和()初始化语法不是通用的。
             *
             *  \attention  {}初始化器语法不允许窄化转换。这是我们更倾向于{}风格，而不是()或=的另一个原因。
             */
            struct Y : X
            {
                X m{0};
                Y(int a) : X{a}, m{a} {}
                Y() : X{0} {}
            };

            THEN("Construct and initialize the object")
            {
                X g{1};

                auto fn = [](int a) {
                    // X def{};    // Error: X没有默认构造函数，没有默认值
                    Y def2{};       // OK: 使用Y的默认构造函数 Y::Y()
                    X* ptr{nullptr};

                    X var{2};
                    ptr = new X{4};     // 初始化自由空间中的对象
                    X array[]{1, 2, 3}; // 初始化数组
                    std::vector<X> vec{5, 6, 7, 8, 9, 10};  // 初始化向量元素

                    delete ptr;
                };

                fn(9);
            }

            THEN("构造函数需遵循常规的重载解析规则")
            {
                struct S
                {
                    S(const char*) {}
                    S(double*) {}
                };

                S s1{"Napier"};

                double data{1.0};
                S s2{&data};
                // S s3{nullptr};      // Error: 有歧义，是S::S(const char*)还是S::S(double*)?
            }
        }

        WHEN("Used the () notation to initialize the members")
        {
            struct S1       // no constructor
            {
                int a;
                int b;
            };

            struct S2       // with constructor
            {
                int a;
                int b;
                S2(int val1 = 0, int val2 = 0) : a(val1), b(val2) {}
            };

            THEN("() notation cannot get rhe memberwise initialization or initializer-list initialization")
            {
                // S1 my_error_obj(1, 2);          // Error: no constructor
                S1 my_right_obj{1, 2};          // OK: memberwise initialization

                // S1 his_wrong_obj(1);            // Error: no constructor
                S1 his_right_obj{1};            // OK: .b becomes 0

                S2 your_right_obj(1, 2);        // OK: use constructor
                S2 your_correct_obj{1, 2};      // OK: use constructor

                S2 her_right_obj(1);            // OK: use constructor and one default argument
                S2 her_correct_obj{1};          // OK: use constructor and one default argument

                /*!
                 *  \attention  但在极少数情况下，你需要区分使用一个元素列表初始化，还是用构造函数参数列表初始化？
                 */
                std::vector<int> vec1{77};      // 用值77初始化一个元素
                std::vector<int> vec2(77);      // 将77个元素初始化为0

                REQUIRE(vec1.size() == 1);
                REQUIRE(vec2.size() == 77);
            }

            THEN("But initialize a container with initializer-list constructor or ordinary constructor")
            {
                using std::vector;
                using std::string;

                {
                vector<string> vec_str{77};     // 77个元素初始化为默认值"", 因为vector<string>(initializer_list<string>)不接受{77}
                vector<string> str_vec(77);     // 77个元素初始化为默认值""
                REQUIRE(vec_str.size() == 77);
                REQUIRE(str_vec.size() == 77);
                }

                {
                vector<string> strvec{"Booh!"}; // 一个元素初始化为"Booh!"
                // vector<string> vecstr("Booh!"); // Error: 没有构造函数接受单一字符串参数的
                REQUIRE(strvec.size() == 1);
                REQUIRE(strvec[0] == "Booh!");
                }

                {
                vector<int*> intptr_vec1{100, 0};   // 100个int*初始化为nullptr
                vector<int*> intptr_vec2{0, 0};     // 两个int*初始化为nullptr
                vector<int*> intptr_vec3(0, 0);     // 空的vector
                vector<int*> intptr_vec4;           // 空的vector
                vector<int> int_vec{100, 0};        // 2个int元素，第一个元素为100，第二个为0

                REQUIRE(intptr_vec1.size() == 100);
                {
                    int count = 0;
                    for (auto elem : intptr_vec1)
                    {
                        count++;
                        REQUIRE(elem == nullptr);
                    }
                    REQUIRE(count == 100);
                }

                REQUIRE(intptr_vec2.size() == 2);
                {
                    int cnt = 0;
                    for (auto elem : intptr_vec2)
                    {
                        cnt++;
                        REQUIRE(elem == nullptr);
                    }
                    REQUIRE(cnt == 2);
                }

                REQUIRE(intptr_vec3.size() == 0);
                // REQUIRE(intptr_vec3[0] == nullptr);     // 因为是空的vector，访问其元素会导致崩溃.

                REQUIRE(intptr_vec4.size() == 0);

                REQUIRE(int_vec.size() == 2);
                REQUIRE(int_vec[0] == int{100});
                REQUIRE(int_vec[1] == int{0});
                }
            }
        }
    }
}

SCENARIO("Default constructor")
{
    GIVEN("Define the classes with default constructors")
    {
        class Vector
        {
        public:
            Vector() {}     // 默认构造函数： 无参数
        };

        WHEN("Instantiate the object by calling default constructor")
        {
            /*!
             *  \note   如果构造对象时未指定参数或提供一个空初始化器列表，则会调用默认构造函数。
             */
            Vector v1;
            Vector v2{};
        }

        class String
        {
        public:
            /*!
             *  \note   如果一个接受参数的构造函数仅使用一个默认参数，那该构造函数也是默认构造函数。
             */
            String(const char* p = "") {}
        };

        WHEN("Create an object by calling the constructor with one default argument")
        {
            String s1;
            String s2{};
        }

        WHEN("Initialize the built-in type of objects")
        {
            auto fn = []() {
                int a0;
                int a1();

                int i{};
                double d{};
                char* p{};

                int* unintialized_ptr = new int;
                int* initialized_ptr = new int{};

                REQUIRE(a0 != 0);
                REQUIRE(i == 0);
                REQUIRE(d == 0.0);
                REQUIRE(p == nullptr);
                REQUIRE(*unintialized_ptr != 0);
                REQUIRE(*initialized_ptr == 0);

                delete unintialized_ptr;
                delete initialized_ptr;
            };
            fn();
        }

        WHEN("Reference and const must be initialized")
        {
            Compound obj;

            REQUIRE(obj.a1 == 7);
            REQUIRE(obj.r1 == 9);
        }

        WHEN("Array, vector and similar containers need to declare and "
             "allocate a number of default-initialized elements")
        {
            struct S1
            {
                S1() {}
            };
            struct S2
            {
                S2(const char*) {}
            };

            THEN("Instantiate the array or vector lists")
            {
                S1 array1[10];      // OK: 10 default elements
                // S2 array2[10];      // Error: cannot initialize the elements
                S2 array3[] {"alpha", "beta"};      // OK: two elements

                std::vector<S1> v1(10);
                // std::vector<S2> v2(10);     // Error: cannot initialize elements
                std::vector<S2> v3{"alpha", "beta"};

                std::vector<S2> v4(10, "");
                std::vector<S2> v5;

                REQUIRE(sizeof(array3)/sizeof(array3[0]) == 2);
                REQUIRE(v3.size() == 2);
                REQUIRE(v4.size() == 10);
            }
        }
    }
}

SCENARIO("Initializer-list constructors")
{
    using namespace std;

    vector<double> vec = {1, 2, 3.14, 68.935};
    list<pair<string, string>> languages = {{"Nygaard", "Simula"},
                                            {"Richards", "BCPL"},
                                            {"Ritchie", "C"},
                                            {"Bjarne Stroustrup", "C++"}};

    using Key = vector<string>;
    using Value = vector<int>;
    map<Key, Value> years = {
        {{"Maurice", "Vincent", "Wilkes"}, {1913, 1945, 1951, 1967, 2000}},
        {{"Martin", "Richards"}, {1982, 2003, 2007}},
        {{"David", "John", "Wheeler"}, {1927, 1947, 1951, 2004}}
    };

    REQUIRE(vec.size() == 4);
    REQUIRE(languages.size() == 4);
    REQUIRE(years.size() == 3);

    years.insert({Key{"Bjarne", "Stroustrup"}, Value{1950, 1957, 1985}});

    GIVEN("A class has defined multiple constructors")
    {
        #include <iostream>

        using namespace std;

        class X
        {
        public:
            X()                             // default constructor
            {
                cout << "called the default constructor." << endl;
            }
            explicit X(int)                 // ordinary constructor
            {
                cout << "called the ordinary constructor." << endl;
            }
            X(std::initializer_list<int>)   // initializer-list constructor
            {
                cout << "called the initializer-list constructor." << endl;
            }
            X(const X&)                     // copy constructor
            {
                cout << "called the copy constructor." << endl;
            }
            X(X&&)                          // move constructor
            {
                cout << "called the move constructor." << endl;
            }
            X& operator=(const X&)          // copy assignment
            {
                cout << "called the copy assignment." << endl;
                return *this;
            }
            X& operator=(X&&)               // move assignment
            {
                cout << "called the move assignment." << endl;
                return *this;
            }
            ~X()                            // destructor
            {
                cout << "called the destructor." << endl;
            }
        };

        WHEN("When selecting the constructor, which one is preferred?")
        {
            /*!
             *  \note   如果一个类已有多个构造函数，则编译器会使用常规的重载解析规则根据给定参数选择一个正确的构造函数。
             *          当选择构造函数时，默认构造函数和初始化器列表构造函数优先。
             *
             *  \list   具体规则如下：
             *      \li 如果默认构造函数或初始化器列表构造函数都匹配，优先选择默认构造函数。
             *      \li 如果一个初始化器列表构造函数和一个“普通构造函数”都匹配，优先选择初始化器列表构造函数。
             *  \endlist
             */
            X x0{};     // 空列表： 是选择默认构造函数还是初始化器列表构造函数？ 答案：选择默认构造函数

            X x1{1};    // 一个整数： 是选择一个整型参数普通构造函数还是一个单元素的初始化器列表构造函数？ 答案：选择初始化器列表构造函数

            X x2(3);    // 非列表，只是一个简单参数： 答案：选择普通构造函数
        }

        WHEN("Consider the below std::vector<T> objects")
        {
            /*!
             *  \note   以下vector创建的对象都调用初始化器列表构造函数
             */
            std::vector<int> v1{1};         REQUIRE(v1.size() == 1);    REQUIRE(v1[0] == 1);
            std::vector<int> v2{1, 2};      REQUIRE(v2.size() == 2);    REQUIRE((v2[0] == 1 and v2[1] == 2));
            std::vector<int> v3{1, 2, 3};   REQUIRE(v3.size() == 3);

            std::vector<std::string> vs1{"one"};                    REQUIRE(vs1.size() == 1);
            std::vector<std::string> vs2{"one", "two"};             REQUIRE(vs2.size() == 2);
            std::vector<std::string> vs3{"one", "two", "three"};    REQUIRE(vs3.size() == 3);

            /*!
             *  \note   如果真的希望调用接受一个或两个整型参数的构造函数，就必须使用()语法
             */
            std::vector<int> vec1(1);       REQUIRE(vec1.size() == 1);  REQUIRE(vec1[0] == 0);
            std::vector<int> vec2(1, 2);    REQUIRE(vec2.size() == 1);  REQUIRE(vec2[0] == 2);
            std::vector<int> vec3(3, 1);    REQUIRE(vec3.size() == 3);  REQUIRE(vec3[0] == 1);  REQUIRE(vec3[1] == 1);  REQUIRE(vec3[2] == 1);
            // std::vector<int> vec4(4, 1, 2, 3, 4);   // No matching constructor for vector<T>
        }
    }

    GIVEN("Utilize the initializer_list")
    {
        #define BY_INDEX            1
        #define BY_ITERATOR         2
        #define BY_RANGE_FOR_LOOP   3
        #define VISIT_INITIALIZER_LIST_MEMBERS      BY_ITERATOR

        /*!
         *  \note       使用initializer_list
         *  \details    可以将接受一个initializer_list<T>参数的函数作为一个序列来访问。
         *              initializer_list<T>是以传值方式传递的。这是重载解析规则所要求的，而且不会带来额外开销。
         *              因为一个initializer_list<T>对象只是一个小句柄（通常是2个字节大小），
         *              指向一个元素类型为T的数组。
         */
        auto access = [](std::initializer_list<int> args)
        {
        #if (VISIT_INITIALIZER_LIST_MEMBERS == BY_INDEX)
            for (auto i = 0U; i != args.size(); ++i)
            {
                std::cout << args.begin()[i] << "  ";
            }
        #elif (VISIT_INITIALIZER_LIST_MEMBERS == BY_ITERATOR)
            for (auto iter = args.begin(); iter != args.end(); ++iter)
            {
                std::cout << *iter << "  ";
            }
        #elif (VISIT_INITIALIZER_LIST_MEMBERS == BY_RANGE_FOR_LOOP)
            for (auto arg : args)
            {
                std::cout << arg << "  ";
            }
        #endif
            std::cout << "\n" << std::endl;
        };

        WHEN("visiting the every element inside the initializer_list<T>")
        {
            std::initializer_list<int> numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
            access(numbers);
            REQUIRE(numbers.size() == 10);
        }

        auto cannotModifyInitializerList = [](std::initializer_list<int>& numbers, int new_value) {
            // *(numbers.begin()) = new_value;     // Error: initializer_list<T>里面的元素是不可改变的，不能修改其元素
            // numbers[0] = new_value;     // Error: initializer_list<T>不提供下标操作
            return *numbers.begin();
        };

        WHEN("modifying the element inside the initializer_list<T>")
        {
            /*!
             *  \attention  由于initializer_list<T>元素不可修改，因此就不能对其使用移动构造函数。
             */
            std::initializer_list<int> nums{9, 15, 32, 101};
            int num = cannotModifyInitializerList(nums, -100);
            REQUIRE(num == 9);

            THEN("compilation will fail")
            {
                for (auto& elem : nums)
                {
                    /*!
                     *  \warning    Cannot assign to variable 'elem' with const-qualified type 'const int&'
                     *              variable 'elem' is declared const here.
                     *
                    elem += 10;
                     */
                    std::cout << elem << ", ";
                }
                std::cout << "\n" << std::endl;
            }
        }
    }
}
