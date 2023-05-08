#include "Order.hpp"
#include "PriceLevel.hpp"
#include <unordered_map>
#include <iostream>

class OrderBook{
    public:
        std::vector<PriceLevel> bids {};
        std::vector<PriceLevel> asks {};
        std::unordered_map<long, Order> order_map {};
        bool verbose{};
    
    OrderBook(bool act_verbose){
        verbose = act_verbose;
    }

    void add_order(long uid, bool side, double price, long size){
        if (order_map.count(uid) > 0){
            if (verbose) std::cout << "uid at " << uid << " already taken\n";
            return 1;
        }

        if (price < 0){
            if (verbose) std::cout << "error: invalid price at " << price << "\n";
            return 1; 
        }

        if (size < 0){
            if (verbose) std :: "error: invalid size at " << size <<"\n";
            return 1; 
        }

        Order order(uid, price, side, size);
        order_map[uid] = order; 

        if (side){
            if (asks.size() == 0){
                
            }

        } else {

        }

    }


};