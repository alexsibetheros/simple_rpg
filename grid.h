#ifndef hgrid
#define hgrid

class Block;
class Party;

class Grid{
	private:
		Block*** gridtable;
		int size;
		
	public:
		Grid(void);
		~Grid(void);
		
        void PrintGrid(void);
		bool validMove(int,int);
		bool isNonAccessible(int x,int y){return gridtable[x][y]->isNonAccessible();}
		int gridSize(void){return size;}

		friend void Party::operate(void);
};

#endif
