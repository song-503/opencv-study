#include <opencv2/opencv.hpp>   
#include <cstdio>
#include <cstdlib>

typedef unsigned char uchar;

uchar** uc_alloc(int size_x, int size_y)
{
    uchar** m;
    int i;

    if ((m = (uchar**)calloc(size_y, sizeof(uchar*))) == NULL)
    {
        printf("uc_alloc error 1\n");
        exit(0);
    }

    for (i = 0; i < size_y; i++)
        if ((m[i] = (uchar*)calloc(size_x, sizeof(uchar))) == NULL)
        {
            printf("uc_alloc error 2\n");
            exit(0);
        }

    return m;
}

void read_ucmatrix(int size_x, int size_y, uchar** ucmatrix, char* filename)
{
    int i;
    FILE* f;

    if ((fopen_s(&f, filename, "rb")) != 0)
    {
        printf("%s File open Error!\n", filename);
        exit(0);
    }

    for (i = 0; i < size_y; i++)
        if (fread(ucmatrix[i], sizeof(uchar), size_x, f) != (size_t)size_x)
        {
            printf("Data Read Error!\n");
            fclose(f);
            exit(0);
        }

    fclose(f);
}

void write_ucmatrix(int size_x, int size_y, uchar** ucmatrix, char* filename)
{
    int i;
    FILE* f;

    if ((fopen_s(&f, filename, "wb")) != 0)
    {
        printf("%s File open Error!\n", filename);
        exit(0);
    }

    for (i = 0; i < size_y; i++)
        if (fwrite(ucmatrix[i], sizeof(uchar), size_x, f) != (size_t)size_x)
        {
            printf("Data Write Error!\n");
            fclose(f);
            exit(0);
        }

    fclose(f);
}

int main(int argc, char* argv[])
{
    int i, j;
    cv::Mat cvImg;
    cv::Size imgSize;
    uchar** img;

    if (argc != 4)
    {
        printf("Exe imgData x_size y_size \n");
        exit(0);
    }

    imgSize.width = atoi(argv[2]);
    imgSize.height = atoi(argv[3]);
    if (imgSize.width <= 0 || imgSize.height <= 0)
    {
        printf("Invalid width/height: %s, %s\n", argv[2], argv[3]);
        exit(0);
    }

    img = uc_alloc(imgSize.width, imgSize.height);
    read_ucmatrix(imgSize.width, imgSize.height, img, argv[1]);

    cvImg = cv::Mat(imgSize.height, imgSize.width, CV_8UC1);

    for (i = 0; i < imgSize.height; i++)
        for (j = 0; j < imgSize.width; j++)
            cvImg.at<uchar>(i, j) = img[i][j];

    cv::namedWindow(argv[1], cv::WINDOW_AUTOSIZE);
    cv::imshow(argv[1], cvImg);

    cv::waitKey(0);
    cv::destroyAllWindows();

    getchar();
    getchar();
    return 0;
}
