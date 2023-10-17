//
// Created by gabriele on 25/11/21.
//

#include "precompiler.h"
#include "Item.h"

Item::Item(unsigned level, unsigned value) {

    initVariables();

    this->level = level;
    this->value = value;
    type = ItemTypes::ITEM_DEFAULT;
}

Item::~Item() {

}

void Item::initVariables() {

}

const ItemTypes &Item::getType() const {

    return type;
}

const unsigned &Item::getLevel() const {

    return level;
}

const unsigned &Item::getValue() const {

    return value;
}
