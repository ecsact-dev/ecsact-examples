using UnityEngine;
using UnityEngine.InputSystem;

public class GenerateBlock : MonoBehaviour {
  int entityId;

  public InputAction mouseAction;
  example.PerformGenerateBlock generateBlockAction;

  void Start() {
    mouseAction.Enable();
    mouseAction.performed += OnMouseClick;

    Ecsact.Defaults.Runner.executionOptions.CreateEntity().AddComponent(
        new example.BlockGenerator {});
  }

  public void OnMouseClick(InputAction.CallbackContext context) {
    Vector3 mousePos = Mouse.current.position.ReadValue();
    Vector3 worldPos = Camera.main.ScreenToWorldPoint(mousePos);

    generateBlockAction.pos_x = (int)worldPos.x;
    generateBlockAction.pos_y = (int)worldPos.y;

    Debug.Log("PushAction");
    Ecsact.Defaults.Runner.executionOptions.PushAction(generateBlockAction);
  }
}
