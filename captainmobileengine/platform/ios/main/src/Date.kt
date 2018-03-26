package com.careem.adma.booking.framework.Date

import platform.Foundation.*

actual class Date actual constructor () {
    actual companion object {
        actual val current: Double = NSDate.timeIntervalSince1970()
    }
}
