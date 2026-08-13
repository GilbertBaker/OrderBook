//
// Created by Gilbe on 10/08/2026.
//

#ifndef ORDERBOOK_ORDLIST_H
#define ORDERBOOK_ORDLIST_H
#include "../Order.h"


class OrdListNode {
    public:
    OrdListNode(Order* ord);
    OrdListNode* next;
    Order* order;
    
};


#endif //ORDERBOOK_ORDLIST_H
