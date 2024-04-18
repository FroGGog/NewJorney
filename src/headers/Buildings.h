#pragma once
#include <string>

class Buildings
{

protected:
	std::string type;
	int wood_cost, gold_cost, food_cost;

public:
	Buildings(int w_c, int g_c, int f_c,std::string _type);

	bool checkEnoughtRes(int w, int g, int f);

	void MinusCost(int& g, int& w, int& f);

	std::string getType() const;

};

class GMine : public Buildings
{
private:
	
	int gold_income;

public:

	GMine();

	int getIncome() const;
	

};