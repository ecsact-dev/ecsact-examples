using UnityEngine;

public class GenerateBlockSystem : MonoBehaviour
{

  [Ecsact.DefaultSystemImpl(typeof(example.PerformGenerateBlock))]
  public static void
  PerformGenerateBlock(EcsactRuntime.SystemExecutionContext context)
  {
    var action = context.Action<example.PerformGenerateBlock>();

    context.Add(
        new example.QueueBlock { pos_x = action.pos_x, pos_y = action.pos_y });
  }

  [Ecsact.DefaultSystemImpl(typeof(example.GenerateBlock))]
  public static void
  GenerateBlock(EcsactRuntime.SystemExecutionContext context)
  {
    var builder = context.Generate();
    var block = context.Get<example.QueueBlock>();

    builder.AddComponent(new example.CanMove { })
        .AddComponent(new example.Block { })
        .AddComponent(
            new example.Position { x = block.pos_x, y = block.pos_y })
        .AddComponent(
            new example.Collider { x_radius = 4, y_radius = 4 })
        .AddComponent(
            new example.Velocity { x_value = 0, y_value = 0, speed = 0.1f })
        .Finish();
  }
}
