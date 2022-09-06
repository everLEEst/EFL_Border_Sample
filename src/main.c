#include <Elementary.h>
#include <appcore-efl.h>
#include "main.h"

static Elm_Theme *th = NULL;

void create_buttons(appdata *ad);

static Eina_Bool toggle = EINA_FALSE;

void
_height_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   appdata *ad = data;

   toggle = !toggle;
   if (toggle)
      evas_object_size_hint_min_set(ad->border, 0, 30);
   else
      evas_object_size_hint_min_set(ad->border, 0, 60);
}

void
_close_cb(void *data, Evas_Object *obj, void *event_info EINA_UNUSED)
{
   appdata *ad = data;
   dlog_print(DLOG_ERROR, LOG_TAG, "close click");
   elm_exit();
}

void
_max_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   appdata *ad = data;
   Eina_Bool max = elm_win_maximized_get(ad->win);
   dlog_print(DLOG_ERROR, LOG_TAG, "max click");
   elm_win_maximized_set(ad->win, !max);
}

void
_min_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   appdata *ad = data;
   Eina_Bool min = elm_win_iconified_get(ad->win);
   dlog_print(DLOG_ERROR, LOG_TAG, "min click");
   elm_win_iconified_set(ad->win, !min);
}

void
_border_cb(void *data, Evas_Object *obj EINA_UNUSED, void *event_info EINA_UNUSED)
{
   appdata *ad = data;
   Eina_Bool border = elm_win_borderless_get(ad->win);
   dlog_print(DLOG_ERROR, LOG_TAG, "min click");
   elm_win_borderless_set(ad->win, !border);
}

void create_buttons(appdata *ad)
{
   Evas_Object *btn;

   elm_box_clear(ad->bx2);

   btn = elm_button_add(ad->bx2);           
   elm_object_text_set(btn, "Change Border Height");   
   evas_object_smart_callback_add(btn, "clicked", _height_cb, ad);
   evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(btn);                
   elm_box_pack_end(ad->bx2, btn);          

   btn = elm_button_add(ad->bx2);      
   elm_object_text_set(btn, "Maximized");   
   evas_object_smart_callback_add(btn, "clicked", _max_cb, ad);
   evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(btn);                
   elm_box_pack_end(ad->bx2, btn);

   btn = elm_button_add(ad->bx2);      
   elm_object_text_set(btn, "Borderless");   
   evas_object_smart_callback_add(btn, "clicked", _border_cb, ad);
   evas_object_size_hint_weight_set(btn, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(btn, EVAS_HINT_FILL, EVAS_HINT_FILL);
   evas_object_show(btn);                
   elm_box_pack_end(ad->bx2, btn);
}

void create_content(appdata *ad)
{
   Evas_Object *bx, *bx2, *tb;

   ad->bx = bx =  elm_box_add(ad->win);
   evas_object_size_hint_weight_set(bx, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(bx, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_win_resize_object_add(ad->win, bx);
   evas_object_show(bx);

   ad->bx2 = bx2 = elm_box_add(bx);
   evas_object_size_hint_weight_set(bx2, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(bx2, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(bx, bx2);
   evas_object_show(bx2);

   create_buttons(ad);
}

void app_init(appdata *ad)
{
   Evas_Object *win, *bg;

   elm_theme_overlay_add(NULL, BODER_EDJ);

   elm_policy_set(ELM_POLICY_QUIT, ELM_POLICY_QUIT_LAST_WINDOW_CLOSED);

   ad->win = win = elm_win_add(NULL, "EFL-Border-Sample", ELM_WIN_UTILITY);

   // elm_win_floating_mode_set(win, EINA_TRUE);
   elm_win_autodel_set(win, EINA_TRUE);

   bg = elm_bg_add(win);                                                               
   elm_bg_color_set(bg, 200, 200, 200);
   evas_object_size_hint_weight_set(bg, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(bg, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_win_resize_object_add(win, bg);
   evas_object_show(bg);

   create_content(ad);

   Evas_Object *layout = elm_layout_add(win);
   if (!elm_layout_theme_set(layout, "layout", "border", "default"))
      dlog_print(DLOG_ERROR, LOG_TAG, "layout load fail");
   
   elm_object_part_content_set(win, "border.content", layout);
   evas_object_show(layout);

   Evas_Object *rect = evas_object_rectangle_add(evas_object_evas_get(layout));
   evas_object_size_hint_min_set(rect, 0, 60);
   evas_object_color_set(rect, 0, 0, 0, 0);
   evas_object_show(rect);
   elm_object_part_content_set(layout, "border.height", rect);
   ad->border = rect;

   Evas_Object *box = elm_box_add(layout);
   elm_box_horizontal_set(box, EINA_TRUE);
   elm_box_padding_set(box, 10, 0);
   elm_box_align_set(box, 1.0, 0.5);
   elm_object_part_content_set(layout, "elm.content", box);
   evas_object_show(box);

   /*Evas_Object *en = elm_entry_add(box);
   evas_object_size_hint_weight_set(en, EVAS_HINT_EXPAND, EVAS_HINT_EXPAND);
   evas_object_size_hint_align_set(en, EVAS_HINT_FILL, EVAS_HINT_FILL);
   elm_box_pack_end(box, en);
   evas_object_show(en);*/

   Evas_Object *min = elm_button_add(box);       
   evas_object_size_hint_weight_set(min, 0.0, 0.0);
   evas_object_size_hint_align_set(min, 1.0, 0.5);
   evas_object_smart_callback_add(min, "clicked", _min_cb, ad);
   elm_object_style_set(min, "border-min");   
   elm_box_pack_end(box, min);
   evas_object_show(min);

   Evas_Object *max = elm_button_add(box);       
   evas_object_size_hint_weight_set(max, 0.0, 0.0);
   evas_object_size_hint_align_set(max, 1.0, 0.5);
   evas_object_smart_callback_add(max, "clicked", _max_cb, ad);
   elm_object_style_set(max, "border-max");   
   elm_box_pack_end(box, max);
   evas_object_show(max);

   Evas_Object *close = elm_button_add(box);       
   evas_object_size_hint_weight_set(close, 0.0, 0.0);
   evas_object_size_hint_align_set(close, 1.0, 0.5);
   evas_object_smart_callback_add(close, "clicked", _close_cb, ad);
   elm_object_style_set(close, "border-close");   
   elm_box_pack_end(box, close);
   evas_object_show(close);

   evas_object_resize(win, 400, 300);
   evas_object_move(win, 100, 100);
   evas_object_show(win);
}

bool app_create(void *userdata)
{
   appdata *ad = userdata;

   app_init(ad);

   return true;
}

void app_terminate(void *user_data)
{
}

void show_border(void)
{
   const char *s;
   int borderState = 0;

   s = getenv("ELM_WIN_NO_BORDER");
   if (s) borderState = !atoi(s);

   dlog_print(DLOG_ERROR, LOG_TAG, "borderState %d",borderState);

   if (!borderState) unsetenv("ELM_WIN_NO_BORDER");
}

int main(int argc, char **argv)
{
   appdata app;
   memset(&app, 0, sizeof(app));

   show_border();

   struct appcore_ops ops = {
        .data = &app,
        .create = app_create,
        .terminate = app_terminate,
        .pause = NULL,
        .resume = NULL,
        .reset = NULL,
   };
   return appcore_efl_main("EFL-Border-Sample", &argc, &argv, &ops);
}

