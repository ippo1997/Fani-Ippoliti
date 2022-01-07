//
// Created by alpacox on 04/12/21.
//

#ifndef DRAGHI_E_SOTTERRANEI_INVENTORY_H
#define DRAGHI_E_SOTTERRANEI_INVENTORY_H

#include "Item.h"

class Inventory {
public:
    Inventory(unsigned capacity);
    ~Inventory();

    const unsigned& size() const;
    const unsigned& maxSize() const;

    void clear();
    const bool empty() const;

    const bool addItem(Item* item);
    const bool removeItem(const unsigned index);

    const bool saveToFile(const std::string fileName);
    const bool loadFromFile(const std::string fileName);

private:
    Item** itemArray;
    unsigned itemQuantity;
    unsigned capacity;

    void initialize();
    void nullify(const unsigned from = 0);
    void freeMemory();

};


#endif //DRAGHI_E_SOTTERRANEI_INVENTORY_H
