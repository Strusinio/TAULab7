#ifndef __CLUB_DATABASE__
#define __CLUB_DATABASE__


#include <map>
#include <vector>
#include <string>


class FootballClub
{
public:
	long id{};
	std::string  name;
	int year{};

	FootballClub();
	FootballClub(std::string name, int year);
};

class FootballClubDataBase {
public:
	FootballClubDataBase();
	std::vector<FootballClub> getAll();
	FootballClub createFootballClub(FootballClub footballClub);
	FootballClub findFootballClub(long id);
	void deleteFootballClub(long id);
protected:
	std::map<int, FootballClub> map;
private:
	unsigned long long int id();
};

class FootballClubDataBaseHelper : public FootballClubDataBase
{
public:
	FootballClubDataBaseHelper();

	std::map<int, FootballClub> &getReferenceToMap();
};

#endif 
