#include <pebble.h>
#include "update.h"

#define TIME_SIZE 60
#define DATE_SIZE 38
#define SPLIT 18

static GFont time_font;
static GFont date_font;

static Window *main_window;
static TextLayer *time_layer;
static TextLayer *date_layer;

static char time_buffer[TIME_SIZE];
static char date_buffer[DATE_SIZE];

static const int text_color = 0xFFFFFF; //0xAAAAAA;
static const int highlight_color = 0xFFFFFF;
static const int BACKGROUND[]={
   0x000000,
   0x000055,
   0x0000AA,
   0x5500FF,
   0x00AAFF
};

static void update(struct tm *t) {
   int h = t->tm_hour;
   int m = t->tm_min;
   int s = t->tm_sec;
   
   int mon = t->tm_mon;
   int day = t->tm_mday;
   
   update_time_buffer(h, m, s, time_buffer, TIME_SIZE);
   update_date_buffer(mon, day, date_buffer, DATE_SIZE);

   /* The color choices are all ugly
   int bg_index;
   if        (h < 2) {
      bg_index = 0;
   } else if (h < 5) {
      bg_index = 1;
   } else if (h < 8) {
      bg_index = 2;
   } else if (h < 11) {
      bg_index = 3;
   } else if (h < 14) {
      bg_index = 4;
   } else if (h < 17) {
      bg_index = 3;
   } else if (h < 20) {
      bg_index = 2;
   } else if (h < 23) {
      bg_index = 1;
   } else {
      bg_index = 0;
   }
   
   window_set_background_color(main_window, GColorFromHEX(BACKGROUND[bg_index]));
   */
   text_layer_set_text(time_layer, time_buffer);
   text_layer_set_text(date_layer, date_buffer);

}

static void tick_handler(struct tm *t, TimeUnits units_changed) {
   update(t);
}

static void main_window_load(Window *window) {
   // window setup
   Layer *window_layer = window_get_root_layer(window);
   GRect bounds = layer_get_bounds(window_layer);
   window_set_background_color(main_window, GColorFromHEX(0x000000));

   
   // time setup
   time_font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_ANONYMOUS_PRO_BOLD_24));
   
   time_layer = text_layer_create(
      GRect(3, 0, bounds.size.w - 3, bounds.size.h - SPLIT));
   
   text_layer_set_background_color(time_layer, GColorClear);
   text_layer_set_text_color(time_layer, GColorFromHEX(text_color));
   text_layer_set_font(time_layer, time_font);
   text_layer_set_text(time_layer, time_buffer);
   
   layer_add_child(window_layer, text_layer_get_layer(time_layer));
   
   
   // date setup
   date_layer = text_layer_create(
      GRect(0, bounds.size.h - SPLIT, bounds.size.w, bounds.size.h));
   
   text_layer_set_background_color(date_layer, GColorClear);
   text_layer_set_text_color(date_layer, GColorFromHEX(text_color));
   text_layer_set_font(date_layer, fonts_get_system_font(FONT_KEY_GOTHIC_14));
   text_layer_set_text_alignment(date_layer, GTextAlignmentCenter);
   text_layer_set_text(date_layer, date_buffer);
   
   layer_add_child(window_layer, text_layer_get_layer(date_layer));
}

static void main_window_unload(Window *window) {
   text_layer_destroy(time_layer);
   text_layer_destroy(date_layer);
   
   fonts_unload_custom_font(time_font);
}

static void init() {
   main_window = window_create();
   window_set_window_handlers(main_window, (WindowHandlers) {
      .load = main_window_load,
      .unload = main_window_unload
   });
   window_stack_push(main_window, true);
   
   // set current time and date on load
   time_t now = time(NULL);
   struct tm *t = localtime(&now);
   update(t);
   
   // subscribe to time changes
   tick_timer_service_subscribe(MINUTE_UNIT, tick_handler);
   
}

static void deinit() {
   window_destroy(main_window);
}

int main(void) {
   init();
   app_event_loop();
   deinit();
}