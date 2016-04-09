#ifndef SRC_NOT_ON_HEAP_H_
#define SRC_NOT_ON_HEAP_H_

#include <iostream>

struct not_on_heap {
    static void* operator new(std::size_t sz){
    	throw std::bad_alloc{};
    }
    static void* operator new[](std::size_t sz){
    	throw std::bad_alloc{};
    }
    static void operator delete(void *ptr) noexcept  {
    	// do nothing, never called, but should come in pairs
    }
    static void operator delete[](void *ptr) noexcept {
    	// do nothing, never called, but should come in pairs
    }
};

struct noh_extended: not_on_heap{
	noh_extended():x{10}{}
	int x;
};


#endif /* SRC_NOT_ON_HEAP_H_ */
