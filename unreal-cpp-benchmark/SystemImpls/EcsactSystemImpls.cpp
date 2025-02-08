
#include "generated/EcsactBenchmark.ecsact.hh"
#include "generated/EcsactBenchmark.ecsact.systems.hh"

auto benchmark::IterateCounter::impl(context &ctx) -> void {
  auto counter = ctx.get<Counter>();

  counter.value += 1;
  ctx.update(counter);
}
