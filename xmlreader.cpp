#include"xmlreader.h"

xmlreaderEvent * xmlreaderEvent::DOC_ROOT = 0;

xmlreaderEvent::xmlreaderEvent( QString name, xmlreaderEvent *parent)
{

	elementName = name;
	parentEvent = parent;
	
	std::cout << std::endl << "New Event Handler '" << name << "' registered." << std::endl;

	if(!DOC_ROOT)
	{
		std::cout << "\t is registered as doc_root" << std::endl ;
		DOC_ROOT = this;
	}
	else
	{
		if(!parent)
			parentEvent = DOC_ROOT;

		parentEvent->registerChild(this);
		std::cout << "\t registered as child of " << parentEvent->getName() << std::endl;
	}
}

xmlreaderEvent::~xmlreaderEvent()
{
	QPtrListIterator<xmlreaderEvent> it(children);
	it.toFirst();
	while(!it.atLast())
	{
		it.current()->~xmlreaderEvent();
		delete it.current();
		++it;
	}
}

xmlreaderEvent * xmlreaderEvent::hasChild( QString name)
{
	std::cout << std::endl << getName() << ":  request for child name : " << name << std::endl;
	xmlreaderEvent * returnValue = 0;
	
	if(children.count())
		for(uint i = 0; i!=children.count(); i++)
			if(children.at(i))
				if(children.at(i)->getName() == name)
					returnValue = children.at(i);

	if(returnValue)
		std::cout << returnValue->getName() << "  found." << std::endl;
	else
		std::cout << "No child found" << std::endl;

	return(returnValue);
}

void xmlreaderEvent::registerChild(xmlreaderEvent *child)
{
	children.append(child);
	std::cout << getName() << ": register new child '" << child->getName() << "'" << std::endl;
}

xmlreader::xmlreader(QString filename, xmlreaderEvent *root)
{
	debug = false;

	if(debug)
		std::cout << "Entering Constructor" << std::endl;

	docRoot = root;
	handlerStack.push(docRoot);
	file.setName(filename);
	file.open(IO_ReadOnly);
	QTextStream stream(&file);
	text = stream.read();

	tablevel=0;

	if(debug)
		std::cout << "Exiting Constructor " << std::endl;
}

QString xmlreader::textBetween( int beginning, int end)
{
	int length = end - beginning + 1;
	return(text.mid(beginning,length));
}

void xmlreader::parse()
{
	/*
	text.stripWhiteSpace();
	std::cout << "parse(): stripping white space" << std::endl;
	*/
	currentPosition = 0;
	leftBracketPosition = text.find("<", currentPosition);
	while(leftBracketPosition != -1)
	{
		// treat any intervening text as content belonging to current element
		if(leftBracketPosition > currentPosition)
		{
			if(stack.top())
				stack.top()->content += textBetween(currentPosition, leftBracketPosition -1);
			currentPosition = leftBracketPosition;
		}
			//processText(); 

		//is start element, end element, process instructions or comment ?

		if (text.mid((leftBracketPosition + 1) , 2) == "--") // is < the start of a comment ?
			parseComment();
		else if (text.mid((leftBracketPosition + 1), 1) == "/") // is '<' the start of an end-element ?
			parseElementEnd();
		else if (text.mid((leftBracketPosition + 1), 1) =="?") // is '<' the start of a processing instruction ?
			parseProcessingInstruction();
		else if (text.mid((leftBracketPosition + 1), 1) =="!") // is '<' the start of  CDATA or element type definition?
			parseCDATA();
		else
			parseElementBegin();  // not anything else, so treat as start-element
		
		leftBracketPosition = text.find("<", currentPosition); // this is the while conditional
	}

	if(debug)
	{
		std::cout << "parse(): No further '<' found so exiting at position " << currentPosition << std::endl;
		std::cout << "file length is " << text.length() << std::endl;
	}
}

void xmlreader::parseElementBegin()
{

	// I'm assuming that white space is permitted between a '<' and 
	// an ElementName and also between the name and the '>'

	
	emptyElement = false;
	currentElement = new element;
	currentElement->attributes = new StringMap;
	
	// 
	// find corrisponding right bracket and check to see if
	// this element is and empty element
	//
	
	rightBracketPosition = text.find(">", leftBracketPosition);
	
	if(rightBracketPosition == -1)
		xmlError("No rightBracket Found");

	int elementEndPosition = rightBracketPosition -1;
	
	if(text.mid((rightBracketPosition -1), 1) == "/")
	{
		emptyElement = true;
		elementEndPosition--;
		if(debug)
			std::cout << " Element is An empty element " << std::endl;
	}

	currentPosition = leftBracketPosition + 1;

	if( text.find("<", currentPosition) < rightBracketPosition )
		xmlError("No < permitted inside another tag");

	while(text.at(currentPosition).isSpace())
		currentPosition++; //if white space is permitted here by XML rules, else change to xmlError

	// 
	// check for presence of white space between current position and end of tag
	// since this could indicate the presence of attributes
	// 
	
	if(!parser_findWhiteSpace())
	{
		//
		// since there is not white space before >
		// assume all text in between is the element name
		//

		currentElement->elementName = textBetween(currentPosition, elementEndPosition );
		validateName(currentElement->elementName);
	}
	else
	{
		
		//
		// since there is white space before >,
		// get element name and move cursor to look for attributes
		//
		
		currentElement->elementName = textBetween(currentPosition, (parser_findWhiteSpace() -1) );
		validateName(currentElement->elementName); // NOT IMPLEMENTED YET
		currentPosition = parser_findWhiteSpace() + 1;

		int eqPosition = text.find("=", currentPosition);

		// 
		// an '=' indicates the presence of attributes
		//

		while(eqPosition != -1 && eqPosition < elementEndPosition)
		{
			int leftQuotePosition;
			int rightQuotePosition;
			QString attributeName; 
			QString attributeValue;

			attributeName = textBetween(currentPosition, (eqPosition - 1));
			attributeName = attributeName.stripWhiteSpace();
			validateName(attributeName);

			// find the attribute value by finding the beginning and end quotes

			leftQuotePosition = text.find("\"", currentPosition); 
			// 
			// perhaps the attribute uses single instead of double quotes
			//

			if((text.find("'", currentPosition)!= -1) &&  (text.find("'", currentPosition) < leftQuotePosition)) 
				//if text.find returns -1 then item not found
			{
				leftQuotePosition = text.find("'", currentPosition); 
				rightQuotePosition = text.find("'", leftQuotePosition +1 );
			}
			else
				rightQuotePosition = text.find("\"", (leftQuotePosition+1));

			// make sure the quotes are within the element tag

			if((leftQuotePosition > rightBracketPosition) || (leftQuotePosition == -1) )
				xmlError("Error in attribute value assignment - missing left quote");
			if((rightQuotePosition > rightBracketPosition) || (rightQuotePosition == -1) )
				xmlError("Error in attribute value assignment - missing right quote");

			// fetch attribute value
				
			attributeValue = textBetween( (leftQuotePosition +1) , (rightQuotePosition -1 ) );
			if(attributeValue.length() > 100)
				xmlError("arribute value is too long");

			// make sure attribute isn't already defined
			//
			// the return values of the methods in the following
			// if clause are both QMap::iterator

			if(currentElement->attributes->find(attributeName) != currentElement->attributes->end())
				xmlError("attribute already appears in this element");

			// save attribute info in attribute map

			currentElement->attributes->insert(attributeName, attributeValue);

			//
			// set currentPosition to after last right quote, 
			// look for another '=', and start loop over
			//

			currentPosition = rightQuotePosition +1;
			eqPosition = text.find("=", currentPosition);
		} // end of  while(eqPosition != -1 && eqPosition < elementEndPosition)}
	} // if(!parser_findWhiteSpace())

	if(emptyElement)
		endTagEvent();
	else
	{
		startTagEvent();// put element and attribute values on stack
	}

	currentPosition = rightBracketPosition +1;
}

void xmlreader::parseElementEnd()
{

	rightBracketPosition = text.find(">", currentPosition);
	token = textBetween((leftBracketPosition +2),(rightBracketPosition -1));
	validateName(token);
	endTagEvent();
	currentPosition = rightBracketPosition +1;
}

void xmlreader::parseProcessingInstruction()
{
	// for right now, just ignore them
	
	rightBracketPosition = text.find(">");
	if(rightBracketPosition == -1)
		xmlError("No Right Bracket for this Element");
	currentPosition = rightBracketPosition +1;
}

void xmlreader::parseComment()
{
	currentPosition +=3; // skip past current <, then 2 '-' , then to next character
	rightBracketPosition = text.find("-->", currentPosition); //search for end comment character string
	if(rightBracketPosition == -1) // -1 indicates string not found
		xmlError("No End Comment Tag found");
	currentPosition = rightBracketPosition +3;
}

void xmlreader::parseCDATA()
{
	xmlError("Oh Crap !!! CDATA !");
}

int xmlreader::parser_findWhiteSpace()
{
	int i;

	for(i = currentPosition; i < rightBracketPosition; i++)
		if(text.at(i).isSpace())
			return i;

	return 0;
}

void xmlreader::validateName(QString name)
{
	//name+="whatever";

}


void xmlreader::endTagEvent()
{
	//
	// This method handles both end tags
	// ( </Name>) and empty elements (<Name/>)
	//
	
	

	if(!emptyElement)
	{
		currentElement = stack.pop();
		currentHandler = handlerStack.pop();
	}
		
	if(currentElement->elementName != token)
		xmlError(" End Tag does not match Start Tag ");

	if(debug)
	{
		taboutput();
		if(currentElement->content.length())
			std::cout << "CONTENT : " << currentElement->content << std::endl ;
		else
			std::cout << "NO CONTENT" << std::endl ;
		taboutput();
		std::cout << "END ELEMENT \"" << token << "\"" << std::endl ;
		
		if(stack.top())
			tablevel--; // if stack.top is empty (nothing no stack) then the parser has arrived again
					// at DOCROOT
	}


	//
	//  signal End Element Event
	//
	
//	currentHandler = handlerStack.pop();
	if(currentHandler)
		currentHandler->execFinishEvent(currentElement);
	//
	// now kill all dynamic elements
	//
	
	delete currentElement->attributes;
	delete currentElement;
}

void xmlreader::taboutput()
{
	if(tablevel)
		for(int i =0; i < tablevel; i++)
			std::cout << "\t";
}

void xmlreader::xmlError(QString errorMessage)
{
	std::cout << "*** Error found by xmlReader *** " << std::endl;
	std::cout << " at char position " << currentPosition << std::endl;
	std::cout << errorMessage << std::endl;

	//qApp->quit();
	std::exit(0);
}
	

	
void xmlreader::startTagEvent()
{
	if(debug)
	{
		if(stack.top())
			tablevel++;
		taboutput();
		std::cout << "START ELEMENT \"" << currentElement->elementName << "\"" << std::endl ;
		if(currentElement->attributes->size())
		{
			tablevel++;
			
			for(StringMap::iterator it = currentElement->attributes->begin(); it!= currentElement->attributes->end(); it++)
			{
				taboutput();
				std::cout << "ATTRIBUTE " << it.key() << " = " << it.data() << std::endl ;
			}

			tablevel--;
		}

		
	}

	currentHandler = handlerStack.top() ? handlerStack.top()->hasChild( currentElement->elementName ) : 0 ;
//	currentHandler = handlerStack.top()->hasChild( currentElement->elementName );
	
	if( currentHandler )
		currentHandler->execStartEvent(currentElement);
	
	handlerStack.push(currentHandler);
	std::cout << "Handler Stack size : " << handlerStack.size() << std::endl;
//	currentHandler = 0;
	
	stack.push(currentElement);
	currentElement =0;

	//
	// insert later code for event handling
	// 
}

