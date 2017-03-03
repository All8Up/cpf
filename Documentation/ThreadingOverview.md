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
synchronizations being all that was needed.  As the core counts increased and
functional threading failed to scale up, various approaches were used to attempt
to spread the work load further.  One such approach was the task queue model
where units of work were pushed off the functional threads to a worker pool.
This model has evovled into the work stealing task systems found today.  While
it is a good model it could still be better since it is usually added onto a
functionally threaded foundation which will still end up with one or two cores
maximized and no further scale is gained from additional cores.

The current mid to high level implementation is based on data parallel execution.
At the highest level this means that the setup and work is performed similar
to how you work with D3D12 and other graphics API's.
