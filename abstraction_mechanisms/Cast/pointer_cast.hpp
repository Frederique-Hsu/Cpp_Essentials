/*!
 *  \file       pointer_cast.hpp
 *  \brief      
 *  
 */


#pragma once

#include <memory>

template<class TargetType, class SourceType> 
std::shared_ptr<TargetType> static_pointer_cast(const std::shared_ptr<SourceType>& src_obj_ptr) noexcept;

template<class TargetType, class SourceType>
std::shared_ptr<TargetType> dynamic_pointer_cast(const std::shared_ptr<SourceType>& src_obj_ptr) noexcept;

template<class TargetType, class SourceType>
std::shared_ptr<TargetType> const_pointer_cast(const std::shared_ptr<SourceType>& src_obj_ptr) noexcept;

template<class TargetType, class SourceType>
std::shared_ptr<TargetType> reinterpret_pointer_cast(const std::shared_ptr<SourceType>& src_obj_ptr) noexcept;

template<class TargetType, class SourceType>
std::shared_ptr<TargetType> static_pointer_cast(std::shared_ptr<SourceType>&& src_obj_ptr) noexcept;

template<class TargetType, class SourceType>
std::shared_ptr<TargetType> dynamic_pointer_cast(std::shared_ptr<SourceType>&& src_obj_ptr) noexcept;

template<class TargetType, class SourceType>
std::shared_ptr<TargetType> const_pointer_cast(std::shared_ptr<SourceType>&& src_obj_ptr) noexcept;

template<class TargetType, class SourceType>
std::shared_ptr<TargetType> reinterpret_pointer_cast(std::shared_ptr<SourceType>&& src_obj_ptr) noexcept;

#include "pointer_cast_impl.hpp"