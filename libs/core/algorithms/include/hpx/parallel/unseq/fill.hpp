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

#include <cstddef>
#include <type_traits>
#include <utility>

namespace hpx { namespace parallel { inline namespace v1 { namespace detail {

    ///////////////////////////////////////////////////////////////////////////
    struct unseq_fill_t
    {
        template <typename ExPolicy, typename Iter, typename Sent, typename T>
        HPX_HOST_DEVICE HPX_FORCEINLINE static Iter
        call(ExPolicy&& policy, Iter first, Sent last, T const& val)
        {
            std::cout << "\n Unseq fill (algorithms/unseq) \n" << std::endl;
            for (; first != last; ++first)
            {
                *first = val;
            }
            return first;
        }
    };

    template <typename ExPolicy, typename Iter, typename Sent, typename T,
        HPX_CONCEPT_REQUIRES_(
            hpx::is_unsequenced_execution_policy_v<ExPolicy>)>
    HPX_HOST_DEVICE HPX_FORCEINLINE Iter tag_invoke(sequential_fill_t,
        ExPolicy&& policy, Iter first, Sent last, T const& value)
    {
        std::cout << "Unseq impl was called 1" << std::endl;
        return unseq_fill_t::call(
            HPX_FORWARD(ExPolicy, policy), first, last, value);
    }

}}}}    // namespace hpx::parallel::v1::detail
