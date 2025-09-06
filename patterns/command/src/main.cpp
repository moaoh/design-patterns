#include <iostream>
#include <memory>
#include <stack>

/**
 * @brief Command : 실행과 실행 취소 기능을 캡슐화
 */
class Command {
 public:
  virtual ~Command() = default;
  virtual void execute() = 0;
  virtual void undo() = 0;
};

/**
 * @brief Editor : 실제 텍스트를 다루는 클래스
 * command 객체들은 해당 클래스의 기능을 호출하여 작업을 수행.
 */
class Editor {
 public:
  void write(const std::string& text) {
    content_ += text;
  }

  void eraseLast(size_t len) {
    if (len <= content_.size()) {
      content_.erase(content_.size() - len);
    }
  }

  void show() const {
    std::cout << "[Editor] " << content_ << "\n";
  }

 private:
  std::string content_;
};

/**
 * @brief WriteCommand : 특정 텍스트를 Editor에 작성하는 커맨드
 * - 실행 시 Editor::write() 호출.
 * - 취소 시 Editor::eraseLast() 호출.
 */
class WriteCommand : public Command {
 public:
  WriteCommand(Editor& editor, std::string text) : editor_(editor), text_(std::move(text)) {
  }

  void execute() override {
    editor_.write(text_);
  }

  void undo() override {
    editor_.eraseLast(text_.size());
  }

 private:
  Editor& editor_;
  std::string text_;
};

/**
 * @brief CommandInvoker : 커맨드를 실행하고 실행 이력을 관리
 * - 실행 취소(Undo)를 요청하면 최근 커맨드를 꺼내서 되돌림
 */
class CommandInvoker {
 public:
  void run(std::unique_ptr<Command> cmd) {
    cmd->execute();
    history_.push(std::move(cmd));
  }

  void undo() {
    if (history_.empty())
      return;
    auto cmd = std::move(history_.top());
    history_.pop();
    cmd->undo();
  }

 private:
  std::stack<std::unique_ptr<Command>> history_;
};

int main() {
  Editor editor1;
  Editor editor2;
  CommandInvoker invoker;

  // editor1에 쓰기
  invoker.run(std::make_unique<WriteCommand>(editor1, "Hello "));
  // editor2에 쓰기
  invoker.run(std::make_unique<WriteCommand>(editor2, "World!"));

  editor1.show();  // [Editor] Hello
  editor2.show();  // [Editor] World!

  // Undo : 마지막 커맨드 실행 취소 (editor2에서 실행한 것)
  invoker.undo();

  editor1.show();  // [Editor] Hello
  editor2.show();  // [Editor] (빈 문자열)
}