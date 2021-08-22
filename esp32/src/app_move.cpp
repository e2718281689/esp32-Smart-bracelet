
#include "app_move.h"
 #include <lvgl.h>
 #include <imu.h>
lv_obj_t *pre_app_image;
lv_obj_t *now_app_image;
lv_obj_t *app_scr;
lv_obj_t *back_ground;
LV_IMG_DECLARE(app_bilibili);
  LV_IMG_DECLARE(app_hardware_info);
  LV_IMG_DECLARE(app_loading);
  LV_IMG_DECLARE(app_movie);
  LV_IMG_DECLARE(app_movie2);
  LV_IMG_DECLARE(app_picture);
  LV_IMG_DECLARE(app_screen);
  LV_IMG_DECLARE(app_server);
  LV_IMG_DECLARE(app_weather);
 Imu_Action *imu_info;
lv_img_dsc_t img[15]={app_bilibili,app_hardware_info,app_loading,app_movie,app_movie2,app_picture,app_screen,app_server,app_weather};
int img_sum=2;
IMU imu;
int new_app=0;
void app_move(int vec)
{
      int now_end_x;
      int now_start_x;
      int old_start_x; 
      int old_end_x  ;
    now_app_image = lv_img_create(app_scr, NULL);
    lv_img_set_src(now_app_image, &(img[img_sum]));
    lv_obj_align(now_app_image, app_scr, LV_ALIGN_CENTER, 0, 0);

    pre_app_image = lv_img_create(app_scr, NULL);
    lv_img_set_src(pre_app_image, &(img[img_sum+1]));
    lv_obj_align(pre_app_image, app_scr, LV_ALIGN_CENTER, 0, 0);
  if(vec==TURN_LEFT)
  {
       now_start_x=130;
       now_end_x=0;
       old_start_x = 0;
       old_end_x = -130;
  }
  else if(vec==TURN_RIGHT) {
       now_end_x=130;
       now_start_x=0;
       old_start_x = -130;
       old_end_x = 0;
  }

    
    lv_anim_path_t path;
    lv_anim_path_init(&path);
    lv_anim_path_set_cb(&path, lv_anim_path_ease_out);

    lv_anim_t now_app;
    lv_anim_init(&now_app);
    lv_anim_set_exec_cb(&now_app, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_var(&now_app, now_app_image);
    lv_anim_set_values(&now_app, now_start_x, now_end_x);

     uint32_t duration = lv_anim_speed_to_time(50, now_start_x, now_end_x); // 计算时间
    lv_anim_set_time(&now_app, duration);
    lv_anim_set_path(&now_app, &path); // Default is linear

    lv_anim_t pre_app;
    lv_anim_init(&pre_app);
    lv_anim_set_exec_cb(&pre_app, (lv_anim_exec_xcb_t)lv_obj_set_x);
    lv_anim_set_var(&pre_app, pre_app_image);
    lv_anim_set_values(&pre_app, old_start_x, old_end_x);

    duration = lv_anim_speed_to_time(50, old_start_x, old_end_x); // 计算时间
    lv_anim_set_time(&pre_app, duration);
    lv_anim_set_path(&pre_app, &path); // Default is linear
    lv_anim_start(&pre_app);
    lv_anim_start(&now_app);
    // lv_obj_del(pre_app_image); 
}

void app_init()
{
  // lv_obj_t *act_obj = lv_scr_act(); 
  //   lv_obj_clean(act_obj); // 清空此前页面
  //   pre_app_image = lv_img_create(app_scr, NULL);
  //   lv_img_set_src(pre_app_image, &i6);
  //   lv_obj_align(pre_app_image, NULL, LV_ALIGN_CENTER, 0, 0);
  //   //lv_scr_load_anim(app_scr, LV_SCR_LOAD_ANIM_NONE, 300, 300, false);
  //   lv_task_handler();

  imu.init();
  imu.mpuint();
    app_scr = lv_obj_create(lv_scr_act(), NULL);
    lv_obj_set_size(app_scr,130,130);
    lv_obj_align(app_scr, NULL, LV_ALIGN_CENTER, 2, 1);
    now_app_image = lv_img_create(app_scr, NULL);

    pre_app_image = lv_img_create(app_scr, NULL);

    


}
void app_loop()
{
  imu.update(200);
  if (imu.action_info.active!=new_app)
  {
    if (imu.action_info.active==TURN_RIGHT)
    {  
      lv_obj_del(pre_app_image);
      lv_obj_del(now_app_image);
      app_move(TURN_RIGHT);
      img_sum+=1;
    }
    else if(imu.action_info.active==TURN_LEFT)
    {
      lv_obj_del(pre_app_image);
      lv_obj_del(now_app_image);
      img_sum-=1; 
      app_move(TURN_LEFT);   
    }
    if(imu.action_info.active==UNKNOWN)
    {

    }
    new_app=imu.action_info.active;
    Serial.printf("%d %d \n",new_app,imu.action_info.active);
    while(lv_task_handler());
  }
  

  

}