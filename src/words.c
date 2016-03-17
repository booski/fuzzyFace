#include <pebble.h>
#include <string.h>
#include "words.h"

static const char* const MINUTES[]={
	"",
	"fem över",
 	"tio över",
 	"kvart över",
	"tjugo över",
 	"fem i halv",
 	"halv",
 	"fem över halv",
 	"tjugo i",
 	"kvart i",
 	"tio i",
 	"fem i"
};

static const char* const HOURS[]={
	"tolv",
 	"ett",
 	"två",
	"tre",
 	"fyra",
 	"fem",
 	"sex",
 	"sju",
 	"åtta",
 	"nio",
 	"tio",
 	"elva",
 	"tolv",
};

static const char* const SUFFIXES[]={
   	"natten",
   	"morgonen",
	"förmiddagen",
	"eftermiddagen",
   	"kvällen"
};

static const char* TIME_INTRO = "Klockan är";
static const char* TIME_GLUE = " på ";

static const char* MONTHS[]={
  "januari",
  "februari",
  "mars",
  "april",
  "maj",
  "juni",
  "juli",
  "augusti",
  "september",
  "oktober",
  "november",
  "december"
};

static const char* DAYS[]={
  "1",
  "andra",
  "tredje",
  "fjärde",
  "femte",
  "sjätte",
  "sjunde",
  "åttonde",
  "nionde",
  "tionde",
  "elfte",
  "tolfte",
  "trettonde",
  "fjortonde",
  "femtonde",
  "sextonde",
  "sjuttonde",
  "artonde",
  "nittonde",
  "tjugonde",
  "tjugoförsta",
  "tjugoandra",
  "tjugotredje",
  "tjugofjärde",
  "tjugofemte",
  "tjugosjätte",
  "tjugosjunde",
  "tjugoåttonde",
  "tjugonionde",
  "trettionde",
  "trettioförsta"
};


static size_t append_string(char* buffer, const size_t free, const char* str) {
  strncat(buffer, str, free);

  size_t written = strlen(str);
  return (free > written) ? written : free;
}

bool build_time_string(int h, int m, int s, char* buffer, size_t length) {
  
  //turn minutes into a value between 0 and 11
	int mmod = ((60 * m) + s + 150) / 300;
  
  //increment hour if minutes are in 'to' territory
	int htemp = (mmod > 4) ? h + 1 : h;
  //make 12-hour time
	int hmod = (htemp > 12) ? (htemp - 12) : htemp ;
	
  //set the time of day
	int suf;
	if(h < 3 || h > 22) { 	//natten
		suf = 0;
	} else if(h < 8) { 		//morgonen
		suf = 1;
	} else if(h < 12) { 		//fmdagen
		suf = 2;
	} else if(h < 18) { 	//emdagen
		suf = 3;
	} else { 				//kvällen
		suf = 4;
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
	remain -= append_string(buffer, remain, TIME_GLUE);
	remain -= append_string(buffer, remain, SUFFIXES[suf]);
	remain -= append_string(buffer, remain, ".");
	
	return (mmod > 0 && mmod < 6) || mmod == 7; // is long string
}

void build_date_string(int month, int day, int weekday, char* buffer, size_t length) {
  
  //DEBUG
  //month=8;
  //day=31;
  //weekday=4;
  //END DEBUG
  
  //fix day to fit 0-indexing
  day-=1;
  
  size_t remain = length;
  memset(buffer, 0, length);

  remain -= append_string(buffer, remain, "Den ");
  remain -= append_string(buffer, remain, DAYS[day]);
  remain -= append_string(buffer, remain, " ");
  remain -= append_string(buffer, remain, MONTHS[month]);
  remain -= append_string(buffer, remain, ".");
}