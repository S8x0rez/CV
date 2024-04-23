#include "data.hpp"

void  YUV2HSV(IMG_HSV* img_hsv, IMG_YUV* img_yuv)
{

	int j, k;
	int width, height;
	int u, v;

	width = img_yuv->width;
	height = img_yuv->height;

	for (k = 0; k < height; k++) {
		for (j = 0; j < width; j++) {
			u = img_yuv->U[j + k * width] - 128;
			v = img_yuv->V[j + k * width] - 128;
			if (atan2(v, u) >= 0) img_hsv->H[j + k * width] = (int)(atan2(v, u) * 180 / PI);
			else img_hsv->H[j + k * width] = (int)(atan2(v, u) * 180 / PI + 360);
			img_hsv->S[j + k * width] = (int)(sqrt(pow(u, 2) + pow(v, 2)) * 255 / 100);
			img_hsv->V[j + k * width] = img_yuv->Y[j + k * width];

		}
	}


}

void  HSV2YUV(IMG_YUV* img_yuv, IMG_HSV* img_hsv)
{
	int j, k;
	int width, height;
	double h;
	int s;

	width = img_hsv->width;
	height = img_hsv->height;

	for (k = 0; k < height; k++) {
		for (j = 0; j < width; j++) {
			if (img_hsv->H[j + k * width] <= 180) h = (double)img_hsv->H[j + k * width] * PI / 180;
			else h = (double)((img_hsv->H[j + k * width] - 360) * PI / 180);
			s = img_hsv->S[j + k * width] * 100 / 255;
			img_yuv->Y[j + k * width] = img_hsv->V[j + k * width];       /* Y conponent */
			img_yuv->U[j + k * width] = (int)(s * cos(h) + 128);   /* U conponent */
			img_yuv->V[j + k * width] = (int)(s * sin(h) + 128);   /* V conponent */
		}
	}
}

void  RGB2HSV(IMG_HSV* img_hsv, IMG_RGB* img_rgb)
{
	int width, height;
	double r, g, b;
	int h = 0;
	array<double, 3> value;

	width = img_rgb->width;
	height = img_rgb->height;

	for (int k = 0; k < height; k++) {
		for (int j = 0; j < width; j++) {
			value = { (double)img_rgb->R[j + k * width], (double)img_rgb->G[j + k * width], (double)img_rgb->B[j + k * width] };
			sort(value.begin(), value.end());
			r = img_rgb->R[j + k * width];
			g = img_rgb->G[j + k * width];
			b = img_rgb->B[j + k * width];
			if (value[0] == value[2]) {
				img_hsv->H[j + k * width] = 0;
				img_hsv->S[j + k * width] = 0;
				img_hsv->V[j + k * width] = (int)value[0];
				continue;
			}
			else if (value[2] == r) {
				h = (int)(60 * (g - b) / (value[2] - value[0]));

				if (h < 0) h += 360;
			}
			else if (value[2] == g) {
				h = (int)(60 * (b - r) / (value[2] - value[0]) + 120);
			}
			else if (value[2] == b) {
				h = (int)(60 * (r - g) / (value[2] - value[0]) + 240);
			}
			img_hsv->H[j + k * width] = h;
			img_hsv->S[j + k * width] = (int)((value[2] - value[0]) / value[2] * 255);
			img_hsv->V[j + k * width] = (int)value[2];
		}
	}
}

void  HSV2RGB(IMG_RGB* img_rgb, IMG_HSV* img_hsv)
{
	int width, height;
	double min, max;

	width = img_hsv->width;
	height = img_hsv->height;

	for (int k = 0; k < height; k++) {
		for (int j = 0; j < width; j++) {
			max = img_hsv->V[j + k * width];
			min = max - (double)img_hsv->S[j + k * width] / 255 * max;

			if (img_hsv->H[j + k * width] >= 0 && img_hsv->H[j + k * width] < 60) {
				img_rgb->R[j + k * width] = (int)max;
				img_rgb->G[j + k * width] = (int)((double)img_hsv->H[j + k * width] / 60 * (max - min) + min);
				img_rgb->B[j + k * width] = (int)min;
			}
			else if (img_hsv->H[j + k * width] >= 60 && img_hsv->H[j + k * width] < 120) {
				img_rgb->R[j + k * width] = (int)((double)(120 - img_hsv->H[j + k * width]) / 60 * (max - min) + min);
				img_rgb->G[j + k * width] = (int)max;
				img_rgb->B[j + k * width] = (int)min;
			}
			else if (img_hsv->H[j + k * width] >= 120 && img_hsv->H[j + k * width] < 180) {
				img_rgb->R[j + k * width] = (int)min;
				img_rgb->G[j + k * width] = (int)max;
				img_rgb->B[j + k * width] = (int)((double)(img_hsv->H[j + k * width] - 120) / 60 * (max - min) + min);
			}
			else if (img_hsv->H[j + k * width] >= 180 && img_hsv->H[j + k * width] < 240) {
				img_rgb->R[j + k * width] = (int)min;
				img_rgb->G[j + k * width] = (int)((double)(240 - img_hsv->H[j + k * width]) / 60 * (max - min) + min);
				img_rgb->B[j + k * width] = (int)max;
			}
			else if (img_hsv->H[j + k * width] >= 240 && img_hsv->H[j + k * width] < 300) {
				img_rgb->R[j + k * width] = (int)((double)(img_hsv->H[j + k * width] - 240) / 60 * (max - min) + min);
				img_rgb->G[j + k * width] = (int)min;
				img_rgb->B[j + k * width] = (int)max;
			}
			else if (img_hsv->H[j + k * width] >= 300 && img_hsv->H[j + k * width] < 360) {
				img_rgb->R[j + k * width] = (int)max;
				img_rgb->G[j + k * width] = (int)min;
				img_rgb->B[j + k * width] = (int)((double)(360 - img_hsv->H[j + k * width]) / 60 * (max - min) + min);
			}

		}
	}

}

void  RGB2YUV(IMG_YUV* img_yuv, IMG_RGB* img_rgb, int color_matrix)
{

	int j, k;
	int width, height;
	double y, u, v;

	width = img_rgb->width;
	height = img_rgb->height;

	if (color_matrix == 601) {  /* BT.601 matrix */
		for (k = 0; k < height; k++) {
			for (j = 0; j < width; j++) {
				y = 0.299 * img_rgb->R[j + k * width] + 0.587 * img_rgb->G[j + k * width] + 0.114 * img_rgb->B[j + k * width];
				u = -0.169 * img_rgb->R[j + k * width] - 0.331 * img_rgb->G[j + k * width] + 0.5 * img_rgb->B[j + k * width];
				v = 0.5 * img_rgb->R[j + k * width] - 0.419 * img_rgb->G[j + k * width] - 0.081 * img_rgb->B[j + k * width];
				img_yuv->Y[j + k * width] = RoundingDecimal(y);       /* Y conponent */
				img_yuv->U[j + k * width] = RoundingDecimal(u + 128);   /* U conponent */
				img_yuv->V[j + k * width] = RoundingDecimal(v + 128);   /* V conponent */
			}
		}
	}
	else if (color_matrix == 2020) {  /* BT.2020 matrix */

	}
	else {  /* BT.709 matrix */
		for (k = 0; k < height; k++) {
			for (j = 0; j < width; j++) {
				y = 0.2126 * img_rgb->R[j + k * width] + 0.7152 * img_rgb->G[j + k * width] + 0.0722 * img_rgb->B[j + k * width];
				u = -0.1146 * img_rgb->R[j + k * width] - 0.3854 * img_rgb->G[j + k * width] + 0.5 * img_rgb->B[j + k * width];
				v = 0.5 * img_rgb->R[j + k * width] - 0.4542 * img_rgb->G[j + k * width] - 0.0458 * img_rgb->B[j + k * width];
				img_yuv->Y[j + k * width] = RoundingDecimal(y);       /* Y conponent */
				img_yuv->U[j + k * width] = RoundingDecimal(u + 128);   /* U conponent */
				img_yuv->V[j + k * width] = RoundingDecimal(v + 128);   /* V conponent */
			}
		}
	}

}

void  YUV2RGB(IMG_RGB* img_rgb, IMG_YUV* img_yuv, int color_matrix)
{

	int j, k;
	int width, height;
	double r, g, b;

	width = img_yuv->width;
	height = img_yuv->height;

	if (color_matrix == 601) {  /* BT.601 matrix */
		for (k = 0; k < height; k++) {
			for (j = 0; j < width; j++) {
				r = img_yuv->Y[j + k * width] + 1.402 * (img_yuv->V[j + k * width] - 128);
				g = img_yuv->Y[j + k * width] - 0.344 * (img_yuv->U[j + k * width] - 128) - 0.714 * (img_yuv->V[j + k * width] - 128);
				b = img_yuv->Y[j + k * width] + 1.772 * (img_yuv->U[j + k * width] - 128);
				img_rgb->R[j + k * width] = RoundingDecimal(r);
				img_rgb->G[j + k * width] = RoundingDecimal(g);
				img_rgb->B[j + k * width] = RoundingDecimal(b);
			}
		}
	}
	else if (color_matrix = 2020) {  /* BT.2020 matrix */

	}
	else {  /* BT.709 matrix */
		for (k = 0; k < height; k++) {
			for (j = 0; j < width; j++) {
				r = img_yuv->Y[j + k * width] + 1.5748 * (img_yuv->V[j + k * width] - 128);
				g = img_yuv->Y[j + k * width] - 0.1873 * (img_yuv->U[j + k * width] - 128) - 0.4681 * (img_yuv->V[j + k * width] - 128);
				b = img_yuv->Y[j + k * width] + 1.8556 * (img_yuv->U[j + k * width] - 128);
				img_rgb->R[j + k * width] = RoundingDecimal(r);
				img_rgb->G[j + k * width] = RoundingDecimal(g);
				img_rgb->B[j + k * width] = RoundingDecimal(b);
			}
		}
	}

}

void CopyRGB(IMG_RGB* img_out, IMG_RGB* img_in)
{
	if (img_out->width != img_in->width || img_out->height != img_in->height) {
		cout << "CopyRGB: image size error" << endl;
		return;
	}

	int width, height;

	width = img_in->width;
	height = img_in->height;

	for (int k = 0; k < height ; k++) {
		for (int j = 0; j < width; j++) {
			img_out->R[j + k * width] = img_in->R[j + k * width];
			img_out->G[j + k * width] = img_in->G[j + k * width];
			img_out->B[j + k * width] = img_in->B[j + k * width];
		}
	}
}

uchar RoundingDecimal(double dv)
{
    uchar ucv;
	int iv = (int)(dv + 0.5);
	if (iv < 0) {
		iv = 0;
	}
	else if (iv > 255) {
		iv = 255;
	}
	ucv = (uchar)iv;
	return ucv;
}

uchar RoundingInt(int iv)
{
	unsigned char ucv;
	if (iv < 0) {
		iv = 0;
	}
	else if (iv > 255) {
		iv = 255;
	}
	ucv = (uchar)iv;
	return ucv;
}
