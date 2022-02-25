#include "reader/include/FileReader.h"

#include <string>
#include <vector>

int main()
{
	std::string full = ",split,me";
	//std::vector<std::string> list = split(full, ',');

        std::vector<std::string> list;
	std::stringstream ss(full);
	
	while (ss.good()) {
		std::string substr;
		getline(ss, substr, ',');
		list.push_back(substr);
	}

	if ((list.size() != 3) && (list[0] == ""))
	{
		return 1;
	} else return 0;
	
	//if (list[0] == "")
	//{
//		return 0;
//	}	
}

