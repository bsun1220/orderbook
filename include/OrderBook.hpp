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

    void add_order(long uid, bool side, double price, long size);
    void update_order(long uid, long size);
    void delete_order(long uid);
    void print_book();
    void match();

};