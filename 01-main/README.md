# 01. Main 코드 구조

> 수업에서 제공받은 기본 템플릿 [`main.cpp`](main.cpp)를 한 줄씩 뜯어보며 정리했다. <p>
> 이후 단원(모자이크, 네거티브 이미지 등)은 모두 이 템플릿 위에 함수를 추가하는 방식으로 진행한다.

**동작** : 헤더 없는 8비트 그레이스케일 RAW 파일을 `uchar**` 2차원 배열로 읽고, `cv::Mat`으로 옮겨 화면에 띄운다.

```
Exe imgData x_size y_size        예) Exe boat.512 512 512
```

## 1. `#include`의 의미

`#include`는 컴파일러가 아니라 **전처리기**가 처리하고 지정한 헤더 파일의 내용을 그 자리에 그대로 붙여넣는다.

```
소스(.cpp) → 전처리(#include 펼치기) → 컴파일 → 링크(.lib 연결) → 실행 파일
```

헤더에는 함수 **선언**만 있고 실제 구현은 라이브러리(`.lib`, `.dll`)에 있다. <p>
그래서 [00-setup](../00-setup/)의 링커 설정이 있어야 실행 파일이 만들어진다.

| 표기 | 헤더를 찾는 위치 |
|---|---|
| `#include <...>` | 시스템·라이브러리 경로 |
| `#include "..."` | 현재 소스 폴더 → 없으면 시스템 경로 |

## 2. `#include <opencv2/opencv.hpp>`

OpenCV의 주요 모듈 헤더를 한 번에 포함하는 **통합 헤더**다. <p>

OpenCV의 클래스와 함수는 `cv` 네임스페이스 안에 있어 `cv::`를 붙인다. <p>
 -> 단 `CV_8UC1` 같은 상수는 **매크로**라서 `cv::`를 붙이지 않는다.

이 템플릿에서 OpenCV는 **화면 출력에만** 쓰인다. <p>

| 이름 | 종류 | 설명 |
|---|---|---|
| `cv::Mat` | 클래스 | 영상 데이터를 담는 기본 행렬 |
| `cv::Size` | 구조체 | `width`, `height`를 묶어 표현 |
| `CV_8UC1` | 매크로 상수 | 8bit, 1채널 (0~255 그레이스케일) |
| `cv::namedWindow` | 함수 | 이름과 옵션으로 창 생성 |
| `cv::imshow` | 함수 | 창에 영상 연결 (창이 없으면 자동 생성) |
| `cv::waitKey` | 함수 | 키 입력 대기 + 창 그리기. 0이면 무한 대기 |
| `cv::destroyAllWindows` | 함수 | 열린 창을 모두 닫음 (영상 메모리는 해제 안 함) |

## 3. `#include <cstdio>` — C 표준 입출력

| 이름 | 설명 |
|---|---|
| `printf` | 콘솔 출력 |
| `FILE*` | 열린 파일 하나를 가리키는 포인터 |
| `fopen_s` | 파일 열기 (성공 시 0 반환, MSVC 전용) |
| `fclose` | 파일 닫기 |
| `fread` | 바이너리 데이터 읽기 |
| `fwrite` | 바이너리 데이터 쓰기 |
| `getchar` | 키 입력 한 글자 대기 |

RAW 영상은 `"rb"`, `"wb"`처럼 **바이너리 모드**로 연다. <p>
텍스트 모드로 열면 읽기가 실패한다. 아래 **막힌 점 3)** 에 기록했다.

## 4. `#include <cstdlib>` — C 표준 유틸리티

| 이름 | 설명 |
|---|---|
| `malloc` | 메모리 할당 (초기화 안 함) |
| `calloc` | 메모리 할당 + 0으로 초기화 |
| `realloc` | 할당된 메모리 크기 변경 |
| `free` | 메모리 해제 |
| `atoi` | 문자열 → `int`  |
| `atof` | 문자열 → `double`  |
| `exit` | 프로그램 즉시 종료 (0: 정상, 그 외: 비정상) |

## 5. `typedef unsigned char uchar;`

`typedef 기존타입 새이름;`은 기존 타입에 **별명**을 붙인다. <p>
`uchar`와 `unsigned char`는 완전히 같은 타입이다.

8bit 픽셀 하나는 0~255 정수 하나라서 `unsigned char`가 딱 맞는다.

| 타입 | 크기 | 범위 |
|---|---|---|
| `char` | 1 B | -128 ~ 127 |
| `unsigned char` | 1 B | **0 ~ 255** |
| `int` | 4 B | 약 ±21억 |

## 6. `read_ucmatrix` / `write_ucmatrix`

두 함수는 같은 모양이고 데이터가 흐르는 방향만 반대다.
실제로는 아래 순서로 짝을 지어 쓴다.

```text
uc_alloc ──► read_ucmatrix ──► 픽셀 가공 ──► write_ucmatrix
빈 배열 준비   원본 파일 → 배열               배열 → 새 결과 파일
```

| 함수 | 모드 + 입출력 | 하는 일 |
|---|---|---|
| `read_ucmatrix` | `"rb"` + `fread` | 빈 배열에 원본 파일의 픽셀 `size_x * size_y`개를 채운다 |
| `write_ucmatrix` | `"wb"` + `fwrite` | 배열에 담긴 픽셀 `size_x * size_y`개로 새 결과 파일을 만든다 |

`"wb"`는 같은 이름의 파일이 있으면 내용을 지우고 새로 쓴다.
`write_ucmatrix`에 원본과 같은 파일명을 주면 원본이 덮어써진다.
<br>


## 막힌 점

### 1) 에러인데 `exit(0)`으로 종료함

파일 열기·메모리 할당에 실패하는 분기에서 모두 `exit(0)`을 호출한다.

**< 원인 >**

`exit`의 인자 0은 정상 종료를 뜻한다.
그래서 에러가 나도 VS 출력 창에는 정상 실행과 똑같이 찍힌다.

```text
코드 0(0x0)으로 종료되었습니다.
```

**< 해결 >**

에러 분기에서는 `exit(1)` 또는 `exit(EXIT_FAILURE)`를 쓴다.
수업 템플릿이라 원본은 그대로 두고 차이만 기록했다.

> `exit`는 즉시 종료라서 지역 객체의 소멸자가 호출되지 않는다.
> 정리 작업이 필요한 코드라면 `main`에서 `return`으로 끝내는 편이 안전하다.
<br>

### 2) 2차원 할당에서 `calloc` 하나만 반복문인 이유

`uc_alloc`에서 첫 번째 `calloc`은 한 번, 두 번째 `calloc`은 `for`문으로 여러 번 호출한다.

**< 원인 >**

첫 번째 `calloc`은 픽셀 공간이 아니라 행을 가리킬 포인터 배열을 만든다.

```text
m ──► [ m[0]        ] ──► [ p p p ... p ]   0행 픽셀 size_x개
      [ m[1]        ] ──► [ p p p ... p ]   1행
      [ ...         ]
      [ m[size_y-1] ] ──► [ p p p ... p ]   마지막 행

      └ 1단계: 1번 ┘      └ 2단계: 행마다 1번 → size_y번 ┘
```

| 단계 | 코드 | 만드는 것 | 호출 횟수 |
|---|---|---|---|
| 1 | `calloc(size_y, sizeof(uchar*))` | 행 포인터 배열 | 1번 |
| 2 | `m[i] = calloc(size_x, sizeof(uchar))` | 행 하나의 픽셀 블록 | `size_y`번 |

반복문은 열 공간이 아니라 행 블록을 행 개수만큼 만든다. <p>
이렇게 나누는 이유는 `img[i][j]`로 접근하기 위함이다.

**< 해결 >**

위 방식은 행 블록이 메모리에 흩어져 있다. 
그래서 `fread` 한 번으로 전체를 읽을 수 없고, 해제도 행마다 해야 한다. <p>
픽셀 전체를 연속된 블록 하나로 잡으면 `calloc` 두 번으로 끝난다.

```cpp
uchar** uc_alloc_contiguous(int size_x, int size_y)
{
    uchar** m = (uchar**)calloc(size_y, sizeof(uchar*));           
    uchar* data = (uchar*)calloc(size_x * size_y, sizeof(uchar)); 
    if (m == NULL || data == NULL) { free(m); free(data); exit(EXIT_FAILURE); }

    for (int i = 0; i < size_y; i++)
        m[i] = data + i * size_x;  
    return m;                       
}
```
<br>

### 3) `"r"`로 열면 RAW 파일을 끝까지 못 읽음

`read_ucmatrix`의 `fopen_s` 모드를 `"rb"`에서 `"r"`로 바꿔 실행했다.
읽기 단계에서 바로 종료됐다.

```text
Data Read Error!

C:\Users\***\source\repos\TestViewer\x64\Debug\TestViewer.exe(프로세스 15088)이(가) 0 코드(0x0)와 함께 종료되었습니다.
```

**원인**

`"r"`은 텍스트 모드다.
Windows의 텍스트 모드는 읽는 도중에 특정 바이트를 바꾼다.

| 바이트 | 텍스트 모드에서 일어나는 일 |
|---|---|
| `0x0D 0x0A` (CR LF) | `0x0A` 한 바이트로 합쳐져 픽셀 하나가 사라진다 |
| `0x1A` (Ctrl+Z) | 파일 끝(EOF)으로 처리되어 그 뒤를 읽지 않는다 |

**해결**

바이너리 모드 `"rb"`로 연다.
바이너리 모드는 바이트를 변환하지 않고 파일 내용 그대로 읽는다.
`write_ucmatrix`도 같은 이유로 `"wb"`를 쓴다.
