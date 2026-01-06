#include <WiFi.h>
#include <time.h>
#include <Adafruit_NeoPixel.h>
#include <WiFiManager.h>
#include <nvs_flash.h>

#define LED_PIN     4
#define NUM_MODULES 42
#define LEDS_PER_MODULE 3
#define NUM_LEDS    (NUM_MODULES * LEDS_PER_MODULE)
#define BUTTON_PIN  5

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_RGB + NEO_KHZ800);

const char* tz = "CET-1CEST,M3.5.0,M10.5.0/3";

int hourNow, minuteNow, houranzeigen;
uint32_t Lichtfarbe;

WiFiManager wm;


// ----------- Arrays für Stunden -----------
struct HourLEDs { int start; int end; };
struct MinuteLEDs { int start; int end; };

struct HourSpecial { HourLEDs before5; HourLEDs after5; };

const HourSpecial hours[12] = {
  {{60,62},{59,62}},  // 1
  {{61,64},{61,64}},  // 2
  {{44,47},{44,47}},  // 3
  {{32,35},{32,35}},  // 4
  {{50,53},{50,53}},  // 5
  {{15,19},{15,19}},  // 6
  {{54,59},{54,59}},  // 7
  {{22,25},{22,25}},  // 8
  {{36,39},{36,39}},  // 9
  {{26,29},{26,29}},  //10
  {{40,42},{40,42}},  //11
  {{70,74},{70,74}}   //12
};

// ----------- Arrays für Minuten (max 3 Bereiche) -----------
struct MinuteMulti { MinuteLEDs leds[3]; int count; };
const MinuteMulti minutes[12] = {
  {{{10,12}},1},                       // 0-4
  {{{116,119},{81,84}},2},             // 5-9
  {{{105,108},{81,84}},2},             //10-14
  {{{91,97},{81,84}},2},               //15-19
  {{{98,104},{81,84}},2},              //20-24
  {{{116,119},{78,80},{65,68}},3},     //25-29
  {{{65,68}},1},                        //30-34
  {{{116,119},{81,84},{65,68}},3},     //35-39
  {{{98,104},{78,80}},2},              //40-44
  {{{87,97}},1},                        //45-49
  {{{105,108},{78,80}},2,},            //50-54
  {{{116,119},{78,80}},2}              //55-59
};

// ----------- "Es ist" -----------
const int esIst[5] = {109,110,112,113,114};

// ----------- Setup & Loop -----------
void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT);
  if (digitalRead(BUTTON_PIN) == HIGH) { 
    Serial.println("Button gedrückt, NVS löschen...");
    nvs_flash_erase();
    nvs_flash_init();
    Serial.println("NVS komplett gelöscht!");
  }

  strip.begin();
  strip.clear();
  strip.setBrightness(100);
  strip.show();


  // WLAN
  if (!wm.autoConnect("ESP_Config","12345678")) {
    Serial.println("Fehler beim Verbinden, Neustart...");
    ESP.restart();
  }
  Serial.println("Mit WLAN verbunden! IP: " + WiFi.localIP().toString());

  configTzTime(tz,"pool.ntp.org","time.nist.gov");
  waitForTime();

  updateTimeVariables();
  updateLichtfarbe();
  updateLEDs();
}

void loop() {
  static int lastMin = -1;
  struct tm timeinfo;
  if(getLocalTime(&timeinfo)){
    if(timeinfo.tm_min != lastMin && timeinfo.tm_sec==0){
      lastMin = timeinfo.tm_min;
      updateTimeVariables();
      updateLichtfarbe();
      updateLEDs();
      Serial.printf("Uhrzeit: %02d:%02d\n", hourNow, minuteNow);
    }
  }
}

// ----------- Hilfsfunktionen -----------
void waitForTime(){
  struct tm timeinfo;
  while(!getLocalTime(&timeinfo)){
    Serial.println("Warte auf Zeit...");
    delay(1000);
  }
}

void updateTimeVariables(){
  struct tm timeinfo;
  getLocalTime(&timeinfo);
  hourNow = timeinfo.tm_hour;
  minuteNow = timeinfo.tm_min;

  houranzeigen = hourNow;
  if(minuteNow>24) houranzeigen++;
  if((houranzeigen>12 && houranzeigen<14) || houranzeigen>24) houranzeigen=1;
}

void updateLichtfarbe(){
  if(hourNow<6 || hourNow>=22)
    Lichtfarbe=strip.Color(38,33,27);
  else
    Lichtfarbe=strip.Color(255,220,180);
}

void updateLEDs(){
  strip.clear();
  showEsIst();
  showHour();
  showMinute();
  strip.show();
}

void showEsIst(){
  for(int i=0;i<5;i++) strip.setPixelColor(esIst[i],Lichtfarbe);
}

void showHour(){
  int h = (houranzeigen-1)%12;
  HourLEDs leds = (minuteNow<5)?hours[h].before5:hours[h].after5;
  setModuleColor(leds.start, leds.end, Lichtfarbe);
}

void showMinute(){
  int idx = minuteNow/5;
  for(int i=0;i<minutes[idx].count;i++){
    setModuleColor(minutes[idx].leds[i].start, minutes[idx].leds[i].end, Lichtfarbe);
  }
}

void setModuleColor(int start,int end,uint32_t color){
  for(int i=start;i<=end;i++) strip.setPixelColor(i,color);
}
