// #include <WiFi.h>
#include "lvgl.h"
#include "App_time.h"
#include "Arduino.h"
// #include "time.h"
// #include <NTPClient.h>
// const char *ssid ="MERCURY_6BFC";    //你的网络名称
// const char *password ="02121033"; //你的网络密码

const char *ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 8 * 3600;
const int daylightOffset_sec = 0;


// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "ntp1.aliyun.com",60*60*8, 30*60*1000);
static lv_obj_t* sum;
  static lv_obj_t* sum1;
  static lv_obj_t* sum2;
  static lv_obj_t* sum3;
  
  static  lv_obj_t* background;
  static lv_obj_t* tiime;
  static lv_style_t time_style;
 

  LV_IMG_DECLARE(ground); 
  LV_IMG_DECLARE(i0);
  LV_IMG_DECLARE(i1);
  LV_IMG_DECLARE(i2);
  LV_IMG_DECLARE(i3);
  LV_IMG_DECLARE(i4);
  LV_IMG_DECLARE(i5);
  LV_IMG_DECLARE(i6);
  LV_IMG_DECLARE(i7);
  LV_IMG_DECLARE(i8);
  LV_IMG_DECLARE(i9);
  char time_now[6]="16:00";
  int time_hour=16;
  int time_sin=00;
  lv_img_dsc_t  summou_img[10]={i0,i1,i2,i3,i4,i5,i6,i7,i8,i9};
void app_time_upte()
{
  if(time_sin==60)
  {
    time_hour++;
    time_sin=0;
  }
  if(time_hour==24)
  {
    time_hour=0;
  }
//   lv_obj_del(background);
  delay(1000);
  Serial.printf("%d %d \n",time_hour,time_sin);
  lflf(NULL,time_hour%10,time_hour/10,time_sin%10,time_sin/10);
    time_sin++;
}
void lflf(lv_task_t *param,int a,int b,int c,int d)
{
  (void) param; 


  lv_style_init(&time_style);
  lv_style_set_bg_opa(&time_style, LV_STATE_DEFAULT, LV_OPA_20);//本体不透明度
  lv_style_set_border_width(&time_style, LV_STATE_DEFAULT, 2);//边框
  lv_style_set_border_color(&time_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//边框颜色    
  //lv_style_set_clip_corner(&time_style, 0, true);
  lv_style_set_radius(&time_style, 0, 10);//圆角
  lv_style_set_bg_color(&time_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//本体颜色
  lv_style_set_border_color(&time_style, LV_STATE_DEFAULT, LV_COLOR_BLACK);//边框颜色
  background = lv_img_create(lv_scr_act(), NULL);
  lv_img_set_src(background, &ground);
  lv_obj_set_size(background,130,130);
  tiime=lv_obj_create(background,NULL);
  lv_obj_set_click(tiime,false);
  lv_obj_set_size(tiime,100,100);
  lv_obj_align(tiime,background,LV_ALIGN_CENTER,0,0);
  lv_obj_set_style_local_value_color(tiime,LV_ARC_PART_BG, LV_STATE_DEFAULT,LV_COLOR_RED);
  //lv_obj_set_style_local_value_str(time, LV_ARC_PART_BG, LV_STATE_DEFAULT, "80:80");
  sum= lv_img_create(tiime, NULL);
  sum1= lv_img_create(tiime, NULL);
  sum2= lv_img_create(tiime, NULL);
  sum3= lv_img_create(tiime, NULL);
  lv_img_set_src(sum,&summou_img[a]);
  lv_img_set_src(sum1, &summou_img[b]);
  lv_img_set_src(sum2, &summou_img[c]);
  lv_img_set_src(sum3, &summou_img[d]);
  lv_obj_add_style(tiime,LV_OBJ_PART_MAIN,&time_style);
  lv_obj_align(sum,tiime,LV_ALIGN_CENTER,15,-20);
  lv_obj_align(sum1,tiime,LV_ALIGN_CENTER,-15,-20);
  lv_obj_align(sum2,tiime,LV_ALIGN_CENTER,15,20);
  lv_obj_align(sum3,tiime,LV_ALIGN_CENTER,-15,20);
}
