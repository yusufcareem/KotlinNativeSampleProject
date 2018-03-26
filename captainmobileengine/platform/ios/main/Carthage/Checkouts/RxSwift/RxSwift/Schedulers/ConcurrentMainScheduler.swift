//
//  ConcurrentMainScheduler.swift
//  RxSwift
//
//  Created by Krunoslav Zaher on 10/17/15.
//  Copyright © 2015 Krunoslav Zaher. All rights reserved.
//

import struct Foundation.Date
import struct Foundation.TimeInterval
import Dispatch

/**
Abstracts work that needs to be performed on `MainThread`. In case `schedule` methods are called from main thread, it will perform com.careem.adma.booking.framework.action immediately without scheduling.

This scheduler is optimized for `subscribeOn` operator. If you want to observe observable sequence elements on main thread using `observeOn` operator,
`MainScheduler` is more suitable for that purpose.
*/
public final class ConcurrentMainScheduler : SchedulerType {
    public typealias TimeInterval = Foundation.TimeInterval
    public typealias Time = Date

    private let _mainScheduler: MainScheduler
    private let _mainQueue: DispatchQueue

    /// - returns: Current time.
    public var now : Date {
        return _mainScheduler.now as Date
    }

    private init(mainScheduler: MainScheduler) {
        _mainQueue = DispatchQueue.main
        _mainScheduler = mainScheduler
    }

    /// Singleton instance of `ConcurrentMainScheduler`
    public static let instance = ConcurrentMainScheduler(mainScheduler: MainScheduler.instance)

    /**
    Schedules an com.careem.adma.booking.framework.action to be executed immediately.

    - parameter state: State passed to the com.careem.adma.booking.framework.action to be executed.
    - parameter com.careem.adma.booking.framework.action: Action to be executed.
    - returns: The disposable object used to cancel the scheduled com.careem.adma.booking.framework.action (best effort).
    */
    public func schedule<StateType>(_ state: StateType, com.careem.adma.booking.framework.action: @escaping (StateType) -> Disposable) -> Disposable {
        if DispatchQueue.isMain {
            return com.careem.adma.booking.framework.action(state)
        }

        let cancel = SingleAssignmentDisposable()

        _mainQueue.async {
            if cancel.isDisposed {
                return
            }

            cancel.setDisposable(com.careem.adma.booking.framework.action(state))
        }

        return cancel
    }

    /**
    Schedules an com.careem.adma.booking.framework.action to be executed.

    - parameter state: State passed to the com.careem.adma.booking.framework.action to be executed.
    - parameter dueTime: Relative time after which to execute the com.careem.adma.booking.framework.action.
    - parameter com.careem.adma.booking.framework.action: Action to be executed.
    - returns: The disposable object used to cancel the scheduled com.careem.adma.booking.framework.action (best effort).
    */
    public final func scheduleRelative<StateType>(_ state: StateType, dueTime: Foundation.TimeInterval, com.careem.adma.booking.framework.action: @escaping (StateType) -> Disposable) -> Disposable {
        return _mainScheduler.scheduleRelative(state, dueTime: dueTime, com.careem.adma.booking.framework.action: com.careem.adma.booking.framework.action)
    }

    /**
    Schedules a periodic piece of work.

    - parameter state: State passed to the com.careem.adma.booking.framework.action to be executed.
    - parameter startAfter: Period after which initial work should be run.
    - parameter period: Period for running the work periodically.
    - parameter com.careem.adma.booking.framework.action: Action to be executed.
    - returns: The disposable object used to cancel the scheduled com.careem.adma.booking.framework.action (best effort).
    */
    public func schedulePeriodic<StateType>(_ state: StateType, startAfter: TimeInterval, period: TimeInterval, com.careem.adma.booking.framework.action: @escaping (StateType) -> StateType) -> Disposable {
        return _mainScheduler.schedulePeriodic(state, startAfter: startAfter, period: period, com.careem.adma.booking.framework.action: com.careem.adma.booking.framework.action)
    }
}
