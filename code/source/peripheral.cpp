#include "peripheral.h"
#include "define.h"
#include "memtrace.h"

/*
	PeripheralHUB konstruktor
	a define.h-ban definiált maximum csatlakoztatható perifériák
	számának megfelelõ mennyiségû null pointer-rel feltölti a
	heterogén kollekciót
*/
PeripheralHUB::PeripheralHUB(size_t range) : range(range) {
	for (size_t i = 0; i < range; ++i)
		hub.push_back(nullptr);
}

PeripheralHUB::~PeripheralHUB() {
	for (size_t i = 0; i < range; ++i) {
		delete hub[i];
	}
}

/*
	addElement - hozzáad egy perifériát a heterogén kollekcióhoz
	@param input basePeripheral* = a tárolni kívánt perifériára mutató pointer
*/
void PeripheralHUB::addElement(basePeripheral* input) {
	for (size_t i = 0; i < range; ++i) {
		if (hub[i] == nullptr) {
			hub[i] = input;
			return;
		}
	}
	delete input;
	throw "tele a hub";
}

/*
	removeElement - egy adott helyen lévõ perifériát töröl
	a heterogén kollekcióból
	@param adress size_t = a törölni kívánt adat sorszáma
*/
void PeripheralHUB::removeElement(size_t adress) {
	if (adress >= range) throw "out of range";
	if (hub[adress] == nullptr) throw "already empty";
	delete hub[adress];
	hub[adress] = nullptr;
}

/*
	getter, egy perifériára mutató pointer-t ad vissza
	@param adress size_t = a kért periféria sorszáma
*/
basePeripheral* PeripheralHUB::getPeripheral(size_t adress) const {
	if (hub[adress] == nullptr) return nullptr;
	else return hub[adress];
}

/* A perifériákat tartalmazó hub dump-ja */
void PeripheralHUB::peripheralDump(std::ostream& stream) {
	for (size_t i = 0; i < range; ++i) {
		if (hub[i] != nullptr) {
			stream << "HUB[" << hub[i]->getName() << "]: ";
			hub[i]->print();
		}
		else stream << "HUB[" << i << "]: invalid data!" << std::endl;
	}
}

/* Eléri a perifériahub egyik elemét és kiírja a megadott stream-re */
void PeripheralHUB::accessAddress(size_t adress, std::ostream& o_stream) {
	if (adress >= range) throw "rossz index";
	if (hub[adress] == nullptr) o_stream << "invalid data!" << std::endl;
	else hub[adress]->print(o_stream);
}

/* A perifériahub egyik elemét file-ba írja a tesztekhez */
void PeripheralHUB::testElement(size_t adress) {
	if (hub[adress] == nullptr) throw "ures index";
	hub[adress]->testPrint();
}