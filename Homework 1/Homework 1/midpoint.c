#include <gl/glut.h>

// Function for line drawing using the midpoint algorithm
int midpointAlg(int x1, int y1, int x2, int y2) {
	// Declare variables
	int deltX;
	int deltY;
	float slope;
	int d;
	int incE;
	int incNE;
	int incSE;
	int newVal;
	int i;
	// Find the delta values of the two recent endpoints
	deltX = x2 - x1;
	deltY = y2 - y1;
	// Find the slope to determine line drawn
	slope = (float) deltY / (float) deltX;
	// Check if slope is positive or negative
	if (slope < 0) {
		// Negative slope smaller than -1
		if (slope < -1) {
			d = (2 * deltX) - (-1 * deltY);
			incE = 2 * deltX;
			incNE = 2 * (deltX - (-1 * deltY));
			newVal = x1;
			for (i = y1; i > y2; i--) {
				// Draw the first pixel in the line
				glVertex2i(newVal, i);
				// Calculate position of next pixel in line
				if (d > 0) {
					d = d + incNE;
					newVal = newVal + 1;
				}
				else {
					d = d + incE;
				}
			}
			// Draw the last pixel in the line
			glVertex2i(x2, y2);
		}
		// Negative slope between 0 and -1
		else {
			d = (2 * (-1 * deltY)) - deltX;
			incE = 2 * (-1 * deltY);
			incSE = 2 * ((-1 * deltY) - deltX);
			newVal = y1;
			for (i = x1; i < x2; i++) {
				// Draw the first pixel in the line
				glVertex2i(i, newVal);
				// Calculate position of next pixel in line
				if (d > 0) {
					d = d + incSE;
					newVal = newVal - 1;
				}
				else {
					d = d + incE;
				}
			}
			// Draw the last pixel in the line
			glVertex2i(x2, y2);
		}
	}
	else {
		// Positive slope larger than 1
		if (slope > 1) {
			d = (2 * deltX) - deltY;
			incE = 2 * deltX;
			incNE = 2 * (deltX - deltY);
			newVal = x1;
			for (i = y1; i < y2; i++) {
				// Draw the first pixel in the line
				glVertex2i(newVal, i);
				// Calculate position of next pixel in line
				if (d > 0) {
					d = d + incNE;
					newVal = newVal + 1;
				}
				else {
					d = d + incE;
				}
			}
			// Draw the last pixel in the line
			glVertex2i(x2, y2);
		}
		// Positive slope between 0 and 1
		else {
			d = (2 * deltY) - deltX;
			incE = 2 * deltY;
			incNE = 2 * (deltY - deltX);
			newVal = y1;
			for (i = x1; i < x2; i++) {
				// Draw the first pixel in the line
				glVertex2i(i, newVal);
				// Calculate position of next pixel in line
				if (d > 0) {
					d = d + incNE;
					newVal = newVal + 1;
				}
				else {
					d = d + incE;
				}
			}
			// Draw the last pixel in the line
			glVertex2i(x2, y2);
		}
	}
	return 0;
}