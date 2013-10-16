#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"


#define MY_UUID { 0x24, 0x2B, 0x9F, 0x04, 0xCE, 0x2F, 0x41, 0xF5, 0xB5, 0xBD, 0xFF, 0xDD, 0x9A, 0x8F, 0x93, 0x28 }
PBL_APP_INFO(MY_UUID,
             "Fuzzy watchface", "Booski",
             0, 1, /* App version */
             DEFAULT_MENU_ICON,
             APP_INFO_WATCH_FACE);

Window window;

void handle_init(AppContextRef ctx) {
  (void)ctx;
  
  window_init(&window, "Window Name");
  window_stack_push(&window, true /* Animated */);
}

**char mstrings={
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

**char hstrings={
       "midnatt",
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

**char hposts={
       "natten",
       "morgonen",
       "dagen",
       "kvällen"
};

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init
    .tick_info = {
    	       .tick_handler = &handle_tick,
	       		     .tick_units = MINUTE_UNIT
			     };
  };
  app_event_loop(params, &handlers);
}
