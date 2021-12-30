[[noreturn]] auto DoesNotReturn() -> void;

auto GetInt() -> int;

auto main() -> int {
  switch (GetInt()) {
    case 2:
      DoesNotReturn();
  }
}
