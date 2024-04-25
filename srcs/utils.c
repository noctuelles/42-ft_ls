//
// Created by plouvel on 24/04/24.
//

#include "ft_ls.h"

bool
should_call_stat(const t_options *options) {
    if (options->long_listing_format || options->sort_by_time) {
        return (true);
    }
    return (false);
}
