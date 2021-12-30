#include <match_callback.hpp>

#include <clang/AST/Attr.h>
#include <clang/AST/Stmt.h>
#include <clang/ASTMatchers/ASTMatchFinder.h>
#include <clang/Basic/Diagnostic.h>
#include <clang/Frontend/FrontendActions.h>

#include <llvm/Support/Casting.h>

#include <variant>

namespace {

struct ShouldSkip {};

struct MissingBreak {
  [[maybe_unused]] const clang::Stmt* stmt_before_next_case;
  [[maybe_unused]] const clang::SwitchCase* next_case;
};

// clang-format off
using InspectionResult = std::variant<
    ShouldSkip,
    MissingBreak
>;
// clang-format on

auto InspectSwitchCase(const clang::SwitchCase* switch_case) -> InspectionResult {
  const clang::Stmt* stmt_before_next_case = switch_case;
  const clang::SwitchCase* next_case = nullptr;

  for (const clang::Stmt* sub_stmt : switch_case->children()) {
    // Case has fallen through into another case.
    if (llvm::isa<clang::SwitchCase>(sub_stmt)) {
      next_case = llvm::dyn_cast<clang::SwitchCase>(sub_stmt);
      break;
    }

    // Case has `break` statement.
    if (llvm::isa<clang::BreakStmt>(sub_stmt)) {
      return ShouldSkip{};
    }

    // Case has `return` statement.
    if (llvm::isa<clang::ReturnStmt>(sub_stmt)) {
      return ShouldSkip{};
    }

    // Case has `[[fallthrough]]` attribute.
    if (llvm::isa<clang::AttributedStmt>(sub_stmt)) {
      const auto* attributed_stmt = llvm::dyn_cast<clang::AttributedStmt>(sub_stmt);
      for (const clang::Attr* attribute : attributed_stmt->getAttrs()) {
        if (llvm::isa<clang::FallThroughAttr>(attribute)) {
          return ShouldSkip{};
        }
      }
    }

    stmt_before_next_case = sub_stmt;
  }

  return MissingBreak{
      .stmt_before_next_case = stmt_before_next_case,
      .next_case = next_case,
  };
}

}  // namespace

namespace auto_break {

auto MatchCallback::run(const clang::ast_matchers::MatchFinder::MatchResult& match_result) -> void {
  const auto switch_stmt = match_result.Nodes.getNodeAs<clang::SwitchStmt>(kSwitchStmtID);

  for (const clang::SwitchCase* switch_case = switch_stmt->getSwitchCaseList();
       switch_case != nullptr; switch_case = switch_case->getNextSwitchCase()) {
    const InspectionResult inspection_result = InspectSwitchCase(switch_case);

    if (std::holds_alternative<ShouldSkip>(inspection_result)) {
      continue;
    }

    [[maybe_unused]] const auto missing_break = std::get<MissingBreak>(inspection_result);

    clang::DiagnosticsEngine& diagnostics = match_result.Context->getDiagnostics();
    const unsigned id = diagnostics.getCustomDiagID(clang::DiagnosticsEngine::Warning,
                                                    "Case is missing `break` statement");
    clang::DiagnosticBuilder builder = diagnostics.Report(switch_case->getKeywordLoc(), id);
  }
}

}  // namespace auto_break
