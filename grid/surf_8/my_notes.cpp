#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <sstream>

using namespace std;

const string testfile = "test.txt";
const string outfile = "outs.txt";


class Grid
     { 
		 static const int dec = 10.0;
		 struct fileparam
		 {
			string ncols;  //  ���������� �������
			string nrows;  //  ���������� �������
			string xllcenter; // ��������� � �������������� �����
			string yllcenter; // ��������� � �������������� �����
			string cellsize;     //  c�������� � �������������� �����
			string nodata_value;  // ���������� ��������
		 };  

     list<string> L; 
		 list<string> OUT;
		 list<int> I;

		 // ����������� ������:
        // ������� ������ ����� �����:
	 public: Grid(string path) {
				   
				// c�������� ���������� ����� � ������
				 string line;
				 ifstream myfile("C:/test.txt");
	                      
				 if (myfile.is_open())
				 {
					while (! myfile.eof() )
					{
					 getline(myfile,line);
					 L.push_back( line );
					}
					myfile.close();
				 } 
				 else cout << "Unable to open file"; // TO DO �������� �������, ����� �� ��������� 
				  
				 // �������� ��������� ����������
				 
         int count = 0;
				 fileparam ptr;
				 
				 list<string>::iterator i;
				 for(i = L.begin(); i != L.end(); ++i)
				 {	 
				   count++;
				   switch(count)
				   {
		             case 1: ptr.ncols = *i; break;
                 case 2: ptr.nrows = *i; break; 
		             case 3: ptr.xllcenter = *i; break;
					 case 4: ptr.yllcenter = *i; break;
					 case 5: ptr.cellsize= *i;  break;
					 case 6: ptr.nodata_value = *i; break;
				   }
				   if (count == 7) break; 
				 };	  

        
 				  
         
       
         // ��������� ������ c ���������� ������������ �����
				  count = 0; 
				  list<string>::iterator p;
				  for(p = L.begin(); p != L.end(); ++p)
				  {	 
				    count++;
					if (count < 7) continue;

                    string buf; 
                    stringstream ss(*p);  

                    while (ss >> buf)
                      if (buf != ptr.nodata_value) // �������� ��� �������� �� ������� 
						  I.push_back(  atoi(buf.c_str())  );

				  } ;	

                  //����� ����������� � ������������ �������� � ������� � �������   
				  I.sort();
				  int min, max;
				  list<int>::iterator k;
				  for(k = I.begin(); k != I.end(); ++k)
				  {
				    if (k == I.begin())
						 min = *k;
					
				    if (k != I.end())
						max = *k;
						 
				  };
				  
				  cout << "min = " << min  <<  endl;
				  cout << "max = " << max  << endl;



				  // �������� ��� �������� �� ��������� 10.0
                  count = 0; 
				  list<string>::iterator t;
				  for(t = L.begin(); t != L.end(); ++t)
				  {	 
				    count++;
					if (count < 7) continue;

                    string buf; 
                    stringstream ss(*t);  
					
					string item; 

                    while (ss >> buf)
                      if (buf != ptr.nodata_value) // �������� ��� �������� �� ������� 
					  {
						int some_int =	(atoi(buf.c_str()) * 10); 
						ostringstream buffer;
						buffer << some_int;
						string some_string = buffer.str();
					      OUT.push_back( some_string);
					  }
					  else OUT.push_back( buf );

                      
				 // �������� ��������� � ���� out.txt c ����������� ������ ����������
				 ofstream myfile ("C:/out.txt");
				 
				 if (myfile.is_open())
				 {
                     // � ������ ������ ����������
					 myfile << ptr.ncols << "\n"; 
                     myfile << ptr.nrows << "\n"; 
		             myfile << ptr.xllcenter << "\n";
					 myfile << ptr.yllcenter << "\n";
					 myfile << ptr.cellsize << "\n";
					 myfile << ptr.nodata_value << "\n";
                   
				   // ����� �� ������� ����� ���������� �� 10
   				   int iCount = 0;
				   list<string>::iterator x;
				   for(x = OUT.begin(); x != OUT.end(); ++x)
				   {	 
				     iCount++;
					 myfile << *x <<" ";
					 if ( atoi(ptr.ncols.c_str()) == iCount )
					 {
					   myfile << "\n";
				       iCount = 0;
					 }
				   };	

					myfile.close();
				 }
				 else cout << "Unable to open file";

				  } ;

				  puts("Press Enter key");
  				  getchar();
			
			 }		 

};



int main()
{

  Grid A("C:/");

// A.GetDataFromFile();
// A.Calculate();
// A.PutDataToFile();

	return 0;
}





