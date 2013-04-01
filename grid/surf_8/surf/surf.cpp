#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <vector>
#include <sstream>

using namespace std;


class Grid
     { 
     int dec;
     
     struct fileparam // структура хранит параметры файла. 
     {
      string ncols;  //  количество колонок
      string nrows;  //  количество строчек
      string xllcenter; // сохранить в результирующем файле
      string yllcenter; // сохранить в результирующем файле
      string cellsize;     //  cохранить в результирующем файле
      string nodata_value;  // отсутствие значения
     };  

	 fileparam ptr; // для хранения параметров файла

     list<string> L; // хранение строк исходного файла  
     list<int> I; // операции с числами
	 list<string> OUT; // формирование списка элементов для записи в файл 
     

   // Конструктор класса:
   public: Grid() // path - путь к папке, где лежит файл test.txt
       {
         dec = 10.0;
       }; // public: Grid(string path) // path - путь к папке, где лежит файл test.txt



   private: 

	  void GetGridFromFile()
      {
          // заполняем список I данными из файла
          int count = 0; 
          list<string>::iterator p;
          for(p = L.begin(); p != L.end(); ++p)
          {  
            count++;
          if (count < 7) continue;

            // Перебираем элементы внутри строк, добавляем их в список I
                      string buf; 
                      stringstream ss(*p);  

                      while (ss >> buf)
                       if (buf != ptr.nodata_value) // элементы без значения не считаем 
              I.push_back(  atoi(buf.c_str())  );
          };
      }; //void



      void GetDataToFileStructure()
      {
         // Заполним структуру параметров
         int count = 0;
         
         list<string>::iterator i; // получим первые 6 записей из файла, запишем в структуру
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
      };





   public : 

	 int Grid:: CheckFile(string path)
     {
      // cчитываем содержимое файла в список строк
         string line;
         ifstream myfile(path.c_str());
                        
         if (myfile.is_open())
         {
                     myfile.close();
             return 1;
         }
         else
         {
           cout << "Unable to open file. Press Enter key";
           return 0;
         } 
     };


     void GetDataFromFile(string path)
     {   
        // все строки из файла поместим в список L
         string line;
         ifstream myfile(path.c_str());
                
         while (! myfile.eof() )
         {
           getline(myfile,line);
           L.push_back( line );
         }
          myfile.close();

		  GetGridFromFile();
		  GetDataToFileStructure();
     };

     

      

     void GetAndShowMinAndMaxElement()
     {
          //Найти минимальное и максимальное значение и вывести в консоль   
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
     };



     void Calculate()
     {
         int count = 0; 
          list<string>::iterator t;
          for(t = L.begin(); t != L.end(); ++t)
          {  
              count++;
            if (count < 7) continue;

            string buf; 
            stringstream ss(*t);  
            
            string item; 

              while (ss >> buf)
                    if (buf != ptr.nodata_value) // элементы без значения не считаем 
                    {
                        int some_int =  (atoi(buf.c_str()) * 10.0); 
                        ostringstream buffer;
                        buffer << some_int;
                        string some_string = buffer.str();
                        OUT.push_back( some_string);
                    }
                    else OUT.push_back( buf );
          }
      
     }; //void Calculate()



     int PutDataToFile(string path)
     { 
        ofstream myfile (path.c_str());
         
         if (myfile.is_open())
         {
                   // в начале секция параметров
           myfile << ptr.ncols << "\n"; 
           myfile << ptr.nrows << "\n"; 
           myfile << ptr.xllcenter << "\n";
           myfile << ptr.yllcenter << "\n";
           myfile << ptr.cellsize << "\n";
           myfile << ptr.nodata_value << "\n";
                       
                   // числа из первого файла умноженные на 10
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
          return 1;
        }          
         else
         {
           cout << "Unable to save to file";
           return 0;
         }

     }; // void

     
	 ~Grid()
	 {
		 L.clear();
		 OUT.clear();
		 I.clear();
	 }

};



int main()
{
  string test = "C:/test.txt";
  string out = "C:/out.txt";

  Grid A;
  int i = A.CheckFile(test);
  if ( i==0 ) { getchar(); return 0; }; // выход

  A.GetDataFromFile(test);
  A.GetAndShowMinAndMaxElement();
  A.Calculate();

  i = A.PutDataToFile(out);
  if ( i==0 ) { getchar(); return 0; }; // выход

  puts("Press Enter key");
  getchar();
  
  return 0;

}