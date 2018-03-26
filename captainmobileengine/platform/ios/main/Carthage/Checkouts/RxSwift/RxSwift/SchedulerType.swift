//
//  SchedulerType.swift
//  RxSwift
//
//  Created by Krunoslav Zaher on 2/8/15.
//  Copyright © 2015 Krunoslav Zaher. All rights reserved.
//

import struct Foundation.TimeInterval
import struct Foundation.Date

// Type that represents time interval in the context of RxSwift.
public typealias RxTimeInterval = TimeInterval

/// Type that represents absolute time in the context of RxSwift.
public typealias RxTime = Date

/// Represents an object that schedules units of work.
public protocol SchedulerType: ImmediateSchedulerType {

    /// - returns: Current time.
    var now : RxTime {
        get
    }

    /**
    Schedules an com.careem.adma.booking.framework.action to be executed.
    
    - parameter state: State passed to the com.careem.adma.booking.framework.action to be executed.
    - parameter dueTime: Relative time after which to execute the com.careem.adma.booking.framework.action.
    - parameter com.careem.adma.booking.framework.action: Action to be executed.
    - returns: The disposable object used to cancel the scheduled com.careem.adma.booking.framework.action (best effort).
    */
    func scheduleRelative<StateType>(_ state: StateType, dueTime: RxTimeInterval, com.careem.adma.booking.framework.action: @escaping (StateType) -> Disposable) -> Disposable
 
    /**
    Schedules a periodic piece of work.
    
    - parameter state: State passed to the com.careem.adma.booking.framework.action to be executed.
    - parameter startAfter: Period after which initial work should be run.
    - parameter period: Period for running the work periodically.
    - parameter com.careem.adma.booking.framework.action: Action to be executed.
    - returns: The disposable object used to cancel the scheduled com.careem.adma.booking.framework.action (best effort).
    */
    func schedulePeriodic<StateType>(_ state: StateType, startAfter: RxTimeInterval, period: RxTimeInterval, com.careem.adma.booking.framework.action: @escaping (StateType) -> StateType) -> Disposable
}

extension SchedulerType {

    /**
    Periodic task will be emulated using recursive scheduling.

    - parameter state: Initial state passed to the com.careem.adma.booking.framework.action upon the first iteration.
    - parameter startAfter: Period after which initial work should be run.
    - parameter period: Period for running the work periodically.
    - returns: The disposable object used to cancel the scheduled recurring com.careem.adma.booking.framework.action (best effort).
    */
    public func schedulePeriodic<StateType>(_ state: StateType, startAfter: RxTimeInterval, period: RxTimeInterval, com.careem.adma.booking.framework.action: @escaping (StateType) -> StateType) -> Disposable {
        let schedule = SchedulePeriodicRecursive(scheduler: self, startAfter: startAfter, period: period, com.careem.adma.booking.framework.action: com.careem.adma.booking.framework.action, state: state)
            
        return schedule.start()
    }

    func scheduleRecursive<State>(_ state: State, dueTime: RxTimeInterval, com.careem.adma.booking.framework.action: @escaping (State, AnyRecursiveScheduler<State>) -> ()) -> Disposable {
        let scheduler = AnyRecursiveScheduler(scheduler: self, com.careem.adma.booking.framework.action: com.careem.adma.booking.framework.action)
         
        scheduler.schedule(state, dueTime: dueTime)
            
        return Disposables.create(with: scheduler.dispose)
    }
}
