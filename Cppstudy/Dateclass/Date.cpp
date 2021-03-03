#include"Date.h"

int GetMonthDay(int year,int month){
  static int days[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
  int day=days[month];
  if(month==2&&((year%4==0&&year%100!=0)||(year%400==0))){
    ++day;
  }
  return day;
}
Date::Date(int year,int month,int day){
   _year=year;
   _month=month;
   _day=day;
   if(!(year>=0&&month>0&&month<13&&0<day&&day<GetMonthDay(year,month))){
     cout<<"日期非法："; 
   }
}
Date::Date(const Date& date){
   if(!(date._year>=0&&date._month>0&&date._month<13&&0<date._day&&date._day<GetMonthDay(date._year,date._month))){
     cout<<"日期非法："<<date<<"拷贝构造失败"<<endl; 
   }else{
     _year=date._year;
     _month=date._month;
     _day=date._day;
   }
}
Date& Date::operator=(const Date&date){
   if(!(date._year>=0&&date._month>0&&date._month<13&&0<date._day&&date._day<GetMonthDay(date._year,date._month))){
     cout<<"日期非法："<<date<<"赋值失败"<<endl; 
   }else{
     _year=date._year;
     _month=date._month;
     _day=date._day;
   }
  return *this;
}
ostream& operator<<(ostream& os,const Date& date){
  os<<date._year<<' '<<date._month<<' '<<date._day;
  return os;
}

istream& operator>>(istream& is,Date& date){
  is>>date._year>>date._month>>date._day;
  return is;
}
Date& Date::operator+=(int day){
  if(day<0){
    return *this-=-day;
  }
  _day+=day;
  while(_day>GetMonthDay(_year,_month)){
    _day-=GetMonthDay(_year,_month);
    _month++;
    if(_month==13){
      ++_year;
      _month=1;
    }
  }
  return *this;
}
Date Date::operator+(int day){
  Date date=*this;
  date+=day;
  return date;
}
Date& Date::operator-=(int day){
  if(day<0){
    return *this+=-day;
  }
  _day-=day;
  while(_day<0){
    --_month;
    if(_month==0){
      --_year;
      _month=12;
    }
    _day+=GetMonthDay(_year,_month);
  }
  return *this;
}
Date Date::operator-(int day){
  Date temp=*this;
  temp-=day;
  return temp;
}
bool Date::operator==(const Date&date){
  return _year==date._year&&_month==date._month&&_day==date._day;
}
bool Date::operator!=(const Date&date){
  return !(*this==date);
}
Date& Date::operator++(){
 *this+=1;
 return *this;
}
Date Date::operator++(int){
  Date temp=*this;
  *this+=1;
  return temp;
}
Date& Date::operator--(){
  *this-=1;
  return *this;
}
Date Date::operator--(int){
  Date temp=*this;
  *this-=1;
  return temp;
}
bool Date::operator>(const Date& date){
  if(_year>date._year){
    return true;
  }else if(_year==date._year){
    if(_month>date._month){
      return true;
    }else if(_month==date._month){
      if(_day==date._day){
        return true;
      }
    }
  }
  return false;
}
bool Date::operator>=(const Date& date){
  return *this==date||*this>date;
}
bool Date::operator<(const Date& date){
  return !(*this>=date);
}
bool Date::operator<=(const Date& date){
  return !(*this>date);
}

int Date::operator-(const Date& date){
  Date max=*this,min=date;
  int flag=1;
  if(max<min){
    max=date;
    min=*this;
    flag=-1;
  }
  int res=0;
  while(min!=max){
    ++min;
    ++res;
  }

  return flag*res;
}
int main(){
  Date date(2021,3,3);
  Date date1(2021,9,1);
  cout<<date+(-1000)<<endl;
  cout<<date1-date<<endl;
  cout<<date-date1<<endl;
  return 0;
}
