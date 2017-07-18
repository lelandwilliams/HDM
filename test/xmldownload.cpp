#include"xmldownload.h"

QString downloader::hostname = "";

/*class hostnameEventClass : public xmlreaderEvent
{
	public:
	hostnameEventClass(QString name, xmlreaderEvent *parent) : xmlreaderEvent(name, parent){;}
	void execFinishEvent(element *data);
};

void hostnameEventClass::execFinishEvent(element *data)
{
	//std::cout << "XMLREADER: recived hostname of " << data->content << std::endl;
	downloader::hostname = data->content;
}
*/

downloader::downloader( QObject * parent , const char * name) : QObject(parent, name)
{
	//std::cout << "In downloader::downloader() " << std::endl;
	//filename = "tmp.xml";
}

void downloader::exec()
{
	//std::cout << "In downloader::exec() " << std::endl;
	
	PasswordDialog *dlg = new PasswordDialog();
	if(dlg->exec() == QDialog::Accepted)
	{
			setloginName(dlg->loginname());
			setloginPassword(dlg->password());
	}
	else qApp->exit();

	filename = "tmp.xml";
	file.setName(filename);

	std::cout << "--- filename set " << std::endl;
	downloadAction=fetchServer;
	connect(&http, SIGNAL(responseHeaderReceived(const QHttpResponseHeader&)), this, SLOT(recieveResponseHeader(const QHttpResponseHeader&)));
	connect(&http, SIGNAL(done(bool)), this, SLOT(downloadFinished(bool)) );


	////////////////////////////////////
	//
	// Make Initial Contact to Host
	// and retrieve preferred
	// host name info
	//
	////////////////////////////////////
	request.setRequest("GET", "/Common/menu.asp?outputType=XML");
	request.setValue("HOST", "www.hattrick.org");
	http.setHost("www.hattrick.org");
	http.request(request);
}

void downloader::parseserver()
{
	std::cout << "now in parseserver" << std::endl;

	QDomDocument doc("");
	if(!file.open(IO_ReadOnly))
	{
		std::cout << "ERROR **** Unable to open File " << std::endl;
	}
	if(!doc.setContent(&file))
	{
		std::cout << "ERROR **** Unable to add file to DOM Document" << std::endl;
	}
	file.close();

	//
	// Parse file for hostname
	//
	
	QDomNodeList nodelist = doc.elementsByTagName("RecommendedURL");
	QDomNode node = nodelist.item(0);
	QDomElement e = node.toElement();
	node = e.firstChild();
	hostname = node.toText().data();

	hostname = hostname.remove("http://");
	std::cout << "hostname is " << downloader::hostname << std::endl;

	/////////////////////////////
	//
	// login with name, password
	// to recieve session id (cookie)
	//
	////////////////////////////

	http.setHost(hostname);
	request.setValue("HOST",hostname);

	getStr = QString("/Common/default.asp?outputType=XML&actionType=login&loginType=CHPP&Loginname=%1&readonlypassword=%2")
	.arg(loginName, loginPassword);
	//std::cout << std::endl << "LOGINSTRING :" << getStr << std::endl;

	downloadAction = login;
	request.setRequest("GET", getStr);
	http.request(request);
	std::cout << "exiting downloader()" << std::endl;
}


void downloader::parselogin()
{
	CookieString = response.value("set-cookie");
	CookieString.remove("path=/"); 

	//std::cout << "COOKIE: " << CookieString;
	request.setValue("cookie", CookieString);
	request.setValue("set-cookie", CookieString);
	getStr="/common/players.asp?outputType=XML&actionType=view";
	request.setRequest("GET", getStr);
	downloadAction = fetchPlayers;
	http.request(request);
}

void downloader::recieveResponseHeader(const QHttpResponseHeader &resp)
{
	std::cout << std::endl << "recieving response" << std::endl;
	QStringList keys = resp.keys();
	for(QStringList::Iterator it = keys.begin(); it!=keys.end(); it++)
		std::cout << *it << " => " << resp.value(*it) << std::endl;
	std::cout << "COOKIE: " << resp.value("set-cookie");

	response = resp;
	std::cout << std::endl << "response recived" << std::endl;
}

void downloader::downloadFinished(bool error)
{
	//std::cout << "In downloader::downloadFinished(bool)" << std::endl;

	if(error)
	{/*
		QMessageBox::warning(this, "QHttp",
				QString( "Download Error with QHttp: %1\n " )
				.arg(http.errorString()));
	*/}

	if(downloadAction==fetchPlayers)
	{
		QFile playerfile("players.xml");
		playerfile.open(IO_WriteOnly);
		playerfile.writeBlock(http.readAll());
		playerfile.close();
		HDM::parsePlayers();
		qApp->quit();
	}
	else
	{
		if(!file.open(IO_WriteOnly))
		{
		//	QMessageBox::warning(this, "downloader",
		//QString( "Cannot Write to File %1\n%2\n ") .arg(file.name()) .arg(file.errorString()) );
		
		std::cout << std::endl << "CANNOT OPEN FILE" << std::endl;
		}

		file.writeBlock(http.readAll());
		file.close();
		//	std::cout << "--- file written" << std::endl;

		if(downloadAction==login){parselogin();}
		else if(downloadAction==fetchServer){parseserver();}
	}
}

