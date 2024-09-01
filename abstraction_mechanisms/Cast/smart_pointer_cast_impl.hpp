/*!
 *  \file       smart_pointer_cast_impl.hpp
 *  \brief      
 *  
 */


#include <memory>

namespace my
{
    template<class TargetType, class SourceType>
    std::shared_ptr<TargetType> static_pointer_cast(const std::shared_ptr<SourceType>& src_obj_ptr) noexcept
    {
        auto ptr = static_cast<typename std::shared_ptr<TargetType>::element_type*>(src_obj_ptr.get());
        return std::shared_ptr<TargetType>{src_obj_ptr, ptr};
    }

    template<class TargetType, class SourceType>
    std::shared_ptr<TargetType> dynamic_pointer_cast(const std::shared_ptr<SourceType>& src_obj_ptr) noexcept
    {
        if (auto ptr = dynamic_cast<typename std::shared_ptr<TargetType>::element_type*>(src_obj_ptr.get()))
        {
            return std::shared_ptr<TargetType>{src_obj_ptr, ptr};
        }
        else
        {
            return std::shared_ptr<TargetType>{};
        }
    }

    template<class TargetType, class SourceType>
    std::shared_ptr<TargetType> const_pointer_cast(const std::shared_ptr<SourceType>& src_obj_ptr) noexcept
    {
        auto ptr = const_cast<typename std::shared_ptr<TargetType>::element_type*>(src_obj_ptr.get());
        return std::shared_ptr<TargetType>{src_obj_ptr, ptr};
    }

    template<class TargetType, class SourceType>
    std::shared_ptr<TargetType> reinterpret_pointer_cast(const std::shared_ptr<SourceType>& src_obj_ptr) noexcept
    {
        auto ptr = reinterpret_cast<typename std::shared_ptr<TargetType>::element_type*>(src_obj_ptr);
        return std::shared_ptr<TargetType>(src_obj_ptr, ptr);
    }

    template<class TargetType, class SourceType>
    std::shared_ptr<TargetType> static_pointer_cast(std::shared_ptr<SourceType>&& src_obj_ptr) noexcept
    {
        auto ptr = static_cast<typename std::shared_ptr<TargetType>::element_type*>(std::move(src_obj_ptr.get));
        return std::shared_ptr<TargetType>{src_obj_ptr, ptr};
    }
    
    template<class TargetType, class SourceType>
    std::shared_ptr<TargetType> dynamic_pointer_cast(std::shared_ptr<SourceType>&& src_obj_ptr) noexcept
    {
        if (auto ptr = dynamic_cast<typename std::shared_ptr<TargetType>::element_type*>(std::move(src_obj_ptr)))
        {
            return std::shared_ptr<TargetType>{src_obj_ptr, ptr};
        }
        else
        {
            return std::shared_ptr<TargetType>{};
        }
    }
    
    template<class TargetType, class SourceType>
    std::shared_ptr<TargetType> const_pointer_cast(std::shared_ptr<SourceType>&& src_obj_ptr) noexcept
    {
        auto ptr = const_cast<typename std::shared_ptr<TargetType>::element_type*>(src_obj_ptr);
        return std::shared_ptr<TargetType>{src_obj_ptr, ptr};
    }
    
    template<class TargetType, class SourceType>
    std::shared_ptr<TargetType> reinterpret_pointer_cast(std::shared_ptr<SourceType>&& src_obj_ptr) noexcept
    {
        auto ptr = reinterpret_cast<typename std::shared_ptr<TargetType>::element_type*>(src_obj_ptr);
        return std::shared_ptr<TargetType>{src_obj_ptr, ptr};
    }
}