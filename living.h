#ifndef living
#define living

#include <string.h>
#include <string>
class Living
{
private:	
	std::string name;
	int level;
    	int maxhp;
	int hp;
public:
	Living(const std::string , int ,int);
	std::string get_name(void);
	int get_level(void);
	int get_maxhp(void);
	int get_hp(void);
	void lvl_up(void);
	void set_lvl(void);
	void add_hp(int i);
	virtual ~Living(void);
};

#endif
