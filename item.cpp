#include "header.h"

using namespace std;

Item::Item(const std::string tname, int tprice, int tminlvl)
:name(tname),price(tprice),minimum_lvl(tminlvl){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string Item::getname(void)
{
	return name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Item::getprice(void)
{
	return price;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Item::getminlvl(void)
{
	return minimum_lvl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Item::able(int tlvl,int tmoney)                                            //checks level and price
{
	if( (tmoney>=price) && (tlvl>=minimum_lvl) )
		return true;
	else if( tmoney>=price )
	{		
		return false;
	}
	else
	{	
		return false;
	}
}

 Item::~Item(void){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Weapon::Weapon(const std::string tname, int tprice ,int tminlvl,int dmg,bool tdual ):Item(tname,tprice,tminlvl)
{
	damage=dmg;
	dual_weapon=tdual;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Weapon::printItem(void)
{

cout<<left
		<<setw(22)<<getname();
			cout<<"lvl:";	
		cout<<setw(3)<<getminlvl();
		cout<<"$";
		cout<<setw(4)<<getprice();
		cout<<"dmg:";
		cout<<setw(5)<<damage;
		if(dual_weapon==true)
	{	
		cout << left << setw (5);
		cout<<"Two_Handed";
	}	
	else
	{
		cout << left << setw (5);
		cout<<"One_Handed";	
	}
	cout<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Weapon::get_dual(void)
{
	return dual_weapon;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string Weapon::type(void)
{
	return "W";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Weapon::~Weapon(void){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Armor::Armor(const std::string tname, int tprice, int tminlvl , int tprct):Item(tname,tprice,tminlvl)
{
	protection=tprct;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Armor::printItem(void)
{
cout<<left
		<<setw(22)<<getname();
			cout<<"lvl:";	
		cout<<setw(3)<<getminlvl();
		cout<<"$";
		cout<<setw(4)<<getprice();
		cout<<"prtc:";
		cout<<setw(5)<<protection;
		cout<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Armor::get_dual(void)
{
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string Armor::type(void)
{
	return "A";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Armor::~Armor(void){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Potion::Potion(const std::string tname, int tprice, int tstrenght, int tdexterity, int tagility, int tmp, int thp):Item(tname,tprice,1)
{
	Pstrength=tstrenght;
	Pdexterity=tdexterity;
	Pagility=tagility;
	Pmp=tmp;
	Php=thp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Potion::printItem(void)
{
cout<<left
		<<setw(22)<<getname();
		cout<<"$";
		cout<<setw(4)<<getprice();
		
		
	if(Pstrength!=0)
		cout<<" Strenght by "<<Pstrength<<" points"<<endl;
	else if(Pdexterity!=0)
		cout<<" Dexterity by "<<Pdexterity<<" points"<<endl;
	else if(Pagility!=0)
		cout<<" Agility by "<<Pagility<<" points"<<endl;
	else if(Pmp!=0)
		cout<<" MP by "<<Pmp<<" points"<<endl;
	else if(Php!=0)
		cout<<" HP by "<<Php<<" points"<<endl;		
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Potion::get_dual(void)
{
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string Potion::type(void)
{
	return "P";
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Potion::~Potion(void){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
