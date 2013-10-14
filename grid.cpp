#include "header.h"
#include  <sstream>

using namespace std;

Grid::Grid(void){                                                               //creates the grid from a file

	int i,j,count=0,count2,tmapn;
    string tmp,tmap;
    char*ttmap;
	char c;
	int tsize;
	
	cout<<"Choose which map to play :\n"<<endl;
	cout<<"1: map01(default)   2: map02(tricky)   3: map03(izi)\n"<<endl;
	cout<<"Input :";
	cin>>tmap;
	
	while(tmap!="1" && tmap!="2" && tmap!="3"){
		cout<<"Invalid input. Try again :";
		cin>>tmap;
	}
		
	tmapn=atoi(tmap.c_str());
	
	if(tmapn==1)		{ttmap="map01.txt";}
	else if(tmapn==2)   {ttmap="map02.txt";}
	else                {ttmap="map03.txt";}
	
	ifstream map(ttmap);

	map>>tmp;
	map>>tsize;
	size=tsize;
	cout<<"Loading map...";
	cout<<" "<<tmp<<" loaded, grid size: "<<tsize<<".\n"<<endl;
		
	gridtable=new Block**[size];
	for(i=0;i<size;i++){
		gridtable[i]=new Block*[size];
	}
  

	i=0;j=0;
       for(count=0;count<tsize;count++){
		map>>tmp;
		istringstream ss(tmp);
		j=0;
		for(count2=0;count2<tsize;count2++){
			ss>>c;
			if(c=='c'||c=='C'){
				gridtable[i][j]=new Common();
			}else if(c=='M'||c=='m'){
           		gridtable[i][j]=new Market;
			}else if(c=='n'||c=='N'){
                gridtable[i][j]=new NonAccessible;
			}

			j++;
			}
		i++;
 	}

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool Grid::validMove(int tx,int ty){

	if(gridtable[tx][ty]->isNonAccessible()){return false;}
	else                                    {return true; }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void Grid::PrintGrid(void){
	int i,j,k;
	string tmp;
	cout<<" ";
	for(k=0;k<size;k++){
		cout<<"___";
	}cout<<endl;
	
	for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			tmp=gridtable[i][j]->content();
			
			if(tmp.length()!=2)
			{tmp+=" ";}
			cout<<"|"<<tmp;
		}
		cout<<"|"<<endl;cout<<" ";
		for(k=0;k<size;k++){
			cout<<"___";
		}cout<<endl;
	}
	cout<<endl;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Grid::~Grid(){
    
	int i,j;
    for(i=0;i<size;i++){
		for(j=0;j<size;j++){
			delete gridtable[i][j];
		}
		delete[] gridtable[i]; 
	}
	delete[] gridtable;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
