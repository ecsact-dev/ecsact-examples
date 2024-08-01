using UnityEngine;

public class MoveSystems : MonoBehaviour
{

  [Ecsact.DefaultSystemImpl(typeof(example.Move))]
  public static void Move(EcsactRuntime.SystemExecutionContext context)
  {
    var velocity = context.Get<example.Velocity>();
    var move = context.Action<example.Move>();

    velocity.x_value += move.dir_x;
    velocity.y_value += move.dir_y;

    context.Update(velocity);
  }

  [Ecsact.DefaultSystemImpl(typeof(example.ApplyVelocity))]
  public static void
  ApplyVelocity(EcsactRuntime.SystemExecutionContext context)
  {
    var position = context.Get<example.Position>();
    var velocity = context.Get<example.Velocity>();

    position.prev_x = position.x;
    position.prev_y = position.y;

    position.x += velocity.x_value;
    position.y += velocity.y_value;

    context.Update(position);
  }
}
