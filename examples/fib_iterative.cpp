int fib(int n)
{
  if (n <= 1) return n;
  int a = 0, b = 1, c;
  for (int i = 2; i <= n; ++i)
  {
    c = a + b;
    a = b;
    b = c;
  }
  return b;
}

int main(int argc, char**)
{
  auto const result = fib(argc == 1 ? 35 : 0);
  return result == 9227465 ? 0 : 1;
}
