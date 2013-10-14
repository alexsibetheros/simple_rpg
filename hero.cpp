#include "header.h"
#include <list>
using namespace std;



Hero::Hero(const std::string tname , int tstr,int tdxt, int taglt, int tmaxhp, int tmaxmp, Item* weapon, Item* armor ) : Living( tname,1,tmaxhp)
{		//gives name,lvl=1,hp to "living", and stores statistics and equiped items
	experience=0;
	maxmp=tmaxmp;
	mp=tmaxmp;
	weapon_size=10;
	armor_size=10;
	spell_size=10;
	potion_size=20;
	money=100;

	strength= ( rand()%6 +5)+tstr; 
	dexterity= ( rand()%6 +5)+tdxt;
	agility= ( rand()%6 +5)+taglt;

	Equiped[0]=weapon; //prequiped with a generic weapon and armor
	Equiped[1]=armor;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Hero::get_maxmp(void)
{
	return maxmp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Hero::get_mp(void)
{
	return mp;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Hero::get_strength(void)
{
	return strength;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Hero::get_dexterity(void)
{
	return dexterity;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Hero::get_agility(void)
{
	return agility;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Hero::get_experience(void)
{
	return experience;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::pay_for_item(int price)
{	
	money= money  - price;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Item* Hero::get_weapon(int find)                                                //returns item #find
{
	int i=1;
	list<Item*>::iterator it;	
  	for ( it=weapon_bag.begin() ; it != weapon_bag.end(); ++it )
  	{
		if(i==find)
			return (*it);
		i++;
	}
	return (*it);                                   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Item* Hero::get_armor(int find)                                                 //returns item #find
{
	int i=1;
	list<Item*>::iterator it;	
  	for ( it=armor_bag.begin() ; it != armor_bag.end(); ++it )
  	{
		if(i==find)
			return (*it);
		i++;
	}
	return (*it);                                   
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::equip(Item* tm1)
{
	int cont;
	bool flag=true,flag1=false;		//flag-> done with equip, flag1->equip actually happened
	if( (*tm1).get_dual()==1)	//if item requires 2 hands
	{
		cout<<"This Weapon requires 2 Hands, please unequip all weapons"<<endl;	
		while( flag)
		{
			unequip(); //calls function that asks the player to remove an item, in order for 2 handed, must go through loop again
			if( Equiped[0]==NULL && Equiped[1]==NULL) //if both hands free
			{
				Equiped[0]=tm1;

				if( (*tm1).type() == "W")	//depending on type of item, remove from appropriate bag
					weapon_bag.remove(tm1);
				else
					armor_bag.remove(tm1);
				
				flag=false;
				flag1=true;
			}
			else
			{	
				cout<<"This Weapon requires 2 Hands, either unequip all or equip another weapon.\nPress 0 to quit, 1 to continue : "<<endl;
				
                cin>>cont;
				while(cont!=1 || cont!=0){
					cout<<"\nInvalid option. Type again : ";
					cin>>cont;
				}
				
				if(cont==0)
					flag=false;
				else
					flag=true;				
			}
		}
	}
	else
	{
		flag=true;
		while( flag) 		//if weapon doesnt need 2 hands, check to see if available hands and equip
		{
			if( Equiped[0]==NULL && Equiped[1]==NULL) //both free, add to first hand
			{
				Equiped[0]=tm1;		
                		if( (*tm1).type() == "W")
					weapon_bag.remove(tm1);
				else
					armor_bag.remove(tm1);

				flag=false;
				flag1=true;
			}
			else if( Equiped[0]==NULL && Equiped[1]!=NULL) //first hand free, equip
			{
				Equiped[0]=tm1;		
				if( (*tm1).type() == "W")
					weapon_bag.remove(tm1);
				else
					armor_bag.remove(tm1);

				flag=false;
				flag1=true;
			}
			else if( Equiped[0]!=NULL && Equiped[1]==NULL)//second hand free, equip
			{
				Equiped[1]=tm1;		
                		if( (*tm1).type() == "W")
					weapon_bag.remove(tm1);
				else
					armor_bag.remove(tm1);

				flag=false;
				flag1=true;
			}
			else			//no hand free, enquip first and run loop again
			{
				cout<<"This Weapon requires 1 Hand, but both spaces currently full.\nPlease unequip one item. "<<endl;
				unequip();
				if( Equiped[0]!=NULL && Equiped[1]!=NULL)
				{
     			cout<<"This Weapon requires 1 Hands, either unequip all or equip another weapon.\nPress 0 to quit, 1 to continue : "<<endl;
                cin>>cont;
				while(cont!=1 || cont!=0){
					cout<<"\nInvalid option. Type again : ";
					cin>>cont;
				}
					if(cont==0)
						flag=false;
					else
						flag=true;
				}
			}
		
		
		}
	}	
	if(flag1){cout<<"Succefully equiped."<<endl;show_equiped();}
}
	
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::equip(void)			//asks hero to choose item to equip and calls equip for that item
{
	std::string type;
	int num;
	cout<<"\nWould you like to equip: W (weapon) or A (Armor) or Q (exit) : ";
    cin>>type;
	
	while(type!="w" && type!="W" && type!="A" && type!="a" && type!="Q" && type!="q"){
		cout<<"\nInvalid input. Type again : ";
		cin>>type;
	}
	
	if(type=="W" || type=="w")
	{   cout<<endl;
        show_weapons();
        cout<<endl;
		cout<<"Please Choose a Item to equip : ";

		cin>>num;
		while(num>(int)weapon_bag.size()){
			cout<<"Invalid option. Type again : ";
			cin>>num;
			cout<<endl;
		}
		equip( get_weapon(num) );	
	}
	else if(type=="A" || type=="a")
	{   cout<<endl;
        show_armors();
		cout<<"Please Choose a Item to equip"<<endl;
		cout<<endl;
		cin>>num;
		while(num>(int)armor_bag.size()){
			cout<<"Invalid option. Type again : ";
			cin>>num;
			cout<<endl;
		}
		equip( get_armor(num) );
	}
	else
		return;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::show_equiped(void)
{
	cout<<"Currently Equiped:"<<endl<<endl;
	if(Equiped[0]!=NULL)
		{
			cout<<"1:";
			(* Equiped[0]).printItem();
		}
		if(Equiped[1]!=NULL)
		{
			cout<<"2:";
			(* Equiped[1]).printItem();
		}
		cout<<endl;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::show_items(void)
{   
	cout<<" \n./././././././././././././././././.  Weapons  ././././././././././././././././.\n\n";
	show_weapons();
    cout<<" \n./././././././././././././././././.  Armors  ./././././././././././././././././\n\n";
	show_armors();
    cout<<" \n./././././././././././././././././.  Potions  ././././././././././././././././.\n\n";
	show_potions();
	cout<<" \n./././././././././././././././././.  Spells   ././././././././././././././././.\n\n";
	show_spell();

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::show_weapons(void)
{
	int i=1;
	list<Item*>::iterator it ;
	if(weapon_bag.empty()){
		cout<<"  empty."<<endl;
	}else{
  		for ( it=weapon_bag.begin(); it != weapon_bag.end(); ++it )
  		{
			cout<<"  "<<i<<": ";
			(*(*it)).printItem();
			i++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::show_armors(void)
{
	int i=1;
	list<Item*>::iterator it;
	if(armor_bag.empty()){
		cout<<"  empty."<<endl;
	}else{
	  	for ( it=armor_bag.begin() ; it != armor_bag.end(); ++it )
		{
			cout<<"  "<<i<<": ";
			(*(*it)).printItem();
			i++;
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::show_potions(void)
{
	int i=1;
	list<Item*>::iterator it;
	if(potion_bag.empty()){
		cout<<"  empty."<<endl;
	}else{
  		for ( it=potion_bag.begin() ; it != potion_bag.end(); ++it )
		{
			cout<<"  "<<i<<": ";
			(*(*it)).printItem();
			i++;
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::show_spell(void){
    int i=1;
	list<Spell*>::iterator it;
	if(spell_bag.empty()){
		cout<<"  empty."<<endl;
	}else{
  		for ( it=spell_bag.begin() ; it != spell_bag.end(); ++it )
		{
			cout<<"  "<<i<<": ";
			(*(*it)).printSpell();
			i++;
		}
	}

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::unequip(void)
{
	
	int remove;
	show_equiped();
	cout<<"Please Choose: 1 to unequip Weapon\n               2 to unequip Shield or second Weapon\n               3 to quit.\nInput: ";
	cin>>remove;
	if(remove==1)
	{
		if(Equiped[0]!=NULL)
		{
			if(add_to_bag( Equiped[0]) ==false)
			{
				cout<<"\nNo Space available, please clear space by selling items"<<endl;
				
			}
			else{
				cout<<"\nRemoved: "<< (Equiped[0])->getname()<<endl;
				Equiped[0]=NULL;
			}
		}
		else
			cout<<"\nNothing to unequip in this spot"<<endl;
	}
	else if(remove==2)
	{
		if(Equiped[1]!=NULL)
		{
			if(add_to_bag( Equiped[1]) ==false)
			{
				cout<<"\nNo Space available, please clear space by selling or tossing items"<<endl;
				
			}
			else{
				cout<<"\nRemoved: "<< (Equiped[1])->getname()<<endl;
				Equiped[1]=NULL;
			}
		}
		else
			cout<<"\nNothing to unequip in this spot"<<endl;
	}
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Hero::add_to_bag(Item* t1)
{
	
      	if( (*t1).type() == "W" )
	{
	
		if( add_to_bag_weapon(t1) )
	        	return true;
	        else
	        	return false;   	
       	}
        else if( (*t1).type() == "A" )
	{
		if( add_to_bag_armor(t1) )
	        	return true;
	        else
	        	return false;   	
       	}         	
       	else
       	{
	     	if( add_to_bag_potion(t1) )
	     		return true;
	   	else
	  		return false;   	
        }    
      
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Hero::add_to_bag_weapon(Item* t1)
{
	if( weapon_size > (int)weapon_bag.size() )
	{
		weapon_bag.push_back( t1 );
		return true;
	}
	else
	{	
		cout<<"No Space to add Weapon"<<endl;
		return false;
	}
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Hero::add_to_bag_armor(Item* t1)
{
	if( armor_size > (int)armor_bag.size() )
	{
		armor_bag.push_back( t1 );
		return true;
	}
	else
	{	
		cout<<"No Space to add Armor"<<endl;
		return false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Hero::add_to_bag_potion(Item* t1)
{
	if( potion_size > (int)potion_bag.size() )
	{
		potion_bag.push_back( t1 );
		return true;
	}
	else
	{	
		cout<<"No Space to add Potion"<<endl;
		return false;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Hero::~Hero(void)
{
   	list<Item*>::iterator it;
      	for ( it=weapon_bag.begin() ; it != weapon_bag.end(); ++it )
      	{
           	delete  (*it) ;
       	}

      	for ( it=armor_bag.begin() ; it != armor_bag.end(); ++it )
      	{
           	delete  (*it) ;
       	}

      	for ( it=potion_bag.begin() ; it != potion_bag.end(); ++it )
      	{
           	delete  (*it) ;
       	}
  	list<Spell*>::iterator it1;
      	for ( it1=spell_bag.begin() ; it1 != spell_bag.end(); ++it1 )
      	{
           	delete  (*it) ;
       	}

	weapon_bag.clear();
	armor_bag.clear();
	potion_bag.clear();
	spell_bag.clear();

	delete Equiped[0];
    	delete Equiped[1];
    	delete[] Equiped;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::addXP(int sum){
	experience+=(10*sum);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::check_lvl()		//lvls: lvl1:15exp, lvl2:50exp, alla levels after are 50*lvl(-1)
{
	if( (experience>=15 && get_level()==1 )|| ( experience >= ( ( get_level() -1 )*50 )&&get_level()!=1 ) )
	{
		cout<<"LVL Up"<<endl;
		lvl_up();
		maxmp=(int)( (1.2*maxmp)+(5*get_level())) ;	
		mp=maxmp;
		strength=(int)( (1.2*strength)+(5*get_level())) ;
		dexterity=(int)( (1.2*dexterity)+(5*get_level())) ;
		agility=(int)( (1.2*agility)+get_level()) ;
		if(agility>80)				//if agility exceeds this ammount, hero will almost be invincible since no attack can strike
		    agility=80;
		return;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Hero::get_weapon_damage(void)
{
	int sum=0;
	if( Equiped[0]!=NULL)
		sum=Equiped[0]->getIdamage();
	if (Equiped[1]!=NULL)
		sum+=Equiped[1]->getIdamage();
	return sum;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Hero::get_weapon_defense(void)
{
	int sum=0;
	if( Equiped[0]!=NULL)
		sum=Equiped[0]->getIprotection();
	if (Equiped[1]!=NULL)
		sum+=Equiped[1]->getIprotection();
	return sum;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Hero::get_damage(void)
{
	int sum=0;
	sum=strength+get_weapon_damage();
	
	return sum;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::take_damage(int hit)
{
	int a=get_weapon_defense();
	int sum;

	if( randomn(1,100) <= agility ){                                            //check if dodged attack
		sum=0;
		cout<<get_name()<<":"<<"dodged attack.\n"<<endl;
	}else{
        
        if(hit>a){                                                              //calculate total damage
			sum= hit - a ;
			cout<<get_name()<<":"<<" hit for "<<hit - a<<" damage.\n"<<endl;
		}
		else{                                                                   //if no damage made
			sum=0;
			cout<<get_name()<<":"<<"defense is greater than attack, no damage."<<endl;
		}
	}

	add_hp(-sum);
	if(get_hp()<0)
		add_hp(-get_hp() );
		

	
	if(get_hp()==0)                                                             //check hp ==0
	    cout<<get_name()<<":"<<" Fainted"<<endl;
	
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Spell * Hero::chooseSpell(void)
{
	int i,n=1,nchoice;
	string choice;
	list<Spell*>::iterator it;

	cout<<"Choose which Spell to use.\n"<<endl;
	for (i=1, it=spell_bag.begin() ; it != spell_bag.end(); ++it,i++ )
	{
		cout<<i<<":";
		(*(*it)).printSpell();
	}
	cout<<"Choose : ";

	cin>>choice;
	nchoice=atoi(choice.c_str());		//used string instead of int because user might wrongly give a character instead
	
	while(nchoice>(int)spell_bag.size() || nchoice<1)		//makes sure spell user wants is inside bag
	{
                    cout<<"\nWrong Input. Type again : ";
                    cin>>choice;
                    nchoice=atoi(choice.c_str());
	}
	
  	for ( it=spell_bag.begin() ;nchoice>n; ++it,n++ ){}	//runs through bag to find spell

	return *it;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::Hreplenish(void)
{       
	if(get_hp()==0){ return;}
	add_hp( (int)  (get_maxhp()*10)/100   );
  	mp+=( (maxmp*10)/100 );
  	if(mp>maxmp){ mp=maxmp;}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::set_money(int sum)
{
	if(money>sum)
		money+=sum;
	else
		money=0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::cut_money(void){money=(int)( money*0.7);}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Hero::sell_weapon(int choice){
	int i=1;
    	list<Item*>::iterator it;
   	it=weapon_bag.begin();
   	
   	while( choice>i && it!=weapon_bag.end() ){i++;it++;}
   	
   	if(it==weapon_bag.end()){return false;}
   	
	add_to_money( ((*it)->getprice())/2 );
	
	cout<<(*it)->getname()<<" sold for "<<((*it)->getprice())/2<<"$.\n"<<endl;
	weapon_bag.erase(it);
   	
   	return true;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Hero::sell_armor(int choice ){
    	int i=1;
    	list<Item*>::iterator it;
   	it=armor_bag.begin();
   	
   	while( choice>i && it!=armor_bag.end() ){i++;it++;}
   	
   	if(it==armor_bag.end()){return false;}
	
	add_to_money( ((*it)->getprice())/2 );
	
	cout<<(*it)->getname()<<" sold for "<<((*it)->getprice())/2<<"$.\n"<<endl;
	armor_bag.erase(it);
   	
   	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Hero::sell_potion(int choice){
	int i=1;
    	list<Item*>::iterator it;
   	it=potion_bag.begin();
   	
   	while( choice>i && it!=potion_bag.end() ){i++;it++;}
   	
   	if(it==potion_bag.end()){return false;}
	
	add_to_money( ((*it)->getprice())/2 );
	
	cout<<(*it)->getname()<<" sold for "<<((*it)->getprice())/2<<"$.\n"<<endl;
	potion_bag.erase(it);
   	
   	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 bool Hero::sell_spell(int choice){
    	int i=1;
    	list<Spell*>::iterator it;
   	it=spell_bag.begin();
   	
   	while( choice>i && it!=spell_bag.end() ){i++;it++;}
   	
   	if(it==spell_bag.end()){return false;}
	
	add_to_money( ((*it)->getprice())/2 );
	
	cout<<(*it)->getname()<<" sold for "<<((*it)->getprice())/2<<"$.\n"<<endl;
	
	spell_bag.erase(it);
	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Hero::use_Potion(void){
	int i,n=1;
	show_potions();
	if(potion_bag.empty()){
		cout<<"\nYou have no potions. Potions can be purchased at the market.\n"<<endl;
	}else{
        	cout<<"Choose which potion to use : ";
    		cin>>i;
		while((int)potion_bag.size()<i || i<1){
       			cout<<"Invalid option. Type again : ";
    			cin>>i;
		}
		cout<<"\nbefore potion :\n";
		printHero();
		
		list<Item*>::iterator it;
  		for ( it=potion_bag.begin() ;i>n; ++it,n++ ){}

  		strength+=(*it)->getPstrength();
  		agility+=(*it)->getPagility();
  		dexterity+=(*it)->getPdexterity();
  		mp+=(*it)->getPmp();
  		add_hp((*it)->getPhp());
  	  	cout<<"\nafter potion :\n";
		printHero();
		cout<<endl<<endl;
		potion_bag.remove(*it);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Hero::add_to_bag_spell(Spell* t1){
    	if( spell_size > (int)spell_bag.size() )
	{
		spell_bag.push_back( t1 );
		return true;
	}
	else
	{
		cout<<"No Space to add "<<endl;
		return false;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Warrior::Warrior(std::string tname, Item* sword,Item* shield) : Hero(tname, 10,0,10,120,50,sword,shield) {}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Warrior::printHero(void)
{
	cout<<get_name()<<" -- Warrior"<<endl;
	cout<<left;
		
		cout<<"lvl:";
		cout<<setw(4)<<get_level();
		cout<<"str:";
		cout<<setw(5)<<get_strength();
		cout<<"dxt:";
		cout<<setw(5)<<get_dexterity();
		cout<<"agt:";
		cout<<setw(5)<<get_agility();
		cout<<"hp:";
		cout<<setw(3)<<get_hp();
		cout<<"/";
		cout<<setw(4)<<get_maxhp();
		cout<<"mp:";
		cout<<setw(3)<<get_mp();
		cout<<"/";
		cout<<setw(4)<<get_maxmp();
		cout<<"money:";
		cout<<setw(5)<<get_money();
		cout<<"exp:";
		cout<<setw(5)<<get_exp()

		<<endl<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Warrior::~Warrior(void){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sorcerer::Sorcerer(std::string tname,Item* sword,Item* shield) : Hero(tname, 0,10,10,80,150,sword,shield){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Sorcerer::printHero(void)
{
    cout<<get_name()<<" -- Sorcerer"<<endl;
	cout<<left;
		
		cout<<"lvl:";
		cout<<setw(4)<<get_level();
		cout<<"str:";
		cout<<setw(5)<<get_strength();
		cout<<"dxt:";
		cout<<setw(5)<<get_dexterity();
		cout<<"agt:";
		cout<<setw(5)<<get_agility();
		cout<<"hp:";
		cout<<setw(3)<<get_hp();
		cout<<"/";
		cout<<setw(4)<<get_maxhp();
		cout<<"mp:";
		cout<<setw(3)<<get_mp();
		cout<<"/";
		cout<<setw(4)<<get_maxmp();
		cout<<"money:";
		cout<<setw(5)<<get_money();
		cout<<"exp:";
		cout<<setw(5)<<get_exp()
		<<endl<<endl;

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Sorcerer::~Sorcerer(void){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Paladin::Paladin(std::string tname,Item* sword,Item* shield) : Hero(tname, 10,10,0,100,100,sword,shield) //Paladin has 100 health, 100 mana, boost str & dexterity
{}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Paladin::printHero(void)
{
	cout<<get_name()<<" -- Paladin"<<endl;
	cout<<left;

		cout<<"lvl:";
		cout<<setw(4)<<get_level();
		cout<<"str:";
		cout<<setw(5)<<get_strength();
		cout<<"dxt:";
		cout<<setw(5)<<get_dexterity();
		cout<<"agt:";
		cout<<setw(5)<<get_agility();
		cout<<"hp:";
		cout<<setw(3)<<get_hp();
		cout<<"/";
		cout<<setw(4)<<get_maxhp();
		cout<<"mp:";
		cout<<setw(3)<<get_mp();
		cout<<"/";
		cout<<setw(4)<<get_maxmp();
		cout<<"money:";
		cout<<setw(5)<<get_money();
		cout<<"exp:";
		cout<<setw(5)<<get_exp()
		<<endl<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Paladin::~Paladin(void){}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
