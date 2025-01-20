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
	oszt�ly, hogy a perif�ri�ban t�rolt generikus adat
	t�pus�t ne kelljen mindig megadni, �gy fut�sid�ben
	lesz ki�rt�kelve
*/
class basePeripheral : Serializable {
	/* name (std::string) - a perif�ria neve */
	std::string name;
public:
	/*
		basePeripheral konstruktor
		@param name std::string = perif�ria neve
	*/
	basePeripheral(std::string name) : name(name) { }

	/* basePeripheral destruktor */
	virtual ~basePeripheral() { }

	/*
		ki�r� f�ggv�ny, ami egy streamre �rja a benne t�rolt adatot
		virtu�lis, mert a bel�le sz�rmaz� Peripheral oszt�ly t�rolja
		a ki�rand� adatot
		@param stream std::ostream& = milyen stream-re �rjon
		@return std::ostream& = �gy lehet egym�s ut�n t�bbet is ki�rni
	*/
	virtual std::ostream& print(std::ostream& stream = std::cout) = 0;
	
	/*
		getter
		@return std::string = a perif�ria nev�t adja vissza
	*/
	std::string getName() { return name; }

	/* tiszt�n virtu�lis f�ggv�nyek: */
	virtual void testPrint() const = 0;
	virtual void write() const = 0;
	virtual void read() = 0;
	virtual void clear() = 0;
};

/*
	generikus class Peripheral oszt�ly a basePeripheral-b�l sz�rmaztatava
	@param Type = t�rolt adatt�pus
*/
template<typename Type>
class Peripheral : public basePeripheral {
	/* storedData (std::vector<Type>) - a t�rolt adat vektora */
	std::vector<Type> storedData;
	/* dataType (TYPE) - a t�rolt adat t�pusa */
	TYPE dataType;
public:
	Peripheral() :
		basePeripheral("Unknown"),
		storedData(nullptr),
		dataType(Undefined)
	{ }

	/*
		Peripheral konstruktor
		@param input std::vector<Type> = a t�rolni k�v�nt adat vektora
		@param name std::string = a perif�ria neve
		@param dataType TYPE = a t�rolni k�v�nt adat t�pusa
	*/
	Peripheral(std::vector<Type> input, std::string name, TYPE dataType) :
		basePeripheral(name),
		storedData(input),
		dataType(dataType)
	{ }
	
	/* Peripheral destruktor - kit�rli a vektor tartalm�t */
	~Peripheral() { storedData.clear(); }

	/* stream-re �rja az a t�rolt adatot */
	std::ostream& print(std::ostream& stream = std::cout) override {
		for (size_t i = 0; i < storedData.size(); ++i) {
			stream << storedData[i] << " ";
		}
		stream << std::endl;
		return stream;
	}

	/*
		A tesztekhez haszn�lt file-ba �r� f�ggv�ny
		A gtest_lite onnan fogja visszaolvasni egy string-be
		a ki�rt adatokat, hogy string-et string-gel tudjon �sszehasonl�tani
	*/
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
		file << static_cast<unsigned int>(dataType) << std::endl;
		for (auto iter : storedData) { file << iter << std::endl; }
		file.close();
	}

	/*
		A Serializable oszt�lyb�l lesz�rmaz�s ut�n �r�k�lt read f�ggv�ny
		Egy write f�ggv�ny �ltal file-ba �rt adat visszat�lt�s�t v�gzi a
		perif�ria t�rol�j�ba
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

/* class PeripheralHUB, a k�l�nb�z� perif�ri�k t�rol�s�ra */
class PeripheralHUB {
	/* a k�l�nb�z� perif�ri�k heterog�n kollekci�ja */
	std::vector<basePeripheral*> hub;
	/* perif�ri�k maxim�lis sz�ma */
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