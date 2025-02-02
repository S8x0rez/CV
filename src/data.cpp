#include "data.hpp"

void AllocImg(IMG *img, int width, int height, int channel)
{
    img->width = width;
    img->height = height;
    img->pixel = width * height;
    img->channel = channel;

    if (img->pixel == 0) { // 処理系定義によるエラー回避
        cerr << "AllocImg: img size error" << endl;
        exit(-1);
    }

	img->value = MemoryAlloc<uchar>(channel * img->pixel);
}

void AllocImgCMN(IMG_COMMON *img, int width, int height, int channel)
{
    img->width = width;
    img->height = height;
    img->pixel = width * height;
    img->channel = channel;

    if (img->pixel == 0) { // 処理系定義によるエラー回避
        cerr << "AllocImg: img size error" << endl;
        exit(-1);
    }

	img->value = MemoryAlloc<uchar *>(channel);

	for (int ch = 0; ch < channel; ch++) {
    	img->value[ch] = MemoryAlloc<uchar>(img->pixel);
	}
}

void AllocImgRGB(IMG_RGB *img, int width, int height)
{
    img->width = width;
    img->height = height;
    img->pixel = width * height;

    if (img->pixel == 0) { // 処理系定義によるエラー回避
        cerr << "AllocImg: img size error" << endl;
        exit(-1);
    }

    img->R = MemoryAlloc<uchar>(img->pixel);
    img->G = MemoryAlloc<uchar>(img->pixel);
    img->B = MemoryAlloc<uchar>(img->pixel);
}

void AllocImgHSV(IMG_HSV *img, int width, int height)
{
	img->width = width;
	img->height = height;
	img->pixel = width * height;

	if (img->pixel == 0) {
		cerr << "AllocImg: img size error" << endl;
		exit(-1);
	}

	img->H = MemoryAlloc<int>(img->pixel);
	img->S = MemoryAlloc<uchar>(img->pixel);
	img->V = MemoryAlloc<uchar>(img->pixel);
}

void AllocImgYUV(IMG_YUV* img, int width, int height, int color_format) {
    img->width = width;
    img->height = height;
    img->pixel = width * height;
    img->color_format = color_format;
    
    if (img->pixel == 0) { // 処理系定義によるエラー回避
        cerr << "AllocImg: img size error" << endl;
        exit(-1);
    }

    if (img->color_format == 444) {
        img->Y = MemoryAlloc<uchar>(img->pixel);
        img->U = MemoryAlloc<uchar>(img->pixel);
        img->V = MemoryAlloc<uchar>(img->pixel);
    }
    else {

    }
}

void Free(IMG *img)
{
    if (img->value) delete[] img->value;
    delete img;
}

void Free(IMG_COMMON *img)
{
	for (int ch = 0; ch < img->channel; ch++) {
		if (img->value[ch]) delete[] img->value[ch];
	}
    if (img->value) delete[] img->value;
    delete img;
}

void Free(IMG_RGB *img)
{
    if (img->R) delete[] img->R;
    if (img->G) delete[] img->G;
    if (img->B) delete[] img->B;
    delete img;
}

void Free(IMG_HSV *img)
{
	if (img->H) delete[] img->H;
	if (img->S) delete[] img->S;
	if (img->V) delete[] img->V;
	delete img;
}

void Free(IMG_YUV *img)
{
	if (img->Y) delete[] img->Y;
	if (img->U) delete[] img->U;
	if (img->V) delete[] img->V;
	delete img;
}

void CopyCMN(IMG_COMMON *img_out, IMG_COMMON *img_in)
{
	img_out->width = img_in->width;
	img_out->height = img_in->height;
	img_out->pixel = img_in->pixel;
	img_out->channel = img_in->channel;

	for (int ch = 0; ch < img_in->channel; ch++) {
		for (int i = 0; i < img_in->pixel; i++) {
			img_out->value[ch][i] = img_in->value[ch][i];
		}
	}
}

void CopyRGB(IMG_RGB *img_out, IMG_RGB *img_in)
{
	img_out->width = img_in->width;
	img_out->height = img_in->height;
	img_out->pixel = img_in->pixel;

	for (int i = 0; i < img_in->pixel; i++) {
		img_out->R[i] = img_in->R[i];
		img_out->G[i] = img_in->G[i];
		img_out->B[i] = img_in->B[i];
	}
}

void CopyHSV(IMG_HSV *img_out, IMG_HSV *img_in)
{
	img_out->width = img_in->width;
	img_out->height = img_in->height;
	img_out->pixel = img_in->pixel;

	for (int i = 0; i < img_in->pixel; i++) {
		img_out->H[i] = img_in->H[i];
		img_out->S[i] = img_in->S[i];
		img_out->V[i] = img_in->V[i];
	}
}

void CopyYUV(IMG_YUV *img_out, IMG_YUV *img_in)
{
	img_out->width = img_in->width;
	img_out->height = img_in->height;
	img_out->pixel = img_in->pixel;
	img_out->color_format = img_in->color_format;

	for (int i = 0; i < img_in->pixel; i++) {
		img_out->Y[i] = img_in->Y[i];
		img_out->U[i] = img_in->U[i];
		img_out->V[i] = img_in->V[i];
	}
}

uchar RoundingUC(double dv)
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

uchar RoundingUC(int iv)
{
	uchar ucv;
	if (iv < 0) {
		iv = 0;
	}
	else if (iv > 255) {
		iv = 255;
	}
	ucv = (uchar)iv;
	return (uchar)iv;
}

int RoundingInt(double dv)
{
	return (int)(dv < 0.0 ? dv - 0.5 : dv + 0.5);
}

void IMG2RGB(IMG_RGB *img_rgb, IMG *img)
{
	int j, k;
	int width, height;
	
	width = img->width;
	height = img->height;

    for(int k = 0; k < height; k++) {
        for (int j = 0; j < width; j++) {
            img_rgb->R[j + k * width] = img->value[(j + k * width) * img->channel + 0];
            img_rgb->G[j + k * width] = img->value[(j + k * width) * img->channel + 1];
            img_rgb->B[j + k * width] = img->value[(j + k * width) * img->channel + 2];
        }
    }
}

void RGB2IMG(IMG *img, IMG_RGB *img_rgb)
{
	int j, k;
	int width, height;
	
	width = img_rgb->width;
	height = img_rgb->height;

    for(int k = 0; k < height; k++) {
        for (int j = 0; j < width; j++) {
            img->value[(j + k * width) * img->channel + 0] = img_rgb->R[j + k * width];
            img->value[(j + k * width) * img->channel + 1] = img_rgb->G[j + k * width];
            img->value[(j + k * width) * img->channel + 2] = img_rgb->B[j + k * width];
        }
    }
}

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

void  HSV2YUV(IMG_YUV *img_yuv, IMG_HSV *img_hsv)
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

void  RGB2HSV(IMG_HSV *img_hsv, IMG_RGB *img_rgb)
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

void  HSV2RGB(IMG_RGB *img_rgb, IMG_HSV *img_hsv)
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

void  RGB2YUV(IMG_YUV *img_yuv, IMG_RGB *img_rgb, int color_matrix)
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
				img_yuv->Y[j + k * width] = RoundingUC(y);       /* Y conponent */
				img_yuv->U[j + k * width] = RoundingUC(u + 128);   /* U conponent */
				img_yuv->V[j + k * width] = RoundingUC(v + 128);   /* V conponent */
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
				img_yuv->Y[j + k * width] = RoundingUC(y);       /* Y conponent */
				img_yuv->U[j + k * width] = RoundingUC(u + 128);   /* U conponent */
				img_yuv->V[j + k * width] = RoundingUC(v + 128);   /* V conponent */
			}
		}
	}
}

void  YUV2RGB(IMG_RGB *img_rgb, IMG_YUV *img_yuv, int color_matrix)
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
				img_rgb->R[j + k * width] = RoundingUC(r);
				img_rgb->G[j + k * width] = RoundingUC(g);
				img_rgb->B[j + k * width] = RoundingUC(b);
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
				img_rgb->R[j + k * width] = RoundingUC(r);
				img_rgb->G[j + k * width] = RoundingUC(g);
				img_rgb->B[j + k * width] = RoundingUC(b);
			}
		}
	}
}
