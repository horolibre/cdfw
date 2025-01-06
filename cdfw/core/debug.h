// Copyright (c) 2025 Ian Dinwoodie. All rights reserved.
// Use of this source code is governed by a GPLv3 license that can be found in
// the LICENSE file.

#ifndef CDFW_CORE_DEBUG_H
#define CDFW_CORE_DEBUG_H

void lvgl_heap_report(void);
#ifdef ARDUINO
void esp32_heap_report(void);
#endif // ARDUINO
void mem_report(void);

#endif // CDFW_CORE_DEBUG_H
