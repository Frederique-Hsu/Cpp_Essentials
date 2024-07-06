/*!
 *  \file       resource_management.hpp
 *  \brief
 *
 */


#pragma once

#include <cstdio>
#include <string>
#include <mutex>

/*!
 *  \subsection 资源管理
 *
 *  \details    当函数请求某种资源时，也就是说，当它打开文件、从自由存储中分配一些内存或者一个互斥锁时，系统
 *              常常要求这些资源能在未来某个时刻被正确地释放调。
 *
 *              所谓“正确地释放掉”是指函数应该在返回它的调用者之前释放掉它请求的资源。
 */

void use_file(const char* fn);

class FilePtr
{
private:
    FILE* p;
public:
    FilePtr(const char* filename, const char* mode);
    FilePtr(const std::string& filename, const char* mode);
    explicit FilePtr(FILE* fp);
    ~FilePtr();
public:
    operator FILE*();
    void write(const std::string& content);
    std::string read(size_t size);
};

class LockedFileHandler
{
private:
    FilePtr p;
    std::unique_lock<std::mutex> lck;
public:
    LockedFileHandler(const char* file, std::mutex& mtx);
};

template<typename FnType>
struct FinalAction
{
    FinalAction(FnType f);
    ~FinalAction();

    FnType clean;
};

template<typename FnType>
FinalAction<FnType>::FinalAction(FnType f) : clean{f}
{
}

template<typename FnType>
FinalAction<FnType>::~FinalAction()
{
    clean();
}

template<typename FnType>
FinalAction<FnType> finally(FnType f)
{
    return FinalAction<FnType>(f);
}
