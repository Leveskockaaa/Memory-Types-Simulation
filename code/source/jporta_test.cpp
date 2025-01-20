#include <iostream>
#include "define.h"
#include "memory.h"
#include "peripheral.h"
#include "processor.h"

#include "memtrace.h"

int main()
{
	Processor cpu("cpu_core");
	Memory memory;
	PeripheralHUB hub;

	std::vector<int> int_vector = { 1, 2, 3, 5 };
	std::vector<char> char_vector = { 'c', 'o', 'r', 'e', 'i', '3' };
	std::vector<float> float_vector = { 3.f, 3.1f, 3.14f };
	std::vector<std::string> string_vector = { "cpp", "ctor", "dtor", "goesbrr" };

	basePeripheral* int_per = new Peripheral<int>(int_vector, "eger", Int);
	basePeripheral* char_per = new Peripheral<char>(char_vector, "billentyuzet", Char);
	basePeripheral* float_per = new Peripheral<float>(float_vector, "kamera", Float);
	basePeripheral* string_per = new Peripheral<std::string>(string_vector, "billentyuzet", String);
	
	baseMemoryBlock* int_mem = new memoryBlock<int>(int_vector, Int);
	baseMemoryBlock* char_mem = new memoryBlock<char>(char_vector, Char);
	baseMemoryBlock* float_mem = new memoryBlock<float>(float_vector, Float);
	baseMemoryBlock* string_mem = new memoryBlock<std::string>(string_vector, String);

	int_per->print();
	char_per->print();
	float_per->print();
	string_per->print();
	
	std::cout << std::endl;

	int_mem->print();
	char_mem->print();
	float_mem->print();
	string_mem->print();

	std::cout << std::endl;

	cpu.addVectorToHub(hub, int_vector, "eger", Int);
	cpu.addVectorToHub(hub, char_vector, "billentyuzet", Char);
	cpu.addVectorToHub(hub, float_vector, "kamera", Float);
	cpu.addVectorToHub(hub, string_vector, "billentyuzet", String);

	cpu.addVectorToMemory(memory, int_vector, Int);
	cpu.addVectorToMemory(memory, char_vector, Char);

	cpu.peripheralPrint(0, hub);
	cpu.peripheralPrint(1, hub);
	cpu.peripheralPrint(2, hub);
	cpu.peripheralPrint(3, hub);

	std::cout << std::endl;

	cpu.memoryPrint(0, memory);
	cpu.memoryPrint(1, memory);

	cpu.storeDataToMemory(2, hub, memory);
	cpu.storeDataToMemory(3, hub, memory);

	cpu.memoryPrint(2, memory);
	cpu.memoryPrint(3, memory);
	
	std::cout << std::endl;

	cpu.removeHubElement(hub, 0);
	cpu.peripheralPrint(0, hub);
	
	cpu.removeMemElement(memory, 3);
	cpu.memoryPrint(3, memory);

	std::cout << std::endl;

	cpu.memoryDump(memory);
	std::cout << std::endl;
	cpu.peripheralDump(hub);
	std::cout << std::endl;
	
	delete int_per;
	delete char_per;
	delete float_per;
	delete string_per;

	delete int_mem;
	delete char_mem;
	delete float_mem;
	delete string_mem;
}