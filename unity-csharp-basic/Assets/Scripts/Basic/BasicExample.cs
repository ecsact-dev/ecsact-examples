using System.Collections.Generic;
using TMPro;
using UnityEngine;

public class BasicExample : MonoBehaviour
{

  List<System.Action> cleanUpFns = new();

  public TMP_Text textCounter;

  int entityId;

  void Start()
  {

    // Callbacks from the Ecsact Runtime used to change state in Unity
    cleanUpFns.AddRange(new[] {
      Ecsact.Defaults.Runtime.OnInitComponent<example.Example>(
          (entity, component) => {
            textCounter.text = component.example_value.ToString();
          }),
      Ecsact.Defaults.Runtime.OnUpdateComponent<example.Example>(
          (entity, component) => {
            textCounter.text = component.example_value.ToString();
           }),

      Ecsact.Defaults.Runtime.OnRemoveComponent<example.ToBeRemoved>(
          (entity, component) => { Debug.Log("Component removed"); }),
      Ecsact.Defaults.Runtime.OnEntityCreated(
          (entityId, placeholderId) => { Debug.Log("Entity created"); })
    });

    // Declare an Example component type
    var exampleComponent = new example.Example
    {
      example_value = 0,
    };

    // Declare a ToBeRemoved component type
    var removeComponent = new example.ToBeRemoved { };

    // Create an entity and add inital components
    Ecsact.Defaults.Runner.executionOptions.CreateEntity()
        .AddComponent(exampleComponent)
        .AddComponent(removeComponent);
  }

  void OnDestroy()
  {
    foreach (var cleanUpFn in cleanUpFns)
    {
      cleanUpFn();
    }
  }
}
