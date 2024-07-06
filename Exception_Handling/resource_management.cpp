/*!
 *  \file       resource_management.cpp
 *  \brief
 *
 */


#include "resource_management.hpp"

#include <stdexcept>
#include <cstring>
#if defined(DEBUG)
    #include <iostream>
#endif
#include <memory>


void use_file(const char* fn)
{
    FILE* f = fopen(fn, "r");

    try
    {
        char array[0xFFFF] = {0x00};
        size_t read_buffer_size = fread(array, 0xFF, 0xFFFF, f);
    }
    catch (...)     // 捕获所有可能的异常
    {
        fclose(f);
        throw;
    }

    fclose(f);
}

FilePtr::FilePtr(const char* filename, const char* mode) : p{fopen(filename, mode)}
{
#if defined(DEBUG)
    std::cout << "Construct the FilePtr." << std::endl;
#endif
    if (p == nullptr)
    {
        throw std::runtime_error("FilePtr: Cannot open file");
    }
}

FilePtr::FilePtr(const std::string& filename, const char* mode) : FilePtr(filename.c_str(), mode)
{
}

FilePtr::FilePtr(FILE* fp) : p(fp)
{
    if (p == nullptr)
    {
        throw std::runtime_error("FilePtr: nullptr");
    }
}

FilePtr::~FilePtr()
{
#if defined(DEBUG)
    std::cout << "Destruct the FilePtr." << std::endl;
#endif
    fclose(p);
}

FilePtr::operator FILE*()
{
    return p;
}

void FilePtr::write(const std::string& content)
{
    const char* str = content.c_str();
    size_t len = fwrite(str, sizeof(char), content.size(), p);
    if (len != content.size())
    {
        fprintf(stderr, "fwrite() error: %zu\n", len);
        throw std::runtime_error(std::string(__FUNCTION__) + " error.");
    }
}

std::string FilePtr::read(size_t size)
{
    std::unique_ptr<char> content(new char[size]);
    std::memset(content.get(), 0x00, sizeof(char) * size);

    size_t len = fread(content.get(), sizeof(char), size, p);
    if (len != size)
    {
        fprintf(stderr, "fread() failed: %zu\n", len);
        throw std::runtime_error(std::string(__FUNCTION__) + " error.");
    }

    std::string ret(content.get());
    return ret;
}

LockedFileHandler::LockedFileHandler(const char* file, std::mutex& mtx) : p(file, "rw"), lck(mtx)
{
}
