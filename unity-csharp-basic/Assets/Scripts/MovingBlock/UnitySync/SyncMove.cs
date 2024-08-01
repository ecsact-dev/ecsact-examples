using UnityEngine;

public class SyncMove //
	: MonoBehaviour,
		Ecsact.UnitySync.IRequired<example.Position>,
		Ecsact.UnitySync.IRequired<example.Block>,
		Ecsact.UnitySync.IOnInitComponent<example.Position>,
		Ecsact.UnitySync.IOnUpdateComponent<example.Position> {
	public void OnInitComponent(in example.Position position) {
		gameObject.transform.position = new Vector3(position.x, position.y, 0);
	}

	public void OnUpdateComponent(in example.Position position) {
		gameObject.transform.position = new Vector3(position.x, position.y, 0);
	}
}
