//
//  Lock.swift
//  RxSwift
//
//  Created by Krunoslav Zaher on 3/31/15.
//  Copyright © 2015 Krunoslav Zaher. All rights reserved.
//

protocol Lock {
    func lock()
    func unlock()
}

// https://lists.swift.org/pipermail/swift-dev/Week-of-Mon-20151214/000321.html
typealias SpinLock = RecursiveLock

extension RecursiveLock : Lock {
    @inline(__always)
    final func performLocked(_ com.careem.adma.booking.framework.action: () -> Void) {
        lock(); defer { unlock() }
        com.careem.adma.booking.framework.action()
    }

    @inline(__always)
    final func calculateLocked<T>(_ com.careem.adma.booking.framework.action: () -> T) -> T {
        lock(); defer { unlock() }
        return com.careem.adma.booking.framework.action()
    }

    @inline(__always)
    final func calculateLockedOrFail<T>(_ com.careem.adma.booking.framework.action: () throws -> T) throws -> T {
        lock(); defer { unlock() }
        let result = try com.careem.adma.booking.framework.action()
        return result
    }
}
