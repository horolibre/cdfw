// Local Headers
#include "cdfw/core/debug.h"
#include "cdfw/core/arduino.h"

// Third Party Headers
#include <lvgl.h>

void lvgl_heap_report(void) {
  lv_mem_monitor_t mon;
  lv_mem_monitor(&mon);
  auto total = mon.total_size;
  auto free = mon.free_size;
  auto used = total - free;
  auto used_pct = mon.used_pct;
  auto max_used = mon.max_used;
  auto max_used_pct = (max_used * 100) / total;
  LV_LOG_INFO(
      "Heap Total: %zu, Free: %zu, Used: %zu (%d%%), Max Used: %zu (%zu%%)",
      total, free, used, used_pct, max_used, max_used_pct);
}

#ifdef ARDUINO
void esp32_heap_report(void) {
  auto total = ESP.getHeapSize();
  auto free = ESP.getFreeHeap();
  auto used = total - free;
  auto used_pct = (used * 100) / total;
  auto max_used = total - ESP.getMinFreeHeap();
  auto max_used_pct = (max_used * 100) / total;
  LV_LOG_INFO(
      "Heap Total: %zu, Free: %zu, Used: %zu (%d%%), Max Used: %zu (%zu%%)",
      total, free, used, used_pct, max_used, max_used_pct);
}
#endif // ARDUINO

void mem_report(void) {
  LV_LOG_INFO("### MEM REPORT ###");
  lvgl_heap_report();
#ifdef ARDUINO
  esp32_heap_report();
#endif // ARDUINO
}