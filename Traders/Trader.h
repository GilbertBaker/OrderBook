//
// Created by Gilbe on 17/08/2026.
//

#ifndef ORDERBOOK_TRADER_H
#define ORDERBOOK_TRADER_H
class TraderAlgo;


class Trader {
    public:
    Trader(int id);
    void Update();
    const int ID;
    int qOwned;
    int money;
    TraderAlgo* algo;
    void limitSell();
    void limitBuy();
    void marketSell();
    void marketBuy();

};


#endif //ORDERBOOK_TRADER_H
