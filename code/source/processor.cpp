#include "processor.h"
#include "memory.h"
#include "peripheral.h"
#include "memtrace.h"
#include "define.h"

/* periféria egy adott címén lévõ adatot tárol a memóriába */
void Processor::storeDataToMemory(size_t adress, PeripheralHUB& hub, Memory& memory) {
	basePeripheral* peri = hub.getPeripheral(adress);
	if (peri == nullptr) throw "nullptr";
	peri->write();
	std::ifstream file("serializable.txt");
	unsigned int type;
	file >> type;
	TYPE peri_type = static_cast<TYPE>(type);
	file.close();
	try {
		memory.saveDataToMemory(peri_type);
	}
	catch (const char*) {
		std::cout << "\n\n=== [ MEMORY OVERFLOW ] ===\n\n";
	}
}

/* kiír a memória egy címén lévõ adatot */
void Processor::memoryPrint(size_t adress, Memory& memory) {
	try {
		memory.accessAddress(adress);
	}
	catch (const char*) {
		std::cout << "\n\n=== [ OUT OF RANGE ] ===\n\n";
	}
}

/* kiír a hub egy címén lévõ adatot */
void Processor::peripheralPrint(size_t adress, PeripheralHUB& hub) {
	try {
		hub.accessAddress(adress);
	}
	catch (const char*) {
		std::cout << "\n\n=== [ OUT OF RANGE ] ===\n\n";
	}
}

/* teszteléshez file-ba írja a memória egy celláját */
void Processor::testMemPrint(Memory& memory, size_t adress) const {
	memory.testPrint(adress);
}

/* teszteléshez file-ba írja a hub egy celláját */
void Processor::testPerPrint(PeripheralHUB& hub, size_t adress) const {
	hub.testElement(adress);
}

/* memóriadump-ot hív a megfelelõ memória példányon */
void Processor::memoryDump(Memory& memory, std::ostream& o_stream) {
	memory.memoryDump(o_stream);
}

/* perifériadump-ot hív a megfelelõ hub példányon */
void Processor::peripheralDump(PeripheralHUB& hub, std::ostream& o_stream) {
	hub.peripheralDump(o_stream);
}

/* egy adott címen lévõ memóriacellát töröl */
void Processor::removeMemElement(Memory& memory, size_t adress) {
	try { memory.removeElement(adress); }
	catch (const char*) { std::cout << "=== [ ERROR ] ==="; }
}

/* egy adott címen lévõ perifériát töröl */
void Processor::removeHubElement(PeripheralHUB& hub, size_t adress) {
	try { hub.removeElement(adress); }
	catch (const char*) { std::cout << "=== [ ERROR ] ==="; }
}