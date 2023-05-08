#include "OrderBook.hpp"


void OrderBook::print_book(){
        std::cout << "ASKS (volume @ price)\n";
        for(int i = 0; i < asks.size(); i ++){
            std::cout << std::setw(6) << asks[asks.size() - 1 - i].volume << " @ " << asks[asks.size() - 1 - i].price << "\n";
        }
        std::cout << "BIDS (volume @ price)\n";
        for(int i = 0; i < bids.size(); i ++){
            std::cout << std::setw(6) << bids[i].volume << " @ " << bids[i].price << "\n";
        }
}

void OrderBook::update_order(long uid, long size){
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

            bids[left].adjust_id(size - old_vol, uid, true);
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
            asks[left].adjust_id(size - old_vol, uid, true);
        }
    
}

void OrderBook::delete_order(long uid){
        if(order_map.count(uid) == 0){
            if(verbose) std::cout << "ID " << uid << " not found\n";
            return;
        }
        double price = order_map[uid].price;
        bool side = order_map[uid].side; 
        long vol = order_map[uid].volume;

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

            bids[left].adjust_id(-vol, uid, false);
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
            asks[left].adjust_id(-vol, uid, true);

            if (asks[left].volume == 0){
                asks.erase(asks.begin() + left);
            }
        }
    
}

void OrderBook::add_order(long uid, bool side, double price, long size){
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
            if (bids.size() == 0){
                PriceLevel pl (price);
                pl.add_id(size, uid);
                bids.push_back(pl);
            }
            else if (price > bids[0].price){
                PriceLevel pl (price);
                pl.add_id(size, uid);
                bids.insert(bids.begin(), pl);
            }
            else if (price < bids[bids.size() - 1].price){
                PriceLevel pl(price);
                pl.add_id(size, uid);
                bids.push_back(pl);
            }
            else if (price == bids[0].price){
                bids[0].add_id(size, uid);
            }
            else if (price == bids[bids.size() - 1].price){
                bids[bids.size() - 1].add_id(size, uid);
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
                    bids[left].add_id(size, uid);
                } else {
                    PriceLevel pl(price);
                    pl.add_id(size, uid);
                    bids.insert(bids.begin() + left + 1, pl);
                }

            }

        } else {
            if (asks.size() == 0){
                PriceLevel pl (price);
                pl.add_id(size, uid);
                asks.push_back(pl);
            }
            else if (price < asks[0].price){
                PriceLevel pl (price);
                pl.add_id(size, uid);
                asks.insert(asks.begin(), pl);
            }
            else if (price > asks[asks.size() - 1].price){
                PriceLevel pl(price);
                pl.add_id(size, uid);
                asks.push_back(pl);
            }
            else if (price == asks[0].price){
                asks[0].add_id(size, uid);
            }
            else if (price == asks[asks.size() - 1].price){
                asks[asks.size() - 1].add_id(size, uid);
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
                    asks[left].add_id(size, uid);
                } else {
                    PriceLevel pl(price);
                    pl.add_id(size, uid);
                    asks.insert(asks.begin() + left + 1, pl);
                }

            }
        }
}