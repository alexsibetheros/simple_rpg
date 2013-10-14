#include "header.h"

using namespace std;

Monster::Monster(const std::string tname , int tdmg,int tdfns, int taglt, int tlvl ) : Living(tname,tlvl, 20+ (tlvl)*10 )
{	//monster created by giving living the name,lvl and hp(hp depending on monster lvl)
damage= tlvl* ( ( rand()%3 +5) + tdmg);			//damage and others depending on lvl of monster and extra bonuses depending on type
defense= tlvl* ( ( rand()%3 +5) + tdfns);
agility= tlvl* ( ( rand()%3 +5) + taglt);
if(agility>=80)		//makes sure monster isnt invincible
	agility=80;
	
burned=0;
frozen=0;
stunned=0;
Bcounter=0;
Fcounter=0;
Scounter=0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Monster::get_damage(void)
{   
	if(frozen<=damage)
		return damage-frozen;
	else
		return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Monster::get_defense(void)
{
	if(burned<=defense)
		return defense-burned;
	else
		return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Monster::get_agility(void)
{
		if(stunned<=agility)
		return agility-stunned;
	else
		return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Monster::take_damage(int hit)
{
	int sum;
if( randomn(1,100) <= get_agility() ){                                          //check if attacked is dodged
		sum=0;
		cout<<get_name()<<":"<<"dodged attack."<<endl;
		}else{
	if( hit>get_defense())                                                      //calculates damage
	{	sum =hit-get_defense();
		cout<<get_name()<<":"<<" hit for "<<sum<<" damage.\n"<<endl;
	}else{                                                                      //if no damage taken
		sum=0;
		cout<<get_name()<<":"<<" defense is greater than attack, no damage."<<endl;
	}
	
	}
	add_hp(-sum);                                                               //no hp negative
	if(get_hp()<0)
		add_hp(-get_hp() );
		
	
	if(get_hp()==0)                                                             //checks if dead
	{
		    cout<<get_name()<<":"<<" Dead"<<endl;
			return false;
	}
	else
	        return true;
	    
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Monster::Fburned(int c,int a)
{
	Bcounter=c;
	burned=a;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Monster::Ffrozen(int c,int a)
{
	Fcounter=c;
	frozen=a;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Monster::Fstunned(int c,int a)
{
	Scounter=c;
	stunned=a;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Monster::decrease_counter(void)                                            //every round counter for the duration of spells
{                                                                               //are decreased

	if(Fcounter>=2){Fcounter-=1;}
	else if(Fcounter==1){Fcounter=0;frozen=0;}				//if counter reachs zero, end spells effect

	if(Bcounter>=2){Bcounter-=1;}
    else if(Bcounter==1){Bcounter=0;burned=0;}

	if(Scounter>=2){Scounter-=1;}
	else if(Scounter==1){Scounter=0;stunned=0;}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Monster::Mreplenish(void)			//after each round, if monster still alive, give back 10 of max health
{       if(get_hp()==0){return;}
		add_hp( (int)(get_maxhp()*10)/100 );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Dragon::Dragon(std::string tname, int tlvl) : Monster(tname,5,0,0,tlvl) {} //stronger monster
									//Dragon is a "living" " monster" with increased strength
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Dragon::printMonster(void)
{
	cout<<"(Dragon) : ";
	cout<<left
		<<setw(20)<<get_name();
		cout<<"lvl:";
		cout<<setw(4)<<get_level();
		cout<<"dmg:";
		cout<<setw(5)<<get_damage();
		cout<<"dfs:";
		cout<<setw(5)<<get_defense();
		cout<<"agt:";
		cout<<setw(5)<<get_agility();
		cout<<"hp:";
		cout<<setw(4)<<get_hp();
		cout<<"/";
		cout<<setw(4)<<get_maxhp()
		<<endl;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Exoskeleton::Exoskeleton(std::string tname, int tlvl) : Monster(tname,0,5,0,tlvl){} //monster with greater defense

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Exoskeleton::printMonster(void)
{
	cout<<"(Exo)    : ";
	cout<<left
		<<setw(20)<<get_name();
		cout<<"lvl:";
		cout<<setw(4)<<get_level();
		cout<<"dmg:";
		cout<<setw(5)<<get_damage();
		cout<<"dfs:";
		cout<<setw(5)<<get_defense();
		cout<<"agt:";
		cout<<setw(5)<<get_agility();
		cout<<"hp:";
		cout<<setw(4)<<get_hp();
		cout<<"/";
		cout<<setw(4)<<get_maxhp()
		<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Spirit::Spirit(std::string tname, int tlvl) : Monster(tname,0,0,5,tlvl){} //quicker monster

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Spirit::printMonster(void)
{
    cout<<"(Spirit) : ";
	cout<<left
		<<setw(20)<<get_name();
		cout<<"lvl:";
		cout<<setw(4)<<get_level();
		cout<<"dmg:";
		cout<<setw(5)<<get_damage();
		cout<<"dfs:";
		cout<<setw(5)<<get_defense();
		cout<<"agt:";
		cout<<setw(5)<<get_agility();
		cout<<"hp:";
		cout<<setw(4)<<get_hp();
		cout<<"/";
		cout<<setw(4)<<get_maxhp()
		<<endl;
		
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
