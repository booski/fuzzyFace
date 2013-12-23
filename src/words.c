#include "words.h"
#include "string.h"

static const char* const MSTRINGS[]={
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

static const char* const HSTRINGS[]={
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

static const char* const HPOSTS[]={
   	"natten",
   	"morgonen",
   	"dagen",
   	"kvällen"
};

static const char* INTRO = "Klockan är";
static const char* GLUE = " på ";

/*
static const char* const MSTRINGS_EN[]={
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

static const char* const HSTRINGS_EN[]={
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

static const char* const HPOSTS_EN[]={
	"night",
	"morning",
	"day",
	"evening"
};

static const char* INTRO_EN = "It is";
static const char* GLUE_EN = " in the ";
*/
static size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}

void build_time_string(int h, int m, int s, char* buffer, size_t length) {
	//DEBUG
	//h=13;
	//m=0;
	//END DEBUG
	int mmod = ((60 * m) + s + 150) / 300;
	int htemp = (mmod > 4) ? h + 1 : h;
	int hmod = (htemp > 12) ? (htemp - 12) : htemp ;
		
	int spec;
	if(htemp < 3 || htemp > 22) {
		spec = 0;
	} else if(htemp < 11) {
		spec = 1;
	} else if(htemp < 18) {
		spec = 2;
	} else {
		spec = 3;
	}
	
	// echo Klockan är( $mstrings[mmod]) $hstrings[hmod] på $hposts[spec].
	
	size_t remain = length;
	memset(buffer, 0, length);
	
	remain -= append_string(buffer, remain, INTRO);
	if (mmod != 0 && mmod < 12) {
		remain -= append_string(buffer, remain, " ");
		remain -= append_string(buffer, remain, MSTRINGS[mmod]);
	}
	remain -= append_string(buffer, remain, " ");
	remain -= append_string(buffer, remain, HSTRINGS[hmod]);
	remain -= append_string(buffer, remain, GLUE);
	remain -= append_string(buffer, remain, HPOSTS[spec]);
	remain -= append_string(buffer, remain, ".");
}