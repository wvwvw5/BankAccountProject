#include <iostream>
#include <stdexcept>

class BankAccount {
private:
    int accountNumber;
    double balance;
    double interestRate;

public:
    // Конструктор
    BankAccount(int accountNumber, double initialBalance)
        : accountNumber(accountNumber), balance(initialBalance), interestRate(0.0) {}

    // Внести средства на счет
    void deposit(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Amount to deposit should be greater than zero.");
        }
        balance += amount;
    }

    // Снять средства со счета
    void withdraw(double amount) {
        if (amount <= 0) {
            throw std::invalid_argument("Amount to withdraw should be greater than zero.");
        }
        if (amount > balance) {
            throw std::runtime_error("Insufficient funds.");
        }
        balance -= amount;
    }

    // Получить текущий баланс
    double getBalance() const {
        return balance;
    }

    // Рассчитать и вернуть сумму процентов
    double getInterest() const {
        return balance * interestRate * (1.0 / 12.0);
    }

    // Обновить процентную ставку
    void setInterestRate(double newRate) {
        if (newRate < 0) {
            throw std::invalid_argument("Interest rate cannot be negative.");
        }
        interestRate = newRate;
    }

    // Получить номер банковского счёта
    int getAccountNumber() const {
        return accountNumber;
    }

    // Дружественная функция для перевода средств между счетами
    friend bool transfer(BankAccount& fromAccount, BankAccount& toAccount, double amount);
};

// Реализация функции перевода средств
bool transfer(BankAccount& fromAccount, BankAccount& toAccount, double amount) {
    if (amount <= 0) {
        throw std::invalid_argument("Transfer amount should be greater than zero.");
    }
    if (fromAccount.balance < amount) {
        return false;
    }
    fromAccount.withdraw(amount);
    toAccount.deposit(amount);
    return true;
}

int main() {
    try {
        BankAccount account1(12345, 1000.0);
        BankAccount account2(67890, 500.0);

        std::cout << "Initial balance of account 1: " << account1.getBalance() << std::endl;
        std::cout << "Initial balance of account 2: " << account2.getBalance() << std::endl;

        account1.deposit(200.0);
        std::cout << "Balance of account 1 after deposit: " << account1.getBalance() << std::endl;

        account1.withdraw(100.0);
        std::cout << "Balance of account 1 after withdrawal: " << account1.getBalance() << std::endl;

        account1.setInterestRate(0.05);
        std::cout << "Interest earned on account 1: " << account1.getInterest() << std::endl;

        bool success = transfer(account1, account2, 150.0);
        if (success) {
            std::cout << "Transfer successful." << std::endl;
        }
        else {
            std::cout << "Transfer failed due to insufficient funds." << std::endl;
        }

        std::cout << "Final balance of account 1: " << account1.getBalance() << std::endl;
        std::cout << "Final balance of account 2: " << account2.getBalance() << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
