#include "words.h"
#include "string.h"

static const char* const mstrings[]={
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

static const char* const hstrings[]={
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

static const char* const hposts[]={
   	"natten",
   	"morgonen",
   	"dagen",
   	"kvällen"
};

static const char* INTRO = "Klockan är";
static const char* GLUE = " på ";

static size_t append_string(char* buffer, const size_t length, const char* str) {
  strncat(buffer, str, length);

  size_t written = strlen(str);
  return (length > written) ? written : length;
}

void build_time_string(int h, int m, char* buffer, size_t length) {
	//DEBUG
	//h=3;
	//m=34;
	//END DEBUG
	int hmod = (h > 12) ? (h - 12) : h ;
	int mmod = ((60 * m) + 150) / (60*5);
	
	if(mmod > 4) {
		hmod += 1;
	}
	
	int spec;
	if(h < 3 || h > 22) {
		spec = 0;
	} else if(h < 11) {
		spec = 1;
	} else if(h < 18) {
		spec = 2;
	} else {
		spec = 3;
	}
	
	// echo Klockan är( $mstrings[mmod]) $hstrings[hmod] på $hposts[spec].
	
	size_t remain = length;
	memset(buffer, 0, length);
	
	remain -= append_string(buffer, remain, INTRO);
	if (! strlen(mstrings[mmod]) < 2) {
		remain -= append_string(buffer, remain, " ");
		remain -= append_string(buffer, remain, mstrings[mmod]);
	}
	remain -= append_string(buffer, remain, " ");
	remain -= append_string(buffer, remain, hstrings[hmod]);
	remain -= append_string(buffer, remain, GLUE);
	remain -= append_string(buffer, remain, hposts[spec]);
	remain -= append_string(buffer, remain, ".");
}