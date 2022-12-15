#pragma once
#include <iostream>
#include <vector>
#include <nlohmann/json.hpp>
#include <list>
#include <fstream> 


using namespace std;


class Exception : public exception {
    string text;
    int line;
    string source;
    string time;


public:

    Exception(string text, int line, string source, string time) {
        SetText(text);
        SetLine(line);
        SetSource(source);
        SetTime(time);
    }


#pragma region Setters
    void SetText(string text) {
        this->text = text;
    }

    void SetLine(int line) {
        this->line = line;
    }

    void SetSource(string source) {
        this->source = source;
    }

    void SetTime(string time) {
        this->time = time;
    }

#pragma endregion


#pragma region Getters
    string GetText()const { return text; }
    int GetLine()const { return line; }
    string GetSource()const { return source; }
    string GetTime()const { return time; }
#pragma endregion
};



class DatabaseException :public Exception {
public:
    DatabaseException(string text, int line, string source, string time) :Exception(text, line, source, time) {}
};



class InvalidArgumentException :public Exception {
public:
    InvalidArgumentException(string text, int line, string source, string time) :Exception(text, line, source, time) {}
};



////////////////////////////////////////////////////////////////////////////////////




bool SingIn() {
    string username;
    cout << "Insert Username : ";
    cin >> username;

    if (username == "Hakuna") {
        string password;
        cout << "Insert Password : ";
        cin >> password;
        if (password == "Matata") {
            return 1;
        }
        throw InvalidArgumentException("This password is not valid!", __LINE__, "SignIn()", __TIME__);
    }
    else
        throw InvalidArgumentException("This username is not valid!", __LINE__, "SignIn()", __TIME__);
}



class Ingredient {
    string name;
    int count;
    int id;
    static int staticId;

public:

    Ingredient()
    {
        id = staticId++;
    }

    Ingredient(string name, int count)
    {
        id = staticId++;
        SetName(name);
        SetCount(count);
    }

    Ingredient(string name, int count, int id)
    {
        SetName(name);
        SetCount(count);
        this->id = id;
    }

    void SetName(string name) {
        this->name = name;
    }

    void SetCount(int count) {
        this->count = count;
    }

    string GetName()const { return name; }
    int GetCount()const { return count; }
    int GetId()const { return id; }



    void Show() {
        cout << "Id : " << id << "\nIngredient Name : " << name << "\nIngredient Count : " << count << endl << endl;
    }


    void AddIngredient() {
        nlohmann::json json;
        json["Ingredient Id"] = id;
        json["Ingredient Name"] = name;
        json["Ingredient Count"] = count;
        bool check = true;
        string line;
        ifstream readFile("Ingredient.txt");
        while (getline(readFile, line)) {
            if (nlohmann::json::parse(line)["Ingredient Name"] == name) {
                check = false;
                readFile.close();
            }
        }
        if (check) {
            readFile.close();
            ofstream ingre("Ingredient.txt", ios::app);
            ingre << json << endl;
            ingre.close();
        }
    }



    void Increase() {
        nlohmann::json json;
        json["Ingredient Id"] = id;
        json["Ingredient Name"] = name;
        json["Ingredient Count"] = count;
        string line;
        list<nlohmann::json> ings;
        ifstream readFile("Ingredient.txt");
        while (getline(readFile, line)) {
            if (nlohmann::json::parse(line)["Ingredient Name"] == name) {
                nlohmann::json json = nlohmann::json::parse(line);
                json["Ingredient Count"] = json["Ingredient Count"] + 1;
                ings.push_back(json);
            }
            else {
                ings.push_back(nlohmann::json::parse(line));
            }
        }
        readFile.close();
        ofstream ingre("Ingredient.txt", ios::out);
        for (nlohmann::json i : ings) {
            ingre << i << endl;
        }
        ingre.close();
    }



    void Decrease() {
        nlohmann::json json;
        json["Ingredient Id"] = id;
        json["Ingredient Name"] = name;
        json["Ingredient Count"] = count;
        string line;
        list<nlohmann::json> ings;
        ifstream readFile("Ingredient.txt");
        while (getline(readFile, line)) {
            if (nlohmann::json::parse(line)["Ingredient Name"] == name) {
                nlohmann::json json = nlohmann::json::parse(line);
                json["Ingredient Count"] = json["Ingredient Count"] - 1;
                ings.push_back(json);
            }
            else {
                ings.push_back(nlohmann::json::parse(line));
            }
        }
        readFile.close();
        ofstream ingre("Ingredient.txt", ios::out);
        for (nlohmann::json i : ings) {
            ingre << i << endl;
        }
        ingre.close();
    }
};
int Ingredient::staticId = 1;



class Dish {
    int id;
    static int staticId;
    string name;
    double price;
    vector <Ingredient> ings;
    list <string> list;


public:


    Dish()
    {
        id = staticId++;
    }

    Dish(string name, double price, vector<Ingredient> i)
    {
        id = staticId++;
        SetName(name);
        SetPrice(price);
        SetIngs(i);
    }

    Dish(string name, double price, int id)
    {
        SetName(name);
        SetPrice(price);
        this->id = id;
    }

    Dish(string name, double price, vector<Ingredient> i, int id)
    {
        SetName(name);
        SetPrice(price);
        SetIngs(i);
        this->id = id;
    }


    void SetName(string name) {
        this->name = name;
    }

    void SetPrice(double price) {
        this->price = price;
    }

    void SetIngs(vector <Ingredient> ings) {
        for (int i = 0; i < ings.size(); i++) {
            list.push_back(ings[i].GetName());
        }
    }


    string GetName()const { return name; }
    double GetPrice()const { return price; }
    int GetId()const { return id; }


    
    void AddDish() {
        nlohmann::json json;

        json["Dish Id"] = id;
        json["Dish Name"] = name;
        json["Dish Price"] = price;
        json["Dish's Ingredient"] = list;

        bool check = true;
        string line;

        ifstream readFile("Dish.txt");

        while (getline(readFile, line)) {
            if (nlohmann::json::parse(line)["Dish Name"] == name) {
                check = false;
                readFile.close();
            }
        }
        if (check) {
            readFile.close();
            ofstream dish("Dish.txt", ios::app);
            dish << json << endl;
            dish.close();
        }
    }
};
int Dish::staticId = 1;