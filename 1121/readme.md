# 장애물 런 게임 (Obstacle Run Game)

Unity 2019.2.5f1 버전 기반 3D 런 게임 튜토리얼

## 프로젝트 개요

플레이어가 장애물을 피해 목표 지점까지 달려가는 3D 런 게임입니다. 시간 기록과 최고 기록을 저장하며, 재시작 기능을 포함합니다.

## 주요 기능

- 3인칭 캐릭터 컨트롤
- 장애물 회피 게임플레이
- 타이머 및 기록 시스템
- 낙하 판정 (재시작)
- 목표 지점 도달 시 결과 화면
- 최고 기록 저장 (PlayerPrefs)
- 3D 사운드 효과

## 프로젝트 설정

### 1. 프로젝트 생성
- Unity Hub에서 새 3D 프로젝트 생성
- 프로젝트 이름: `RUN`
- Scene 이름: `Main`

### 2. Standard Assets 임포트
Window → Asset Store에서 다음 항목 임포트:
- `Standard Assets (for Unity 2017.3)`
- 필요한 폴더만 선택:
  - Cameras
  - Characters
  - CrossPlatformInput
  - Prototyping
  - Utility

### 3. 텍스처 에셋 임포트
- `Yughues Free Metal Materials` (Asset Store)

### 4. 사운드 에셋 임포트
- `Free Music Pack` (Asset Store)

## 게임 오브젝트 구성

### 스테이지 구조

#### 바닥 (Floors)
- **Floor1**: Position (0, 0, 0), Scale (1, 1, 1)
- **Floor2**: Position (0, 0, 12), Scale (1, 1, 4)
- **Floor3**: Position (0, 0, 36), Scale (4, 1, 4)
- **Floor4**: Position (0, 0, 54), Scale (1, 1, 1)

#### 장애물
- **BigBlock**: Position (0, 0, 36), Scale (5, 1, 5)
- **Block1**: Position (0, 0, 8), Scale (0.5, 0.5, 0.5)
- **Block2**: Position (12, 0, 24.5), Scale (0.5, 0.5, 0.75)
- **Block3**: Position (12, 0, 33), Scale (1, 1, 1)
- **Block4**: Position (-11, 0, 32), Scale (0.5, 0.5, 0.5)
- **Block5**: Position (-13.5, 0, 38), Scale (0.5, 0.5, 0.5)

#### 배경
- **Wall1**: Position (32, -10, 36), Scale (1, 6, 30)
- **Wall2**: Position (-32, -10, 36), Scale (1, 6, 30)
- **Pillar**: Position (0, -15, 100), Rotation (0, 315, 0), Scale (20, 10, 20)

### 캐릭터
- **Player**: ThirdPersonController
  - Tag: "Player"
  - Position: (0, 0, -1)
  - Scale: (1, 1, 1)

### 카메라
- **MultipurposeCameraRig**: 플레이어 추적 카메라
- Main Camera 삭제

### 라이팅

#### Directional Light
- Intensity: 0.2

#### Spotlights
- **Spotlight1**: Position (0, 10, 0), Rotation (90, 0, 0)
  - Range: 23, Spot Angle: 50, Intensity: 8
- **Spotlight2**: Position (0, 11, 24.6), Rotation (90, 0, 0)
  - Range: 25, Spot Angle: 56
- **Spotlight3**: Position (0, 7.5, 54), Rotation (90, 0, 0)
  - Range: 20, Spot Angle: 34

#### Point Lights
- **Pointlight1**: Position (-19.2, 6, 32)
  - Range: 28, Intensity: 8
- **Pointlight2**: Position (13, 3.5, 39)
  - Range: 8, Intensity: 6

### 게임 영역

#### OutArea (낙하 판정)
- Create → 3D Object → Cube
- Position: (0, -33, 0)
- Scale: (1000, 1, 1000)
- Mesh Renderer 제거
- Box Collider → Is Trigger 체크

#### GoalArea (목표 지점)
- Create → 3D Object → Cube
- Position: (0, 1, 54.5)
- Scale: (4, 2, 3)
- Mesh Renderer 제거
- Box Collider → Is Trigger 체크

## UI 구성

### Canvas 계층 구조
```
Canvas
├── TimeText
└── Result
    ├── ResultTitle
    ├── ResultTimeText
    ├── BestTimeText
    └── RetryButton
        └── Text
```

### TimeText
- Anchor: Left, Top
- Position: (90, -20, 0)
- Text: "Time : 0"
- Font Size: 22
- Color: Red (255, 0, 0, 255)

### ResultTitle
- Anchor: Middle, Center
- Position: (0, 80, 50)
- Width: 200, Height: 50
- Text: "Game Result"
- Font Size: 32
- Alignment: Center
- Color: Red (255, 0, 0, 255)

### ResultTimeText
- Anchor: Middle, Center
- Position: (0, -30, 0)
- Width: 200, Height: 40
- Text: "ResultTime : 0"
- Font Size: 24
- Alignment: Center
- Color: Sky (0, 255, 255, 255)

### BestTimeText
- Anchor: Middle, Center
- Position: (0, 0, 0)
- Width: 200, Height: 40
- Text: "BestTime : 0"
- Font Size: 24
- Alignment: Center
- Color: Sky (0, 255, 255, 255)

### RetryButton
- Anchor: Middle, Center
- Position: (0, -80, 0)
- Width: 160, Height: 30
- Text: "Retry?"
- Font Size: 14
- Alignment: Center

## 스크립트

### 1. Out.cs
OutArea에 부착하여 플레이어 낙하 시 게임 재시작

```csharp
using UnityEngine;
using UnityEngine.SceneManagement;

public class Out : MonoBehaviour
{
    private void OnTriggerEnter(Collider col)
    {
        if(col.gameObject.tag == "Player")
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }
}
```

### 2. GoalArea.cs
GoalArea에 부착하여 목표 도달 여부 관리

```csharp
using UnityEngine;

public class GoalArea : MonoBehaviour
{
    public static bool goal;

    void Start()
    {
        goal = false;
    }

    private void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.tag == "Player")
        {
            goal = true;
        }
    }
}
```

### 3. Timer.cs
TimeText에 부착하여 시간 측정 및 표시

```csharp
using UnityEngine;
using UnityEngine.UI;

public class Timer : MonoBehaviour
{
    public static float time;

    void Start()
    {
        time = 0;
    }

    void Update()
    {
        if (GoalArea.goal == false)
        {
            time += Time.deltaTime;
        }

        int t = Mathf.FloorToInt(time);
        Text uiText = GetComponent<Text>();
        uiText.text = "Time : " + t.ToString();
    }
}
```

### 4. GameResult.cs
Canvas에 부착하여 게임 결과 표시 및 재시작 관리

```csharp
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class GameResult : MonoBehaviour
{
    private int highScore;
    public Text resultTime;
    public Text bestTime;
    public GameObject parts;

    void Start()
    {
        if (PlayerPrefs.HasKey("HighScore"))
        {
            highScore = PlayerPrefs.GetInt("HighScore");
        }
        else
        {
            highScore = 999;
        }
    }

    void Update()
    {
        if (GoalArea.goal)
        {
            parts.SetActive(true);
            int result = Mathf.FloorToInt(Timer.time);
            resultTime.text = "ResultTime " + result;
            bestTime.text = "BestTime " + highScore;

            if (highScore > result)
            {
                PlayerPrefs.SetInt("HighScore", result);
            }
        }
    }

    public void OnRetry()
    {
        SceneManager.LoadScene("Main");
    }
}
```

## 컴포넌트 연결

### GameResult 스크립트 설정 (Canvas)
1. Hierarchy → Canvas 선택
2. Inspector → Game Result (Script)
3. 다음 항목 드래그 앤 드롭:
   - Result Time: ResultTimeText
   - Best Time: BestTimeText
   - Parts: Result 오브젝트

### RetryButton 이벤트 설정
1. Hierarchy → RetryButton 선택
2. Inspector → Button (Script) → On Click()
3. '+' 클릭
4. Canvas를 None으로 드래그
5. No Function → GameResult → OnRetry() 선택

## 사운드 설정

### Audio Source (Pillar)
1. Pillar 선택
2. Add Component → Audio → Audio Source
3. 설정:
   - AudioClip: Road Hard - Solo
   - Loop: 체크
   - Spatial Blend: 1 (3D 사운드)

## 텍스처 적용

### 바닥 (Floor1-4)
- Metal textures pack → pattern 13 → diffuse

### 벽 (Wall1-2)
- Metal textures pack → pattern 09 → diffuse

### 장애물 (Block1-5)
- Metal textures pack → pattern 02 → diffuse

### BigBlock
- Metal textures pack → pattern 10 → diffuse

### Pillar
- Metal textures pack → pattern 14 → diffuse

## 빌드 전 필수 설정

**중요**: Lighting Settings 설정 (씬 재시작 시 조명 변경 방지)

```
Window → Rendering → Lighting Settings
- Auto Generate 체크 해제
- Generate Lighting 클릭
```

## 주요 설정

### Transform 좌표계
- X축: 좌우 (Right)
- Y축: 상하 (Up)
- Z축: 전후 (Forward)

### 조작 방법
- **WASD** / **방향키**: 이동
- **Space**: 점프

## 게임 플레이 흐름

1. **게임 시작**
   - 타이머 시작
   - Player는 (0, 0, -1) 위치에서 시작

2. **플레이**
   - 캐릭터 이동 및 장애물 회피
   - 화면 좌측 상단에 경과 시간 표시

3. **낙하 시**
   - OutArea 진입
   - 씬 자동 재시작

4. **목표 도달 시**
   - GoalArea 진입
   - 타이머 정지
   - 결과 화면 표시
   - 현재 기록과 최고 기록 비교
   - 최고 기록 갱신 (더 빠른 기록인 경우)

5. **재시작**
   - Retry 버튼 클릭
   - Main 씬 재로드

## 프로젝트 구조

```
RUN/
├── Assets/
│   ├── Scenes/
│   │   └── Main.unity
│   ├── Standard Assets/
│   │   ├── Cameras/
│   │   ├── Characters/
│   │   ├── CrossPlatformInput/
│   │   ├── Prototyping/
│   │   └── Utility/
│   ├── Metal textures pack/
│   ├── Free Music Pack/
│   └── Scripts/
│       ├── Out.cs
│       ├── GoalArea.cs
│       ├── Timer.cs
│       └── GameResult.cs
└── ...
```

## 개발 정보

- **Unity Version**: 2019.2.5f1
- **제작자**: 김진우 (2016848029)
- **과목**: 게임프로그래밍04

## 참고 자료

- (초보자를 위한) 유니티 5 입문 - 아라카와 다쿠야, 아사노 유이치 지음, 윤준 옮김, 한빛미디어
- [Unity 관련 튜토리얼](http://wapiduck.tistory.com/529)
- [Unity Lighting 이슈 해결](http://answers.unity3d.com/questions/919940/applicationloadlevel-changeslighting-for-some=rea.html)

## 라이선스

이 프로젝트는 교육 목적으로 제작되었습니다.

---

**Note**: 이 프로젝트는 Unity 2019.2.5f1에서 테스트되었습니다. 다른 버전에서는 일부 수정이 필요할 수 있습니다.
