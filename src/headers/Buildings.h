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

	//minus building cost from player goods
	void MinusCost(int& g, int& w, int& f);

	//return building type - g_mine, w_mine, f_mine - for gold mine, wood mine and food mine
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

// TODO : food farm
// TODO : may be add some new building, like armory, barracks etc