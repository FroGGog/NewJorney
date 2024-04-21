#pragma once
#include <string>

class Buildings
{

protected:
	std::string type;
	int wood_cost, gold_cost, food_cost;
	int income;

public:
	Buildings(int w_c, int g_c, int f_c,std::string _type, int _in);

	int getIncome() const;

	bool checkEnoughtRes(int w, int g, int f);

	void MinusCost(int& g, int& w, int& f);

	std::string getType() const;

};

class GMine : public Buildings
{

public:

	GMine();
	
};

class SawMill : public Buildings {

public:

	SawMill();

};