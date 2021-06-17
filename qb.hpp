#ifndef H_QWENDUBASE
#define H_QWENDUBASE
#include <cstddef>
#include <stdlib.h>

//--------------------------------------------------------------------------------------------------
// Defines
//
#define LIKELY(x) __builtin_expect(!!(x), 1)
#define UNLIKELY(x) __builtin_expect(!!(x), 0)









//-----------------------------------------------------------------------------------------------
//Allocators
//


template<typename T = void>
struct Typed_Blk;
typedef Typed_Blk<> Blk;

template<typename T>
struct Typed_Blk{
	T* ptr = nullptr;
	size_t size = 0;
};

template<typename PRIMARY, typename FALLBACK>
struct Fallocator{
	PRIMARY primary_;
	FALLBACK fallback_;
	Blk allocate(size_t size){
		Blk allocation = primary_.allocate(size);
		if(allocation.ptr != nullptr) return allocation;
		return fallback_.allocate(size);
	};
	void deallocate(Blk& block){
		if(primary_.owns(block)){
		       	primary_.deallocate(block);
			return;
		}
		fallback_.deallocate(block);
	};
	bool owns(Blk& block){
		return primary_.ows(block) || fallback_.owns(block);
	};
};

struct Mallocator{
	Blk allocate(size_t size){
		return {malloc(size), size};
	};
	void deallocate(Blk& block){
		if(block.ptr == nullptr) return;
		free(block.ptr);
	};
	bool owns(Blk& block){
		return (bool)block.ptr;
	};
};

template<size_t SIZE>
struct Stacklocator{
	char space_[SIZE];
	char* top_;
	
	Stacklocator():top_(space_){};	
	Blk allocate(size_t size_to_allocate){
		if(top_ + size_to_allocate <= space_ + SIZE){
			Blk allocation = {top_, size_to_allocate};
			top_ += size_to_allocate;
			return allocation;
		};
		return {nullptr, 0};
	};
	void deallocate(Blk& block){
		if(!owns(block)) return;
		if(isLastAllocationInStack(block)){

			top_ -= block.size;
			block.ptr = nullptr;
		}
		//If it wasnt the last allocation dont do anything
	};	
	bool owns(Blk& block){
		return block.ptr >= space_ && (char*)block.ptr + block.size <= top_ && (char*)block.ptr + block.size <= space_ + SIZE;
	};
	size_t constexpr size(){return SIZE;};
	size_t remaining(){
		return SIZE - (size_t)(top_ - space_);
	};
	bool isLastAllocationInStack(Blk& block){
		return (char*)block.ptr + block.size == top_;
	};
};

enum CHOOSEMODE {LOWER, LARGER, LOWEREQ, LARGEREQ, EQ};

template<typename PRIMARY, typename FALLBACK, size_t SPLITVALUE, CHOOSEMODE MODE = LOWER>
struct Choosocator{
	PRIMARY primary_;
	FALLBACK fallback_;
	Choosocator();
	Blk allocate(size_t size){
		if constexpr (MODE == LOWER){
			Blk allocation = {nullptr, 0};
			if(size < SPLITVALUE){
				
				allocation = primary_.allocate(size);
				if(allocation.ptr != nullptr) return allocation;
			}
			return fallback_.allocate(size);

		} else if constexpr(MODE == LARGER){
		
		
		} else if constexpr (MODE == EQ){
			
		}
	};
	void deallocate(Blk& block);
	bool owns(Blk& block);
};






#endif
