#include <string>


class Position{
		int x;
		int y;
	public:
		Position(int,int);
		Position(void){}
		Position& operator=(const Position& );
		
		int getX(){return x;}
		int getY(){return y;}

		bool operator ==(Position&);
		void move(int,int);
};
