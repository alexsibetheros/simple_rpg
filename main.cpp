/*
  Name: ChronicSeq
  Copyright: 2011
  Author: Chronis John, Sibetheros Alexandros
  Date: 27/02/11
  Description: oop project
*/

#include "header.h"

using namespace std;

int main(int argc,char* argv[]){

	srand(time(NULL));
	
	cout<<"\n\n\t\t\tChronicSeq initialazing...\n\n"<<endl;

	Grid g;                                                                     //creating the Grid

	Party party(&g);                                                            //creating the Party

	party.operate();                                                            //Play.

    return 0;
}
