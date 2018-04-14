//////////////////////////////////////////////////////////////////////////
#pragma once
namespace VTune
{
#if CPF_VTUNE
#	include <ittnotify.h>


	//////////////////////////////////////////////////////////////////////////
	// VTune is enabled.

	// Enable or disable the analysis.
	inline void Enable() { __itt_resume(); }
	inline void Disable() { __itt_pause(); }

	// Domain tags for logging.
	using Domain = __itt_domain;
	inline void Enable(Domain* domain) { domain->flags = 1; }
	inline void Disable(Domain* domain) { domain->flags = 0; }
	inline Domain* DomainCreate(const char* name) { return __itt_domain_createA(name); }

	// Create a string name.
	using StringHandle = __itt_string_handle;
	inline StringHandle* StringHandleCreate(const char* name) { return __itt_string_handle_create(name); }

	// Name threads.
	inline void IgnoreThisThread() { __itt_thread_ignore(); }
	inline void SetThreadName(const char* name) { __itt_thread_set_nameA(name); }

	// Frame API.
	using Id = __itt_id;
	inline Id MakeID(void* addr, uint64_t extra) { return __itt_id_make(addr, extra); }
	inline void IdCreate(Domain* domain, Id id) { __itt_id_create(domain, id); }
	inline void IdDestroy(Domain* domain, Id id) { __itt_id_destroy(domain, id); }
	inline void BeginFrame(Domain* domain, Id* id = nullptr) { __itt_frame_begin_v3(domain, id); }
	inline void EndFrame(Domain* domain, Id* id = nullptr) { __itt_frame_end_v3(domain, id); }

	// Task API.
	inline void TaskBegin(Domain* domain, StringHandle* name) { __itt_task_begin(domain, __itt_null, __itt_null, name); }
	inline void TaskEnd(Domain* domain) { __itt_task_end(domain); }

	// Event API.
	using Event = __itt_event;
	inline Event EventCreate(const char* name, int namelen) { return __itt_event_create(name, namelen); }
	inline void EventStart(Event event) { __itt_event_start(event); }
	inline void EventEnd(Event event) { __itt_event_end(event); }

	// Synchronization API.
	enum SyncType : int {eBarrier = __itt_attr_barrier, eMutex = __itt_attr_mutex};
	inline void SyncCreate(void* addr, const char* type, const char* name, int attr) { __itt_sync_create(addr, type, name, attr); }
	inline void SyncRename(void* addr, const char* name) { __itt_sync_rename(addr, name); }
	inline void SyncDestroy(void* addr) { __itt_sync_destroy(addr); }
	inline void SyncPrepare(void* addr) { __itt_sync_prepare(addr); }
	inline void SyncCancel(void* addr) { __itt_sync_cancel(addr); }
	inline void SyncAcquired(void* addr) { __itt_sync_acquired(addr); }
	inline void SyncReleasing(void* addr) { __itt_sync_releasing(addr); }


	//////////////////////////////////////////////////////////////////////////
#	define VTUNE_DOMAIN(varName, name) static VTune::Domain* varName = VTune::DomainCreate(name)
#	define VTUNE_GET_DOMAIN(name) VTune::DomainCreate(name)

#	define VTUNE_SYNC_CREATE(name, addr, attr) VTune::SyncCreate(addr, nullptr, #name, attr)
#	define VTUNE_SYNC_DESTROY(addr) VTune::SyncDestroy(addr)
#	define VTUNE_SYNC_PREPARE(addr) VTune::SyncPrepare(addr)
#	define VTUNE_SYNC_CANCEL(addr) VTune::SyncCancel(addr)
#	define VTUNE_SYNC_ACQUIRED(addr) VTune::SyncAcquired(addr)
#	define VTUNE_SYNC_RELEASING(addr) VTune::SyncReleasing(addr)

#	define VTUNE_EVENT_CREATE(name) VTune::Event name = VTune::EventCreate(#name, int(::strlen(#name)))
#	define VTUNE_EVENT_START(ev) VTune::EventStart(ev)
#	define VTUNE_EVENT_END(ev) VTune::EventEnd(ev)

#	define VTUNE_BEGIN_FRAME(domain) VTune::BeginFrame(domain)
#	define VTUNE_END_FRAME(domain) VTune::EndFrame(domain)

#	define VTUNE_THREAD_NAME(name) VTune::SetThreadName(name);

#else
	// VTune is disabled.
	inline void Enable() {}
	inline void Disable() {}

	using Domain = void;
	inline Domain* DomainCreate(const char*) { return nullptr; }

	using StringHandle = void;
	inline StringHandle* StringHandleCreate(const char*) { return nullptr; }

	inline void IgnoreThisThread() {}
	inline void SetThreadName(const char*) {}

	using Id = int;
	inline Id Make(void*, uint64_t) { return 0; }
	inline void IdCreate(Domain*, Id) {}
	inline void IdDestroy(Domain*, Id) {}
	inline void BeginFrame(Domain*, Id* = nullptr) {}
	inline void EndFrame(Domain*, Id* = nullptr) {}

	// Task API.
	inline void TaskBegin(Domain*, StringHandle*) {}
	inline void TaskEnd(Domain*) {}

	// Event API.
	using Event = int;
	inline Event EventCreate(const char*, int) { return 0; }
	inline void EventStart(Event) {}
	inline void EventEnd(Event) {}

	// Synchronization API.
	enum SyncType : int { eBarrier = 0, eMutex = 1 };
	inline void SyncCreate(void*, const char*, const char*, int) {}
	inline void SyncRename(void*, const char*) {}
	inline void SyncDestroy(void*) {}
	inline void SyncPrepare(void*) {}
	inline void SyncCancel(void*) {}
	inline void SyncAcquired(void*) {}
	inline void SyncReleasing(void*) {}


	//////////////////////////////////////////////////////////////////////////
#	define VTUNE_DOMAIN(varName, name)
#	define VTUNE_GET_DOMAIN(name)

#	define VTUNE_SYNC_CREATE(name, addr, attr)
#	define VTUNE_SYNC_DESTROY(addr)
#	define VTUNE_SYNC_PREPARE(addr)
#	define VTUNE_SYNC_CANCEL(addr)
#	define VTUNE_SYNC_ACQUIRED(addr)
#	define VTUNE_SYNC_RELEASING(addr)

#	define VTUNE_EVENT_CREATE(name)
#	define VTUNE_EVENT_START(ev)
#	define VTUNE_EVENT_END(ev)

#	define VTUNE_BEGIN_FRAME(domain)
#	define VTUNE_END_FRAME(domain)

#	define VTUNE_THREAD_NAME(name)

#endif
}
