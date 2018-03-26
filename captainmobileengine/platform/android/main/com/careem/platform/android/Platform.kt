package com.careem.platform.android

actual class Platform(url: String) {
    actual fun get():String {
        return "test"
    }
}

//actual class System {
//
//    actual constructor()
//}