#include <memorymanagerment.h>

using namespace myos;
using namespace myos::common;



MemoryManage* MemoryManage::activeMemoryManager = 0;

MemoryManage::MemoryManage(size_t start, size_t size){
	activeMemoryManager = this;

	if(size < sizeof(MemoryChunk)){
		first = 0;
	}else{
		first = (MemoryChunk*)start;
		first->allocated = false;
		first->prev = 0;
		first->next = 0;
		first->size = size - sizeof(MemoryChunk);
	}
	

}
MemoryManage::~MemoryManage(){
	if(activeMemoryManager == this){
		activeMemoryManager = 0;
	}
}


void* MemoryManage::malloc(size_t size){
	MemoryChunk* result = 0;
	for(MemoryChunk* chunk =  first; chunk != 0; chunk = chunk->next){
		if(chunk->size > size && !chunk->allocated){
			result = chunk;
		}
	}

	if(result = 0){
		return 0;
	}

	if(result->size >= size + sizeof(MemoryChunk) + 1){

		MemoryChunk* temp = (MemoryChunk*)((size_t)result + size);
		temp->allocated = false;

		temp->size = result->size - size - sizeof(MemoryChunk);
		temp->prev = result;
		temp->next = result->next;
		if(temp->next != 0){
			temp->next->prev = temp;
		}
		result->size = size;
		result->next = temp;	
	}

	result->allocated = true;

	return (void*)(((size_t)result) + sizeof(MemoryChunk));
}
void MemoryManage::free(void* ptr){
	MemoryChunk* chunk = (MemoryChunk*)((size_t)ptr - sizeof(MemoryChunk));
	
	chunk->allocated = false;

	//prev 
	if(chunk->prev != 0 && !chunk->prev->allocated){
		chunk->prev->next = chunk->next;

		//修改块的大小
		chunk->prev->size += chunk->size + sizeof(MemoryChunk);
		//修改前驱指向
		if(chunk->next != 0){
			chunk->next->prev = chunk->prev;
		}

		chunk = chunk->prev;
	}

	//next
	if(chunk->next != 0 && !chunk->next->allocated){
		chunk->size += chunk->next->size + sizeof(MemoryChunk);
		chunk->next = chunk->next->next;

		if(chunk->next != 0){
			chunk->next->prev = chunk;
		} 
	}
}

void* operator new(unsigned size){
	if(myos::MemoryManage::activeMemoryManager == 0){
		return 0;
	}
	return myos::MemoryManage::activeMemoryManager->malloc(size);
}
void* operator new[](unsigned size){
	if(myos::MemoryManage::activeMemoryManager == 0){
		return 0;
	}
	return myos::MemoryManage::activeMemoryManager->malloc(size);
}

void* operator new(unsigned size, void* ptr){
	return ptr;
}


void* operator new[](unsigned size, void* ptr){
	return ptr;
}

void operator delete(void* ptr){
	if(myos::MemoryManage::activeMemoryManager != 0){
		myos::MemoryManage::activeMemoryManager->free(ptr);
	}
}
void operator delete[](void* ptr){
	if(myos::MemoryManage::activeMemoryManager != 0){
		myos::MemoryManage::activeMemoryManager->free(ptr);
	}
}