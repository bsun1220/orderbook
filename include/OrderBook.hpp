#include "Order.hpp"
#include "PriceLevel.hpp"
#include <unordered_map>
#include <iostream>
#include <math.h>
#include <iomanip>

class OrderBook{
    public:
        std::vector<PriceLevel> bids {};
        std::vector<PriceLevel> asks {};
        std::unordered_map<long, Order> order_map {};
        bool verbose{};
    
    OrderBook(bool act_verbose){
        verbose = act_verbose;
    }

    void addOrder(long uid, bool side, double price, long size);
    void updateOrder(long uid, long size);
    void deleteOrder(long uid);
    void printBook();
    void match(bool side, long uid);
    double getMidpoint();

};