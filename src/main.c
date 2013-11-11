#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"
#include "words.h"


#define MY_UUID { 0x24, 0x2B, 0x9F, 0x04, 0xCE, 0x2F, 0x41, 0xF5, 0xB5, 0xBD, 0xFF, 0xDD, 0x9A, 0x8F, 0x93, 0x28 }
PBL_APP_INFO(MY_UUID,
             "SweFuzzy", "Erik Thuning",
             1, 0, /* App version */
             RESOURCE_ID_IMAGE_MENU_ICON,
             APP_INFO_WATCH_FACE);

#define BUFFER_SIZE 86

static struct CommonData {
	TextLayer label;
	Window window;
	char buffer[BUFFER_SIZE];
} common;

void update_time(PblTm* t) {
	build_time_string(t->tm_hour, t->tm_min, t->tm_sec, common.buffer, BUFFER_SIZE);
	text_layer_set_text(&common.label, common.buffer);
}

void handle_init(AppContextRef ctx) {
  
  resource_init_current_app(&APP_RESOURCES);
  
  window_init(&common.window, "SweFuzzy");
  const bool animated = true;
  window_stack_push(&common.window, animated);

  window_set_background_color(&common.window, GColorBlack);
  GFont font = fonts_load_custom_font(resource_get_handle(RESOURCE_ID_ANONYMOUS_PRO_BOLD_28));

  text_layer_init(&common.label, GRect(0, 5, common.window.layer.frame.size.w, common.window.layer.frame.size.h-5));
  text_layer_set_background_color(&common.label, GColorBlack);
  text_layer_set_text_color(&common.label, GColorWhite);
  text_layer_set_font(&common.label, font);
  layer_add_child(&common.window.layer, &common.label.layer);

  PblTm t;
  get_time(&t);
  update_time(&t);
}

void handle_tick(AppContextRef ctx, PebbleTickEvent *event) {
	update_time(event->tick_time);
}

void pbl_main(void *params) {
  PebbleAppHandlers handlers = {
    .init_handler = &handle_init,
	.tick_info = {
		.tick_handler = &handle_tick,
		.tick_units = MINUTE_UNIT
	}
  };
  app_event_loop(params, &handlers);
}
