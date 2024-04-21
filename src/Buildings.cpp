#include "headers/Buildings.h"

Buildings::Buildings(int w_c, int g_c, int f_c, std::string _type, int _in) : wood_cost(w_c), gold_cost(g_c), food_cost(f_c), type(_type), income(_in)
{

}

int Buildings::getIncome() const
{
	return this->income;
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


GMine::GMine() : Buildings(50, 50, 0, "g_mine", 10) {}

SawMill::SawMill() : Buildings(25, 100, 0, "w_mine", 10){}
