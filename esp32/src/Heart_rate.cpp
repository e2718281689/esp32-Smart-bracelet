#include "Heart_rate.h"
xinlu Xinlv;
heartdate* info_haert;
    lv_task_t *date_task;
    lv_task_t *main_page_task;
  LV_IMG_DECLARE(HeartRate_background);
  LV_IMG_DECLARE(i4);  
static lv_point_t line_points[12] = { {0, 0},{10, 0},  {20, 0}, 
                                      {30, 0},{40, 0} ,{50, 0},
                                      {60, 0},{70, 0} ,{80, 0},
                                      {90, 0},{100, 0} ,{110, 0}};
int sum=0;

  LV_IMG_DECLARE(HeartRate_background);
  LV_IMG_DECLARE(i4);  
   lv_obj_t *label ;

static void renew_date(lv_task_t *param)
{
    
    info_haert=Xinlv.heartRate();
    String awe=(String)(rand()%10+80);
    line_points[11].y=(((info_haert->IR)-100000)/100)-20;
    for (int i = 0; i < 11; i++)
    {
        line_points[i].y=line_points[i+1].y;
         Serial.printf("%d \n",line_points[i].y);
    }
    Serial.printf("%d \n",((info_haert->IR)-100000)/100);
    // char asd[3]="80";
    // asd[1]=(char)48;
    // Serial.printf("dfgdfgdf %s dfgdfgdf\n",asd);
}
static void main_page(lv_task_t *param)
{

    /*Create style*/
    static lv_style_t style_line;
    static lv_obj_t* bground;
    bground=lv_img_create(lv_scr_act(),NULL);
    lv_img_set_src(bground, &HeartRate_background);
    lv_obj_align(bground, NULL, LV_ALIGN_CENTER, 0, 0);
    lv_style_init(&style_line);
    lv_style_set_line_width(&style_line, LV_STATE_DEFAULT, 3);
    lv_style_set_line_color(&style_line, LV_STATE_DEFAULT, LV_COLOR_BLUE);
    lv_style_set_line_rounded(&style_line, LV_STATE_DEFAULT, true);
    /*Create a line and apply the new style*/
    lv_obj_t * line1;
    line1 = lv_line_create(bground, NULL);
    lv_line_set_y_invert(line1, true);
    lv_line_set_points(line1, line_points, 12);     /*Set the points*/
    lv_obj_add_style(line1, LV_LINE_PART_MAIN, &style_line);     /*Set the points*/
    lv_obj_align(line1, bground,  LV_ALIGN_IN_BOTTOM_LEFT, 0, -55);
     label = lv_obj_create(bground, NULL);
      static lv_style_t style_arc_bg;
    lv_style_init(&style_arc_bg);
    lv_obj_set_size(label,40,40);
    // lv_style_set_bg_color(&style_arc_bg, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_style_set_line_width(&style_arc_bg, LV_STATE_DEFAULT, 4);
    // lv_style_set_line_color(&style_arc_bg, LV_STATE_DEFAULT, LV_COLOR_BLACK);
    // lv_style_set_border_width(&style_arc_bg, LV_STATE_DEFAULT, 0);


    lv_obj_set_style_local_value_str(label, LV_ARC_PART_BG, LV_STATE_DEFAULT,"心率图");
    lv_style_set_value_font(&style_arc_bg, LV_STATE_DEFAULT, &lv_font_montserrat_40);
    lv_style_set_value_color(&style_arc_bg, LV_STATE_DEFAULT, LV_COLOR_CYAN);
    lv_style_set_value_align(&style_arc_bg, LV_STATE_DEFAULT, LV_ALIGN_CENTER);
    lv_obj_add_style(label, LV_ARC_PART_INDIC, &style_arc_bg);
     lv_obj_align(label, bground, LV_ALIGN_IN_BOTTOM_LEFT, 10, -5);
     
 // lv_obj_set_style_local_value_str(label, LV_ARC_PART_BG, LV_STATE_DEFAULT,(String)(rand()%10+80).str_c());

}
void Heart_rate_init(lv_task_t *param)
{
    Xinlv.Init();
    renew_date(NULL);
    main_page(NULL);
    lv_task_handler();
    date_task=lv_task_create(main_page,1000,LV_TASK_PRIO_HIGH,NULL);
    main_page_task=lv_task_create(renew_date,5,LV_TASK_PRIO_MID,NULL);
}