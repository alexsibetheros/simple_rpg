#include "header.h"


Position::Position(int tx=1,int ty=1){
	x=tx;
	y=ty;
}

///////////////////////////////////////////////////////////////////////////////

bool Position::operator ==(Position& p){

	if(x==p.x && y==p.y){return true; }
	else			    {return false;}
}

///////////////////////////////////////////////////////////////////////////////

Position& Position::operator=(const Position& p){
	if(this!=&p){
		x=p.x;
		y=p.y;
	}
return *this;
}

////////////////////////////////////////////////////////////////////////////////

 void Position::move(int tx,int ty){
		x=tx;
		y=ty;
	}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
