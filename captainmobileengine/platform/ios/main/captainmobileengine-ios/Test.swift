//
//  Test.swift
//  captainmobileengine-ios
//
//  Created by Yusuf Afghan on 3/7/18.
//  Copyright © 2018 Andres Portillo. All rights reserved.
//

import Foundation
import CaptainMobileEngine
import RxSwift


class BookingStateStore: CMEStore {
    
    override func notifyOnStateChanged(stateChange: CMEStateChange) {
        
        print("notifyOnStateChangedCalled")
    }
}

class BookingStoreState: CMEState {
    
}

class Test {
    
    func test() {
        
        let store = BookingStateStore(state: BookingStoreState(), reducers: <#T##[AnyHashable : CMEReducer]#>, commands: <#T##[AnyHashable : CMECommand]#>, logManager: <#T##CMELogManager#>)
    }
}

//
//class CMEBehaviorSubjectImpl: CMEBehaviorSubject {
//    
//    func doOnNext(onNext: @escaping (Any?) -> CMEStdlibUnit) -> CMEObservable {
//        
//        let behaviorSubject = BehaviorSubject.creat
//    }
//    
//    func onNext(onNext thing: Any?) {
//        
//        BehaviorSubject.onNext(thing)
//    }
//    
//    func subscribe() {
//        
//    }
//    
//    func subscribe(callback: @escaping (Any?) -> CMEStdlibUnit) {
//        
//    }
//    
//    func subscribeOn(on: CMEScheduler) -> CMEObservable {
//        
//    }
//    
//    func toSerialized() -> CMEBehaviorSubject {
//        
//    }
//}

