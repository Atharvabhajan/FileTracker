#ifndef CHANGEDETECTOR_H
#define CHANGEDETECTOR_H

#include "DirectorySnapshot.h"
#include <vector>
#include <string>
#include <utility>

class ChangeDetector : public ISerializable {
private:
    const DirectorySnapshot& oldSnapshot;
    const DirectorySnapshot& newSnapshot;

    std::vector<std::pair<std::string, std::string>> changes;


public:
    ChangeDetector(const DirectorySnapshot& oldSnap, const DirectorySnapshot& newSnap);

    void detectChanges();
    bool saveChangesCSV(const std::string& filename) const;
    const std::vector<std::pair<std::string,std::string>>& getChanges() const;

    std::string toCSV() const override;
    void printCLI() const override;
};

#endif
