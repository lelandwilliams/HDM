/* This File includes the map that connects the xml tags from players.asp to the sql headers I used.
 * Perhaps in future versions this map can be altered depending on language, or maybe the sql headers
 * can be the same as the xml (for convenience) and the name mapping can be handled at runtime { ie with
 * a SELECT xxx AS statement */

#ifndef XMLSQLMAP_H
#define XMLSQLMAP_H

#include<qmap.h>
#include<qstring.h>
#include<qvaluelist.h>
#include<iostream>

class xmlsqlmap{

	public:
		static QString translate(QString s);
		static bool contains(QString s);
		static xmlsqlmap* _singleton; 
		static QString language;
		static void printMap();

	private:
		QMap<QString,QString> theMap;
		xmlsqlmap();
		static QValueList<QString> keys(){return(_singleton->theMap.keys());}
		static bool instantiated;
};


#endif
