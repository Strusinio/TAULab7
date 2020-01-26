#include "stdafx.h"
#include "FootballClubDataBase.hpp"
#include <algorithm>
#include <utility>
#include <stdexcept>
#include <map>
#include <vector>

using namespace std;

FootballClubDataBase::FootballClubDataBase() = default;

vector<FootballClub> FootballClubDataBase::getAll() {
	vector<FootballClub> clubs;

	for (auto& e : map) {
		clubs.push_back(e.second);
	}
	return clubs;
}

FootballClub FootballClubDataBase::createFootballClub(FootballClub footballClub) {
	footballClub.id = id();
	map.insert(std::pair<int, FootballClub>(footballClub.id, footballClub));
	return  map[footballClub.id];

}

FootballClub FootballClubDataBase::findFootballClub(long id)
{
	std::map<int, FootballClub>::iterator it;
	it = map.find(id);

	if (it == map.end()) {
		throw invalid_argument("cant find");
	}

	return map.find(id)->second;
}

void FootballClubDataBase::deleteFootballClub(long id)
{
	std::map<int, FootballClub>::iterator it;
	it = map.find(id);
	if (it == map.end())
	{
		throw invalid_argument("cant find");
	}
	else {
		map.erase(id);
	}
}

unsigned long long int FootballClubDataBase::id()
{
	static unsigned long long int i = 0;
	return ++i;
}

FootballClub::FootballClub() = default;

FootballClub::FootballClub(string name, int year) : name(move(name)), year(year)
{
}

FootballClubDataBaseHelper::FootballClubDataBaseHelper() : FootballClubDataBase()
{
}

map<int, FootballClub>& FootballClubDataBaseHelper::getReferenceToMap()
{
	return map;
}