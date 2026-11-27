## #include <opencv2/opencv.hpp> 
: OpenCV의 주요 기능 헤더 파일들을 통합해 사용하게 해줌 <p>
: OpenCV에서는 모든 기능이 cv라는 네임스페이스 내부에서 진행됨

plus) cv 명령어
 cv::Mat > 영상 데이터를 담는 OpenCV 기본 행렬 클래스
 cv::Size > 영상의 가로/세로 크기를 묶어 표현하는 구조체
 cv::waitKey > 실제 화면 렌더링을 처리하는 함수
 cv::imshow > 창에 데이터를 연결해 출력 예약을 거는 함수
 cv::namedwindow > 이미지를 띄울 창을 고유 이름과 크기 옵션으로 미리 생성하는 함수
 cv::destroyAllWindows > 열려 있는 모든 OpenCV 창과 메모리 리소스를 일괄 해제하는 함수

** #include <cstdio> **
: C언어 표준 입출력 담당

## 표준 입출력
printf : 콘솔에 출력
fopen_s : 파일 열기
fclose : 파일 닫기

FILE* : 열린 파일들을 가리킴
