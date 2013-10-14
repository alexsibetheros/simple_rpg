#include <iostream>
#include "position.h"
#include "Party.h"
#include "item.h"
#include "block.h"
#include "grid.h"
#include "hero.h"
#include "spell.h"
#include "living.h"
#include "monster.h"

#include <ctime>
#include <cstdlib>
#include <iostream>
#include <list>
#include <iomanip>
#include <fstream>
#include <string>

int randomn(int a,int b); //returns 0 or 1, it only needs the seed to be set at the calling function
bool YesNo(void);         //returns a number between 0 and n
