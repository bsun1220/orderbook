#include "OrderBook.hpp"
#include <math.h>

void OrderBook::printBook(){
    std::cout<<"\n";
    std::cout<<"ORDERBOOK INFORMATION\n";
    std::cout << "ASKS (volume @ price)\n";
    for(int i = 0; i < asks.size(); i ++){
        std::cout << std::setw(6) << asks[asks.size() - 1 - i].volume << " @ " << asks[asks.size() - 1 - i].price << "\n";
    }
    std::cout << "BIDS (volume @ price)\n";
    for(int i = 0; i < bids.size(); i ++){
        std::cout << std::setw(6) << bids[i].volume << " @ " << bids[i].price << "\n";
    }
}

void OrderBook::updateOrder(long uid, long size){
        if(order_map.count(uid) == 0){
            if(verbose) std::cout << "ID " << uid << " not found\n";
            return;
        }
        if (size <= 0){
            if(verbose) std::cout << "size of " << size << " invalid\n";
            return;
        }

    
        long old_vol = order_map[uid].volume;
        order_map[uid].volume = size; 
        double price = order_map[uid].price;
        bool side = order_map[uid].side; 


        if (side){
            int left = 0, right = bids.size() - 1;

            while (left < right){
                int mid = (left + right)/2;

                if (price > bids[mid].price){
                    right = mid - 1;
                } else if (price < bids[mid].price){
                    left = mid + 1; 
                } else {
                    left = mid;
                    right = mid;
                }
            }

            bids[left].adjustId(size - old_vol, uid, true);
        }
        else {

            int left = 0, right = asks.size() - 1;
            while (right > left){
                int mid = (left + right)/2;
                if (price > asks[mid].price){
                    left = mid + 1; 
                } else if (price < asks[mid].price){
                    right = mid - 1;
                }  else {
                    right = mid;
                    left = mid;
                }
            }
            asks[left].adjustId(size - old_vol, uid, true);
        }
        if (verbose){
            std::cout <<"order " << uid << " has adjusted volume to " << size << "\n";
        }
    
}

void OrderBook::deleteOrder(long uid){
        if(order_map.count(uid) == 0){
            if(verbose) std::cout << "ID " << uid << " not found\n";
            return;
        }
        double price = order_map[uid].price;
        bool side = order_map[uid].side; 
        long vol = order_map[uid].volume;

        order_map.erase(uid);

        if(verbose){
            std::cout<< "order " << uid << " has been deleted\n";
        }

        if (side){
            int left = 0, right = bids.size() - 1;

            while (left < right){
                int mid = (left + right)/2;

                if (price > bids[mid].price){
                    right = mid - 1;
                } else if (price < bids[mid].price){
                    left = mid + 1; 
                } else {
                    left = mid;
                    right = mid;
                }
            }

            bids[left].adjustId(-vol, uid, false);
            if (bids[left].volume == 0){
                bids.erase(bids.begin() + left);
            }
        }
        else {

            int left = 0, right = asks.size() - 1;
            while (right > left){
                int mid = (left + right)/2;
                if (price > asks[mid].price){
                    left = mid + 1; 
                } else if (price < asks[mid].price){
                    right = mid - 1;
                }  else {
                    right = mid;
                    left = mid;
                }
            }
            asks[left].adjustId(-vol, uid, true);

            if (asks[left].volume == 0){
                asks.erase(asks.begin() + left);
            }
        }
    
}

void OrderBook::addOrder(long uid, bool side, double price, long size){
        price = (double)std::round(price * 100 ) / 100.0;
        if (order_map.count(uid) > 0){
            if (verbose) std::cout << "uid at " << uid << " already taken\n";
            return;
        }

        if (price <= 0){
            if (verbose) std::cout << "error: invalid price at " << price << "\n";
            return; 
        }

        if (size <= 0){
            if (verbose) std::cout<< "error: invalid size at " << size <<"\n";
            return; 
        }

        Order order(uid, price, side, size);
        order_map.insert({uid, order});

        if (side){
            if(verbose){
                std::cout<<uid<< " added buy order for " << size << " @ " << price << "\n";
            }

            if (bids.size() == 0){
                PriceLevel pl (price);
                pl.addId(size, uid);
                bids.push_back(pl);
            }
            else if (price > bids[0].price){
                PriceLevel pl (price);
                pl.addId(size, uid);
                bids.insert(bids.begin(), pl);
            }
            else if (price < bids[bids.size() - 1].price){
                PriceLevel pl(price);
                pl.addId(size, uid);
                bids.push_back(pl);
            }
            else if (price == bids[0].price){
                bids[0].addId(size, uid);
            }
            else if (price == bids[bids.size() - 1].price){
                bids[bids.size() - 1].addId(size, uid);
            }
            else {
                int left = 0, right = bids.size() - 1; 
                while(right - left > 1 && right > left){
                    int mid = (right + left)/2;
                    if (price > bids[mid].price){
                        right = mid - 1;
                    } else if (price < bids[mid].price){
                        left = mid;
                    } else {
                        left = mid;
                        right = mid; 
                    }
                }
                if (bids[left].price == price){
                    bids[left].addId(size, uid);
                } else {
                    PriceLevel pl(price);
                    pl.addId(size, uid);
                    bids.insert(bids.begin() + left + 1, pl);
                }

            }

        } else {
            if(verbose){
                std::cout<<uid<< " added sell order for " << size << " @ " << price << "\n";
            }

            if (asks.size() == 0){
                PriceLevel pl (price);
                pl.addId(size, uid);
                asks.push_back(pl);
            }
            else if (price < asks[0].price){
                PriceLevel pl (price);
                pl.addId(size, uid);
                asks.insert(asks.begin(), pl);
            }
            else if (price > asks[asks.size() - 1].price){
                PriceLevel pl(price);
                pl.addId(size, uid);
                asks.push_back(pl);
            }
            else if (price == asks[0].price){
                asks[0].addId(size, uid);
            }
            else if (price == asks[asks.size() - 1].price){
                asks[asks.size() - 1].addId(size, uid);
            }
            else {

                int left = 0, right = asks.size() - 1; 
                while(right - left > 1 && right > left){
                    int mid = (right + left)/2;
                    if (price > asks[mid].price){
                        left = mid + 1;
                    } else if (price < asks[mid].price){
                        right = mid;
                    } else {
                        left = mid;
                        right = mid; 
                    }
                }
                
                if (asks[left].price == price){
                    asks[left].addId(size, uid);
                } else {
                    PriceLevel pl(price);
                    pl.addId(size, uid);
                    asks.insert(asks.begin() + left + 1, pl);
                }

            }
        }
        match(side, uid);
}

void OrderBook::match(bool side, long uid){

    if (side){
        if (asks.size() == 0) return;
        if (bids[0].getIds()[0] != uid) return; 
        if (asks[0].price > bids[0].price) return; 

        
        while (order_map.count(uid) > 0 && asks.size() > 0){


            if (asks[0].price > order_map[uid].price) break; 

            bool no_vol = false; 
            int asks_orders_size = asks[0].orderids.size();
            for (int i = 0; i < asks_orders_size; i++){
                Order ask_order = order_map[asks[0].orderids[i]];
                long volume_traded = std::min(order_map[uid].volume, order_map[asks[0].orderids[i]].volume);

                order_map[uid].volume -= volume_traded;
                bids[0].volume -= volume_traded;
                order_map[asks[0].orderids[i]].volume -= volume_traded;
                asks[0].volume -= volume_traded;

                if (verbose){
                    double traded_price = (bids[0].price + asks[0].price)/2;
                    std::cout << uid << " bought from " << order_map[asks[0].orderids[i]].uid << " for " << volume_traded << " @ " << traded_price << "\n";
                }

                if (order_map[uid].volume == 0){
                    bids.erase(bids.begin());
                    order_map.erase(uid);
                    no_vol = true; 
                }
                if (order_map[asks[0].orderids[i]].volume == 0){
                    asks[0].orderids.erase(asks[0].orderids.begin());
                    order_map.erase(order_map[asks[0].orderids[i]].uid);
                    no_vol = true; 
                }

                if (no_vol) break;
            }

            if (asks[0].volume == 0){
                asks.erase(asks.begin());
            }
        }



    } else {
        if (bids.size() == 0) return;
        if (asks[0].getIds()[0] != uid) return; 
        if (bids[0].price < asks[0].price) return; 

         Order ask_order = order_map[uid];
        
        while (order_map.count(uid) > 0 && bids.size() > 0){


            if (bids[0].price < order_map[uid].price) break; 

            bool no_vol = false; 
            int bids_orders_size = bids[0].orderids.size();
            for (int i = 0; i < bids_orders_size; i++){
                Order bid_order = order_map[bids[0].orderids[i]];
                long volume_traded = std::min(order_map[bids[0].orderids[i]].volume, order_map[uid].volume);

                order_map[bids[0].orderids[i]].volume -= volume_traded;
                bids[0].volume -= volume_traded;
                order_map[uid].volume -= volume_traded;
                asks[0].volume -= volume_traded;

                if (verbose){
                    double traded_price = (bids[0].price + asks[0].price)/2;
                    std::cout << uid << " sold to " << order_map[bids[0].orderids[i]].uid << " for " << volume_traded << " @ " << traded_price << "\n";
                }

                if (order_map[uid].volume == 0){
                    asks.erase(asks.begin());
                    order_map.erase(uid);
                    no_vol = true; 
                }
                if (order_map[bids[0].orderids[i]].volume == 0){
                    bids[0].orderids.erase(bids[0].orderids.begin());
                    order_map.erase(bid_order.uid);
                    no_vol = true; 
                }

                if (no_vol) break;
            }

            if (bids[0].volume == 0){
                bids.erase(bids.begin());
            }
        }
    }
}

double OrderBook::getMidpoint(){
    long bid_volume = bids[0].volume;
    long ask_volume = asks[0].volume;

    double bid_price = bids[0].price;
    double ask_price = asks[0].price;

    return (ask_volume * bid_price + bid_volume * ask_price)/(bid_volume + ask_volume);
}