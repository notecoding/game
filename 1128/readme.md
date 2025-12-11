언리얼 엔진 5 초보자 가이드
목차

EP1: 언리얼 엔진 설치 및 실행
EP2: 프로젝트 생성과 기본 가이드
EP3: 블루프린트 기초
EP4: C++ 개발 기초
EP5: 샘플 & 애셋 사용법


EP1: 언리얼 엔진 설치 및 실행
설치 과정

Epic Games 웹사이트 접속

Epic Games 검색 → Download Launcher 클릭
계정 생성 또는 소셜 로그인


런처 실행

좌측 메뉴에서 Unreal Engine 선택
Library 탭에서 엔진 버전 확인
설치되어 있지 않다면 Launch 버튼 클릭


엔진 설치

설치 위치 및 옵션 선택
Installation Options에서 필요한 기능 선택
Apply → Install 클릭



TIP: 내 프로젝트 관리

Library 탭 하단의 My Projects에서 기존 프로젝트 확인 가능
⚠️ 주의: 자동 저장 위치가 아닌 다른 곳에 저장하면 인식 불가


EP2: 프로젝트 생성과 기본 가이드
새 프로젝트 생성

Launch 버튼 → Unreal Project Browser 화면 대기
좌측 메뉴에서 GAMES 선택
원하는 템플릿 선택 (예: Third Person)
프로젝트 이름 입력 후 Create

언리얼 엔진 화면 구성

뷰포트(Viewport): 게임 화면 및 오브젝트 배치 공간
메뉴바/툴바: 기본 동작 제어
아웃라이너(Outliner): 계층 구조 표시
디테일(Detail): 오브젝트 세부 설정
콘텐츠 브라우저: 게임 자료 저장 공간
액터 배치: 기본 오브젝트 제공

기본 조작법

화면 이동: 우클릭 + WASD
오브젝트 조작:

Q: 선택 모드
W: 이동 모드
E: 회전 모드
R: 스케일 모드


스냅 기능: 툴바에서 On/Off 가능
카메라 속도 조절: 툴바에서 설정

레벨 생성 및 환경 설정

Content Browser에서 폴더 생성
우클릭 → Level 생성
환경 라이트 설정:

방법 1: 환경 라이트 믹서 창 사용
방법 2: 액터 배치에서 개별 설정



주요 환경 요소

Sky Light: 간접광 표현
Directional Light: 태양광 시뮬레이션
Sky Atmosphere: 대기 효과
Volumetric Cloud: 구름 생성
Exponential Height Fog: 안개 효과


EP3: 블루프린트 기초
블루프린트 종류
1. 레벨 블루프린트

툴바 → Open Level Blueprint 클릭
해당 레벨에서만 작동하는 스크립트

2. 일반 블루프린트

Content Browser에서 우클릭
Blueprint Class → Actor 선택
재사용 가능한 독립적인 스크립트

블루프린트 화면 구성

상태창: 함수, 변수 등 컨트롤
이벤트 그래프: 블루프린트 작업 공간
디테일: 세부 설정 변경

Practice: 키보드 입력으로 메시지 출력
필요한 요소

Input Mapping Context
Input Action
Print String
EnhancedInputAction

작업 순서

Input Action 생성 (IA_KeyName)
ThirdPerson\Input\IMC_Default 더블클릭
새 매핑 추가 및 키 설정
레벨 블루프린트 열기
EnhancedInputAction 노드 생성
Print String 노드 연결
컴파일 및 테스트


EP4: C++ 개발 기초
Visual Studio 설치

Visual Studio 다운로드
Visual Studio Installer에서 수정 클릭
C++을 사용한 게임 개발 선택
추가 구성 요소 설치:

v143 빌드 도구
MSVC v143 (필수)



프로젝트 연동

UE5에서 Tools → Visual Studio 열기
솔루션 설치 확인
.Net 데스크톱 개발 설치 (필요시)

기본 Actor 클래스 구조
헤더 파일 (.h)
cpp#include "CoreMinimal.h"  // 핵심 헤더
#include "GameFramework/Actor.h"  // Actor 기능
#include "MyActor.generated.h"  // 필수 (맨 마지막)
CPP 파일 (.cpp)
cppvoid BeginPlay()  // 시작 시 1회 실행
void Tick()       // 매 프레임 실행
Practice: 메시지 출력 Actor 생성
코드 작성
cpp// MyActor.h
UFUNCTION()
void LogMessage();

// MyActor.cpp
void AMyActor::LogMessage()
{
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Hello, World!"));
    }
}

void AMyActor::BeginPlay()
{
    Super::BeginPlay();
    LogMessage();
}
블루프린트 생성

C++ 클래스 우클릭
기반 블루프린트 클래스 생성
레벨에 배치 후 테스트

버그 해결: 링크 에러

증상: Visual Studio 재설치 후 빌드 크래시
해결:

Save 폴더 삭제
UE5 및 Visual Studio 재시작




EP5: 샘플 & 애셋 사용법
샘플 프로젝트 가져오기

Epic Games Launcher → 샘플 탭
원하는 콘텐츠 선택
내 라이브러리 추가 클릭
Library 탭에서 프로젝트 생성

애셋 가져오기

Launcher → Fab 탭
모든 애셋 → 필터 설정
가격: 무료 체크
원하는 애셋 선택 → 구독
추가할 프로젝트 선택
프로젝트 내 폴더로 자동 추가

Practice
다운받은 애셋으로 자신만의 레벨 꾸미기!

템플릿 종류
GAMES 카테고리

First Person: 1인칭 시점
Third Person: 3인칭 시점
Top Down: 상부 시점
Virtual Reality: VR 전용
Handheld AR: 모바일 AR
Vehicle: 차량 레이싱

FILM/VIDEO & LIVE EVENTS

Virtual Production: 가상 스튜디오
InCameraVFX: 실시간 CG 배경
nDisplay: 다중 디스플레이
Motion Design: 모션 그래픽
DMX: 조명 제어

ARCHITECTURE

Archvis: 건축 시각화
Collab Viewer: 협업 리뷰
Design Configurator: 커스터마이징 시뮬레이터
Handheld AR: 건축 특화 AR

AUTOMOTIVE

Photo Studio: 차량 포토그래픽
Production Configuration: 실시간 커스터마이징


유용한 단축키

Ctrl + Space: 콘텐츠 브라우저 열기/닫기
Q/W/E/R: 선택/이동/회전/스케일 모드
F: 선택한 오브젝트로 포커스
Alt + 드래그: 복제

참고 자료

UE5 공식 문서
UE5 설치 가이드
UE5 Include What You Use
Character Movement


작성일: 2024
언리얼 엔진 버전: 5.5.4
대상: 초보자
