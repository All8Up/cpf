*** Currently in heavy flux.

Const, non-const and mutability.

In the threaded environment these options take on a slightly different meaning.  The best
overview is probably from Herb Sutter and you can read about it here:
https://herbsutter.com/2013/05/24/gotw-6a-const-correctness-part-1-3/

This still leaves a problem for the data parallel threading model and how to express
constraints in C++.  Using a simple example, a flocking algorithm would be the following
at it's core:

{
	Vector3fv alignment = GetAlignment(range);
	Vector3fv cohesion = GetCohesion(range);
	Vector3fv separation = GetSeparation(range);

	SetVelocity(Normalize(GetVelocity() + alignment + cohesion + separation));
}

The problem is that setting the velocity here breaks the rules but there is not a decent
way to express this to the user.  The problem being that it is viable for an entity to
read and modify velocity in a single stage but if it also reads velocities from others of
the same (or derived, if we want to get really complicated) type then it becomes illegal
to make modifications since others of the same type will be reading this data thinking it
is const during the stage.

Enforcement of the rules is the key item which is trying to be solved.  What is desired is an
interface which expresses the read/write/both rules.  So, an IDL which could be used to
express this would be:

interface iEntity
{
	[self=read] Vector3fv GetPosition()
	[self=read] Vector3fv GetVelocity()

	[self=read, sibling=read] Vector3fv GetAlignment(float range)
	[self=read, sibling=read] Vector3fv GetCohesion(float range)
	[self=read, sibling=read] Vector3fv GetSeparation(float range)

	[self=write] void SetPosition(Vector3fv pos)
	[self=write] void SetVelocity(Vector3fv velocity)
};

While this is not perfect, it would allow for validation in stage blocks.  Basically
the compiler could see that there are reads from other instances (and with propogation)
which specific members are begin read and detect that writes to those members, velocity
in this case, are illegal within this particular block.  The user should either cache
the result and apply it in a later block or should be using shadowing.

Some of the possibilities being considered are:

* Use a template accessor which applies const within stage blocks appropriately.
* Write a translator which uses the above IDL, validates it and passes the transformed
C++ back to be compiled.

With any of these, the user can always bypass them at their own risk.
