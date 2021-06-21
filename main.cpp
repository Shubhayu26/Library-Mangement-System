#include<windows.h>
#include<iostream>//getline method
#include<mysql.h>
#include<sstream>
#include<string>
#include<conio.h>//for _getch()at password
#include<ctime>//for date
#include<regex>
#include<limits>//for validations
using namespace std;

class Database
{
public:
MYSQL* conn;
int verify=0;
//*****************Connection*********************
void Connect()
{
        conn = mysql_init(0);
        conn = mysql_real_connect(conn, "localhost", "admin", "admin", "demo1", 0, NULL, 0);
        if(conn)
            {
                //cout<<"connected to database"<<endl;
            }
        else
            {
                cout<<"not connected";

            }
}
//*************Display whole book table*************/
void getBookTable()
{
      Connect();
        int qstate=0;
        stringstream ss;
        MYSQL_ROW row;
        MYSQL_RES* res;

        ss<< "SELECT * FROM Book1 ";
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                res=mysql_store_result(conn);

            while(row = mysql_fetch_row(res))
                    {
                       cout<<endl;
                       cout<<"Book Name     : "<<row[0]<<"\nBook ID       : "<<row[1]<<"\nBook Author   : "<<row[2]<<"\nBook Quantity : "<<row[3];
                       cout<<endl;
                    }
            }

            else{
                cout<<mysql_error(conn);
                }
}
//***************INSERT query*******************

//***********Insert members data in Table Membership********
void InsertMember(string sname,int stud_id,unsigned long long  int pno,string pass)
{
    Connect(); //creating connection with database
    stringstream ss;
    int qstate=0;
    unsigned long long  int phone = pno;
    string pswd = pass;

        ss << "INSERT INTO membership(name,ID,phone_number,Password)  VALUES('" << sname <<"', '"<<stud_id<<"','" << phone <<"', '" << pswd <<"')";

        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
        {
         cout<<"record inserted"<<endl;
        }
        else{
            cout<<mysql_error(conn);
            cout<<"\nID or Phone Number Already Exist.\n Failed to Insert Data"<<endl;
            }
}
//*******************Insert Book Data***********************************************

void Insert_book_data(string book_name,int book_id, string book_author,int book_quant)
{
    string b_name = book_name;
    int b_quant=book_quant;
    int b_id=book_id;
    string b_author=book_author;
    int qstate=0;
    Connect();
    stringstream ss;

        ss << "INSERT INTO book1 (Book_Name,Book_ID,Book_Author,Book_Quantity,Quantity)  VALUES('" << b_name<<"', '" << b_id <<"', '" << b_author <<"', '" << b_quant<<"', '" << b_quant <<"')";

        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                cout<<"record inserted"<<endl;
            }
        else{
                 cout<<mysql_error(conn);
                cout<<"Failed to insert data. Book of id "<<b_id<<" already exsists";
        }

}
int Select_book_Quantity(int b_issue_id )
{
        Connect();
        int qstate=0;
        stringstream ss;
        MYSQL_ROW row;
        MYSQL_RES* res;
        int book_quantity;
        ss<< "SELECT Book_Quantity FROM Book1 WHERE Book_ID = '"<<b_issue_id<<"' ";
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                res=mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                    {
                        book_quantity = stoi(row[0]);
                    }
            }
            else{
                cout<<mysql_error(conn);
                }
return book_quantity;

}

//********************Update Query******************************

void Update_Book_on_issue(int b_issue_id,string b_issue)
{
    int b=Select_book_Quantity(b_issue_id);
    Connect();
        int qstate=0;
        stringstream ss;
        b=b-1;
        ss<< "UPDATE book1 SET Book_Quantity = '"<<b<<"' WHERE Book_Name = '"<<b_issue<<"' ";
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                cout<<"record updated"<<endl;
            }
        else{
                 cout<<mysql_error(conn);
           }
}
//*******************Delete Query******************************************
void Delete_book_data(string book_name_del)
{
        Connect();
        int qstate=0;
        stringstream ss;
        string bname=book_name_del;

        ss<< "DELETE FROM book1 WHERE Book_Name = '"<<bname<<"' ";
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                cout<<"record Deleted"<<endl;
            }
        else{
                 cout<<mysql_error(conn);
        }
}
void Delete_issue_book_data(string return_book_name,int return_book_ID,string s_name,int s_id)
{
        Connect();
        int qstate=0;
        stringstream ss;
        cout<<return_book_name;
        ss<< "DELETE FROM book_issue1 WHERE Book_Name = '"<<return_book_name <<"'  AND Stud_ID='"<<s_id <<"' " ;
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                cout<<"record Deleted"<<endl;

            }
        else{
                 cout<<mysql_error(conn);
        }
}
//******************SELECT query*******************

//*******************************************************
  int checknumberofissuedbooks(int s_id,int issue_book_ID)
  {
        int counter=0;
       Connect();
        int qstate=0;
        stringstream ss;
        MYSQL_ROW row;
        MYSQL_RES* res;
        ss<< "SELECT Book_Name FROM book_issue1 WHERE Stud_ID = '"<<s_id<<"'  ";
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
            res=mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                    {
                    counter++;
                    }
            }

            else{
                     cout<<mysql_error(conn);
                }
return counter;
  }
string Selectforpassword(int s_id)
{

  string getpassfrom_db;
  //int student_choice;
    Connect();
        int qstate=0;
        stringstream ss;
        MYSQL_ROW row;
        MYSQL_RES* res;


        ss<< "SELECT Password FROM membership WHERE ID = '"<<s_id<<"' ";
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                res=mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                    {
                        getpassfrom_db=row[0];
                    }
            }

            else{
                     cout<<mysql_error(conn);
                }
return getpassfrom_db;

}

string Selectforname(int s_id)
{
  string getnamefrom_db;
    Connect();
        int qstate=0;
        stringstream ss;
        MYSQL_ROW row;
        MYSQL_RES* res;
        ss<< "SELECT name FROM membership WHERE ID = '"<<s_id<<"' ";
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                res=mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                    {
                        getnamefrom_db=row[0];
                    }
            }
        else{
            cout<<mysql_error(conn);
            }
return getnamefrom_db;
}

/*************************************/
 int check_book_quantity_to_delete(string book_name_del,int book_id_del)
 {
     int flag=0;
        Connect();
        int qstate=0;
        stringstream ss;
        MYSQL_ROW row;
        MYSQL_RES* res;
        ss<< "SELECT Book_Quantity, Quantity FROM book1 WHERE Book_Name = '"<<book_name_del<<"' AND Book_ID ='"<<book_id_del<<"'";
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                res=mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                    {
                        flag=1;
                       int q1=stoi(row[0]);
                       int q2=stoi(row[1]);
                       if(q1==q2)
                       {
                           return 10;
                       }
                       else{
                        return 0;
                       }
                    }
            }
            else{
                cout<<mysql_error(conn);
                }
        if(flag==0)
        {
        cout<<"Invalid Book name or ID";
        }
 }
//***********************************************************************
 int checkifissue(string return_book_name,int return_book_ID,int s_id)
 {
     int flag=0;
     Connect();
        int qstate=0;
        stringstream ss;
        MYSQL_ROW row;
        MYSQL_RES* res;
        ss<< "SELECT * FROM book_issue1 WHERE book_id = '"<<return_book_ID<<"' AND Book_Name ='"<<return_book_name<<"' AND Stud_ID ='"<<s_id<<"' ";
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                res=mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                    {
                        flag=1;
                    }
            }
            else{
                cout<<mysql_error(conn);
                }
if(flag==0)
{
return 1;
}
else{
    return 10;
}

 }
//************** search_book_in_DB************//
 void search_book_in_DB()
 {
     system("cls");
     string search_book_name;
     cout<<"Enter Book Name that you Want to search"<<endl;
     cin.ignore();
    getline(cin,search_book_name);
     int search_book_id;
      while(1)
     {
        cout<<"\nEnter Book ID \n";
        cin>>search_book_id;
       if(cin.fail())
        {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(),'\n');
         cout<<"Id Should be number only\n"<<endl;
        cout<<"Enter Book ID \n";
        cin>>search_book_id;
        }
        if(!cin.fail())
        {
         break;
        }
    }
     int flag=0;
     Connect();
        int qstate=0;
        stringstream ss;
        MYSQL_ROW row;
        MYSQL_RES* res;
        ss<< "SELECT * FROM book1 WHERE Book_Name = '"<<search_book_name<<"' AND Book_ID ='"<<search_book_id<<"' ";
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                res=mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                    {
                        cout<<endl<<"Book Name     : "<<row[0]<<"\nBook ID       : "<<row[1]<<"\nBook Author   : "<<row[2]<<"\nBook Quantity : "<<row[3]<<endl;
                        flag=1;
                    }
            }
            else{
                cout<<mysql_error(conn);
                }
if(flag==0)
{
    cout<<"No Such Book is avaiable in library";
}

 }

 void book_validate(string b_issue,int b_issue_id)//check whether that particular book is present in library book DB
 {
     Connect();
        int qstate=0;
        stringstream ss;
        MYSQL_ROW row;
        MYSQL_RES* res;
        //int store_book_id;
       ss<<"SELECT Book_Name,Book_ID FROM book1 WHERE Book_Name='"<<b_issue<<"' AND Book_ID='"<<b_issue_id<<"' ";
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                res=mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                    {
                       // store_book_id = stoi(row[1]);
                         verify=1;
                    }
            }
        else
        {
             cout<<mysql_error(conn);
        }

 }

 void Issue_Book(string issue_book_name,string student_name,int s_id,int issue_book_id)
 {
   string b_issue=issue_book_name;
   string s_issue=student_name;
   int b_issue_id= issue_book_id;
   string store_name,store_book;
   int store_book_id;
   int flag=0;
   //int arr[5];
   //bool a=true;
   book_validate(b_issue,b_issue_id);
 if(verify==1)
 {
     verify=0;
    int qstate=0;
    MYSQL_ROW row;
    MYSQL_RES* res;
    stringstream ss;
    Connect();

        ss<< "SELECT Book_Name,book_id FROM book_issue1 WHERE Stud_ID = '"<<s_id<<"' AND book_id = '"<<b_issue_id<<"' ";

        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                res=mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                    {
                        store_book_id = stoi(row[1]);
                        if(store_book_id == b_issue_id)
                        {
                            cout<<" You Have Already Issued The Book";
                        }
                        flag=1;
                    }
            }
        else
        {
             cout<<mysql_error(conn);
        }

       if(flag==0)
        {
            insert_issue_book1(b_issue,s_issue,s_id,b_issue_id);
        }

  }
  else
    {
        cout<<"\n No Such Book avaiable in library\n";
    }

 }
 void insert_issue_book1(string b_issue,string s_issue,int s_id,int b_issue_id)
 {
     string date=get_date();
     int returnday=get_curr_day()+14;
     int returnmon=get_curr_month();
     int returnyear=get_curr_year();
if(returnmon==4||returnmon==6||returnmon==9||returnmon==11)
{
    if(returnday>31)
    {
        returnday=returnday-30;
        returnmon = returnmon+1;

    }
}
if(returnmon==1||returnmon==3||returnmon==5||returnmon==7||returnmon==8||returnmon==10||returnmon==12)
{
    if(returnday>32)
    {
        if(returnday>32 && returnmon==12)
        {
            returnday=returnday-31;
             returnmon=1;
            returnyear++;

        }
        else
        {
          returnday=returnday-31;
            returnmon = returnmon+1;
        }
    }
}
if(returnmon==2)
{
    if(returnday>30)
    {
        returnday=returnday-29;
        returnmon = returnmon+1;
    }
}

    Connect();
    stringstream ss;
    int qstate=0;
    string b_issue1=b_issue;
    string s_issue1=s_issue;
    int b_issue_id1=b_issue_id;

        ss << "INSERT INTO book_issue1 (Book_Name,book_id,Student_Name,Stud_ID,issue_time)  VALUES('" << b_issue1<<"','" <<b_issue_id1 <<"', '" << s_issue1 <<"','" << s_id <<"','" <<date <<"')";

        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                cout<<"Book Issued"<<endl;
                cout<<"your Return Date is: "<<returnday<<"-"<<returnmon<<"-"<<returnyear;
              Update_Book_on_issue(b_issue_id,b_issue);
            }
        else{
                 cout<<mysql_error(conn);
        }


 }

void Return_book(string return_book_name,int return_book_ID,string s_name,int s_id)
{
   int checkfine = fine( return_book_name,return_book_ID, s_name, s_id);

   if(checkfine == 10)
   {
     // cout<<endl<<"Admin will update ";
   }
   else{
      cout<<endl<<"call Delete Function";


    Delete_issue_book_data(return_book_name,return_book_ID,s_name,s_id);
    int book_quantity=Select_book_Quantity(return_book_ID);
    Connect();
        int qstate=0;
        stringstream ss;
        book_quantity=book_quantity+1;
        ss<< "UPDATE book1 SET Book_Quantity = '"<<book_quantity<<"' WHERE Book_Name = '"<<return_book_name<<"' ";
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                cout<<"record updated"<<endl;
            }
        else{
                cout<<mysql_error(conn);
                cout<<"Failed to delete496 "<<endl;
           }
       }

}

string get_date()
{
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int day=ltm->tm_mday;
    int month= 1 + ltm->tm_mon;
    int year=1900 + ltm->tm_year;
    string dash ="-";
    string day1= to_string(day);
    string month1= to_string(month);
    string year1= to_string(year);
    string date1=year1+dash+month1+dash+day1;
    return date1;
}


int fine(string return_book_name,int return_book_ID,string s_name,int s_id)
{
  // string current_date=get_date();
   //cout<<"current date: "<<current_date;
 //string current_date="2021-05-29";
        string issue_date;
        Connect();
        int qstate=0;
        stringstream ss;
        MYSQL_ROW row;
        MYSQL_RES* res;
        ss<< "SELECT issue_time FROM book_issue1 WHERE book_id = '"<<return_book_ID<<"'  AND Stud_id= '"<<s_id<<"' ";
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                res=mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                    {
                        issue_date=row[0];
                        cout<<"issue date: "<<issue_date<<endl;
                    }
            }

            else{
                     cout<<mysql_error(conn);
                cout<<"else part 550";
            }
       // int current_day   =  16;
        //int current_month =  1;
        //int current_year  =  2022;
       // int issue_day   =  25;
        //int issue_month = 5;
        //int issue_year  = 2021;
        int current_day   =  get_curr_day();
        int current_month  =  get_curr_month();
        int current_year  =  get_curr_year();

       //cout<<"current day: "<<current_day<<endl;
       // cout<<"current month: "<<current_month<<endl;
       // cout<<"current year: "<<current_year<<endl;

        int issue_day   =  get_day1(issue_date);
        int issue_month =  get_month(issue_date);
        int issue_year  =  get_year(issue_date);

       // cout<<"issue day: "<<issue_day<<endl;
        //cout<<"issue month: "<<issue_month<<endl;
       // cout<<"issue year: "<<issue_year<<endl;


    int rd = issue_day +14;
    int rm =issue_month;
    int ry =issue_year;
    int count_days=0;
    int tdays=0;
    int finecal=0;

if(rm==4||rm==6||rm==9||rm==11)
{
    if(rd>31)
    {
        rd=rd-30;
        rm = issue_month+1;
    }
}
if(rm==1||rm==3||rm==5||rm==7||rm==8||rm==10||rm==12)
{
    if(rd>32)
    {
        if(rd>32 && rm==12)
        {
            rd=rd-31;
             rm=1;
            ry++;
        }
        else
        {
          rd=rd-31;
            rm = issue_month+1;
        }
    }
}
if(rm==2)
{
    if(rd>30)
    {
        rd=rd-29;
        rm = issue_month+1;
    }
}
    //  cout<<"return day: "<<rd<<endl;
   // cout<<"return month: "<<rm<<endl;
   // cout<<"return year: "<<ry<<endl;

  if (current_year == issue_year)
    {
        if (current_month >= issue_month)
        {
            if (current_day >= issue_day && current_month==issue_month)
            {
                while(issue_day!=current_day)
                {

                    tdays=tdays+1;
                    issue_day++;

                }
                if(tdays<15)
                {
                    cout << endl << "NO Fine";
                    return 0;

                }
                else
                {
                    //cout<<"fine";
                    finecal=(tdays-15)*10;
                    if(finecal>100)
                    {
                        cout<<"Pay fine of 100";
                    }
                    else{
                        cout<<"pay fine of ruppees "<<finecal;
                    }
                    return 10;

                }return 0;
            }
            else
            {

                count_days = issue_day;


                    while (issue_month != current_month ||  count_days != current_day)
                        {
                        count_days++;
                        tdays++;
                        if (count_days > 30)
                        {
                            count_days = 0;
                            issue_month++;
                        }

                        if (issue_month == 1 || issue_month == 3 ||issue_month == 5 || issue_month == 7 ||issue_month == 8 || issue_month == 10 ||issue_month == 12)
                        {
                            if (count_days > 31)
                            {
                                count_days = 0;
                                issue_month++;
                                if (issue_month > 12) {
                                    issue_month = 1;
                                    issue_year = issue_year + 1;
                                }
                            }
                        }
                        if (issue_month == 2)
                        {
                            if (count_days > 28)
                            {
                                count_days = 0;
                                issue_month++;
                            }
                        }
                    }
                if(tdays<15)
                {
                cout << endl << "NO Fine";
                return 0;
                }
                else
                {   //cout<<"fine";
                    finecal=(tdays-15)*10;
                    if(finecal>100)
                    {
                        cout<<"Pay fine of 100";
                    }
                     else{
                        cout<<"pay fine of ruppees "<<finecal;
                    }
                    return 10;
                }
            }
        }
        }
        else{

            while(issue_year!=current_year || issue_month!=current_month ||issue_day!=current_day)
            {
            tdays++;
            issue_day++;
            if(issue_month==1||issue_month==3||issue_month==5||issue_month==7||issue_month==8||issue_month==10||issue_month==12)
            {
                if(issue_day>31)
                    {
                        issue_month++;
                        issue_day=0;
                    }
                    if(issue_month>12)
                    {
                        issue_year++;
                        issue_month=1;
                    }
             }
             if(issue_month==4||issue_month==6||issue_month==9||issue_month==11)
             {
                  if(issue_day>30)
                    {
                        issue_month++;
                        issue_day=0;
                    }
             }
            if(issue_month==2)
             {
                  if(issue_day>28)
                    {
                        issue_month++;
                        issue_day=0;
                    }
             }

            }

            if(tdays>15)
            {
               // cout<<"Fine";
                finecal=(tdays-15)*10;
              if(finecal>100)
              {
                cout<<"Pay fine of 100";
              }
              else{
                    cout<<"pay fine of ruppees "<<finecal;
                }
                return 10;
            }
            else{
                cout<<"No Fine";
                return 0;
            }
        }
}


int get_curr_day()
{
  time_t now = time(0);
  tm *ltm = localtime(&now);
  int day = ltm->tm_mday;
   return day;
}
int get_curr_month()
{
  time_t now = time(0);
  tm *ltm = localtime(&now);
  int month = 1 + ltm->tm_mon;
  return month;
}
int get_curr_year()
{
  time_t now = time(0);
  tm *ltm = localtime(&now);
  int year= 1900 + ltm->tm_year;
   return year;
}
int get_day1(string date)
{
     string s1 =date;
     string s2 = s1.substr(8, 9);
    int daay = stoi(s2);
    return daay;
}
int get_year(string date)
{
    string s1 =date;
    string s2 = s1.substr(0, 4);
    int year = stoi(s2);
    return year;
}
int get_month(string date)
{
    string s1 =date;
    string s2 = s1.substr(5, 2);
    int month = stoi(s2);
    return month;
}
int checkforvalidinputstring(string str)
{    int flag=0;
     int len= str.length();

    for(int i=0;i<len;i++)
    {
        if(str[i]=='0'||str[i]=='1'||str[i]=='2'||str[i]=='3'||str[i]=='4'||str[i]=='5'||str[i]=='6'||str[i]=='7'||str[i]=='8'||str[i]=='9'||str[i]=='!'||str[i]=='@'||str[i]=='#'||str[i]=='$'||str[i]=='%'||str[i]=='^'||str[i]=='&'||str[i]=='*'||str[i]=='('||str[i]==')'||str[i]=='?')
        {
            flag=1;
            break;
        }
    }
    if(flag==1)
    {
        return 1;
    }
    else{
        return 0;
    }
}
/*******************************************************************************/

int validatphon(unsigned long long int phno)
{
    string pno=to_string(phno);
    const regex pattern("[7-9][0-9]{9}");
    if(regex_match(pno, pattern))
    {
       return 1;
    }
    else{
        return 0;
    }
}

/*******************************************/

};

//**********student class***********

class Student : public Database
{
public:
    int log,login_page_recall;
    unsigned long long int phno;
    string student_name;
    string s_name;
    string passward;    //inserting data into db
    string s_passward;      //Getting data from db
    string issue_book_name;
    string return_book_name;
    int issue_book_ID,stud_id,s_id;
    int return_book_ID;
    int q , checkbookreturn;//quantity of book
    char ch;
    void Studentlogin()
    {
        Student s;
        int student_choice;
            while(1)
            {
                cout<<"Are u member of library ? press 1 if yes. press 2 to get membership 3.Home Page"<<endl;
                cin>>log;
                if(cin.fail() || log>3 ||log<=0)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout<<"You have entered wrong input"<<endl;
                }
                if(!cin.fail() && log<=3 )
                {
                    break;
                }
            }
         if(log == 3)
         {
            // break;
         }
        if(log == 1)
        {
            system("cls");
             while(1)
                {
                    cout<<"enter your name "<<endl;
                    cin.ignore();
                    getline(cin,s_name);
                    int check=checkforvalidinputstring(s_name);
                    if(check == 1)
                    {
                    cout<<"Name Cannot have Number or special characters\n";
                    }
                    else{
                        break;
                    }
                }
            cout<<endl<<"Enter Student Id"<<endl;
            cin>>s_id;
            while(1){
                if(cin.fail())
                {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout<<"ID Should Integer only\n";
                cout<<endl<<"Enter Student Id"<<endl;
                cin>>s_id;
                }
                if(!cin.fail())
                {
                    break;
                }
        }
            cout<<"enter your Password "<<endl;
            s_passward="";
            ch=_getch();
            while(ch != 13)
                {
                    s_passward.push_back(ch);
                    cout << '*';
                    ch = _getch();
                }
            string namefromdb=Selectforname(s_id);
            string passfromdb= Selectforpassword(s_id);
            if(namefromdb==s_name && passfromdb==s_passward)
            {
                system("cls");
                    cout<<"Welcome "<<namefromdb<<endl;
                    do{
                    cout<<"\n What would you like to do?\n"<<endl;
                    cout<<"1.Search Book"<<endl<<"2.Issue Book"<<endl<<"3.Return Book"<<endl<<"4.List of all Books"<<endl<<"5.Home Page\n";
                    cin>>student_choice;
                    while(1)
                    {
                        if(cin.fail() || student_choice>5)
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(),'\n');
                            cout<<"You have entered wrong input"<<endl;
                            cout<<endl<<"what would you like to do?\n"<<endl;
                            cout<<"1.Search Book"<<endl<<"2.Issue Book"<<endl<<"3.Return Book"<<endl<<"4.List of all Books"<<endl<<"5.Home Page\n";
                            cin>>student_choice;
                        }
                        if(!cin.fail() && student_choice<=5)
                        {
                        break;
                        }
                    }
                    switch(student_choice)
                        {
                            case 1:
                                search_book_in_DB();
                                break;
                            case 2:
                                cout<<"Enter Book Name That you want to issue "<<endl;
                                 cin.ignore();
                                getline(cin,issue_book_name);
                                cout<<"Enter Book ID that you want to issue"<<endl;
                                cin>>issue_book_ID;
                                 while(1)
                                    {
                                        if(cin.fail())
                                        {
                                         cin.clear();
                                         cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                         cout<<"ID Should Integer only\n";
                                         cout<<"Enter Book ID that you want to issue"<<endl;
                                         cin>>issue_book_ID;
                                        }
                                        if(!cin.fail())
                                        {
                                        break;
                                        }
                                    }
                                   q  =  Select_book_Quantity( issue_book_ID );
                                  if(q==0)
                                  {
                                      cout<<"All Books of Name: "<<issue_book_name<< " and ID: "<<issue_book_ID<<" are Issued, No book currently available in library ";
                                  }
                                  else{
                                      int cc= checknumberofissuedbooks(s_id,issue_book_ID);
                                        if(cc<3)
                                        {
                                           Issue_Book(issue_book_name,s_name,s_id,issue_book_ID);
                                        }
                                         else{
                                            cout<<"You cant issue more than 3 books.";
                                         }
                                  }
                                break;
                            case 3:
                                cout<<"Enter the Book name That u want to Return ";
                                cin.ignore();
                                getline(cin,return_book_name);
                                cout<<"Enter the book ID ";
                                cin>>return_book_ID;
                                while(1)
                                    {
                                        if(cin.fail())
                                        {
                                         cin.clear();
                                         cin.ignore(numeric_limits<streamsize>::max(),'\n');
                                         cout<<"ID Should Integer only\n";
                                         cout<<"Enter the book ID ";
                                         cin>>return_book_ID;
                                        }
                                        if(!cin.fail())
                                        {
                                        break;
                                        }
                                    }
                                     checkbookreturn=checkifissue(return_book_name,return_book_ID,s_id);
                                    if(checkbookreturn!=10)
                                    {
                                     cout<<"You have not issued that book";
                                    }
                                    else
                                    {
                                    Return_book(return_book_name,return_book_ID,s_name,s_id);
                                    }
                                break;
                            case 4:
                                 getBookTable();
                                break;
                            default:
                                break;
                        }
                      }while(student_choice<=4);
                }
                else{

                    cout<<"\n Name,ID or Password Invalid \n";
                }
            }

        if(log == 2)
        {
            system("cls");
            cout<<"Membership Form \n"<<endl;
             while(1)
                {
                   cout<<"Enter your name"<<endl;
                   cin.ignore();
                  getline(cin,student_name);
                    int check=checkforvalidinputstring(student_name);
                    if(check == 1)
                    {
                    cout<<"Name Cannot have Number\\special characters\n";
                    }
                    else{
                        break;
                    }
                }
         cout<<endl<<"Enter Student Id"<<endl;
         cin>>stud_id;
        while(1){
                if(cin.fail())
                {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout<<"ID Should Integer only\n";
                cout<<endl<<"Enter Student Id"<<endl;
                cin>>stud_id;
                }
                if(!cin.fail())
                {
                        break;
                }
        }
            while(1)
            {
                 cout<<"Enter your phone number plz"<<endl;
                 cin>>phno;
                if(cin.fail())
                {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout<<"phone number Should be Integer only\n";
                }
                else{
               if(!cin.fail())
                {
                int flag=validatphon(phno);
                if(flag==1)
                {
                    break;
                }
                else{
                    cout<<"Invalid Phone Number \n";
                }
                }
                }
            }
                while(1)
                {
                cout<<"enter your password"<<endl;
                cin>>passward;
                if(passward.length()<4)
                {
                    cout<<"Password should be of minimum 4 characters \n";
                }
                else{
                    break;
                }
                }
              InsertMember(student_name,stud_id,phno,passward);
           while(1)
           {
            cout<<endl<<"do u want to go to login page press 1 if yes 2 for home page"<<endl;
            cin>>login_page_recall;
            if(cin.fail())
            {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"You have entered wrong input"<<endl;
            cout<<endl<<"do u want to go to login page press 1 if yes 2 for home page"<<endl;
            cin>>login_page_recall;
            }
            if(!cin.fail() && login_page_recall < 3)
            {
                break;
            }
            else{
                cout<<"invalid choice\n";
            }
           }
           if (login_page_recall==1)
           {
               s.Studentlogin();
           }
           if(login_page_recall==2)
           {
             //break;
           }
        }
    }
};
class admin : public Database
{
public:
    string book_name, book_author, book_name_del,search_book_name;
    int book_id, book_quant,book_id_del;
  public:
    void Add_book()
    {
        system("cls");
        cout<<"Enter Book name\n";
        cin.ignore();
        getline(cin,book_name);
        cout<<endl<<"Enter Book Id"<<endl;
        cin>>book_id;
        while(1){
                if(cin.fail())
                {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout<<"ID Should Integer only\n";
                cout<<endl<<"Enter Book Id"<<endl;
                cin>>book_id;
                }
                if(!cin.fail())
                {
                    break;
                }
        }
     while(1)
    {
        cout<<endl<<"Enter author name"<<endl;
        cin.ignore();
        getline(cin,book_author);
       // cout<<book_author;
        int check=checkforvalidinputstring(book_author);
        if(check == 1)
        {
            cout<<"Name Cannot have Number\\special characters\n";
        }
        else{
            break;
        }
    }

        cout<<"\nEnter Book Quantity"<<endl;
        cin>>book_quant;
         while(1){
                if(cin.fail())
                {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout<<"book quantity Should be Number only\n";
                cout<<endl<<"Enter Book book_quantity"<<endl;
                cin>>book_quant;
                }
                if(!cin.fail())
                {
                    break;
                }
        }
   Insert_book_data(book_name,book_id,book_author,book_quant);
    }
    void Search_book()
    {
        search_book_in_DB();
    }
    void Delete_book()
    {
       cout<<"Enter the book Name that want to delete"<<endl;
       cin.ignore();
       getline(cin,book_name_del);
       cout<<"Enter Book Id";
       cin>>book_id_del;
        while(1){
                if(cin.fail())
                {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(),'\n');
                cout<<"book ID Should be Number only\n";
                cout<<endl<<"Enter Book ID"<<endl;
                cin>>book_id_del;
                }
                if(!cin.fail())
                {
                        break;
                }
        }
      int check= check_book_quantity_to_delete(book_name_del,book_id_del);
       if(check==10)
       {
           Delete_book_data(book_name_del);
       }
       if(check==0){
        cout<<"All books Are not present in database Cannot delete the book";
       }

    }
    void Update_book()
    {
        cout<<"Enter Book Name that u want to update"<<endl<<"NO Function written for update CHeck line 1134";
    }

    void admin_db(string admin_name, string admin_pass)
    {

        string a_name= admin_name;
        string a_pass= admin_pass;
        string a_db_pass,a_db_name;
        int admin_ch;
        Connect();
        cout<<" Verifying  Username and Password..... ";
        int qstate=0;
        stringstream ss;
        MYSQL_ROW row;
        MYSQL_RES* res;
        ss<< "SELECT Admin_Name, Admin_Password FROM verify_admin" ;
        string query =ss.str();
        const char* q = query.c_str();
        qstate = mysql_query(conn, q);
        if(qstate == 0)
            {
                res=mysql_store_result(conn);
            while(row = mysql_fetch_row(res))
                    {
                       a_db_name=row[0];
                       a_db_pass=row[1];
                    }
            }
            else{
                cout<<"else part";
                }
        if(a_name==a_db_name && a_pass==a_db_pass)
        {
            system("cls");
            cout<<"welcome admin"<<endl;
            do{
            cout<<endl<<"what would you like to do?"<<endl;
            cout<<"1.Add Book"<<endl;
            cout<<"2.Search Book"<<endl;
            cout<<"3.Delete Book"<<endl;
            //cout<<"4.Update Book"<<endl;
            cout<<"4.list of all books"<<endl;
            cout<<"5.Exit"<<endl;
            cin>>admin_ch;
            while(1)
            {
                if(cin.fail() || admin_ch>5)
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(),'\n');
                    cout<<"You have entered wrong input"<<endl;
                    cout<<endl<<"what would you like to do?"<<endl;
                    cout<<"1.Add Book"<<endl;
                    cout<<"2.Search Book"<<endl;
                    cout<<"3.Delete Book"<<endl;
                   // cout<<"4.Update Book"<<endl;
                    cout<<"4.list of all books"<<endl;
                    cout<<"5.Exit"<<endl;
                    cin>>admin_ch;
                }
                if(!cin.fail() && admin_ch<=5)
                {
                        break;
                }

            }
            switch(admin_ch)
            {
                case 1:
                   Add_book();
                   break;
                case 2:
                    Search_book();
                    break;
                case 3:
                    Delete_book();
                    break;
                /*case 4:
                    Update_book();
                    break;*/
                case 4:
                    getBookTable();
                    break;
                default:
                    cout<<"exited\n";
                    break;
            }
            }while(admin_ch<=4);
        }
        else{
            cout<<endl<<"Wrong Username or Password\n";
            }
    }
};

int main()
{
    Student s;
    admin ad;
    int whoru;
    string admin_name;
    string admin_pass;
    char ch;
while(1)
  {
    cout<<"Press 1 for admin  Press 2 for Student"<<endl;
    cin>>whoru;
    while(1)
     {

       if(cin.fail())
        {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(),'\n');
         cout<<"You have entered wrong input\n"<<endl;
         cout<<"Press 1 for admin  Press 2 for Student"<<endl;
         cin>>whoru;
        }
        if(!cin.fail())
        {
         break;
        }
    }
    switch(whoru)
    {
    case 1:
            system("cls");
            cout<<"Enter Admin Username"<<endl;
            cin>> admin_name;
            cout<<"Enter Admin Password"<<endl;
            admin_pass="";
            ch = _getch();
            while(ch != 13)
               {
                admin_pass.push_back(ch);
                cout << '*';
                ch = _getch();
               }
            ad.admin_db(admin_name,admin_pass);
            break;
        case 2:
            system("cls");
            s.Studentlogin();
            break;
        default:
            printf("invalid value\n");
            break;
      }
  }
}
