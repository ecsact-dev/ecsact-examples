using System.Collections;
using System.Collections.Generic;
using System;
using UnityEngine;

public class BasicExample : MonoBehaviour {

  List<System.Action> cleanUpFns = new();

  int entityId;

  void Start() {

    cleanUpFns.AddRange(new[] {
      // Callback that's invoked upon adding a component
      Ecsact.Defaults.Runtime.OnInitComponent<example.Example>(
          (entity, component) => {
            Debug.Log("Example component added");
            Debug.Log(component.example_value);
          }),
      // Callback that's invoked on the update of a component
      Ecsact.Defaults.Runtime.OnUpdateComponent<example.Example>(
          (entity, component) => { Debug.Log(component.example_value); }),
      // Callback that's invoked on the removal of a component
      Ecsact.Defaults.Runtime.OnRemoveComponent<example.ToBeRemoved>(
          (entity, component) => { Debug.Log("Component removed"); }),
      // Callback that's invoked when an entity is created
      Ecsact.Defaults.Runtime.OnEntityCreated(
          (entityId, placeholderId) => { Debug.Log("Entity created"); })
    });

    // Declare an Example component type
    var exampleComponent = new example.Example {
      example_value = 5,
    };

    // Declare a ToBeRemoved component type
    var removeComponent = new example.ToBeRemoved {};

    // Create an entity and add inital components
    Ecsact.Defaults.Runner.executionOptions.CreateEntity()
        .AddComponent(exampleComponent)
        .AddComponent(removeComponent);
  }

  void OnDestroy() {
    foreach (var cleanUpFn in cleanUpFns) {
      cleanUpFn();
    }
  }
}
