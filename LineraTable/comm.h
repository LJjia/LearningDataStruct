//
// Created by LJjia on 2021-08-14.
//



#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/types.h>
/*stdint.h包含uint32_t这种*/
#include <stdint.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <pthread.h>
#include <stdarg.h>

#ifndef LINERATABLE_COMM_H
#define LINERATABLE_COMM_H


#ifdef __cplusplus
extern "C"{
#endif


#define True 1
#define False 0
#define OK 0
#define FAILED -1

#define CHECK_PARAM(con,ret) if(con){return ret;}









// 颜色宏


#define NORMAL		22      /*正常字体*/
#define RESET		0       /*还原*/
#define BOLD		1       /*加粗*/
#define UNDERLINE	4       /*下划线*/
#define BLINK		5       /*闪烁*/

/*前景色,前景色部分实际数值是30+,而且前景色使用字符串表示,这里取个位数*/
#define PT_BLACK	0
#define PT_RED		1
#define PT_GREEN	2
#define PT_YELLOW	3
#define PT_BLUE		4
#define PT_MAGENTA	5 /* 品红 R207 G0 B112 */
#define PT_CYAN		6 /* 青色   */
#define PT_WHITE	7

/* 背景色 和前景色类似,这里取个位数 */
#define PT_BG_NULL
#define PT_BG_BLACK		0
#define PT_BG_RED		1
#define PT_BG_GREEN		2
#define PT_BG_YELLOW	3
#define PT_BG_BLUE		4
#define PT_BG_MAGENTA	5
#define PT_BG_CYAN		6
#define PT_BG_WHITE		7

#define PT_COLOR_BUF_LEN 1024

void _print_color_withBG(int attr, int fg_color, int bg_color, const char *fmt, ...);
void _print_color(int attr, int color, const char *fmt, ...);


#define PRINT(fmt, ...)				printf("[LJjia]: %s:%s:%u ", __FILE__, __FUNCTION__, __LINE__); _print_color(NORMAL, PT_GREEN, fmt, ## __VA_ARGS__); printf("\n");
/*不带背景色的打印*/
#define print_color(attr, color, fmt, ...) _print_color(attr, color, fmt, ## __VA_ARGS__)
/*带背景色的打印*/
#define print_color_bg(attr, color, bg, fmt, ...) _print_color_withBG(attr, color, bg, fmt, ## __VA_ARGS__)

#define PRINT_MODE(level, fmt, ...) printf("[LJjia]: %s:%s:%u ", __FILE__, __FUNCTION__, __LINE__); _print_color(NORMAL, level, fmt, ## __VA_ARGS__); printf("\n");

#ifdef __cplusplus
}
#endif



#endif //LINERATABLE_COMM_H
