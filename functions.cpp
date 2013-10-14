#include "header.h"

bool YesNo(void){ //returns 0 or 1, it only needs the seed to be set at the calling function
        if(randomn(0,9)<6){return true;}
        return false;
}

int randomn(int lm,int hm){//returns a number between 0 and n
	return rand() % (hm+1-lm)+lm;
}
