#ifndef PERIPHERAL_H
#define PERIPHERAL_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "define.h"
#include "serializable.h"

/*
	class basePeripheral
	osztály, hogy a perifériában tárolt generikus adat
	típusát ne kelljen mindig megadni, így futásidõben
	lesz kiértékelve
*/
class basePeripheral : Serializable {
	/* name (std::string) - a periféria neve */
	std::string name;
public:
	/*
		basePeripheral konstruktor
		@param name std::string = periféria neve
	*/
	basePeripheral(std::string name) : name(name) { }

	/* basePeripheral destruktor */
	virtual ~basePeripheral() { }

	/*
		kiíró függvény, ami egy streamre írja a benne tárolt adatot
		virtuális, mert a belõle származó Peripheral osztály tárolja
		a kiírandó adatot
		@param stream std::ostream& = milyen stream-re írjon
		@return std::ostream& = így lehet egymás után többet is kiírni
	*/
	virtual std::ostream& print(std::ostream& stream = std::cout) = 0;
	
	/*
		getter
		@return std::string = a periféria nevét adja vissza
	*/
	std::string getName() { return name; }

	/* tisztán virtuális függvények: */
	virtual void testPrint() const = 0;
	virtual void write() const = 0;
	virtual void read() = 0;
	virtual void clear() = 0;
};

/*
	generikus class Peripheral osztály a basePeripheral-ból származtatava
	@param Type = tárolt adattípus
*/
template<typename Type>
class Peripheral : public basePeripheral {
	/* storedData (std::vector<Type>) - a tárolt adat vektora */
	std::vector<Type> storedData;
	/* dataType (TYPE) - a tárolt adat típusa */
	TYPE dataType;
public:
	Peripheral() :
		basePeripheral("Unknown"),
		storedData(nullptr),
		dataType(Undefined)
	{ }

	/*
		Peripheral konstruktor
		@param input std::vector<Type> = a tárolni kívánt adat vektora
		@param name std::string = a periféria neve
		@param dataType TYPE = a tárolni kívánt adat típusa
	*/
	Peripheral(std::vector<Type> input, std::string name, TYPE dataType) :
		basePeripheral(name),
		storedData(input),
		dataType(dataType)
	{ }
	
	/* Peripheral destruktor - kitörli a vektor tartalmát */
	~Peripheral() { storedData.clear(); }

	/* stream-re írja az a tárolt adatot */
	std::ostream& print(std::ostream& stream = std::cout) override {
		for (size_t i = 0; i < storedData.size(); ++i) {
			stream << storedData[i] << " ";
		}
		stream << std::endl;
		return stream;
	}

	/*
		A tesztekhez használt file-ba író függvény
		A gtest_lite onnan fogja visszaolvasni egy string-be
		a kiírt adatokat, hogy string-et string-gel tudjon összehasonlítani
	*/
	void testPrint() const override {
		std::ofstream file("test.txt");
		for (auto iter : storedData) { file << iter << ' '; }
		file.close();
	}

	/*
		A Serializable osztályból leszármazás után örökölt write függvény
		Az adat tartalmát soronként file-ba írja, hogy egy, a read függvény
		segítségével visszatölthetõ legyen
	*/
	void write() const override {
		std::ofstream file("serializable.txt");
		file << static_cast<unsigned int>(dataType) << std::endl;
		for (auto iter : storedData) { file << iter << std::endl; }
		file.close();
	}

	/*
		A Serializable osztályból leszármazás után örökölt read függvény
		Egy write függvény által file-ba írt adat visszatöltését végzi a
		periféria tárolójába
	*/
	void read() override {
		storedData.clear();
		std::ifstream file("serializable.txt");
		std::string temp;
		std::getline(file, temp);
		Type read_in;
		while (file >> read_in) {
			storedData.push_back(read_in);
		}
		file.close();
	}

	/* kívülrõl elérhetõvé teszi a vector clear függvényét */
	void clear() override {
		storedData.clear();
	}
};

/* class PeripheralHUB, a különbözõ perifériák tárolására */
class PeripheralHUB {
	/* a különbözõ perifériák heterogén kollekciója */
	std::vector<basePeripheral*> hub;
	/* perifériák maximális száma */
	const size_t range;
public:
	PeripheralHUB(size_t range = 4);
	~PeripheralHUB();

	void addElement(basePeripheral* input);
	void removeElement(size_t adress);

	basePeripheral* getPeripheral(size_t adress) const;

	void accessAddress(size_t adress, std::ostream& o_stream = std::cout);
	void testElement(size_t adress);
	void peripheralDump(std::ostream& stream = std::cout);
};

#endif