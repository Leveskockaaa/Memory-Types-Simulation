#ifndef PRECESSOR_H
#define PROCESSOR_H

#include <iostream>
#include <vector>
#include "define.h"
#include "memory.h"
#include "peripheral.h"

/* A memória és a perifériák kezelésére szolgáló osztály */
class Processor {
	std::string name;
public:
	Processor(const char* input) : name(input) { }
	~Processor() { }

	template<typename Type>
	void addVectorToMemory(Memory& memory, std::vector<Type> vector, TYPE type) {
		baseMemoryBlock* mem = new memoryBlock<Type>(vector, type);
		try { memory.addElement(mem); }
		catch (const char*) {
			std::cout << "=== [ MEMORY FULL ] ===";
			delete mem;
		}
	}

	template<typename Type>
	void addVectorToHub(PeripheralHUB& hub, std::vector<Type> vector, std::string name, TYPE type) {

		basePeripheral* per = new Peripheral<Type>(vector, name, type);
		try { hub.addElement(per); }
		catch (const char*) {
			std::cout << "=== [ HUB FULL ] ===";
			delete per;
		}
	}

	void storeDataToMemory(size_t adress, PeripheralHUB& hub, Memory& memory);

	void memoryPrint(size_t adress, Memory& memory);
	void peripheralPrint(size_t adress, PeripheralHUB& hub);
	void testMemPrint(Memory& memory, size_t adress) const;
	void testPerPrint(PeripheralHUB& hub, size_t adress) const;

	void memoryDump(Memory& memory, std::ostream& o_stream = std::cout);
	void peripheralDump(PeripheralHUB& hub, std::ostream& o_stream = std::cout);

	void removeMemElement(Memory& memory, size_t adress);
	void removeHubElement(PeripheralHUB& hub, size_t adress);
};

#endif