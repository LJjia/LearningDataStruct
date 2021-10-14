/**
 * @Author: JialiangJun
 * @Description:
 * @Date: Created on 15:29 2021-08-14.
 * @Modify:
 */



#include "comm.h"
/*******************************************************************************

   Function:		my_vprint

   Author:		jialiangjun

   Description: 完成颜色头尾信息以及可变参数填充后,最后输出字符串的函数

   Input:
    @fmt        待输出的字符串指针
    @va_args    可变参数列表

   Output:		N/A

   Return:
    0:			Successful
    ohters:		Failed

*******************************************************************************/
static void my_vprint(char *fmt, va_list va_args) {
    char buffer[PT_COLOR_BUF_LEN] = {0};

    vsnprintf(buffer, PT_COLOR_BUF_LEN - 1, fmt, va_args);
    /* printf("%s", buffer); */

    printf("%s", buffer);
}

/*******************************************************************************

   Function:		_print_color

   Author:		jialiangjun

   Description:

   Input:
    @attr   字体
    @color  颜色
    @fmt    类似printf的打印buff

   Output:		N/A

   Return:
    0:			Successful
    ohters:		Failed

*******************************************************************************/
void _print_color(int attr, int color, const char *fmt, ...) {
    char buffer[PT_COLOR_BUF_LEN] = {0};
    va_list marker;

    va_start(marker, fmt);

    /* 背景色为0时，不影响后面的信息，其它值会影响 */
    snprintf(buffer, PT_COLOR_BUF_LEN - 1, "\x1b[%d;%dm%s\x1b[0m", color + 30, attr, fmt);
    my_vprint(buffer, marker);  /* 一定要这个函数才能使用可变参数 */
    va_end(marker);
}

/*******************************************************************************

   Function:		_print_color

   Author:		jialiangjun

   Description: 打印带有背景色的函数,此函数没有使用,若要使用,请替换print_color

   Input:
    @attr       字体
    @fg_color   前景色
    @bg_color   背景色
    @fmt        类型printf的打印字符串

   Output:		N/A

   Return:
    0:			Successful
    ohters:		Failed

*******************************************************************************/
void _print_color_withBG(int attr, int fg_color, int bg_color, const char *fmt, ...) {
    char buffer[PT_COLOR_BUF_LEN] = {0};
    va_list marker;

    va_start(marker, fmt);

    /* 背景色为0时，不影响后面的信息，其它值会影响 */
    snprintf(buffer, PT_COLOR_BUF_LEN - 1, "\x1b[%d;%d;%dm%s\x1b[0m", fg_color + 30, bg_color + 40, attr, fmt);
    my_vprint(buffer, marker);  /* 一定要这个函数才能使用可变参数 */
    va_end(marker);
}
