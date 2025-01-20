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
	oszt�ly, hogy a mem�riablokkban t�rolt generikus adat
	t�pus�t ne kelljen mindig megadni, �gy fut�sid�ben lesz
	ki�rt�kelve
*/
class baseMemoryBlock : Serializable {
	/* a mem�riablokkban t�rolt adat �rv�nyess�ge */
	bool valid;
public:
	/*
		baseMemoryBlock konstruktor 
		@param valid (bool) - az adat �rv�nyess�ge
	*/
	baseMemoryBlock(bool valid) : valid(valid) { }

	/*
		baseMemoryBlock destruktor
		virtu�lis, hogy a bel�le sz�rmaz� memoryBlock
		destruktora is lefusson t�rl�s eset�n
	*/
	virtual ~baseMemoryBlock() { }

	/*
		ki�r� f�ggv�ny, ami egy streamre �rja a benne t�rolt adatot
		virtu�lis, mert a bel�le sz�rmaz� memoryBlock oszt�ly t�rolja
		a ki�rand� adatot
		@param stream (std::ostream&) - milyen stream-re �rjon
		@return (std::ostream&) - �gy lehet egym�s ut�n t�bbet is ki�rni
	*/
	virtual std::ostream& print(std::ostream& stream = std::cout) = 0;
	
	/* tiszt�n virtu�lis f�ggv�nyek */
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
		@param input std::vector<Type> = t�rolni k�v�nt vector
		@param memoryType TYPE = a vector t�pusa
	*/
	memoryBlock(std::vector<Type> input, TYPE memoryType) :
		baseMemoryBlock(true),
		storedData(input),
		memoryType(memoryType)
	{ }

	~memoryBlock() { }

	/* stream-re �rja az a t�rolt adatot */
	std::ostream& print(std::ostream& stream = std::cout) override {
		for (size_t i = 0; i < storedData.size(); ++i) {
			stream << storedData[i] << " ";
		}
		stream << std::endl;
		return stream;
	}

	/* Tesztel�shez file-ba �rja az adatot */
	void testPrint() const override {
		std::ofstream file("test.txt");
		for (auto iter : storedData) { file << iter << ' '; }
		file.close();
	}

	/*
		A Serializable oszt�lyb�l lesz�rmaz�s ut�n �r�k�lt write f�ggv�ny
		Az adat tartalm�t soronk�nt file-ba �rja, hogy egy, a read f�ggv�ny
		seg�ts�g�vel visszat�lthet� legyen
	*/
	void write() const override {
		std::ofstream file("serializable.txt");
		file << static_cast<unsigned int>(memoryType) << std::endl;
		for (auto iter : storedData) { file << iter << std::endl; }
		file.close();
	}

	/*
		A Serializable oszt�lyb�l lesz�rmaz�s ut�n �r�k�lt read f�ggv�ny
		Egy write f�ggv�ny �ltal file-ba �rt adat visszat�lt�s�t v�gzi a
		mem�ria t�rol�j�ba
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

	/* k�v�lr�l el�rhet�v� teszi a vector clear f�ggv�ny�t */
	void clear() override {
		storedData.clear();
	}
};

/*
	Memory oszt�ly, ami a k�l�nb�z� mem�riacell�kat
	tartalmazza egy heterog�n kollekci�ban �s kezeli
	a mem�ri�val kapcsolatos m�veletek v�grehajt�s�t
*/
struct Memory {
	std::vector<baseMemoryBlock*> memory;
	/* mem�riablokkok maxim�lis sz�ma */
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