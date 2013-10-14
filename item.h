#ifndef item
#define item

#include <string.h>
#include <string>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Item
{
private:	
	std::string name;
	int price;
	int minimum_lvl;
public:
	Item(const std::string , int ,int);	
	virtual ~Item(void);
	
	int getprice(void);
	int getminlvl(void);
	
	std::string getname(void);

	bool able(int,int);
	
	virtual bool get_dual(void)=0;
	virtual std::string type(void)=0;
	virtual void printItem(void)=0;												//checks level and price
	virtual int getPstrength()	{return 0;}	//potion statistics
	virtual int getPdexterity()	{return 0;}
	virtual int getPagility()	{return 0;}
	virtual int getPmp()		{return 0;}
	virtual int getPhp()		{return 0;}
	virtual int getIdamage(void){return 0;}		//weapon stats
	virtual int getIprotection(void){return 0;}	//armor stats
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Weapon: public Item
{
private:
	bool dual_weapon;                                                           //true:hands required 2
	int damage;
public:
	Weapon(const std::string , int,int,int,bool );	
    	~Weapon(void);

	int getIdamage(void){return damage;}
 	int getIprotection(void){return 0;}
 	void printItem(void);
	bool get_dual(void);
	std::string type(void);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Armor: public Item
{
private:	
	int protection;
public:
	Armor(const std::string , int,int,int );	
	~Armor(void);
	
	int getIdamage(void){return 0;}
 	int getIprotection(void){return protection;}
	void printItem(void);
	bool get_dual(void);
	std::string type(void);
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Potion: public Item
{
private:	
	int Pstrength;
	int Pdexterity;
	int Pagility;
	int Pmp;
	int Php;
public:
	Potion(const std::string ,int,int,int,int,int,int);
    	~Potion(void);

	void printItem(void);
	bool get_dual(void);	
	std::string type(void);
	int getPstrength()	{return Pstrength;}
	int getPdexterity()	{return Pdexterity;}
	int getPagility()	{return Pagility;}
	int getPmp()		{return Pmp;}
	int getPhp()		{return Php;}
	int getPdamage(void);
	int getPprotection(void);

};


#endif

