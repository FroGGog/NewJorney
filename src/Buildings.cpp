#include "headers/Buildings.h"

Buildings::Buildings(int w_c, int g_c, int f_c, std::string _type) : wood_cost(w_c), gold_cost(g_c), food_cost(f_c), type(_type)
{

}

bool Buildings::checkEnoughtRes(int w, int g, int f)
{
	if (w >= this->wood_cost && g >= this->gold_cost && f >= this->food_cost) {
		return true;
	}
	return false;
}

void Buildings::MinusCost(int& g, int& w, int& f)
{
	g -= this->gold_cost;
	w -= this->wood_cost;
	f -= this->food_cost;
}

std::string Buildings::getType() const
{
	return this->type;
}


GMine::GMine() : Buildings(100, 50, 0, "g_mine")
{
	this->gold_income = 10;
}

int GMine::getIncome() const
{
	return this->gold_income;
}


