#ifndef hero
#define hero

#include "living.h"
#include "item.h"

#include <string>
#include <list>

class Item;

class Hero : public Living
{
 	private:
	
	int maxmp;
	int mp;
	int strength;
	int dexterity;
	int agility;
	int experience;
	int maxitems;
	int maxpotions;
	int maxspells;
	int money;
	
	Item* Equiped[2];
	std::list<Item*> weapon_bag;
	std::list<Item*> armor_bag;
	std::list<Spell*> spell_bag;
	std::list<Item*> potion_bag;
	int weapon_size;
	int armor_size;
	int spell_size;
	int potion_size;
	
	
	public:

	Hero(const std::string , int ,int , int , int , int ,Item*,Item* );
	virtual void printHero(void)=0;
	int get_maxmp(void);
	int get_mp(void);
	int get_strength(void);
	int get_dexterity(void);
	int get_agility(void);
	int get_experience(void);
	int get_money(void){return money;}
	int get_weapon_damage(void);
	int get_weapon_defense(void);
	int get_damage(void);
	Item* get_weapon(int);
	Item* get_armor(int);
	int get_exp(){return experience;}
	
		void set_money(int sum);
    	void pay_for_item(int);
    	bool sell_weapon(int);
	bool sell_armor(int);
	bool sell_potion(int);
	bool sell_spell(int);
	void cut_money(void);
	void add_to_money(int m){money+=m;}
	
    	void set_mana(int i){mp=+i;}
	void use_Potion(void);
	Spell* chooseSpell(void);

	void check_lvl();
	void take_damage(int hit);
    	void addXP(int);
	void Hreplenish(void);
	
	void unequip(void);
	void equip(Item*);
	void equip(void);
	
	bool add_to_bag(Item*);
	bool add_to_bag_weapon(Item*);
	bool add_to_bag_armor(Item*);
	bool add_to_bag_potion(Item*);
	bool add_to_bag_spell(Spell*);
	
	void show_equiped(void)	;
	void show_items(void);
	void show_armors(void);
	void show_weapons(void);
	void show_potions(void);
	void show_spell(void);
	
	virtual ~Hero(void);

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Warrior : public Hero
{
	private:
	
	public:	
	Warrior(std::string,Item*,Item* );
	void printHero(void);
	~Warrior(void);
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Sorcerer : public Hero
{
	private:
	
	public:	
	Sorcerer(std::string ,Item*,Item* );
	void printHero(void);
	~Sorcerer(void);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class Paladin : public Hero
{
	private:
	
	public:	
	Paladin(std::string,Item*,Item*  );
	void printHero(void);
	~Paladin(void);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
