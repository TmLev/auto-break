#ifndef AUTO_BREAK_MATCH_CALLBACK_HPP
#define AUTO_BREAK_MATCH_CALLBACK_HPP

#include <bind_ids.hpp>

#include <clang/ASTMatchers/ASTMatchFinder.h>

namespace auto_break {

class MatchCallback : public clang::ast_matchers::MatchFinder::MatchCallback {
 public:
  auto run(const clang::ast_matchers::MatchFinder::MatchResult& match_result) -> void override;
};

}  // namespace auto_break

#endif  // AUTO_BREAK_MATCH_CALLBACK_HPP
