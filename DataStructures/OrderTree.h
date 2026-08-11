//
// Created by Gilbe on 10/08/2026.
//

#ifndef ORDERBOOK_ORDERTREE_H
#define ORDERBOOK_ORDERTREE_H
#include "../Order.h"
#include "../OrdList.h"


class OrderTree {
    public:
    OrderTree(OrdList ordList);
    OrderTree* left;
    OrderTree* right;
    Order ordList;
};


#endif //ORDERBOOK_ORDERTREE_H
