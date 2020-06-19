#ifndef TEXT_H
#define TEXT_H

#include "stds.h"

extern App app;

/*
 *
 */
extern void initFonts(void);

/*
 *
 */
extern void freeFonts(void);

/*
 *
 */
extern void drawText(float, float, uint8_t, uint8_t, uint8_t, const char*, ...);

/*
 * Computes the size of the string with the default font were it to be drawn
 * to the screen in pixels. This is useful for positioning the string in the middle
 * of the screen if need-be.
 * 
 * @param char* string.
 * @param pointer to integer where the width of the string is stored.
 * @param pointer to integer where the height of the string is stored.
 */
extern void getStringSize(char*, int*, int*);

/*
 * Computes the size of the string with the supplied font were it to be drawn
 * to the screen in pixels. This is useful for positioning the string in the middle
 * of the screen if need-be.
 * 
 * @param char* string.
 * @param TTF_Font* font used for determining the size.
 * @param pointer to integer where the width of the string is stored.
 * @param pointer to integer where the height of the string is stored.
 */
extern void getStringSizeFont(char*, TTF_Font*, int*, int*);

#endif
