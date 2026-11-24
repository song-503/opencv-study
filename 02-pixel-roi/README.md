# 02. 픽셀 접근 / ROI

## 목표
픽셀 값을 직접 읽고 바꾸며, 이미지의 일부 영역(ROI)만 다룬다.

## 공부할 것
- [ ] `at<Vec3b>()` vs 포인터 접근 (`ptr`) 속도 차이
- [ ] `Rect`로 ROI 지정
- [ ] ROI와 원본의 데이터 공유, `clone()` / `copyTo()` 차이

## 핵심 개념 정리
(직접 정리)

## 코드 핵심
전체 코드는 [`main.cpp`](main.cpp). 중요한 부분만 발췌해서 설명.

```cpp
// 핵심 코드
```

## 결과
| 원본 | 결과 |
|---|---|
| ![](result/before.png) | ![](result/after.png) |

## 막힌 점
- 문제:
- 원인:
- 해결:

## 확인 문제
<details>
<summary>Q1. ROI를 수정하면 원본 이미지도 바뀌는 이유는?</summary>

(답 작성)
</details>

<details>
<summary>Q2. 이미지 범위를 벗어나는 Rect로 ROI를 잡으면 어떻게 되고, 어떻게 막아야 하나?</summary>

(답 작성)
</details>
