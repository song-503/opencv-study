# 05. 얼굴 검출 + 모자이크

## 목표
이미지에서 얼굴을 검출하고, 검출된 영역에만 모자이크를 적용한다.

## 공부할 것
- [ ] Haar Cascade 얼굴 검출 (`CascadeClassifier`, `detectMultiScale`)
- [ ] 검출 결과(Rect)에 04단원 모자이크 적용
- [ ] (확장) DNN 기반 얼굴 검출과 정확도 비교

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

## 개인정보 보호 관점
얼굴 검출 + 모자이크는 CCTV·영상 공개 시 쓰이는 **영상 개인정보 비식별 처리**의 기본 형태다.

- 한계 1: 측면·가림·저조도 얼굴은 미검출 → 얼굴이 그대로 노출됨
- 한계 2: 블록이 작거나 블러가 약하면 복원·식별 가능성이 남음
- 개선 방향: (직접 정리)

## 막힌 점
- 문제:
- 원인:
- 해결:

## 확인 문제
<details>
<summary>Q1. detectMultiScale의 scaleFactor / minNeighbors 값을 바꾸면 결과가 어떻게 달라지나?</summary>

(답 작성)
</details>

<details>
<summary>Q2. 얼굴 검출이 실패(미검출)했을 때 비식별 처리 관점에서 어떤 문제가 생기나?</summary>

(답 작성)
</details>
