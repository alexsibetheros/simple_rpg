#ifndef spell
#define spell

#include <string.h>
#include <string>

class Spell
{
private:	
	std::string name;
	int price;
	int minimum_lvl;
	int mana_req;
	int S_damage;
	int counter;
	int ability;
public:
	Spell(const std::string , int ,int,int, int,int,int);	
    	virtual ~Spell(void);
    
	virtual void printSpell(void)=0;
	std::string getname(void);
	int getprice(void);
	int getminlvl(void);
	int get_mana(void);
	int get_damage(void);
	int get_counter(void);
	int get_ability(void);
	virtual bool use(Monster*,Hero*){return false;}
	bool able(int tlvl,int tmoney);

};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class IceSpell: public Spell
{
public:
	IceSpell(const std::string , int,int,int, int,int,int);
	void printSpell(void);
    bool use(Monster*,Hero*);
	~IceSpell(void);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class FireSpell :public Spell
{
public:
	FireSpell(const std::string , int,int,int, int,int,int);
	void printSpell(void);
	bool use(Monster*,Hero*);
	~FireSpell(void);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class LightningSpell: public Spell
{
public:
	LightningSpell(const std::string , int,int,int, int,int,int);	
	void printSpell(void);
	bool use(Monster*,Hero*);
	~LightningSpell(void);
};

#endif
