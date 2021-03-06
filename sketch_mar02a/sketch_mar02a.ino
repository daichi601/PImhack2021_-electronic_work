#include <Adafruit_NeoPixel.h>
#include <MsTimer2.h>
#define LED_TAPE_PIN 9
#define LED_NUM_PIN 60
#define gun_trigger A0
#define INFRARED_PIN A1
#define TRIG_PIN 12
#define ECHO_PIN 11
#define SENSOR_DISTANCE_VOLTAGE 180
#define PERIOD_GAMING_TAPE 100

Adafruit_NeoPixel strip = Adafruit_NeoPixel(LED_NUM_PIN, LED_TAPE_PIN, NEO_GRB + NEO_KHZ800);
void gaming_tape(int gmaing_speed);
void sensor_system();

void setup() {
  static int IsFirst = true;
  strip.begin();
  /*LEDの初期化*/
  strip.show(); // Initialize all pixels to 'off'
  MsTimer2::set(PERIOD_GAMING_TAPE, gaming_tape);
}
int now_blink_led=0;
void loop() {
  unsigned long kyori;
  kyori = analogRead(INFRARED_PIN);
  Serial.println(kyori);
  if(kyori < SENSOR_DISTANCE_VOLTAGE){
   trigger_system(1000, 5000);
    MsTimer2::start();
    while(kyori <= SENSOR_DISTANCE_VOLTAGE){
      kyori = analogRead(INFRARED_PIN);
      }
     MsTimer2::stop();
  }
}
void gaming_tape(int gmaing_speed){
   for(int i=0;i<60;i++){
      int color_status=i/20;/*光らせる色の選択*/
      int red_power    = 0;/*赤の光の強度*/
      int green_power  = 0;/*緑の光の強度*/
      int blue_power   = 0;/*青の光の強度*/
      int color_power=i%20;/*光の強度*/
      switch (color_status){
      /*赤が明るくなって緑が暗くなる*/
      case 0:
        red_power = color_power*13+8;
        green_power = (19-color_power)*13+8;
        blue_power = 0;   
        break;  
      /*青が明るくなって赤が暗くなる*/
      case 1:
        red_power = (20-color_power)*13+8;
        green_power = 0;
        blue_power =    color_power*13+8;
        break;
      /*緑が明るくなって青が暗くなる*/
      case 2:
        red_power = 0;
        green_power = color_power*13+8;
        blue_power = (20-color_power)*13+8;
        break;
      }
      /*光らせるLEDの指定*/
      if(now_blink_led+i>59){
          strip.setPixelColor(now_blink_led+i-60, strip.Color(red_power,green_power,blue_power));
      }
      else{
         strip.setPixelColor(now_blink_led+i, strip.Color(red_power,green_power,blue_power));
      }
    }
    /*ＬＥＤの光らせる強度のＬＥＤへの反映 */
    strip.show();
    delay(50);
    /*先頭の色の変更*/
    now_blink_led++;
    /*60以上になるとリセット*/
    if(now_blink_led>60){
      now_blink_led=0;
    }  
}
void trigger_system(int jet_time,int waiting_time){
  pinMode(A0,OUTPUT);
  digitalWrite(gun_trigger,HIGH);/*噴射の入力*/
  delay(jet_time);
  digitalWrite(gun_trigger,LOW);/*噴射の入力をしない*/
  delay(waiting_time);
  }
