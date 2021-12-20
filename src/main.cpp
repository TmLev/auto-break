#include <details/impl.hpp>

#include <clang/Tooling/CommonOptionsParser.h>
#include <clang/Tooling/Tooling.h>

#include <llvm/Support/CommandLine.h>

namespace {

static auto auto_break_category = llvm::cl::OptionCategory{"auto_break options"};

}

auto main(int argc, const char* argv[]) -> int {
  using clang::tooling::ClangTool;
  using clang::tooling::CommonOptionsParser;

  auto expected_parser = CommonOptionsParser::create(argc, argv, auto_break_category);
  if (!expected_parser) {
    llvm::errs() << expected_parser.takeError();
    return 1;
  }

  CommonOptionsParser& options_parser = expected_parser.get();
  auto tool = ClangTool{options_parser.getCompilations(), options_parser.getSourcePathList()};

  return tool.run(auto_break::MakeFactory().get());
}
