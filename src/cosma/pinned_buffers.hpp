#ifdef COSMA_HAVE_GPU
#pragma once
#include <unordered_map>
#include <memory>

#include <Tiled-MM/util.hpp>

// container of pinned buffers
class pinned_buffers {
    struct deleter {
        void operator()(void* p) const {
            check_runtime_status(gpu::runtime_api::host_unregister(p));
        }
    };
    using pin_ptr_t = std::unique_ptr<void, deleter>;

    struct item {
        pin_ptr_t ptr;
        size_t size;
    };

    std::unordered_map<void*, item> items_;

  public:
    template <class T>
    void add(T* ptr, std::size_t size);

    void clear() { items_ = {}; }
};
#endif
