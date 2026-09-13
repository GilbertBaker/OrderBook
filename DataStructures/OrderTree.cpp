//
// Created by Gilbe on 10/08/2026.
//

#include "OrderTree.h"
#include <iostream>

OrderTree::OrderTree() {
    ordList = nullptr;
    left = nullptr;
    right = nullptr;
}

OrdListNode* OrderTree::addOrder(Order* ord) {
    if (ordList == nullptr) {
        ordList = new OrderList(ord->price);

        return ordList->PushOrder(ord);
    }
    int p = ord->price;
    if (p < ordList->price) {
        if (left != nullptr) {
            return left->addOrder(ord);
        }
        else {
            left = new OrderTree();
            return left->addOrder(ord);
        }
    }
    else if (p > ordList->price) {
        if (right != nullptr) {
            return right->addOrder(ord);
        }
        else {
            right = new OrderTree();
            return right->addOrder(ord);
        }
    }
    else {
        return ordList->PushOrder(ord);
    }
}

Order* OrderTree::getLowestOrder() {
    if (left != nullptr) {
        Order* order = left->getLowestOrder();

        if (order != nullptr) {
            return order;
        }
    }

    Order* currentOrder = nullptr;
    if (ordList != nullptr) {
        currentOrder = ordList->getFirstOrder();
    }

    if (currentOrder != nullptr) {
        return currentOrder;
    }

    if (right != nullptr) {
        return right->getLowestOrder();
    }

    return nullptr;
}

Order* OrderTree::getHighestOrder() {
    if (right != nullptr) {
        Order* order = right->getHighestOrder();

        if (order != nullptr) {
            return order;
        }
    }

    Order* currentOrder = nullptr;
    if (ordList != nullptr) {
        currentOrder = ordList->getFirstOrder();
    }

    if (currentOrder != nullptr) {
        return currentOrder;
    }

    if (left != nullptr) {
        return left->getHighestOrder();
    }

    return nullptr;
}

/*bool OrderTree::deleteLowestOrder() {
    if (left != nullptr) {
        if (left->deleteLowestOrder()) {
            return true;
        }
    }

    if (ordList != nullptr && ordList->getFirstOrder() != nullptr) {
        delete ordList->PopOrder();
        return true;
    }

    if (right != nullptr) {
        return right->deleteLowestOrder();
    }

    return false;
}*/

/*bool OrderTree::deleteHighestOrder() {
    if (right != nullptr) {
        if (right->deleteHighestOrder()) {
            return true;
        }
    }

    if (ordList != nullptr && ordList->getFirstOrder() != nullptr) {
        delete ordList->PopOrder();
        return true;
    }

    if (left != nullptr) {
        return left->deleteHighestOrder();
    }

    return false;
}*/

void OrderTree::printLowestLevels(int& printed, int maxLevels) {
    if (printed >= maxLevels) return;

    if (left != nullptr)
        left->printLowestLevels(printed, maxLevels);

    if (printed >= maxLevels) return;

    if (ordList !=nullptr) {
        int quantity = ordList->CalcOrders();

        if (quantity > 0) {
            std::cout << ordList->price << " x " << quantity << '\n';
            printed++;
        }
    }

    if (right != nullptr)
        right->printLowestLevels(printed, maxLevels);
}

void OrderTree::printHighestLevels(int& printed, int maxLevels) {
    if (printed >= maxLevels) return;

    if (right != nullptr)
        right->printHighestLevels(printed, maxLevels);

    if (printed >= maxLevels) return;

    if (ordList !=nullptr) {
        int quantity = ordList->CalcOrders();

        if (quantity > 0) {
            std::cout << ordList->price << " x " << quantity << '\n';
            printed++;
        }
    }

    if (left != nullptr)
        left->printHighestLevels(printed, maxLevels);
}



