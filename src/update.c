#include <pebble.h>
#include "update.h"
#include "words.h"

static size_t append_string(char* buffer, const size_t free, const char* str) {
  strncat(buffer, str, free);

  size_t written = strlen(str);
  return (free > written) ? written : free;
}

void update_time_buffer(int h, int m, int s, char* buffer, size_t length) {   
   // DEBUG
   //h = 3;
   //m = 34;
   //s = 0;
   // END DEBUG
   
   //turn minutes into a value between 0 and 11
	int mmod = ((60 * m) + s + 150) / 300;
  
   //increment hour if minutes are in 'to' territory
	int htemp = (mmod > 4) ? h + 1 : h;
   //make 12-hour time
	int hmod = (htemp > 12) ? (htemp - 12) : htemp ;
	
   //set the time of day
	int suf;
	if(h < 3 || h > 22) { //natten
		suf = 0;
	} else if(h < 12) { 	 //morgonen
		suf = 1;
	} else if(h < 18) { 	 //dagen
		suf = 2;
	} else { 				 //kvällen
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
	remain -= append_string(buffer, remain, TIME_GLUE);
	remain -= append_string(buffer, remain, SUFFIXES[suf]);
	remain -= append_string(buffer, remain, ".");
}

void update_date_buffer(int month, int day, char* buffer, size_t length) {
   // DEBUG
   //month = 8;
   //day = 31;
   // END DEBUG
   
   //fix day to fit 0-indexing
   day-=1;
   
   size_t remain = length;
   memset(buffer, 0, length);
   
   remain -= append_string(buffer, remain, "Den ");
   remain -= append_string(buffer, remain, DAYS[day]);
   remain -= append_string(buffer, remain, " ");
   remain -= append_string(buffer, remain, MONTHS[month]);
}