#include <details/impl.hpp>

#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/Tooling.h>

#include <llvm/ADT/StringRef.h>

#include <memory>

namespace auto_break {

class Consumer : public clang::ASTConsumer {
 public:
  Consumer() = default;
};

class Action : public clang::ASTFrontendAction {
 public:
  Action() = default;

  auto CreateASTConsumer(clang::CompilerInstance& compiler, llvm::StringRef filename)
      -> std::unique_ptr<clang::ASTConsumer> override {
    return std::make_unique<Consumer>();
  }
};

class Factory : public clang::tooling::FrontendActionFactory {
 public:
  Factory() = default;

  auto create() -> std::unique_ptr<clang::FrontendAction> override {
    return std::make_unique<Action>();
  }
};

////////////////////////////////////////////////////////////////////////////////////////////////////

auto MakeFactory() -> std::unique_ptr<clang::tooling::FrontendActionFactory> {
  return std::make_unique<Factory>();
}

}  // namespace auto_break
