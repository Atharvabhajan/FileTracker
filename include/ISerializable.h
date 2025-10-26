#ifndef ISERIALIZABLE_H
#define ISERIALIZABLE_H
#include <string>

class ISerializable {
public:
    virtual std::string toCSV() const = 0;
    virtual void printCLI() const = 0;
    virtual ~ISerializable() = default;
};

#endif
