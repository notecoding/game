# 🎮 게임 프로그래밍 요약 (Unity - 간단 예제 & 캐릭터 이동)

---

# 📌 1. 간단한 예제: RollingBall 프로젝트

## ✔ 씬 기본 설정
- Main Camera 위치 초기화  
  - Position: (0, 0, 0)
- 씬 기즈모로 방향 조정  
- X는 오른쪽, Y는 위 방향으로 설정

---

## ✔ 바닥(Floor) 만들기
- `Hierarchy → 3D Object → Cube`
- 이름: **Floor**
- Transform  
  - Position: (0, 0, 0)  
  - Scale: (10, 0.5, 5)

---

## ✔ Scene 뷰 조작(Tip)
- Alt + 드래그 → 시점 회전  
- Ctrl + Alt + 드래그 → 시점 평행 이동  
- 마우스 휠 → Zoom  
- F → 선택된 오브젝트에 시점 고정  
- Q/W/E/R/T → Move·Rotate·Scale 도구 전환  
- Directional Light는 한 방향으로 빛을 쏘는 광원

---

## ✔ 벽(Wall) 만들기
### Wall01
- Position: (-5.3, 4.6, 0)  
- Scale: (1, 10, 5)

### Wall02
- Wall01 복제(Duplicate) 후 위치만 변경  
- Position: (5.3, 4.6, 0)

### Wall03
- Position: (0, 4.6, 2)  
- Scale: (10, 10, 1)

---

## ✔ 카메라·라이트 조정
### Main Camera
- Position: (0, 8, -11.9)  
- Rotation: (18, 0, 0)

### Directional Light
- Position: (0, 0, -11.9)  
- Rotation: (10, 0, 0)

---

## ✔ 경사면(Slope) 만들기 (1~5)
- Cube 생성 후 이름 변경(Slope01~05)
- 위치/각도/크기 단계적으로 조정
- 여러 개의 Slope를 이어서 구불구불한 경사로 구성

예시:
- Slope01 → Rotation Z: -10°, Position: (-1, 8.57, 1)  
- Slope04 → Rotation Z: +8°, Position: (0.9, 6.2, 1)

---

## ✔ 공(Ball) 만들기
- `3D Object → Sphere`
- 이름: Ball  
- Position: (-4.4, 9.58, 0.7)  
- Scale: (0.4, 0.4, 0.4)

---

## ✔ 물리 적용 (Physics)
- Ball 선택 → `Component → Physics → Rigidbody`
- Use Gravity 체크

---

## ✔ 탄성(Bounce) 적용
1. Project에서  
   - Create → Physic Material → **Bounce**
2. Bounce의 Bounciness: **0.6**
3. Ball의 Sphere Collider → Material에 Bounce 적용

---

## ✔ 공의 색상(Material) 변경
- Material 생성(이름: Ball Material)
- Color 변경 후
- Material을 Ball 오브젝트에 드래그

---

---

# 📌 2. 캐릭터 이동: QueryChan Controller

## ✔ 리소스 Import
- Menu → Assets → Import Package → Custom Package  
- `Chapter4 Terrain.unitypackage` 가져오기

---

## ✔ 캐릭터 스크립트 생성
- `Assets → Script → Create → C# Script`
- 이름: **QueryChanController**

### ✨ 주요 기능 포함
- 이동 (WASD, 방향키)  
- 점프  
- 애니메이션 연동  
- CharacterController 기반 이동 처리

---

## ✔ 캐릭터 이동 코드 요약
```csharp
public class QueryChanController : MonoBehaviour
{
    public float speed = 3.0f;
    public float jumpPower = 6.0f;

    private Vector3 direction;
    private CharacterController controller;
    private Animator anim;

    void Start()
    {
        controller = GetComponent<CharacterController>();
        anim = GetComponent<Animator>();
    }

    void Update()
    {
        float x = Input.GetAxis("Horizontal");
        float y = Input.GetAxis("Vertical");

        Vector3 inputDir = new Vector3(x, 0, y);
        direction = Vector3.zero;

        if (inputDir.magnitude > 0.1f)
        {
            transform.LookAt(transform.position + inputDir);
            direction += transform.forward * speed;
            anim.SetFloat("Speed", direction.magnitude);
        }
        else anim.SetFloat("Speed", 0);

        if (Input.GetButton("Jump"))
        {
            anim.SetTrigger("Jump");
            direction.y += jumpPower;
        }

        controller.Move(direction * Time.deltaTime);
        direction.y += Physics.gravity.y * Time.deltaTime;
    }
}
