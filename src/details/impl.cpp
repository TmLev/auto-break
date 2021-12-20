#include <details/impl.hpp>

#include <clang/AST/ASTContext.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>

#include <clang/Frontend/FrontendActions.h>
#include <clang/Tooling/Tooling.h>

#include <llvm/ADT/StringRef.h>

#include <memory>

namespace auto_break {

constexpr auto kSwitchCase = "switch_case";

class MatchCallback : public clang::ast_matchers::MatchFinder::MatchCallback {
 public:
  using MatchResult = clang::ast_matchers::MatchFinder::MatchResult;

  auto run(const MatchResult& result) -> void override {
    const auto switch_case = result.Nodes.getNodeAs<clang::SwitchCase>(kSwitchCase);
  }

 private:
};

class Consumer : public clang::ASTConsumer {
 public:
  using MatchFinder = clang::ast_matchers::MatchFinder;

  Consumer() {
    using namespace clang::ast_matchers;  // NOLINT
    const auto matcher = switchCase(isExpansionInMainFile()).bind(kSwitchCase);
    match_finder_.addMatcher(matcher, &match_callback_);
  }

  auto HandleTranslationUnit(clang::ASTContext& context) -> void override {
    match_finder_.matchAST(context);
  }

 private:
  MatchCallback match_callback_;
  MatchFinder match_finder_;
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
