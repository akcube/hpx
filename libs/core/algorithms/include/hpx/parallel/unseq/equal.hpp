//  Copyright (c) 2022 A Kishore Kumar
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <hpx/config.hpp>

#include <hpx/execution/traits/is_execution_policy.hpp>
#include <hpx/functional/tag_invoke.hpp>
#include <hpx/parallel/algorithms/detail/fill.hpp>
#include <hpx/parallel/util/result_types.hpp>
#include <hpx/parallel/unseq/loop.hpp>

#include <hpx/parallel/algorithms/detail/distance.hpp>
#include <hpx/parallel/algorithms/detail/equal.hpp>
#include <hpx/parallel/util/result_types.hpp>
#include <hpx/parallel/util/zip_iterator.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>

namespace hpx { namespace parallel { inline namespace v1 { namespace detail {

    ///////////////////////////////////////////////////////////////////////////
    template <typename ExPolicy>
    struct unseq_equal
    {
        template <typename InIter1, typename InIter2, typename F>
        HPX_HOST_DEVICE HPX_FORCEINLINE static bool call(
            InIter1 first1, InIter1 last1, InIter2 first2, F&& f)
        {
            HPX_IVDEP HPX_UNROLL HPX_VECTORIZE
            for (/* */; first1 != last1; (void) ++first1, ++first2)
            {
                if (!HPX_INVOKE(f, *first1, *first2))
                    return false;
            }
            return true;
        }
    };

    template <typename ExPolicy, typename ZipIterator, typename Token,
        typename F,
        HPX_CONCEPT_REQUIRES_(
            hpx::is_unsequenced_execution_policy_v<ExPolicy>)>
    HPX_HOST_DEVICE HPX_FORCEINLINE void tag_invoke(
        sequential_equal_t<ExPolicy>, ZipIterator it, std::size_t part_count,
        Token& tok, F&& f)
    {
            return unseq_equal<ExPolicy>::call(
                it, part_count, tok, HPX_FORWARD(F, f));
    }

    template <typename ExPolicy, typename InIter1, typename InIter2, typename F,
        HPX_CONCEPT_REQUIRES_(
            hpx::is_unsequenced_execution_policy_v<ExPolicy>)>
    HPX_HOST_DEVICE HPX_FORCEINLINE bool tag_invoke(
        sequential_equal_t<ExPolicy>, InIter1 first1, InIter1 last1,
        InIter2 first2, F&& f)
    {
            return unseq_equal<ExPolicy>::call(
                first1, last1, first2, HPX_FORWARD(F, f));
    }

}}}}    // namespace hpx::parallel::v1::detail