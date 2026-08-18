//
// Created by Gilbe on 10/08/2026.
//

#include "OrderTree.h"

OrderTree::OrderTree(Order* order) {
    ordList = new OrderList(order->price);
    ordList->PushOrder(order);
}

void OrderTree::addOrder(Order* ord) {
    int p = ord->price;
    if (p < ordList->price) {
        if (left != nullptr) {
            left->addOrder(ord);
        }
        else {
            left = new OrderTree(ord);
        }
    }
    else if (p > ordList->price) {
        if (right != nullptr) {
            right->addOrder(ord);
        }
        else {
            right = new OrderTree(ord);
        }
    }
    else {
        ordList->PushOrder(ord);
    }
}

Order* OrderTree::getLowestOrder() {
    if (left != nullptr) {
        Order* lo = left->getLowestOrder();
        //return lowest order in this tree val if one below is empty.
        return (lo==nullptr ? ordList->getFirstOrder() : lo);
    }

    return ordList -> getFirstOrder();
}

bool OrderTree::deleteLowestOrder() {
    if (left != nullptr) {
        bool v = left->deleteLowestOrder();
        if (!v) {
            if (ordList -> getFirstOrder() == nullptr) {return false;}
            delete ordList->PopOrder();
            return true;
        }
    }
    if (ordList->getFirstOrder() == nullptr) {return false;}
    delete ordList->PopOrder();
    return true;
}

bool OrderTree::deleteHighestOrder() {
    if (right != nullptr) {
        bool v = right->deleteHighestOrder();
        if (!v) {
            if (ordList -> getFirstOrder() == nullptr) {return false;}
            delete ordList->PopOrder();
            return true;
        }
    }
    if (ordList->getFirstOrder() == nullptr) {return false;}
    delete ordList->PopOrder();
    return true;
}

Order* OrderTree::getHighestOrder() {
    if (right != nullptr) {
        Order* lo = right->getHighestOrder();
        return (lo==nullptr ? ordList->getFirstOrder() : lo);
    }

    return ordList -> getFirstOrder();
}



