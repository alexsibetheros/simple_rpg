#ifndef hparty
#define hparty

#include <list>
#include <string>

class Grid;
class Hero;

class Party{
	std::list<Hero*> party_list;
	Position hposition;
	Grid* grid;

	public:
		Party(Grid* g);
		~Party(void);
		
		void operate(void);
		void checkInventory(void);
		void partyEquip(void);
		void printParty(void);
        void usePotion(void);
        void showEquipment(void);
        void addXP(int);
        void check_lvl(void);
        void dead(void);
        void Replenish(void);
        void set_all_money(int sum);
        void cut_money(void);
        void Revive(void);

		bool move(void);
		bool alive(void);

		int size(void);
        int get_average(void);

		Hero* chooseHero(std::string);
		Hero* nextHero(int);
};
	
#endif
