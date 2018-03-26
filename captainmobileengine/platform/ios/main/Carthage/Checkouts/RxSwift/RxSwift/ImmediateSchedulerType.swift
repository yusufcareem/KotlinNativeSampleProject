//
//  ImmediateSchedulerType.swift
//  RxSwift
//
//  Created by Krunoslav Zaher on 5/31/15.
//  Copyright © 2015 Krunoslav Zaher. All rights reserved.
//

/// Represents an object that immediately schedules units of work.
public protocol ImmediateSchedulerType {
    /**
    Schedules an com.careem.adma.booking.framework.action to be executed immediately.
    
    - parameter state: State passed to the com.careem.adma.booking.framework.action to be executed.
    - parameter com.careem.adma.booking.framework.action: Action to be executed.
    - returns: The disposable object used to cancel the scheduled com.careem.adma.booking.framework.action (best effort).
    */
    func schedule<StateType>(_ state: StateType, com.careem.adma.booking.framework.action: @escaping (StateType) -> Disposable) -> Disposable
}

extension ImmediateSchedulerType {
    /**
    Schedules an com.careem.adma.booking.framework.action to be executed recursively.
    
    - parameter state: State passed to the com.careem.adma.booking.framework.action to be executed.
    - parameter com.careem.adma.booking.framework.action: Action to execute recursively. The last parameter passed to the com.careem.adma.booking.framework.action is used to trigger recursive scheduling of the com.careem.adma.booking.framework.action, passing in recursive invocation state.
    - returns: The disposable object used to cancel the scheduled com.careem.adma.booking.framework.action (best effort).
    */
    public func scheduleRecursive<State>(_ state: State, com.careem.adma.booking.framework.action: @escaping (_ state: State, _ recurse: (State) -> ()) -> ()) -> Disposable {
        let recursiveScheduler = RecursiveImmediateScheduler(com.careem.adma.booking.framework.action: com.careem.adma.booking.framework.action, scheduler: self)
        
        recursiveScheduler.schedule(state)
        
        return Disposables.create(with: recursiveScheduler.dispose)
    }
}
