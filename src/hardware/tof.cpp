#include "tof.h"
#include <Wire.h>
#include "system/systemResources.h"

// Define sensor objects
VL53L4CD sensor_front(&Wire, XSHUT_FRONT);
VL53L4CD sensor_r90(&Wire, XSHUT_RIGHT90);
VL53L4CD sensor_r45(&Wire, XSHUT_RIGHT45);
VL53L4CD sensor_l45(&Wire, XSHUT_LEFT45);
VL53L4CD sensor_l90(&Wire, XSHUT_LEFT90);

// Define arrays (definitions for extern declarations in tof.h)
VL53L4CD *SENSORS[NUM_TOF] = {&sensor_front, &sensor_r90, &sensor_r45, &sensor_l45, &sensor_l90};
const int XSHUTS[NUM_TOF] = {XSHUT_FRONT, XSHUT_RIGHT90, XSHUT_RIGHT45, XSHUT_LEFT45, XSHUT_LEFT90};
const char *NAMES[NUM_TOF] = {"Front", "Right 90", "Right 45", "Left 45", "Left 90"};
const uint8_t ADDR8[NUM_TOF] = {ADDR_FRONT_8B, ADDR_RIGHT90_8B, ADDR_RIGHT45_8B, ADDR_LEFT45_8B, ADDR_LEFT90_8B};
const uint16_t BUDGET_MS[NUM_TOF] = {BUDGET_MS_DEFAULT, BUDGET_MS_DEFAULT, BUDGET_MS_DEFAULT, BUDGET_MS_DEFAULT, BUDGET_MS_DEFAULT};
const uint16_t PERIOD_MS[NUM_TOF] = {PERIOD_FRONT_MS, PERIOD_LEFT90_MS, PERIOD_RIGHT45_MS, PERIOD_LEFT45_MS, PERIOD_RIGHT90_MS};
const uint8_t POLL_ORDER[NUM_TOF] = {IDX_FRONT, IDX_RIGHT90, IDX_RIGHT45, IDX_LEFT45, IDX_LEFT90};
const uint8_t START_ORDER[NUM_TOF] = {IDX_FRONT, IDX_RIGHT90, IDX_RIGHT45, IDX_LEFT45, IDX_LEFT90};

static void allXshutLow()
{
  for (int i = 0; i < NUM_TOF; ++i)
  {
    pinMode(XSHUTS[i], OUTPUT);
    digitalWrite(XSHUTS[i], LOW);
  }
}

// Bring up exactly one sensor
static bool bringUpOne(int idx)
{
  pinMode(XSHUTS[idx], OUTPUT);
  digitalWrite(XSHUTS[idx], LOW);
  delay(5);
  digitalWrite(XSHUTS[idx], HIGH);
  delay(5);
  xSemaphoreTake(g_i2cMutex, portMAX_DELAY);
  bool ok = (SENSORS[idx]->begin() == 0);
  xSemaphoreGive(g_i2cMutex);
  if (!ok)
    Serial.printf("[ERR] %s.begin()\n", NAMES[idx]);
  return ok;
}

// Set address and CONTINUOUS timing (period >= budget)
static bool setAddrContinuous(int idx, uint8_t addr8)
{
  xSemaphoreTake(g_i2cMutex, portMAX_DELAY);
  VL53L4CD *s = SENSORS[idx];
  bool ok = true;
  s->VL53L4CD_Off();
  if (ok && s->InitSensor(addr8) != 0)
  {
    Serial.printf("[ERR] %s.InitSensor(8b=0x%02X)\n", NAMES[idx], addr8);
    ok = false;
  }
  if (ok)
    s->VL53L4CD_SetRangeTiming(BUDGET_MS[idx], PERIOD_MS[idx]); // continuous
  xSemaphoreGive(g_i2cMutex);
  if (ok)
  {
    Serial.printf("[OK] %s -> 8b=0x%02X (7b=0x%02X), budget=%ums, period=%ums\n",
                  NAMES[idx], addr8, addr8 >> 1, BUDGET_MS[idx], PERIOD_MS[idx]);
  }
  return ok;
}

void initTofSensors()
{
  Serial.println("Initializing ToF sensors...");

  // Check if mutex was created by systemResources
  if (g_i2cMutex == nullptr)
  {
    Serial.println("[ERR] I2C mutex not initialized! Call initSystemResources() first.");
    return;
  }

  // Initialize I2C if not already done
  if (!Wire.begin())
  {
    Serial.println("[ERR] Failed to initialize I2C!");
    return;
  }

  // All XSHUT low
  allXshutLow();
  delay(10);

  // Bring up each sensor in sequence, set address and timing
  for (int i = 0; i < NUM_TOF; ++i)
  {
    if (!bringUpOne(START_ORDER[i]))
    {
      Serial.printf("[ERR] Failed to bring up %s\n", NAMES[START_ORDER[i]]);
      continue;
    }
    if (!setAddrContinuous(START_ORDER[i], ADDR8[START_ORDER[i]]))
    {
      Serial.printf("[ERR] Failed to configure %s\n", NAMES[START_ORDER[i]]);
      continue;
    }
    delay(10);
  }

  // Start continuous ranging on all sensors with slight phase offsets
  // (Not strictly required since periods differ, but it helps avoid rare alignments)
  for (uint8_t i = 0; i < NUM_TOF; ++i)
  {
    int idx = START_ORDER[i];
    xSemaphoreTake(g_i2cMutex, portMAX_DELAY);
    SENSORS[idx]->VL53L4CD_StartRanging();
    xSemaphoreGive(g_i2cMutex);
    // keep RIGHT90 & LEFT90 farther apart on start
    if (idx == IDX_RIGHT90)
      delay(8); // extra gap before LEFT90 starts
    else
      delay(2);
  }

  Serial.println("ToF sensors initialized.");
}
