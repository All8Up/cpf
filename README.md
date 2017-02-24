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

The threading solution consists of a low level scheduler and a mid/high level
abstraction.  For the purposes here, the low level scheduler will be ignored
for the most part, direct access is intended to be avoided as it is not often
needed.  Sticking to the mid to high level will be the primary focus as it
makes threaded code a viable starting point without having to worry about
the details of locking, synchronization or other lower level and often difficult
details.

Starting with the D3D12 parallels, the primary item of interest to the user is
running shaders on the GPU.  In order to do this, D3D12 exposes control of 3
layers: Pipeline stages, Pipeline State and Bound Resources.  In order to be
as familiar as possible, the Cpf model loosely follows this breakdown.  It is
not as strict due to the fact that the CPU has better random data access
abilities than a GPU which is what makes utilizing CPU's for more abstract work
such as AI, scene graph traversals and other items the preferred target.  It is
important to note that this is *not* intended to follow the lines of OpenCL or
other languages which attempt to use a single model for either CPU or GPU
targets, it is tailored to general purpose CPU's.

In the Cpf model, the layers which loosely corresponds to the D3D12 concepts are:
Stage and Systems.  Resources are not called out specifically since they can be
pretty much anything, but usually will be references to other systems.  So, for
instance, a scene graph system would be responsible for applying culling and
outputting a list of entities which need to be rendered.  For this purpose the
scene graph system contains a pointer to the render system and stages can get
that pointer so it can write the output of the scene traversal.  Or, in the D3D12
terminology, a scene graph stage has a reference to it's owning system (pipeline
state in D3D12) which allows the stage access to the resource which is the
rendering system.  Also, much like D3D12 state transitions, stages have the
ability to define if their access is read only or write access.

The data dependencies are the key part of the threading model.  Instead of
worrying about locking and synchronization, the programmer generally just
sets up various data dependencies and lets the stages sort themselves out
in a manner which prevents simultaneous read/write to resources.  This model
has two primary gains: simplicity and performance.  In typical threaded
solutions individual locks are taken when writing, in a game this can happen
thousands of times per frame and the overhead adds up quickly.  Within this
model the stages individually know if they can read or write and as such
there is usually no locking required.  At most a synchronization point will
be introduced between two stages in order to guarantee that all writes from
one stage have completed before reads in another stage begin.  Hundreds or
thousands of locks thus become one and the overhead is very low.

Multiple levels of dependency description are possible and required within
the threading model.  This is probably the most complicated portion of using
the libraries but it is also the most important.  Dependencies can be described
as system to system and/or stage to stage.  Under the hood, system to system
dependencies are simply stage to stage dependencies but it is often easier to
say that rendering takes place after entity update instead of digging out the
specific stages involved.  Only stage to stage dependencies will be described
in detail as system to system is just syntactic sugar to simplify things.

Using three systems as example, the stage dependencies will be described.  The
three systems are: TimerSystem, EntitySystem and RenderSystem.  The systems
each break down to one or more stages as follows:

* TimerSystem:
  * Update - Simply update the time.
* EntitySystem:
  * Deletion - Deletes any destroyed entities.
  * Addition - Adds new entities.
  * Messages - Any inter-entity messaging is processed.
  * Update - Run a generic update over the entities.  (NOTE: Not accurate in the real code, only for example.)
* RenderSystem:
  * BeginRenderPass
  * Draw
  * EndRenderPass

During system setup, default dependencies are injected.  For instance, the
EntitySystem will insert a chain of dependencies to ensure that the four
stages run in sequence without overlap.  By itself the EntitySystem would
generate the following scheduler instructions:

Run Deletion
Barrier
Run Addition
Barrier
Run Messages
Barrier
Run Update

All that is added in the above are the three Barrier instructions which
guarantee that the individual stages run in sequence instead of concurrently.
The RenderSystem also sets up dependencies in the same manner to run the
three stages it supplies in sequential order.  This takes a lot of the
work out of the hands of the programmer but leaves an important detail
unaccounted for.  The threading pipeline will optimize stages in order
to reduce the number of barriers and allow as much to run concurrently
as possible.  Since it knows nothing about the three systems involved
it will generate the following operation order:

Run TimerSystem:Update
Run EntitySystem:Deletion
Run RenderSystem:BeginRenderPass
Barrier
Run EntitySystem:Addition
Run RenderSystem:Draw
Barrier
Run EntitySystem:Message
Run RenderSystem:EndRenderPass
Barrier
Run EntitySystem:Update

That's a little bit out of order and not what we actually want.  So,
introducing additional dependencies is needed.  We only need a couple
dependencies to get everything in the correct order:

EntitySystem::Update depends on TimerSystem:Update
EntitySystem::Update depends on RenderSystem:BeginRenderPass
RenderSystem:Draw depends on EntitySystem:Update

Run TimerSystem:Update
Run EntitySystem:Deletion
Run RenderSystem:BeginRenderPass
Barrier
Run EntitySystem:Addition
Barrier
Run EntitySystem:Message
Barrier
Run EntitySystem:Update
Barrier
Run RenderSystem:Draw
Barrier
Run RenderSystem:EndRenderPass

With the dependencies, the order of operations is now correct and the
game will function as intended.  Obviously this is not as optimal as the
first case but with a real game consisting of potentially hundreds of
stages, the overhead of the barriers quickly goes away as more work
happens concurrently between the barriers.

This model greatly simplifies most users interaction with threading.
With enough supplied systems, it is hoped that entire games can be
written without ever having the user interact with the underlying
threading scheduler.  Advanced users and those with unique requirements
will still have the option to write new systems themselves and as such
they will need to dig into the underlying details of the threading
scheduler and all the difficulties that can present.  But, even in
such cases, the user is not actually required to thread the code,
they can simply issue the stage as a singled threaded task which,
while not optimal will still benefit from running concurrently with
other non-dependent systems.
