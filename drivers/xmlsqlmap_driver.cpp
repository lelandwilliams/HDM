#include<qstring.h>
#include"xmlsqlmap.h"
#include<iostream>

void containsTest(QString str)
{
	std::cout << str << " -> " ;
	if( xmlsqlmap::contains(str))
		std::cout << "TRUE" << std::endl;
	else
		std::cout << "FALSE" << std::endl;
}

void printValue(QString str)
{
	std::cout << str << "-> " << xmlsqlmap::translate(str) << std::endl;
}

int main(){

	std::cout << "<-------====== Xmlsqlmap T E S T ======------>" << std::endl << std::endl;

	std::cout << "\t\t TEST FOR PRESENCE OF VARIOUS KEYS IN theMap" << std::endl << std::endl;
	containsTest("test");
	containsTest("boogyman");
	containsTest("PlayerID");
	containsTest("Experience");

	std::cout << "\t\t TEST RETRIEVEING VALES OF KEYS FROM  theMap" << std::endl << std::endl;
	printValue("Experience");
	printValue("DefenderSkill");
	printValue("MarketValue");

	std::cout << "\t\t PRINT OUT ALL KEYS & VALUES FORM theMap" << std::endl << std::endl;
	xmlsqlmap::printMap();
	return 0;
	}


