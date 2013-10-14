#ifndef hblock
#define hblock

#include <string>

class Spell;
class Party;
class Monster;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Block{
 	public:
		virtual int engage(void)=0;
		virtual std::string content(void){return ""; }
		virtual bool isNonAccessible(void){return false;}
		virtual bool isMarket(void){return false;}
		virtual void HeroesIn(Party *){}
		virtual void HeroesOut(void){}
		virtual ~Block(){}
		
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Market : public Block{

		Party* heroes;
		std::list<Weapon*> weapon_list;
		std::list<Armor*> armor_list;
		std::list<Potion*> potion_list;
		std::list<Spell*> spell_list;
		
	public:
		Market(void);
		virtual ~Market(void);

		void HeroesIn(Party* p){heroes=p;}
        void HeroesOut(void){heroes=NULL;}
        void printOptions(void);
		void Buy();
		void Sell();
        bool isMarket(void){return true;}
		int engage(void);
  		std::string content(void){
			if(heroes!=NULL){return "MH";}
			else		    {return "M" ;}
			}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Common : public Block{

		Party* heroes;
		std::list<Monster*> monster_list;
		
	public:
        Common(void){heroes=NULL;}
        ~Common(void);

        void HeroesIn(Party* p){heroes=p;}
        void HeroesOut(void){heroes=NULL;}
        void printOptions(void);
        void decrease_counters(void);
        void replenish(void);
        void check_lvl(void);
        int engage(void);
        int monster_average(void);
        int battle(void);
        std::string content(void){if(heroes!=NULL){return "H";}return "  ";}
        Monster * chooseMonster(void);
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class NonAccessible : public Block{
		
	public:
        std::string content(void){return "NA";}
		bool isNonAccessible(void){return true;}
		int engage(void){return 0;}
		
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif
