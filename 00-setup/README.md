# 00. 개발환경 구축 (Visual Studio + OpenCV)

> 전공 교재를 참고해 설치 과정과 환경 설정들을 정리
> 참고 교재: IOT에서의 디지털 영상처리 [김인겸 저]

## 내 환경

| IDE | OpenCV | 빌드 |
|---|---|---|
| Visual Studio 2026 Community | 3.4.1 | Debug / x64 |

## 1. Visual Studio 설치

Visual Studio는 Visual Studio Installer를 통해 설치하며, 설치 과정에서 어떤 개발 도구를 함께 받을지 "워크로드" 단위로 고른다. C++로 OpenCV를 사용하려면 **C++를 사용한 데스크톱 개발** 워크로드를 선택해야 한다. 이 워크로드에 C++ 소스를 기계어로 번역하는 MSVC 컴파일러와 링커, 그리고 Windows 프로그램을 만들 때 필요한 Windows SDK가 포함되어 있다. VS Code와 달리 Visual Studio는 이 컴파일러를 함께 설치하기 때문에 별도로 gcc 같은 컴파일러를 준비할 필요가 없다.

## 2. OpenCV 설치

OpenCV는 공식 사이트의 Releases 페이지에서 Windows용 패키지를 내려받는다. 패키지는 실행하면 압축이 풀리는 형태로, 지정한 경로(예: `C:\opencv`)에 미리 빌드된 라이브러리가 풀린다. 직접 소스를 컴파일하지 않아도 바로 쓸 수 있다는 것이 이 방식의 장점이다.

압축을 풀면 `build` 폴더 아래에 세 가지가 중요하다. `include` 폴더에는 `opencv2/opencv.hpp` 같은 헤더 파일이 있어 코드에서 OpenCV 함수의 선언을 가져올 때 쓰인다. `x64\vcXX\lib` 폴더에는 링크 단계에서 필요한 `.lib` 파일이, `x64\vcXX\bin` 폴더에는 실행할 때 필요한 `.dll` 파일이 들어 있다. 여기서 `vcXX`는 OpenCV를 빌드한 Visual Studio 컴파일러 버전을 뜻하며, 공식 Windows 패키지는 x64용으로 제공된다.

라이브러리 파일은 `opencv_worldXXX.lib`처럼 모든 모듈이 하나로 합쳐진 형태이고, 이름 끝에 `d`가 붙은 `opencv_worldXXXd.lib`는 Debug 빌드 전용이다. Debug 구성에서 `d`가 없는 라이브러리를 섞어 쓰면 빌드는 되더라도 실행 중 비정상 종료가 날 수 있으므로 구성에 맞는 파일을 연결해야 한다.

## 3. 프로젝트 환경 설정

Visual Studio에서 빈 C++ 프로젝트를 만든 뒤, 상단의 솔루션 플랫폼을 **x64**로 맞춘다. OpenCV 라이브러리가 x64용이기 때문에 플랫폼이 x86이면 링크 단계에서 실패한다. 이후 프로젝트 속성에서 구성을 Debug / x64로 선택한 상태로 아래 설정을 한다.

먼저 **C/C++ → 일반 → 추가 포함 디렉터리**에 `build\include` 경로를 넣는다. 컴파일러는 `#include <opencv2/opencv.hpp>`를 만나면 이 경로에서 헤더를 찾는다. 이 설정이 없으면 컴파일 단계에서 헤더를 찾을 수 없다는 오류가 난다.

다음으로 **링커 → 일반 → 추가 라이브러리 디렉터리**에 `build\x64\vcXX\lib` 경로를, **링커 → 입력 → 추가 종속성**에 `opencv_worldXXXd.lib`를 넣는다. (OpenCV 3.4.1 기준 `opencv_world341d.lib`) 헤더에는 함수의 선언만 있고 실제 구현은 라이브러리에 있기 때문에, 링커가 어떤 파일에서 구현을 가져올지 알려줘야 한다. 이 설정이 빠지면 `cv::imshow` 같은 함수를 찾을 수 없다는 링크 오류가 발생한다.

마지막으로 실행 시 필요한 dll 위치를 알려준다. Windows는 프로그램을 실행할 때 실행 파일과 같은 폴더나 시스템 환경 변수 `Path`에 등록된 폴더에서 dll을 찾는다. 따라서 `build\x64\vcXX\bin` 경로를 시스템 `Path`에 추가하거나, 프로젝트 속성의 **디버깅 → 환경**에 `PATH=...\bin;%PATH%`를 지정한다. 이 설정이 없으면 빌드는 성공하지만 실행하는 순간 dll이 없다는 오류 창이 뜬다.

Release 구성으로 빌드할 때는 같은 설정을 Release / x64 구성에도 반복하되, 추가 종속성에는 `d`가 없는 `opencv_worldXXX.lib`를 넣는다.

## 4. 동작 확인

헤더 없는 8비트 그레이스케일 RAW 파일을 읽어 화면에 띄우는 [`main.cpp`](main.cpp)로 설정을 확인했다. 실행 인수는 프로젝트 속성의 **디버깅 → 명령 인수**에 `<파일 경로> <WIDTH> <HEIGHT>` 형식으로 넣는다. 이미지 창이 뜨면 컴파일, 링크, 실행 단계의 설정이 모두 정상이라는 뜻이다.

### 정상 실행

`boat.512 512 512`

(결과 캡처 추가 예정)

### 잘못된 입력 처리

| 명령 인수 | 출력 |
|---|---|
| `boat.512 256 256` | `[error] size mismatch: file is 262144 bytes, expected 65536 (256 x 256)` |
| `없는파일.512 512 512` | `[error] cannot open file: 없는파일.512` |
| `boat.512 -512 512` | `[error] WIDTH must be positive: -512` |
| `boat.512 abc 512` | `[error] stoi` (숫자가 아닌 입력) |
