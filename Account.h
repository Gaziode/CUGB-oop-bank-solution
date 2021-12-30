#include "pch.h"
#include "date.h"
#include "string"
#include "accumulator.h"
#include "map"
#include "istream"
#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account;//declare account, avoid conflict

class AccountRecord {
private:
	Date date;
	const Account* account;
	double amount;
	double balance;
	std::string desc;
public:
	AccountRecord(const Date& date, const Account*, double amount, double balance, const std::string& desc);
	void show() const;
};
typedef std::multimap<Date, AccountRecord>RecordMap;

class Account {
private:
	std::string id;
	double balance;
	static double total;
	static RecordMap recordMap;
protected:
	Account(const Date& date, const std::string& id);
	void record(const Date& date, double amount, const std::string& desc);
	void error(const std::string& msg) const;
public:
	const std::string& getId() const { return id; }
	double getBalance() const { return balance; }
	static double getTotal() { return total; }
	virtual void deposit(const Date& date, double amount, const std::string& desc) = 0;
	virtual void withdraw(const Date& date, double amount, const std::string& desc) = 0;
	virtual void settle(const Date& date) = 0;
	virtual void show(std::ostream& out) const;
	static void query(const Date& begin, const Date& end);
};

inline std::ostream& operator<<(std::ostream& out, const Account& account) {
	account.show(out);
	return out;
}

class SavingAccount :public Account {
private:
	Accumulator acc;
	double rate;
public:
	SavingAccount(const Date& date, const std::string& id, double rate);
	double getRate() const { return rate; }
	void deposit(const Date& date, double amount, const std::string& desc);
	void withdraw(const Date& date, double amount, const std::string& desc);
	void settle(const Date& date);
};

class CreditAccount :public Account {
private:
	Accumulator acc;
	double credit;
	double rate;
	double fee;
	double getDebt() const {
		double balance = getBalance();
		return (balance < 0 ? balance : 0);
	}
public:
	CreditAccount(const Date& date, const std::string& id, double credit, double rate, double fee);
	double getGredit() const { return credit; }
	double getRate() const { return rate; }
	double getFee() const { return fee; }
	double getAvailbaleCredit() const {
		if (getBalance() < 0)
			return credit + getBalance();
		else
			return credit;
	}
	void deposit(const Date& date, double amount, const std::string& desc);
	void withdraw(const Date& date, double amount, const std::string& desc);
	void settle(const Date& date);
	virtual void show(std::ostream& out)const;
};

class AccountException :public std::runtime_error {
private:
	const Account* account;
public:
	AccountException(const Account* account, const std::string& msg)
		:runtime_error(msg), account(account) {}
	const Account* getAccount() const { return account; }
};
#endif