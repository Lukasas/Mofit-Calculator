#include <string>
#include <sstream>
#include <vector>
struct Node
{
	int type;
	std::string value;
	Node(){}
	Node(int t, std::string v)
	{
		type = t;
		value = v;
	}
};

std::string Make_Calculation(std::string & input);