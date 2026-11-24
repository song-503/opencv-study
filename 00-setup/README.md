# 00. 개발환경 구축 (Visual Studio + OpenCV)

## 목표
Visual Studio에서 OpenCV(C++) 프로젝트를 빌드하고 이미지 한 장을 띄운다.

## 설치 정보
- Visual Studio: (버전)
- OpenCV: (버전), 설치 경로: (예: `C:\opencv`)

## 설치 과정
1. OpenCV Windows 패키지 다운로드 및 압축 해제
2. 환경변수 `OPENCV_DIR` = `...\opencv\build` 설정
3. `OpenCV.props`의 `OpenCVVer`, `OpenCVVc` 값을 설치 버전에 맞게 수정
   - `OpenCVVer`: `build\x64\vcXX\lib` 안의 `opencv_worldXXXX.lib` 숫자
   - `OpenCVVc`: `build\x64` 아래 폴더명
4. VS에서 빈 C++ 프로젝트 생성 → 플랫폼 **x64** 확인
5. 속성 관리자 → 기존 속성 시트 추가 → `OpenCV.props`
6. 테스트 코드 실행

## 왜 절대경로 대신 환경변수 + props를 쓰나
(직접 정리)

## 막힌 점
- 문제:
- 원인:
- 해결:

## 확인 문제
<details>
<summary>Q1. Debug 빌드에서 opencv_worldXXXX.lib(뒤에 d 없음)를 링크하면 어떤 문제가 생기나?</summary>

(답 작성)
</details>

<details>
<summary>Q2. 빌드는 되는데 실행하면 "dll을 찾을 수 없습니다"가 뜨는 이유와 해결법은?</summary>

(답 작성)
</details>
