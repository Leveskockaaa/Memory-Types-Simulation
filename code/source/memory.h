#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "define.h"
#include "serializable.h"

/*
	class baseMemoryBlock
	osztály, hogy a memóriablokkban tárolt generikus adat
	típusát ne kelljen mindig megadni, így futásidõben lesz
	kiértékelve
*/
class baseMemoryBlock : Serializable {
	/* a memóriablokkban tárolt adat érvényessége */
	bool valid;
public:
	/*
		baseMemoryBlock konstruktor 
		@param valid (bool) - az adat érvényessége
	*/
	baseMemoryBlock(bool valid) : valid(valid) { }

	/*
		baseMemoryBlock destruktor
		virtuális, hogy a belõle származó memoryBlock
		destruktora is lefusson törlés esetén
	*/
	virtual ~baseMemoryBlock() { }

	/*
		kiíró függvény, ami egy streamre írja a benne tárolt adatot
		virtuális, mert a belõle származó memoryBlock osztály tárolja
		a kiírandó adatot
		@param stream (std::ostream&) - milyen stream-re írjon
		@return (std::ostream&) - így lehet egymás után többet is kiírni
	*/
	virtual std::ostream& print(std::ostream& stream = std::cout) = 0;
	
	/* tisztán virtuális függvények */
	virtual void testPrint() const = 0;
	virtual void write() const = 0;
	virtual void read() = 0;
	virtual void clear() = 0;
};

/*  */
template<typename Type>
class memoryBlock : public baseMemoryBlock {
	std::vector<Type> storedData;
	TYPE memoryType;
public:
	memoryBlock() :
		baseMemoryBlock(false),
		storedData(nullptr),
		memoryType(Undefined)
	{ }

	/*
		memoryBlock konstruktor
		@param input std::vector<Type> = tárolni kívánt vector
		@param memoryType TYPE = a vector típusa
	*/
	memoryBlock(std::vector<Type> input, TYPE memoryType) :
		baseMemoryBlock(true),
		storedData(input),
		memoryType(memoryType)
	{ }

	~memoryBlock() { }

	/* stream-re írja az a tárolt adatot */
	std::ostream& print(std::ostream& stream = std::cout) override {
		for (size_t i = 0; i < storedData.size(); ++i) {
			stream << storedData[i] << " ";
		}
		stream << std::endl;
		return stream;
	}

	/* Teszteléshez file-ba írja az adatot */
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
		file << static_cast<unsigned int>(memoryType) << std::endl;
		for (auto iter : storedData) { file << iter << std::endl; }
		file.close();
	}

	/*
		A Serializable osztályból leszármazás után örökölt read függvény
		Egy write függvény által file-ba írt adat visszatöltését végzi a
		memória tárolójába
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

/*
	Memory osztály, ami a különbözõ memóriacellákat
	tartalmazza egy heterogén kollekcióban és kezeli
	a memóriával kapcsolatos mûveletek végrehajtását
*/
struct Memory {
	std::vector<baseMemoryBlock*> memory;
	/* memóriablokkok maximális száma */
	const size_t range;
public:
	Memory(size_t range = 4);
	~Memory();
	void addElement(baseMemoryBlock* input);
	void removeElement(size_t adress);

	void saveDataToMemory(TYPE type);

	void memoryDump(std::ostream& o_stream = std::cout);
	void testPrint(size_t adress) const;
	void accessAddress(size_t adress, std::ostream& o_stream = std::cout);
};

#endif