#include "memory.h"
#include "memtrace.h"

/* null pointerekkel t�lti fel a heterog�n kollekci�t */
Memory::Memory(size_t range) : range(range) {
	for (size_t i = 0; i < range; ++i)
		memory.push_back(nullptr);
}

Memory::~Memory() {
	for (size_t i = 0; i < range; ++i) {
		delete memory[i];
	}
}

/* Mem�ri�hoz f�z egy mem�riacell�t */
void Memory::addElement(baseMemoryBlock* input) {
	for (size_t i = 0; i < range; ++i) {
		if (memory[i] == nullptr) {
			memory[i] = input;
			return;
		}
	}
	delete input;
	throw "tele a memoria";
}

/* Adott c�men l�v� mem�riacell�t t�r�l */
void Memory::removeElement(size_t adress) {
	if (adress >= range) throw "out of range";
	if (memory[adress] == nullptr) throw "already empty";
	delete memory[adress];
	memory[adress] = nullptr;
}

/* Ki�rja a mem�ria teljes tartalm�t egy stream-re */
void Memory::memoryDump(std::ostream& o_stream) {
	for (size_t i = 0; i < range; ++i) {
		if (memory[i] != nullptr) {
			o_stream << "memory[" << i << "]: ";
			memory[i]->print();
		}
		else o_stream << "memory[" << i << "]: invalid data!" << std::endl;
	}
}

/* Tesztel�shez file-ba �rja a mem�ria egy cell�j�t */
void Memory::testPrint(size_t adress) const {
	if (memory[adress] == nullptr) throw "ures cella";
	memory[adress]->testPrint();
}

/* A mem�ria egyik cell�j�t �rja ki */
void Memory::accessAddress(size_t adress, std::ostream& o_stream) {
	if (adress >= range) throw "rossz index";
	if (memory[adress] == nullptr) o_stream << "invalid data!" << std::endl;
	else memory[adress]->print(o_stream);
}

/*
	Miut�n egy perif�ria kimentette az adat�t egy file-ba, ez
	a f�ggv�ny olvassa be �s t�rolja el a mem�ri�ban a perif�ria
	adat�t a t�mogatott adatt�pusok alapj�n
*/
void Memory::saveDataToMemory(TYPE type) {
	for (size_t i = 0; i < range; ++i) {
		if (memory[i] == nullptr) {
			switch (type) {
			case (Int): {
				std::vector<int> data;
				baseMemoryBlock* mem = new memoryBlock<int>(data, Int);
				mem->read();
				memory[i] = mem;
				return;
			}
			case (Float): {
				std::vector<float> data;
				baseMemoryBlock* mem = new memoryBlock<float>(data, Float);
				mem->read();
				memory[i] = mem;
				return;
			}
			case (Char): {
				std::vector<char> data;
				baseMemoryBlock* mem = new memoryBlock<char>(data, Char);
				mem->read();
				memory[i] = mem;
				return;
			}
			case(String): {
				std::vector<std::string> data;
				baseMemoryBlock* mem = new memoryBlock<std::string>(data, String);
				mem->read();
				memory[i] = mem;
				return;
			}
			case(Undefined): {
				break;
			}
			}
		}
	}
	throw "memory is full";
}