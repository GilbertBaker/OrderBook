//
// Created by Gilbe on 17/08/2026.
//

#ifndef ORDERBOOK_ORDERBOOK_H
#define ORDERBOOK_ORDERBOOK_H
#include "OrderTree.h"
//#include "../Traders/TraderAlgo.h"
class TraderAlgo;

class OrderBook {
    public:
        void placeBuyOrder(Order* order);
        void placeSellOrder(Order* order);

        void placeBuyInstantOrder(int quantity, int traderID);
        void placeSellInstantOrder(int quantity, int traderID);

        int getBuyPrice();
        int getSellPrice();
        int getMeanPrice();
        OrderBook();

        //allows for it to be updated later
        TraderAlgo* algo;
    private:
        OrderTree* buyOrders;
        OrderTree* sellOrders;
};


#endif //ORDERBOOK_ORDERBOOK_H
