#ifndef __MYOS__MULTITASKING__H
#define __MYOS__MULTITASKING__H

#include <common/types.h>
#include <gdt.h>
namespace myos{

	struct CPUState{

		//data register
		myos::common::uint32_t eax;
		myos::common::uint32_t ebx;
		myos::common::uint32_t ecx;
		myos::common::uint32_t edx;

		//pointer and indexed address register
		myos::common::uint32_t esi;
		myos::common::uint32_t edi;
		myos::common::uint32_t ebp;

		myos::common::uint32_t gs;
		myos::common::uint32_t fs;
		myos::common::uint32_t es;
		myos::common::uint32_t ds;

		myos::common::uint32_t error;

		myos::common::uint32_t eip;//instructor pointer
		myos::common::uint32_t cs;
		myos::common::uint32_t eflags;
		myos::common::uint32_t esp;//stack register
		myos::common::uint32_t ss;//segment register 
	}__attribute__((packed));

	
	class Task
	{

	friend class TaskManager;
	public:
		Task(GlobalDescriptorTable* gdt, void entrypoint());
		~Task();
	private:
		myos::common::uint8_t stack[4096]; //4k	
		CPUState* cpustate;
	};

	class TaskManager
	{
	public:
		TaskManager();
		~TaskManager();
		bool AddTask(Task* task);
		CPUState* Schedule(CPUState* cpustate);
	private:
		Task* tasks[256];
		int numTasks;
		int currentTask;	
	};



}






#endif


