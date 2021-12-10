#pragma once

#include "load/item/item-loader-base.h"

struct object_type;
class ItemLoader1 : public ItemLoaderBase {
public:
    ItemLoader1() = default;
    void rd_item(object_type *o_ptr) override;
};
