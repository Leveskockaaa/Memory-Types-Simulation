#include "peripheral.h"
#include "define.h"
#include "memtrace.h"

/*
	PeripheralHUB konstruktor
	a define.h-ban defini�lt maximum csatlakoztathat� perif�ri�k
	sz�m�nak megfelel� mennyis�g� null pointer-rel felt�lti a
	heterog�n kollekci�t
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
	addElement - hozz�ad egy perif�ri�t a heterog�n kollekci�hoz
	@param input basePeripheral* = a t�rolni k�v�nt perif�ri�ra mutat� pointer
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
	removeElement - egy adott helyen l�v� perif�ri�t t�r�l
	a heterog�n kollekci�b�l
	@param adress size_t = a t�r�lni k�v�nt adat sorsz�ma
*/
void PeripheralHUB::removeElement(size_t adress) {
	if (adress >= range) throw "out of range";
	if (hub[adress] == nullptr) throw "already empty";
	delete hub[adress];
	hub[adress] = nullptr;
}

/*
	getter, egy perif�ri�ra mutat� pointer-t ad vissza
	@param adress size_t = a k�rt perif�ria sorsz�ma
*/
basePeripheral* PeripheralHUB::getPeripheral(size_t adress) const {
	if (hub[adress] == nullptr) return nullptr;
	else return hub[adress];
}

/* A perif�ri�kat tartalmaz� hub dump-ja */
void PeripheralHUB::peripheralDump(std::ostream& stream) {
	for (size_t i = 0; i < range; ++i) {
		if (hub[i] != nullptr) {
			stream << "HUB[" << hub[i]->getName() << "]: ";
			hub[i]->print();
		}
		else stream << "HUB[" << i << "]: invalid data!" << std::endl;
	}
}

/* El�ri a perif�riahub egyik elem�t �s ki�rja a megadott stream-re */
void PeripheralHUB::accessAddress(size_t adress, std::ostream& o_stream) {
	if (adress >= range) throw "rossz index";
	if (hub[adress] == nullptr) o_stream << "invalid data!" << std::endl;
	else hub[adress]->print(o_stream);
}

/* A perif�riahub egyik elem�t file-ba �rja a tesztekhez */
void PeripheralHUB::testElement(size_t adress) {
	if (hub[adress] == nullptr) throw "ures index";
	hub[adress]->testPrint();
}