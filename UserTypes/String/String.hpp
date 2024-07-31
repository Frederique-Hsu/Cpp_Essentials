/*!
 *  \file       String.hpp
 *  \brief
 *
 */


#pragma once

#include <cstddef>
#include <iostream>

class String
{
public:
    String();
    /* explicit */ String(const char* str);
    String(const String& rhs);
    String(String&& rhs);
    String& operator=(const String& rhs);
    String& operator=(String&& rhs);
    ~String();

private:
    static const int short_max = 15;

    std::size_t sz;
    char* ptr;
    union {
        int space;
        char ch[short_max + 1];
    };

public:
    char& operator[](int n);
    char  operator[](int n) const;

    char& at(int n);
    char  at(int n) const;

    String& operator+=(char c);
    String& operator+=(const char* str);

    char* c_str();
    const char* c_str() const;

    int size() const;
    int capacity() const;
    bool is_empty() const;

private:
    void check(int n) const;
    void copy_from(const String& other);
    void move_from(String& other);
};

std::ostream& operator<<(std::ostream& os, const String& str);
std::istream& operator>>(std::istream& is,       String& str);
bool operator==(const String& a, const String& b);
bool operator==(const String& a, const char* str);
bool operator==(const char* str, const String& b);
bool operator!=(const String& a, const String& b);
bool operator< (const String& a, const String& b);
bool operator<=(const String& a, const String& b);
bool operator> (const String& a, const String& b);
bool operator>=(const String& a, const String& b);

char* begin(String& str);
char* end(String& str);
const char* begin(const String& str);
const char* end(const String& str);

String& operator+=(String& a, const String& b);
String  operator+(const String& a, const String& b);

String operator"" _s(const char* str, std::size_t);

extern void (*visit)(const char*);
extern void (*access)(const String&);