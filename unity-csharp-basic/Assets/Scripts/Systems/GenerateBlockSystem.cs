using UnityEngine;

public class GenerateBlockSystem : MonoBehaviour {

  [Ecsact.DefaultSystemImpl(typeof(example.PerformGenerateBlock))]
  public static void
  PerformGenerateBlock(EcsactRuntime.SystemExecutionContext context) {
    var action = context.Action<example.PerformGenerateBlock>();

    context.Add<example.QueueBlock>(
        new example.QueueBlock { pos_x = action.pos_x, pos_y = action.pos_y });
  }

  [Ecsact.DefaultSystemImpl(typeof(example.GenerateBlock))]
  public static void
  GenerateBlock(EcsactRuntime.SystemExecutionContext context) {
    var builder = context.Generate();
    var block = context.Get<example.QueueBlock>();

    builder.AddComponent<example.CanMove>(new example.CanMove {})
        .AddComponent<example.Block>(new example.Block {})
        .AddComponent<example.Position>(
            new example.Position { x = block.pos_x, y = block.pos_y })
        .AddComponent<example.Collider>(
            new example.Collider { x_radius = 4, y_radius = 4 })
        .AddComponent<example.Velocity>(
            new example.Velocity { x_value = 0, y_value = 0, speed = 0.1f })
        .Finish();
  }
}
