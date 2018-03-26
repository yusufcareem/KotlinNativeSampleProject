## RxSwift KISS code generator.

RxSwift code is partially machine generated. 
It converts *.tt files into generated *.swift files.

There are multiple reasons why that is the case.

* Performance
* Consistency
* Removes burden from developers (me :)
* It's fun

To see how it in com.careem.adma.booking.framework.action, take a look at

CombineLatest+arity.tt
CombineLatest+arity.swift

```
//
//  CombineLatest.tt.swift
//  RxSwift
//
//  Created by Krunoslav Zaher on 4/22/15.
//  Copyright (c) 2015 Krunoslav Zaher. All rights reserved.
//

import Foundation

<% for i in 2 ... 10 { %>

// <%= i %>

public func combineLatestOrDie<<%= ", ".join(map(1...i) { "E\($0)" }) %>, R>
    (<%= ", ".join(map(1...i) { "source\($0): Observable<E\($0)>" }) %>, resultSelector: (<%= ", ".join(map(1...i) { "E\($0)" }) %>) -> Result<R>)
        -> Observable<R> {
    return CombineLatest<%= i %>(
        <%= ", ".join(map(1...i) { "source\($0): source\($0)" }) %>,
        resultSelector: resultSelector
    )
}

public func combineLatest<<%= ", ".join(map(1...i) { "E\($0)" }) %>, R>
    (<%= ", ".join(map(1...i) { "source\($0): Observable<E\($0)>" }) %>, resultSelector: (<%= ", ".join(map(1...i) { "E\($0)" }) %>) -> R)
        -> Observable<R> {
    return CombineLatest<%= i %>(
        <%= ", ".join(map(1...i) { "source\($0): source\($0)" }) %>,
        resultSelector: { success(resultSelector(<%= ", ".join(map(0..<i) { "$\($0)" }) %>)) }
    )
}
```

to 

```
// This file is autogenerated.
// Take a look at `Preprocessor` target in RxSwift project 
//
//  CombineLatest.tt.swift
//  RxSwift
//
//  Created by Krunoslav Zaher on 4/22/15.
//  Copyright (c) 2015 Krunoslav Zaher. All rights reserved.
//

import Foundation



// 2

public func combineLatestOrDie<E1, E2, R>
    (source1: Observable<E1>, source2: Observable<E2>, resultSelector: (E1, E2) -> Result<R>)
        -> Observable<R> {
    return CombineLatest2(
        source1: source1, source2: source2,
        resultSelector: resultSelector
    )
}

public func combineLatest<E1, E2, R>
    (source1: Observable<E1>, source2: Observable<E2>, resultSelector: (E1, E2) -> R)
        -> Observable<R> {
    return CombineLatest2(
        source1: source1, source2: source2,
        resultSelector: { success(resultSelector($0, $1)) }
    )
}

```


It's pretty generic, I'm thinking of extracting it as a separate project.