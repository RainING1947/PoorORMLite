#include <iostream>

#include "PoorORMLite.h"

struct MyClass
{
	int id;
	double score;
	std::string name;
	ORMAP(MyClass, id, score, name)
};

using namespace Poor_ORM;

int main()
{
	Poor_ORM::ORMapper<MyClass> mapper("test.db");

	mapper.CreateTable();

	mapper.Insert(MyClass {1, 2.5, "Jessica"});
	
	mapper.Insert(MyClass{ 2, 3.8, "Gaven.IV" });

	std::vector<MyClass> initObjs = {
		{4, 2.2, "Febiveen"},
		{5, 3.3, "Latex"}
	};
	
	MyClass initObj = {3, 4.56, "Lax"};
	mapper.Insert(initObj);
	mapper.Insert(initObjs[0]);
	mapper.Insert(initObjs[1]);

	initObj.name = "Wooooooop";
	initObj.score = 6.6666666;
	mapper.Update(initObj);

	mapper.Delete(initObjs[1]);

	//mapper.DropTable();
	
	MyClass qHelper;

	auto query = mapper.Query(qHelper)
		//.Where(
		//	Field(qHelper.id) <= 3 &&
		//	Field(qHelper.score) >= 1.0)
		//.OrderBy(qHelper.id, true)
		.Limit(2, 1)
		.ToVector();

	for (auto c : query)
	{
		std::cout << c.id << " " << c.score << " " << c.name << std::endl;
	}

	std::cin.get();
	return 0;
}