#pragma once


class Guest {
	string fullname;
	string connected_date; //tarix saat
public:
	Guest(string fullname, string date)
	{
		this->setFullname(fullname);
		this->setDate(date);
	}

	// Copy Constructor
	Guest(const Guest& guest)
	{
		this->setFullname(guest.getFullname());
		this->setDate(guest.getDate());
	}

	void setFullname(string fullname)
	{
		if (fullname.size() < 1) throw invalid_argument("fullname is not given");
		this->fullname = fullname;
	}

	void setDate(string date)
	{
		if (date.size() < 1) throw invalid_argument("date is not given");
		this->connected_date = date;
	}

	string getFullname() const {
		return this->fullname;
	}

	string getDate() const {
		return this->connected_date;
	}

	void print()
	{
		cout << "Fullname: " << fullname << endl;
		cout << "Connection date: " << connected_date << endl;
	}

};

class Admin {
	string _username;
	string _password;
public:

	Admin(string username, string password) {
		this->SetUsername(username);
		this->SetPassword(password);
	}

	// Copy Constructor
	Admin(const Admin& admin) {
		this->SetUsername(admin.GetUsername());
		this->SetPassword(admin.GetPassword());
	}

	void SetUsername(string username)
	{
		if (username.size() < 5) throw length_error("username must contain min 5 symbols");
		if (!(username[0] >= 65 && username[0] <= 90))
			throw invalid_argument("first symbol must be uppercase letter");

		this->_username = username;
	}

	void SetPassword(string password)
	{
		if (password.size() < 5) throw length_error("password must contain at least 5 symbols");
		this->_password = password;
	}

	string GetUsername() const {
		return this->_username;
	}

	string GetPassword()const {
		return this->_password;
	}

};

class Product {
	static int _id;
	int id;
	string _name;
	string _description = " ";
	double _price;
	double _discount = 0;
	int _quantity;
	double _tax = 0;
public:

	Product(string name, double price, int quantity = 1)
	{
		id = ++_id;
		this->setName(name);
		this->setPrice(price);
		this->setQuantity(quantity);
	}


	Product(string name, string description, double price, double discount, double tax, int quantity = 1)
		:Product(name, price, quantity)
	{
		this->setDescription(description);
		this->setDiscount(discount);
		this->setTax(tax);
	}

	// Copy constructor
	Product(const Product& product)
		:Product(product.getName(), product.getDescription(), product.getPrice(), product.getDiscount(), product.getTax(), product.getQuantity())
	{
		this->id = product.id;
	}

	//Accessors
	void setName(string name)
	{
		if (name.size() < 3) throw length_error("product name must contain at least 3 symbols");
		this->_name = name;
	}

	void setDescription(string description)
	{
		if (description.size() < 5) throw length_error("product description must contain at least 5 symbols");
		this->_description = description;
	}

	void setPrice(double price)
	{
		if (price > 0)
			this->_price = price;
		else
			throw invalid_argument("product price can not be zero or negative");
	}

	void setDiscount(double discount)
	{
		if (discount < 0) throw invalid_argument("discount can not be zero");
		this->_discount = discount;
	}

	void setTax(double tax)
	{
		if (tax < 0) throw invalid_argument("tax can not be zero");
		this->_tax = tax;
	}

	void setQuantity(int quantity)
	{
		if (quantity < 1) throw invalid_argument("quantity should be min 1");
		this->_quantity = quantity;
	}

	string getName()const { return this->_name; }
	string getDescription()const { return this->_description; }
	double getPrice()const { return this->_price; }
	double getDiscount()const { return this->_discount; }
	double getTax()const { return this->_tax; }
	int getId()const { return this->id; }
	int getQuantity()const { return this->_quantity; }

	void print()
	{
		cout << "ID: " << id << endl;
		cout << "Product name: " << _name << endl;
		cout << "Description: " << _description << endl;
		cout << "Price: " << _price << endl;
		cout << "Quantity: " << _quantity << endl;
		cout << "Discount: " << _discount << endl;
		cout << "Tax: " << _tax << endl;
	}

	double GetDiscountPrice()
	{
		int discount_price = _price - (_price * _discount) / 100;
		return discount_price;
	}
};

int Product::_id = 0;


template<typename T>
class DbSet {
	T** items = nullptr;
	int count = 0;
public:
	void add(const T* item)
	{
		if (items == nullptr)
		{
			items = new T * [++count];
			items[0] = new T(*item);
		}
		else
		{
			T** nItems = new T * [count + 1];
			for (size_t i = 0; i < count; i++)
				nItems[i] = items[i];


			nItems[count] = new T(*item);
			delete[] items;
			items = nItems;
			count++;
		}
	}

	bool checkId(const int& id)
	{
		for (size_t i = 0; i < count; i++)
			if (items[i]->getId() == id)
				return true;
		return false;

	}

	void deleteById(const int& id)
	{
		if (checkId(id))
		{
			T** nItems = new T * [count - 1];
			int index = 0;

			for (size_t i = 0; i < count; i++)
			{
				if (items[i]->getId() != id)
					nItems[index++] = items[i];
				else
					delete items[i];
			}
			delete[] items;
			items = nItems;
			count--;
		}
	}

	T* getItem(const int& id)
	{
		if (checkId(id))
			for (size_t i = 0; i < count; i++)
				if (items[i]->getId() == id)
					return items[i];
		return nullptr;
	}

	int getCount() const
	{
		return count;
	}

	T** getItems() const
	{
		return items;
	}

	void printItems()
	{
		if (items != nullptr)
			for (size_t i = 0; i < count; i++)
			{
				items[i]->print();
				cout << endl;
			}
		else
			cout << "elements not found";
	}

	void DeleteAllItems()
	{
		for (size_t i = 0; i < count; i++)
		{
			if (items[i] != nullptr)
			{
				delete items[i];
				items[i] = nullptr;
			}
		}

		delete[] items;
		items = nullptr;
	}

	void ShowPriceById(const int& id)
	{
		if (checkId(id))
		{
			for (size_t i = 0; i < count; i++)
				if (items[i]->getId() == id)
					cout << items[i]->getPrice() << endl;
		}
		else
			throw invalid_argument("product with this Id not found!!!");

	}

	void ShowDetailsById(const int& id)
	{
		if (checkId(id))
		{
			for (size_t i = 0; i < count; i++)
				if (items[i]->getId() == id)
					items[i]->print();
		}
		else
			throw invalid_argument("product with this Id not found!!!");
	}

	void ShowDiscountPriceById(const int& id)
	{
		if (checkId(id))
		{
			for (size_t i = 0; i < count; i++)
			{
				if (items[i]->getId() == id)
				{
					if (items[i]->getDiscount() != 0)
						cout << "Discount price: " << items[i]->GetDiscountPrice() << endl;
					else
						cout << "There is no discount on this product" << endl;
				}
			}
		}

		else
			throw invalid_argument("product with this Id not found!!!");
	}

	void UpdateProduct(const int& id)
	{
		if (checkId(id))
		{
			cin.ignore();
			string name, description;
			double price, discount, tax;
			int quantity;

			cout << "enter new name: ";
			getline(cin, name);
			cout << "enter description: ";
			getline(cin, description);
			cout << "enter new price: ";
			cin >> price;
			cout << "enter discount: ";
			cin >> discount;
			cout << "enter tax: ";
			cin >> tax;
			cout << "product quantity: ";
			cin >> quantity;

			for (size_t i = 0; i < count; i++)
			{
				if (items[i]->getId() == id)
				{
					items[i]->setName(name);
					items[i]->setDescription(description);
					items[i]->setPrice(price);
					items[i]->setDiscount(discount);
					items[i]->setTax(tax);
					items[i]->setQuantity(quantity);

				}
			}
		}

		else
			throw invalid_argument("product with this Id not found!!!");



	}

	~DbSet()
	{
		if (items != nullptr)
		{
			for (size_t i = 0; i < count; i++)
			{
				if (items[i] != nullptr)
				{
					delete items[i];
					items[i] = nullptr;
				}
			}

			delete[] items;
		}
	}
};


class Database {
public:
	DbSet<Product>products;
	DbSet<Admin>admins;
	DbSet<Guest>guest;


	bool checkAdmin(string username)
	{
		for (size_t i = 0; i < admins.getCount(); i++)

			if (admins.getItems()[i]->GetUsername() == username)
				return true;
		return false;
	}

	bool adminLogin(string username, string password)
	{
		for (size_t i = 0; i < admins.getCount(); i++)
			if (admins.getItems()[i]->GetUsername() == username && admins.getItems()[i]->GetPassword() == password)
				return true;
		return false;
	}
};





void start() {

	Database db;

	Admin* admin = new Admin("Admin", "admin");
	db.admins.add(admin);

	////////////////////////////////////////////////////////////////////////////////////

	string menuOne = R"(
				[1] => As Gusest
				[2] => As Admin
				[0] => Exit
		)";

	string menuAdmin = R"(
				[1] => Add Product
				[2] => Delete Product
				[3] => Show All Products
				[4] => Show All Guests
				[5] => Update Product
				[6] => Delete All Products
				[7] => Delete All Guests
				[8] => Show Total price by Id
				[0] => Exit
		)";

	string menuGuest = R"(    
                [1] => Buy Product
                [2] => Show Details of product
                [3] => Show Discount Price of Product
                [4] => Show All Products 
                [0] => Exit
)";


	while (true)
	{
		cout << menuOne << endl;
		cout << "Enter your choice: ";

		int select;
		cin >> select;

		if (select == 1)
		{
			system("cls");
			string fullname, date;
			try
			{
				cin.ignore();
				cout << "enter fullname: ";
				getline(cin, fullname);
				cout << "enter date and time: ";
				getline(cin, date);

				Guest* nGuest=new Guest(fullname, date);
				db.guest.add(nGuest);

				while (true)
				{
					cout << menuGuest << endl;
					int choice;
					cout << "enter your choice: ";
					cin >> choice;

					if (choice == 1)
					{
						system("cls");
						int id;
						cout << "enter product id: ";
						cin >> id;
						db.products.deleteById(id);
					}

					else if (choice == 2)
					{
						system("cls");
						int id;
						cout << "enter product id: ";
						cin >> id;
						db.products.ShowDetailsById(id);

					}

					else if (choice == 3)
					{
						system("cls");
						int id;
						cout << "enter product id: ";
						cin >> id;
						db.products.ShowDiscountPriceById(id);
					}

					else if (choice == 4)
					{
						system("cls");
						db.products.printItems();
					}

					else if (choice == 0)
					{
						system("cls");
						break;
					}

					else
						cout << "invalid input" << endl;
				}
			}
			catch (exception ex)
			{
				cout << ex.what();
			}

			catch (...)
			{
				cout << "error happened";
			}
		}

		else if (select == 2)
		{
			cin.ignore();
			string username, password;
			cout << "username: ";
			getline(cin, username);
			cout << "password: ";
			getline(cin, password);
			try
			{
				if (db.checkAdmin(username))
				{
					if (db.adminLogin(username, password))
					{
						system("cls");
						while (true)
						{
							cout << menuAdmin << endl;
							int choice;
							cout << "enter your choice: ";
							cin >> choice;

							if (choice == 1)
							{
								system("cls");
								cin.ignore();
								string name, description;
								double price, discount, tax;
								int quantity;

								cout << "enter product name: ";
								getline(cin, name);
								cout << "enter product description: ";
								getline(cin, description);
								cout << "enter price: ";
								cin >> price;
								cout << "enter discount(%): ";
								cin >> discount;
								cout << "enter tax: ";
								cin >> tax;
								cout << "enter product quantity: ";
								cin >> quantity;

								Product* newProduct = new Product(name, description, price, discount, tax, quantity);
								db.products.add(newProduct);
							}

							else if (choice == 2)
							{
								system("cls");
								int id;
								cout << "enter product id: ";
								cin >> id;

								db.products.deleteById(id);
							}

							else if (choice == 3)
							{
								system("cls");
								db.products.printItems();
							}

							else if (choice == 4)
							{
								system("cls");
								db.guest.printItems();
							}

							else if (choice == 5)
							{
								system("cls");
								int id;
								cout << "enter product id: ";
								cin >> id;
								db.products.UpdateProduct(id);
							}

							else if (choice == 6)
							{
								system("cls");
								db.products.DeleteAllItems();
							}

							else if (choice == 7)
							{
								//system("cls");
								db.guest.DeleteAllItems();
							}

							else if (choice == 8)
							{
								//system("cls");
								int id;
								cout << "enter id: ";
								cin >> id;
								db.products.ShowDiscountPriceById(id);
							}

							else if (choice == 0)
							{
								system("cls");
								break;
							}
							else
								throw invalid_argument("incorrect input");

						}

					}
					else
						throw invalid_argument("incorrect password");
				}
				else
					throw invalid_argument("admin not found");

			}
			catch (exception ex)
			{
				cout << ex.what();
			}

			catch (...)
			{
				cout << "error happened";
			}
		}

		else if (select == 0)
		{
			system("cls");
			cout << "Bye Bye...";
			return;
		}

		else
		{
			system("cls");
			cout << "Invalid input" << endl;
		}

	}
}






