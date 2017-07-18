#include "xmlsqlmap.h"

bool xmlsqlmap::instantiated = false;
xmlsqlmap* xmlsqlmap::_singleton = NULL;
QString xmlsqlmap::language = "EN";

void xmlsqlmap::printMap()
{
	if(!instantiated)
		_singleton = new xmlsqlmap();

	for(QMap<QString,QString>::Iterator it = _singleton->theMap.begin(); it != _singleton->theMap.end(); ++it)
		std::cout << it.key().latin1() << " --> " << it.data().latin1() << std::endl;
}

bool xmlsqlmap::contains(QString s)
{
	if(!instantiated)
		_singleton = new xmlsqlmap();
	
	return(_singleton->theMap.contains(s));
}

QString xmlsqlmap::translate(QString s)
{
	if(!instantiated)
		_singleton = new xmlsqlmap();
	
	return(_singleton->theMap[s]);
}

xmlsqlmap::xmlsqlmap()
{
	instantiated = true;

	if(language == "EN")
	{
		theMap["PlayerID"] = "ID";
		theMap["PlayerName"] = "Name";
		theMap["PlayerNumber"] = "";
		theMap["Age"] = "Age";
		theMap["MarketValue"] = "";
		theMap["TSI"] = "TSI";
		theMap["PlayerForm"] = "Form";
		theMap["Statement"] = "";
		theMap["Experience"] = "Experience";
		theMap["Leadership"] = "Leadership";

		theMap["Salary"] = "Salary";
		theMap["IsAbroad"] = "";

		theMap["Agreeability"] = "";
		theMap["Aggressiveness"] = "";
		theMap["Honesty"] = "";

		theMap["LeagueGoals"] = "";
		theMap["CupGoals"] = "";
		theMap["FriendliesGoals"] = "";
		theMap["CareerGoals"] = "";
		theMap["CareerHattricks"] = "";

		theMap["Specialty"] = "";
		theMap["TransferListed"] = "";
		theMap["NationalTeamID"] = "";
		theMap["CountryID"] = "";
		theMap["Caps"] = "";
		theMap["CapsU20"] = "";

		theMap["Cards"] = "";
		theMap["InjuryLevel"] = "";

		theMap["StaminaSkill"] = "Stamina";
		theMap["KeeperSkill"] = "Keeper";
		theMap["PlaymakerSkill"] = "Playmaking";
		theMap["ScorerSkill"] = "Scoring";
		theMap["PassingSkill"] = "Passing";
		theMap["WingerSkill"] = "Winger";
		theMap["DefenderSkill"] = "Defending";
		theMap["SetPiecesSkill"] = "SetPieces";
	}
}

