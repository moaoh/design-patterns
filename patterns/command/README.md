## [Command Pattern](https://refactoring.guru/ko/design-patterns/command)



커맨드 패턴은 실행할 동작을 객체로 캡슐화하는 디자인패턴

이를 통해 호출자는 구체적인 동작내용을 알지 못해도 실행과 취소를 관리가능

---

- Command (인터페이스)
  - 모든 구체 커맨드가 구현해야 하는 `execute()`, `undo()` 메서드를 정의
- Editor (Receiver)
  - 실제 텍스트 편집 기능을 담당
- WriteCommand (ConcreteCommand)
  - `Editor`에 텍스트를 작성하는 구체적인 커맨드 클래스
  - 실행(`execute`)과 취소(`undo`) 로직을 함께 캡슐화
- CommandInvoker (Invoker)
  - 커맨드를 실행하고 기록하며, 실행 취소를 요청받으면 가장 최근의 커맨드를 삭제
- Client (main)
  - 커맨드를 생성하여 Invoker에 전달