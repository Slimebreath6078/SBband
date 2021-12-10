#pragma once

#include <memory>
#include "load/item/item-loader-base.h"

enum class ItemLoaderVersionType;
class ItemLoaderBase;
class ItemLoaderFactory {
public:
    static std::shared_ptr<ItemLoaderBase> create_loader();

private:
    ItemLoaderFactory() = delete;
    static ItemLoaderVersionType get_version();
};
