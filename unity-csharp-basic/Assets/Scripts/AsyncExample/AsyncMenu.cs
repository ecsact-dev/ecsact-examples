using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using TMPro;

public class AsyncMenu : MonoBehaviour {

  public Button connectBtn;
  public TMP_Dropdown dropdown;
  public TMP_InputField connectionString;

  private List<string> options = new();

  void OnEnable() {
    options.Add("BasicExample");
    options.Add("MovingBlock");

    dropdown.AddOptions(options);

    // This connection string will start a connection with 20ms delta time
    // At 20ms, systems will execute 50 times/sec (1000ms / 20ms)
    connectionString.text = "good?delta_time=20";

    connectBtn.onClick.AddListener(onButtonClick);

    // Callback invoked when the Defaults class is initialized
    Ecsact.Defaults.WhenReady(() => {
      Ecsact.Defaults.Runtime.async.OnAsyncError(
          (err, requestIds) => { Debug.Log("Error: " + err); });
    });

    Object.DontDestroyOnLoad(this.gameObject);
  }

  void onButtonClick() {
    var sceneName = options[dropdown.value];
    Debug.Log("Loading scene " + sceneName);
    SceneManager.LoadScene(sceneName);

    Debug.Log("connecting with: " + connectionString.text);

    Ecsact.Defaults.Runtime.async.Connect(connectionString.text);

    this.gameObject.SetActive(false);
  }
}
