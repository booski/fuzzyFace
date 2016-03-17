#include <pebble.h>
#include <time.h>
#include "words.h"

#define TIME_SIZE 86
#define DATE_SIZE 38
#define SPLIT 18	

Window *window;
TextLayer *time_label;
TextLayer *date_label;

char time_buffer[TIME_SIZE];
char date_buffer[DATE_SIZE];
int date;

GFont font, smallfont, minifont;

void update_time(int h, int m, int s) {
	if(build_time_string(h,m,s,time_buffer,TIME_SIZE)){
		text_layer_set_font(time_label, smallfont);	
	}else{
		text_layer_set_font(time_label, font);
	}
	text_layer_set_text(time_label, time_buffer);
}

void update_date(int month, int day, int weekday) {
  build_date_string(month,
                    day, 
                    weekday, 
                    date_buffer, 
                    DATE_SIZE);
  text_layer_set_text(date_label, date_buffer);
}

void update(struct tm *t, TimeUnits units_changed) {
  update_time(t->tm_hour, 
              t->tm_min, 
              t->tm_sec);
  
  if(t->tm_mday != date) {
    date = t->tm_mday;
    update_date(t->tm_mon,
                t->tm_mday,
                t->tm_wday);
  }
}

void handle_init(void) {
  window = window_create();
  window_stack_push(window, true);
	
  #ifdef PBL_COLOR
  window_set_background_color(window, GColorWhite );
  #else
   window_set_background_color(window, GColorWhite);
  #endif
  GRect rect = layer_get_frame(window_get_root_layer(window));
  
  //timelabel init
  time_label = text_layer_create(GRect(0, 0, rect.size.w, rect.size.h-SPLIT));
	
  text_layer_set_background_color(time_label, GColorClear);
  #ifdef PBL_COLOR
	text_layer_set_text_color(time_label, GColorBlack);
  #else
	text_layer_set_text_color(time_label, GColorBlack);
  #endif
  
  font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TRAVELING_26));
  smallfont = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TRAVELING_24));
  text_layer_set_font(time_label, font);
  
  //add timelabel to window
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(time_label));

  //datelabel init
  date_label = text_layer_create(GRect(0, rect.size.h-SPLIT, rect.size.w, SPLIT));
  
  
  #ifdef PBL_COLOR
	text_layer_set_background_color(date_label, GColorRed);
	text_layer_set_text_color(date_label, GColorWhite);
  #else
	text_layer_set_background_color(date_label, GColorClear);
	text_layer_set_text_color(date_label, GColorBlack);
  #endif
  text_layer_set_text_alignment(date_label, GTextAlignmentCenter);
	
  minifont = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_TRAVELING_12));
  //text_layer_set_font(date_label, fonts_get_system_font(FONT_KEY_FONT_FALLBACK));
	text_layer_set_font(date_label, minifont);
  
  //add datelabel to window
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(date_label));
  
  //make sure time/date is shown immediately
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  date = t->tm_mday;
  update_time(t->tm_hour, 
              t->tm_min, 
              t->tm_sec);
  
  update_date(t->tm_mon,
              t->tm_mday,
              t->tm_wday);
  
  //make sure that keeps happening
  tick_timer_service_subscribe(MINUTE_UNIT, &update);
}

void handle_deinit(void) {
  text_layer_destroy(time_label);
  text_layer_destroy(date_label);
  window_destroy(window);
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
