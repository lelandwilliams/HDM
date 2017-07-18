-- MySQL dump 9.11
--
-- Host: localhost    Database: 
-- ------------------------------------------------------
-- Server version	4.0.25-log

--
-- Current Database: hattrick
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `hattrick`;

USE hattrick;

--
-- Table structure for table `assignments`
--

DROP TABLE IF EXISTS `assignments`;
CREATE TABLE `assignments` (
  `ID` int(11) NOT NULL default '0',
  `positionID` int(11) NOT NULL default '0',
  `depth` int(11) NOT NULL default '0'
) TYPE=MyISAM;

--
-- Dumping data for table `assignments`
--


/*!40000 ALTER TABLE `assignments` DISABLE KEYS */;
LOCK TABLES `assignments` WRITE;
INSERT INTO `assignments` VALUES (22889764,1,0),(35007642,1,2),(47208845,1,1),(60344492,1,5),(47208854,1,6),(46840330,1,3),(65623446,1,4),(58437124,1,7),(47208859,0,1),(48223040,0,2),(47208845,0,3),(65623446,0,0),(47208853,0,4);
UNLOCK TABLES;
/*!40000 ALTER TABLE `assignments` ENABLE KEYS */;

--
-- Table structure for table `players`
--

DROP TABLE IF EXISTS `players`;
CREATE TABLE `players` (
  `Name` varchar(50) NOT NULL default '',
  `ID` int(11) NOT NULL default '0',
  `Age` int(11) NOT NULL default '0',
  `Health` int(11) NOT NULL default '0',
  `Form` int(11) NOT NULL default '0',
  `Stamina` int(11) NOT NULL default '0',
  `Playmaking` int(11) NOT NULL default '0',
  `Scoring` int(11) NOT NULL default '0',
  `Passing` int(11) NOT NULL default '0',
  `Winger` int(11) NOT NULL default '0',
  `SetPieces` int(11) NOT NULL default '0',
  `Defending` int(11) NOT NULL default '0',
  `Keeper` int(11) NOT NULL default '0',
  `Experience` int(11) NOT NULL default '0',
  `Leadership` int(11) NOT NULL default '0',
  `Salary` int(11) NOT NULL default '0',
  `TSI` int(11) NOT NULL default '0',
  PRIMARY KEY  (`ID`)
) TYPE=MyISAM;

--
-- Dumping data for table `players`
--


/*!40000 ALTER TABLE `players` DISABLE KEYS */;
LOCK TABLES `players` WRITE;
INSERT INTO `players` VALUES ('Jim Jones',47208859,24,-1,5,7,4,6,5,4,4,2,1,3,4,5800,760),('Sam  Adams',65772371,18,-1,4,5,5,4,4,5,5,5,1,1,3,6421,590),('Blue Ash',40329460,29,-1,5,4,5,2,5,7,2,2,2,4,4,7440,350),('Davide  Bannor',60344492,19,-1,6,5,8,3,3,4,5,5,1,1,5,7440,1420),('Garrett  Levi',65666140,17,-1,6,4,6,2,3,2,2,4,1,1,3,5000,340),('George  Washington',48223040,20,0,5,7,3,7,2,3,3,3,1,2,1,7440,350),('Grant  Hope',65623446,17,-1,5,5,6,5,4,2,2,5,1,1,5,5481,700),('Guy  Fawkes',70257223,18,-1,7,4,8,3,3,3,3,3,1,1,3,6327,1030),('One-Eyed  Jack',47208845,26,-1,6,6,6,5,4,4,3,7,2,4,4,7600,1460),('Henry  Fonda',70247420,17,-1,8,5,5,2,6,3,4,2,1,1,2,6631,480),('Henry  Aaron',47371060,21,-1,7,5,4,3,2,3,2,6,1,2,3,5400,240),('Jeffrey  Jocks',67694058,19,-1,6,5,6,4,3,7,5,2,1,1,2,6223,770),('Mr  Jones',22889764,29,-1,4,8,7,3,7,5,7,3,1,4,4,7200,1730),('Doc  Holliday',47208848,23,-1,8,7,5,3,5,6,6,3,2,3,6,6400,1170),('Larry  Leisure',47208853,31,2,3,8,5,5,2,4,2,4,2,5,6,6000,120),('Yari  Alvarez',46840330,20,-1,6,8,6,3,3,5,4,3,1,1,4,6960,470),('King  Fischer',70949104,18,0,4,5,4,2,5,3,2,5,1,1,4,5180,210),('Issac  Newton',66096064,18,-1,4,5,4,3,5,6,3,5,1,1,7,6632,450),('Moshe  Dayim',65620883,17,-1,6,3,4,4,6,5,6,3,1,1,2,5292,340),('Ricky  Hartman',36964085,28,-1,5,7,4,4,1,3,6,7,2,5,5,8640,740),('Musharraf  Perales',35007642,23,-1,5,8,6,3,4,5,1,5,1,3,4,6960,730),('Ernest  Gallo',70261067,18,-1,6,3,1,1,1,1,1,1,6,1,4,19917,2590),('George  Telemann',70335750,17,0,6,3,3,2,4,3,2,7,1,1,2,6874,340),('Victor  Petersen',12424803,60,-1,3,2,1,1,1,1,2,1,1,6,5,6000,0),('Wallace  Grommit',47208854,24,-1,5,8,4,3,5,5,1,6,2,3,5,6800,890),('Jim  Xiun',58437124,18,-1,5,7,6,5,3,3,1,3,1,1,3,5400,510);
UNLOCK TABLES;
/*!40000 ALTER TABLE `players` ENABLE KEYS */;

--
-- Table structure for table `positions`
--

DROP TABLE IF EXISTS `positions`;
CREATE TABLE `positions` (
  `positionID` int(11) NOT NULL default '0',
  `positionName` varchar(25) default NULL,
  `buildTablequery` varchar(255) default NULL,
  `fetchTablequery` varchar(255) default NULL,
  PRIMARY KEY  (`positionID`)
) TYPE=MyISAM;

--
-- Dumping data for table `positions`
--


/*!40000 ALTER TABLE `positions` DISABLE KEYS */;
LOCK TABLES `positions` WRITE;
INSERT INTO `positions` VALUES (1,'Midfield','SELECT ID, Name, Playmaking, Age, Passing, Defending, Stamina, Experience FROM players \nORDER BY 2 * Playmaking + 1.5 * Stamina + Passing + Defending DESC, Playmaking DESC Limit 8;',' SELECT pl.Name, pl.Age, pl.Playmaking, pl.Passing, pl.Defending, pl.Stamina, pl.Experience\nFROM players pl, assignments a\nWHERE pl.ID = a.ID and a.positionID=1'),(0,'Forwards','SELECT ID, Name, Age, Scoring, Passing, Stamina, Experience\nFROM players\nORDER BY Scoring*2.5 + Passing + 0.5 * Experience DESC, Scoring\nLIMIT 5;',' SELECT pl.Name, pl.Age, pl.Scoring, pl.Passing, pl.Stamina, pl.Experience\nFROM players pl, assignments a\nWHERE pl.ID = a.ID and a.positionID=0');
UNLOCK TABLES;
/*!40000 ALTER TABLE `positions` ENABLE KEYS */;

--
-- Current Database: mysql
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `mysql`;

USE mysql;

--
-- Table structure for table `columns_priv`
--

DROP TABLE IF EXISTS `columns_priv`;
CREATE TABLE `columns_priv` (
  `Host` char(60) binary NOT NULL default '',
  `Db` char(64) binary NOT NULL default '',
  `User` char(16) binary NOT NULL default '',
  `Table_name` char(64) binary NOT NULL default '',
  `Column_name` char(64) binary NOT NULL default '',
  `Timestamp` timestamp(14) NOT NULL,
  `Column_priv` set('Select','Insert','Update','References') NOT NULL default '',
  PRIMARY KEY  (`Host`,`Db`,`User`,`Table_name`,`Column_name`)
) TYPE=MyISAM COMMENT='Column privileges';

--
-- Dumping data for table `columns_priv`
--


/*!40000 ALTER TABLE `columns_priv` DISABLE KEYS */;
LOCK TABLES `columns_priv` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `columns_priv` ENABLE KEYS */;

--
-- Table structure for table `db`
--

DROP TABLE IF EXISTS `db`;
CREATE TABLE `db` (
  `Host` char(60) binary NOT NULL default '',
  `Db` char(64) binary NOT NULL default '',
  `User` char(16) binary NOT NULL default '',
  `Select_priv` enum('N','Y') NOT NULL default 'N',
  `Insert_priv` enum('N','Y') NOT NULL default 'N',
  `Update_priv` enum('N','Y') NOT NULL default 'N',
  `Delete_priv` enum('N','Y') NOT NULL default 'N',
  `Create_priv` enum('N','Y') NOT NULL default 'N',
  `Drop_priv` enum('N','Y') NOT NULL default 'N',
  `Grant_priv` enum('N','Y') NOT NULL default 'N',
  `References_priv` enum('N','Y') NOT NULL default 'N',
  `Index_priv` enum('N','Y') NOT NULL default 'N',
  `Alter_priv` enum('N','Y') NOT NULL default 'N',
  `Create_tmp_table_priv` enum('N','Y') NOT NULL default 'N',
  `Lock_tables_priv` enum('N','Y') NOT NULL default 'N',
  PRIMARY KEY  (`Host`,`Db`,`User`),
  KEY `User` (`User`)
) TYPE=MyISAM COMMENT='Database privileges';

--
-- Dumping data for table `db`
--


/*!40000 ALTER TABLE `db` DISABLE KEYS */;
LOCK TABLES `db` WRITE;
INSERT INTO `db` VALUES (0x25,0x74657374,'','Y','Y','Y','Y','Y','Y','N','Y','Y','Y','Y','Y'),(0x25,0x746573745C5F25,'','Y','Y','Y','Y','Y','Y','N','Y','Y','Y','Y','Y'),(0x6C6F63616C686F7374,0x686174747269636B,0x686174747269636B,'Y','Y','Y','Y','Y','Y','N','Y','Y','Y','Y','Y');
UNLOCK TABLES;
/*!40000 ALTER TABLE `db` ENABLE KEYS */;

--
-- Table structure for table `func`
--

DROP TABLE IF EXISTS `func`;
CREATE TABLE `func` (
  `name` char(64) binary NOT NULL default '',
  `ret` tinyint(1) NOT NULL default '0',
  `dl` char(128) NOT NULL default '',
  `type` enum('function','aggregate') NOT NULL default 'function',
  PRIMARY KEY  (`name`)
) TYPE=MyISAM COMMENT='User defined functions';

--
-- Dumping data for table `func`
--


/*!40000 ALTER TABLE `func` DISABLE KEYS */;
LOCK TABLES `func` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `func` ENABLE KEYS */;

--
-- Table structure for table `host`
--

DROP TABLE IF EXISTS `host`;
CREATE TABLE `host` (
  `Host` char(60) binary NOT NULL default '',
  `Db` char(64) binary NOT NULL default '',
  `Select_priv` enum('N','Y') NOT NULL default 'N',
  `Insert_priv` enum('N','Y') NOT NULL default 'N',
  `Update_priv` enum('N','Y') NOT NULL default 'N',
  `Delete_priv` enum('N','Y') NOT NULL default 'N',
  `Create_priv` enum('N','Y') NOT NULL default 'N',
  `Drop_priv` enum('N','Y') NOT NULL default 'N',
  `Grant_priv` enum('N','Y') NOT NULL default 'N',
  `References_priv` enum('N','Y') NOT NULL default 'N',
  `Index_priv` enum('N','Y') NOT NULL default 'N',
  `Alter_priv` enum('N','Y') NOT NULL default 'N',
  `Create_tmp_table_priv` enum('N','Y') NOT NULL default 'N',
  `Lock_tables_priv` enum('N','Y') NOT NULL default 'N',
  PRIMARY KEY  (`Host`,`Db`)
) TYPE=MyISAM COMMENT='Host privileges;  Merged with database privileges';

--
-- Dumping data for table `host`
--


/*!40000 ALTER TABLE `host` DISABLE KEYS */;
LOCK TABLES `host` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `host` ENABLE KEYS */;

--
-- Table structure for table `tables_priv`
--

DROP TABLE IF EXISTS `tables_priv`;
CREATE TABLE `tables_priv` (
  `Host` char(60) binary NOT NULL default '',
  `Db` char(64) binary NOT NULL default '',
  `User` char(16) binary NOT NULL default '',
  `Table_name` char(64) binary NOT NULL default '',
  `Grantor` char(77) NOT NULL default '',
  `Timestamp` timestamp(14) NOT NULL,
  `Table_priv` set('Select','Insert','Update','Delete','Create','Drop','Grant','References','Index','Alter') NOT NULL default '',
  `Column_priv` set('Select','Insert','Update','References') NOT NULL default '',
  PRIMARY KEY  (`Host`,`Db`,`User`,`Table_name`),
  KEY `Grantor` (`Grantor`)
) TYPE=MyISAM COMMENT='Table privileges';

--
-- Dumping data for table `tables_priv`
--


/*!40000 ALTER TABLE `tables_priv` DISABLE KEYS */;
LOCK TABLES `tables_priv` WRITE;
UNLOCK TABLES;
/*!40000 ALTER TABLE `tables_priv` ENABLE KEYS */;

--
-- Table structure for table `user`
--

DROP TABLE IF EXISTS `user`;
CREATE TABLE `user` (
  `Host` varchar(60) binary NOT NULL default '',
  `User` varchar(16) binary NOT NULL default '',
  `Password` varchar(16) binary NOT NULL default '',
  `Select_priv` enum('N','Y') NOT NULL default 'N',
  `Insert_priv` enum('N','Y') NOT NULL default 'N',
  `Update_priv` enum('N','Y') NOT NULL default 'N',
  `Delete_priv` enum('N','Y') NOT NULL default 'N',
  `Create_priv` enum('N','Y') NOT NULL default 'N',
  `Drop_priv` enum('N','Y') NOT NULL default 'N',
  `Reload_priv` enum('N','Y') NOT NULL default 'N',
  `Shutdown_priv` enum('N','Y') NOT NULL default 'N',
  `Process_priv` enum('N','Y') NOT NULL default 'N',
  `File_priv` enum('N','Y') NOT NULL default 'N',
  `Grant_priv` enum('N','Y') NOT NULL default 'N',
  `References_priv` enum('N','Y') NOT NULL default 'N',
  `Index_priv` enum('N','Y') NOT NULL default 'N',
  `Alter_priv` enum('N','Y') NOT NULL default 'N',
  `Show_db_priv` enum('N','Y') NOT NULL default 'N',
  `Super_priv` enum('N','Y') NOT NULL default 'N',
  `Create_tmp_table_priv` enum('N','Y') NOT NULL default 'N',
  `Lock_tables_priv` enum('N','Y') NOT NULL default 'N',
  `Execute_priv` enum('N','Y') NOT NULL default 'N',
  `Repl_slave_priv` enum('N','Y') NOT NULL default 'N',
  `Repl_client_priv` enum('N','Y') NOT NULL default 'N',
  `ssl_type` enum('','ANY','X509','SPECIFIED') NOT NULL default '',
  `ssl_cipher` blob NOT NULL,
  `x509_issuer` blob NOT NULL,
  `x509_subject` blob NOT NULL,
  `max_questions` int(11) unsigned NOT NULL default '0',
  `max_updates` int(11) unsigned NOT NULL default '0',
  `max_connections` int(11) unsigned NOT NULL default '0',
  PRIMARY KEY  (`Host`,`User`)
) TYPE=MyISAM COMMENT='Users and global privileges';

--
-- Dumping data for table `user`
--


/*!40000 ALTER TABLE `user` DISABLE KEYS */;
LOCK TABLES `user` WRITE;
INSERT INTO `user` VALUES (0x6C6F63616C686F7374,0x726F6F74,0x37396234656539333539303136303536,'Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','','','','',0,0,0),(0x686F7564696E69,0x726F6F74,0x37396234656539333539303136303536,'Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','Y','','','','',0,0,0),(0x6C6F63616C686F7374,0x686174747269636B,'','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','N','','','','',0,0,0);
UNLOCK TABLES;
/*!40000 ALTER TABLE `user` ENABLE KEYS */;

--
-- Current Database: test
--

CREATE DATABASE /*!32312 IF NOT EXISTS*/ `test`;

USE test;

--
-- Table structure for table `simpletable`
--

DROP TABLE IF EXISTS `simpletable`;
CREATE TABLE `simpletable` (
  `id` int(11) NOT NULL default '0',
  `name` varchar(20) default NULL,
  `address` varchar(20) default NULL,
  PRIMARY KEY  (`id`)
) TYPE=MyISAM;

--
-- Dumping data for table `simpletable`
--


/*!40000 ALTER TABLE `simpletable` DISABLE KEYS */;
LOCK TABLES `simpletable` WRITE;
INSERT INTO `simpletable` VALUES (1,'trond','oslo'),(2,'dave','oslo');
UNLOCK TABLES;
/*!40000 ALTER TABLE `simpletable` ENABLE KEYS */;

