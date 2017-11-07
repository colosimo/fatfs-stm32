/*
 * Author: Aurelio Colosimo, 2016
 *
 * This file is part of kim-os project: https://github.com/colosimo/kim-os
 * According to kim-os license, you can do whatever you want with it,
 * as long as you retain this notice.
 */

#ifndef _LOG_H_
#define _LOG_H_

#include <kprint.h>
#include <basic.h>

#define V_NON 0 /* No log */
#define V_CRT 1 /* Log critical */
#define V_ERR 2 /* Log errors */
#define V_WRN 3 /* Log warnings */
#define V_LOG 4 /* Log normal behaviour */
#define V_DBG 5 /* Log debug */

#ifndef VERB
#define VERB V_LOG
#endif

#define crt(...) do { \
	if (VERB >= V_CRT) {kprint("[CRT] " __VA_ARGS__);}} while(0)

#define err(...) do { \
	if (VERB >= V_ERR) {kprint("[ERR] " __VA_ARGS__);}} while(0)

#define log(...) do { \
	if (VERB >= V_LOG) {kprint("[LOG] " __VA_ARGS__);}} while(0)

#define wrn(...) do { \
	if (VERB >= V_WRN) {kprint("[WRN] " __VA_ARGS__);}} while(0)

#define dbg(...) do { \
	if (VERB >= V_DBG) {kprint("[DBG] " __VA_ARGS__);}} while(0)

#endif /* _LOG_H_ */
