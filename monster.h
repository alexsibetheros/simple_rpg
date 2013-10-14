#ifndef monster
#define monster

#include "living.h"
#include <string>

class Monster : public Living
{
	private:
	int damage;
	int defense;
	int agility;
	int burned;                                                                 //effect of fire spell
	int frozen;                                                                 //effect of ice spell
	int stunned;                                                                //effect of lightning spell
	int Bcounter;                                                               //round counter for the effect of fire spell
	int Fcounter;                                                               //round counter for the effect of ice spell
	int Scounter;                                                               //round counter for the effect of lightning spell
	public:
		Monster(const std::string , int ,int , int , int );
		virtual void printMonster(void)=0;
		int get_damage(void);
		int get_agility(void);
		int get_defense(void);
		void Fburned(int,int);
		void Ffrozen(int,int);
		void Fstunned(int,int);
		void decrease_counter(void);
		void Mreplenish(void);
		bool Burned(){if(burned!=0){return true;}return false;}
		bool Frozen(){if(frozen!=0){return true;}return false;}
		bool Stunned(){if(stunned!=0){return true;}return false;}
		bool take_damage(int hit);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Dragon : public Monster
{
	public:
	Dragon(std::string , int);
	void printMonster(void);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Exoskeleton : public Monster
{
	public:
	Exoskeleton(std::string , int);
	void printMonster(void);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Spirit : public Monster
{
	public:
	Spirit(std::string , int);
	void printMonster(void);
};

#endif
