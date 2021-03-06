#include "header.h"

using namespace std;

Living::Living(const std::string tname, int tlvl, int tmaxhp) 	//name,lvl,hp needed for living, everything else in children 
:name(tname),level(tlvl),maxhp(tmaxhp),hp(maxhp){}
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string Living::get_name(void)
{
	return name;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Living::get_level(void)
{
	return level;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Living::get_maxhp(void)
{
	return maxhp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Living::get_hp(void)
{
	return hp;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Living::lvl_up(void)
{
	level++;
	maxhp+=20*level; 	//hp increased with lvl up
	hp=maxhp;		//health topped up when lvlup
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Living::add_hp(int i)
{
	if(hp+i>maxhp)
	{
		hp=maxhp;
	}
	else
	{
		hp+=i;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
Living::~Living(void){}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
