/*!
 *  \file       Factory_Impl.hpp
 *  \brief
 *
 */


#include <cstdio>
#include <sstream>


#define ERROR(message)                                                                \
    {                                                                                 \
        std::ostringstream err;                                                       \
        err << "Fatal error.\n"                                                       \
            << " In function " << __func__ << " at line " << __LINE__ << " of file "  \
            << __FILE__ << "\n"                                                       \
            << message << std::endl;                                                  \
        std::fprintf(stderr, "%s\n", err.str().c_str());                              \
        std::exit(EXIT_FAILURE);                                                      \
    }


namespace detail
{
template<typename CreateObject>
typename BaseFactory<CreateObject>::CallbackConstIter
BaseFactory<CreateObject>::retrieve(const std::string& obj_id) const
{
    if (obj_id.empty())
    {
        ERROR("No object ID string provided to the Factory");
    }
    CallbackConstIter iter = m_callbacks.find(obj_id);
    if (iter == m_callbacks.end())
    {
        ERROR("The unknown object ID " + obj_id + " occurred in the Factory.");
    }
    return iter;
}

template<typename CreateObject>
bool BaseFactory<CreateObject>::registerObject(const std::string& obj_id,
                                               const CreateObject& functor)
{
    return m_callbacks.insert(CallbackPair(obj_id, functor)).second;
}

template<typename CreateObject>
bool BaseFactory<CreateObject>::unregisterObject(const std::string& obj_id)
{
    return m_callbacks.erase(obj_id) == 1;
}

template<typename CreateObject>
void BaseFactory<CreateObject>::subscribe(const std::string& obj_id,
                                          const CreateObject& functor)
{
    bool done = registerObject(obj_id, functor);
    if (!done)
    {
        ERROR("Subscription of object ID " + obj_id + " to factory failed!");
    }
}

template<typename CreateObject>
void BaseFactory<CreateObject>::unsubscribe(const std::string& obj_id)
{
    bool done = unregisterObject(obj_id);
    if (!done)
    {
        ERROR("Unsubscription of object ID " + obj_id + " from factory failed!");
    }
}
}

/*!
 *  \brief      Calls the appropriate creation functor, based on the passed objID
 *  \param[in]  objID the object's identification string
 *  \param[in]  data  input data for the creation of the object
 *  \tparam     ObjectInputArgs type(s) of the object creation callback function input arguments
 *  \note       Return type is deduced based on the type(s) of the input
 *              argument(s) template parameter pack and the type of the object creation
 *              callback function.
 */
template<typename CreateObject>
template<typename... ObjectInputArgs>
typename std::result_of<CreateObject(ObjectInputArgs...)>::type
Factory<CreateObject>::create(const std::string& obj_id, ObjectInputArgs... data) const
{
    return (this->retrieve(obj_id)->second)(data...);
}