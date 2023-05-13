from orderbook import *
import sys
import warnings
warnings.filterwarnings('ignore')

def run_txt_reader(file_name):
    with open(file_name) as f:
        i = 1
        ob = None
        for line in f:
            if i == 1:
                ob = OrderBook(line[0] == '1')
            else:
                subj = line.split(',')
                if len(subj) == 0:
                    print("Error on Line " + str(i))
                elif subj[0] == 'Add':
                    uid = int(subj[1])
                    side = bool(subj[2])
                    price = float(subj[3])
                    amount = int(subj[4])
                    ob.addOrder(uid, side, price, amount)
                elif subj[0] == 'Update':
                    uid = int(subj[1])
                    amount = int(subj[2])
                    ob.updateOrder(uid, amount)
                elif subj[0] == 'Delete':
                    uid = int(subj[1])
                    ob.deleteOrder(uid)
                elif subj[0] == 'Print':
                    ob.printBook()
                else:
                    print("Error on Line " + str(i))
            i += 1

if __name__ == "__main__":
    if len(sys.argv) <= 1:
        print("Require Txt File Name")
    elif sys.argv[1] == "example":
        b = OrderBook(True)

        b.addOrder(1, True, 105, 100)
        b.addOrder(2, True, 105, 100)
        b.addOrder(3, True, 105, 100)
        b.addOrder(4, True, 104, 100)
        b.addOrder(5, False, 103.5, 399)

        b.printBook()
    else:
        run_txt_reader(sys.argv[1])