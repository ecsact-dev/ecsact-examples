using UnityEngine;

public class StaticCollider : MonoBehaviour {
  int entityId;

  void Start() {

    var xScale = System.Convert.ToInt32(gameObject.transform.localScale.x);
    var yScale = System.Convert.ToInt32(gameObject.transform.localScale.y);

    var xPos = (int)gameObject.transform.position.x;
    var yPos = (int)gameObject.transform.position.y;

    Ecsact.Defaults.Runner.executionOptions.CreateEntity()
        .AddComponent(
            new example.Collider { x_radius = xScale, y_radius = yScale })
        .AddComponent(new example.Position { x = xPos, y = yPos });
  }
}
