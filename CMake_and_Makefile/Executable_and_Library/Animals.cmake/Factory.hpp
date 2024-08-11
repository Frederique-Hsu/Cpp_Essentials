/*!
 *  \file       Factory.hpp
 *  \brief
 *
 */


#pragma once

#include <map>
#include <string>
#include <type_traits>


namespace detail
{
template <typename CreateObject> class BaseFactory
{
private:
    typedef std::map<std::string, CreateObject> CallbackMap;
    typedef typename CallbackMap::value_type CallbackPair;
    typedef typename CallbackMap::const_iterator CallbackConstIter;

protected:
    CallbackMap m_callbacks;

private:
    bool registerObject(const std::string& obj_id, const CreateObject& functor);
    bool unregisterObject(const std::string& obj_id);

public:
    void subscribe(const std::string& obj_id, const CreateObject& functor);
    void unsubscribe(const std::string& obj_id);

protected:
    CallbackConstIter retrieve(const std::string& obj_id) const;
};
}

/*!
 *  \class      Factory
 *  \brief      C++11 implementation of the Factory Method
 *  \tparam     CreateObject type of the object creation callback function
 *  \details    Factory Method using a variadic template parameter pack to handle possible
 *              input value to the object creation callback function.
 */
template <typename CreateObject>
class Factory final : public detail::BaseFactory<CreateObject>
{
public:
    template <typename... ObjectInputArgs>
    typename std::result_of<CreateObject(ObjectInputArgs...)>::type create(const std::string& objID,
                                                                           ObjectInputArgs... data) const;
};


#include "Factory_Impl.hpp"