#include <iostream>
#include <stdlib.h>
#include<sstream>
#include<fstream>
#include<string>
using namespace std;
class Book
{
  public:
    string isbn;
    string name;
    string auth;
    string buffer;
    string quant;
    string isbn_list[100];
    int address_list[100];
    int count=-1;
    void create_index();
    string extract_isbn();
    void read_book();
    void del_book(string);
    void write();
    void pack();
    int search_index(string);
    void search_book(string);
    void issue_book();
    void deposit();
    void sort_index();
};


class Member
{
  public:
    string name;
    string phone;
};

void Book::read_book()
{
    cout << "Enter ISBN:";
    cin >>isbn;
    cout << "enter name of the book";
    cin >>name;
    cout << "enter the quantity";
    cin >>quant;
    cout << "enter author";
    cin >>auth;
}


void Book::pack()
{
    buffer.erase();
    buffer += isbn + '|' + name + '|' + quant + '|' + auth + '$'+'\n';
}


void Book::write()
{
    fstream file;
    int pos;
    file.open("book.txt",ios::out|ios::app);
    pos=file.tellg();
    file<<buffer;
    file.close();
   // isbn_list[++count]=isbn;
    //address_list[count]=pos;
    create_index();
    sort_index();
}

void Book::create_index()
{
  fstream file;
  int pos;
  string isbn;
  file.open("book.txt",ios::in);
  while(!file.eof())
  {
     pos=file.tellp();
     cout<<"index pos: "<<pos<<"\n";
     buffer.erase();
     getline(file,buffer);
     cout<<"buffer is: "<<buffer<<"\n";
     if(buffer[0]!='*')
		{
		     if(buffer.empty()){
                 cout<<"inside\n";
                 break;
             }
            
		     isbn=extract_isbn();
             cout<<"outside\n";
		     isbn_list[++count]=isbn;
		     address_list[count]=pos;
      		}
   }
   file.close();
   sort_index();

   buffer.erase();
}


string Book::extract_isbn()
{
    string isbn;
    int i=0;
    isbn.erase();
    while(buffer[i]!='|')
        isbn+=buffer[i++];
    return isbn;
}

void Book::sort_index()
{
    int i,j,temp_address;
    string temp_isbn;
    for(i=0;i<=count;i++)
    {
        for(j=i+1;j<=count;j++)
        {
            if(isbn_list[i]>isbn_list[j])
            {
                temp_isbn=isbn_list[i];
                isbn_list[i]=isbn_list[j];
                isbn_list[j]=temp_isbn;
                temp_address=address_list[i];
                address_list[i]=address_list[j];
                address_list[j]=temp_address;

            }

        }
    }
    for(i=0;i<=count;i++)
    {
        cout<<isbn_list[i]<<"\t"<<address_list[i]<<"\n";
    }
}


int Book::search_index(string key)
{
    int low=0,high=count,mid=0,flag=0,pos;
  while(low<=high)
  	{
        mid=(low+high)/2;
   		if(isbn_list[mid]==key)
            {
                flag=1;
                break;
            }
    	if(isbn_list[mid]>key)
            high=mid-1;
	   	if(isbn_list[mid]<key)low=mid+1;
 	}
  	if(flag)
  	return mid;
  	else
  	return -1 ;
}

void Book::search_book(string key)
{
    int pos=0,address;
    ifstream file;
    buffer.erase();
    pos=search_index(key);
    if(pos==-1)
    cout<<"book not found"<<"\n";
    else if(pos>=0)
    {
        file.open("book.txt");
        address=address_list[pos];

        cout<<"address list is:"<<address_list[pos];
        cout<<"adress is:"<<address<<"\n";
        file.seekg(address,ios::beg);
        buffer.erase();
        getline(file,buffer);
        cout<<"book found\n";
        cout<<buffer<<"\n";
        file.close();
    }
}
void Book::del_book(string key)
{
    fstream file;
    int pos=0;
    int i,adress;
    pos=search_index(key);
    if(pos>=0)
    {
        file.open("book.txt");
        adress=address_list[pos];
        file.seekp(adress,ios::beg);
        buffer.erase();
        getline(file,buffer);
        cout<<buffer;
        file.put('*');
        cout<<"book removed\n";
        for(i=pos;i<count;i++)
        {
            isbn_list[i]=isbn_list[i+1];
            address_list[i]=address_list[i+1];
        }
        count--;
        cout<<"count:"<<count<<"\n";
    }
    
    else
    {
        cout<<"book not found";
    }
    file.close();
    
}

int main()
{

    int choice;
    string isbn;
    Book b;
    int c;
   // b.create_index();
    while(true){

    
    cout << "1.)add book\n2.)search book\n3.)delete book\n4.)exit\n";
    cin >> choice;
    switch (choice)
    {
    case 1:
        cout<<"enter the no.of books to be added\t";
        cin>>c;
        while(c--)
        {
        b.read_book();
        b.pack();
        b.write();
        }
        break;
    case 2:
        cout<<"enter the isbn of the book\t";
        cin>>isbn;
        b.search_book(isbn);
        break;
    case 3: 
        cout<<"enter the isbn of the book\t";
        cin>>isbn;
        b.del_book(isbn);
        break;
    case 4:exit(0);
    default:cout<<"invalid choice";
    }
    }
}