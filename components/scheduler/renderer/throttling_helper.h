// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SCHEDULER_RENDERER_THROTTLING_HELPER_H_
#define COMPONENTS_SCHEDULER_RENDERER_THROTTLING_HELPER_H_

#include <set>

#include "base/macros.h"
#include "components/scheduler/base/cancelable_closure_holder.h"
#include "components/scheduler/base/time_domain.h"
#include "components/scheduler/scheduler_export.h"
#include "third_party/WebKit/public/platform/WebViewScheduler.h"

namespace scheduler {

class RendererSchedulerImpl;
class VirtualTimeDomain;
class WebFrameSchedulerImpl;

class SCHEDULER_EXPORT ThrottlingHelper : public TimeDomain::Observer {
 public:
  ThrottlingHelper(RendererSchedulerImpl* renderer_scheduler,
                   const char* tracing_category);

  ~ThrottlingHelper() override;

  // TimeDomain::Observer implementation:
  void OnTimeDomainHasImmediateWork() override;
  void OnTimeDomainHasDelayedWork() override;

  void Throttle(TaskQueue* task_queue);
  void Unthrottle(TaskQueue* task_queue);

  const VirtualTimeDomain* time_domain() const { return time_domain_.get(); }

  static base::TimeTicks ThrottledRunTime(base::TimeTicks unthrottled_runtime);

  const scoped_refptr<TaskQueue>& task_runner() const { return task_runner_; }

 private:
  void PumpThrottledTasks();
  void MaybeSchedulePumpThrottledTasksLocked(
      const tracked_objects::Location& from_here,
      base::TimeTicks now,
      base::TimeTicks unthrottled_runtime);

  std::set<TaskQueue*> throttled_queues_;
  base::Closure forward_immediate_work_closure_;
  scoped_refptr<TaskQueue> task_runner_;
  RendererSchedulerImpl* renderer_scheduler_;  // NOT OWNED
  base::TickClock* tick_clock_;                // NOT OWNED
  const char* tracing_category_;               // NOT OWNED
  scoped_ptr<VirtualTimeDomain> time_domain_;

  CancelableClosureHolder suspend_timers_when_backgrounded_closure_;
  base::TimeTicks pending_pump_throttled_tasks_runtime_;

  base::WeakPtrFactory<ThrottlingHelper> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ThrottlingHelper);
};

}  // namespace scheduler

#endif  // COMPONENTS_SCHEDULER_RENDERER_THROTTLING_HELPER_H_
