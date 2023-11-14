//*****************************************************************************
//*                                                                           *
//*                      Cho sanghyun's Game Classes II                       *
//*                       Ver 6.1 / Release 2012.05.28                        *
//*                                                                           *
//*                           Data Template Classes                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*                                                                           *
//*  This Program is programmed by Cho SangHyun. sangducks@gmail.com          *
//*  Best for Game Developement and Optimized for Game Developement.          *
//*                                                                           *
//*                   (C) 2008 CGLabs All right reserved.                     *
//*                           http://www.CGDK.co.kr                           *
//*                                                                           *
//*****************************************************************************

#pragma once
//-----------------------------------------------------------------------------
//
// CGDK::span
//
//-----------------------------------------------------------------------------
#include "cgdk/sdk10/containers/_definitions.h"

namespace CGDK
{

template <class _TTYPE>
class span
{
public:
public:
    using element_type     = _TTYPE;
    using value_type       = std::remove_cv_t<_TTYPE>;
    using size_type        = size_t;
    using difference_type  = ptrdiff_t;
    using pointer          = _TTYPE*;
    using const_pointer    = const _TTYPE*;
    using reference        = _TTYPE&;
    using const_reference  = const _TTYPE&;
    using iterator         = _Span_iterator<_TTYPE>;
    using reverse_iterator = std::reverse_iterator<iterator>;

public:
    constexpr span() noexcept {}
    constexpr span(pointer _Ptr, size_type _ICOUNT) noexcept : _Mybase(_Ptr, _ICOUNT) {}
    constexpr span(pointer _First, pointer _Last) noexcept : _Mybase(_First, static_cast<size_type>(_Last - _First)) { _Adl_verify_range(_First, _Last); }

    template <size_t _ISIZE>
    constexpr span(element_type (&_array)[_ISIZE]) noexcept : _Mybase(_array, _ISIZE) {}

    template <class _TOTHER_TYPE, size_t _ISIZE>
    constexpr span(array<_TOTHER_TYPE, _ISIZE>& _array) noexcept : _Mybase(_array.data(), _ISIZE) {}

    template <class _TOTHER_TYPE, size_t _ISIZE, std::is_convertible<const _TOTHER_TYPE(*)[], element_type (*)[]>>, int> = 0>
    constexpr span(const array<_TOTHER_TYPE, _ISIZE>& _array) noexcept : _Mybase(_array.data(), _ISIZE) {}

    template <class _TRANGE, std::enable_if_t<_Is_span_compatible_range<_TRANGE, element_type>, int> = 0>
    constexpr span(_TRANGE& _range) : _Mybase(_STD data(_range), static_cast<size_type>(_STD size(_range))) {}
    template <class _TRANGE, std::enable_if_t<_Is_span_compatible_range<const _TRANGE, element_type>, int> = 0>
    constexpr span(const _TRANGE& _range) : _Mybase(_STD data(_range), static_cast<size_type>(_STD size(_range))) {}

    // [span.sub] Subviews
    template <size_t _ICOUNT>
    _NODISCARD constexpr auto                   first() const noexcept { return span<element_type, _ICOUNT>{_Mydata, _ICOUNT}; }
    [[no_discard]] constexpr auto               first(const size_type _ICOUNT) const noexcept { return span<element_type, dynamic_extent>{_Mydata, _ICOUNT}; }
    template <size_t _ICOUNT>
    [[no_discard]] constexpr auto               last() const noexcept
    {
        if constexpr (_Extent != dynamic_extent) 
        {
            static_assert(_ICOUNT <= _Extent, "Count out of range in span::last()");
        }
        return span<element_type, _ICOUNT>{_Mydata + (_Mysize - _ICOUNT), _ICOUNT};
    }
    [[no_discard]] constexpr auto               last(const size_type _ICOUNT) const noexcept
    {
        return span<element_type, dynamic_extent>{_Mydata + (_Mysize - _ICOUNT), _ICOUNT};
    }

    template <size_t _IOFFSET, size_t _ICOUNT = dynamic_extent>
    [[no_discard]] constexpr auto subspan() const noexcept
    {
        if constexpr (_Extent != dynamic_extent) 
        {
            static_assert(_IOFFSET <= _Extent, "Offset out of range in span::subspan()");
            static_assert(_ICOUNT == dynamic_extent || _ICOUNT <= _Extent - _IOFFSET, "Count out of range in span::subspan()");
        }
        using _ReturnType = span<element_type, _ICOUNT != dynamic_extent ? _ICOUNT : (_Extent != dynamic_extent ? _Extent - _IOFFSET : dynamic_extent)>;
        return _ReturnType{_Mydata + _IOFFSET, _ICOUNT == dynamic_extent ? _Mysize - _IOFFSET : _ICOUNT};
    }

    [[no_discard]] constexpr auto               subspan(const size_type _IOFFSET, const size_type _ICOUNT = dynamic_extent) const noexcept
    {
        using _ReturnType = span<element_type, dynamic_extent>;
        return _ReturnType{_Mydata + _IOFFSET, _ICOUNT == dynamic_extent ? _Mysize - _IOFFSET : _ICOUNT};
    }

    // [span.obs] Observers
    [[no_discard]] constexpr size_t             size() const noexcept { return _Mysize; }
    [[no_discard]] constexpr size_type          size_bytes() const noexcept { return _Mysize * sizeof(element_type); }
    [[no_discard]] constexpr bool               empty() const noexcept { return _Mysize == 0; }

    // [span.elem] Element access
    [[no_discard]] constexpr reference operator[](const size_type _Off) const noexcept { return _Mydata[_Off]; }
    [[no_discard]] constexpr reference          front() const noexcept { return _Mydata[0]; }
    [[no_discard]] constexpr reference          back() const noexcept { return _Mydata[_Mysize - 1]; }

    [[no_discard]] constexpr pointer            data() const noexcept { return _Mydata; }
    [[no_discard]] constexpr iterator           begin() const noexcept { return {_Mydata}; }
    [[no_discard]] constexpr iterator           end() const noexcept { const auto _End = _Mydata + _Mysize; return {_End}; }
    [[no_discard]] constexpr reverse_iterator   rbegin() const noexcept { return reverse_iterator{end()}; }
    [[no_discard]] constexpr reverse_iterator   rend() const noexcept { return reverse_iterator{begin()}; }
};


}