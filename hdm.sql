-- MySQL dump 10.10
--
-- Host: localhost    Database: hattrick
-- ------------------------------------------------------
-- Server version	5.0.22-log

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `PlayerTMP`
--

DROP TABLE IF EXISTS `PlayerTMP`;
CREATE TABLE `PlayerTMP` (
  `Name` char(50) NOT NULL,
  `ID` bigint(20) NOT NULL,
  `Age` int(11) NOT NULL default '0',
  `Health` bigint(20) NOT NULL,
  `Form` bigint(20) NOT NULL,
  `Stamina` bigint(20) NOT NULL,
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Table structure for table `assignments`
--

DROP TABLE IF EXISTS `assignments`;
CREATE TABLE `assignments` (
  `ID` int(11) NOT NULL default '0',
  `positionID` int(11) NOT NULL default '0',
  `depth` int(11) NOT NULL default '0'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Table structure for table `players`
--

DROP TABLE IF EXISTS `players`;
CREATE TABLE `players` (
  `Name` char(50) NOT NULL,
  `ID` bigint(20) NOT NULL,
  `Age` int(11) NOT NULL default '0',
  `Health` bigint(20) NOT NULL,
  `Form` bigint(20) NOT NULL,
  `Stamina` bigint(20) NOT NULL,
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
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Table structure for table `position_order`
--

DROP TABLE IF EXISTS `position_order`;
CREATE TABLE `position_order` (
  `positionID` int(11) default NULL,
  `Age` int(11) NOT NULL default '-1',
  `Health` int(11) NOT NULL default '-1',
  `Form` int(11) NOT NULL default '-1',
  `Stamina` int(11) NOT NULL default '-1',
  `Playmaking` int(11) NOT NULL default '-1',
  `Scoring` int(11) NOT NULL default '-1',
  `Passing` int(11) NOT NULL default '-1',
  `Winger` int(11) NOT NULL default '-1',
  `SetPieces` int(11) NOT NULL default '-1',
  `Defending` int(11) NOT NULL default '-1',
  `Keeper` int(11) NOT NULL default '-1',
  `Experience` int(11) NOT NULL default '-1',
  `Leadership` int(11) NOT NULL default '-1',
  `Salary` int(11) NOT NULL default '-1',
  `TSI` int(11) NOT NULL default '-1'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Table structure for table `position_weight`
--

DROP TABLE IF EXISTS `position_weight`;
CREATE TABLE `position_weight` (
  `positionID` int(11) default NULL,
  `Age` double(3,2) NOT NULL default '0.00',
  `Health` double(3,2) NOT NULL default '0.00',
  `Form` double(3,2) NOT NULL default '1.00',
  `Stamina` double(3,2) NOT NULL default '1.00',
  `Playmaking` double(3,2) NOT NULL default '1.00',
  `Scoring` double(3,2) NOT NULL default '1.00',
  `Passing` double(3,2) NOT NULL default '1.00',
  `Winger` double(3,2) NOT NULL default '1.00',
  `SetPieces` double(3,2) NOT NULL default '1.00',
  `Defending` double(3,2) NOT NULL default '1.00',
  `Keeper` double(3,2) NOT NULL default '1.00',
  `Experience` double(3,2) NOT NULL default '1.00',
  `Leadership` double(3,2) NOT NULL default '1.00',
  `Salary` double(3,2) NOT NULL default '0.00',
  `TSI` double(3,2) NOT NULL default '0.00',
  `Lim` int(11) NOT NULL default '10'
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Table structure for table `positions`
--

DROP TABLE IF EXISTS `positions`;
CREATE TABLE `positions` (
  `positionID` int(11) NOT NULL auto_increment,
  `positionName` varchar(25) default NULL,
  PRIMARY KEY  (`positionID`)
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Table structure for table `summary`
--

DROP TABLE IF EXISTS `summary`;
CREATE TABLE `summary` (
  `Name` varchar(100) default NULL,
  `position1` varchar(50) default NULL,
  `position2` varchar(50) default NULL,
  `position3` varchar(50) default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;

--
-- Table structure for table `tmp`
--

DROP TABLE IF EXISTS `tmp`;
CREATE TABLE `tmp` (
  `Name` varchar(11) default NULL,
  `fieldOrder` smallint(3) default NULL,
  `Weight` float(2,3) unsigned default NULL
) ENGINE=MyISAM DEFAULT CHARSET=latin1;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

