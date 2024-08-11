/*!
 *  \file       path-info.cpp
 *  \brief
 *
 */


#include <cstdlib>
#include <iostream>

#include <boost/filesystem.hpp>


inline const char* say_what(bool b)
{
    return b ? "true" : "false";
}

int main(int argc, char* argv[])
{
    using namespace std;

    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << " path-element [path-element...]" << endl
             << "Composes a path via operator/= from one or more path-element arguments\n"
                "Example: path_info foo/bar baz\n"
#ifdef BOOST_POSIX_API
                " would report information about the composed path foo/bar/baz"
#elif BOOST_WINDOWS_API
                " would report information about the composed path foo/bar\\baz"
#endif
             << endl;

        return EXIT_FAILURE;
    }

    boost::filesystem::path file_path;
    for (; argc > 1; --argc, ++argv)
    {
        file_path /= argv[1];
    }

    cout << "\ncomposed path: " << endl;
    cout << " operator<<()-----------: " << file_path << endl;
    cout << " make_preferred()-------: " << file_path.make_preferred() << endl;
    cout << "\nelements: " << endl;
    for (auto element : file_path)
    {
        cout << " " << element << endl;
    }
    cout << "\nobservers, native format: " << endl;
#ifdef BOOST_POSIX_API
    cout << "native()----------------: " << file_path.native() << endl;
    cout << "c_str()-----------------: " << file_path.c_str() << endl;
#elif BOOST_WINDOWS_API
    wcout << L"native()---------------: " << file_path.native() << endl;
    wcout << L"c_str()----------------: " << file_path.c_str() << endl;
#endif

    cout << "string()----------------: " << file_path.string() << endl;
    wcout << L"wstring()---------------: " << file_path.wstring() << endl;

    cout << "\nobservers, generic format: " << endl;
    cout << "generic_string()--------: " << file_path.generic_string() << endl;
    wcout << L"generic_wstring()-------: " << file_path.generic_wstring() << endl;

    cout << "\ndecomposition: " << endl;
    cout << "root name()-------------: " << file_path.root_name() << endl;
    cout << "root_directory()--------: " << file_path.root_directory() << endl;
    cout << "root_path()-------------: " << file_path.root_path() << endl;
    cout << "relative_path()---------: " << file_path.relative_path() << endl;
    cout << "parent_path()-----------: " << file_path.parent_path() << endl;
    cout << "filename()--------------: " << file_path.filename() << endl;
    cout << "stem()------------------: " << file_path.stem() << endl;
    cout << "extension()-------------: " << file_path.extension() << endl;

    cout << "\nquery: " << endl;
    cout << "empty()-----------------: " << say_what(file_path.empty()) << endl;
    cout << "is_absolute()-----------: " << say_what(file_path.is_absolute()) << endl;
    cout << "has_root_name()---------: " << say_what(file_path.has_root_name()) << endl;
    cout << "has_root_directory()----: " << say_what(file_path.has_root_directory()) << endl;
    cout << "has_root_path()---------: " << say_what(file_path.has_root_path()) << endl;
    cout << "has_relative_path()-----: " << say_what(file_path.has_relative_path()) << endl;
    cout << "has_parent_path()-------: " << say_what(file_path.has_parent_path()) << endl;
    cout << "has_filename()----------: " << say_what(file_path.has_filename()) << endl;
    cout << "has_stem()--------------: " << say_what(file_path.has_stem()) << endl;
    cout << "has_extension()---------: " << say_what(file_path.has_extension()) << endl;

    return EXIT_SUCCESS;
}