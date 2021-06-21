# Library-Mangement-System
Engineering SDP(Software Development Project). Library Management is a C++ Command Line Project.
/**********************************************************************************************/

 Requirement:
 1.CodeBlocks or any IDE
 2.Xamp
 3.Mysql.zip (File has been Provided)
 
 Exract Mysql.zip. ()
 
 1.Open libmysql.a folder >> Copy that File >> Paste it to C:\Program Files\CodeBlocks\MinGW\lib 
 
 2.Open Mysqlheaders >> Copy all the files inside that folder >> Paste it to C:\Program Files\CodeBlocks\MinGW\include
 
 3. Open CodeBLocks >> Create new Project>> Click Console application >> Select Proper directory for your project (New Project has been Created) 
     >> Now Click on Project tab in CodeBlocks >> select Build option >> Goto Linker Setting>> Click on add 
     >> Add libmysql.a file from your PC located at C:\Program Files\CodeBlocks\MinGW\lib\libmysql.a >>Select yes >> Select Ok 
     >>Now Goto search directory (Besides Linker setting) >> Select Inculde folder from your PC C:\Program Files\CodeBlocks\MinGW\include>> Click on yes

4.Open libmysql (Provided in zip file) >> Copy libmysql.dll file>> Paste it to Project Directory\bin\Debug (Project Directory is the directory where you just created your project)     
     
5.Start Xamp Server >> Start Apache and Mysql.

6.Copy code from main.cpp or code.txt file (Both files are provided).

Database Part:

/***Demo1.sql file is your databse file (Already Provided).**/

7.Start Xamp Server >> Start Apache and Mysql.
8. Open Browser >> Search Localhost>> Open PHPMyadmin >> Create new Database name 'demo1' >> Click on Import>> Click on Choose File>> Open Demo1.sql file.

9.Your Database has succefully created now Run Your c++ File.

