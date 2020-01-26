// ConsoleApplicationTAU7.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "FootballClubDataBase.hpp"

TEST_CASE("method exists check ")
{
	FootballClubDataBaseHelper database = FootballClubDataBaseHelper();

	REQUIRE_NOTHROW(database.getAll());
}

TEST_CASE("Test getAll() method ")
{
	FootballClubDataBaseHelper database = FootballClubDataBaseHelper();

	SECTION("new class should be empty") {
		REQUIRE(database.getAll().empty());
	}

	SECTION("object return if map is not empty check")
	{
		FootballClub footballClub = FootballClub("FC Barcelona", 1899);
		std::map<int, FootballClub>* mapExample = &database.getReferenceToMap();
		mapExample->insert(std::pair<int, FootballClub>(1, footballClub));

		REQUIRE(database.getAll().size() == 1);
		REQUIRE(database.getAll()[0].id == 0);
		REQUIRE(database.getAll()[0].name == "FC Barcelona");
		REQUIRE(database.getAll()[0].year == 1899);
	}
}

TEST_CASE("validate if createFC method exists") {
	FootballClubDataBaseHelper database = FootballClubDataBaseHelper();
	FootballClub footballClub = FootballClub("FC Barcelona", 1899);

	REQUIRE_NOTHROW(database.createFootballClub(footballClub));
	//id = 1

}

TEST_CASE("createFC test method ") {
	FootballClubDataBaseHelper database = FootballClubDataBaseHelper();
	FootballClub footballClub = FootballClub("FC Barcelona", 1899);

	SECTION("return FC") {

		auto createdFootballClub = database.createFootballClub(footballClub);
		//id = 2 
		REQUIRE(createdFootballClub.year == 1899);
		REQUIRE(createdFootballClub.name == "FC Barcelona");
	}

	SECTION("FC id assing") {
		auto createdFootballClub = database.createFootballClub(footballClub);
		//id = 3
		REQUIRE(createdFootballClub.id == 3);
	}

	SECTION("check if 3 elements are in map") {
		database.createFootballClub(footballClub);				
		//id = 4
		database.createFootballClub(footballClub);
		//id = 5
		database.createFootballClub(footballClub);	
		//id = 6

		auto size = database.getReferenceToMap().size();

		REQUIRE(size == 3);
	}
}

TEST_CASE("findFC Test  Method ") {
	FootballClubDataBaseHelper database = FootballClubDataBaseHelper();
	FootballClub footballClub = FootballClub("FC Barcelona", 1899);

	SECTION("exception thrown if FC with given id not exist")
	{
		REQUIRE_THROWS(database.findFootballClub(10));
	}

	SECTION("find object by given id")
	{
		FootballClub footballClubInsert = FootballClub("Real Madrid", 1902);
		database.createFootballClub(footballClubInsert);				
		//id = 7

		REQUIRE(database.findFootballClub(7).id == 7);
		REQUIRE(database.findFootballClub(7).name == "Real Madrid");
		REQUIRE(database.findFootballClub(7).year == 1902);
	}
}

TEST_CASE("deleteFC Method Test") {

	SECTION("remove by given id")
	{
		FootballClubDataBaseHelper database = FootballClubDataBaseHelper();
		FootballClub footballClub = FootballClub("Valencia", 1919);
		database.createFootballClub(footballClub);								
		//id = 8

		REQUIRE(database.findFootballClub(8).id == 8);

		database.deleteFootballClub(8);

		REQUIRE(database.getAll().empty());
	}

	SECTION("exception thrown when try delete no existing FootballClub")
	{
		FootballClubDataBaseHelper database = FootballClubDataBaseHelper();
		REQUIRE_THROWS(database.deleteFootballClub(1919));
	}
}

SCENARIO("deleted data from database", "[FCDataBase][deleteFC][bdd]") {

	GIVEN("FC with id = 1 & id = 2") {
		FootballClubDataBaseHelper database = FootballClubDataBaseHelper();
		FootballClub footballClub = FootballClub("FC Barcelona", 1899);
		footballClub.id = 1;

		FootballClub footballClub2 = FootballClub("Real Madrid", 1902);
		footballClub2.id = 2;

		std::map<int, FootballClub>* maps = &database.getReferenceToMap();
		maps->insert(std::pair<int, FootballClub>(footballClub.id, footballClub));
		maps->insert(std::pair<int, FootballClub>(footballClub2.id, footballClub2));

		REQUIRE(maps->size() == 2);


		WHEN("delete FC id = 1") {
			database.deleteFootballClub(1);

			THEN("DB size equals 1") {
				REQUIRE(database.getAll().size() == 1);
			}

			THEN("FC with id is still in DB") {
				REQUIRE(database.findFootballClub(2).name == "Real Madrid");
			}
		}
	}
}