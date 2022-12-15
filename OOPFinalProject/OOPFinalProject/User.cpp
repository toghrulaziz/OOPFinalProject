#include "Admin.h"


void Register() {
	string username;
	string password;
	string name;
	string surname;
	string phoneNumber;

	cout << "Insert Name : ", cin >> name;
	cout << "Insert Surname : ", cin >> surname;
	cout << "Insert Phone Number : ", cin >> phoneNumber;

	if (phoneNumber.size() != 10) {
		throw InvalidArgumentException("This phone number is not valid!", __LINE__, "Register()", __TIME__);
	}
	cout << "Insert username : ", cin >> username;
	if (username.size() < 6) {
		throw InvalidArgumentException("This username is not valid!", __LINE__, "Register()", __TIME__);
	}
	if (username.at(0) > char(97) && username.at(0) < char(122)) {
		throw InvalidArgumentException("The first character of the username must be capitalized.", __LINE__, "Register()", __TIME__);
	}
	cout << "Insert password : ", cin >> password;
	if (password.size() < 6) {
		throw InvalidArgumentException("This password is not valid.", __LINE__, "Register()", __TIME__);
	}
}



void MainMenu();
void Menu();
void DeleteFromBasket(int id);



void Basket() {
	ifstream basket1("Basket.txt");
	string l;
	double bill = 0;

	while (getline(basket1, l)) {
		int basketId = nlohmann::json::parse(l)["dish id"];
		string basketName = nlohmann::json::parse(l)["dish name"];
		double basketPrice = nlohmann::json::parse(l)["dish price"];
		cout << "Dish Id : " << basketId << " | " << "Dish Name : " << basketName << " | " << "Dish Price : " << basketPrice << endl;
		bill += basketPrice;
	}
	basket1.close();

	cout << "\nBill : " << bill << " $" << endl;
	cout << "\n\n1. Buy" << "\n2. Delete from basket\n" << "3. Back\n";
	int sechim;
	cout << "\n\nInsert your choose : ", cin >> sechim;

	if (sechim == 3) {
		system("cls");
		Menu();
	}
	else if (sechim == 1) {
		vector<int> basketIds;
		ifstream readBasketId("Basket.txt");
		string basketString;
		int i;
		while (getline(readBasketId, basketString)) {
			i = nlohmann::json::parse(basketString)["dish id"];
			basketIds.push_back(i);
		}
		readBasketId.close();
		ifstream readDishId("Dish.txt");
		string lineforDish;
		string ingsss;
		int size;
		while (getline(readDishId, lineforDish)) {

			for (int i = 0; i < basketIds.size(); i++) {

				if (nlohmann::json::parse(lineforDish)["Dish Id"] == basketIds[i]) {

					size = nlohmann::json::parse(lineforDish)["Dish's Ingredient"].size();

					for (int i = 0; i < size; i++) {

						ingsss = nlohmann::json::parse(lineforDish)["Dish's Ingredient"].at(i);

						ifstream readIngres("Ingredient.txt");
						string lineforIngre;

						while (getline(readIngres, lineforIngre)) {

							if (nlohmann::json::parse(lineforIngre)["Ingredient Name"] == ingsss) {
								string name4ings = nlohmann::json::parse(lineforIngre)["Ingredient Name"];
								int count4ings = nlohmann::json::parse(lineforIngre)["Ingredient Count"];
								int id4ings = nlohmann::json::parse(lineforIngre)["Ingredient Id"];
								Ingredient temp = Ingredient(name4ings, count4ings, id4ings);
								temp.Decrease();
							}

						}
						readIngres.close();
					}
				}
			}
		}
		readDishId.close();


		system("cls");
		cout << "Bill : " << bill << " $" << endl;
		double money;
		cout << "Pay money\n", cin >> money;

		if (money > bill) {
			double remainder = money - bill;
			cout << "Remainder : " << remainder << "$" << endl;
			cout << "\tBon Appetit!!!\n";
			return;
		}
		else if (money == bill) {
			cout << "\tBon Appetit!!!\n";
			return;
		}
		else if (money < bill) {
			throw InvalidArgumentException("Unfortunately, money is not enough!!!\n\n", __LINE__, "Pay()", __TIME__);
		}
	}
	else if (sechim == 2) {
		system("cls");
		int i;
		cout << "Insert the id of the dish you want to remove from the basket : ", cin >> i;
		DeleteFromBasket(i);
	}
}





void DeleteFromBasket(int i) {
	ifstream read("Basket.txt");
	string sl;

	while (getline(read, sl)) {
		if (nlohmann::json::parse(sl)["dish id"] != i) {
			system("cls");
			int i = nlohmann::json::parse(sl)["dish id"];
			string name = nlohmann::json::parse(sl)["dish name"];
			double price = nlohmann::json::parse(sl)["dish price"];
			nlohmann::json json;
			json["dish id"] = i;
			json["dish name"] = name;
			json["dish price"] = price;
			ofstream basket("Basket1.txt", ios::app);
			basket << json << endl;
			basket.close();
		}
	}
	read.close();

	ifstream readBasket1("Basket1.txt");
	string stringline;

	while (getline(readBasket1, stringline)) {
		int i = nlohmann::json::parse(stringline)["dish id"];
		string name = nlohmann::json::parse(stringline)["dish name"];
		double price = nlohmann::json::parse(stringline)["dish price"];

		nlohmann::json json1;
		json1["dish id"] = i;
		json1["dish name"] = name;
		json1["dish price"] = price;

		fstream writeToBasketFromBasket1("Basket.txt", ios::out);
		writeToBasketFromBasket1 << json1 << endl;
		writeToBasketFromBasket1.close();
	}
	readBasket1.close();

	cout << "Dish removed from basket\n\n";
	cout << "1. Back\n";
	int c;
	cout << "Insert your choose : ", cin >> c;
	if (c == 1) {
		system("cls");
		Basket();
	}
	else
		return;
}




void AddBasket(int id) {
	ifstream read("Dish.txt");
	string lines;

	while (getline(read, lines)) {
		if (nlohmann::json::parse(lines)["Dish Id"] == id) {
			system("cls");
			int i = nlohmann::json::parse(lines)["Dish Id"];
			string name = nlohmann::json::parse(lines)["Dish Name"];
			double price = nlohmann::json::parse(lines)["Dish Price"];
			nlohmann::json json;
			json["dish id"] = i;
			json["dish name"] = name;
			json["dish price"] = price;
			ofstream basket("Basket.txt", ios::app);
			basket << json << endl;
			basket.close();
		}
	}
	read.close();

	cout << "Dish Added Basket\n";
	cout << "1. Basket" << "\n2. Back\n";
	int choo;
	cout << "\n\nInsert your choose : ", cin >> choo;

	if (choo == 2) {
		system("cls");
		Menu();
	}
	else if (choo == 1) {
		system("cls");
		Basket();
	}
}




void Menu() {
	ifstream readFile("Dish.txt");
	string line;
	int s;
	cout << "\t******** DISH ********\n\n";
	while (getline(readFile, line)) {
		int id = nlohmann::json::parse(line)["Dish Id"];
		string name = nlohmann::json::parse(line)["Dish Name"];
		cout << id << ". " << name << endl;
		s = id + 1;
	}
	readFile.close();

	cout << s << ". Back";
	cout << "\n\nInsert your choose : ";
	int ch;
	cin >> ch;

	if (ch == s) {
		system("cls");
		MainMenu();
	}

	ifstream read("Dish.txt");
	string lines;

	while (getline(read, lines)) {
		if (nlohmann::json::parse(lines)["Dish Id"] == ch) {
			system("cls");
			cout << "\tDish's Info\n\n";
			cout << "Dish Id : " << nlohmann::json::parse(lines)["Dish Id"] << endl;
			cout << "Dish Name : " << nlohmann::json::parse(lines)["Dish Name"] << endl;
			cout << "Dish Price : " << nlohmann::json::parse(lines)["Dish Price"] << '$' << endl;
			cout << "Dish's Ingredients : " << nlohmann::json::parse(lines)["Dish's Ingredient"] << "\n\n";
		}
	}
	read.close();

	cout << "1. Add Basket\n" << "2. Back\n";
	int choo;
	cout << "\n\nInsert your choose : ";
	cin >> choo;

	if (choo == 2) {
		system("cls");
		Menu();
	}
	else if (choo == 1) {
		AddBasket(ch);
	}
	else
		return;
}



void MainMenu() {
	cout << "\tUser Panel\t\n\n";
	cout << "1. Sign Up\n" << "2. Exit\n\n";
	int choose;
	cout << "Insert your choose : ";
	cin >> choose;

	if (choose == 1) {
		system("cls");
		try
		{
			Register();
		}
		catch (Exception ex)
		{
			cout << ex.GetText();
		}

		system("cls");
		cout << "\t Registration completed successfully!!!\t\n";
		cout << "1. Menu\n" << "2. Back\n\n";
		int cho;
		cout << "Insert your choose : ";
		cin >> cho;

		if (cho == 1) {
			system("cls");
			Menu();
		}
		else if (cho == 2) {
			system("cls");
			MainMenu();
		}
	}
	else if (choose == 2)
		return;
	else
		return;
}


void main() {
	cout << "\t\tRestaurant\t\n\n";
	cout << "\tAre you admin or user ?\t\n\n";
	cout << "1. Admin\n" << "2. User\n";
	int choo;
	cout << "\nInsert your choose : ", cin >> choo;
	if (choo == 1) {
		system("cls");
		SingIn();
		system("cls");

		cout << "\tAdmin Panel\t\n\n";

		cout << "1. Add Dish\n" << "2. Add Ingredient\n" << "3. Exit\n\n";

		int adminChoo;
		cout << "Insert your choose : ", cin >> adminChoo;

		if (adminChoo == 1) {
			system("cls");
			string dishName;
			double dishPrice;
			int cinIngreId;
			int countIngredient;
			vector<Ingredient> ingss;

			cout << "\nInsert Dish name : ", cin >> dishName;
			cout << "\nInsert Dish price : ", cin >> dishPrice;
			cout << "\nInsert Ingredient count : ", cin >> countIngredient;

			int ingid;
			string ingName;
			int ingCount;
			cout << endl << endl;

			ifstream readFile("Ingredient.txt");
			string line;

			while (getline(readFile, line)) {
				ingid = nlohmann::json::parse(line)["Ingredient Id"];
				ingName = nlohmann::json::parse(line)["Ingredient Name"];
				ingCount = nlohmann::json::parse(line)["Ingredient Count"];
				cout << "Ingredient Id : " << ingid << "    " << "Ingredient Name : " << ingName << "    " << "Ingredient Count : " << ingCount << endl;
			}
			readFile.close();

			int n = 0;
			while (n < countIngredient) {
				cout << "\n Insert the id of the ingredients needed for the dish : ", cin >> cinIngreId;
				int ingid1;
				string ingName1;
				int ingCount1;
				ifstream read("Ingredient.txt");
				string lines;
				while (getline(read, lines)) {
					if (nlohmann::json::parse(lines)["Ingredient Id"] == cinIngreId) {
						ingid1 = nlohmann::json::parse(lines)["Ingredient Id"];
						ingName1 = nlohmann::json::parse(lines)["Ingredient Name"];
						ingCount1 = nlohmann::json::parse(lines)["Ingredient Count"];
						ingss.push_back(Ingredient(ingName1, ingCount1));
					}
				}
				read.close();
				n++;
			}

			int dishId;
			ifstream readDish("Dish.txt");
			string lineDish;
			
			while (getline(readDish, lineDish)) {
				dishId = nlohmann::json::parse(lineDish)["Dish Id"];
			}

			
			readDish.close();
			dishId++;
			Dish dish = Dish(dishName, dishPrice, ingss, dishId);
			dish.AddDish();
		}
		else if (adminChoo == 2) {
			system("cls");
			string ingName;
			int ingCount;
			cout << "\nInsert Inredient name : ", cin >> ingName;
			cout << "\nInsert Ingredient count : ", cin >> ingCount;
			int ingreId;

			ifstream readIngredient("Ingredient.txt");
			string lineIngredient;

			while (getline(readIngredient, lineIngredient)) {
				ingreId = nlohmann::json::parse(lineIngredient)["Ingredient Id"];
			}

			readIngredient.close();
			ingreId++;
			Ingredient ingre = Ingredient(ingName, ingCount, ingreId);
			ingre.AddIngredient();
			cout << "\nIngredient successfully added!!!\n\n";
		}
		else if (adminChoo == 3) {
			return;
		}
		else
			return;
	}
	else if (choo == 2) {
		system("cls");
		try
		{
			MainMenu();
		}
		catch (Exception ex)
		{
			cout << ex.GetText() << endl;
		}
	}
	else
		return;



	//SingIn();
	/*Ingredient i = Ingredient("Pomidor", 23);
	Ingredient i1 = Ingredient("Yumurta", 50);

	vector<Ingredient> ings;
	ings.push_back(i);
	ings.push_back(i1);

	Ingredient i2 = Ingredient("Biber", 25);
	Ingredient i3 = Ingredient("Kolbasa", 9);
	Ingredient i4 = Ingredient("Pendir", 13);
	Ingredient i5 = Ingredient("Un", 50);

	vector<Ingredient> ings2;
	ings2.push_back(i);
	ings2.push_back(i2);
	ings2.push_back(i3);
	ings2.push_back(i4);
	ings2.push_back(i5);

	Dish d = Dish("Pomidor - Yumurta", 2.3, ings);
	Dish d1 = Dish("Pizza", 7.4, ings2);*/

	//d.Show();
	//i.AddIngredient();
	//i1.AddIngredient();
	//i2.AddIngredient();
	//i3.AddIngredient();
	//i4.AddIngredient();
	//i5.AddIngredient();
	//i.Increase();
	//i.Decrease();

	//d.AddDish();
	//d1.AddDish();

	/*try
	{
		MainMenu();
	}
	catch (Exception ex)
	{
		cout << ex.GetText() << endl;
	}*/
}