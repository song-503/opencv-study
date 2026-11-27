#include <opencv2/opencv.hpp>  // OpenCV 명령어 사용 
#include <cstdio>  // C언어 표준 입출력 (열기/닫기/읽기/쓰기)
#include <cstdlib> // C언어 표준 유틸리티 (메모리 할당)

typedef unsigned char uchar; // unsigned char 대신 uchar 사용 -> 별칭 부여 (alias)

uchar** uc_alloc(int size_x, int size_y) // size_x [가로/열]  size_y [세로/행]
{
    uchar** m; // m은 포인터 배열의 첫번째 주소를 가리킴
    int i; 

    if ((m = (uchar**)calloc(size_y, sizeof(uchar*))) == NULL) 
        // 세로 행 개수만큼 포인터 공간 할당 + 0으로 초기화해 할당 성공 여부를 검사 [calloc : 할당 + 0으로 초기화]
    {
        printf("uc_alloc error 1\n"); 
        exit(0); // 오류메세지 출력 + 프로그램 정상종료
    }

    for (i = 0; i < size_y; i++) // C언어의 동적 할당은 1차원 배열만 생성할 수 있음 [2차원 = 1차원 내부에 1차원 배 생성]
        if ((m[i] = (uchar*)calloc(size_x, sizeof(uchar))) == NULL)
            // 세로 행 개수만큼 포인터 공간 할당 + 0으로 초기화해 할당 성공 여부를 검사 [calloc : 할당 + 0으로 초기화]
        {
            printf("uc_alloc error 2\n");
            exit(0); // 오류메세지 출력 + 프로그램 정상종료
        }

    return m; // 힙 메모리의 시작주소를 main 함수에 넘겨줌
}

void read_ucmatrix(int size_x, int size_y, uchar** ucmatrix, char* filename)
 // 2차원 배열 공간에 디스크에 저장된 원본 파일을 열어 픽셀 값을 하나씩 배열에 채워넣는 과정
{
    int i;
    FILE* f; // 운영체제에 의해 열린 파일의 상태를 점검

    if ((fopen_s(&f, filename, "rb")) != 0)
        // 파일을 "rb"로 열고 스트림 주소를 f에 저장한 뒤 성공 여부 판단해 반환 [성공시 0 / 실패시 에러코드]
    {
        printf("%s File open Error!\n", filename);
        exit(0); // 0이 아닐 경우 오류 메세지 + 프로그램 정상종료
    }

    for (i = 0; i < size_y; i++)
        if (fread(ucmatrix[i], sizeof(uchar), size_x, f) != (size_t)size_x)
            // f 위치에서 sizeof(uchar) 크기의 원소를 size_x개 만큼 읽어 ucmatrix[i]에 저장하고 실제와 갯수 일치 판별
        {
            // 사용자의 요청 원소 수 != 실제로 찍힌 원소 수
            printf("Data Read Error!\n"); 
            fclose(f);
            exit(0); // 오류 메세지 출력 -> 열어둔 파일 닫기 + 정상 종료
        }

    fclose(f); // 모든 작업이 끝난 후에 파일 반납
}

void write_ucmatrix(int size_x, int size_y, uchar** ucmatrix, char* filename)
 // 2차원 배열에 이미 데이터가 가득차 있고 픽셀 값을 꺼내 결과 파일로 내보내 저
{
    int i;
    FILE* f; // 운영체제에 의해 열린 파일의 상태를 점검

    if ((fopen_s(&f, filename, "wb")) != 0)
        // 파일을 "wb"로 열고 스트림 주소를 f에 저장한 뒤 성공 여부 판단해 반환 [성공시 0 / 실패시 에러코드]
    {
        printf("%s File open Error!\n", filename);
        exit(0); // 0이 아닐 경우 오류 메세지 + 프로그램 정상종료
    }

    for (i = 0; i < size_y; i++)
        if (fwrite(ucmatrix[i], sizeof(uchar), size_x, f) != (size_t)size_x)
             // f 위치에서 sizeof(uchar) 크기의 원소를 size_x개 만큼 쓰고 ucmatrix[i]에 저장하고 실제와 갯수 일치 판별
        {
            printf("Data Write Error!\n");
            fclose(f);
            exit(0);  // 오류 메세지 출력 -> 열어둔 파일 닫기 + 정상 종료
        }

    fclose(f); // 모든 작업이 끝난 후에 파일 반납
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
