//
// Created by alpacox on 04/12/21.
//

#include "precompiler.h"
#include "Inventory.h"


Inventory::Inventory(unsigned capacity) {

    this->capacity = capacity;
    initialize();
    nullify();
}

Inventory::~Inventory() {

    freeMemory();
}

void Inventory::initialize() {

    itemQuantity = 0;
    itemArray = new Item*[this->capacity];

}


void Inventory::nullify(const unsigned int from) {

    for(size_t i = from; i < capacity; i++){

        itemArray[i] = nullptr;
    }
}

void Inventory::freeMemory() {

    for(size_t i = 0; i < this->itemQuantity; i++){

        delete itemArray[i];
    }

    delete[] itemArray;
}

const unsigned &Inventory::size()  const{

    return itemQuantity;
}

const unsigned &Inventory::maxSize() const{

    return capacity;
}

void Inventory::clear() {

    for(size_t i = 0; i < itemQuantity; i++){

        delete itemArray[i];
    }

    itemQuantity = 0;

    nullify();
}

const bool Inventory::empty() const {

    return itemQuantity == 0;
}

const bool Inventory::addItem(Item *item) {

    if(itemQuantity <= capacity){

        itemArray[itemQuantity++] = item->clone();

        return true;
    }

    return false;
}

const bool Inventory::removeItem(const unsigned int index) {

    if( itemQuantity > 0){

        if(index <0 || index >= capacity)
            return false;

        delete itemArray[index];
        itemArray[index] = nullptr;
        --itemQuantity;

        return true;
    }

    return false;
}

const bool Inventory::saveToFile(const std::string fileName) {

    return 0;
}

const bool Inventory::loadFromFile(const std::string fileName) {

    return 0;
}






