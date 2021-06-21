-- phpMyAdmin SQL Dump
-- version 5.0.2
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 21, 2021 at 11:50 AM
-- Server version: 10.4.14-MariaDB
-- PHP Version: 7.4.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `demo1`
--

-- --------------------------------------------------------

--
-- Table structure for table `book1`
--

CREATE TABLE `book1` (
  `Book_Name` varchar(100) NOT NULL,
  `Book_ID` int(11) NOT NULL,
  `Book_Author` varchar(100) NOT NULL,
  `Book_Quantity` int(100) NOT NULL,
  `Quantity` int(100) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `book1`
--

INSERT INTO `book1` (`Book_Name`, `Book_ID`, `Book_Author`, `Book_Quantity`, `Quantity`) VALUES
('java', 123, 'oracle', 3, 4),
('C', 234, 'kanetkar', 6, 7),
('harry potter', 456, 'jkrowling', 3, 3),
('Rich Dad Poor Dad', 852, 'Robert Kiyosaki', 5, 5),
('c++', 2345, 'kanetkar', 4, 5);

-- --------------------------------------------------------

--
-- Table structure for table `book_issue1`
--

CREATE TABLE `book_issue1` (
  `SrNo` int(11) NOT NULL,
  `Book_Name` varchar(100) DEFAULT NULL,
  `book_id` int(11) DEFAULT NULL,
  `Student_Name` varchar(100) DEFAULT NULL,
  `Stud_ID` int(11) DEFAULT NULL,
  `issue_time` date DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `book_issue1`
--

INSERT INTO `book_issue1` (`SrNo`, `Book_Name`, `book_id`, `Student_Name`, `Stud_ID`, `issue_time`) VALUES
(1, 'c++', 2345, 'Shubhayu', 12020103, '2021-05-20'),
(2, 'c', 234, 'shubhayu', 12020103, '2021-04-25'),
(3, 'java', 123, 'shubhayu', 12020103, '2021-05-21');

-- --------------------------------------------------------

--
-- Table structure for table `membership`
--

CREATE TABLE `membership` (
  `name` varchar(100) NOT NULL,
  `ID` varchar(100) NOT NULL,
  `phone_number` bigint(12) UNSIGNED NOT NULL,
  `Password` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `membership`
--

INSERT INTO `membership` (`name`, `ID`, `phone_number`, `Password`) VALUES
('Example', '12020100', 7897897899, 'example123');

-- --------------------------------------------------------

--
-- Table structure for table `verify_admin`
--

CREATE TABLE `verify_admin` (
  `Sr.No.` int(11) NOT NULL,
  `Admin_Name` varchar(100) NOT NULL,
  `Admin_Password` varchar(100) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `verify_admin`
--

INSERT INTO `verify_admin` (`Sr.No.`, `Admin_Name`, `Admin_Password`) VALUES
(1, 'admin', 'admin');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `book1`
--
ALTER TABLE `book1`
  ADD PRIMARY KEY (`Book_ID`);

--
-- Indexes for table `book_issue1`
--
ALTER TABLE `book_issue1`
  ADD PRIMARY KEY (`SrNo`);

--
-- Indexes for table `membership`
--
ALTER TABLE `membership`
  ADD PRIMARY KEY (`ID`),
  ADD UNIQUE KEY `phone_number` (`phone_number`);

--
-- Indexes for table `verify_admin`
--
ALTER TABLE `verify_admin`
  ADD PRIMARY KEY (`Sr.No.`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `verify_admin`
--
ALTER TABLE `verify_admin`
  MODIFY `Sr.No.` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=3;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
