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



