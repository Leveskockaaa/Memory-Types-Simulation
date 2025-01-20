#ifndef SERIALIZABLE_H
#define SERIALIZABLE_H

struct Serializable {
	virtual void write() const = 0;
	virtual void read() = 0;
};

#endif