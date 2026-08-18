//
// Created by Gilbe on 10/08/2026.
//

#ifndef ORDERBOOK_ORDERTREE_H
#define ORDERBOOK_ORDERTREE_H
#include "OrderList.h"
#include "../Order.h"


class OrderTree {
    public:
    OrderTree(Order* ord);
    void addOrder(Order* ord);
    OrderTree* left;
    OrderTree* right;
    OrderList* ordList;
    Order* getHighestOrder();
    Order* getLowestOrder();
    bool deleteLowestOrder();
    bool deleteHighestOrder();
    void printLowestLevels(int& printed, int maxLevels);
    void printHighestLevels(int& printed, int maxLevels);
};



#endif //ORDERBOOK_ORDERTREE_H
