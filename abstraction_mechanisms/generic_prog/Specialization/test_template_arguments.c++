/*!
 *  \file       test_template_arguments.c++
 *  \brief
 *
 */


#include "template_arguments.hpp"
#include "template_arguments.cpp"

#include <cstdio>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <catch2/catch_test_macros.hpp>


TEST_CASE("Make the unit testing for values as the template arguments", "[value_arguments]")
{
    SECTION("Check the Buffer class template")
    {
        Buffer<char, 128> char_buffer;

        CHECK(char_buffer.capacity() == 128);
        CHECK(sizeof(char_buffer) == 128 * sizeof(char));

        Buffer<int, 5'000> int_buffer;
        CHECK(sizeof(int_buffer) == 5'000 * sizeof(int));
    }

    SECTION("Check the constructors of Buffer")
    {
        Buffer<int, 32> buf{1, 2, 3, 4, 5};

        CHECK(buf[0] == 1);
        CHECK(buf[1] == 2);
        CHECK(buf[2] == 3);
        CHECK(buf[3] == 4);
        CHECK(buf[4] == 5);
        CHECK(buf.capacity() == 32);

        const auto& nonvolatile_target = buf[3];    // this will call T& Buffer<T, N>::operator[](int index)
        // nonvolatile_target = 20;    // const reference cannot be changed.
        auto& volatile_target = buf[4];     // still call call T& Buffer<T, N>::operator[](int index)
        volatile_target = 15;           // but non-const reference can be changed, and influence the buf object itself.
        CHECK(buf[4] == volatile_target);

        Buffer<float, 10> fbuf = {1.0F, 2.0, 3.0F, 4.0, 5.0, static_cast<float>(std::atan(1.0) * 4)};
        CHECK(fbuf[4] == 5.0);
        CHECK_FALSE(fbuf[5] == std::asin(1.0) * 2);
        CHECK(fbuf[6] == 0.0);
        CHECK(fbuf[7] == 0.0);
        CHECK(fbuf[8] == 0.0);
        CHECK(fbuf[9] == 0.0);
        CHECK_THROWS_AS(fbuf[10] == 0.0, std::out_of_range);

        fbuf = {20.0, 30.5, 40.6, 50.2, 60.5};
        CHECK(fbuf[4] == 60.5);

        CHECK_THROWS_AS(fbuf = std::initializer_list<float>({1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0, 10.0, 11.0}), std::out_of_range);

        const Buffer<int, 5> fixed_buf{1, 2, 3, 4, 5};
        auto& value = fixed_buf[3];     // this will call the "const T& Buffer<T, N>::operator[](int index) const"
        // value = 100;    // value 是 const， 不可修改的。
        CHECK(value == 4);
    }

    SECTION("Check the iterator of Buffer")
    {
        Buffer<int, 10> ibuf{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        int index = 1;
        for (auto iter = ibuf.begin(); iter != ibuf.end(); ++iter)
        {
            CHECK(*iter == (index++));
        }


        const Buffer<int, 10> another_buffer(ibuf);
        index = 0;
        for (auto it = another_buffer.cbegin(); it != another_buffer.cend(); ++it)
        {
            CHECK(*it == ibuf[index++]);
        }
    }

    SECTION("Check the copy constructor and copy assignment of Buffer")
    {
        Buffer<int, 10> ibuf{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

        Buffer<int, 10> same_length_buff(ibuf);

        int index = 0;
        for (auto iter = same_length_buff.begin(); iter != same_length_buff.end(); ++iter)
        {
            CHECK(*iter == ibuf[index++]);
        }

        Buffer<int, 10> buffer;
        buffer = ibuf;
        bool is_equal = (buffer == ibuf);
        CHECK(is_equal == true);

        Buffer<int, 5> different_size_buffer;
        CHECK(different_size_buffer.capacity() == 5);
        // different_size_buffer = ibuf;   // 由于N是值参数，ibuf的N是10, different_size_buffer的N是10, 两者不能调用operator=拷贝赋值运算符。
    }

    SECTION("Check the operator>> and operator<< for Buffer")
    {
        SKIP();        

        Buffer<int, 8> buf;
        std::cin >> buf;
        std::cout << buf << std::endl;
        CAPTURE(buf);
    }
}


namespace {
    template<typename T, char* label> class X
    {
    public:
        explicit X(const char* msg);
    private:
        std::unordered_map<std::string, std::string> m_dict;
    };

    template<typename T, char* label> X<T, label>::X(const char* msg)
    {
        m_dict[label] = msg;
    }

    template<typename T, T default_value = T{}>
    class Misc
    {
    public:
        Misc() : m_elem{default_value} {}
        explicit Misc(T init_value) : m_elem{init_value} {}
    private:
        T m_elem;
    public:
        T getElement() const
        {
            return m_elem;
        }
    };

    template<typename T, T default_value> using Manipulator = Misc<T, default_value>;

SCENARIO("Make some specific cases for values as the template arguments", "[specific_cases]")
{
    GIVEN("Define the first type argument, assign the default_value, but arrange it as the second value argument")
    {
    #if false
        X<int, "BMW323Ci"> x1;  // error: string literals can never be used in the value argument of template.
        char my_car[] = "BMW 218i"; // error: 'my_car' is not a valid template argument, because it does not have a static storage duration.
        X<int, my_car> myX(std::string("This is my car."));
    #endif

        THEN("Retrieve the element from Misc<T, default_value> object")
        {
            Misc<int, 45> misc;
            CHECK(misc.getElement() == 45);

            Misc<double> empty;
            CHECK(empty.getElement() == double{});
        }

        WHEN("Assign std::string or char* as the first type argument of Misc<T, default_value>, but it will "
             "fail in the compilation")
        {
            /*!
             *  \warning    error: "std::basic_string<char>" is not a valid type for a template non-type parameter
             *              because it is not structural.
             *
             *  \remark     \code   using std::string = std::basic_string<char>;
             */
            // Misc<std::string, std::string("42")> digit_str;

            Misc<const char*> digit_str(static_cast<const char*>("42"));    // only "const char*" can work here
            int digit = std::stoi(digit_str.getElement());
            CHECK(digit == 42);
        }
    }

    GIVEN("Define the user data type")
    {
        using ElemType = int;
        struct Node
        {
            ElemType        elem;
            struct Node*    left;
            struct Node*    right;
        };

        WHEN("Assign user-defined struct Node as the type argument")
        {
            Misc<Node> tree(Node{.elem = 15, .left = nullptr, .right = nullptr});
            CHECK(tree.getElement().elem == 15);
        }

        WHEN("Especially define the function pointer")
        {
            using Tree = struct Node;
            typedef Node* (*CreateTree)  (ElemType init_elem);
            typedef void  (*DestroyTree) (Tree* tree);
            typedef Node* (*InsertTree)  (Tree* tree, ElemType new_elem);
            typedef void  (*TraverseTree)(Tree* tree, void (*access)(Node* node));
            typedef Node* (*FindTree)    (Tree* tree, ElemType target);

            class TreeManipulator
            {
            public:
                static Tree* createBinaryTree(ElemType init_elem)
                {
                    Tree* tree = new Tree{init_elem, nullptr, nullptr};
                    return tree;
                }
                static Node* getTreeNode(Tree* tree, ElemType target)
                {
                    Node* proot_node = tree;
                    if (proot_node == nullptr)
                    {
                        return nullptr;
                    }
                    if (target < proot_node->elem)
                    {
                        return getTreeNode(proot_node->left, target);
                    }
                    else if (proot_node->elem < target)
                    {
                        return getTreeNode(proot_node->right, target);
                    }
                    else    // if (target == proot_node->elem)
                    {
                        return proot_node;
                    }
                }
                static Tree* insertIntoTree(Tree* tree, ElemType new_elem)
                {
                    Node* proot_node = tree;
                    if (proot_node == nullptr)
                    {
                        proot_node = new Node{new_elem, nullptr, nullptr};
                        proot_node->left = proot_node->right = nullptr;
                    }
                    else
                    {
                        if (new_elem < proot_node->elem)
                        {
                            proot_node->left = insertIntoTree(proot_node->left, new_elem);
                        }
                        else if (proot_node->elem < new_elem)
                        {
                            proot_node->right = insertIntoTree(proot_node->right, new_elem);
                        }
                        else    // if (new_elem == proot_node->elem)
                        {
                            // new_elem has already been in the tree.  Do nothing!
                        }
                    }
                    return proot_node;
                }
                static void destroyBinaryTree(Tree* tree)
                {
                    Node* proot_node = tree;
                    while (proot_node)
                    {
                        if (proot_node->left != nullptr)
                        {
                            destroyBinaryTree(proot_node->left);
                        }
                        if (proot_node->right != nullptr)
                        {
                            destroyBinaryTree(proot_node->right);
                        }
                        delete proot_node;
                        proot_node = nullptr;
                    }
                }
                static void traverseBinaryTree(Tree* tree, void (*access)(Node* node))
                {
                #define BREADTH_FIRST_TRAVERSE              1       // 广度优先遍历，从上到下，从左到右
                #define DEPTH_FIRST_IN_ORDER_TRAVERSE       2       // 深度优先遍历，中序
                #define DEPTH_FIRST_PRE_ORDER_TRAVERSE      3       // 深度优先遍历，前序
                #define DEPTH_FIRST_POST_ORDER_TRAVERSE     4       // 深度优先遍历，后序
                #define TRAVERSE_WAY                        BREADTH_FIRST_TRAVERSE

                #if (TRAVERSE_WAY == DEPTH_FIRST_IN_ORDER_TRAVERSE)
                    Node* pnode = tree;
                    if (pnode != nullptr)
                    {
                        traverseBinaryTree(pnode->left, access);
                        access(pnode);
                        traverseBinaryTree(pnode->right, access);
                    }
                #elif (TRAVERSE_WAY == DEPTH_FIRST_PRE_ORDER_TRAVERSE)
                    Node* pnode = tree;
                    if (pnode != nullptr)
                    {
                        access(pnode);
                        traverseBinaryTree(pnode->left, access);
                        traverseBinaryTree(pnode->right, access);
                    }
                #elif (TRAVERSE_WAY == DEPTH_FIRST_POST_ORDER_TRAVERSE)
                    Node* pnode = tree;
                    if (pnode != nullptr)
                    {
                        traverseBinaryTree(pnode->left, access);
                        traverseBinaryTree(pnode->right, access);
                        access(pnode);
                    }
                #elif (TRAVERSE_WAY == BREADTH_FIRST_TRAVERSE)
                    Node* pnode = tree;

                    std::queue<Node*> queue;
                    if (pnode != nullptr)
                    {
                        queue.push(pnode);

                        while (!queue.empty())
                        {
                            pnode = queue.front();
                            queue.pop();
                            access(pnode);

                            if (pnode->left != nullptr)
                            {
                                queue.push(pnode->left);
                            }
                            if (pnode->right != nullptr)
                            {
                                queue.push(pnode->right);
                            }
                        }
                    }
                #endif
                }
            };

            THEN("Instantiate some manipulator to operator, and make the checkings")
            {
                Manipulator<CreateTree, nullptr> creator(&TreeManipulator::createBinaryTree);
                Manipulator<InsertTree, nullptr> inserter(&TreeManipulator::insertIntoTree);
                Manipulator<DestroyTree, nullptr> destroyer(TreeManipulator::destroyBinaryTree);
                Manipulator<TraverseTree, nullptr> traverser(&TreeManipulator::traverseBinaryTree);
                Manipulator<FindTree, nullptr> seeker(TreeManipulator::getTreeNode);

                Tree* tree = creator.getElement()(8);
                inserter.getElement()(tree, 5);
                inserter.getElement()(tree, 14);
                inserter.getElement()(tree, 3);
                inserter.getElement()(tree, 10);
                inserter.getElement()(tree, 38);
                inserter.getElement()(tree, -5);
                inserter.getElement()(tree, 9);

                auto print = [](Node* node) -> void
                {
                #if false
                    std::printf("%p    %p    % 8d    %p\n",
                                (void*)node, (void*)(node->left), node->elem, (void*)(node->right));
                #else
                    std::cout << std::setw(16) << std::right << (void*)node << "    "
                              << std::setw(16) << std::right << (void*)(node->left) << "    "
                              << std::setw(8)  << std::right << node->elem << "    "
                              << std::setw(16) << std::right << (void*)(node->right) << std::endl;
                #endif
                };
                std::cout << std::setw(16) << std::right << "current node" << "    "
                          << std::setw(16) << std::right << "left node" << "    "
                          << std::setw(8)  << std::right << "element" << "    "
                          << std::setw(16) << std::right << "right node" << std::endl;
                traverser.getElement()(tree, print);

                CHECK(seeker.getElement()(tree, 10)->elem == 10);
                CHECK(seeker.getElement()(tree, 2) == nullptr);
                CHECK(seeker.getElement()(tree, -5)->elem == -5);
                CHECK(seeker.getElement()(tree, 38)->elem == 38);

                destroyer.getElement()(tree);
            }
        }
    }
}
}

bool insensitive(const std::string& a, const std::string& b)
{
    auto to_lower = [](std::string s) -> std::string
    {
        std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c) { return std::tolower(c); });
        return s;
    };

    std::string lower_a = to_lower(a);
    std::string lower_b = to_lower(b);

    return std::strcmp(lower_a.c_str(), lower_b.c_str()) < 0;
}

TEST_CASE("Make the operation or function pointer as the template argument", "[option]")
{
    std::map<std::string, int> m1;      // 使用默认比较操作 std::less<std::string>
    std::map<std::string, int, std::greater<std::string>> m2;   // 用greater<string>进行比较

    using Cmp = bool (*)(const std::string&, const std::string&);
    std::map<std::string, int, Cmp> m4{insensitive};

    std::map<std::string, int, Cmp> m5{[](const std::string& a, const std::string& b) { return a > b; }};
}

TEST_CASE("Make the template as the template argument", "[template]")
{
    class Entry
    {
    public:
        Entry() {};
    };

    SECTION("Instantiate the Xrefd with a template type")
    {
        Xrefd<Entry, MyVec> entries;        // 在vector中存储Entry的交叉引用

        struct Record
        {
            int             id;
            std::string     name;
            double          score;
        };

        Xrefd<Record, MyContainer> records; // 在MyContainer中存储Record的交叉引用

        Xrefd_2Containers<std::vector<Entry>, std::set<Entry*>> entries_with_2containers;
    }
}


TEST_CASE("Default template argument", "[default]")
{
    SECTION("Specify the default parameter for template's argument")
    {
        my::map<std::string, int> m1;   // 使用std::less<std::string>进行比较
        CHECK(m1.empty() == true);

        my::map<std::string, int, std::greater<std::string>> m2;    // 使用指定的标准std::greater<std::string>进行比较
        m2["hello"] = 1;
        m2["world"] = 2;

        struct NoCase
        {
            bool operator()(const std::string& a, const std::string& b)
            {
                return insensitive(a, b);
            }
        };

        my::map<std::string, int, NoCase> m3;
        m3["hEllo"] = 1;
        m3["WoRLd"] = 2;
    }
}

TEST_CASE("Validate how to utilize the default function template argument")
{
    auto x1 = to<std::string, double>(1.2);     // Target type is std::string, and Source type is double
    auto x2 = to<std::string>(1.2);             // Source type is deduced to be double
    auto x3 = to<>(1.2);                        // Target type is std::string by default, and Source type is deduced to be double
    auto x4 = to(1.2);                          // the <> is redundant

    CHECK(x1 == std::string("1.2"));
    CHECK(x2 == "1.2");
    CHECK(std::stod(x3) == std::stod(std::to_string(1.2)));
    CHECK(std::stod(x4) == 1.2);

    /*============================================================================================*/

    auto checker = [](double d, int i, char* p)
    {
        auto c1 = narrow_cast<char>(64);
        CAPTURE(c1);
        auto c2 = narrow_cast<char>(-64);
        CHECK_THROWS_AS(narrow_cast<char>(264), std::runtime_error);
        auto c4 = narrow_cast<unsigned char>(i);

        auto d1 = narrow_cast<double>(1 / 3.0F);
        auto d2 = narrow_cast<double>(i);

        CHECK_THROWS_AS(narrow_cast<float>(1/3.0), std::runtime_error);
        CHECK_THROWS_AS(narrow_cast<float>(d), std::runtime_error);

        // auto p1 = narrow_cast<char*>(i);    // compile error: cannot cast from 'int' to pointer type 'char*'
        // auto i1 = narrow_cast<int>(p);      // error: static_cast from 'char*' to 'int' is not allowed
        
        CHECK_THROWS_AS(narrow_cast<int>(d), std::runtime_error);
    };

    char p[] = "hello";
    checker(3.1415926, 128, p);
}