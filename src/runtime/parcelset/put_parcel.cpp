//  Copyright (c) 2016 Thomas Heller
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <hpx/config.hpp>

#if defined(HPX_HAVE_NETWORKING)
#include <hpx/parcelset/parcelhandler.hpp>
#include <hpx/runtime/parcelset/put_parcel.hpp>
#include <hpx/runtime_distributed.hpp>

#include <utility>

namespace hpx::parcelset {

    namespace detail {

        void put_parcel_handler::operator()(parcelset::parcel&& p) const
        {
            parcelset::parcelhandler& ph =
                hpx::get_runtime_distributed().get_parcel_handler();
            ph.put_parcel(HPX_MOVE(p));
        }
    }    // namespace detail

    void put_parcel(parcelset::parcel&& p, write_handler_type&& f)
    {
        parcelset::parcelhandler& ph =
            hpx::get_runtime_distributed().get_parcel_handler();
        ph.put_parcel(HPX_MOVE(p), HPX_MOVE(f));
    }

    void sync_put_parcel(parcelset::parcel&& p)
    {
        parcelset::parcelhandler& ph =
            hpx::get_runtime_distributed().get_parcel_handler();
        ph.sync_put_parcel(HPX_MOVE(p));
    }
}    // namespace hpx::parcelset

#endif
