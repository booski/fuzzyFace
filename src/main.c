#include <pebble.h>
#include <time.h>
#include "words.h"


#define BUFFER_SIZE 86

TextLayer *label;
Window *window;
char buffer[BUFFER_SIZE];

void update_time(int h, int m, int s) {
	build_time_string(h, 
                    m, 
                    s, 
                    buffer, 
                    BUFFER_SIZE);
	text_layer_set_text(label, buffer);
}

void handle_tick(struct tm *t, TimeUnits units_changed) {
  update_time(t->tm_hour, 
              t->tm_min, 
              t->tm_sec);
}

void handle_init(void) {

  window = window_create();
  window_stack_push(window, true);
  window_set_background_color(window, GColorBlack);
  GFont font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_ANONYMOUS_PRO_BOLD_28));
  //GFont font = fonts_get_system_font(FONT_KEY_DROID_SERIF_28_BOLD);

  GRect rect = layer_get_frame(window_get_root_layer(window));
  
  label = text_layer_create(GRect(0, 
                          5, 
                          rect.size.w, 
                          rect.size.h-5
                         ));
  
  text_layer_set_background_color(label, GColorClear); //crashes here  
  text_layer_set_text_color(label, GColorWhite);
  text_layer_set_font(label, font);
  
  layer_add_child(window_get_root_layer(window), text_layer_get_layer(label));
  
  time_t now = time(NULL);
  struct tm *t = localtime(&now);
  update_time(t->tm_hour, 
              t->tm_min, 
              t->tm_sec);
  
  tick_timer_service_subscribe(MINUTE_UNIT, &handle_tick);
}

void handle_deinit(void) {
  window_destroy(window);
  text_layer_destroy(label);
  tick_timer_service_unsubscribe();
}

int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}
