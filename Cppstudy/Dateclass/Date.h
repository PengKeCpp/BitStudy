#pragma once

#include<iostream>
#include<string>
using namespace std;
class Date{
  friend istream& operator>>(istream&,Date&);
  friend ostream& operator<<(ostream&,const Date&);
public:
  Date(int year,int month,int day);
  Date(const Date& date);
  Date& operator=(const Date&date);
  Date& operator+=(int day);
  Date operator+(int day);
  Date& operator-=(int day);
  Date operator-(int day);
  Date& operator++();
  Date operator++(int);
  Date& operator--();
  Date operator--(int);
  bool operator>(const Date&);
  bool operator<(const Date&);
  bool operator==(const Date&);
  bool operator!=(const Date&);
  bool operator<=(const Date&);
  bool operator>=(const Date&);
  int operator-(const Date&);

private:
  int _year;
  int _month;
  int _day;
};

istream& operator>>(istream&,Date&);
ostream& operator<<(ostream&,const Date&);
