/*!
 *  \file       stream_iterator.cpp
 *  \brief
 *
 */


#include "stream_iterator.hpp"

#include <string>
#include <iostream>
#include <fstream>
#include <iterator>
#include <vector>
#include <algorithm>
#include <set>

int handle_text_file_stream()
{
#if 0
    std::string from_file_name, to_file_name;
    std::cin >> from_file_name >> to_file_name;     // 获取源文件和目标文件名

    std::ifstream file_in_stream(from_file_name);       // 对应文件from_file_name的输入流
    std::istream_iterator<std::string> in_stream_iter(file_in_stream);      // 输入流的迭代器
    std::istream_iterator<std::string> end_of_stream{};     // 输入流哨兵

    std::ofstream file_out_stream(to_file_name);    // 对应文件to_file_name的输出流
    std::ostream_iterator<std::string> out_stream_iter(file_out_stream, "\n");      // 输出流的迭代器

    std::vector<std::string> str_vec(in_stream_iter, end_of_stream);
    std::sort(str_vec.begin(), str_vec.end());      // 排序缓冲区中的单词

    /* 将不重复的单词拷贝到输出，丢弃重复值 */
    std::unique_copy(str_vec.begin(), str_vec.end(), out_stream_iter);

    return !file_in_stream.eof() || !file_out_stream;       // 返回错误状态
#else
    using namespace std;

    string from_file_name, to_file_name;
    cin >> from_file_name >> to_file_name;

    ifstream file_in_stream(from_file_name);
    ofstream file_out_stream(to_file_name);

    set<string> str_set(istream_iterator<string>{file_in_stream}, istream_iterator<string>{});  // 读取输入
    copy(str_set.begin(), str_set.end(), ostream_iterator<string>{file_out_stream, "\n"});      // 拷贝到输出

    return !file_in_stream.eof() || !file_out_stream;
#endif
}

void find_specific_elements(std::map<std::string, int>& student_scores, int score)
{
    auto p = std::find_if(student_scores.begin(), student_scores.end(), GreaterThan{score});

    int count = std::count_if(student_scores.begin(),
                              student_scores.end(),
                              [score](const std::pair<std::string, int>& target)
                              {
                                    return target.second > score;
                              });
}
