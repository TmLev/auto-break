#ifndef AUTO_BREAK_IMPL_HPP
#define AUTO_BREAK_IMPL_HPP

#include <clang/Tooling/Tooling.h>

#include <memory>

namespace auto_break {

auto MakeFactory() -> std::unique_ptr<clang::tooling::FrontendActionFactory>;

}

#endif  // AUTO_BREAK_IMPL_HPP
