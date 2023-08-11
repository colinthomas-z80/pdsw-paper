/* -*- Mode: C; c-basic-offset:4 ; indent-tabs-mode:nil ; -*- */
/*
 * See COPYRIGHT in top-level directory.
 */

#ifndef ABT_H_INCLUDED
#define ABT_H_INCLUDED

/* user include file for ARGOBOTS programs */

#if defined(ABT_C_HAVE_VISIBILITY)
#define ABT_API_PUBLIC  __attribute__((visibility ("default")))
#else
#define ABT_API_PUBLIC
#endif

/* Keep C++ compilers from getting confused */
#if defined(__cplusplus)
extern "C" {
#endif

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <sys/time.h>

/**
 * @ingroup INFO
 * @brief   Version string of Argobots.
 *
 * \c ABT_VERSION is the version string of Argobots.  \c ABT_VERSION uses the
 * following format:
 *
 * \code{.unparsed}
 * ABT_VERSION = [MAJ].[MIN].[REV][EXT][EXT_NUMBER]
 * Example: ABT_VERSION = 1.0.7rc1 represents
 *          MAJ = 1
 *          MIN = 0
 *          REV = 7
 *          EXT = rc
 *          EXT_NUMBER = 1
 * \endcode
 *
 * Regular releases are treated as patch 0.
 */
#define ABT_VERSION "1.1"
/**
 * @ingroup INFO
 * @brief   Version number of Argobots.
 *
 * \c ABT_NUMVERSION is the numeric version of Argobots that can be used in
 * numeric comparisons.  \c ABT_NUMVERSION is calculated as follows.
 *
 * \code{.unparsed}
 * ABT_NUMVERSION = [MAJ] * 10000000 + [MIN] * 100000 + [REV] * 1000
 *                  + [EXT] * 100 + [EXT_NUMBER]
 * where [EXT] is converted to the following format number:
 *    ALPHA (a) = 0 (ABT_RELEASE_TYPE_ALPHA)
 *    BETA (b)  = 1 (ABT_RELEASE_TYPE_BETA)
 *    RC (rc)   = 2 (ABT_RELEASE_TYPE_RC)
 *    PATCH (p) = 3 (ABT_RELEASE_TYPE_PATCH)
 * \endcode
 *
 * \c ABT_NUMVERSION has 1 digit for MAJ, 2 digits for MIN, 2 digits for REV, 1
 * digit for EXT, and 2 digits for EXT_NUMBER.  For example, 1.0.7rc1 is
 * converted to the numeric version 10007201.
 */
#define ABT_NUMVERSION 10100300

#define ABT_RELEASE_TYPE_ALPHA  0
#define ABT_RELEASE_TYPE_BETA   1
#define ABT_RELEASE_TYPE_RC     2
#define ABT_RELEASE_TYPE_PATCH  3

#define ABT_CALC_VERSION(MAJOR, MINOR, REVISION, TYPE, PATCH) \
    (((MAJOR) * 10000000) + ((MINOR) * 100000) + ((REVISION) * 1000) + ((TYPE) * 100) + (PATCH))

#define ABT_DEPRECATED __attribute__((deprecated))

#define ABT_ENABLE_VER_20_API_VAL 0
#undef ABT_ENABLE_VER_20_API
#if ABT_ENABLE_VER_20_API_VAL
#define ABT_ENABLE_VER_20_API 1
#endif

/**
 * @ingroup ERROR_CODE
 * @brief   Error code: the routine returns successfully.
 *
 * \c ABT_SUCCESS is guaranteed to be 0.
 */
#define ABT_SUCCESS                 0
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: Argobots it not initialized.
 */
#define ABT_ERR_UNINITIALIZED       1
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: Memory allocation failure.
 *
 * \c ABT_ERR_MEM is returned if memory allocation fails.
 */
#define ABT_ERR_MEM                 2
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: other error.
 */
#define ABT_ERR_OTHER               3
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid execution stream.
 */
#define ABT_ERR_INV_XSTREAM         4
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid execution stream rank.
 */
#define ABT_ERR_INV_XSTREAM_RANK    5
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid execution stream barrier.
 */
#define ABT_ERR_INV_XSTREAM_BARRIER 6
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid scheduler.
 */
#define ABT_ERR_INV_SCHED           7
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid scheduler kind.
 */
#define ABT_ERR_INV_SCHED_KIND      8
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid predefined scheduler type.
 */
#define ABT_ERR_INV_SCHED_PREDEF    9
/**
 * @ingroup ERROR_CODE
 * @brief   Unused error code
 *
 * This error code is not used.  This error code is deprecated.
 */
#define ABT_ERR_INV_SCHED_TYPE     10
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid scheduler configuration.
 */
#define ABT_ERR_INV_SCHED_CONFIG   11
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid pool.
 */
#define ABT_ERR_INV_POOL           12
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid pool kind.
 */
#define ABT_ERR_INV_POOL_KIND      13
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid pool access type.
 */
#define ABT_ERR_INV_POOL_ACCESS    14
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid work unit for scheduling.
 */
#define ABT_ERR_INV_UNIT           15
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid work unit.
 */
#define ABT_ERR_INV_THREAD         16
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid ULT attribute.
 */
#define ABT_ERR_INV_THREAD_ATTR    17
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid work unit.
 *
 * @changev20
 * \DOC_V20 This error code is an alias of \c ABT_ERR_INV_THREAD.
 * @endchangev20
 */
#define ABT_ERR_INV_TASK           18
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid work-unit-specific data key.
 */
#define ABT_ERR_INV_KEY            19
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid mutex.
 */
#define ABT_ERR_INV_MUTEX          20
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid mutex attribute.
 */
#define ABT_ERR_INV_MUTEX_ATTR     21
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid condition variable.
 */
#define ABT_ERR_INV_COND           22
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid readers-writer lock.
 */
#define ABT_ERR_INV_RWLOCK         23
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid eventual.
 */
#define ABT_ERR_INV_EVENTUAL       24
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid future.
 */
#define ABT_ERR_INV_FUTURE         25
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid barrier.
 */
#define ABT_ERR_INV_BARRIER        26
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid timer.
 */
#define ABT_ERR_INV_TIMER          27
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid query kind.
 */
#define ABT_ERR_INV_QUERY_KIND     28
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid tool context.
 */
#define ABT_ERR_INV_TOOL_CONTEXT   52
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: invalid user argument.
 */
#define ABT_ERR_INV_ARG            53
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to an execution stream.
 */
#define ABT_ERR_XSTREAM            29
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to an execution stream state.
 *
 * This error code is deprecated.
 */
#define ABT_ERR_XSTREAM_STATE      30
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to an execution stream.
 */
#define ABT_ERR_XSTREAM_BARRIER    31
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a scheduler.
 */
#define ABT_ERR_SCHED              32
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a scheduler configuration.
 */
#define ABT_ERR_SCHED_CONFIG       33
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a pool.
 */
#define ABT_ERR_POOL               34
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a work unit for scheduling.
 */
#define ABT_ERR_UNIT               35
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a work unit.
 */
#define ABT_ERR_THREAD             36
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a work unit.
 *
 * @changev20
 * \DOC_V20 This error code is an alias of \c ABT_ERR_THREAD.
 * @endchangev20
 */
#define ABT_ERR_TASK               37
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a work-unit-specific data key.
 */
#define ABT_ERR_KEY                38
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a mutex.
 */
#define ABT_ERR_MUTEX              39
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: a return value when a mutex is locked.
 *
 * This error code is used by \c ABT_mutex_trylock().
 */
#define ABT_ERR_MUTEX_LOCKED       40
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a condition variable.
 */
#define ABT_ERR_COND               41
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: a return value when a condition variable is timed out.
 *
 * This error code is used by \c ABT_cond_timedwait().
 */
#define ABT_ERR_COND_TIMEDOUT      42
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a readers-writer lock.
 */
#define ABT_ERR_RWLOCK             43
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to an eventual.
 */
#define ABT_ERR_EVENTUAL           44
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a future.
 */
#define ABT_ERR_FUTURE             45
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a barrier.
 */
#define ABT_ERR_BARRIER            46
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a timer.
 */
#define ABT_ERR_TIMER              47
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to a migration target.
 */
#define ABT_ERR_MIGRATION_TARGET   48
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: migration is not supported.
 *
 * @changev20
 * \DOC_V20 This error code is an alias of \c ABT_ERR_FEATURE_NA.
 * @endchangev20
 */
#define ABT_ERR_MIGRATION_NA       49
/**
 * @ingroup ERROR_CODE
 * @brief   Unused error code
 *
 * This error code is not used.  This error code is deprecated.
 */
#define ABT_ERR_MISSING_JOIN       50
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: unsupported feature.
 */
#define ABT_ERR_FEATURE_NA         51
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to system calls and standard libraries.
 *
 * \c ABT_ERR_SYS represents a general error that happens in libraries used by
 * Argobots.  For example, this error is returned when system calls such as
 * \c futex() and \c open() or functions provided by external libraries such as
 * \c pthread_create() and \c unw_init_local() fail.  Note that \c ABT_ERR_MEM
 * is returned if a memory allocation function such as \c malloc() or \c mmap()
 * fails.
 */
#define ABT_ERR_SYS                54
/**
 * @ingroup ERROR_CODE
 * @brief   Error code: error related to CPU ID.
 */
#define ABT_ERR_CPUID              55

/**
 * @ingroup ES
 * @brief   State of an execution stream.
 */
enum ABT_xstream_state {
    /** The execution stream is running. */
    ABT_XSTREAM_STATE_RUNNING,
    /** The execution stream is terminated. */
    ABT_XSTREAM_STATE_TERMINATED
};

/**
 * @ingroup ULT
 * @brief   State of a work unit.
 */
enum ABT_thread_state {
    /** The work unit is ready to run. */
    ABT_THREAD_STATE_READY,
    /** The work unit is running. */
    ABT_THREAD_STATE_RUNNING,
    /** The work unit is blocked. */
    ABT_THREAD_STATE_BLOCKED,
    /** The work unit is terminated. */
    ABT_THREAD_STATE_TERMINATED
};

/**
 * @ingroup TASK
 * @brief   State of a tasklet
 *
 * @changev20
 * \DOC_V20 \c ABT_task_state is replaced by \c ABT_thread_state.
 * @endchangev20
 */
enum ABT_task_state {
    /** Corresponding to \c ABT_THREAD_STATE_READY. */
    ABT_TASK_STATE_READY,
    /** Corresponding to \c ABT_THREAD_STATE_RUNNING. */
    ABT_TASK_STATE_RUNNING,
    /** Corresponding to \c ABT_THREAD_STATE_TERMINATED. */
    ABT_TASK_STATE_TERMINATED
};

/**
 * @brief Unused enum.
 *
 * @changev20
 * \DOC_V20 This enum is removed since no Argobots routine uses this.
 * @endchangev20
 */
enum ABT_sched_state {
    ABT_SCHED_STATE_READY,
    ABT_SCHED_STATE_RUNNING,
    ABT_SCHED_STATE_STOPPED,
    ABT_SCHED_STATE_TERMINATED
};

/**
 * @ingroup SCHED
 * @brief   Predefined scheduler type.
 *
 * Relying on a specific scheduling order is not recommended since the
 * implementation of predefined schedulers can be changed.  Users can create
 * their own scheduler by using \c ABT_sched_create().
 */
enum ABT_sched_predef {
    /** Default scheduler.  \c ABT_SCHED_BASIC is used. */
    ABT_SCHED_DEFAULT,
    /** Basic scheduler. */
    ABT_SCHED_BASIC,
    /**
     * Priority scheduler.  This scheduler type is not recommended because this
     * scheduler does not work as the user expects. */
    ABT_SCHED_PRIO,
    /**
     * Random work-stealing scheduler.  This scheduler type is not recommended
     * because this scheduler does not work as the user expects. */
    ABT_SCHED_RANDWS,
    /** Basic scheduler with the ability to wait for work units. */
    ABT_SCHED_BASIC_WAIT,
};

/**
 * @ingroup SCHED
 * @brief   Scheduler's work unit type.
 *
 * @changev11
 * \DOC_DESC_V10_ALWAYS_SCHED_TYPE_ULT
 * @endchangev11
 */
enum ABT_sched_type {
    /** A ULT is used for the scheduler's underlying work unit. */
    ABT_SCHED_TYPE_ULT,
    /** Ignored.  A ULT is used for the scheduler's underlying work unit. */
    ABT_SCHED_TYPE_TASK
};

/**
 * @ingroup POOL
 * @brief   Predefined pool type.
 *
 * Predefined pools provide all the pool functions that are defined in
 * \c ABT_pool_def unless otherwise noted.
 */
enum ABT_pool_kind {
    /** FIFO pool. */
    ABT_POOL_FIFO,
    /**
     * FIFO pool with a waiting ability.  If a caller's pop operation fails,
     * either an execution stream running the caller or a calling external
     * thread will suspend for a while.  This can reduce CPU utilization when
     * a pool is empty, but it increases an overhead of each pool operation.
     *
     * If the user does not know how \c ABT_POOL_FIFO_WAIT works,
     * \c ABT_POOL_FIFO is recommended. */
    ABT_POOL_FIFO_WAIT
};

/**
 * @ingroup POOL
 * @brief   Pool access type.
 */
enum ABT_pool_access {
    /**
     * The created pool may be pushed and popped by only one execution stream
     * in the lifetime of the pool. */
    ABT_POOL_ACCESS_PRIV,
    /**
     * The created pool may be pushed by only one execution stream and popped
     * by only one execution stream in the lifetime of the pool.  The two
     * execution streams can be different. */
    ABT_POOL_ACCESS_SPSC,
    /**
     * The created pool may be popped by only one execution stream in the
     * lifetime of the pool. */
    ABT_POOL_ACCESS_MPSC,
    /**
     * The created pool may be pushed by only one execution stream in the
     * lifetime of the pool. */
    ABT_POOL_ACCESS_SPMC,
    /** No restriction regarding a caller of pushing and popping operations. */
    ABT_POOL_ACCESS_MPMC
};

/**
 * @ingroup UNIT
 * @brief   Type of a work unit for scheduling.
 */
enum ABT_unit_type {
    /** A ULT. */
    ABT_UNIT_TYPE_THREAD,
    /**
     * A tasklet.
     *
     * \DOC_V20 This type is an alias of \c ABT_UNIT_TYPE_THREAD.
     */
    ABT_UNIT_TYPE_TASK,
    /** Deprecated since no Argobots function uses it. */
    ABT_UNIT_TYPE_XSTREAM,
    /** An external thread. */
    ABT_UNIT_TYPE_EXT
};

/**
 * @ingroup INFO
 * @brief   Query kind for \c ABT_info_query_config().
 */
enum ABT_info_query_kind {
    /** Whether the debug mode is enabled or not */
    ABT_INFO_QUERY_KIND_ENABLED_DEBUG,
    /** Whether Argobots prints an error number when an error happens or not */
    ABT_INFO_QUERY_KIND_ENABLED_PRINT_ERRNO,
    /** Whether Argobots prints a debug message or not */
    ABT_INFO_QUERY_KIND_ENABLED_LOG,
    /** Whether Argobots is configured to be Valgrind friendly or not */
    ABT_INFO_QUERY_KIND_ENABLED_VALGRIND,
    /** Whether an error is checked or not */
    ABT_INFO_QUERY_KIND_ENABLED_CHECK_ERROR,
    /** Whether a pool access violation regarding producer is checked or not */
    ABT_INFO_QUERY_KIND_ENABLED_CHECK_POOL_PRODUCER,
    /** Whether a pool access violation regarding consumer is checked or not */
    ABT_INFO_QUERY_KIND_ENABLED_CHECK_POOL_CONSUMER,
    /** Whether floating-point registers are saved on context switching or not
     */
    ABT_INFO_QUERY_KIND_ENABLED_PRESERVE_FPU,
    /** Whether the thread cancellation feature is supported or not */
    ABT_INFO_QUERY_KIND_ENABLED_THREAD_CANCEL,
    /** Whether the task cancellation feature is supported or not */
    ABT_INFO_QUERY_KIND_ENABLED_TASK_CANCEL,
    /** Whether the thread and task migration feature is supported or not */
    ABT_INFO_QUERY_KIND_ENABLED_MIGRATION,
    /** Whether the stackable scheduler feature is supported or not */
    ABT_INFO_QUERY_KIND_ENABLED_STACKABLE_SCHED,
    /** Whether the external thread feature is supported or not */
    ABT_INFO_QUERY_KIND_ENABLED_EXTERNAL_THREAD,
    /** Whether a predefined scheduler sleeps when idle or not */
    ABT_INFO_QUERY_KIND_ENABLED_SCHED_SLEEP,
    /** Whether the Argobots configuration is printed in the top-level
     *  ABT_init() or not */
    ABT_INFO_QUERY_KIND_ENABLED_PRINT_CONFIG,
    /** Whether the affinity setting is supported or not */
    ABT_INFO_QUERY_KIND_ENABLED_AFFINITY,
    /** The maximum number of execution streams */
    ABT_INFO_QUERY_KIND_MAX_NUM_XSTREAMS,
    /** Default stack size of ULTs */
    ABT_INFO_QUERY_KIND_DEFAULT_THREAD_STACKSIZE,
    /** Default stack size of ULT-type schedulers */
    ABT_INFO_QUERY_KIND_DEFAULT_SCHED_STACKSIZE,
    /** Default event-checking frequency of a predefined scheduler */
    ABT_INFO_QUERY_KIND_DEFAULT_SCHED_EVENT_FREQ,
    /** Default sleep time of a predefined scheduler */
    ABT_INFO_QUERY_KIND_DEFAULT_SCHED_SLEEP_NSEC,
    /** Whether the tool interface is enabled or not */
    ABT_INFO_QUERY_KIND_ENABLED_TOOL,
    /** Whether fcontext is used for context switch or not */
    ABT_INFO_QUERY_KIND_FCONTEXT,
    /** Whether dynamic promotion is used for context switch or not */
    ABT_INFO_QUERY_KIND_DYNAMIC_PROMOTION,
    /** Whether the stack unwinding feature is enabled or not */
    ABT_INFO_QUERY_KIND_ENABLED_STACK_UNWIND,
    /** Whether the stack overflow check is enabled or not */
    ABT_INFO_QUERY_KIND_ENABLED_STACK_OVERFLOW_CHECK,
    /** Wait policy */
    ABT_INFO_QUERY_KIND_WAIT_POLICY,
};

/**
 * @ingroup TOOL
 * @brief   Tool query kind for \c ABT_tool_query_thread().
 */
enum ABT_tool_query_kind {
    /** Query a pool to which a work unit is or will be pushed. */
    ABT_TOOL_QUERY_KIND_POOL,
    /** Query a current depth of stacked work units. */
    ABT_TOOL_QUERY_KIND_STACK_DEPTH,
    /** Query a type of the caller that incurs an event. */
    ABT_TOOL_QUERY_KIND_CALLER_TYPE,
    /** Query a handle to the caller that incurs an event. */
    ABT_TOOL_QUERY_KIND_CALLER_HANDLE,
    /** Query a type of the synchronization object that incurs an event. */
    ABT_TOOL_QUERY_KIND_SYNC_OBJECT_TYPE,
    /** Query a handle of the synchronization object that incurs an event. */
    ABT_TOOL_QUERY_KIND_SYNC_OBJECT_HANDLE,
};

/**
 * @ingroup TOOL
 * @brief   Type of execution entity.
 */
enum ABT_exec_entity_type {
    /** External thread. */
    ABT_EXEC_ENTITY_TYPE_EXT,
    /** Work unit. */
    ABT_EXEC_ENTITY_TYPE_THREAD,
};

/**
 * @ingroup TOOL
 * @brief   Type of synchronization event.
 */
enum ABT_sync_event_type {
    /** Unknown synchronization events. */
    ABT_SYNC_EVENT_TYPE_UNKNOWN = 0,
    /** Explicit context switching triggered by the user. */
    ABT_SYNC_EVENT_TYPE_USER,
    /** Other synchronization events. */
    ABT_SYNC_EVENT_TYPE_OTHER,
    /** Joining an execution stream. */
    ABT_SYNC_EVENT_TYPE_XSTREAM_JOIN,
    /** Joining a work unit. */
    ABT_SYNC_EVENT_TYPE_THREAD_JOIN,
    /** Events related to a mutex. */
    ABT_SYNC_EVENT_TYPE_MUTEX,
    /** Events related to a condition variable. */
    ABT_SYNC_EVENT_TYPE_COND,
    /** Events related to a readers-writer lock. */
    ABT_SYNC_EVENT_TYPE_RWLOCK,
    /** Events related to an eventual. */
    ABT_SYNC_EVENT_TYPE_EVENTUAL,
    /** Events related to a future. */
    ABT_SYNC_EVENT_TYPE_FUTURE,
    /** Events related to a barrier. */
    ABT_SYNC_EVENT_TYPE_BARRIER,
};

/**
 * @ingroup TOOL
 * @brief   Work-unit-event mask: none.
 */
#define ABT_TOOL_EVENT_THREAD_NONE    (0)
/**
 * @ingroup TOOL
 * @brief   Work-unit-event mask: creating a work unit.
 */
#define ABT_TOOL_EVENT_THREAD_CREATE  (1 << 0)
/**
 * @ingroup TOOL
 * @brief   Work-unit-event mask: joining a work unit.
 */
#define ABT_TOOL_EVENT_THREAD_JOIN    (1 << 1)
/**
 * @ingroup TOOL
 * @brief   Work-unit-event mask: freeing a work unit.
 */
#define ABT_TOOL_EVENT_THREAD_FREE    (1 << 2)
/**
 * @ingroup TOOL
 * @brief   Work-unit-event mask: reviving a work unit.
 */
#define ABT_TOOL_EVENT_THREAD_REVIVE  (1 << 3)
/**
 * @ingroup TOOL
 * @brief   Work-unit-event mask: running a work unit.
 */
#define ABT_TOOL_EVENT_THREAD_RUN     (1 << 4)
/**
 * @ingroup TOOL
 * @brief   Work-unit-event mask: finishing a work unit.
 */
#define ABT_TOOL_EVENT_THREAD_FINISH  (1 << 5)
/**
 * @ingroup TOOL
 * @brief   Work-unit-event mask: canceling a work unit.
 */
#define ABT_TOOL_EVENT_THREAD_CANCEL  (1 << 6)
/**
 * @ingroup TOOL
 * @brief   Work-unit-event mask: yielding a work unit.
 */
#define ABT_TOOL_EVENT_THREAD_YIELD   (1 << 7)
/**
 * @ingroup TOOL
 * @brief   Work-unit-event mask: suspending a work unit.
 */
#define ABT_TOOL_EVENT_THREAD_SUSPEND (1 << 8)
/**
 * @ingroup TOOL
 * @brief   Work-unit-event mask: resuming a work unit.
 */
#define ABT_TOOL_EVENT_THREAD_RESUME  (1 << 9)
/**
 * @ingroup TOOL
 * @brief   Work-unit-event mask: all events.
 */
#define ABT_TOOL_EVENT_THREAD_ALL     ((uint64_t)((1 << 12) - 1))


/** @brief  True constant for ABT_bool. */
#define ABT_TRUE  1
/** @brief  False constant for ABT_bool. */
#define ABT_FALSE 0

/**
 * @brief Unused macro
 *
 * @changev20
 * \DOC_V20 This constant is removed since no Argobots routine uses it.
 * @endchangev20
 */
#define ABT_XSTREAM_ANY_RANK    -1

/* Data Types */
struct ABT_xstream_opaque;
struct ABT_xstream_barrier_opaque;
struct ABT_sched_opaque;
struct ABT_sched_config_opaque;
struct ABT_pool_opaque;
struct ABT_pool_config_opaque;
struct ABT_unit_opaque;
struct ABT_thread_opaque;
struct ABT_thread_attr_opaque;
struct ABT_task_opaque;
struct ABT_key_opaque;
struct ABT_mutex_opaque;
struct ABT_mutex_attr_opaque;
struct ABT_cond_opaque;
struct ABT_rwlock_opaque;
struct ABT_eventual_opaque;
struct ABT_future_opaque;
struct ABT_barrier_opaque;
struct ABT_timer_opaque;
struct ABT_tool_context_opaque;

/**
 * @ingroup ES
 * @brief   Execution stream handle type.
 *
 * A NULL handle of this type is \c ABT_XSTREAM_NULL.
 */
typedef struct ABT_xstream_opaque *         ABT_xstream;
/**
 * @ingroup ES
 * @brief   Execution stream state type.
 */
typedef enum ABT_xstream_state              ABT_xstream_state;
/**
 * @ingroup ES_BARRIER
 * @brief   Execution-stream barrier handle type.
 *
 * A NULL handle of this type is \c ABT_XSTREAM_BARRIER_NULL.
 */
typedef struct ABT_xstream_barrier_opaque * ABT_xstream_barrier;
/**
 * @ingroup SCHED
 * @brief   Scheduler handle type.
 *
 * A NULL handle of this type is \c ABT_SCHED_NULL.
 */
typedef struct ABT_sched_opaque *           ABT_sched;
/**
 * @ingroup SCHED_CONFIG
 * @brief   Scheduler configuration handle type.
 *
 * A NULL handle of this type is \c ABT_SCHED_CONFIG_NULL.
 */
typedef struct ABT_sched_config_opaque *    ABT_sched_config;
/**
 * @ingroup SCHED
 * @brief   Predefined scheduler type.
 */
typedef enum ABT_sched_predef               ABT_sched_predef;
/**
 * @ingroup SCHED
 * @brief   Scheduler state type.
 *
 * @changev20
 * \DOC_V20 This type is removed since no Argobots routine uses this.
 * @endchangev20
 */
typedef enum ABT_sched_state                ABT_sched_state;
/**
 * @ingroup SCHED
 * @brief   Scheduler's work unit type.
 */
typedef enum ABT_sched_type                 ABT_sched_type;
/**
 * @ingroup POOL
 * @brief   Pool handle type.
 *
 * A NULL handle of this type is \c ABT_POOL_NULL.
 */
typedef struct ABT_pool_opaque *            ABT_pool;
/**
 * @ingroup POOL
 * @brief   Pool configuration handle type.
 *
 * A NULL handle of this type is \c ABT_POOL_CONFIG_NULL.
 */
typedef struct ABT_pool_config_opaque *     ABT_pool_config;
/**
 * @ingroup POOL
 * @brief   Predefined pool type.
 */
typedef enum ABT_pool_kind                  ABT_pool_kind;
/**
 * @ingroup POOL
 * @brief   Pool access type.
 */
typedef enum ABT_pool_access                ABT_pool_access;
/**
 * @ingroup UNIT
 * @brief   Work unit handle type for scheduling.
 *
 * \c ABT_unit is a work unit handle encapsulated by its associated pool, so
 * the value of \c ABT_unit is different from its associated \c ABT_thread or
 * \c ABT_task.
 *
 * A NULL handle of this type is \c ABT_UNIT_NULL.
 */
typedef struct ABT_unit_opaque *            ABT_unit;
/**
 * @ingroup UNIT
 * @brief   Work unit type.
 */
typedef enum ABT_unit_type                  ABT_unit_type;
/**
 * @ingroup UNIT
 * @brief   Work unit ID type.
 */
typedef uint64_t                            ABT_unit_id;
/**
 * @ingroup ULT
 * @brief   Work unit handle type.
 *
 * A NULL handle of this type is \c ABT_THREAD_NULL.
 *
 * @changev20
 * \DOC_DESC_V1X_THREAD_TASK_NULL
 * @endchangev20
 */
typedef struct ABT_thread_opaque *          ABT_thread;
/**
 * @ingroup ULT
 * @brief   ULT attribute handle type.
 *
 * A NULL handle of this type is \c ABT_THREAD_ATTR_NULL.
 */
typedef struct ABT_thread_attr_opaque *     ABT_thread_attr;
/**
 * @ingroup ULT
 * @brief   Work unit state type.
 */
typedef enum ABT_thread_state               ABT_thread_state;
/**
 * @ingroup TASK
 * @brief   Tasklet state type.
 *
 * @changev20
 * \DOC_V20 This type is replaced by \c ABT_thread_state.
 * @endchangev20
 */
typedef enum ABT_task_state                 ABT_task_state;
/**
 * @ingroup ULT
 * @brief   Work unit ID type.
 *
 * This type is an alias of \c ABT_unit_id.
 */
typedef ABT_unit_id                         ABT_thread_id;
/**
 * @ingroup TASK
 * @brief   Work unit handle type.
 *
 * This type is an alias of \c ABT_thread.
 *
 * A NULL handle of this type is \c ABT_TASK_NULL.
 *
 * @changev20
 * \DOC_DESC_V1X_THREAD_TASK_NULL
 * @endchangev20
 */
typedef struct ABT_thread_opaque *          ABT_task;
/**
 * @ingroup KEY
 * @brief   Work-unit-specific data key handle type.
 *
 * A NULL handle of this type is \c ABT_KEY_NULL.
 */
typedef struct ABT_key_opaque *             ABT_key;
/**
 * @ingroup MUTEX
 * @brief   Mutex handle type.
 *
 * A NULL handle of this type is \c ABT_MUTEX_NULL.
 */
typedef struct ABT_mutex_opaque *           ABT_mutex;
/**
 * @ingroup MUTEX_ATTR
 * @brief   Mutex attribute handle type.
 *
 * A NULL handle of this type is \c ABT_MUTEX_ATTR_NULL.
 */
typedef struct ABT_mutex_attr_opaque *      ABT_mutex_attr;
/**
 * @ingroup COND
 * @brief   Condition variable handle type.
 *
 * A NULL handle of this type is \c ABT_COND_NULL.
 */
typedef struct ABT_cond_opaque *            ABT_cond;
/**
 * @ingroup RWLOCK
 * @brief   Readers-writer lock handle type.
 *
 * A NULL handle of this type is \c ABT_RWLOCK_NULL.
 */
typedef struct ABT_rwlock_opaque *          ABT_rwlock;
/**
 * @ingroup EVENTUAL
 * @brief   Eventual handle type.
 *
 * A NULL handle of this type is \c ABT_EVENTUAL_NULL.
 */
typedef struct ABT_eventual_opaque *        ABT_eventual;
/**
 * @ingroup FUTURE
 * @brief   Future handle type.
 *
 * A NULL handle of this type is \c ABT_FUTURE_NULL.
 */
typedef struct ABT_future_opaque *          ABT_future;
/**
 * @ingroup BARRIER
 * @brief   Barrier handle type.
 *
 * A NULL handle of this type is \c ABT_BARRIER_NULL.
 */
typedef struct ABT_barrier_opaque *         ABT_barrier;
/**
 * @ingroup TIMER
 * @brief   Timer handle type.
 *
 * A NULL handle of this type is \c ABT_TIMER_NULL.
 */
typedef struct ABT_timer_opaque *           ABT_timer;
/**
 * @brief  Boolean type.
 *
 * The value must be either \c ABT_TRUE or \c ABT_FALSE.  It is guaranteed that
 * \c ABT_FALSE is zero.
 */
typedef int                                 ABT_bool;
/**
 * @ingroup INFO
 * @brief   Query type for \c ABT_info_query_config().
 */
typedef enum ABT_info_query_kind            ABT_info_query_kind;
/**
 * @ingroup TOOL
 * @brief   Tool context handle type.
 *
 * A NULL handle of this type is \c ABT_TOOL_CONTEXT_NULL.
 */
typedef struct ABT_tool_context_opaque *    ABT_tool_context;
/**
 * @ingroup TOOL
 * @brief   Tool query type.
 */
typedef enum ABT_tool_query_kind            ABT_tool_query_kind;
/**
 * @ingroup TOOL
 * @brief   Execution entity type.
 */
typedef enum ABT_exec_entity_type           ABT_exec_entity_type;
/**
 * @ingroup TOOL
 * @brief   Synchronization event type.
 */
typedef enum ABT_sync_event_type            ABT_sync_event_type;


/* Null Object Handles */
#define ABT_NULL 1
#if ABT_NULL == 1
#define ABT_XSTREAM_NULL         ((ABT_xstream)        NULL)
#define ABT_XSTREAM_BARRIER_NULL ((ABT_xstream_barrier)NULL)
#define ABT_SCHED_NULL           ((ABT_sched)          NULL)
#define ABT_SCHED_CONFIG_NULL    ((ABT_sched_config)   NULL)
#define ABT_POOL_NULL            ((ABT_pool)           NULL)
#define ABT_POOL_CONFIG_NULL     ((ABT_pool_config)    NULL)
#define ABT_UNIT_NULL            ((ABT_unit)           NULL)
#define ABT_THREAD_NULL          ((ABT_thread)         NULL)
#define ABT_THREAD_ATTR_NULL     ((ABT_thread_attr)    NULL)
#define ABT_TASK_NULL            ((ABT_task)           NULL)
#define ABT_KEY_NULL             ((ABT_key)            NULL)
#define ABT_MUTEX_NULL           ((ABT_mutex)          NULL)
#define ABT_MUTEX_ATTR_NULL      ((ABT_mutex_attr)     NULL)
#define ABT_COND_NULL            ((ABT_cond)           NULL)
#define ABT_RWLOCK_NULL          ((ABT_rwlock)         NULL)
#define ABT_EVENTUAL_NULL        ((ABT_eventual)       NULL)
#define ABT_FUTURE_NULL          ((ABT_future)         NULL)
#define ABT_BARRIER_NULL         ((ABT_barrier)        NULL)
#define ABT_TIMER_NULL           ((ABT_timer)          NULL)
#define ABT_TOOL_CONTEXT_NULL    ((ABT_tool_context)   NULL)
#else
#define ABT_XSTREAM_NULL         ((ABT_xstream)        (0x01))
#define ABT_XSTREAM_BARRIER_NULL ((ABT_xstream_barrier)(0x02))
#define ABT_SCHED_NULL           ((ABT_sched)          (0x03))
#define ABT_SCHED_CONFIG_NULL    ((ABT_sched_config)   (0x04))
#define ABT_POOL_NULL            ((ABT_pool)           (0x05))
#define ABT_POOL_CONFIG_NULL     ((ABT_pool_config)    (0x06))
#define ABT_UNIT_NULL            ((ABT_unit)           (0x07))
#define ABT_THREAD_NULL          ((ABT_thread)         (0x08))
#define ABT_THREAD_ATTR_NULL     ((ABT_thread_attr)    (0x09))
#define ABT_TASK_NULL            ((ABT_task)           (0x0a))
#define ABT_KEY_NULL             ((ABT_key)            (0x0b))
#define ABT_MUTEX_NULL           ((ABT_mutex)          (0x0c))
#define ABT_MUTEX_ATTR_NULL      ((ABT_mutex_attr)     (0x0d))
#define ABT_COND_NULL            ((ABT_cond)           (0x0e))
#define ABT_RWLOCK_NULL          ((ABT_rwlock)         (0x0f))
#define ABT_EVENTUAL_NULL        ((ABT_eventual)       (0x10))
#define ABT_FUTURE_NULL          ((ABT_future)         (0x11))
#define ABT_BARRIER_NULL         ((ABT_barrier)        (0x12))
#define ABT_TIMER_NULL           ((ABT_timer)          (0x13))
#define ABT_TOOL_CONTEXT_NULL    ((ABT_tool_context)   (0x14))
#endif

/**
 * @ingroup MUTEX
 * @brief   A struct that can be converted to ABT_mutex.
 * @hideinitializer
 *
 * \c ABT_mutex_memory is a struct to statically allocate and initialize
 * \c ABT_mutex.  \c ABT_mutex_memory can be statically initialized by
 * \c ABT_MUTEX_MEMORY_INITIALIZER and \c ABT_RECURSIVE_MUTEX_INITIALIZER and
 * can be converted to \c ABT_mutex by \c ABT_MUTEX_MEMORY_GET_HANDLE().
 *
 * \c dummy may not be accessed by a user.
 */
typedef struct {
    int dummy[16];
} ABT_mutex_memory;

/**
 * @ingroup MUTEX
 * @brief   Initialize \c ABT_mutex_memory.
 *
 * \c ABT_MUTEX_INITIALIZER statically initializes \c ABT_mutex_memory.  The
 * created mutex is not recursive.

 * The following shows how to use \c ABT_MUTEX_INITIALIZER.
 * @code{.c}
 * ABT_mutex_memory mutex_mem = ABT_MUTEX_INITIALIZER;
 *
 * void thread(void *)
 * {
 *     ABT_mutex mutex = ABT_MUTEX_MEMORY_GET_HANDLE(&mutex_mem);
 *     ABT_mutex_lock(mutex);
 *     ABT_mutex_unlock(mutex);
 * }
 * @endcode
 *
 * \c ABT_mutex_memory that is in use may not be initialized again.
 */
#define ABT_MUTEX_INITIALIZER                                                  \
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }

/**
 * @ingroup MUTEX
 * @brief   Initialize \c ABT_mutex_memory with a recursive property.
 *
 * \c ABT_RECURSIVE_MUTEX_INITIALIZER statically initializes
 * \c ABT_mutex_memory.  The created mutex is recursive.
 *
 * The following shows how to use \c ABT_RECURSIVE_MUTEX_INITIALIZER.
 * @code{.c}
 * ABT_mutex_memory rec_mutex_mem = ABT_RECURSIVE_MUTEX_INITIALIZER;
 *
 * void thread(void *)
 * {
 *     ABT_mutex rec_mutex = ABT_MUTEX_MEMORY_GET_HANDLE(&rec_mutex_mem);
 *     // rec_mutex is recursive.
 *     ABT_mutex_lock(rec_mutex);
 *     ABT_mutex_lock(rec_mutex);
 *     ABT_mutex_unlock(rec_mutex);
 *     ABT_mutex_unlock(rec_mutex);
 * }
 * @endcode
 *
 * \c ABT_mutex_memory that is in use may not be initialized again.
 */
#define ABT_RECURSIVE_MUTEX_INITIALIZER                                        \
    { { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }

/**
 * @ingroup MUTEX
 * @brief   Obtain \c ABT_mutex from \c ABT_mutex_memory.
 *
 * \c ABT_MUTEX_MEMORY_GET_HANDLE() takes the pointer \c p_mutex_memory, which
 * points to \c ABT_mutex_memory, and returns \c ABT_mutex that internally uses
 * \c p_mutex_memory to store the data.  If the memory pointed to by
 * \c p_mutex_memory is not properly initialized, it returns a corrupted mutex.
 *
 * \c ABT_mutex obtained by \c ABT_MUTEX_MEMORY_GET_HANDLE() may not be freed by
 * \c ABT_mutex_free().  The lifetime of \c ABT_mutex obtained by
 * \c ABT_MUTEX_MEMORY_GET_HANDLE() is the same as that of \c ABT_mutex_memory.
 */
#define ABT_MUTEX_MEMORY_GET_HANDLE(p_mutex_memory)                            \
    ((ABT_mutex)p_mutex_memory)

/**
 * @ingroup COND
 * @brief   A struct that can be converted to ABT_cond.
 * @hideinitializer
 *
 * \c ABT_cond_memory is a struct to statically allocate and initialize
 * \c ABT_cond.  \c ABT_cond_memory can be statically initialized by
 * \c ABT_COND_MEMORY_INITIALIZER and converted to \c ABT_cond by
 * \c ABT_COND_MEMORY_GET_HANDLE().
 *
 * \c dummy may not be accessed by a user.
 */
typedef struct {
    int dummy[16];
} ABT_cond_memory;

/**
 * @ingroup COND
 * @brief   Initialize \c ABT_cond_memory.
 *
 * \c ABT_COND_INITIALIZER statically initializes \c ABT_cond_memory.

 * The following example shows how to use \c ABT_COND_INITIALIZER.
 * @code{.c}
 * ABT_mutex_memory mutex_mem = ABT_MUTEX_INITIALIZER;
 * ABT_cond_memory cond_mem = ABT_COND_INITIALIZER;
 *
 * void thread(void *)
 * {
 *     ABT_mutex mutex = ABT_MUTEX_MEMORY_GET_HANDLE(&mutex_mem);
 *     ABT_cond cond = ABT_COND_MEMORY_GET_HANDLE(&cond_mem);
 *     ABT_mutex_lock(mutex);
 *     if (...) {
 *        ABT_cond_wait(cond, mutex);
 *     } else {
 *        ABT_cond_signal(cond);
 *     }
 *     ABT_mutex_unlock(mutex);
 * }
 * @endcode
 *
 * \c ABT_cond_memory that is in use may not be initialized again.
 */
#define ABT_COND_INITIALIZER                                                   \
    { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 } }

/**
 * @ingroup COND
 * @brief   Obtain \c ABT_cond from \c ABT_cond_memory.
 *
 * \c ABT_COND_MEMORY_GET_HANDLE() takes the pointer \c p_cond_memory, which
 * points to \c ABT_cond_memory, and returns \c ABT_cond that internally uses
 * \c p_cond_memory to store the data.  If the memory pointed to by
 * \c p_cond_memory is not properly initialized, it returns a corrupted
 * condition variable.
 *
 * \c ABT_cond obtained by \c ABT_COND_MEMORY_GET_HANDLE() may not be freed by
 * \c ABT_cond_free().  The lifetime of \c ABT_cond obtained by
 * \c ABT_COND_MEMORY_GET_HANDLE() is the same as that of \c ABT_cond_memory.
 */
#define ABT_COND_MEMORY_GET_HANDLE(p_cond_memory)                              \
    ((ABT_cond)p_cond_memory)

/**
 * @ingroup SCHED_CONFIG
 * @brief   A struct that sets and gets a scheduler configuration.
 */
typedef enum {
    /** Parameter of type int */
    ABT_SCHED_CONFIG_INT    = 0,
    /** Parameter of type double */
    ABT_SCHED_CONFIG_DOUBLE = 1,
    /** Parameter of type pointer */
    ABT_SCHED_CONFIG_PTR    = 2,
} ABT_sched_config_type;

/**
 * @ingroup SCHED_CONFIG
 * @brief   A struct that sets and gets a scheduler configuration.
 */
typedef struct {
    /** An index of the configuration variable.  It must be non-negative. */
    int idx;
    /** Type of the configuration variable. */
    ABT_sched_config_type type;
} ABT_sched_config_var;

/**
 * @ingroup SCHED_CONFIG
 * @var     ABT_sched_config_var_end
 * @brief   Predefined ABT_sched_config_var to mark the last parameter.
 * @hideinitializer
 *
 * Check ABT_sched_config_create() for details.  The user may not change its
 * variables.
 */
extern ABT_sched_config_var ABT_sched_config_var_end ABT_API_PUBLIC;
/**
 * @ingroup SCHED_CONFIG
 * @var     ABT_sched_basic_freq
 * @brief   Predefined ABT_sched_config_var to configure the frequency for
 *          checking events of the basic scheduler.
 * @hideinitializer
 *
 * Its type is int.  The user may not change its variables.
 */
extern ABT_sched_config_var ABT_sched_basic_freq ABT_API_PUBLIC;
/**
 * @ingroup SCHED_CONFIG
 * @var     ABT_sched_config_access
 * @brief   Unused predefined ABT_sched_config_var.
 * @hideinitializer
 *
 * Its type is int.  Currently, this setting is ignored.  The user may not
 * change its variables.
 */
extern ABT_sched_config_var ABT_sched_config_access ABT_API_PUBLIC;
/**
 * @ingroup SCHED_CONFIG
 * @var     ABT_sched_config_automatic
 * @brief   Predefined ABT_sched_config_var to configure whether the scheduler
 *          is freed automatically or not.
 * @hideinitializer
 *
 * Its type is int.  If the value is non-zero, the scheduler is freed
 * automatically after its associated objects are released.  If the value is
 * zero, the scheduler is configured to be not freed automatically by the
 * Argobots runtime.  The user may not change its variables.
 */
extern ABT_sched_config_var ABT_sched_config_automatic ABT_API_PUBLIC;

/* Scheduler Functions */
typedef int      (*ABT_sched_init_fn)(ABT_sched, ABT_sched_config);
typedef void     (*ABT_sched_run_fn)(ABT_sched);
typedef int      (*ABT_sched_free_fn)(ABT_sched);
/* To get a pool ready for receiving a migration */
typedef ABT_pool (*ABT_sched_get_migr_pool_fn)(ABT_sched);

/**
 * @ingroup SCHED
 * @brief   A struct that defines a scheduler.
 */
typedef struct {
    /**
     * @brief Unused value.
     *
     * This value is ignored.  A created scheduler always uses a ULT as an
     * underlying work unit.
     */
    ABT_sched_type type;
    /**
     * @fn    int (*init)(ABT_sched sched, ABT_sched_config config)
     * @brief Function that initializes a scheduler.
     *
     * \c init() initializes the scheduler \c sched with the scheduler
     * configuration \c config.  If \c init() does not return \c ABT_SUCCESS,
     * the scheduler creation fails.
     *
     * \c init() is optional, so the user may set \c init to \c NULL.
     *
     * @note
     * The caller of \c init() is undefined, so a program that relies on the
     * caller of \c init() is non-conforming.
     *
     * \c init() is called only on creating a scheduler.  \c init() is not
     * called when its associated work unit is revived.
     */
    ABT_sched_init_fn          init;
    /**
     * @fn    void (*run)(ABT_sched sched)
     * @brief Function that defines a kernel of a scheduler.
     *
     * \c run() runs the scheduler \c sched.  The user can freely design this
     * function, Argobots assumes the following properties:
     *
     * - Scheduling loop:
     *
     *   \c run() pops units from pools associated with \c sched and run it.
     *
     *   \c sched can access pools that are not associated with \c sched.
     *   However, the Argobots runtime assumes that a scheduler that does not
     *   have units in its associated pools is idle and should yield to the
     *   parent.
     *
     * - Periodic event check:
     *
     *   \c run() calls \c ABT_xstream_check_events() with \c sched
     *   periodically.
     *
     *   The frequency is user-defined, but some Argobots routines such as
     *   request handling rely on \c ABT_xstream_check_events().
     *
     * - Finish \c run() if necessary:
     *
     *   \c run() calls \c ABT_sched_has_to_stop() with \c sched periodically
     *   and if it returns \c ABT_TRUE as \c stop, \c run() should return
     *   immediately.
     *
     *   The frequency is user-defined, but some Argobots routines such as
     *   request handling rely on the mechanism of \c ABT_sched_has_to_stop().
     *
     * The caller of \c run() is a work unit associated with \c sched.  If
     * \c sched is the main scheduler, the underlying execution stream is
     * unchanged in \c run().
     *
     * \c run() is not optional, so the user must implement this function.
     */
    ABT_sched_run_fn           run;
    /**
     * @fn    int (*free)(ABT_sched sched)
     * @brief Function that frees a scheduler.
     *
     * \c free() finalizes the scheduler \c sched with the scheduler.  The
     * return value of \c free() is ignored.
     *
     * \c free() is optional, so the user may set \c free to \c NULL.
     *
     * \c free() is called only on freeing a scheduler.  \c free() is not called
     * when its associated work unit is terminated.
     *
     * The caller of \c free() is undefined, so a program that relies on the
     * caller of \c free() is non-conforming.
     */
    ABT_sched_free_fn          free;
    /**
     * @fn    ABT_pool (*get_migr_pool)(ABT_sched sched)
     * @brief Function that returns a pool for migration.
     *
     * \c get_migr_pool() returns a pool from pools associated with the
     * scheduler \c sched as a work unit migration target.  If
     * \c get_migr_pool() returns either \c ABT_POOL_NULL or a pool that is not
     * associated with \c sched, the results are undefined.
     *
     * \c get_migr_pool() is optional, so the user may set \c get_migr_pool to
     * \c NULL.  If \c get_migr_pool is \c NULL, the Argobots runtime chooses
     * a proper pool that is associated with \c sched.
     *
     * The caller of \c get_migr_pool() is undefined, so a program that relies
     * on the caller of \c get_migr_pool() is non-conforming.
     */
    ABT_sched_get_migr_pool_fn get_migr_pool;
} ABT_sched_def;

/* Pool Functions */
typedef ABT_unit_type (*ABT_unit_get_type_fn)(ABT_unit);
typedef ABT_thread    (*ABT_unit_get_thread_fn)(ABT_unit);
typedef ABT_task      (*ABT_unit_get_task_fn)(ABT_unit);
typedef ABT_bool      (*ABT_unit_is_in_pool_fn)(ABT_unit);
typedef ABT_unit      (*ABT_unit_create_from_thread_fn)(ABT_thread);
typedef ABT_unit      (*ABT_unit_create_from_task_fn)(ABT_task);
typedef void          (*ABT_unit_free_fn)(ABT_unit *);
typedef int           (*ABT_pool_init_fn)(ABT_pool, ABT_pool_config);
typedef size_t        (*ABT_pool_get_size_fn)(ABT_pool);
typedef void          (*ABT_pool_push_fn)(ABT_pool, ABT_unit);
typedef ABT_unit      (*ABT_pool_pop_fn)(ABT_pool);
typedef ABT_unit      (*ABT_pool_pop_wait_fn)(ABT_pool, double);
typedef ABT_unit      (*ABT_pool_pop_timedwait_fn)(ABT_pool, double); /* Deprecated .*/
typedef int           (*ABT_pool_remove_fn)(ABT_pool, ABT_unit);
typedef int           (*ABT_pool_free_fn)(ABT_pool);
typedef int           (*ABT_pool_print_all_fn)(ABT_pool, void *arg,
                                               void (*)(void*, ABT_unit));

/**
 * @ingroup POOL
 * @brief   A struct that defines a pool.
 */
typedef struct {
    /**
     * @brief Access type.
     *
     * This value is used to determine a value returned by
     * \c ABT_pool_get_access().  Argobots assumes all pools can be accessed by
     * any ULTs, tasklets, and external threads.  It is the user's
     * responsibility to manage the access to pools.
     *
     * @changev11
     * \DOC_DESC_V10_POOL_NOACCESS
     * @endchangev11
     */
    ABT_pool_access access;
    /**
     * @brief Unused function
     *
     * This function is not used.
     */
    ABT_unit_get_type_fn           u_get_type;
    /**
     * @brief Unused function.
     *
     * This function is not used.
     */
    ABT_unit_get_thread_fn         u_get_thread;
    /**
     * @brief Unused function.
     *
     * This function is not used.
     */
    ABT_unit_get_task_fn           u_get_task;
    /**
     * @fn    ABT_bool (*u_is_in_pool)(ABT_unit unit)
     * @brief Function that returns whether a work unit is in its associated
     *        pool or not.
     *
     * \c u_is_in_pool() returns whether the work unit \c unit is in its
     * associated pool or not.  If \c unit is in its pool, this function returns
     * \c ABT_TRUE.  Otherwise, this function returns \c ABT_FALSE.  \c unit is
     * not \c ABT_UNIT_NULL.
     *
     * \c u_is_in_pool() is optional, so the user may set \c u_is_in_pool to
     * \c NULL.  The Argobots does not call \c u_is_in_pool() if it is not
     * supported.
     *
     * The caller of \c u_is_in_pool() is undefined, so a program that relies on
     * the caller of \c u_is_in_pool() is non-conforming.
     */
    ABT_unit_is_in_pool_fn         u_is_in_pool;
    /**
     * @fn    ABT_unit (*u_create_from_thread)(ABT_thread thread)
     * @brief Function that creates an \c ABT_unit handle that is associated
     *        with an \c ABT_thread handle.
     *
     * \c u_create_from_thread() creates a user-defined \c ABT_unit handle that
     * is associated with the work-unit \c thread and returns.  \c thread is
     * neither \c ABT_THREAD_NULL nor \c ABT_TASK_NULL.  The returned value must
     * point to a 4-byte aligned memory address that is unique in the system.
     * For example, a pointer that points to a sufficiently large memory block
     * allocated by \c malloc() or \c mmap() satisfies this requirement.  This
     * function may return \c ABT_UNIT_NULL if creation fails.
     *
     * @note
     * Specifically, the Argobots implementation assumes that 1. the first 2
     * least significant bits are zero and 2. all ABT_unit values are unique.
     * Both requirements are satisfied if \c ABT_unit points to a 4-byte aligned
     * memory block.
     *
     * \c u_create_from_thread() is not optional, so the user must implement
     * this function.
     *
     * The caller of \c u_create_from_thread() is undefined, so a program that
     * relies on the caller of \c u_create_from_thread() is non-conforming.
     *
     * @changev11
     * \DOC_DESC_V10_POOL_NOTASK
     * @endchangev11
     */
    ABT_unit_create_from_thread_fn u_create_from_thread;
    /**
     * @brief Unused function.
     *
     * This function is not used.
     *
     * @changev11
     * \DOC_DESC_V10_POOL_NOTASK
     * @endchangev11
     */
    ABT_unit_create_from_task_fn   u_create_from_task;
    /**
     * @fn    void (*u_free)(ABT_unit *unit)
     * @brief Function that frees a work unit.
     *
     * \c u_free() frees the work unit \c unit that is created by
     * \c u_create_from_thread().  Its associated entity (i.e., \c ABT_thread)
     * is freed by the Argobots runtime.  Neither \c NULL nor a pointer pointing
     * to \c ABT_UNIT_NULL is passed as \c unit to this function.  \c u_free()
     * may modify the value pointed to by \c unit.
     *
     * \c u_free() is not optional, so the user must implement this function.
     *
     * The caller of \c u_free() is undefined, so a program that relies on the
     * caller of \c u_free() is non-conforming.
     */
    ABT_unit_free_fn               u_free;
    /**
     * @fn    int (*p_init)(ABT_pool pool, ABT_pool_config pool_config)
     * @brief Function that frees a work unit.
     *
     * \c p_init() sets up the pool \c pool with the pool configuration
     * \c pool_config.  If \c p_init() does not return \c ABT_SUCCESS, the
     * pool creation fails.
     *
     * \c p_init() is optional, so the user may set \c p_init to \c NULL.
     *
     * The caller of \c p_init() is undefined, so a program that relies on the
     * caller of \c p_init() is non-conforming.
     */
    ABT_pool_init_fn          p_init;
    /**
     * @fn    size_t (*p_get_size)(ABT_pool pool)
     * @brief Function that returns a work unit.
     *
     * \c p_get_size() returns the size of the pool \c pool.  The Argobots
     * assumes that the size is the number of work units in \c pool.
     *
     * @note
     * Specifically, the current Argobots treats a pool whose size is zero as an
     * empty pool.
     *
     * \c p_get_size() is not optional, so the user must implement this
     * function.
     *
     * The caller of \c p_get_size() is undefined, so a program that relies on
     * the caller of \c p_get_size() is non-conforming.
     */
    ABT_pool_get_size_fn      p_get_size;
    /**
     * @fn    void (*p_push)(ABT_pool pool, ABT_unit unit)
     * @brief Function that pushes a work unit to a pool.
     *
     * \c p_push() pushes the work unit \c unit to the pool \c pool.  \c unit
     * must be stored in \c pool and able to be popped by its pop functions
     * (e.g., \c p_pop()) later.
     *
     * \c p_push() is not optional, so the user must implement this function.
     *
     * The caller of \c p_push() is undefined, so a program that relies on the
     * caller of \c p_push() is non-conforming.
     */
    ABT_pool_push_fn          p_push;
    /**
     * @fn    ABT_unit (*p_pop)(ABT_pool pool)
     * @brief Function that pops a work unit from a pool.
     *
     * \c p_pop() pops a work unit from the pool \c pool and returns it.  If
     * no work unit exists in \c pool, \c ABT_UNIT_NULL must be returned.
     *
     * \c p_pop() is not optional, so the user must implement this function.
     *
     * The caller of \c p_pop() is undefined, so a program that relies on the
     * caller of \c p_pop() is non-conforming.
     */
    ABT_pool_pop_fn           p_pop;
#ifdef ABT_ENABLE_VER_20_API
    /**
     * @fn    ABT_unit (*p_pop_wait)(ABT_pool pool, double time_secs)
     * @brief Function that pops a work unit from a pool with wait.
     *
     * \c p_pop_wait() pops a work unit from the pool \c pool and returns it.
     * If no work unit exists in \c pool, \c ABT_UNIT_NULL must be returned.
     * \c time_secs hints at the duration in seconds that indicates how long the
     * caller should wait on \c pool until a work unit is added to \c pool.
     *
     * \c p_pop_wait() is optional, so the user may set \c p_pop_wait to
     * \c NULL.
     *
     * The caller of \c p_pop_wait() is undefined, so a program that relies on
     * the caller of \c p_pop_wait() is non-conforming.
     *
     * @changev20
     * \DOC_DESC_V1X_P_POP_WAIT
     * @endchangev20
     */
    ABT_pool_pop_wait_fn      p_pop_wait;
#endif
    /**
     * @fn    ABT_unit (*p_pop_timedwait)(ABT_pool pool, double abstime_secs)
     * @brief Function that pops a work unit from a pool with wait.
     *
     * \c p_pop_timedwait() pops a work unit from the pool \c pool and returns
     * it.  If no work unit exists in \c pool, \c ABT_UNIT_NULL must be
     * returned.  \c abstime_secs hints at the system time that indicates how
     * long the caller should wait on \c pool until a work unit is added to
     * \c pool.  The current system time is obtained via \c ABT_get_wtime().
     *
     * \c p_pop_timedwait() is optional, so the user may set \c p_pop_timedwait
     * to \c NULL.
     *
     * The caller of \c p_pop_timedwait() is undefined, so a program that relies
     * on the caller of \c p_pop_timedwait() is non-conforming.
     *
     * @changev20
     * \DOC_V20 \c p_pop_timedwait() is deprecated and replaced by
     * \c p_pop_wait().
     * @endchangev20
     */
    ABT_pool_pop_timedwait_fn p_pop_timedwait;
    /**
     * @fn    int (*p_remove)(ABT_pool pool, ABT_unit unit)
     * @brief Function that removes a work unit from a pool.
     *
     * \c p_remove() removes the work unit \c unit from the pool \c pool.  The
     * caller of this function guarantees that \c unit exists in the pool.
     * The return value of this function is ignored.
     *
     * \c p_remove() is optional, so the user may set \c p_remove to \c NULL.
     *
     * The caller of \c p_remove() is undefined, so a program that relies on
     * the caller of \c p_remove() is non-conforming.
     */
    ABT_pool_remove_fn        p_remove;
    /**
     * @fn    int (*p_free)(ABT_pool pool)
     * @brief Function that frees a pool.
     *
     * \c p_free() frees the pool \c pool.  The return value of this function is
     * ignored.
     *
     * \c p_free() is optional, so the user may set \c p_free to \c NULL.
     *
     * The caller of \c p_free() is undefined, so a program that relies on the
     * caller of \c p_free() is non-conforming.
     */
    ABT_pool_free_fn          p_free;
    /**
     * @fn    int (*p_print_all)(ABT_pool pool, void *arg,
     *                           void (*print_f)(void *arg, ABT_unit unit))
     * @brief Function that applies a user-given function to all work units in a
     *        pool.
     *
     * \c p_print_all() applies \c print_f to all work units in the pool
     * \c pool.  \c print_f() is called with the user-given argument \c arg and
     * the work unit handle.  The caller guarantees that \c print_f() does not
     * modify the states of \c pool and work units in \c pool.
     *
     * \c p_print_all() is optional, so the user may set \c p_print_all to
     * \c NULL.
     *
     * The caller of \c p_print_all() is undefined, so a program that relies on
     * the caller of \c p_print_all() is non-conforming.
     */
    ABT_pool_print_all_fn     p_print_all;
} ABT_pool_def;

/* Tool callback type. */
typedef void (*ABT_tool_thread_callback_fn)(ABT_thread, ABT_xstream, uint64_t event,
                                            ABT_tool_context context, void *user_arg);
typedef void (*ABT_tool_task_callback_fn)(ABT_task, ABT_xstream, uint64_t event,
                                          ABT_tool_context context, void *user_arg);

/* Init & Finalize */
int ABT_init(int argc, char **argv) ABT_API_PUBLIC;
int ABT_finalize(void) ABT_API_PUBLIC;
int ABT_initialized(void) ABT_API_PUBLIC;

/* Execution Stream (ES) */
int ABT_xstream_create(ABT_sched sched, ABT_xstream *newxstream) ABT_API_PUBLIC;
int ABT_xstream_create_basic(ABT_sched_predef predef, int num_pools,
                             ABT_pool *pools, ABT_sched_config config,
                             ABT_xstream *newxstream) ABT_API_PUBLIC;
int ABT_xstream_create_with_rank(ABT_sched sched, int rank,
                                 ABT_xstream *newxstream) ABT_API_PUBLIC;
int ABT_xstream_free(ABT_xstream *xstream) ABT_API_PUBLIC;
int ABT_xstream_join(ABT_xstream xstream) ABT_API_PUBLIC;
int ABT_xstream_revive(ABT_xstream xstream) ABT_API_PUBLIC;
int ABT_xstream_exit(void) ABT_API_PUBLIC;
int ABT_xstream_cancel(ABT_xstream xstream) ABT_API_PUBLIC;
int ABT_xstream_self(ABT_xstream *xstream) ABT_API_PUBLIC;
int ABT_xstream_self_rank(int *rank) ABT_API_PUBLIC;
int ABT_xstream_set_rank(ABT_xstream xstream, int rank) ABT_API_PUBLIC;
int ABT_xstream_get_rank(ABT_xstream xstream, int *rank) ABT_API_PUBLIC;
int ABT_xstream_set_main_sched(ABT_xstream xstream, ABT_sched sched) ABT_API_PUBLIC;
int ABT_xstream_set_main_sched_basic(ABT_xstream xstream,
                                     ABT_sched_predef predef,
                                     int num_pools, ABT_pool *pools) ABT_API_PUBLIC;
int ABT_xstream_get_main_sched(ABT_xstream xstream, ABT_sched *sched) ABT_API_PUBLIC;
int ABT_xstream_get_main_pools(ABT_xstream xstream, int max_pools,
                               ABT_pool *pools) ABT_API_PUBLIC;
int ABT_xstream_get_state(ABT_xstream xstream, ABT_xstream_state *state) ABT_API_PUBLIC;
int ABT_xstream_equal(ABT_xstream xstream1, ABT_xstream xstream2,
                      ABT_bool *result) ABT_API_PUBLIC;
int ABT_xstream_get_num(int *num_xstreams) ABT_API_PUBLIC;
int ABT_xstream_is_primary(ABT_xstream xstream, ABT_bool *is_primary) ABT_API_PUBLIC;
int ABT_xstream_run_unit(ABT_unit unit, ABT_pool pool) ABT_API_PUBLIC;
int ABT_xstream_check_events(ABT_sched sched) ABT_API_PUBLIC;
int ABT_xstream_set_cpubind(ABT_xstream xstream, int cpuid) ABT_API_PUBLIC;
int ABT_xstream_get_cpubind(ABT_xstream xstream, int *cpuid) ABT_API_PUBLIC;
int ABT_xstream_set_affinity(ABT_xstream xstream, int num_cpuids, int *cpuids)
                             ABT_API_PUBLIC;
int ABT_xstream_get_affinity(ABT_xstream xstream, int max_cpuids, int *cpuids,
                             int *num_cpuids) ABT_API_PUBLIC;

/* ES Barrier */
int ABT_xstream_barrier_create(uint32_t num_waiters, ABT_xstream_barrier *newbarrier)
                               ABT_API_PUBLIC;
int ABT_xstream_barrier_free(ABT_xstream_barrier *barrier) ABT_API_PUBLIC;
int ABT_xstream_barrier_wait(ABT_xstream_barrier barrier) ABT_API_PUBLIC;

/* Scheduler */
int ABT_sched_create(ABT_sched_def *def, int num_pools, ABT_pool *pools,
                     ABT_sched_config config, ABT_sched *newsched) ABT_API_PUBLIC;
int ABT_sched_create_basic(ABT_sched_predef predef, int num_pools,
                           ABT_pool *pools, ABT_sched_config config,
                           ABT_sched *newsched) ABT_API_PUBLIC;
int ABT_sched_free(ABT_sched *sched) ABT_API_PUBLIC;
int ABT_sched_set_data(ABT_sched sched, void *data) ABT_API_PUBLIC;
int ABT_sched_get_data(ABT_sched sched, void **data) ABT_API_PUBLIC;
int ABT_sched_get_num_pools(ABT_sched sched, int *num_pools) ABT_API_PUBLIC;
int ABT_sched_get_pools(ABT_sched sched, int max_pools, int idx,
                        ABT_pool *pools) ABT_API_PUBLIC;
int ABT_sched_get_size(ABT_sched sched, size_t *size) ABT_API_PUBLIC;
int ABT_sched_get_total_size(ABT_sched sched, size_t *size) ABT_API_PUBLIC;
int ABT_sched_finish(ABT_sched sched) ABT_API_PUBLIC;
int ABT_sched_exit(ABT_sched sched) ABT_API_PUBLIC;
int ABT_sched_has_to_stop(ABT_sched sched, ABT_bool *stop) ABT_API_PUBLIC;

/* Scheduler config */
int ABT_sched_config_create(ABT_sched_config *config, ...) ABT_API_PUBLIC;
int ABT_sched_config_read(ABT_sched_config config, int num_vars, ...) ABT_API_PUBLIC;
int ABT_sched_config_free(ABT_sched_config *config) ABT_API_PUBLIC;

/* Pool */
int ABT_pool_create(ABT_pool_def *def, ABT_pool_config config,
                    ABT_pool *newpool) ABT_API_PUBLIC;
int ABT_pool_create_basic(ABT_pool_kind kind, ABT_pool_access access,
                          ABT_bool automatic, ABT_pool *newpool) ABT_API_PUBLIC;
int ABT_pool_free(ABT_pool *pool) ABT_API_PUBLIC;
int ABT_pool_get_access(ABT_pool pool, ABT_pool_access *access) ABT_API_PUBLIC;
int ABT_pool_get_size(ABT_pool pool, size_t *size) ABT_API_PUBLIC;
int ABT_pool_get_total_size(ABT_pool pool, size_t *size) ABT_API_PUBLIC;
int ABT_pool_pop(ABT_pool pool, ABT_unit *unit) ABT_API_PUBLIC;
int ABT_pool_pop_wait(ABT_pool pool, ABT_unit *unit, double time_secs) ABT_API_PUBLIC;
int ABT_pool_pop_timedwait(ABT_pool pool, ABT_unit *unit, double abstime_secs)
                           ABT_DEPRECATED ABT_API_PUBLIC;
int ABT_pool_remove(ABT_pool pool, ABT_unit unit) ABT_API_PUBLIC;
int ABT_pool_push(ABT_pool pool, ABT_unit unit) ABT_API_PUBLIC;
int ABT_pool_print_all(ABT_pool pool, void *arg,
                       void (*print_fn)(void *arg, ABT_unit)) ABT_API_PUBLIC;
int ABT_pool_set_data(ABT_pool pool, void *data) ABT_API_PUBLIC;
int ABT_pool_get_data(ABT_pool pool, void **data) ABT_API_PUBLIC;
int ABT_pool_add_sched(ABT_pool pool, ABT_sched sched) ABT_API_PUBLIC;
int ABT_pool_get_id(ABT_pool pool, int *id) ABT_API_PUBLIC;

/* Work Unit */
int ABT_unit_get_thread(ABT_unit unit, ABT_thread *thread) ABT_API_PUBLIC;
int ABT_unit_set_associated_pool(ABT_unit unit, ABT_pool pool) ABT_API_PUBLIC;

/* User-level Thread (ULT) */
int ABT_thread_create(ABT_pool pool, void (*thread_func)(void *), void *arg,
                      ABT_thread_attr attr, ABT_thread *newthread) ABT_API_PUBLIC;
int ABT_thread_create_on_xstream(ABT_xstream xstream,
                      void (*thread_func)(void *), void *arg,
                      ABT_thread_attr attr, ABT_thread *newthread) ABT_API_PUBLIC;
int ABT_thread_create_many(int num_threads, ABT_pool *pool_list,
                      void (**thread_func_list)(void *), void **arg_list,
                      ABT_thread_attr attr, ABT_thread *newthread_list)
                      ABT_API_PUBLIC;
int ABT_thread_revive(ABT_pool pool, void(*thread_func)(void *), void *arg,
                      ABT_thread *thread) ABT_API_PUBLIC;
int ABT_thread_free(ABT_thread *thread) ABT_API_PUBLIC;
int ABT_thread_free_many(int num_threads, ABT_thread *thread_list) ABT_API_PUBLIC;
int ABT_thread_join(ABT_thread thread) ABT_API_PUBLIC;
int ABT_thread_join_many(int num_threads, ABT_thread *thread_list) ABT_API_PUBLIC;
int ABT_thread_exit(void) ABT_API_PUBLIC;
int ABT_thread_cancel(ABT_thread thread) ABT_API_PUBLIC;
int ABT_thread_self(ABT_thread *thread) ABT_API_PUBLIC;
int ABT_thread_self_id(ABT_unit_id *id) ABT_API_PUBLIC;
int ABT_thread_get_last_xstream(ABT_thread thread, ABT_xstream *xstream) ABT_API_PUBLIC;
int ABT_thread_get_state(ABT_thread thread, ABT_thread_state *state) ABT_API_PUBLIC;
int ABT_thread_get_last_pool(ABT_thread thread, ABT_pool *pool) ABT_API_PUBLIC;
int ABT_thread_get_last_pool_id(ABT_thread thread, int *id) ABT_API_PUBLIC;
int ABT_thread_get_unit(ABT_thread thread, ABT_unit *unit) ABT_API_PUBLIC;
int ABT_thread_set_associated_pool(ABT_thread thread, ABT_pool pool) ABT_API_PUBLIC;
int ABT_thread_yield_to(ABT_thread thread) ABT_API_PUBLIC;
int ABT_thread_yield(void) ABT_API_PUBLIC;
int ABT_thread_resume(ABT_thread thread) ABT_API_PUBLIC;
int ABT_thread_migrate_to_xstream(ABT_thread thread, ABT_xstream xstream) ABT_API_PUBLIC;
int ABT_thread_migrate_to_sched(ABT_thread thread, ABT_sched sched) ABT_API_PUBLIC;
int ABT_thread_migrate_to_pool(ABT_thread thread, ABT_pool pool) ABT_API_PUBLIC;
int ABT_thread_migrate(ABT_thread thread) ABT_API_PUBLIC;
int ABT_thread_set_callback(ABT_thread thread,
        void(*cb_func)(ABT_thread thread, void *cb_arg), void *cb_arg) ABT_API_PUBLIC;
int ABT_thread_set_migratable(ABT_thread thread, ABT_bool migratable) ABT_API_PUBLIC;
int ABT_thread_is_migratable(ABT_thread thread, ABT_bool *is_migratable) ABT_API_PUBLIC;
int ABT_thread_is_primary(ABT_thread thread, ABT_bool *is_primary) ABT_API_PUBLIC;
int ABT_thread_is_unnamed(ABT_thread thread, ABT_bool *is_unnamed) ABT_API_PUBLIC;
int ABT_thread_equal(ABT_thread thread1, ABT_thread thread2, ABT_bool *result)
                     ABT_API_PUBLIC;
int ABT_thread_get_stacksize(ABT_thread thread, size_t *stacksize) ABT_API_PUBLIC;
int ABT_thread_get_id(ABT_thread thread, ABT_unit_id *thread_id) ABT_API_PUBLIC;
int ABT_thread_set_arg(ABT_thread thread, void *arg) ABT_API_PUBLIC;
int ABT_thread_get_arg(ABT_thread thread, void **arg) ABT_API_PUBLIC;
int ABT_thread_get_thread_func(ABT_thread thread, void (**thread_func)(void *)) ABT_API_PUBLIC;
int ABT_thread_set_specific(ABT_thread thread, ABT_key key, void *value) ABT_API_PUBLIC;
int ABT_thread_get_specific(ABT_thread thread, ABT_key key, void **value) ABT_API_PUBLIC;
int ABT_thread_get_attr(ABT_thread thread, ABT_thread_attr *attr) ABT_API_PUBLIC;

/* ULT Attributes */
int ABT_thread_attr_create(ABT_thread_attr *newattr) ABT_API_PUBLIC;
int ABT_thread_attr_free(ABT_thread_attr *attr) ABT_API_PUBLIC;
int ABT_thread_attr_set_stack(ABT_thread_attr attr, void *stackaddr,
                              size_t stacksize) ABT_API_PUBLIC;
int ABT_thread_attr_get_stack(ABT_thread_attr attr, void **stackaddr,
                              size_t *stacksize) ABT_API_PUBLIC;
int ABT_thread_attr_set_stacksize(ABT_thread_attr attr, size_t stacksize) ABT_API_PUBLIC;
int ABT_thread_attr_get_stacksize(ABT_thread_attr attr, size_t *stacksize) ABT_API_PUBLIC;
int ABT_thread_attr_set_callback(ABT_thread_attr attr,
        void(*cb_func)(ABT_thread thread, void *cb_arg), void *cb_arg) ABT_API_PUBLIC;
int ABT_thread_attr_set_migratable(ABT_thread_attr attr, ABT_bool is_migratable) ABT_API_PUBLIC;

/* Tasklet */
int ABT_task_create(ABT_pool pool, void (*task_func)(void *), void *arg,
                    ABT_task *newtask) ABT_API_PUBLIC;
int ABT_task_create_on_xstream(ABT_xstream xstream, void (*task_func)(void *),
                    void *arg, ABT_task *newtask) ABT_API_PUBLIC;
int ABT_task_revive(ABT_pool pool, void (*task_func)(void *), void *arg,
                    ABT_task *task) ABT_API_PUBLIC;
int ABT_task_free(ABT_task *task) ABT_API_PUBLIC;
int ABT_task_join(ABT_task task) ABT_API_PUBLIC;
int ABT_task_cancel(ABT_task task) ABT_API_PUBLIC;
int ABT_task_self(ABT_task *task) ABT_API_PUBLIC;
int ABT_task_self_id(uint64_t *id) ABT_API_PUBLIC;
int ABT_task_get_xstream(ABT_task task, ABT_xstream *xstream) ABT_API_PUBLIC;
int ABT_task_get_state(ABT_task task, ABT_task_state *state) ABT_API_PUBLIC;
int ABT_task_get_last_pool(ABT_task task, ABT_pool *pool) ABT_API_PUBLIC;
int ABT_task_get_last_pool_id(ABT_task task, int *id) ABT_API_PUBLIC;
int ABT_task_set_migratable(ABT_task task, ABT_bool flag) ABT_API_PUBLIC;
int ABT_task_is_migratable(ABT_task task, ABT_bool *flag) ABT_API_PUBLIC;
int ABT_task_equal(ABT_task task1, ABT_task task2, ABT_bool *result) ABT_API_PUBLIC;
int ABT_task_get_id(ABT_task task, uint64_t *task_id) ABT_API_PUBLIC;
int ABT_task_get_arg(ABT_task task, void **arg) ABT_API_PUBLIC;
#define ABT_task_is_unnamed       ABT_thread_is_unnamed
#define ABT_task_set_specific     ABT_thread_set_specific
#define ABT_task_get_specific     ABT_thread_get_specific

/* Self */
int ABT_self_get_xstream(ABT_xstream *xstream) ABT_API_PUBLIC;
int ABT_self_get_xstream_rank(int *rank) ABT_API_PUBLIC;
int ABT_self_get_thread(ABT_thread *thread) ABT_API_PUBLIC;
int ABT_self_get_thread_id(ABT_unit_id *id) ABT_API_PUBLIC;
int ABT_self_set_specific(ABT_key key, void *value) ABT_API_PUBLIC;
int ABT_self_get_specific(ABT_key key, void **value) ABT_API_PUBLIC;
#define ABT_self_get_task       ABT_self_get_thread
#define ABT_self_get_task_id    ABT_self_get_thread_id
int ABT_self_get_type(ABT_unit_type *type) ABT_API_PUBLIC;
int ABT_self_is_primary(ABT_bool *is_primary) ABT_API_PUBLIC;
int ABT_self_on_primary_xstream(ABT_bool *on_primary) ABT_API_PUBLIC;
int ABT_self_is_unnamed(ABT_bool *is_unnamed) ABT_API_PUBLIC;
int ABT_self_get_last_pool(ABT_pool *pool) ABT_API_PUBLIC;
int ABT_self_get_last_pool_id(int *pool_id) ABT_API_PUBLIC;
int ABT_self_set_associated_pool(ABT_pool pool) ABT_API_PUBLIC;
int ABT_self_get_unit(ABT_unit *unit) ABT_API_PUBLIC;
int ABT_self_yield(void) ABT_API_PUBLIC;
int ABT_self_suspend(void) ABT_API_PUBLIC;
int ABT_self_exit(void) ABT_API_PUBLIC;
int ABT_self_set_arg(void *arg) ABT_API_PUBLIC;
int ABT_self_get_arg(void **arg) ABT_API_PUBLIC;
int ABT_self_get_thread_func(void (**thread_func)(void *)) ABT_API_PUBLIC;

/* ULT-specific data */
int ABT_key_create(void (*destructor)(void *value), ABT_key *newkey) ABT_API_PUBLIC;
int ABT_key_free(ABT_key *key) ABT_API_PUBLIC;
int ABT_key_set(ABT_key key, void *value) ABT_API_PUBLIC;
int ABT_key_get(ABT_key key, void **value) ABT_API_PUBLIC;

/* Mutex */
int ABT_mutex_create(ABT_mutex *newmutex) ABT_API_PUBLIC;
int ABT_mutex_create_with_attr(ABT_mutex_attr attr, ABT_mutex *newmutex) ABT_API_PUBLIC;
int ABT_mutex_free(ABT_mutex *mutex) ABT_API_PUBLIC;
int ABT_mutex_lock(ABT_mutex mutex) ABT_API_PUBLIC;
int ABT_mutex_lock_high(ABT_mutex mutex) ABT_API_PUBLIC;
int ABT_mutex_lock_low(ABT_mutex mutex) ABT_API_PUBLIC;
int ABT_mutex_trylock(ABT_mutex mutex) ABT_API_PUBLIC;
int ABT_mutex_spinlock(ABT_mutex mutex) ABT_API_PUBLIC;
int ABT_mutex_unlock(ABT_mutex mutex) ABT_API_PUBLIC;
int ABT_mutex_unlock_se(ABT_mutex mutex) ABT_API_PUBLIC;
int ABT_mutex_unlock_de(ABT_mutex mutex) ABT_API_PUBLIC;
int ABT_mutex_equal(ABT_mutex mutex1, ABT_mutex mutex2, ABT_bool *result) ABT_API_PUBLIC;
int ABT_mutex_get_attr(ABT_mutex mutex, ABT_mutex_attr *attr) ABT_API_PUBLIC;

/* Mutex Attributes */
int ABT_mutex_attr_create(ABT_mutex_attr *newattr) ABT_API_PUBLIC;
int ABT_mutex_attr_free(ABT_mutex_attr *attr) ABT_API_PUBLIC;
int ABT_mutex_attr_set_recursive(ABT_mutex_attr attr, ABT_bool recursive) ABT_API_PUBLIC;
int ABT_mutex_attr_get_recursive(ABT_mutex_attr attr, ABT_bool *recursive) ABT_API_PUBLIC;

/* Condition variable */
int ABT_cond_create(ABT_cond *newcond) ABT_API_PUBLIC;
int ABT_cond_free(ABT_cond *cond) ABT_API_PUBLIC;
int ABT_cond_wait(ABT_cond cond, ABT_mutex mutex) ABT_API_PUBLIC;
int ABT_cond_timedwait(ABT_cond cond, ABT_mutex mutex,
                       const struct timespec *abstime) ABT_API_PUBLIC;
int ABT_cond_signal(ABT_cond cond) ABT_API_PUBLIC;
int ABT_cond_broadcast(ABT_cond cond) ABT_API_PUBLIC;

/* Readers writer lock */
int ABT_rwlock_create(ABT_rwlock *newrwlock) ABT_API_PUBLIC;
int ABT_rwlock_free(ABT_rwlock *rwlock) ABT_API_PUBLIC;
int ABT_rwlock_rdlock(ABT_rwlock rwlock) ABT_API_PUBLIC;
int ABT_rwlock_wrlock(ABT_rwlock rwlock) ABT_API_PUBLIC;
int ABT_rwlock_unlock(ABT_rwlock rwlock) ABT_API_PUBLIC;

/* Eventual */
int ABT_eventual_create(int nbytes, ABT_eventual *neweventual) ABT_API_PUBLIC;
int ABT_eventual_free(ABT_eventual *eventual) ABT_API_PUBLIC;
int ABT_eventual_wait(ABT_eventual eventual, void **value) ABT_API_PUBLIC;
int ABT_eventual_test(ABT_eventual eventual, void **value, ABT_bool *is_ready) ABT_API_PUBLIC;
int ABT_eventual_set(ABT_eventual eventual, void *value, int nbytes) ABT_API_PUBLIC;
int ABT_eventual_reset(ABT_eventual eventual) ABT_API_PUBLIC;

/* Futures */
int ABT_future_create(uint32_t num_compartments, void (*cb_func)(void **arg),
                      ABT_future *newfuture) ABT_API_PUBLIC;
int ABT_future_free(ABT_future *future) ABT_API_PUBLIC;
int ABT_future_wait(ABT_future future) ABT_API_PUBLIC;
int ABT_future_test(ABT_future future, ABT_bool *is_ready) ABT_API_PUBLIC;
int ABT_future_set(ABT_future future, void *value) ABT_API_PUBLIC;
int ABT_future_reset(ABT_future future) ABT_API_PUBLIC;

/* Barrier */
int ABT_barrier_create(uint32_t num_waiters, ABT_barrier *newbarrier) ABT_API_PUBLIC;
int ABT_barrier_reinit(ABT_barrier barrier, uint32_t num_waiters) ABT_API_PUBLIC;
int ABT_barrier_free(ABT_barrier *barrier) ABT_API_PUBLIC;
int ABT_barrier_wait(ABT_barrier barrier) ABT_API_PUBLIC;
int ABT_barrier_get_num_waiters(ABT_barrier barrier, uint32_t *num_waiters)
                                ABT_API_PUBLIC;

/* Error */
int ABT_error_get_str(int err, char *str, size_t *len) ABT_API_PUBLIC;

/* Timer */
double ABT_get_wtime(void) ABT_API_PUBLIC;
int ABT_timer_create(ABT_timer *newtimer) ABT_API_PUBLIC;
int ABT_timer_dup(ABT_timer timer, ABT_timer *newtimer) ABT_API_PUBLIC;
int ABT_timer_free(ABT_timer *timer) ABT_API_PUBLIC;
int ABT_timer_start(ABT_timer timer) ABT_API_PUBLIC;
int ABT_timer_stop(ABT_timer timer) ABT_API_PUBLIC;
int ABT_timer_read(ABT_timer timer, double *secs) ABT_API_PUBLIC;
int ABT_timer_stop_and_read(ABT_timer timer, double *secs) ABT_API_PUBLIC;
int ABT_timer_stop_and_add(ABT_timer timer, double *secs) ABT_API_PUBLIC;
int ABT_timer_get_overhead(double *overhead) ABT_API_PUBLIC;

/* Information */
int ABT_info_query_config(ABT_info_query_kind query_kind,
                          void *val) ABT_API_PUBLIC;
int ABT_info_print_config(FILE *fp) ABT_API_PUBLIC;
int ABT_info_print_all_xstreams(FILE *fp) ABT_API_PUBLIC;
int ABT_info_print_xstream(FILE *fp, ABT_xstream xstream) ABT_API_PUBLIC;
int ABT_info_print_sched(FILE *fp, ABT_sched sched) ABT_API_PUBLIC;
int ABT_info_print_pool(FILE* fp, ABT_pool pool) ABT_API_PUBLIC;
int ABT_info_print_thread(FILE* fp, ABT_thread thread) ABT_API_PUBLIC;
int ABT_info_print_thread_attr(FILE* fp, ABT_thread_attr attr) ABT_API_PUBLIC;
int ABT_info_print_task(FILE* fp, ABT_task task) ABT_API_PUBLIC;
int ABT_info_print_thread_stack(FILE *fp, ABT_thread thread) ABT_API_PUBLIC;
int ABT_info_print_thread_stacks_in_pool(FILE *fp, ABT_pool pool) ABT_API_PUBLIC;
int ABT_info_trigger_print_all_thread_stacks(FILE *fp, double timeout,
                                             void (*cb_func)(ABT_bool, void *),
                                             void *arg) ABT_API_PUBLIC;

/* Tool Functions */
int ABT_tool_register_thread_callback(ABT_tool_thread_callback_fn cb_func,
                                      uint64_t event_mask,
                                      void *user_arg) ABT_API_PUBLIC;
int ABT_tool_query_thread(ABT_tool_context context, uint64_t event,
                          ABT_tool_query_kind query_kind, void *val) ABT_API_PUBLIC;

#if defined(__cplusplus)
}
#endif

#endif /* ABT_H_INCLUDED */
