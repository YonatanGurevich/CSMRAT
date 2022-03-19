#include <iostream>
#include <deque>
#include <map>
#include <algorithm>

// first user defines tax rate and action price
// user can buy shares: enter ticker, price, num of shares
// for each new ticker symbol new shares list/deque is created
// user can sell shares: enter ticker, price, num of shares
// shares will be sold in fifo order


class Share{
    private:
        std::string ticker_symbol;
        double share_price;
    public:
        Share(std::string, double);
        Share();
        ~Share();
        std::string getTicker() {
            return this->ticker_symbol;
        }
        double getSharePrice() {
            return this->share_price;
        }

};


class User{
    private:
        std::string name;
        double USD_CASH;
        double tax_shield;
    
    public:
        std::map<std::string, std::deque<Share> > all_shares;

        double getCash(){
            return this->USD_CASH;
            }

        void AddCash(double amount){
            this->USD_CASH += amount;
            }

        double getTaxShield() {
            return this->tax_shield;
            }

        void AddTaxShield(double amount) {
            this->tax_shield += amount;
            }

        std::string getName() {
            return this->name;
        }

        void SetName(std::string name) {
            this->name = name;
        }
                
        int getShareCount(std::string ticker_symbol) {
            this->all_shares[ticker_symbol].size();
        }

        double getAveragePrice(std::string ticker_symbol) {
            double average_price = 0;
            for (int i = 0; i < this->all_shares[ticker_symbol].size(); i++) {
                
            }
        }

        User() {
            SetName("user");
            AddCash(0.0);
        };
        User(std::string name, double cash) {
            SetName(name);
            AddCash(cash);
        };

};

void BuyShares(User user, std::string ticker_symbol, double share_price, int number_of_shares, double action_fee) {
    user.AddCash(-action_fee);
    if (user.all_shares.find(ticker_symbol) == user.all_shares.end()) {
        std::deque<Share> position;
        for (int i = 0; i < number_of_shares; i++) {
            position.push_back(Share(ticker_symbol, share_price));
            user.all_shares.insert({ticker_symbol, position});
        }
    }
    else {
        for (int i = 0; i < number_of_shares; i++) {
            user.all_shares[ticker_symbol].push_back(Share(ticker_symbol, share_price));
        }
    }
}

void SellShares(User user, std::string ticker_symbol, double share_price, int number_of_shares, double tax_rate, double action_fee) {
    user.AddCash(-action_fee);
    if (user.all_shares.find(ticker_symbol) == user.all_shares.end()) {
        std::cout << "You do not hold any shares of the given ticker symbol" << std::endl;
        std::cout << "You can not open short positions in this brokerage account" << std::endl;
    }
    else {
        for (int i = 0; i < number_of_shares; i++) {
            double profit = (share_price - user.all_shares[ticker_symbol].front().getSharePrice());
            if (profit < 0) {
                user.AddTaxShield(-profit);
            }
            else {
                if (user.getTaxShield() > profit) {
                    user.AddTaxShield(-profit);
                    user.AddCash(profit);
                }
                else {
                    user.AddCash(user.getTaxShield());
                    profit -= user.getTaxShield();
                    user.AddTaxShield(-user.getTaxShield());
                    double tax_payed = profit - profit*tax_rate;
                    std::cout << "Payed taxes: " + std::to_string(tax_payed) << std::endl;
                    user.AddCash(profit - tax_payed);
                }
            }
            user.all_shares[ticker_symbol].pop_front();
        }
    }
}

int main() {

    std::cout << "--------- Stock Market Tax Calculator ---------\n\n\n" << std::endl;

    std::string user_name;
    double initial_cash;

    std::cout << "Please Enter Your Name: " << std::endl;
    std::cin >> user_name;
    std::cout << "Initial Cash position (in $): " << std::endl;
    std::cin >> initial_cash;
    User user = User(user_name, initial_cash);

    double tax_rate;
    double action_fee;

    std::cout << "What is your tax rate? (enter a number representing the % value): " << std::endl;
    std::cin >> tax_rate;
    tax_rate /= 100;
    std::cout << "Your broker's action fee (in $): " << std::endl;
    std::cin >> action_fee;

    // Main loop
    bool exit = false;
    while (not exit) {

        int action;
        std::cout << "[1] Show My Positions" << std::endl;
        std::cout << "[2] Buy Shares" << std::endl;
        std::cout << "[3] Sell Shares" << std::endl;
        std::cout << "[4] Add Cash" << std::endl;
        std::cout << "[0] Exit" << std::endl;
        std::cin >> action;

        if (action == 1) {
            std::cout << user.getName() + "'s brokerage account" << std::endl;
            std::cout << "Current Cash Position: " + std::to_string(user.getCash()) << std::endl;
            std::cout << "Current Tax Shild: " + std::to_string(user.getTaxShield());
            if (not user.all_shares.empty()) {
                for (auto i : user.all_shares) {
                    std::cout << "Ticker Symbol: " + i.first << std::endl;
                    std::cout << "Shares Owned: " + std::to_string(user.getShareCount(i.first)) << std::endl;
                    std::cout << "Average Price: " + std::to_string(user.getAveragePrice(i.first)) << std::endl;
                    std::cout << "---------------------------" << std::endl;
                }
            }
        }

        else if (action == 2) {
            std::string ticker_symbol;
            double share_price;
            int quantity;
            std::cout << "Enter Ticker Symbol: " << std::endl;
            std::cin >> ticker_symbol;
            std::cout << "Share Price: " << std::endl;
            std::cin >> share_price;
            std::cout << "Quantity: " << std::endl;
            std::cin >> quantity;
        }

        else if (action == 3) {
            // code
        }
        
        else if (action == 4) {
            // code
        }
        
        else if (action == 0) {
            exit = true;
        }

        else {
            std::cout << "Invalid Action. Choose Again." << std::endl;
        }

    }
    std::cout << "Program closed" << std::endl;
}
