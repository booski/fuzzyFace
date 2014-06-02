#include <string.h>
#include "words.h"

static const char* const MINUTES[]={
	"",
	"five past",
 	"ten past",
 	"quarter past",
	"twenty past",
 	"twenty-five past",
 	"half past",
 	"twenty-five to",
 	"twenty to",
 	"quarter to",
 	"ten to",
 	"five to"
};

static const char* const HOURS[]={
	"twelve",
	"one",
	"two",
	"three",
	"four",
	"five",
	"six",
	"seven",
	"eight",
	"nine",
	"ten",
	"eleven",
	"twelve"
};

static const char* const SUFFIXES[]={
 	"at night",
 	"in the morning",
 	"in the day",
 	"in the evening"
};

static const char* TIME_INTRO = "It is";

static const char* MONTHS[]={
  "Janurary",
  "February",
  "March",
  "April",
  "May",
  "June",
  "July",
  "August",
  "September",
  "October",
  "November",
  "December"
};

static const char* DAYS[]={
  "first",
  "second",
  "third",
  "fourth",
  "fifth",
  "sixth",
  "seventh",
  "eighth",
  "ninth",
  "tenth",
  "eleventh",
  "twelfth",
  "thirteenth",
  "fourteenth",
  "fifteenth",
  "sixteenth",
  "seventeenth",
  "eighteenth",
  "nineteenth",
  "twentieth",
  "twentyfirst",
  "twentysecond",
  "twentythird",
  "twentyfourth",
  "twentyfifth",
  "twentysixth",
  "twentyseventh",
  "twentyeighth",
  "twentyninth",
  "thirtieth",
  "thirtyfirst"
};

static size_t append_string(char* buffer, const size_t free, const char* str) {
  strncat(buffer, str, free);

  size_t written = strlen(str);
  return (free > written) ? written : free;
}

void build_time_string(int h, int m, int s, char* buffer, size_t length) {

  //DEBUG
	//h=7;
	//m=25;
	//END DEBUG
  
  //turn minutes into a value between 0 and 12.
	int mmod = ((60 * m) + s + 299) / 300;
  
  //increment hour if minutes are in 'to' territory
	int htemp = (mmod > 5) ? h + 1 : h;
  //make 12-hour time
	int hmod = (htemp > 12) ? (htemp - 12) : htemp ;
	
  //set the time of day
	int suf;
	if(htemp < 3 || htemp > 22) {
		suf = 0;
	} else if(htemp < 11) {
		suf = 1;
	} else if(htemp < 18) {
		suf = 2;
	} else {
		suf = 3;
	}
	
	size_t remain = length;
	memset(buffer, 0, length);
	
	remain -= append_string(buffer, remain, TIME_INTRO);
	if (mmod != 0 && mmod < 12) {
		remain -= append_string(buffer, remain, " ");
		remain -= append_string(buffer, remain, MINUTES[mmod]);
	}
	remain -= append_string(buffer, remain, " ");
	remain -= append_string(buffer, remain, HOURS[hmod]);
	remain -= append_string(buffer, remain, " ");
	remain -= append_string(buffer, remain, SUFFIXES[suf]);
	remain -= append_string(buffer, remain, ".");
}

void build_date_string(int month, int day, int weekday, char* buffer, size_t length) {
  
  //DEBUG
  //month=8;
  //day=27;
  //weekday=4;
  //END DEBUG
  
  //fix day to fit 0-indexing
  day-=1;
  
  size_t remain = length;
  memset(buffer, 0, length);

  remain -= append_string(buffer, remain, MONTHS[month]);
  remain -= append_string(buffer, remain, " ");
  remain -= append_string(buffer, remain, DAYS[day]);
  remain -= append_string(buffer, remain, ".");
}