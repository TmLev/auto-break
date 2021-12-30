auto GetInt() -> int;

auto main() -> int {
  switch (GetInt()) {
    case 1:
      [[fallthrough]];
    case 2:
      return 2;
    default:
      return 0;
  }
}
