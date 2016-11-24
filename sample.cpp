#include <iostream>

#include "PoorORMLite.h"

struct MyClass
{
	int id;
	double score;
	std::string name;
	ORMAP(MyClass, id, score, name)
};

struct PlayerInfo
{
	std::string name;
	std::string password;
	int pokemonNumber;
	int rank;
	std::string beginDateTime; //201611171230 2016-11-17 12:30
	std::string gameTime; //12003 120hours 3minutes
	ORMAP(PlayerInfo, name, password,
		pokemonNumber, rank, beginDateTime,
		gameTime)
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

	PlayerInfo playerInfo = {
		"Lee",
		"2014232",
		0,
		9999,
		"201611171230", //201611171230 2016-11-17 12:30
		"122300" //1223hours 00minutes
	};

	Poor_ORM::ORMapper<PlayerInfo> mapper1("playerinfo.db");
	mapper1.CreateTable();
	mapper1.Insert(playerInfo);
	PlayerInfo qHelper1;
	auto query1 = mapper1.Query(qHelper1)
		.ToVector();
	for (auto c : query1)
		std::cout << c.name << " " << c.password << std::endl;

	std::cin.get();
	return 0;
}