#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <lvgl.h>
#include <zmk/display.h>
#include <zmk/display/status_screen.h>
#include <zmk/scanner_core.h>

LOG_MODULE_REGISTER(display_screen, LOG_LEVEL_INF);

static lv_obj_t *screen_obj = NULL;
static lv_obj_t *name_label = NULL;
static lv_obj_t *layer_label = NULL;
static lv_obj_t *bat_label = NULL;

static void update_cb(lv_timer_t *timer) {
    struct pending_display_data data;
    if (scanner_get_pending_update(&data)) {
        if (name_label) lv_label_set_text(name_label, data.device_name);
        char layer_buf[16];
        snprintf(layer_buf, sizeof(layer_buf), "Layer: %d", data.layer);
        if (layer_label) lv_label_set_text(layer_label, layer_buf);
        char bat_buf[16];
        snprintf(bat_buf, sizeof(bat_buf), "Bat: %d%%", data.bat[0]);
        if (bat_label) lv_label_set_text(bat_label, bat_buf);
    }
}

lv_obj_t *zmk_display_status_screen(void) {
    screen_obj = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen_obj, lv_color_black(), LV_PART_MAIN);

    name_label = lv_label_create(screen_obj);
    lv_obj_align(name_label, LV_ALIGN_TOP_MID, 0, 4);
    lv_label_set_text(name_label, "Waiting...");

    layer_label = lv_label_create(screen_obj);
    lv_obj_align(layer_label, LV_ALIGN_CENTER, 0, -8);
    lv_label_set_text(layer_label, "Layer: -");

    bat_label = lv_label_create(screen_obj);
    lv_obj_align(bat_label, LV_ALIGN_BOTTOM_MID, 0, -4);
    lv_label_set_text(bat_label, "Bat: --%");

    lv_timer_create(update_cb, 200, NULL);
    return screen_obj;
}