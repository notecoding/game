# 🎮 게임 프로그래밍 OT 요약 (C 언어)

## 📌 OT 핵심 내용 정리
- 게임 프로그래밍을 **C 언어 기반으로 배우는 과정** 소개
- Dev-C++, VSCode 등 개발 환경 설정 안내  
- 콘솔 기반 게임 제작을 위한 기본 개념 학습  
  - 커서 이동(gotoxy)  
  - 화면 지우기(system("cls"))  
  - 키보드 입력(getch, getchar, getche)  
  - ASCII 코드 / 스캔 코드 이해  
- 화살표 키 입력에 따른 캐릭터 이동 구현  
- 텍스트를 이용한 **사각형·격자 그리기**  
- 메뉴 기반 프로그램 구현 (switch + getch 활용)  
- 난수 생성(rand, srand) 및 중복 없는 로또 번호 생성  
- 가변 인수 함수(stdarg.h) 사용법 소개  

---

## 🛠 사용 언어 및 개발 환경
- **Language** : C  
- **Compiler** : gcc / Dev-C++ / VSCode  
- **Header** : `<stdio.h>`, `<conio.h>`, `<windows.h>`, `<stdlib.h>`, `<stdarg.h>`  

---

## 🧩 학습한 주요 기능

### ✔ 콘솔 제어
- `gotoxy(x, y)`로 커서 위치 이동  
- `system("cls")`로 화면 지우기  
- 텍스트 모드에서 사각형·격자 그리기  

### ✔ 키보드 입력 처리
- `getch()`로 즉시 입력 받기  
- ASCII 코드 vs 확장키(스캔 코드) 구분  
- 화살표 키 입력에 따라(x, y) 좌표 이동  

### ✔ 난수 생성
- `rand() % n` 형식으로 범위 난수 생성  
- 중복 없는 난수(로또 번호) 생성  
- 정렬(selection sort) 적용  

### ✔ 메뉴 만들기
- 메인 메뉴 → 서브 메뉴 → 기능 호출 구조  
- `switch` + `getch()` 로 번호 입력 처리  
- "아무 키나 누르기"로 화면 전환  

### ✔ 가변 인수 함수
- `stdarg.h`  
- `va_list`, `va_start`, `va_arg`, `va_end`  
- printf와 비슷한 형태의 함수 작성 가능  

---

## 🎯 향후 목표
- 콘솔 게임 기본 모듈 완성  
- 캐릭터 이동, 맵, 충돌 처리 등 구현  
- 난수 기반 이벤트 처리  
- 간단한 텍스트 기반 게임 제작  

---

## 📘 참고 링크
- https://kcoder.tistory.com/  
- https://plustag.tistory.com/  
- https://dojang.io  
- http://egloos.zum.com/EireneHue/v/350618

