#include <iostream>
#include <string>
using namespace std;

void menu() {
	cout << "ATM MENU\n";
	cout << "1 - Add money on balance\n";
	cout << "2 - Remove money\n";
	cout << "3 - Show info\n";
	cout << "4 - Show balance\n";
	cout << "5 - Show loan debt\n";
	cout << "==========\n";
	cout << "Enter choice: ";
}

class ArgumentException :public exception {

	string _mess;
public:
	ArgumentException(string mess) :_mess(mess) {}

	const string what() {
		return _mess;
	}
};

class InsufficientFundsException:public exception {
	string _mess;
public:
	InsufficientFundsException(string mess) :_mess(mess) {}

	const string what() {
		return _mess;
	}

};

class BankAccount {
	string _userName;
	int _balance;
	int* _bankId;
	int _creditBalance;
	
public:
	static unsigned int _creditSum;
	BankAccount() = default;
	BankAccount(string name, int balance) {
		srand(time(0));
		_creditBalance = _creditSum;
		_userName = name;
		_balance = balance;
		_bankId = new int[10];
		for (int i = 0; i < 9; i++) {
			_bankId[i] = rand() % 10;
		}
	}

	void setName(string newName) {
		_userName = newName;
	}
	void setBal(int newBalance) {
		_balance = newBalance;
	}



	
	bool isEnough(int removeSum) {
		if (removeSum <= _balance) {
			return true;
		}
		return false;

	}

	int creditDifference(int removeSum) {
		return removeSum - _balance;
	}

	int creditInputIfNeed(int creditBalance) {
		return _creditSum - creditBalance;
	}

	bool useCredit() {
		int answ;
		cout << "Do you want to use credit cost[1 - yes/2 - no]: ";
		cin >> answ;

		if (answ == 1) {
			return true;

		}
		else {
			return false;
		}
		
		
	}
	
	void showBalance() {
		cout << "Current balance: " << _balance << endl;
	}

	void showMoney(int removeSum) {
		cout << "Take your money: " << removeSum << "$\n";
	}


	void inputDepos() {
	
		int newDep;
		cout << "Enter sum: ";
		cin >> newDep;

		if(newDep>=0){
			if (_creditBalance != _creditSum) {
				int difSum = creditInputIfNeed(_creditBalance);
				setBal(newDep - difSum);
				_creditBalance += difSum;
			}
			else {
				int newBal = _balance + newDep;
				setBal(newBal);
			}
		}
		else {
			throw ArgumentException("You try input negative numbers");
		}
		
	}

	void showCreditDebt() {
		cout << "Loan debt: " << _creditSum - _creditBalance << endl;
	}

	void withDraw() {
		int removeSum;
		cout << "Enter remove sum: ";
		cin >> removeSum;

		if (removeSum >= 0) {
			if (isEnough(removeSum)) {
				int newBal = _balance - removeSum;
				setBal(newBal);
			}
			else {
				int removeDiff = creditDifference(removeSum);
				bool choice = useCredit();
				if (choice == true) {
					_creditBalance -= removeDiff;
					setBal(0);
				}
				else {
					cout << "Not enough money" << endl;
				}
			}
		}
		else {
			InsufficientFundsException("You try draw negative num");
		}

		
	}

	void showBankAccInfo() const {
		
		cout << "Name: " << _userName << endl;
		cout << "Balance: " << _balance << endl;
		cout << "Bank ID: " << _bankId << endl;
		cout << "Credit balance: " << _creditBalance << endl;
	}
};

unsigned int BankAccount::_creditSum = 10000;

class ATM {
	unsigned int _atmBalance;
public:
	ATM() = default;
	ATM(int balance) {
		_atmBalance = balance;
	}

	void widthDrawMoney(BankAccount& acc) {
		try {
			acc.withDraw();
		}
		catch (InsufficientFundsException& ex) {
			cout << ex.what() << endl;
		}
	}

	void inputMoney(BankAccount& acc) {
		try {
			acc.inputDepos();
		}
		catch(ArgumentException& ex){
			cout << ex.what() << endl;
		}
	}

};

int main() {
	srand(time(0));
	string name = "Max Teplov";
	int balance = 1000;


	BankAccount banckAcc (name, balance);
	ATM atm;
	int choice;

	
	do {
		menu();
		cin >> choice;

		switch (choice)
		{
		case 1:	
			atm.inputMoney(banckAcc);
			break;	
		case 2:
			atm.widthDrawMoney(banckAcc);
			break;
		case 3:
			banckAcc.showBankAccInfo();
			break;
		case 4:
			banckAcc.showBalance();
			break;
		case 5:
			banckAcc.showCreditDebt();
			break;
		default:
			break;
		}
	} while (choice != 0);

	return 0;
}