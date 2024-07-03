using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BasicExampleSystem : MonoBehaviour {
  // The system implement of our AddToExample system
  [Ecsact.DefaultSystemImpl(typeof(example.AddToExample))]
  public static void
  AddToExampleSystem(EcsactRuntime.SystemExecutionContext context) {
    // Get a component from the context
    var value = context.Get<example.Example>();

    // Modify and update its value
    value.example_value += 1;
    context.Update<example.Example>(value);

    if (value.example_value >= 100) {
      // Remove the component from the context
      context.Remove<example.ToBeRemoved>();
    }
  }
}
