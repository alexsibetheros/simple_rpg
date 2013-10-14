#include "header.h"
#include <list>

using namespace std;


Market::Market(void){

	int tprice,tlvl,tdmg,i=0,n=5,tprt,tst,tdxt,tmp,thp,tag,tmana,tcount,tab;
	bool tdual;
    std::string tname;
	
	heroes=NULL;
	ifstream on("weapon_list.txt");

 	while (i<=20){                                                              //filling weapon list from weapon_list.txt
           	on >> tname>>tprice>>tlvl>>tdmg>>tdual;
        	if ( on.eof() ) break;
			weapon_list.push_back( new Weapon(tname,tprice,tlvl,tdmg,tdual) );
			i++;
	}
    on.close();

	ifstream on1("armor_list.txt");                                             //filling armor list from armor_list.txt
	i=0;n=5;

	while (i<=20){
           	on1 >> tname>>tprice>>tlvl>>tprt;
        	if ( on1.eof() ) break;
			armor_list.push_back( new Armor(tname,tprice,tlvl,tprt) );
			i++;
	}
    on1.close();

	ifstream on2("potion_list.txt");                                            //filling potion list from potion_list.txt
	i=0;n=5;

	while (i<=20){
           	on2 >> tname>>tprice>>tst>>tdxt>>tag>>tmp>>thp;
        	if ( on2.eof() ) break;
			potion_list.push_back( new Potion(tname,tprice,tst,tdxt,tag,tmp,thp) );
			i++;
	}
    on2.close();

	ifstream on3("firespell_list.txt");                                         //filling spell list from *spell_list.txt
    ifstream on4("icespell_list.txt");
    ifstream on5("lightningspells_list.txt");
	i=0;n=5;

	while (i<=9){
          	on3 >> tname>>tprice>>tlvl>>tmana>>tdmg>>tcount>>tab;
        	if ( on3.eof() ) break;
			spell_list.push_back( new FireSpell(tname,tprice,tlvl,tmana,tdmg,tcount,tab) );
			i++;
	}
    on3.close();

	i=0;
    while (i<=9){
        	on4 >> tname>>tprice>>tlvl>>tmana>>tdmg>>tcount>>tab;
        	if ( on4.eof() ) break;
			spell_list.push_back( new IceSpell(tname,tprice,tlvl,tmana,tdmg,tcount,tab) );
			i++;
	}
    on4.close();

	i=0;
    while (i<=9){
        	on5 >> tname>>tprice>>tlvl>>tmana>>tdmg>>tcount>>tab;
        	if ( on5.eof() ) break;
			spell_list.push_back( new LightningSpell(tname,tprice,tlvl,tmana,tdmg,tcount,tab) );
			i++;
	}
    on5.close();

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Market::printOptions(void){
    cout<<"\t\t\t--------------------------";
    cout<<"\n\nYou are in a Market, the following options are available :\n"<<endl;
    cout<<"1: Buy    3: CheckInventory     5: Use potion    7: Move    9:Show equipment "<<endl;
    cout<<"2: Sell   4: Show party stats   6: Display Map   8: Equip   10: Quit \n"<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Market::engage(void){
	
    string schoice;
	int choice;
	printOptions();
    while(true){

		cout<<"Market : Choose by typing the corresponding number (0 for options):";
        cin>>schoice;
		choice=atoi(schoice.c_str());

		if(choice!= 0 && choice!=1 && choice!=2 && choice!=3 && choice!=4 && choice!=5 && choice!=6 && choice!=7 && choice!=8 && choice!=9 && choice!=10){cout<<"\nInvalid Input.\n\n";continue;}
 		switch (choice){
			case 0: printOptions();break;
			case 1: Buy(); break;
			case 2: Sell();break;
			case 3:	heroes->checkInventory();break;
			case 4:heroes->printParty();break;
			case 5: heroes->usePotion();break;
			case 6: return 0;
			case 7: return 1;
			case 8: heroes->partyEquip(); 	break;
           	case 9:heroes->showEquipment();break;
			case 10: return 2;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Market::Buy(void){
	Hero* h;
	int itemchoice,c=0,choice,i,tlvl,tmn;
	
	h=heroes->chooseHero("use for buying");                                     //choose Hero
	tlvl=h->get_level();
	tmn=h->get_money();

	cout<<"Type 1 to see available weapons\n     2 to see available armors\n     3 to see available potions\n     4 to see available spells.\n(More items will appear while you gain level and money)\nInput : ";
	cin>>choice;
	while(choice<1||choice>4){
		cout<<"Invalid Input.Type again : ";
		cin>>choice;
	}

	list<Weapon*>::iterator it;
	list<Armor*>::iterator ita;
	list<Potion*>::iterator itb;
	list<Spell*>::iterator itc;

	switch(choice){
		case 1:                                                                 //buy weapons
  			for ( i=0,it=weapon_list.begin() ; it!= weapon_list.end(); ++it ){  //print only the items which the hero is able to buy
				if( (*(*it)).able(tlvl,tmn) ){
                	cout<<++i<<" : ";
					(*(*it)).printItem();
				}
			}

			if(i==0){cout<<"No weapons can be bought with your money and level\nincrease them and return."<<endl;break;}

			cout<<"Type the number of the weapon you want to buy or 0 to exit : "<<endl;
			cin>>itemchoice;

			while(itemchoice<0 || itemchoice>i){
				cout<<"Wrong Input.Type again : ";
				cin>>itemchoice;
			}

  			for ( it=weapon_list.begin() ; it!= weapon_list.end(); ++it ){      //search list for the item choosen by input from those 
				if((*(*it)).able(tlvl,tmn) ){                               	//that the player can buy
                	c++;
				if(c==itemchoice)
				    break;
				}
			}

			if(h->add_to_bag( (*it) )){

				h->pay_for_item( (*it)->getprice() );
			}

			break;

		case 2:                                                                 //buy armor
  			for ( i=0,ita=armor_list.begin() ; ita != armor_list.end(); ++ita ){
				if( (*(*ita)).able(tlvl,tmn) ){
                cout<<++i<<" : ";
				(*(*ita)).printItem();
				}
			}
			
			if(i==0){cout<<"No armors can be bought with your money and level\nincrease them and return."<<endl;break;}

			cout<<"Type the number of the armor you want to buy or 0 to exit : "<<endl;
			cin>>itemchoice;
			while(itemchoice<0 || itemchoice>i){
				cout<<"Wrong Input.Type again : ";
				cin>>itemchoice;
			}
			
				for ( ita=armor_list.begin() ; ita!= armor_list.end(); ++ita ){
				if((*(*ita)).able(tlvl,tmn) ){
                	c++;
				if(c==itemchoice)
				    break;
				}
			}

			if(h->add_to_bag( (*ita) )){
				h->pay_for_item( (*ita)->getprice() );
            }
            
			break;
			
		case 3:                                                                 //buy potions
  			for ( i=0,itb=potion_list.begin() ; itb != potion_list.end(); ++itb ){

				if( (*(*itb)).able(tlvl,tmn) ){
                cout<<++i<<" : ";
				(*(*itb)).printItem();

				}
			}
			
			if(i==0){cout<<"No armors can be bought with your money and level\nincrease them and return."<<endl;break;}

			cout<<"Type the number of the armor you want to buy or 0 to exit : "<<endl;
			cin>>itemchoice;
			while(itemchoice<0 || itemchoice>i){
				cout<<"Wrong Input.Type again : ";
				cin>>itemchoice;
			}
			
				for ( itb=potion_list.begin() ; itb!= potion_list.end(); ++itb ){
				if((*(*itb)).able(tlvl,tmn) ){
                	c++;
				if(c==itemchoice)
				    break;
				}
			}

			if(h->add_to_bag( (*itb) )){

				h->pay_for_item( (*itb)->getprice() );
			}
			
			break;
			
        case 4:                                                                 //buy spells
			for ( i=0,itc=spell_list.begin() ; itc != spell_list.end(); ++itc ){
				if( (*(*itc)).able(tlvl,tmn) ){
                cout<<++i<<" : ";
				(*(*itc)).printSpell();

				}
			}
			
			if(i==0){cout<<"No spells can be bought with your money and level\nincrease them and return."<<endl;break;}

			cout<<"Type the number of the spell you want to buy or 0 to exit : "<<endl;
			cin>>itemchoice;
			while(itemchoice<0 || itemchoice>i){
				cout<<"Wrong Input.Type again : ";
				cin>>itemchoice;
			}

			for ( itc=spell_list.begin() ; itc!= spell_list.end(); ++itc ){
				if((*(*itc)).able(tlvl,tmn) ){
                	c++;
				if(c==itemchoice)
				    break;
				}
			}
			
			if( h->add_to_bag_spell( *itc )  ){

				h->pay_for_item( (*itc)->getprice() );
			}
			
			break;
 	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Market::Sell(void){
	Hero *h;
	int achoice,bchoice;
	
	h=heroes->chooseHero("use for selling");                                    //choose Hero
	h->show_items();

	cout<<"\nIf you want to sell weapon type 1, for armor type 2, for potion 3, for spell 4 : ";
	cin>>achoice;
	while(achoice<1||achoice>4){
		cout<<"Wrong Input.Type again : ";
		cin>>achoice;
	}

	switch(achoice){
		case 1:                                                                 //sell weapons
			cout<<"Selling weapon.Give the number of the weapon to be sold : ";    
			cin>>bchoice;
			if(! (h->sell_weapon(bchoice)) ){cout<<"\nNo such weapon.try selling again from Market menu.\n";}
			break;
		case 2:                                                                 //sell armor
			cout<<"Selling armor.Give the number of the armor to be sold : ";    
			cin>>bchoice;
			if(! (h->sell_armor(bchoice) ) ){cout<<"\nNo such armor. Try selling again from Market menu.\n";}
			break;
		case 3:                                                                 //sell potions
			cout<<"Selling potion.Give the number of the potion to be sold : ";    
			cin>>bchoice;
			if(! (h->sell_potion(bchoice)) ){cout<<"\nNo such potion. Try selling again from Market menu.\n";}
			break;
        case 4:                                                                 //sell spells
			cout<<"Selling spell.Give the number of the spell to be sold : ";   
			cin>>bchoice;
			if(! (h->sell_spell(bchoice)) ){cout<<"\n No such spell. Try selling again from Market menu.\n";}
			break;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Market::~Market(void){

    	list<Weapon*> :: iterator it;
		list<Armor*>  :: iterator ita;
		list<Potion*> :: iterator itb;
		list<Spell*>  :: iterator itc;

  		for (it=weapon_list.begin() ; it!= weapon_list.end(); ++it ){
			delete *it;
		}

		for ( ita=armor_list.begin() ; ita != armor_list.end(); ++ita ){
			delete *ita;
		}

		for ( itb=potion_list.begin() ; itb != potion_list.end(); ++itb ){
            delete *itb;
		}

		for ( itc=spell_list.begin() ; itc != spell_list.end(); ++itc ){
            delete *itc;
		}

  		weapon_list.clear();
		armor_list.clear();
		potion_list.clear();
		spell_list.clear();


}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Common::printOptions(void){

    cout<<"1: CheckInventory     3: Use potion    5: Move    7: Show equiped items "<<endl;
    cout<<"2: Show party stats   4: Display Map   6: Equip   8: Quit \n"<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Common::engage(){
    static bool reuse=false;                                                    //checks if it's the first time calling this function
																				//for a block without moving so i it's not it doesn't
	static ifstream mon("monster_list.txt");                                    //initialize battle

	if(YesNo() && (!reuse)){                                                    //YesNo() return bool based an a possibility

		cout<<"\n\n\n\t/./././. Monsters rule this block and are attacking you. ././././\n\n\t\t\t    Get ready for battle. \n\n";

		string tname;
		int a,b,tmp;
		int i=randomn(1,5);                                                     //randomn(arg1,arg2) return an int for arg1 up to arg2

		for(int n=0;n<i;n++){                                                   //creates the monsters
   	    	mon >> tname;
   	     	if ( mon.eof() ) break;

			a=randomn(1,3);                                                     
			b=heroes->get_average();                                            //decides the monster level based on an averge of the
			b=randomn( b-3,b+1);                                                //heroes levels

			if(b<1){b=1;}

			switch(a){
				case 1:                                                         //Dragon
                    monster_list.push_back( new Dragon(tname,b) );
                    break;
				case 2:
                    monster_list.push_back( new Exoskeleton(tname,b) );         //Exoskeleton
                    break;
				case 3:
                    monster_list.push_back( new Spirit(tname,b) );              //Spirit
                    break;
			}
	   	}

			tmp=battle();
			
			if(tmp==1){                                                         //option : flee from battle
				heroes->cut_money();
				cout<<"...........................................................";
				cout<<"\nYou escaped from battle.\nEach hero has lost 30% of his money in order to escape from the monsters."<<endl;
                cout<<"...........................................................\n\n";
				heroes->Revive();
            }
			else if(tmp==2){                                                    //option : Quit
                return 2;
			}                                 

            list<Monster*>::iterator it;                                        //delete monsters
			for ( it=monster_list.begin() ; it != monster_list.end(); ++it ){delete *it;}
			monster_list.clear();
	}
	
	cout<<"\t\t\t--------------------------";                                   //normal block menu and options from here(without battle)
	cout<<"\n\nYou are in a Common Block, the following options are available :\n"<<endl;

	int choice;
	string schoice;

	printOptions();

    while(true){
		cout<<"Common : Choose by typing the corresponding number (0 for options):";

	    cin>>schoice;
		choice=atoi(schoice.c_str());
 	    if( choice!= 0 && choice!=1 && choice!=2 && choice!=3 && choice!=4 && choice!=5 && choice!=6 && choice!=7 && choice!=8){cout<<"\nInvalid Input.\n\n";continue;}

		switch (choice){                                                        //menu options
			case 0: printOptions();break;
			case 1: heroes->checkInventory();break;
            case 2: heroes->printParty();break;
            case 3: heroes->usePotion();break;
            case 4: reuse=true;  return 0;                              		//display Map
            case 5: reuse=false; return 1;                                      //Move
			case 6: heroes->partyEquip(); break;
			case 7: heroes->showEquipment();break;
			case 8: return 2;                                                   //Exit Game
   		}
	}
return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Common::monster_average(){
	int i=0;

	list<Monster*>::iterator it;
	for(it=monster_list.begin();it!=monster_list.end();it++){
		i+=(*it)->get_level(); }

	return (int)(i/ (monster_list.size()) );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Monster * Common::chooseMonster(void){                                          //prints monsters and retutn the one the user choose
	int i,n=1;
	string choice;
	int nchoice;
	list<Monster*>::iterator it;

	cout<<"Choose which monster to attack.\n"<<endl;

	for (i=1, it=monster_list.begin() ; it != monster_list.end(); ++it,i++ ){
		cout<<i<<":";
		(*(*it)).printMonster();
	}
	cout<<"Choose : ";
	cin>>choice;
	nchoice=atoi(choice.c_str());

	while(nchoice>(int)monster_list.size() || nchoice<1){
	    cout<<"\nWrong Input. Type again : ";
        cin>>choice;
        nchoice=atoi(choice.c_str());
	}

	for ( it=monster_list.begin() ;nchoice>n; ++it,n++ ){}
  	return *it;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int Common::battle(void){
	int rounds=0,i=1,nchoice,msavg=monster_average();
	string choice;
	Hero *shero;
	Spell *sspell;
	Monster *smonster;
	bool flag=true;                                                             //used for entering the options menu for the same hero
	                                                                            //again if user choose an option like 4(displaystats),
	cout<<"Your are facing :\n"<<endl;                                          //6(show equipment)
    list<Monster*>::iterator it;
  	for ( it=monster_list.begin() ; it != monster_list.end(); ++it ){
			(*(*it)).printMonster();
	}

	while(!monster_list.empty() && heroes->alive()){

		while( i<=heroes->size() ){                                             //each hero attack
            
			shero=heroes->nextHero(i);                                          //enable a hero
			cout<<"\n/....................................................../"<<endl;
			cout<<"\nYou are using Hero : \n";shero->printHero();cout<<endl;
			cout<<"choose your action for this round :\n\n";
			flag=true;
			
			while(flag){
				flag=false;

            	cout<<"1: Attack      3: Use potion     5: Equip            7 : Escape battle"<<endl;
    			cout<<"2: castSpell   4: DisplayStats   6: Show equipment   8 : Quit\n"         <<endl;

    			cout<<"Choose : ";
    			cin>>choice;
        		while(choice!="1" && choice!= "2" && choice!= "3" && choice!= "4" && choice!= "5" && choice!= "6" && choice!= "7" && choice!= "8"  ){
    		    	cout<<"\nWrong Input. Type again : ";
					cin>>choice;
				}

				nchoice=atoi(choice.c_str());

				switch(nchoice){
					case 1:
						smonster=chooseMonster();                               //choose a monster to attack

     					if(!(smonster->take_damage( shero->get_damage() ))){    //if the monster is killed
             	        	shero->addXP(smonster->get_level() ) ; 		        //give xp to the hero
              	            shero->check_lvl();                         	    //check for level up
							monster_list.remove(smonster);delete smonster; 		//delete monster
						}
						
      					break;
						
					case 2:
						smonster=chooseMonster();
					 	sspell= shero->chooseSpell() ;
						if(!sspell->use(smonster,shero)){flag=true;}
						if(smonster->get_hp()==0){                              //if the monster is killed
							shero->addXP(smonster->get_level() ) ;              //give xp to the hero
							shero->check_lvl();                                 //check for level up
							delete smonster;monster_list.remove(smonster);
						}
                        
						break;
						
					case 3:
						shero->use_Potion();
					
						break;
						
					case 4:
                	    heroes->printParty();
                	    cout<<"Monsters : \n"<<endl;
                	    for ( it=monster_list.begin() ; it != monster_list.end(); ++it )
						(*(*it)).printMonster();
						cout<<endl;
						flag=true;                                              //allows this hero to enter the menu again
						break;
					case 5:
						shero->equip();
						
						break;
					case 6:
						shero->show_equiped();
						flag=true;                                              //allows this hero to enter the menu again
						break;
					case 7:
						return 1;
					case 8:
						return 2;
          		}
			}

        i++;
		}
		
		if( !monster_list.empty())                                              //turn of the monsters to attack
		{
			cout<<"\n\t\t:: Monster are attacking, take cover !! ::\n"<<endl;

			for ( it=monster_list.begin() ; it != monster_list.end(); ++it ){
				if( heroes->alive() ){
					shero=heroes->nextHero( randomn(1,heroes->size()) );
					cout<<(*it)->get_name()<<" attacking ";
					shero->take_damage( (*it)->get_damage() );
				}else{
					break;
				}
   			}


			i=1;
	   		decrease_counters();                                                //counters are kept for the effects of spells
			replenish();                                                        //at the end of each round some hp is replenished

			}
	
    	rounds++;

	}

	if( heroes->alive() ){
		heroes->addXP( msavg);                                                  //add xp to each hero
		heroes->Revive();                                                       //revive any hero who is dead
		heroes->set_all_money( msavg );                                         //money bonus for their win
	}
	else{
		heroes->dead();                                                         //make the appropriate action if all heroes died
	}

	heroes->check_lvl();                                                        //check for level up

return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Common::decrease_counters(void){                                           //counters are kept for the effects of spells
	list<Monster*>::iterator it;
	for (it=monster_list.begin() ; it != monster_list.end(); ++it){
		(*(*it)).decrease_counter();
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Common::replenish(void){
	list<Monster*>::iterator it;
	for (it=monster_list.begin() ; it != monster_list.end(); ++it)
		(*(*it)).Mreplenish();

	heroes->Replenish();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Common::~Common(void){

	list<Monster*>::iterator it;
	for (it=monster_list.begin() ; it!= monster_list.end(); ++it ){
			delete *it;
	}
	
	monster_list.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
