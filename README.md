* Develop: ![Build Status](https://ci.appveyor.com/api/projects/status/17oguo2o6a2builq/branch/develop?svg=true)
* Master : ![Build status](https://ci.appveyor.com/api/projects/status/17oguo2o6a2builq/branch/master?svg=true)

Very early multithreaded D3D12/Vulkan/Metal system.
Threading is fairly solid, but lots of work to be done.

Requirements:

CMake 2.8 +

Visual Studio 2015 +

Some external dependencies: See Readme.txt under External/Source

A binary external distributable will be auto built at a later time.

---
Threading integration outline.

A brief overview of how the threading solution integrates within the overall
framework.  For those that have done work with D3D12 and/or Vulkan, a lot of
similarities will be apparent.  The model which is used in those API's is
almost identical to that used in this library which is actually 10+ years
old, though highly refined since the initial version.  As such, a few tweaks
were made to align this library and the new API's as closely as possible.
For these reasons, parallels will be drawn from D3D12 to help explain the
way things work.

An important thing to understand is that there are two separate layers
in the programming model.  At the lowest level is the scheduler system which
is intended to simply provide a framework to support most needed threading
patterns.  It manages control of the threads themselves and organizes how they
interact but otherwise does not provide much in terms of executing actual code.
For this reason, the scheduler is sometimes refered to as a pattern engine and
not a multicore distribution system.

On top of the scheduler the user can layer domain specific threading models.
While this document covers a game specific data dependency model instead of
the more normally used work stealing task queue model, it is actually possible
for both to coexist on top of the scheduler.  There are two manners in which
coexistence can happen.  First, the task queue model can be implemented between
two barriers during a frame such that it does not overlap with the higher
performance, but more user work intensive, data dependency model.  The
alternate, used in other areas, is to run up two separate schedulers with the
different models on top of each.  The underlying scheduler allows the engine to
balance thread utilization between the two implementations dynamically such
that oversubscription to the CPU's can be minimized.

Game threading and the possible methods of doing so is an ever evolving area
of active research.  Several years ago, functional threading was the primary
focus as there were only a couple of cores and as such the primary areas of
game engines were simply split into individual threads with occasional frame
synchronizations beign all that was needed.  As the core counts increased and
functional threading failed to scale up, various approaches were used to attempt
to spread the work load further.  One such approach was the task queue model
where units of work were pushed off the functional threads to a worker pool.
This model has evovled into the work stealing task systems found today.  While
it is a good model it could still be better since it is usually added onto a
functionally threaded foundation which will still end up with one or two cores
maximized and no further scale is gained from additional cores.

Instead of starting with functional threading, the Cpf libraries start with
parallel processing right in the main loop and build up from there.  This means
that there are no centralized bottlenecks on the performance of the engine other
than how well the remaining work can be parallelized.  The model in use is
typically referred to as data parallel execution model where the user is expected
to model data dependencies and describe them to the underlying system so it can
organize the work in a highly parallel manner.  The benefits over a task queue
is better parallel performance since with good data modelling there are no locks
required in most code, synchronization is handled at a higher level where one
lock can often replace literally thousands of locks.

A very simple example of the differences between task and data parallel models
is presented as one thousand points bouncing around in a volume.  While very
simplistic, it will point out the highest level differences between the models.
The example starts with the single threaded approach:

static const int kObjectCount = 1000;
static Vector3fv mObjects[kObjectCount];

int main(int, char**)
{
	bool running = true;
	while (running)
	{
		for (int i=0; i<kObjectCount; ++i)
			UpdateObject(mObjects[i]);
		for (int i=0; i<kObjectCount; ++i)
			DrawObject(mObjects[i]);
	}
}
