10/31 파일

# Git & GitHub 빠른 시작 가이드

## 목차
1. [설치 및 초기 설정](#설치-및-초기-설정)
2. [기본 명령어](#기본-명령어)
3. [브랜치 사용법](#브랜치-사용법)
4. [GitHub 연동](#github-연동)
5. [협업하기](#협업하기)
6. [문제 해결](#문제-해결)

---

## 설치 및 초기 설정

### Git 설치
```bash
# Windows: https://git-scm.com/download/win
# macOS: brew install git
# Linux: sudo apt install git

# 설치 확인
git --version
```

### 초기 설정
```bash
# 사용자 정보 설정
git config --global user.name "Your Name"
git config --global user.email "your.email@example.com"

# 기본 브랜치 이름 설정
git config --global init.defaultBranch main

# 설정 확인
git config --list
```

---

## 기본 명령어

### 저장소 생성
```bash
# 새 프로젝트
git init

# 기존 저장소 복제
git clone https://github.com/username/repository.git
```

### 기본 작업 흐름
```bash
# 1. 상태 확인
git status

# 2. 파일 추가 (스테이징)
git add .              # 모든 파일
git add filename.txt   # 특정 파일

# 3. 커밋
git commit -m "커밋 메시지"

# 4. 히스토리 확인
git log --oneline
```

### 좋은 커밋 메시지
```
feat: 새로운 기능 추가
fix: 버그 수정
docs: 문서 수정
style: 코드 포맷팅
refactor: 리팩토링
test: 테스트 코드
chore: 기타 작업

예시: feat: 로그인 기능 추가
```

### 파일 관리
```bash
# 파일 삭제
git rm filename.txt

# 파일 이름 변경
git mv old.txt new.txt

# 변경사항 취소
git restore filename.txt

# 스테이징 취소
git restore --staged filename.txt
```

---

## 브랜치 사용법

### 기본 명령어
```bash
# 브랜치 목록
git branch

# 브랜치 생성 및 이동
git checkout -b feature-name
# 또는
git switch -c feature-name

# 브랜치 이동
git switch main

# 브랜치 삭제
git branch -d feature-name
```

### 병합 (Merge)
```bash
# main으로 이동
git switch main

# 브랜치 병합
git merge feature-name
```

### 충돌 해결
```bash
# 1. 충돌 파일 확인
git status

# 2. 파일 열어서 아래 부분 찾기
<<<<<<< HEAD
현재 브랜치 내용
=======
병합할 브랜치 내용
>>>>>>> feature-branch

# 3. 원하는 내용으로 수정 후 저장

# 4. 병합 완료
git add .
git commit -m "merge: 충돌 해결"
```

---

## GitHub 연동

### SSH 키 설정 (권장)
```bash
# 1. SSH 키 생성
ssh-keygen -t ed25519 -C "your.email@example.com"

# 2. 공개키 복사
cat ~/.ssh/id_ed25519.pub

# 3. GitHub → Settings → SSH and GPG keys → New SSH key
# 4. 복사한 키 붙여넣기

# 5. 연결 테스트
ssh -T git@github.com
```

### 원격 저장소 연결
```bash
# 원격 저장소 추가
git remote add origin git@github.com:username/repo.git

# 처음 푸시
git push -u origin main

# 이후 푸시
git push

# 원격 변경사항 가져오기
git pull
```

### 기본 워크플로우
```bash
# 1. 최신 코드 받기
git pull

# 2. 작업 브랜치 생성
git checkout -b feature-login

# 3. 코드 작성 후 커밋
git add .
git commit -m "feat: 로그인 기능 추가"

# 4. 푸시
git push -u origin feature-login

# 5. GitHub에서 Pull Request 생성
```

---

## 협업하기

### Fork & Pull Request
```bash
# 1. GitHub에서 Fork 버튼 클릭

# 2. Fork한 저장소 Clone
git clone git@github.com:your-username/repo.git

# 3. 원본 저장소 추가
git remote add upstream git@github.com:original-owner/repo.git

# 4. 작업 브랜치 생성
git checkout -b feature-name

# 5. 코드 작성 후 커밋
git add .
git commit -m "feat: 새 기능 추가"

# 6. 내 저장소에 푸시
git push origin feature-name

# 7. GitHub에서 Pull Request 생성

# 8. 병합 후 최신화
git checkout main
git pull upstream main
git push origin main
```

### PR 작성 템플릿
```markdown
## 변경사항
- 추가된 기능 설명
- 수정된 버그 설명

## 테스트 방법
1. ...
2. ...

관련 이슈: #123
```

---

## 문제 해결

### 자주 쓰는 명령어
```bash
# 커밋 되돌리기
git reset --soft HEAD~1    # 커밋만 취소
git reset HEAD~1           # 커밋 + 스테이징 취소
git reset --hard HEAD~1    # 모든 변경사항 삭제 (⚠️ 위험)

# 커밋 메시지 수정
git commit --amend -m "새 메시지"

# 병합 취소
git merge --abort

# 변경사항 임시 저장
git stash              # 저장
git stash pop          # 복원
git stash list         # 목록 확인

# 브랜치 이름 변경
git branch -m old-name new-name

# 원격 브랜치 삭제
git push origin --delete branch-name
```

### 일반적인 문제

#### 푸시 거부됨
```bash
# 원격에 새 커밋이 있을 때
git pull --rebase
git push
```

#### 잘못된 파일 커밋
```bash
# 아직 푸시 안 했으면
git rm --cached filename
git commit --amend

# 이미 푸시 했으면
git rm --cached filename
git commit -m "remove: 불필요한 파일 제거"
git push
```

#### .gitignore가 안 먹힐 때
```bash
git rm -r --cached .
git add .
git commit -m "chore: .gitignore 적용"
```

---

## 자주 사용하는 .gitignore
```gitignore
# 운영체제
.DS_Store
Thumbs.db

# 에디터
.vscode/
.idea/
*.swp

# 언어별
node_modules/
__pycache__/
*.pyc
.env
.venv/

# 빌드
dist/
build/
*.log
```

---

## 빠른 참조

### 명령어 치트시트

| 작업 | 명령어 |
|------|--------|
| 초기화 | `git init` |
| 복제 | `git clone URL` |
| 상태 확인 | `git status` |
| 추가 | `git add .` |
| 커밋 | `git commit -m "메시지"` |
| 푸시 | `git push` |
| 풀 | `git pull` |
| 브랜치 생성 | `git checkout -b NAME` |
| 브랜치 이동 | `git switch NAME` |
| 병합 | `git merge NAME` |
| 로그 | `git log --oneline` |
| 되돌리기 | `git reset HEAD~1` |

### Git 흐름도
```
Working Directory → Staging Area → Local Repo → Remote Repo
     (작업)            (준비)         (로컬)       (GitHub)
        ↓                ↓              ↓            ↓
    git add        git commit      git push
```

---

## 유용한 링크

- [Git 공식 문서](https://git-scm.com/doc)
- [GitHub 가이드](https://guides.github.com/)
- [Learn Git Branching](https://learngitbranching.js.org/) - 인터랙티브 튜토리얼
- [Oh My Git!](https://ohmygit.org/) - 게임으로 배우는 Git

---

**작성일**: 2024  
**대상**: 초보자  
**예상 소요 시간**: 30분

> 이 가이드가 도움이 되셨다면 ⭐️ Star를 눌러주세요!
