#ifndef XMLREADER_H
#define XMLREADER_H

#include<iostream.h>
#include<qstring.h>
#include<qfile.h>
#include<qvaluestack.h>
#include<iostream>
#include<stdlib.h>
#include<qmap.h>
#include<qapplication.h>
#include<qptrlist.h>

typedef QMap<QString, QString> StringMap;
class xmlreaderEvent;

struct element
{
	QString elementName;
	StringMap *attributes;// key == attribute name, value == attribute value
	QString content;
};

class xmlreaderEvent
{
	public:
	
	static xmlreaderEvent * DOC_ROOT;
	xmlreaderEvent * parentEvent;

	xmlreaderEvent(QString elementName="docRoot", xmlreaderEvent *parent=xmlreaderEvent::DOC_ROOT);
	~xmlreaderEvent();
	void registerChild(xmlreaderEvent *child);
	virtual void execStartEvent( element *data ){;}
	virtual void execFinishEvent( element *data ){;}
	xmlreaderEvent * hasChild( QString childName);
	QString getName(){return elementName;}

	private:

	QString elementName;
	QPtrList<xmlreaderEvent> children;

};


//xmlreaderEvent * xmlreaderEvent::DOC_ROOT = 0;
	
class xmlreader
{
	public:
	xmlreader(QString filename, xmlreaderEvent *root);
	void parse();
	
	private:
	QFile file;
	QValueStack<element*> stack;
	QValueStack<xmlreaderEvent*> handlerStack;
	element * currentElement;
	xmlreaderEvent* currentHandler;
	xmlreaderEvent *docRoot;
	QChar curChar;
	QString token;
	QString text;
	
	bool debug;
	int tablevel;
	int leftBracketPosition;
	int rightBracketPosition;
	int currentPosition;
	void taboutput();
	QString textBetween(int beginning, int end);
		
	bool emptyElement;

	void xmlError(QString str);
	void validateName(QString str);
	void getXmlData();
	void parseElementBegin();
	void parseElementEnd();
	void parseProcessingInstruction();
	void parseComment();
	void parseCDATA();
	void parseAmpersand();

	int parser_findWhiteSpace();

	void endTagEvent();
	void startTagEvent();

};

#endif
