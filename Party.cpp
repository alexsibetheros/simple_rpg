#include "header.h"

using namespace std;


Party::Party(Grid* g){
 	int i=0,j=0,n;
	string type,tname,nu;
	Weapon* t1;
	Armor* t2;
	
    grid=g;
    
	while((grid->isNonAccessible(i,j))){
		if(j>=g->gridSize()){
			j=0;
			i++;
		}
		j++;
	}

	hposition.move(i,j);
	cout<<"Starting position "<<i<<", "<<j<<".\n"<<endl;
	
	cout<<"Give the ammount of Heroes to join our party(from 1 up to 3) : ";
	cin>>nu;
	
	while(nu!="1" &&nu!="2" && nu!="3"){
		cout<<"\n Wrong input.Give the ammount of Heroes to join our party(from 1 up to 3) :";
        cin>>nu;
	}

	n=atoi(nu.c_str());

	for(i=0;i<n;i++)                                                            //creating each hero of the party
	{
		cout<<"\nWhat type of hero, hero#"<<i+1<<" will be?\nType W( for Warrior) S( for Sorcerer) P( for Paladin) : ";
		cin>>type;
		while(type!="w" && type!="W" && type!="s" && type!="S" && type!="p" && type!="P" ){
			cout<<"\n Wrong input.Type W( for Warrior) S( for Sorcerer) P( for Paladin) : ";
			cin>>type;
		}
		cout<<"Give the name of the hero : ";
		cin>>tname;
		
		if("W"==type || "w"==type)
		{
			 t1=new Weapon("Wooden_Stick",0,1,1,0) ;
			 t2 =new Armor("Wooden_Shield",0,1,1) ;
			 party_list.push_back( new Warrior(tname,t1,t2) );
			
		}
		else if("S"==type || "s"==type)
		{
			 t1=new Weapon("Wooden_Staff",0,1,1,0) ;
			 t2 =new Armor("Wooden_Sphere",0,1,1) ;
			party_list.push_back( new Sorcerer(tname,t1,t2) );
			
		}
		else if("P"==type || "p"==type)
		{
			 t1=new Weapon("Wooden_Bow",0,1,1,0) ;
			 t2 =new Armor("Wooden_Cloke",0,1,1) ;
			party_list.push_back( new Paladin(tname,t1,t2) );
			
		}
	}
	
	cout<<"\n\n The party is created, with members :\n\n";

	list<Hero*>::iterator it;                                                   //giving each hero some equipment
  	for ( it=party_list.begin() ; it != party_list.end(); ++it ){
         t1=new Weapon("Screw_driver",0,1,1,0) ;
		 t2=new Armor("Paper_box",0,1,1) ;
		 Potion *p=new Potion("Powerade",0,0,0,0,0,1);
		 Spell  *s=new FireSpell("Zippo",0,1,1,1,1,0) ;
		 (*(*it)).add_to_bag(t1);
		 (*(*it)).add_to_bag(t2);
		 (*(*it)).add_to_bag(p);
		 (*(*it)).add_to_bag_spell(s);
		 (*(*it)).printHero();
 	}
 	cout<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Party::move(void){
	int addx=0,addy=0;
	int x=hposition.getX(),y=hposition.getY();
	string movement;
	
	cout<<"\nType the move you want to make (right,left,up,down,0 to Display Map) : ";
	cin>>movement;

	while(!cin.good()){
		cout<<"Input error, please type again : " ;
		cin>>movement;
	}
        

	if 	   (movement.compare("right")==0 || movement.compare("Right")==0){addy=1; }
	else if(movement.compare("down" )==0 || movement.compare("Down" )==0){addx=1; }
	else if(movement.compare("up"   )==0 || movement.compare("Up"   )==0){addx=-1;}
	else if(movement.compare("left" )==0 || movement.compare("Left" )==0){addy=-1;}
	else if(movement.compare("0"    )==0         ){grid->PrintGrid();return false;}
	else {cout<<"\nYou misstyped the command please try again carefully.\n"<<endl;return false;}

	if(x+addx<0 ||x+addx>4 ||y+addy<0 ||y+addy>4){
        cout<<"\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
		cout<<"\nOut of grid play is forbidden, please give a valid move.\n"<<endl;
		cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
		return false;
	}

	if(grid->validMove(hposition.getX()+addx,hposition.getY()+addy)){
          
		hposition.move(hposition.getX()+addx,hposition.getY()+addy);

		return true;
	}

	cout<<"\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!";
	cout<<"\nNonAccesible block, please try another move.\n"<<endl;
	cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Party::operate(void){                                                      //operates the party and basically the whole game
		int tmp,tx,ty;

		tx=hposition.getX();
		ty=hposition.getY();
		grid->gridtable[tx][ty]->HeroesIn(this);
		grid->PrintGrid();

		while(true){
			tx=hposition.getX();
			ty=hposition.getY();

			grid->gridtable[tx][ty]->HeroesIn(this);

			tmp=grid->gridtable[tx][ty]->engage();                              //each block has an engage function whick is called
			                                                                    //when the party moves there
			if(tmp==1){                                                         //option for move
				while(!move()){}
			}else if(tmp==2){                                                   //quit
				break;
			}else if(tmp==0){
				grid->PrintGrid();continue;
			}
			grid->gridtable[tx][ty]->HeroesOut();
		}


}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Hero* Party::chooseHero(string function){                                       //prints heroes and retutn the one the user choose
    int i;
	list<Hero*>::iterator it;
	cout<<endl;

  	for ( i=1,it=party_list.begin() ; it != party_list.end(); ++it,i++){
		cout<<i<<": "<<(*(*it)).get_name()<<endl;
	}

	do{
        cout<<"\nChoose which hero to "<<function<<" : ";
    	cin>>i;
	}while( cin.fail() || (int)party_list.size()<i || i<1);

	int n=1;

  	for ( it=party_list.begin() ;i>n; ++it,n++ ){}

	return *it;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Party::checkInventory(void){
	chooseHero("check inventory")->show_items();
	cout<<endl<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Party::partyEquip(void){
	chooseHero("equip")->equip();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Party::printParty(){

    cout<<"\n\nParty:\n\n";
	list<Hero*>::iterator it;
  	for ( it=party_list.begin() ; it != party_list.end(); ++it ){(*(*it)).printHero();}
		cout<<endl<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Party::usePotion(void){

    chooseHero("use potion")->use_Potion();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Party::showEquipment(void){

	chooseHero("show equipment")->show_equiped();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Party::size(void){
	return party_list.size();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Party::check_lvl()                                                         //checks level for each hero
{
    list<Hero*>::iterator it;
	for(it=party_list.begin();it!=party_list.end();it++){
	(*it)->check_lvl();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Party::alive(){                                                            //checks if any hero is alive
	list<Hero*>::iterator it;
	for(it=party_list.begin();it!=party_list.end();it++){
	if( (*it)->get_hp()>0){return true;}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Party::addXP(int sum){                                                     //adds xp for each hero
    list<Hero*>::iterator it;
	for(it=party_list.begin();it!=party_list.end();it++){
		(*it)->addXP(sum);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Party::get_average(void)                                                    //return the average level of the heroes
{
	int i=0;
	list<Hero*>::iterator it;
	for(it=party_list.begin();it!=party_list.end();it++){
		i+=(*it)->get_level(); }
		return (int)(i/ (party_list.size() ));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 Hero* Party::nextHero(int i){                                                  //return the i hero
		
      	list<Hero*>::iterator it;
		int n=1;
		for ( it=party_list.begin() ;i>n; ++it,n++ ){}
		i++;
		return *it;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Party::Replenish(void)
{       list<Hero*>::iterator it;
		for (it=party_list.begin() ; it != party_list.end(); ++it)
			(*(*it)).Hreplenish();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Party::set_all_money(int sum)
{   list<Hero*>::iterator it;
	for (it=party_list.begin() ; it != party_list.end(); ++it)
			(*(*it)).set_money(sum);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Party::cut_money(void){
    list<Hero*>::iterator it;
	for (it=party_list.begin() ; it != party_list.end(); ++it)
			(*(*it)).cut_money();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Party::dead(void)                                                          //if the party loses a battle this function
{       list<Hero*>::iterator it;                                               //does the neede actions to revive and lower 
		for (it=party_list.begin() ; it != party_list.end(); ++it)              //their stats
		{
			(*(*it)).add_hp( (int)((*it)->get_maxhp()/2) );
			(*(*it)).set_mana( -(*it)->get_mp() );
			(*(*it)).set_mana( (*it)->get_maxmp()/2 );
			(*(*it)).add_hp( (int)((*it)->get_maxhp()/2) );
			(*(*it)).set_money( -(int)((*(*it)).get_money()/2 ) );
			cout<< (*it)->get_name()<<" : Return from the grave with half hp,mp and money."<<endl;
		}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Party::Revive(void)                                                        //revive any dead hero
{       list<Hero*>::iterator it;
    	for (it=party_list.begin() ; it != party_list.end(); ++it)
		{
			if((*(*it)).get_hp() ==0)
			{
				cout<<"Hero: "<< (*it)->get_name() <<" is Revived. "<<endl;
				(*(*it)).add_hp( (int)((*it)->get_maxhp()/2) );}
		}
		
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Party::~Party(void){

	list<Hero*>::iterator it;
	for(it=party_list.begin();it!=party_list.end();it++){
		delete *it;
	}
	party_list.clear();
}
