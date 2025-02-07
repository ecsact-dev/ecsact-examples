// GENERATED FILE - DO NOT EDIT

#nullable enable

namespace example {

public struct Example : global::Ecsact.Component {
	public static readonly global::System.Int32 id = 1;
	public global::System.Int32 example_value;

	public override bool Equals(object? obj) {
		if(obj == null) return false;
		var other_ = (example.Example)obj;
		return true
			&& other_.example_value.Equals(this.example_value);
	}

	public override int GetHashCode() {
		int hashCode_ = 17;
		hashCode_ = hashCode_ * 23 + example_value.GetHashCode();
		return hashCode_;
	}
}

public struct ToBeRemoved : global::Ecsact.Component {
	public static readonly global::System.Int32 id = 2;

	public override bool Equals(object? obj) {
		if(obj == null) return false;
		var other_ = (example.ToBeRemoved)obj;
		return true;
	}

	public override int GetHashCode() {
		int hashCode_ = 17;
		return hashCode_;
	}
}

public struct CanMove : global::Ecsact.Component {
	public static readonly global::System.Int32 id = 4;

	public override bool Equals(object? obj) {
		if(obj == null) return false;
		var other_ = (example.CanMove)obj;
		return true;
	}

	public override int GetHashCode() {
		int hashCode_ = 17;
		return hashCode_;
	}
}

public struct Velocity : global::Ecsact.Component {
	public static readonly global::System.Int32 id = 5;
	public global::System.Single x_value;
	public global::System.Single y_value;
	public global::System.Single speed;

	public override bool Equals(object? obj) {
		if(obj == null) return false;
		var other_ = (example.Velocity)obj;
		return true
			&& other_.x_value.Equals(this.x_value)
			&& other_.y_value.Equals(this.y_value)
			&& other_.speed.Equals(this.speed);
	}

	public override int GetHashCode() {
		int hashCode_ = 17;
		hashCode_ = hashCode_ * 23 + x_value.GetHashCode();
		hashCode_ = hashCode_ * 23 + y_value.GetHashCode();
		hashCode_ = hashCode_ * 23 + speed.GetHashCode();
		return hashCode_;
	}
}

public struct Position : global::Ecsact.Component {
	public static readonly global::System.Int32 id = 6;
	public global::System.Single x;
	public global::System.Single y;
	public global::System.Single prev_x;
	public global::System.Single prev_y;

	public override bool Equals(object? obj) {
		if(obj == null) return false;
		var other_ = (example.Position)obj;
		return true
			&& other_.x.Equals(this.x)
			&& other_.y.Equals(this.y)
			&& other_.prev_x.Equals(this.prev_x)
			&& other_.prev_y.Equals(this.prev_y);
	}

	public override int GetHashCode() {
		int hashCode_ = 17;
		hashCode_ = hashCode_ * 23 + x.GetHashCode();
		hashCode_ = hashCode_ * 23 + y.GetHashCode();
		hashCode_ = hashCode_ * 23 + prev_x.GetHashCode();
		hashCode_ = hashCode_ * 23 + prev_y.GetHashCode();
		return hashCode_;
	}
}

public struct Collider : global::Ecsact.Component {
	public static readonly global::System.Int32 id = 7;
	public global::System.Int32 x_radius;
	public global::System.Int32 y_radius;

	public override bool Equals(object? obj) {
		if(obj == null) return false;
		var other_ = (example.Collider)obj;
		return true
			&& other_.x_radius.Equals(this.x_radius)
			&& other_.y_radius.Equals(this.y_radius);
	}

	public override int GetHashCode() {
		int hashCode_ = 17;
		hashCode_ = hashCode_ * 23 + x_radius.GetHashCode();
		hashCode_ = hashCode_ * 23 + y_radius.GetHashCode();
		return hashCode_;
	}
}

public struct Block : global::Ecsact.Component {
	public static readonly global::System.Int32 id = 8;

	public override bool Equals(object? obj) {
		if(obj == null) return false;
		var other_ = (example.Block)obj;
		return true;
	}

	public override int GetHashCode() {
		int hashCode_ = 17;
		return hashCode_;
	}
}

public struct BlockGenerator : global::Ecsact.Component {
	public static readonly global::System.Int32 id = 9;

	public override bool Equals(object? obj) {
		if(obj == null) return false;
		var other_ = (example.BlockGenerator)obj;
		return true;
	}

	public override int GetHashCode() {
		int hashCode_ = 17;
		return hashCode_;
	}
}

public struct QueueBlock : global::Ecsact.Component {
	public static readonly global::System.Int32 id = 14;
	public global::System.Int32 pos_x;
	public global::System.Int32 pos_y;

	public override bool Equals(object? obj) {
		if(obj == null) return false;
		var other_ = (example.QueueBlock)obj;
		return true
			&& other_.pos_x.Equals(this.pos_x)
			&& other_.pos_y.Equals(this.pos_y);
	}

	public override int GetHashCode() {
		int hashCode_ = 17;
		hashCode_ = hashCode_ * 23 + pos_x.GetHashCode();
		hashCode_ = hashCode_ * 23 + pos_y.GetHashCode();
		return hashCode_;
	}
}

public struct Move : global::Ecsact.Action {
	public static readonly global::System.Int32 id = 10;
	public global::System.Single dir_x;
	public global::System.Single dir_y;

	public override bool Equals(object? obj) {
		if(obj == null) return false;
		var other_ = (example.Move)obj;
		return true
			&& other_.dir_x.Equals(this.dir_x)
			&& other_.dir_y.Equals(this.dir_y);
	}

	public override int GetHashCode() {
		int hashCode_ = 17;
		hashCode_ = hashCode_ * 23 + dir_x.GetHashCode();
		hashCode_ = hashCode_ * 23 + dir_y.GetHashCode();
		return hashCode_;
	}
}

public struct PerformGenerateBlock : global::Ecsact.Action {
	public static readonly global::System.Int32 id = 15;
	public global::System.Int32 pos_x;
	public global::System.Int32 pos_y;

	public override bool Equals(object? obj) {
		if(obj == null) return false;
		var other_ = (example.PerformGenerateBlock)obj;
		return true
			&& other_.pos_x.Equals(this.pos_x)
			&& other_.pos_y.Equals(this.pos_y);
	}

	public override int GetHashCode() {
		int hashCode_ = 17;
		hashCode_ = hashCode_ * 23 + pos_x.GetHashCode();
		hashCode_ = hashCode_ * 23 + pos_y.GetHashCode();
		return hashCode_;
	}
}
public struct AddToExample : global::Ecsact.System {
	public static readonly global::System.Int32 id = 3;
}
public struct CollisionComparer : global::Ecsact.System {
	public static readonly global::System.Int32 id = 11;
	public struct CheckCollision : global::Ecsact.System {
		public static readonly global::System.Int32 id = 12;
	}
}
public struct ApplyVelocity : global::Ecsact.System {
	public static readonly global::System.Int32 id = 13;
}
public struct GenerateBlock : global::Ecsact.System {
	public static readonly global::System.Int32 id = 16;
}
public struct RemoveQueueBlock : global::Ecsact.System {
	public static readonly global::System.Int32 id = 18;
}

}
