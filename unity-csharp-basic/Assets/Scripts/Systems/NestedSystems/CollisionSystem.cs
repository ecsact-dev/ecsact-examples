using UnityEngine;

public class CollisionSystem : MonoBehaviour {

  [Ecsact.DefaultSystemImpl(typeof(example.CollisionComparer.CheckCollision))]
  public static void
  CheckCollision(EcsactRuntime.SystemExecutionContext context) {
    if (context.Same(context.Parent()))
      return;

    var position = context.Get<example.Position>();
    var velocity = context.Get<example.Velocity>();

    var otherPos = context.Parent().Get<example.Position>();
    var other_collider = context.Parent().Get<example.Collider>();

    var xDiff = System.Math.Abs(position.x - otherPos.x);
    var yDiff = System.Math.Abs(position.y - otherPos.y);

    if (xDiff <= other_collider.x_radius && yDiff <= other_collider.y_radius) {
      position.x = position.prev_x;
      position.y = position.prev_y;

      if (position.x < otherPos.x) {
        velocity.x_value = -0.5f;
      } else {
        velocity.x_value = 0.5f;
      }

      if (position.y < otherPos.y) {
        velocity.y_value = -0.5f;
      } else {
        velocity.y_value = 0.5f;
      }

      context.Update<example.Velocity>(velocity);
      context.Update<example.Position>(position);
    }
  }
}
