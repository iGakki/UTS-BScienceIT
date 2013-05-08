#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace std;

class person
{
   /* person class to contain person data
   */
   
   private:
      string surname;
      double hourlyRate;
      int socialSec;
     
   public:
      person() {
         hourlyRate = -1;
         socialSec = -1;
         surname = "";
      }
      
      person(const person &other) :
         surname(other.surname),
         hourlyRate(other.hourlyRate),
         socialSec(other.socialSec)
      {
         // copy constructor
      }
      
      void setPerson(const string &name, double rate, int num) { 
         surname = name;
         hourlyRate = rate;
         socialSec = num;
      }
      
      const string& getSurname() const {
         return surname;
      }
      
      void printPerson() const {
         cout << fixed << setprecision(2);
         cout << setw(20) << left << surname << setw(4) << socialSec << "  " << hourlyRate << "\n";
      }
      
      bool loadPerson(ifstream &fin) {
         fin >> surname;
         fin >> hourlyRate;
         fin >> socialSec;
         return fin.good();
      }
      
      void swap(person &other) {
         std::swap(surname, other.surname);
         std::swap(hourlyRate, other.hourlyRate);
         std::swap(socialSec, other.socialSec);
      }
      
};
