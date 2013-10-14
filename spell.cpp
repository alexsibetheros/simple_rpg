#include "header.h"

using namespace std;

Spell::Spell(const std::string tname, int tprice, int tminlvl ,int tmana, int tdmg,int tcntr,int tablty)
:name(tname),price(tprice),minimum_lvl(tminlvl),mana_req(tmana),S_damage(tdmg),counter(tcntr),ability(tablty){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string Spell::getname(void)
{
	return name;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Spell::getprice(void)
{
	return price;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Spell::getminlvl(void)
{
	return minimum_lvl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Spell::get_mana(void)
{
	return mana_req;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Spell::get_damage(void)
{
	return S_damage;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Spell::get_counter(void)
{
	return counter;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Spell::get_ability(void)
{
	return ability;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Spell::~Spell(void){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Spell::able(int tlvl,int tmoney){                                          //checks level and price
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

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IceSpell::IceSpell(const std::string tname, int tprice, int tminlvl ,int tmana, int tdmg,int tcntr,int tablty)
:Spell( tname , tprice, tminlvl, tmana, tdmg , tcntr, tablty ){}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void IceSpell::printSpell(void)
{
cout<<left
		<<setw(15)<<getname();
		cout<<"$";
		cout<<setw(5)<<getprice();
		cout<<"lvl:";
		cout<<setw(5)<<getminlvl();
		cout<<"mp:";
		cout<<setw(5)<<get_mana();
		cout<<"dmg:";
		cout<<setw(5)<<get_damage();
		cout<<"rounds:";
		cout<<setw(5)<<get_counter();
		cout<<"Attack:-";
		cout<<setw(2)<<get_ability();
		cout<<"%";
		cout<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

IceSpell::~IceSpell(void){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IceSpell::use(Monster* mn,Hero* hn)                                        //applies spell, or doesn't if the mp of the hero is not
{                                                                               //enough or the monster is already under the effect of
	 if(mn->Frozen()){cout<<"\nUnable to cast Ice spell, monster already frozen.\n"<<endl;return false;}
	 if( !(hn->get_mp())>=get_mana() ){cout<<"\nUnable to cast Ice spell,not enough magical power."<<endl; return false;}
	 mn->take_damage( get_damage() );                                           // a same type spell
	 mn->Ffrozen( get_counter(), get_ability() );
	 hn->set_mana(-get_mana());
	 cout<<"Successfully ice spell"<<endl;
	 return true;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FireSpell::FireSpell(const std::string tname, int tprice, int tminlvl ,int tmana, int tdmg,int tcntr,int tablty)
:Spell( tname , tprice, tminlvl, tmana, tdmg , tcntr, tablty ){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void FireSpell::printSpell(void)
{
cout<<left
		<<setw(15)<<getname();
		cout<<"$";
		cout<<setw(5)<<getprice();
		cout<<"lvl:";
		cout<<setw(5)<<getminlvl();
		cout<<"mp:";
		cout<<setw(5)<<get_mana();
		cout<<"dmg:";
		cout<<setw(5)<<get_damage();
		cout<<"rounds:";
		cout<<setw(5)<<get_counter();
		cout<<"Defense:-";
		cout<<setw(2)<<get_ability();
		cout<<"%";
		cout<<endl;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

FireSpell::~FireSpell(void){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool FireSpell::use(Monster* mn,Hero* hn)
{    if(mn->Burned()){cout<<"\nUnable to cast Fire spell, monster already burned.\n"<<endl;return false;}
	 if( !(hn->get_mp())>=get_mana() ){cout<<"\nUnable to cast Fire spell,not enough magical power."<<endl; return false;}
	 mn->take_damage( get_damage() );
	 mn->Fburned( get_counter(), get_ability() );
	 hn->set_mana(-get_mana());
	 cout<<"Successfully fire spell"<<endl;
	 return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LightningSpell::LightningSpell(const std::string tname, int tprice, int tminlvl ,int tmana, int tdmg,int tcntr,int tablty)
:Spell( tname , tprice, tminlvl, tmana, tdmg , tcntr, tablty )
{
	/*cout<<"Creating Item called: "<<name<<" with price="<< price<<" and minimum level= "<< minimum_lvl<< endl;*/
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LightningSpell::printSpell(void)
{
cout<<left
		<<setw(15)<<getname();
		cout<<"$";
		cout<<setw(5)<<getprice();
		cout<<"lvl:";
		cout<<setw(5)<<getminlvl();
		cout<<"mp:";
		cout<<setw(5)<<get_mana();
		cout<<"dmg:";
		cout<<setw(5)<<get_damage();
		cout<<"rounds:";
		cout<<setw(5)<<get_counter();
		cout<<"Agility:-";
		cout<<setw(2)<<get_ability();
		cout<<"%";
		cout<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

LightningSpell::~LightningSpell(void){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool LightningSpell::use(Monster* mn,Hero* hn)
{
     if(mn->Stunned()){cout<<"\nUnable to cast Lightning spell, monster already stunned.\n"<<endl;return false;}
	 if( !(hn->get_mp())>=get_mana() ){cout<<"\nUnable to cast Lightning spell,not enough magical power."<<endl; return false;}
	 mn->take_damage( get_damage() );
	 mn->Fstunned( get_counter(), get_ability() );
	 hn->set_mana(-get_mana());
	 cout<<"Successfully lightning spell"<<endl;
	 return true;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
