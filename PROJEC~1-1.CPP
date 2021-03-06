
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>


//                   CLASS USED IN PROJECT



     class travel

{      char destination[50];
       int days;
       long rate;
public:

       void input()
       {
	cout<<"\nenter your destination: ";cin>>destination;
	cout<<"\nenter number of days: ";cin>>days;
	cout<<"\nenter rate: ";cin>>rate;
       }
       void output()
       {
	cout<<"\nyour destination: " << destination;
	cout<<"\nnumber of days: " << days;
	cout<<"\nrate: " << rate << endl;
       }
       char* getdestination()
       {
	return destination;
       }
       int getdays()
       {
	return days;
       }
       long getrate()
       {
	return rate;
       }

};

//    	function to write in file

      void write_file()
       {

       ofstream fout("package.dat",ios::binary);
	 if(!fout)
	 {cout<<"file not open";
	 return;}
	travel t;
	char choice;
	do{t.input();
	fout.write((char*)&t,sizeof(t));
	cout<<"want to continue(y/n):";
	choice=getche();
	}while(choice=='y'||choice=='Y');
	fout.close();

	}

//    	function to display a file

   void read_file()
   {
    ifstream fin("package.dat",ios::binary);
    if(!fin)
	 {cout<<"file not open";
	 return;}
    travel t;
    while(fin.read((char*)&t,sizeof(t)))
    {
     t.output();
     cout<<"\nPress any key to see next record";
     getch();
    }
   }

//    	function to display a record

void read_record()
   {
    ifstream fin("package.dat",ios::binary);
    if(!fin)
	 {cout<<"file not open";
	 return;}
    travel t;
    char des[20];
    cout<<"\nenter the destination whose record is to be displayed=";
    cin>>des;
    int flag=0;
    while(fin.read((char*)&t,sizeof(t)))
     {
     if(strcmpi(t.getdestination(),des)==0)
     {
	flag=1;
	t.output();
     }
    }
    if (flag==0)
      cout<<"\n this destination is not present in file\n";
     }

//    	function to delete a record

void Delete()
{
	ifstream fin("package.dat",ios::binary);
	ofstream fout("pack.dat",ios::binary);
	if(!fin||!fout)
	{cout<<"file not open";
	return;}
	travel t;
	char des[20];
	cout<<"enter the destination whose record is to be deleted:";
	cin>>des;
	while(fin.read((char*)&t,sizeof(t)))
	{
	if(strcmpi(t.getdestination(),des)!=0)	// wrong condition
	fout.write((char*)&t,sizeof(t));
	}
	fin.close();
	fout.close();
	remove("package.dat");
	rename("pack.dat","package.dat");
	}

//    	modification of a record

void modify()
{
    fstream f("package.dat",ios::in|ios::out|ios::ate|ios::binary);
    if(!f)
    {cout<<"file not open";
	 return;}
     f.seekg(0);
     travel t;
     char des[20];
     cout<<"\nenter the destination whose record is to be modified=";
     cin>>des;
     int size = sizeof(t);
     int flag=0;
     while(f.read((char*)&t,sizeof(t)))
     {
     if (f.eof())
	break;
     if(strcmpi(t.getdestination(),des)==0)
       {
	flag=1;
	t.input();
	f.seekp(-size,ios::cur);
	f.write((char*)&t,sizeof(t));
	break;
	}
      }
      if (flag==0){
	cout << "\nInvalid Destination\n";
	getch();
      }
      f.close();
      }


//    	insertion of a record

void insert()
       {
       ifstream fin("package.dat",ios::binary);
       ofstream fout("pack.dat",ios::binary);
       travel NEW,OLD;
       NEW.input();
       char last='y';
       while(fin.read((char*)&OLD,sizeof(OLD)))
       {
       if(NEW.getdays()<OLD.getdays())
	{
	 fout.write((char*)&NEW,sizeof(NEW));
	 last='n';
	 break;
	}
	else
	{
	 fout.write((char*)&OLD,sizeof(OLD));
	}
     }
     if(last=='y')
       fout.write((char*)&NEW,sizeof(NEW));
     else
      {
       fout.write((char*)&OLD,sizeof(OLD));
	while(fin.read((char*)&OLD,sizeof(OLD)))
	{fout.write((char*)&OLD,sizeof(OLD));}
      }

      fin.close();
      fout.close();
      remove("package.dat");
      rename("pack.dat","package.dat");
      }

//    	searching of a record

void search()
{
  ifstream fin("package.dat",ios::binary);
    if(!fin)
	 {cout<<"file not open";
	 return;}
	 int flag=0;
	 char des[20];
   cout<<"\nenter the destination whose record is to be searched=";
    cin>>des;
    travel t;
    while(fin.read((char*)&t,sizeof(t)))
    {
     if(strcmpi(t.getdestination(),des)==0){
	  flag=1;
	     break;
     }
     }
     if(flag==1)
	t.output();
    else
	cout << "\nDestination not found\n";
    getch();
}

//    	THE MAIN FUNCTION OF PROGRAM

     void main()
{
       travel t;

	 clrscr();
	char ch,ch1;
	do
	{
		clrscr();

		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. DISPLAY";
		cout<<"\n\n\t02. INSERT";
		cout<<"\n\n\t03. MODIFY";
		cout<<"\n\n\t04. DELETE";
		cout<<"\n\n\t05. SEARCH";
		cout<<"\n\n\t06. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-6) ";
		ch=getche();
		clrscr();
	switch(ch)
		{
			case '1':
				 cout<<"\n1.display file\n";
				 cout<<"\n2.display record\n";
				 cout<<"\nenter choice: ";
				 cin>>ch;
				 if(ch=='1')
					 read_file();
				 else
					read_record();

				 break;

			case '2': insert(); break;
			case '3': modify(); break;
			case '4': Delete(); break;
			case '5': search(); break;
			case '6': exit(0);
		}
	}while(ch!='6');
}

