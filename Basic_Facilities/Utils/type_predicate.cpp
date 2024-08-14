/*!
 *  \file       type_predicate.cpp
 *  \brief
 *
 */


#include "type_predicate.hpp"

#include <algorithm>


Record::Record(const std::string& record_name) : name(record_name)
{
}

std::ostream& operator<<(std::ostream& out_stream, const Record& record)
{
    return out_stream << record.name;
}

void search_sub_sequence(const std::vector<Record>& records)
{
    auto rec_eq = [](const Record& r1, const Record& r2)
                  {
                      return r1.name < r2.name;
                  };
    auto er = std::equal_range(records.begin(), records.end(), Record("Reg"), rec_eq);
    for (auto p = er.first; p!= er.second; ++p)
    {
        std::cout << *p;
    }
}
