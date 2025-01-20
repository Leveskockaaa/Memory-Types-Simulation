#include "processor.h"
#include "memory.h"
#include "peripheral.h"
#include "memtrace.h"
#include "define.h"

/* perif�ria egy adott c�m�n l�v� adatot t�rol a mem�ri�ba */
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

/* ki�r a mem�ria egy c�m�n l�v� adatot */
void Processor::memoryPrint(size_t adress, Memory& memory) {
	try {
		memory.accessAddress(adress);
	}
	catch (const char*) {
		std::cout << "\n\n=== [ OUT OF RANGE ] ===\n\n";
	}
}

/* ki�r a hub egy c�m�n l�v� adatot */
void Processor::peripheralPrint(size_t adress, PeripheralHUB& hub) {
	try {
		hub.accessAddress(adress);
	}
	catch (const char*) {
		std::cout << "\n\n=== [ OUT OF RANGE ] ===\n\n";
	}
}

/* tesztel�shez file-ba �rja a mem�ria egy cell�j�t */
void Processor::testMemPrint(Memory& memory, size_t adress) const {
	memory.testPrint(adress);
}

/* tesztel�shez file-ba �rja a hub egy cell�j�t */
void Processor::testPerPrint(PeripheralHUB& hub, size_t adress) const {
	hub.testElement(adress);
}

/* mem�riadump-ot h�v a megfelel� mem�ria p�ld�nyon */
void Processor::memoryDump(Memory& memory, std::ostream& o_stream) {
	memory.memoryDump(o_stream);
}

/* perif�riadump-ot h�v a megfelel� hub p�ld�nyon */
void Processor::peripheralDump(PeripheralHUB& hub, std::ostream& o_stream) {
	hub.peripheralDump(o_stream);
}

/* egy adott c�men l�v� mem�riacell�t t�r�l */
void Processor::removeMemElement(Memory& memory, size_t adress) {
	try { memory.removeElement(adress); }
	catch (const char*) { std::cout << "=== [ ERROR ] ==="; }
}

/* egy adott c�men l�v� perif�ri�t t�r�l */
void Processor::removeHubElement(PeripheralHUB& hub, size_t adress) {
	try { hub.removeElement(adress); }
	catch (const char*) { std::cout << "=== [ ERROR ] ==="; }
}