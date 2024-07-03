using UnityEngine;
using UnityEngine.InputSystem;

public class MoveControls : MonoBehaviour {
  public InputAction moveInput;

  example.Move moveAction;

  private Vector2 currentDirection = Vector2.zero;

  void Start() {
    moveInput.Enable();

    moveInput.performed += OnMove;
    moveInput.started += OnMove;
    moveInput.canceled += OnMove;

    moveAction = new example.Move {};
  }

  void OnDisable() {
    moveInput.Disable();

    moveInput.started -= OnMove;
    moveInput.performed -= OnMove;
    moveInput.canceled -= OnMove;
  }

  public void OnMove(InputAction.CallbackContext context) {
    var direction = context.ReadValue<Vector2>();

    if (direction != currentDirection) {
      currentDirection = direction;
      moveAction.dir_x = direction.x;
      moveAction.dir_y = direction.y;
      Ecsact.Defaults.Runner.executionOptions.PushAction(moveAction);
    }
  }
}
