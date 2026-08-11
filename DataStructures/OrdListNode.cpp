//
// Created by Gilbe on 10/08/2026.
//

#include "OrdList.h"


OrdList::OrdList() {
    next = nullptr;
    order = nullptr;
    end=nullptr;
}

OrdList::OrdList(Order* ord) {
    next = nullptr;
    order = ord;
    end=nullptr;
}

void OrdList::addOrder(Order* ord) {
    if (next != nullptr) {
        OrdList newEnd = OrdList(ord);
        end->next = &newEnd;
        end = &newEnd;
    }
    else {
        OrdList newEnd = OrdList(ord);
        end = &newEnd;
        next = &newEnd;
    }

}

Order* OrdList::remOrder() {
    if (this->next !=nullptr) {
        OrdList* item = next;
        if (end == item) {
            end = nullptr;
        }
        next = next->next;
        return item->order;
    }
    return nullptr;
}

