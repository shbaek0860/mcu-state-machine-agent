# mcu-state-machine-agent

## 소개
이 프로젝트는 제한된 자원을 가진 MCU(Microcontroller Unit) 환경에서 동작하는 가열 모듈 제어용 상태 머신(State Machine) 펌웨어 템플릿입니다. 단일 책임 원칙(SRP)과 오버헤드 최소화 기법을 적용하여, AI 기반 코드 생성기와 협업할 때 안전하고 예측 가능한 코드를 생성할 수 있도록 최적화된 아키텍처를 제공합니다.

## 주요 기능
- **단일 책임 원칙(SRP) 준수 상태 머신**: 최대 100줄 이하의 모듈화된 함수로 구성된 깔끔한 상태 제어 로직 (IDLE, HEATING, COOLING, ERROR).
- **MCU 스택 오버헤드 최적화**: 하드웨어 제어 함수에 `inline` 처리를 적용하여 메모리 및 실행 속도 최적화.
- **안전성 검증 아키텍처**: 타이머 및 인터럽트 서비스 루틴(ISR) 내 자원 경합(Race Condition) 방지를 고려한 이벤트 큐 설계.
- **AI-Assisted Development 지향**: `AGENTS.md`에 정의된 룰셋을 통해 AI 에이전트가 펌웨어 코드를 안전하게 유지보수 및 확장할 수 있는 가이드라인 제공.

## 사용 방법
1. **다운로드**:
   ```bash
   git clone https://github.com/shbaek0860/mcu-state-machine-agent.git
   cd mcu-state-machine-agent
   ```
2. **빌드 및 실행** (GCC 환경 필요):
   ```bash
   make
   ./mcu_heater_agent
   ```

## 라이선스
Apache License 2.0