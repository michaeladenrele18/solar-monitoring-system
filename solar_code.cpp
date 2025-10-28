// ===== Panel (A1) + Battery (A0) Sense — Long-Settling ADC =====
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// --- Analog inputs ---
const int AIN_BATT  = A0;  // battery divider node (through ~1k series)
const int AIN_PANEL = A1;  // panel  divider node (through ~1k series)

// --- ADC reference (measure Arduino 5V rail with DMM) ---
float VREF = 4.960f;  // example: 4.960 V

// --- PANEL divider (measured resistors) ---
const float RTOP_P_OHMS = 100200.0f;             // 100.2k
const float RBOT_P_OHMS = 9950.0f + 9960.0f;     // 19.91k
const float SCALE_P     = (RTOP_P_OHMS + RBOT_P_OHMS) / RBOT_P_OHMS; // ≈ 6.03265

// --- BATTERY divider (measured resistors) ---
const float RTOP_B_OHMS = 100000.0f;             // 100k
const float RBOT_B_OHMS = 1005.0f + 999.0f + 9970.0f + 9930.0f; // 21.904k
const float SCALE_B     = (RTOP_B_OHMS + RBOT_B_OHMS) / RBOT_B_OHMS; // ≈ 5.565376

// --- High-impedance friendly ADC read (extra settle + averaging) ---
int readADCHiZ(int pin, int N = 64) {
  // several dummy conversions with long settle for high-impedance divider
  for (int i = 0; i < 6; ++i) {
    analogRead(pin);
    delayMicroseconds(2000);
  }
  long sum = 0;
  for (int i = 0; i < N; ++i) {
    delayMicroseconds(2000);
    sum += analogRead(pin);
  }
  return (int)(sum / N);
}

void setup() {
  Serial.begin(9600);           // Match Serial Monitor to 9600 baud
  analogReference(DEFAULT);     // Use 5V rail as ADC reference
  lcd.begin(16, 2);

  lcd.clear(); lcd.print("Solar Monitor");
  lcd.setCursor(0,1); lcd.print("Warming up...");
  delay(5000);
  lcd.clear();

  // One-time Serial calibration banner
  Serial.println(F("=== Panel & Battery Sense ==="));
  Serial.print(F("VREF=")); Serial.print(VREF,3); Serial.println(F(" V"));
  Serial.print(F("SCALE_P=")); Serial.print(SCALE_P,4);
  Serial.print(F("  SCALE_B=")); Serial.println(SCALE_B,4);
  Serial.println(F("Columns: Vpanel[V], Vbatt[V]"));
}

void loop() {
  // ---- PANEL (A1) ----
  int   rawP    = readADCHiZ(AIN_PANEL, 64);
  float v_nodeP = (rawP * VREF) / 1023.0f;
  float v_panel = v_nodeP * SCALE_P;

  // ---- BATTERY (A0) ----
  int   rawB    = readADCHiZ(AIN_BATT, 64);
  float v_nodeB = (rawB * VREF) / 1023.0f;
  float v_batt  = v_nodeB * SCALE_B;

  // ---- Serial: only scaled voltages ----
  Serial.print(v_panel, 3); Serial.print(", ");
  Serial.println(v_batt, 3);

  // ---- LCD: display both scaled voltages ----
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Panel: "); lcd.print(v_panel, 1); lcd.print("V");
  lcd.setCursor(0,1);
  lcd.print("Batt:  "); lcd.print(v_batt, 1); lcd.print("V");

  delay(1000);  // 1 s refresh
}
