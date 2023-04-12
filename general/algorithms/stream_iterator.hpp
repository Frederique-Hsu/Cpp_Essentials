/*!
 *  \file       stream_iterator.hpp
 *  \brief
 *
 */


#pragma once

#include <map>
#include <string>

/* About stream iterator =========================================================================*/
int handle_text_file_stream();


/* About predicate ===============================================================================*/
void find_specific_elements(std::map<std::string, int>& student_scores, int score);

struct GreaterThan
{
    int value;
    GreaterThan(int val) : value(val) {}
    bool operator()(const std::pair<std::string, int>& target)
    {
        return target.second > value;
    }
};
