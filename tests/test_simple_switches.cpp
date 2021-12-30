auto GetInt() -> int;

auto main() -> int {
  switch (GetInt()) {
    case 1:
      return 1;
    case 2:
    default:
      return 3;
  }
}
