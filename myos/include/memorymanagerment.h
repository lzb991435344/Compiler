#ifndef __MYOS__MEMORYMANAGERMENT_H 
#define __MYOS__MEMORYMANAGERMENT_H


#include <common/types.h>

struct MemoryChunk{
	MemoryChunk* next;
	MemoryChunk* prev;
	bool allocated;
	myos::common::size_t size;
};


class MemoryManage
{
public:
	MemoryManage(myos::common::size_t first, myos::common::size_t size);
	~MemoryManage();

	static MemoryManage* activeMemoryManager;

	void* malloc(myos::common::size_t size);
	void free(void* ptr);
protected:
	MemoryChunk* first;	
};


#endif